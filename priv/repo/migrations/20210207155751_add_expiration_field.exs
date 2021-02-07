defmodule Contributio.Repo.Migrations.AddExpirationField do
  use Ecto.Migration

  def change do
    alter table("users_origins") do
      add :expiration, :utc_datetime, null: true
    end
  end
end
