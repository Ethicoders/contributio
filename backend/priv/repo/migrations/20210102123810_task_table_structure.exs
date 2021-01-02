defmodule Contributio.Repo.Migrations.TaskTableStructure do
  use Ecto.Migration

  def change do
    alter table(:tasks) do
      add :content, :string
      add :url, :string
      add :issue_id, :integer
      add :difficulty, :integer
      add :project_id, references(:projects)
    end
  end
end
