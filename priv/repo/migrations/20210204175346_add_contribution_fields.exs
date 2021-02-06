defmodule Contributio.Repo.Migrations.AddContributionFields do
  use Ecto.Migration

  def change do
    create table(:users_contributions) do
      add :user_id, references(:users)
      add :contribution_id, references(:contributions)
    end

    create unique_index(:users_contributions, [:user_id, :contribution_id])

    alter table(:contributions) do
      add :status, :integer, default: 0
      add :pull_request_id, :string
      add :rewarded, :boolean, default: false
      add :task_id, references(:tasks)
    end
  end
end
