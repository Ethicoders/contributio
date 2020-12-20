defmodule Contributio.Market.Project do
  use Ecto.Schema
  import Ecto.Changeset

  schema "projects" do
    field :name, :string
    field :uuid, :string
    field :secret, :string
    field :url, :string
    field :readme, :string
    # field :languages, :array
    field :owner, :string



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
    |> cast(attrs, [:name])
    |> validate_required([:name])
  end
end
