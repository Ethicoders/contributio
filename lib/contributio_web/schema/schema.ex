defmodule Contributio.Schema do
  use Absinthe.Schema
  import Contributio.Absinthe.Macros

  import_types(Contributio.Schema.DataTypes)

  require Logger

  query do
    @desc "Get a list of users"
    field :users, list_of!(:user) do
      resolve(fn _parent, _args, _resolution ->
        {:ok,
         Contributio.Accounts.list_users()
         |> Enum.map(&Contributio.Accounts.User.set_next_level_experience(&1))}
      end)
    end

    @desc "Get a single user"
    field :user, f!(:user) do
      arg(:id, f!(:id))
      resolve(&Resolvers.Users.get_user/2)
    end

    @desc "Get a list of projects"
    field :projects, list_of!(:project) do
      arg(:name, :string)
      arg(:languages, :string)

      resolve(&Resolvers.Projects.get_projects/2)
    end

    @desc "Get a single project"
    field :project, f!(:project) do
      arg(:id, f!(:id))
      resolve(&Resolvers.Projects.get_project/2)
    end

    @desc "Get a list of projects languages"
    field :languages, list_of!(:string) do
      resolve(&Resolvers.Projects.get_projects_languages/2)
    end

    @desc "Get a list of tasks"
    field :tasks, list_of!(:task) do
      resolve(&Resolvers.Projects.list_tasks/2)
    end

    @desc "Get a single task"
    field :task, f!(:task) do
      arg(:id, f!(:id))
      resolve(&Resolvers.Projects.get_task/2)
    end

    @desc "Request access token from Version Control platform"
    field :request_access_token, f!(:access_token_payload) do
      arg(:origin_id, f!(:integer))
      arg(:code, f!(:string))

      resolve(&Resolvers.Users.request_access_token/2)
    end

    @desc "Retrieve current user data"
    field :my, f!(:current_user) do
      resolve(&Resolvers.Users.get_current_user/2)
    end

    @desc "Fetch user repositories"
    field :fetch_repositories, list_of!(:repository) do
      arg(:origin_id, f!(:integer))

      resolve(&Resolvers.Users.fetch_repositories/2)
    end

    @desc "Fetch issues linked to a given project"
    field :fetch_project_issues, list_of!(:issue) do
      arg(:origin_id, f!(:integer))
      arg(:project_id, f!(:string))

      resolve(&Resolvers.Users.fetch_issues/2)
    end
  end

  mutation do
    @desc "Create a new user"
    field :create_user, :user do
      arg(:email, f!(:string))
      arg(:password, f!(:string))

      resolve(&Resolvers.Users.create/2)
    end

    @desc "Partially update a user"
    field :update_user, f!(:user) do
      arg(:email, :string)
      arg(:access_tokens, :string)

      resolve(&Resolvers.Users.update_current_user/2)
    end

    @desc "Create a new project"
    field :create_project, :project do
      arg(:name, f!(:string))

      resolve(&Resolvers.Users.create/2)
    end

    @desc "Create a new task"
    field :create_task, :task do
      arg(:name, f!(:string))

      resolve(&Resolvers.Users.create/2)
    end

    @desc "auth"
    field :auth, f!(:auth_payload) do
      arg(:email, f!(:string))
      arg(:password, f!(:string))

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

    # @desc "Set a VC service user access token"
    # field :set_user_access_token, f!(:user) do
    #   arg(:origin_id, f!(:string))
    #   arg(:content, f!(:string))

    #   resolve(&Resolvers.Users.set_access_token/2)
    # end

    @desc "Link VCS service account"
    field :link_account, f!(:user) do
      arg(:origin_id, f!(:integer))
      arg(:content, f!(:string))

      resolve(&Resolvers.Users.link_account/2)
    end

    @desc "Import VCS service repositories as projects"
    field :import_repositories, :boolean do
      arg(:origin_id, f!(:integer))
      arg(:ids, list_of!(:string))

      resolve(&Resolvers.Users.import_repositories/2)
    end

    @desc "Import VCS service issues as tasks from a given project"
    field :import_project_issues, :boolean do
      arg(:origin_id, f!(:integer))
      arg(:ids, list_of!(:string))
      arg(:project_id, f!(:string))

      resolve(&Resolvers.Users.import_issues/2)
    end
  end
end
