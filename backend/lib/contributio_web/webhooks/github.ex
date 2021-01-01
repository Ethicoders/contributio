defmodule ContributioWeb.Webhooks.Github do
  require Logger
  def endpoint(conn) do
    {:ok, body, _} = Plug.Conn.read_body(conn)
    Logger.debug(inspect body)
    handle_webhook(body)
  end

  defp handle_webhook(%{pull_request: pull_request, action: "opened"}) do
    {:ok}
  end

  defp handle_webhook(%{pull_request: pull_request, action: "closed", merged: merged}) do
    # If the action is closed and the merged key is false,
    # the pull request was closed with unmerged commits.
    # If the action is closed and the merged key is true, the pull request was merged.
    {:ok}
  end

  defp handle_webhook(%{issue: issue, action: "opened"}) do
    {:ok}
  end

  defp handle_webhook(%{issue: issue, action: "closed"}) do
    {:ok}
  end
end
