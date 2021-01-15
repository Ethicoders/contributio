defmodule Contributio.Platforms.Origin do
  use Ecto.Schema
  import Ecto.Changeset

  schema "origins" do
    field :name, :string
    field :url, :string
    field :webhook_secret, :string
    has_many :users_origins, Contributio.Accounts.UserOrigin
    has_many :projects, Contributio.Market.Project
  end

  @doc false
  def changeset(origin, attrs) do
    origin
    |> cast(attrs, [])
    |> validate_required([])
  end
end
