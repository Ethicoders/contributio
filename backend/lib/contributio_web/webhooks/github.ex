defmodule ContributioWeb.Webhooks.Github do
  require Logger
  alias ContributioWeb.Utils

  def dispatch(params) do
    case Contributio.Market.get_project_by_repo_id(params.repository["id"]) do
      nil ->
        Logger.info("No matching project.")
        {:ok}

      project ->
        handle_webhook(project, params)
    end
  end

  defp handle_webhook(project, %{pull_request: pull_request, action: "opened"}) do
    {:ok}
  end

  defp handle_webhook(project, %{pull_request: pull_request, action: "closed", merged: merged}) do
    # If the action is closed and the merged key is false,
    # the pull request was closed with unmerged commits.
    # If the action is closed and the merged key is true, the pull request was merged.
    {:ok}
  end

  defp handle_webhook(project, %{issue: issue, action: "opened"}) do
    data =
      Utils.extract_contributio_code_data(issue["body"])
      |> Map.merge(%{
        name: issue["title"],
        content: issue["body"],
        url: issue["html_url"],
        issue_id: issue["id"],
        project_id: project.id
      })

      Logger.debug(inspect data)
    Contributio.Market.create_task(data)

    {:ok}
  end

  defp handle_webhook(project, %{issue: issue, action: "edited"}) do
    {:ok}
  end

  defp handle_webhook(project, %{issue: issue, action: "closed"}) do
    {:ok}
  end

  defp handle_webhook(_, _) do
    Logger.info("No matching event pushed.")
    {:ok}
  end
end
