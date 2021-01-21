defmodule Contributio.Repo.Migrations.AddGamification do
  use Ecto.Migration

  def change do
    alter table("users") do
      add :level, :integer, default: 1
      add :current_experience, :integer, default: 0
    end
  end
end
