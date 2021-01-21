defmodule Contributio.Repo.Migrations.AddMissingFields do
  use Ecto.Migration

  def change do
    alter table(:tasks) do
      add :time, :integer
    end
  end
end
