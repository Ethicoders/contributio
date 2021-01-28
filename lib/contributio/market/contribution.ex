defmodule Contributio.Market.Contribution do
  use Ecto.Schema
  import Ecto.Changeset

  schema "contributions" do
    field :status, :integer
    belongs_to :user, Contributio.Accounts.User

    timestamps()
  end

  @doc false
  def changeset(contribution, attrs) do
    contribution
    |> cast(attrs, [:status])
    |> validate_required([])
  end
end
