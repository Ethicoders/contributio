defmodule Contributio.Repo.Migrations.CreateOrigins do
  use Ecto.Migration

  def change do
    create table(:origins) do

      timestamps()
    end

  end
end
