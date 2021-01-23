defmodule ContributioWeb.Context do
  @behaviour Plug

  import Plug.Conn
  import Ecto.Query, only: [where: 2]

  alias Contributio.Accounts

  require Logger

  def init(opts), do: opts

  def call(conn, _) do
    case build_context(conn) do
      {:ok, context} ->
        put_private(conn, :absinthe, %{context: context})
      _ ->
        conn
    end
  end


  defp build_context(%{req_cookies: req_cookies}) do
    with true <- Map.has_key?(req_cookies, "ctiotoken"),
         user <- Accounts.get_user_by_token(req_cookies["ctiotoken"]) do
      case user do
        nil -> {:error, message: "You're not connected"}
        user -> {:ok, %{current_user: user}}
      end
      #  else
      #   {:error, "Error"}
    end
  end
end
