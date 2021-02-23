defmodule Contributio.Accounts.User do
  use Ecto.Schema
  import Ecto.Changeset
  require Logger

  schema "users" do
    field :name, :string
    field :email, :string
    field :password, :string, virtual: true
    field :hash, :string, allow_nil: true # Can be nil for users using GH login
    field :token, :string, allow_nil: true
    field :level, :integer
    field :current_experience, :integer
    field :next_level_experience, :integer, virtual: true
    has_many :projects, Contributio.Market.Project
    has_many :users_origins, Contributio.Accounts.UserOrigin
    many_to_many :contributions, Contributio.Market.Contribution, join_through: :users_contributions
  end

  @doc false
  def changeset(user, attrs) do
    user
    |> cast(attrs, [:name, :email, :password, :hash, :token, :level, :current_experience])
    # , :password
    |> validate_required([:email])
    |> unique_constraint(:email)

    # |> set_password_hash()
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

  def set_next_level_experience(%Contributio.Accounts.User{} = user) do
    %{
      user
      | next_level_experience: Contributio.Game.get_level_experience(user.level)
    }
  end
end
