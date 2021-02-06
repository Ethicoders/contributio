defmodule Resolvers.Projects do
  alias Contributio.{Market, Repo}
  alias Contributio.Accounts.User
  require Logger

  def get_project(%{id: id}, _info) do
    {:ok, Market.get_project!(id) |> Repo.preload(tasks: Market.prepare_task_query())}
  end

  def get_projects(params, _info) do
    filters = Enum.map(params, fn {key, value} -> {key, value} end)
    Market.list_filtered_projects(filters)
  end

  def get_projects_languages(_params, _info) do
    languages = Market.list_projects_languages()
    {:ok, languages}
  end

  def get_task(%{id: id}, _info) do
    {
      :ok,
      Market.get_task!(id)
      #  |> Repo.preload(:contributions)
    }
  end

  def list_tasks(params, _info) do
    filters = Enum.map(params, fn {key, value} -> {key, value} end)
    Market.list_filtered_tasks(filters)
  end

  def set_project_visibility(%{id: id, status: status}, %{
        context: %{current_user: %User{}}
      }) do

    {:ok,
     %{
       project:
         case Market.get_project(id) |> Market.update_project(%{status: status}) do
           {:ok, project} -> project
           _ -> {:error, "Failed setting visibility"}
         end
     }}
  end

  def set_project_visibility(_args, _info), do: {:error, "Not Authorized"}

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
