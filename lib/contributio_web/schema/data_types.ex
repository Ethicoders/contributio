defmodule Contributio.Absinthe.Macros do
  defmacro list_of!(field) do
    quote do
      non_null(list_of(non_null(unquote(field))))
    end
  end

  defmacro f!(field) do
    quote do
      non_null(unquote(field))
    end
  end
end

defmodule Contributio.Schema.DataTypes do
  use Absinthe.Schema.Notation
  import Contributio.Absinthe.Macros

  object :user do
    field :id, f!(:id)
    field :name, f!(:string)
    field :level, f!(:string)
    field :current_experience, f!(:integer)
    field :next_level_experience, f!(:integer)
    field :projects, list_of!(:project)
  end

  object :current_user do
    import_fields :user
    field :linked_origins, f!(:origin_family)
  end

  enum :origin_family do
    value :github
    # value :gitlab
    # value :bitbucket
  end

  object :origin do
    field :uri, f!(:string)
    field :family, f!(:origin_family)
  end

  object :project do
    field :id, f!(:id)
    field :name, f!(:string)
    field :url, f!(:string)
    field :origin, f!(:origin)
    field :languages, :json
    field :description, f!(:string)
    field :tasks, list_of!(:task)
  end

  object :task do
    field :id, f!(:id)
    field :name, f!(:string)
    field :project, f!(:project)
    field :content, f!(:string)
    field :experience, f!(:integer)
    field :difficulty, f!(:integer)
    field :time, f!(:integer)
    # field :rewards, list_of!(:reward)
  end

  object :reward do
    field :id, f!(:id)
  end

  scalar :json do
    serialize &(&1)
    parse &Jason.decode!/1
  end

  @desc "Authentication payload"
  object :auth_payload do
    field :user, f!(:user)
  end

  @desc "Access token from Versioning Control services payload"
  object :access_token_payload do
    field :access_token, f!(:string)
  end

  @desc "Repository data fetched from a VCS platform"
  object :repository do
    field :id, f!(:string)
    field :statuses_url, f!(:string)
    field :name, f!(:string)
    field :full_name, f!(:string)
    field :url, f!(:string)
  end

  @desc "Issue data fetched from a VCS platform"
  object :issue do
    field :id, f!(:string)
    field :statuses_url, f!(:string)
    field :title, f!(:string)
    field :number, f!(:integer)
    field :url, f!(:string)
  end

  object :delete_project_payload do
    field :id, f!(:string)
  end

  object :delete_task_payload do
    field :id, f!(:string)
  end
end
