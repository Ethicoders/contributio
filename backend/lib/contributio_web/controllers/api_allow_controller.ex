defmodule ContributioWeb.APIAllowController do
  use ContributioWeb, :controller

  def index(conn, %{"code" => code}) do

    # case HTTPoison.post(
    #   "https://github.com/login/oauth/access_token",
    #   Jason.encode!(%{
    #     code: code,
    #     client_id: System.get_env("GITHUB_CLIENT_ID"),
    #     client_secret: System.get_env("GITHUB_CLIENT_SECRET")}
    #   ),
    #   [{"Content-Type", "application/json"}]
    # ) do
    #   {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
    #     ...
    #     # body should look like that: {
    #     #   "access_token": "e72e16c7e42f292c6912e7710c838347ae178b4a",
    #     #   "expires_in": "28800",
    #     #   "refresh_token": "r1.c1b4a2e77838347a7e420ce178f2e7c6912e1692",
    #     #   "refresh_token_expires_in": "15811200",
    #     #   "scope": "",
    #     #   "token_type": "bearer"
    #     # }

    #   {:error, %HTTPoison.Error{reason: reason}} ->
    #     IO.inspect reason
    # end

    text conn, "bla"

    # render(conn, "allow.html")
  end
end
