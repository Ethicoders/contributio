defmodule Contributio.Schema do
  use Absinthe.Schema

  import_types Contributio.Schema.DataTypes


  query do
    @desc "Get a list of users"
    field :users, list_of(:user) do
      resolve fn _parent, _args, _resolution ->
        {:ok, Contributio.Accounts.list_users()}
      end
    end

    @desc "Get a list of projects"
    field :projects, list_of(:project) do
      resolve fn _parent, _args, _resolution ->
        {:ok, Contributio.Market.list_projects()}
      end
    end

    @desc "Get a list of tasks"
    field :tasks, list_of(:task) do
      resolve fn _parent, _args, _resolution ->
        {:ok, Contributio.Market.list_tasks()}
      end
    end
  end

  mutation do
    @desc "Create a new user"
    field :create_user, :user do
      arg :email, non_null(:string)
      arg :password, non_null(:string)

      resolve(&Resolvers.Users.create/2)
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
    field :auth, :auth_payload do
      arg :email, non_null(:string)
      arg :password, non_null(:string)

      resolve(&Resolvers.Users.authenticate/2)
    end
  end
end
