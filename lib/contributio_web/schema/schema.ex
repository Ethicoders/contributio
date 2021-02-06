defmodule Contributio.Schema do
  use Absinthe.Schema
  use Absinthe.Relay.Schema, :modern
  import Contributio.Absinthe.Macros
  alias Contributio.Repo

  import_types(Contributio.Schema.DataTypes)

  require Logger

  query do
    @desc "Get a list of users"
    field :users, list_of!(:user) do
      arg(:cursor, :id)

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
    connection field :projects, node_type: :project do
      arg(:cursor, :id)
      arg(:search, :string)
      arg(:languages, :string)
      arg(:topic, :string)

      resolve(fn args, resolution ->
        Logger.debug(inspect(args))

        Resolvers.Projects.get_projects(args, resolution)
        |> Absinthe.Relay.Connection.from_query(&Repo.all/1, args, count: 6)
      end)
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
    connection field :tasks, node_type: :task do
      arg(:cursor, :id)
      arg(:difficulty, list_of(non_null(:integer)))
      arg(:time, list_of(non_null(:integer)))
      arg(:status, :integer)

      resolve(fn args, resolution ->
        Resolvers.Projects.list_tasks(args, resolution)
        |> Absinthe.Relay.Connection.from_query(&Repo.all/1, args, count: 6)
      end)
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

    @desc "Get registered origins"
    field :origins, list_of!(:origin) do
      resolve(fn _, _, _ -> {:ok, Contributio.Platforms.list_origins()} end)
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

      middleware(&add_token_to_context/2)
    end

    field :delete_project, f!(:delete_project_payload) do
      arg(:id, f!(:string))

      resolve(&Resolvers.Projects.delete_project/2)
    end

    field :delete_task, f!(:delete_task_payload) do
      arg(:id, f!(:string))

      resolve(&Resolvers.Projects.delete_task/2)
    end

    defp add_token_to_context(resolution, _) do
      Map.update!(
        resolution,
        :context,
        &Map.merge(&1, %{token: resolution.value.user.token})
      )
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

    @desc "Create a linked VCS service account"
    field :create_linked_account, f!(:auth_payload) do
      arg(:origin_id, f!(:integer))
      arg(:content, f!(:string))

      resolve(&Resolvers.Users.create_linked_account/2)
      middleware(&add_token_to_context/2)
    end

    @desc "Revoke VCS access token"
    field :revoke_linked_account, :boolean do
      arg(:origin_id, f!(:integer))

      resolve(&Resolvers.Users.revoke_linked_account/2)
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
