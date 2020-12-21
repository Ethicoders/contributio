defmodule Resolvers.Users do
  def create(params, _info) do
    Contributio.Accounts.create_user(params)
  end

  def login(%{email: email, password: password}, _info) do
    email
    |> Contributio.Accounts.get_user_by_email()
    |> Bcrypt.check_pass(password, hash_key: :hash)
  end
end
