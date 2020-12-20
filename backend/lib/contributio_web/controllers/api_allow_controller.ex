defmodule ContributioWeb.APIAllowController do
  use ContributioWeb, :controller

  def index(conn, %{"code" => code}) do
    # params.
    text conn, "bla"

    # render(conn, "allow.html")
  end
end
