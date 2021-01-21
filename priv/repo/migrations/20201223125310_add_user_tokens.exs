defmodule Contributio.Repo.Migrations.AddUserTokens do
  use Ecto.Migration

  def change do
    alter table("users") do
      add :access_tokens, :map
    end
  end
end
