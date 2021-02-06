defmodule Contributio.Market.UserContribution do
  use Ecto.Schema
  import Ecto.Changeset

  schema "users_contributions" do

    belongs_to :user, Contributio.Accounts.User
    belongs_to :contribution, Contributio.Market.Contribution
  end

  def changeset(user, attrs) do
    user
    |> cast(attrs, [:user_id, :contribution_id])
  end
end
