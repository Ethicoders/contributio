defmodule Resolvers.Projects do
  alias Contributio.{Market}
  require Logger

  def get_projects(params, _info) do
    filters = Enum.map(params, fn({key, value}) -> {key, value} end)
    {:ok, Market.list_filtered_projects(filters)}
  end

  def get_projects_languages(_params, _info) do
    languages = Market.list_projects_languages()
    {:ok, languages}
  end

  def list_tasks(_params, _info) do
    {:ok, Market.list_tasks()}
  end
end
