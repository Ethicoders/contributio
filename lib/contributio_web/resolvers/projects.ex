defmodule Resolvers.Projects do
  alias Contributio.{Market, Repo}
  alias Contributio.Accounts.User
  require Logger

  def get_project(%{id: id}, _info) do
    {:ok, Market.get_project!(id) |> Repo.preload(tasks: Market.prepare_task_query())}
  end

  def get_projects(params, _info) do
    filters = Enum.map(params, fn({key, value}) -> {key, value} end)
    Market.list_filtered_projects(filters)
  end

  def get_projects_languages(_params, _info) do
    languages = Market.list_projects_languages()
    {:ok, languages}
  end

  def get_task(%{id: id}, _info) do
    {:ok, Market.get_task!(id)
    #  |> Repo.preload(:contributions)
    }
  end

  def list_tasks(params, _info) do
    filters = Enum.map(params, fn({key, value}) -> {key, value} end)
    Market.list_filtered_tasks(filters)
  end

  def delete_project(%{id: id}, %{
    context: %{current_user: %User{}}
  }) do
    case Market.delete_project_by_id(id) do
      {1, _} -> {:ok, %{id: id}}
      {0, _} -> {:error, message: "Could not delete the given project."}
    end
  end

  def delete_project(_args, _info), do: {:error, "Not Authorized"}

  def delete_task(%{id: id}, %{
    context: %{current_user: %User{}}
  }) do
    case Market.delete_task_by_id(id) do
      {1, _} -> {:ok, %{id: id}}
      {0, _} -> {:error, message: "Could not delete the given task."}
    end
  end

  def delete_task(_args, _info), do: {:error, "Not Authorized"}
end
