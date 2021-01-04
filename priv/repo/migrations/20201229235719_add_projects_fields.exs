defmodule Contributio.Repo.Migrations.AddProjectsFields do
  use Ecto.Migration

  def change do
    alter table(:projects) do
      add :repo_id, :integer
      add :description, :string
      add :url, :string
      add :languages, :map
    end
  end
end
