defmodule Contributio.Repo.Migrations.AddUniqueConstraints do
  use Ecto.Migration

  def change do
    create unique_index("users", [:email, :name])
  end
end
