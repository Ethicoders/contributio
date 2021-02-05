defmodule Contributio.Repo.Migrations.AddStatusField do
  use Ecto.Migration

  def change do
    alter table("projects") do
      add :status, :integer
    end

    alter table("tasks") do
      add :status, :integer
    end
  end
end
