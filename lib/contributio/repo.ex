defmodule Contributio.Repo do
  use Ecto.Repo,
    otp_app: :contributio,
    adapter: Ecto.Adapters.Postgres
end
