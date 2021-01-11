defmodule Contributio.Repo.Migrations.UpdateUserIdOrigin do
  use Ecto.Migration

  def change do
    alter table("users") do
      remove :access_tokens
      remove :origin_ids
    end

    create table("users_origins") do
      add :user_id, references(:users), null: false, primary_key: true, on_delete: :delete_all
      add :origin_id, references(:origins), null: false, primary_key: true, on_delete: :delete_all
      add :user_origin_id, :integer # The user ID from the VCS platform
      add :access_token, :string, null: true
    end
  end
end
