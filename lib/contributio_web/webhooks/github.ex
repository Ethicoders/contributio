defmodule ContributioWeb.Webhooks.Github do
  require Logger
  alias ContributioWeb.Utils

  def handle_webhook(headers, params) do
    resolve(headers["x-github-event"], params)
  end

  defp resolve("github_app_authorization", %{sender: sender, action: "revoked"}) do
    {sender["id"], :user, :revoke, nil}
  end

  defp resolve("pull_request", %{
         pull_request: pull_request,
         action: "opened"
       }) do
    {nil, :contribution, :create, %{pull_request_id: pull_request["id"]}}
  end

  defp resolve("pull_request", %{
         pull_request: pull_request,
         action: "closed",
         merged: false
       }) do
    {:contribution, :close, pull_request["id"], %{}}
  end

  defp resolve("pull_request", %{
         pull_request: pull_request,
         action: "closed",
         merged: true
       }) do
    linked_issue = Utils.parse_contributio_code(pull_request["body"]) |> String.to_integer()

    user_ids =
      case HTTPoison.get(
             pull_request["_links"]["commits"],
             "Content-Type": "application/json"
           ) do
        {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
          case Jason.decode!(body, keys: :atoms) do
            commits -> commits |> Enum.map(& &1["committer"]["id"])
          end

        {:error, %HTTPoison.Error{reason: reason}} ->
          IO.inspect(inspect(reason))
      end

    {linked_issue, :task, :validate, %{contribution: pull_request["id"], user_ids: user_ids}}
  end

  defp resolve("issues", %{issue: issue, action: "opened", repository: repository}) do
    data =
      Utils.extract_contributio_code_data(issue["body"])
      |> Map.merge(%{
        name: issue["title"],
        content: issue["body"],
        url: issue["html_url"],
        issue_id: Integer.to_string(issue["number"]),
        project_id: repository["full_name"]
      })

    {nil, :task, :create, data}
  end

  defp resolve("issues", %{issue: issue, action: "edited"}) do
    data =
      Utils.extract_contributio_code_data(issue["body"])
      |> Map.merge(%{
        name: issue["title"],
        content: issue["body"]
      })

    {issue["id"], :task, :update, data}
  end

  # defp resolve("issues", %{issue: issue, action: "assigned"}) do
  #   data =
  #     Utils.extract_contributio_code_data(issue["body"])
  #     |> Map.merge(%{
  #       name: issue["title"],
  #       content: issue["body"]
  #     })

  #   {issue["id"], :task, :update, data}
  # end

  # defp resolve("issues", %{issue: issue, action: "labeled"}) do
  #   data =
  #     Utils.extract_contributio_code_data(issue["body"])
  #     |> Map.merge(%{
  #       name: issue["title"],
  #       content: issue["body"]
  #     })

  #   {issue["id"], :task, :update, data}
  # end

  defp resolve("repository", %{repository: repository, action: "renamed"}) do
    {repository["id"], :update, :project, %{repo_id: repository["full_name"]}}
  end

  defp resolve("repository", %{repository: repository, action: "deleted"}) do
    {repository["id"], :close, :project, %{}}
  end

  defp resolve(_, _) do
    Logger.info("No matching event pushed.")
    {nil, nil, :exit, nil}
  end
end
