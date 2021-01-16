defmodule Contributio.Repo.Migrations.AddUserDefaults do
  use Ecto.Migration

  def change do
    alter table("users") do
      modify :current_experience, :integer, default: 0
      modify :level, :integer, default: 1
    end
  end
end
