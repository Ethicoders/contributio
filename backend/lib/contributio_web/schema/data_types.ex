defmodule Contributio.Schema.DataTypes do
  use Absinthe.Schema.Notation

  object :user do
    field :id, non_null(:id)
    field :email, non_null(:string)
    field :projects, list_of(:project)
  end

  object :current_user do
    import_fields :user
  end

  object :project do
    field :id, non_null(:id)
    field :name, non_null(:string)
  end

  object :task do
    field :id, non_null(:id)
    field :name, non_null(:string)
  end

  scalar :json do
    description "Tokens"
  end

  @desc "Authentication payload"
  object :auth_payload do
    field :token, non_null(:string)
    field :user, non_null(:user)
  end

  @desc "Access token from Versioning Control services payload"
  object :access_token_payload do
    field :access_token, non_null(:string)
  end

  @desc ""
  object :repository do
    field :statuses_url, non_null(:string)
    field :name, non_null(:string)
    field :full_name, non_null(:string)
    field :url, non_null(:string)
  end
end
