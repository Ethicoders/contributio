defmodule Contributio.Repo.Migrations.ChangeIdTypes do
  use Ecto.Migration

  def change do
    alter table("projects") do
      modify :repo_id, :string
    end

    alter table("tasks") do
      modify :issue_id, :string
    end
  end
end
