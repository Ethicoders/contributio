defmodule Resolvers.Users do
  require Logger
  alias Contributio.{Accounts, Repo}

  def create(params, _info) do
    Accounts.create_user(params)
  end

  def update_current_user(params, %{context: %{current_user: current_user}}) do
    current_user
    |> Accounts.User.changeset(params)
    |> Repo.update!()

    {:ok, %{user: current_user}}
  end

  def update_current_user(_args, _info), do: {:error, "Not Authorized"}

  def set_access_token(%{vendor: vendor, content: content}, %{
        context: %{current_user: current_user}
      }) do

    access_tokens =
      case current_user.access_tokens do
        nil -> Map.put(%{}, vendor, content)
        _ -> current_user.access_tokens |> Map.put(vendor, %{content: content})
      end

    current_user
    |> Accounts.User.changeset(%{access_tokens: access_tokens})
    |> Repo.update!()

    {:ok, current_user}
  end

  # Authorized context, can fetch sensitive data
  def get_current_user(_args, %{context: %{current_user: current_user}}) do
    {:ok, Map.merge(current_user, %{projects: []})}
  end

  def get_current_user(_args, _info), do: {:error, "Not Authorized"}

  def authenticate(%{email: email, password: password}, _info) do
    case email
         |> Accounts.get_user_by_email()
         |> Bcrypt.check_pass(password, hash_key: :hash) do
      {:ok, user} ->
        token = Phoenix.Token.sign(ContributioWeb.Endpoint, "user auth", user.id)

        user
        |> Accounts.User.changeset(%{token: token})
        |> Repo.update!()

        {:ok, %{user: user, token: token}}

      payload
      when payload in [{:error, "invalid user-identifier"}, {:error, "invalid password"}] ->
        {:error, "Invalid email or password."}
    end
  end

  def request_access_token(%{code: code}, _info) do
    case HTTPoison.post(
           "https://github.com/login/oauth/access_token",
           Jason.encode!(%{
             code: code,
             client_id: System.get_env("GITHUB_CLIENT_ID"),
             client_secret: System.get_env("GITHUB_CLIENT_SECRET")
           }),
           [{"Content-Type", "application/json"}]
         ) do
      {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
        {:ok, %{access_token: body}}

      {:error, %HTTPoison.Error{reason: reason}} ->
        IO.inspect(reason)
    end
  end
end
