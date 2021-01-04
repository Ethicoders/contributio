defmodule ContributioWeb.WebhooksController do
  use ContributioWeb, :controller

  alias Contributio.Market
  alias ContributioWeb.Webhooks.{Github}
  alias ContributioWeb.Utils

  def dispatch(%{req_headers: req_headers, body_params: body_params} = conn, _info) do
    {subject_id, subject_type, action, data} =
      case resolve_origin(req_headers) do
        :github -> Github.handle_webhook(req_headers, Utils.map_keys_to_atom(body_params))
        nil -> {nil, nil, :exit, nil}
      end

    case action do
      :exit -> {:ok}
      :create -> execute(subject_type, action, data)
      _ ->
        case get_tracked_subject(subject_id, subject_type) do
          nil -> {:ok}
          subject -> execute(subject, action, data)
        end
    end

    text(conn, "")
  end

  defp resolve_origin(headers) do
    case headers do
      %{"X-GitHub-Event": _} -> :github
      _ -> nil
    end
  end

  defp execute(%Contributio.Market.Project{} = project, action, data) when action == :update do
    Market.update_project(project, data)
  end

  defp execute(%Contributio.Market.Project{} = project, action, _) when action == :close do
    Market.close_project(project)
  end

  defp execute(type, action, data) when type == :task and action == :create do
    Market.create_task(data)
  end

  defp execute(%Contributio.Market.Task{} = task, action, data) when action == :update do
    Market.update_task(task, data)
  end

  defp execute(%Contributio.Market.Task{} = task, action, data) when action == :validate do
    # Give rewards here
    Market.close_task(task)
  end

  defp execute(%Contributio.Market.Task{} = task, action, _) when action == :close do
    Market.close_task(task)
  end

  defp execute(type, action, data) when type == :submission and action == :create do
    Market.create_submission(data)
  end

  defp execute(%Contributio.Market.Submission{} = submission, action, data) when action == :update do
    Market.update_submission(submission, data)
  end

  defp execute(%Contributio.Market.Submission{} = submission, action, _) when action == :close do
    Market.close_submission(submission)
  end

  defp get_tracked_subject(subject_type, subject_id) do
    case subject_type do
      :project -> Contributio.Market.get_project_by_repo_id(subject_id)
      :task -> Contributio.Market.get_task_by_issue_id(subject_id)
      :submission -> Contributio.Market.get_submission_by_pull_request_id(subject_id)
    end
  end
end
