defmodule Contributio.Schema.DataTypes do
  use Absinthe.Schema.Notation

  object :user do
    field :id, :id
    field :email, :string
  end

  object :project do
    field :id, :id
    field :name, :string
  end

  object :task do
    field :id, :id
    field :name, :string
  end

  # object :jwt do
  #   field
  # end

  @desc "Authentication payload"
  object :auth_payload do
    field :jwt, non_null(:string)
    field :user, non_null(:user)
  end
end
