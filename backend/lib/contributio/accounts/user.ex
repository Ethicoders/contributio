defmodule Contributio.Accounts.User do
  use Ecto.Schema
  import Ecto.Changeset
  require Logger

  schema "users" do
    field :email, :string
    field :password, :string, virtual: true
    field :hash, :string
    field :token, :string, allow_nil: true
    # field :access_tokens, :map

    timestamps()
  end

  @doc false
  def changeset(user, attrs) do
    user
    |> cast(attrs, [:email, :password, :hash, :token])
    |> validate_required([:email, :password])
    |> unique_constraint(:email)
    |> set_password_hash()
  end

  defp set_password_hash(
         %Ecto.Changeset{valid?: true, changes: %{password: password}} = changeset
       ) do
    put_change(
      changeset,
      :hash,
      Bcrypt.hash_pwd_salt(
        password
        # Bcrypt.gen_salt(12, true)
      )
    )
  end
end
