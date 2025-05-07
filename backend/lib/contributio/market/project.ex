defmodule Contributio.Market.Project do
  use Ecto.Schema
  import Ecto.Changeset

  schema "projects" do
    field :name, :string
    field :repo_id, :integer
    field :description, :string
    field :url, :string
    # field :readme, :string
    field :languages, :map
    # field :owner, :string
    has_one :origin, Contributio.Platforms.Origin
    belongs_to :user, Contributio.Accounts.User
    has_many :tasks, Contributio.Market.Task



#     - Name
# - url
# - description/about
# - readme
# - languages
# - owner/organization
# - tags
# - license?

    timestamps()
  end

  @doc false
  def changeset(project, attrs) do
    project
    |> cast(attrs, [:name, :repo_id, :description, :url, :languages])
    |> validate_required([:name])
  end
end

defimpl Jason.Encoder, for: Any do
  def encode(%{__struct__: _} = struct, opts) do
    struct
    |> Map.from_struct()
    |> sanitize_map()
    |> Jason.Encode.map(opts)
  end

  defp sanitize_map(map) do
    map
    |> Map.drop([:__meta__, :__struct__])
    |> Enum.reduce(%{}, fn {key, value}, acc ->
      value =
        case value do
          %Ecto.Association.NotLoaded{} -> nil
          _ -> value
        end

      Map.put(acc, key, value)
    end)
  end
end
