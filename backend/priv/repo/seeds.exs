# Script for populating the database. You can run it as:
#
#     mix run priv/repo/seeds.exs
#
# Inside the script, you can read and write to any of your
# repositories directly:
#
#     Contributio.Repo.insert!(%Contributio.SomeSchema{})
#
# We recommend using the bang functions (`insert!`, `update!`
# and so on) as they will fail if something goes wrong.
defmodule Contributio.DatabaseSeeder do
  alias Faker.Random
  alias Contributio.Repo
  alias Contributio.Accounts
  import Faker

  def insert_user do
    Repo.insert! %Accounts.User{
      name: Faker.Pokemon.name(),
      email: Faker.Internet.email(),
      password: "password",
      hash: Argon2.hash_pwd_salt("password"),
      token: nil,
      access_tokens: %{},
      origin_ids: %{},
      projects: []
    }
  end

  def insert_project do
    Repo.insert! %Contributio.Market.Project{
      name: Faker.Internet.domain_word(),
      description: Faker.Lorem.sentence(),
      user_id: Enum.random(1..100),
      tasks: []
    }
  end

  def clear do
    Repo.delete_all
  end
end

(1..100) |> Enum.each(fn _ -> Contributio.DatabaseSeeder.insert_user end)
(1..100) |> Enum.each(fn _ -> Contributio.DatabaseSeeder.insert_project end)
