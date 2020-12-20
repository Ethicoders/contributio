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
end
