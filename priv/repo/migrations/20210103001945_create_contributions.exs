defmodule Contributio.Repo.Migrations.CreateContributions do
  use Ecto.Migration

  def change do
    create table(:contributions) do

      timestamps()
    end

  end
end
