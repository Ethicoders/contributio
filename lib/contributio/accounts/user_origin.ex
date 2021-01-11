defmodule Contributio.Accounts.UserOrigin do
  use Ecto.Schema
  import Ecto.Changeset

  schema "users_origins" do

    has_many :users, Contributio.Accounts.User
    has_many :origins, Contributio.Market.Origin
    field :user_origin_id, :integer
    field :access_token, :string

    timestamps()
  end

  def changeset(user, attrs) do
    user
    |> cast(attrs, [:user_origin_id, :access_token])
  end
end
