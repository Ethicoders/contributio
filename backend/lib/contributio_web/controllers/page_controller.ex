defmodule ContributioWeb.PageController do
  use ContributioWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end
end
