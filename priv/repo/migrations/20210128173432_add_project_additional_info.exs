defmodule Contributio.Repo.Migrations.AddProjectAdditionalInfo do
  use Ecto.Migration

  def change do
    alter table("projects") do
      add :topics, {:array, :string}
      add :readme, :text
      add :license, :string
    end
  end
end
