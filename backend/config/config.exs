# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.

# General application configuration
import Config

config :contributio,
  ecto_repos: [Contributio.Repo]

# Configures the endpoint
config :contributio, ContributioWeb.Endpoint,
  url: [host: "localhost"],
  secret_key_base: "XCzlVysyqRJiIz0W/IIkl5beysuJ72ZYs2F/zcGx1GQdph2lGogQSwXknZLtOo0e",
  render_errors: [view: ContributioWeb.ErrorView, accepts: ~w(html json), layout: false],
  pubsub_server: Contributio.PubSub,
  live_view: [signing_salt: "4B5t/j8t"]

config :contributio, ContributioWeb.Guardian,
  issuer: "contributio",
  secret_key: "d5dJxEKYWQA+1oR59XUkKgTwlCVc6DdrwlFn7qZG20ekZ6P70nEMbKtjJ4bGGAKo"


# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:request_id]

# Use Jason for JSON parsing in Phoenix
config :phoenix, :json_library, Jason

# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env()}.exs"
