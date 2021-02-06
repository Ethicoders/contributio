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
          nil ->
            Logger.warn("No subject '#{subject_type}' matching ID '#{subject_id}'")
            {:ok}

          subject ->
            execute(subject, action, data)
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
    Market.update_project(project, data)
  end

  defp execute(%Contributio.Market.Project{} = project, action, data) when action == :update do
    Market.update_project(project, data)
  end

  defp execute(%Contributio.Market.Project{} = project, action, _) when action == :close do
    Market.close_project(project)
  end

  defp execute(type, action, data) when type == :task and action == :create do
    origin_id = get_origin_id()

    Market.create_task(%{
      data
      | project_id: Market.get_project_by_origin_repo_id(origin_id, data[:project_id]).id
    })
  end

  defp execute(%Contributio.Market.Task{} = task, action, data) when action == :update do
    Market.update_task(task, data)
  end

  defp execute(%Contributio.Market.Contribution{} = contribution, action, %{
         user_ids: user_ids
       })
       when action == :validate do
    task = contribution.task

    experience = Game.get_experience_from_effort(task.time, task.difficulty)

    task = task |> Repo.preload(:contributions)

    origin_id = get_origin_id()

    Repo.preload(contribution, :users)
    |> Map.get(:users)
    |> Enum.map(&Accounts.reward_user(&1, experience))

    # Send little XP to users who created a PR
    # Waiting for a better way to share XP, more adapted to the result
    low_reward_users =
      task.contributions
      |> Enum.filter(&(&1.id !== contribution.id))
      |> Enum.map(&Repo.preload(&1, :users))
      |> Enum.filter(&(&1.users not in user_ids))
      |> Enum.concat()
      |> Enum.uniq_by(fn user -> user.id end)
      |> Enum.map(&Accounts.reward_user(&1, (experience / 10) |> Float.floor()))

    Market.close_contribution(contribution)

    Market.close_task(task)
  end

  defp execute(%Contributio.Market.Task{} = task, action, _) when action == :close do
    Market.close_task(task)
  end

  defp execute(%Contributio.Market.Task{} = task, action, _) when action == :reopen do
    Market.open_task(task)
  end

  defp execute(type, action, data) when type == :contribution and action == :create do
    Market.create_contribution(data)
  end

  defp execute(%Contributio.Market.Contribution{} = contribution, action, data)
       when action == :update do
    Market.update_contribution(contribution, data)
  end

  defp execute(%Contributio.Market.Contribution{} = contribution, action, _)
       when action == :close do
    Market.close_contribution(contribution)
  end

  defp execute(%Contributio.Market.Contribution{} = contribution, action, _)
       when action == :reopen do
    Market.open_contribution(contribution)
  end

  defp get_tracked_subject(subject_type, subject_id) do
    origin_id = get_origin_id()

    case subject_type do
      :user -> Accounts.get_user_by_user_origin(origin_id, subject_id)
      :project -> Market.get_project_by_origin_repo_id(origin_id, subject_id)
      :task -> Market.get_task_by_origin_issue_id(origin_id, subject_id)
      :contribution -> Market.get_contribution_by_origin_pull_request_id(origin_id, subject_id)
    end
  end
end
