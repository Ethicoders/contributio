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
    field :email, f!(:string)
    field :projects, list_of!(:project)
  end

  object :current_user do
    import_fields :user
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
    field :description, :string
  end

  object :task do
    field :id, f!(:id)
    field :name, f!(:string)
    field :project, f!(:project)
    field :content, f!(:string)
    field :experience, f!(:integer)
    field :rewards, list_of!(:reward)
  end

  object :reward do
    field :id, f!(:id)
  end

  scalar :json do
    description "Any"
  end

  @desc "Authentication payload"
  object :auth_payload do
    field :token, f!(:string)
    field :user, f!(:user)
  end

  @desc "Access token from Versioning Control services payload"
  object :access_token_payload do
    field :access_token, f!(:string)
  end

  @desc ""
  object :repository do
    field :id, f!(:integer)
    field :statuses_url, f!(:string)
    field :name, f!(:string)
    field :full_name, f!(:string)
    field :url, f!(:string)
  end
end
