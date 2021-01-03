defmodule Contributio.Market.Submission do
  use Ecto.Schema
  import Ecto.Changeset

  schema "submissions" do
    field :status, :integer
    belongs_to :user, Contributio.Accounts.User

    timestamps()
  end

  @doc false
  def changeset(submission, attrs) do
    submission
    |> cast(attrs, [:status])
    |> validate_required([])
  end
end
