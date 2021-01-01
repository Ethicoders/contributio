defmodule Contributio.Schema do
  use Absinthe.Schema

  import_types Contributio.Schema.DataTypes

  require Logger

  query do
    @desc "Get a list of users"
    field :users, list_of(:user) do
      resolve fn _parent, _args, _resolution ->
        {:ok, Contributio.Accounts.list_users()}
      end
    end

    @desc "Get a list of projects"
    field :projects, list_of(non_null :project) do
      arg :name, :string
      arg :languages, :string

      resolve(&Resolvers.Projects.get_projects/2)
    end

    @desc "Get a list of projects languages"
    field :languages, non_null(list_of(non_null :string)) do
      resolve(&Resolvers.Projects.get_projects_languages/2)
    end

    @desc "Get a list of tasks"
    field :tasks, list_of(:task) do
      resolve fn _parent, _args, _resolution ->
        {:ok, Contributio.Market.list_tasks()}
      end
    end


    @desc "Request access token from Version Control platform"
    field :request_access_token, non_null(:access_token_payload) do
      arg :code, non_null(:string)

      resolve(&Resolvers.Users.request_access_token/2)
    end

    @desc "Retrieve current user data"
    field :my, non_null(:current_user) do

      resolve(&Resolvers.Users.get_current_user/2)
    end

    @desc "Fetch user repositories"
    field :fetch_repositories, non_null(list_of non_null(:repository)) do
      arg :vendor, non_null(:string)

      resolve(&Resolvers.Users.fetch_repositories/2)
    end
  end

  mutation do
    @desc "Create a new user"
    field :create_user, :user do
      arg :email, non_null(:string)
      arg :password, non_null(:string)

      resolve(&Resolvers.Users.create/2)
    end

    @desc "Partially update a user"
    field :update_user, non_null(:user) do
      arg :email, :string
      arg :access_tokens, :string

      resolve(&Resolvers.Users.update_current_user/2)
    end

    @desc "Create a new project"
    field :create_project, :project do
      arg :name, non_null(:string)

      resolve(&Resolvers.Users.create/2)
    end

    @desc "Create a new task"
    field :create_task, :task do
      arg :name, non_null(:string)

      resolve(&Resolvers.Users.create/2)
    end

    @desc "auth"
    field :auth, non_null(:auth_payload) do
      arg :email, non_null(:string)
      arg :password, non_null(:string)

      resolve(&Resolvers.Users.authenticate/2)

      middleware(fn resolution, _ ->
        case resolution.value do
          %{user: _, token: token} ->
            Map.update!(
              resolution,
              :context,
              &Map.merge(&1, %{token: token})
            )

          _ ->
            resolution
        end
      end)
    end

    @desc "Set a VC service user access token"
    field :set_user_access_token, non_null(:user) do
      arg :vendor, non_null(:string)
      arg :content, non_null(:string)

      resolve(&Resolvers.Users.set_access_token/2)
    end

    @desc "Import VC service repositories as projects"
    field :import_repositories, :boolean do
      arg :vendor, non_null(:string)
      arg :ids, non_null(list_of(:integer))

      resolve(&Resolvers.Users.import_repositories/2)
    end
  end
end
