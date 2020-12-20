defmodule Resolvers.Users do

  def create(params, _info) do
    Contributio.Accounts.create_user(params)
  end

end
