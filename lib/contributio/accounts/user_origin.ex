defmodule Contributio.Accounts.UserOrigin do
  use Ecto.Schema
  import Ecto.Changeset

  schema "users_origins" do

    belongs_to :user, Contributio.Accounts.User
    belongs_to :origin, Contributio.Platforms.Origin
    field :user_origin_id, :integer
    field :access_token, :string
  end

  def changeset(user, attrs) do
    user
    |> cast(attrs, [:user_id, :origin_id, :user_origin_id, :access_token])
  end
end
