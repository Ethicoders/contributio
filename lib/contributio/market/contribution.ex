defmodule Contributio.Market.Contribution do
  use Ecto.Schema
  import Ecto.Changeset

  schema "contributions" do
    field :status, :integer
    field :pull_request_id, :string
    field :rewarded, :boolean
    many_to_many :users, Contributio.Accounts.User, join_through: "users_contributions"
    belongs_to :task, Contributio.Market.Task

    timestamps()
  end

  @doc false
  def changeset(contribution, attrs) do
    contribution
    |> cast(attrs, [:status, :pull_request_id, :rewarded, :task_id])
    |> validate_required([])
  end
end
