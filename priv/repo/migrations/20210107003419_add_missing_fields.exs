defmodule Contributio.Repo.Migrations.AddMissingFields do
  use Ecto.Migration

  def change do
    alter table(:users) do
      add :level, :integer
      add :experience, :integer
    end

    alter table(:tasks) do
      add :time, :integer
    end
  end
end
