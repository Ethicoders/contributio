defmodule Contributio.Repo.Migrations.AddUserTable do
  use Ecto.Migration

  def change do
    create table("users") do
      add :name, :string
      add :email, :string
      add :hash, :string
      add :token, :string, null: true
    end

    create table("projects") do
      add :name, :string
      add :repo_id, :string
      add :description, :string
      add :url, :string
      add :languages, :map
    end

    create table("tasks") do
      add :name, :string
      add :content, :string
      add :issue_id, :string
      add :url, :string
      add :difficulty, :integer
      add :project_id, references(:projects)
      timestamps()
    end
  end
end
