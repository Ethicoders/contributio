defmodule Contributio.Repo.Migrations.AddOriginIds do
  use Ecto.Migration

  def change do
    alter table(:users) do
      add :origin_ids, :map
    end
  end
end
