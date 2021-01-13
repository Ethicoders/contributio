defmodule ContributioWeb.WebhooksController do
  use ContributioWeb, :controller

  alias Contributio.{Accounts, Game, Market, Repo}
  alias ContributioWeb.Utils
  alias ContributioWeb.Webhooks.{Github}

  require Logger

  def dispatch(%{req_headers: req_headers, body_params: body_params} = conn, _info) do
    headers_map = Enum.into(req_headers, %{})
    {subject_id, subject_type, action, data} =
      case resolve_vcs_family(headers_map) do
        :github -> Github.handle_webhook(headers_map, Utils.map_keys_to_atom(body_params))
        nil -> {nil, nil, :exit, nil}
      end

    case action do
      :exit ->
        {:ok}

      :create ->
        execute(subject_type, action, data)

      _ ->
        case get_tracked_subject(subject_type, subject_id) do
          nil -> {:ok}
          subject -> execute(subject, action, data)
        end
    end

    text(conn, "")
  end

  defp resolve_vcs_family(headers) do
    case headers do
      %{"x-github-event" => _} -> :github
      _ -> nil
    end
  end

  defp get_origin_id() do
    # github.com only, for now
    1
  end

  defp execute(%Contributio.Market.Project{} = project, action, data) when action == :revoke do
    Accounts.update_user(project, data)
  end

  defp execute(%Contributio.Market.Project{} = project, action, data) when action == :update do
    Market.update_project(project, data)
  end

  defp execute(%Contributio.Market.Project{} = project, action, _) when action == :close do
    Market.close_project(project)
  end

  defp execute(type, action, data) when type == :task and action == :create do
    origin_id = get_origin_id()
    Market.create_task(%{data | project_id: Market.get_project_by_origin_repo_id(origin_id, data[:project_id]).id})
  end

  defp execute(%Contributio.Market.Task{} = task, action, data) when action == :update do
    Market.update_task(task, data)
  end

  defp execute(%Contributio.Market.Task{} = task, action, %{
         user_ids: user_ids,
         submission: submission
       })
       when action == :validate do

    experience = Game.get_experience_from_effort(task.time, task.difficulty)

    task |> Repo.preload(:submissions)

    origin_id = get_origin_id()
    # Send max XP to users who contributed to merged PR
    task[:submissions]
    |> Enum.filter(&(&1 in user_ids))
    |> Enum.map(&(Accounts.get_user_by_user_origin(origin_id, &1) |> Accounts.reward_user(experience)))

    # Send little XP to users who created a PR
    # Waiting for a better way to share XP, more adapted to the result
    task[:submissions]
    |> Enum.filter(&(&1 not in user_ids))
    |> Enum.map(&(Accounts.get_user_by_user_origin(origin_id, &1) |> Accounts.reward_user(experience / 10)))

    Market.close_task(task)
  end

  defp execute(%Contributio.Market.Task{} = task, action, _) when action == :close do
    Market.close_task(task)
  end

  defp execute(type, action, data) when type == :submission and action == :create do
    Market.create_submission(data)
  end

  defp execute(%Contributio.Market.Submission{} = submission, action, data)
       when action == :update do
    Market.update_submission(submission, data)
  end

  defp execute(%Contributio.Market.Submission{} = submission, action, _) when action == :close do
    Market.close_submission(submission)
  end

  defp get_tracked_subject(subject_type, subject_id) do
    origin_id = get_origin_id()

    case subject_type do
      :user -> Accounts.get_user_by_user_origin(origin_id, subject_id)
      :project -> Market.get_project_by_origin_repo_id(origin_id, subject_id)
      :task -> Market.get_task_by_origin_issue_id(origin_id, subject_id)
      :submission -> Market.get_submission_by_origin_pull_request_id(origin_id, subject_id)
    end
  end
end
