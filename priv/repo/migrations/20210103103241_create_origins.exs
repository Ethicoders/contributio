defmodule Contributio.Repo.Migrations.CreateOrigins do
  use Ecto.Migration

  def change do
    create table(:origins) do
      add :name, :string
      add :url, :string
    end
  end
end
