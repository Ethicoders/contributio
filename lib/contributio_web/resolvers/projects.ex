defmodule Resolvers.Projects do
  alias Contributio.{Market, Repo}
  require Logger

  def get_project(%{id: id}, _info) do
    {:ok, Market.get_project!(id) |> Repo.preload(tasks: Market.prepare_task_query())}
  end

  def get_projects(params, _info) do
    filters = Enum.map(params, fn({key, value}) -> {key, value} end)
    {:ok, Market.list_filtered_projects(filters)}
  end

  def get_projects_languages(_params, _info) do
    languages = Market.list_projects_languages()
    {:ok, languages}
  end

  def get_task(%{id: id}, _info) do
    {:ok, Market.get_task!(id)
    #  |> Repo.preload(:submissions)
    }
  end

  def list_tasks(_params, _info) do
    {:ok, Market.list_tasks()}
  end
end
