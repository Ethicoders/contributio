defmodule Contributio.Accounts do
  @moduledoc """
  The Accounts context.
  """

  require Logger
  import Ecto.Query, warn: false
  alias Contributio.Repo

  alias Contributio.Accounts.{User, UserOrigin}

  @doc """
  Returns the list of users.

  ## Examples

      iex> list_users()
      [%User{}, ...]

  """
  def list_users do
    Repo.all(User)
  end

  @doc """
  Gets a single user.

  Raises `Ecto.NoResultsError` if the User does not exist.

  ## Examples

      iex> get_user!(123)
      %User{}

      iex> get_user!(456)
      ** (Ecto.NoResultsError)

  """
  def get_user!(id), do: Repo.get!(User, id)

  def get_user(id), do: Repo.get(User, id)

  def get_user_by!(attrs), do: Repo.get_by!(User, attrs)

  def get_user_by(attrs), do: Repo.get_by(User, attrs)

  def get_user_by_email!(email), do: Repo.get_by!(User, email: email)

  def get_user_by_email(email), do: Repo.get_by(User, email: email)

  def get_user_by_token!(token), do: Repo.get_by!(User, token: token)

  def get_user_by_token(token), do: Repo.get_by(User, token: token)

  def get_or_create_user(attrs) do
    case get_user_by_email(attrs.email) do
      nil -> create_user(attrs)
      user -> user
    end
  end

  def get_user_by_user_origin(origin_id, user_origin_id) do
    from(u in User,
      join: uo in "users_origins",
      select: u,
      where: uo.origin_id == ^origin_id and uo.user_origin_id == ^user_origin_id
    )
    |> Repo.one()
  end

  def create_user_origin(attrs \\ %{}) do
    %UserOrigin{}
    |> UserOrigin.changeset(attrs)
    |> Repo.insert()
  end

  def update_user_origin(%UserOrigin{} = user_origin, attrs \\ %{}) do
    user_origin
    |> UserOrigin.changeset(attrs)
    |> Repo.update()
  end

  def upsert_user_origin(attrs) do
    case get_user_origin(attrs.origin_id, attrs.user_id) do
      nil -> create_user_origin(attrs)
      user_origin -> update_user_origin(user_origin, attrs)
    end
  end

  def get_user_origin(origin_id, user_id),
    do: Repo.get_by(UserOrigin, origin_id: origin_id, user_id: user_id)

  def delete_user_origin(origin_id, user_id),
    do:
      from(o in UserOrigin, where: o.origin_id == ^origin_id and o.user_id == ^user_id)
      |> Repo.delete_all()

  @doc """
  Creates a user.

  ## Examples

      iex> create_user(%{field: value})
      {:ok, %User{}}

      iex> create_user(%{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def create_user(attrs \\ %{}) do
    %User{}
    |> User.changeset(attrs)
    |> Repo.insert()
  end

  @doc """
  Updates a user.

  ## Examples

      iex> update_user(user, %{field: new_value})
      {:ok, %User{}}

      iex> update_user(user, %{field: bad_value})
      {:error, %Ecto.Changeset{}}

  """
  def update_user(%User{} = user, attrs) do
    user
    |> User.changeset(attrs)
    |> Repo.update()
  end

  def reward_user(%User{} = user, experience) do
    calculated_level_experience =
      Contributio.Game.add_experience_to_current_level(
        user.level,
        user.current_experience,
        experience
      )

    user |> update_user(calculated_level_experience)
  end

  @doc """
  Deletes a user.

  ## Examples

      iex> delete_user(user)
      {:ok, %User{}}

      iex> delete_user(user)
      {:error, %Ecto.Changeset{}}

  """
  def delete_user(%User{} = user) do
    Repo.delete(user)
  end

  @doc """
  Returns an `%Ecto.Changeset{}` for tracking user changes.

  ## Examples

      iex> change_user(user)
      %Ecto.Changeset{data: %User{}}

  """
  def change_user(%User{} = user, attrs \\ %{}) do
    User.changeset(user, attrs)
  end
end
