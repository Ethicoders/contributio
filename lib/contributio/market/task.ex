defmodule Contributio.Market.Task do
  use Ecto.Schema
  import Ecto.Changeset

  schema "tasks" do
    field :name, :string
    field :content, :string
    field :difficulty, :integer
    field :time, :integer
    field :experience, :integer, virtual: true
    field :issue_id, :string
    field :url, :string
    belongs_to :project, Contributio.Market.Project
    has_many :submissions, Contributio.Market.Submission

    timestamps()
  end

  @doc false
  def changeset(task, attrs) do
    task
    |> cast(attrs, [:name, :content, :url, :issue_id, :difficulty, :time, :project_id])
    |> validate_required([:name])
  end
end
