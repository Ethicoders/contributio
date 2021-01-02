defmodule ContributioWeb.WebhooksController do
  use ContributioWeb, :controller

  alias ContributioWeb.Webhooks.{Github}
  alias ContributioWeb.Utils

  def dispatch(conn, _info) do
    Github.dispatch(Utils.map_keys_to_atom(conn.body_params))

    text(conn, "")
  end
end
