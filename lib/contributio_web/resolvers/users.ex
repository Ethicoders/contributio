defmodule Resolvers.Users do
  require Logger
  alias Contributio.{Accounts, Repo}

  def get_user(%{id: id}, _info) do
    {:ok,
     Accounts.get_user(id) |> Repo.preload(:projects) |> Accounts.User.set_next_level_experience()}
  end

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

  # Authorized context, can fetch sensitive data
  def get_current_user(_args, %{context: %{current_user: current_user}}) do
    {:ok, current_user |> Repo.preload(:projects)}
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

  # VCS part
  def request_access_token(%{code: code}, %{context: %{current_user: _current_user}}) do
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

  def request_access_token(_args, _info), do: {:error, "Not Authorized"}

  def set_access_token(%{vendor: vendor, content: content}, %{
        context: %{current_user: current_user}
      }) do
    access_tokens =
      case current_user.access_tokens do
        nil -> Map.put(%{}, vendor, content)
        _ -> current_user.access_tokens |> Map.put(vendor, %{content: content})
      end

    # Check other platforms but should be stored as:
    # {
    #   access_token: 4a7c72cc2eaa8e3fa6c988b94543d31f28396a96,
    #   expires_in: 28800,
    #   refresh_token: r1.a4f05c7626645166071140fcd4bd0f0ea70173ae20959d3efd2bda2c3c25f73880fafc4b164d57a1,
    #   refresh_token_expires_in: 15724800,
    #   scope: , ???
    #   token_type: bearer
    # }

    current_user
    |> Accounts.User.changeset(%{access_tokens: access_tokens})
    |> Repo.update!()

    {:ok, current_user}
  end

  def link_account(%{vendor: vendor, content: content}, %{
        context: %{current_user: current_user}
      }) do
    access_tokens =
      case current_user.access_tokens do
        nil -> Map.put(%{}, vendor, content)
        _ -> current_user.access_tokens |> Map.put(vendor, content)
      end

    access_token = current_user.access_tokens[vendor]

    origin_id =
      case HTTPoison.get(
             "https://api.github.com/user",
             "Content-Type": "application/json",
             Authorization: "token #{access_token}"
           ) do
        {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
          case Jason.decode!(body, keys: :atoms) do
            user -> user.id
          end

        {:error, %HTTPoison.Error{reason: reason}} ->
          IO.inspect(inspect(reason))
      end

    origin_ids =
      case current_user.origin_ids do
        nil -> Map.put(%{}, vendor, origin_id)
        _ -> current_user.origin_ids |> Map.put(vendor, origin_id)
      end

    current_user
    |> Accounts.User.changeset(%{access_tokens: access_tokens, origin_ids: origin_ids})
    |> Repo.update!()

    {:ok, current_user}
  end

  def link_account(_args, _info), do: {:error, "Not Authorized"}

  def fetch_repositories(%{vendor: vendor}, %{
        context: %{current_user: current_user}
      }) do
    # with repos <- Contributio.Platforms.GitHub.get(
    #   "/user/repos",
    #   current_user.access_tokens[vendor],
    #   %{type: "public"}
    # ) do
    #   Logger.debug(inspect repos)
    # end

    access_token = current_user.access_tokens[vendor]

    case HTTPoison.get(
           "https://api.github.com/user/repos",
           ["Content-Type": "application/json", Authorization: "token #{access_token}"],
           params: %{type: "public"}
         ) do
      {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
        case Jason.decode!(body, keys: :atoms) do
          repos ->
            {:ok, repos}
        end

      {:error, %HTTPoison.Error{reason: reason}} ->
        IO.inspect(reason)
    end
  end

  def import_repositories(%{vendor: vendor, ids: ids}, %{
        context: %{current_user: current_user}
      }) do
    access_token = current_user.access_tokens[vendor]

    ids
    |> Enum.map(
      &case HTTPoison.get(
              "https://api.github.com/repositories/#{&1}",
              ["Content-Type": "application/json", Authorization: "token #{access_token}"],
              params: %{type: "public"},
              hackney: [pool: :default]
            ) do
        {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
          case Jason.decode!(body, keys: :atoms) do
            repo ->
              case HTTPoison.get(
                     repo.languages_url,
                     ["Content-Type": "application/json"],
                     hackney: [pool: :default]
                   ) do
                {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
                  case Jason.decode!(body, keys: :atoms) do
                    languages ->
                      Contributio.Market.create_project(%{
                        name: repo.name,
                        repo_id: repo.id,
                        description: repo.description,
                        url: repo.html_url,
                        languages: languages,
                        user_id: current_user.id
                      })
                  end
              end
          end

        {:error, %HTTPoison.Error{reason: reason}} ->
          IO.inspect(reason)
      end
    )

    {:ok, true}
  end
end
