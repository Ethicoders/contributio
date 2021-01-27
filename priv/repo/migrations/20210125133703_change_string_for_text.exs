defmodule Contributio.Repo.Migrations.ChangeStringForText do
  use Ecto.Migration

  def change do
    alter table("projects") do
      modify :description, :text
    end

    alter table("tasks") do
      modify :content, :text
    end
  end
end
