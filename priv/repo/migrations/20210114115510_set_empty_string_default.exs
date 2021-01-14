defmodule Contributio.Repo.Migrations.SetEmptyStringDefault do
  use Ecto.Migration

  def change do
    alter table("projects") do
      modify :description, :string, default: ""
    end

    alter table("tasks") do
      modify :content, :string, default: ""
    end
  end
end
