defmodule ContributioWeb.WebhooksController do
  use ContributioWeb, :controller

  alias ContributioWeb.Webhooks.{Github}

  def dispatch(conn, _info) do
    Github.endpoint(conn)
  end
end
