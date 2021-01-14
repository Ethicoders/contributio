defmodule Contributio.Repo.Migrations.AddUserName do
  use Ecto.Migration

  def change do
    alter table("users") do
      add :level, :integer
      add :current_experience, :integer
    end
  end
end
