defmodule Contributio.Repo.Migrations.AddStatusField do
  use Ecto.Migration

  def change do
    alter table("projects") do
      add :status, :integer, default: 0
    end

    alter table("tasks") do
      add :status, :integer, default: 0
    end
  end
end
