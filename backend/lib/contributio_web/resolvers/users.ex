defmodule Resolvers.Users do
  def create(params, _info) do
    Contributio.Accounts.create_user(params)
  end

  def authenticate(%{email: email, password: password}, _info) do
    case email
         |> Contributio.Accounts.get_user_by_email()
         |> Bcrypt.check_pass(password, hash_key: :hash) do
      {:ok, user} ->
        {:ok, token, _} = ContributioWeb.Guardian.encode_and_sign(user)
        {:ok, %{user: user, jwt: token}}
      payload when payload in [{:error, "invalid user-identifier"}, {:error, "invalid password"}] ->
        {:error, "Invalid email or password."}
    end
  end
end
