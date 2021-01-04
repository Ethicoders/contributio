defmodule Contributio.Market.Task do
  use Ecto.Schema
  import Ecto.Changeset

  schema "tasks" do
    field :name, :string
    field :content, :string
    field :difficulty, :integer
    field :issue_id, :integer
    field :url, :string
    belongs_to :project, Contributio.Market.Project

    timestamps()
  end

  @doc false
  def changeset(task, attrs) do
    task
    |> cast(attrs, [:name, :content, :url, :issue_id, :difficulty])
    |> validate_required([:name])
  end
end
