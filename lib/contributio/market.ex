defmodule Contributio.Market do
  require Logger

  @moduledoc """
  The Market context.
  """

  import Ecto.Query, warn: false
  alias Contributio.Repo

  alias Contributio.Market.Project

  @doc """
  Returns the list of projects.

  ## Examples

      iex> list_projects()
      [%Project{}, ...]

  """
  def list_projects do
    Repo.all(Project)
  end

  def list_filtered_projects(args) do
    args
    |> Enum.reduce(Project, fn
      {:topic, topic}, query ->
        from q in query, where: ^topic in q.topics

      {:search, search}, query ->
        from q in query,
          where: like(q.name, ^"%#{search}%") or like(q.description, ^"%#{search}%")

      {:languages, language}, query ->
        from q in query, where: fragment("? \\? ?", q.languages, ^language)

      _, query ->
        query
    end)
  end

  def list_projects_languages do
    from(q in Project, select: fragment("DISTINCT jsonb_object_keys(?)", q.languages))
    |> Repo.all()
  end

  @doc """
  Gets a single project.

  Raises `Ecto.NoResultsError` if the Project does not exist.

  ## Examples

      iex> get_project!(123)
      %Project{}

      iex> get_project!(456)
      ** (Ecto.NoResultsError)

  """
  def get_project!(id), do: Repo.get!(Project, id)

  def get_project_by_origin_repo_id!(_origin_id, repo_id),
    do: Repo.get_by!(Project, repo_id: repo_id)

  def get_project_by_origin_repo_id(_origin_id, repo_id),
    do: Repo.get_by(Project, repo_id: repo_id)

  @doc """
  Creates a project.

  ## Examples

      iex> create_project(%{field: value})
      {:ok, %Project{}}

      iex> create_project(%{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def create_project(attrs \\ %{}) do
    %Project{}
    |> Project.changeset(attrs)
    |> Repo.insert()
  end

  @doc """
  Updates a project.

  ## Examples

      iex> update_project(project, %{field: new_value})
      {:ok, %Project{}}

      iex> update_project(project, %{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def update_project(%Project{} = project, attrs) do
    project
    |> Project.changeset(attrs)
    |> Repo.update()
  end

  def close_project(%Project{} = project) do
    project
    |> Project.changeset(%{status: :closed})
    |> Repo.update()
  end

  @doc """
  Deletes a project.

  ## Examples

      iex> delete_project(project)
      {:ok, %Project{}}

      iex> delete_project(project)
      {:error, %Ecto.Changeset{}}

  """
  def delete_project(%Project{} = project) do
    Repo.delete(project)
  end

  def delete_project_by_id(id) do
    from(p in Project, where: p.id == ^id) |> Repo.delete_all()
  end

  @doc """
  Returns an `%Ecto.Changeset{}` for tracking project changes.

  ## Examples

      iex> change_project(project)
      %Ecto.Changeset{data: %Project{}}

  """
  def change_project(%Project{} = project, attrs \\ %{}) do
    Project.changeset(project, attrs)
  end

  alias Contributio.Market.Task

  @doc """
  Returns the list of tasks.

  ## Examples

      iex> list_tasks()
      [%Task{}, ...]

  """
  def list_filtered_tasks(args) do
    initial =
      from t in Task,
        select_merge: %{experience: fragment("? * ? AS experience", t.time, t.difficulty)},
        preload: [:project]

    args
    |> Enum.reduce(initial, fn
      {:time, time}, query ->
        from q in query,
          where: q.time in ^time

      {:difficulty, difficulty}, query ->
        from q in query, where: q.difficulty in ^difficulty

      {:status, status}, query ->
        from q in query, where: q.status == ^status

      _, query ->
        query
    end)

    # Repo.all(

    # )
  end

  @doc """
  Gets a single task.

  Raises `Ecto.NoResultsError` if the Task does not exist.

  ## Examples

      iex> get_task!(123)
      %Task{}

      iex> get_task!(456)
      ** (Ecto.NoResultsError)

  """
  def get_task_by(id) do
    Repo.get(prepare_task_query(), id)
  end

  def get_task_by!(id) do
    Repo.get!(prepare_task_query(), id)
  end

  def prepare_task_query() do
    from t in Task,
      select_merge: %{experience: fragment("? * ? AS experience", t.time, t.difficulty)},
      preload: [:project]
  end

  def get_task!(id), do: get_task_by(id)
  def get_task(id), do: get_task_by!(id)

  def get_task_by_origin_issue_id(_origin_id, issue_id), do: Repo.get_by(Task, issue_id: issue_id)

  def get_task_by_origin_issue_id!(_origin_id, issue_id),
    do: Repo.get_by!(Task, issue_id: issue_id)

  @doc """
  Creates a task.

  ## Examples

      iex> create_task(%{field: value})
      {:ok, %Task{}}

      iex> create_task(%{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def create_task(attrs \\ %{}) do
    %Task{}
    |> Task.changeset(attrs)
    |> Repo.insert!()
  end

  @doc """
  Updates a task.

  ## Examples

      iex> update_task(task, %{field: new_value})
      {:ok, %Task{}}

      iex> update_task(task, %{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def update_task(%Task{} = task, attrs) do
    task
    |> Task.changeset(attrs)
    |> Repo.update()
  end

  def close_task(%Task{} = task) do
    task
    |> Task.changeset(%{status: 1})
    |> Repo.update()
  end

  def open_task(%Task{} = task) do
    task
    |> Task.changeset(%{status: 0})
    |> Repo.update()
  end

  @doc """
  Deletes a task.

  ## Examples

      iex> delete_task(task)
      {:ok, %Task{}}

      iex> delete_task(task)
      {:error, %Ecto.Changeset{}}

  """
  def delete_task(%Task{} = task) do
    Repo.delete(task)
  end

  def delete_task_by_id(id) do
    from(p in Task, where: p.id == ^id) |> Repo.delete_all()
  end

  @doc """
  Returns an `%Ecto.Changeset{}` for tracking task changes.

  ## Examples

      iex> change_task(task)
      %Ecto.Changeset{data: %Task{}}

  """
  def change_task(%Task{} = task, attrs \\ %{}) do
    Task.changeset(task, attrs)
  end

  alias Contributio.Market.Contribution

  @doc """
  Returns the list of contributions.

  ## Examples

      iex> list_contributions()
      [%Contribution{}, ...]

  """
  def list_contributions do
    Repo.all(Contribution)
  end

  @doc """
  Gets a single contribution.

  Raises `Ecto.NoResultsError` if the Contribution does not exist.

  ## Examples

      iex> get_contribution!(123)
      %Contribution{}

      iex> get_contribution!(456)
      ** (Ecto.NoResultsError)

  """
  def get_contribution!(id), do: Repo.get!(Contribution, id)

  def get_contribution_by_origin_pull_request_id(_origin_id, pull_request_id),
    do: Repo.get_by(Contribution, pull_request_id: pull_request_id) |> Repo.preload(:task)

  def get_contribution_by_origin_pull_request_id!(_origin_id, pull_request_id),
    do: Repo.get_by!(Contribution, pull_request_id: pull_request_id) |> Repo.preload(:task)

  def get_contributions_by_task_id(id), do: Contribution |> where(task_id: ^id) |> Repo.all()

  @doc """
  Creates a contribution.

  ## Examples

      iex> create_contribution(%{field: value})
      {:ok, %Contribution{}}

      iex> create_contribution(%{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def create_contribution(attrs \\ %{}) do
    %Contribution{}
    |> Contribution.changeset(attrs)
    |> Repo.insert()
  end

  @doc """
  Updates a contribution.

  ## Examples

      iex> update_contribution(contribution, %{field: new_value})
      {:ok, %Contribution{}}

      iex> update_contribution(contribution, %{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def update_contribution(%Contribution{} = contribution, attrs) do
    contribution
    |> Contribution.changeset(attrs)
    |> Repo.update()
  end

  def close_contribution(%Contribution{} = contribution),
    do: contribution |> update_contribution(%{status: 1})

  def open_contribution(%Contribution{} = contribution),
    do: contribution |> update_contribution(%{status: 0})

  @doc """
  Deletes a contribution.

  ## Examples

      iex> delete_contribution(contribution)
      {:ok, %Contribution{}}

      iex> delete_contribution(contribution)
      {:error, %Ecto.Changeset{}}

  """
  def delete_contribution(%Contribution{} = contribution) do
    Repo.delete(contribution)
  end

  @doc """
  Returns an `%Ecto.Changeset{}` for tracking contribution changes.

  ## Examples

      iex> change_contribution(contribution)
      %Ecto.Changeset{data: %Contribution{}}

  """
  def change_contribution(%Contribution{} = contribution, attrs \\ %{}) do
    Contribution.changeset(contribution, attrs)
  end
end
