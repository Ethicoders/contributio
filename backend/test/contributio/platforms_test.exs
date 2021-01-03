defmodule Contributio.PlatformsTest do
  use Contributio.DataCase

  alias Contributio.Platforms

  describe "origins" do
    alias Contributio.Platforms.Origin

    @valid_attrs %{}
    @update_attrs %{}
    @invalid_attrs %{}

    def origin_fixture(attrs \\ %{}) do
      {:ok, origin} =
        attrs
        |> Enum.into(@valid_attrs)
        |> Platforms.create_origin()

      origin
    end

    test "list_origins/0 returns all origins" do
      origin = origin_fixture()
      assert Platforms.list_origins() == [origin]
    end

    test "get_origin!/1 returns the origin with given id" do
      origin = origin_fixture()
      assert Platforms.get_origin!(origin.id) == origin
    end

    test "create_origin/1 with valid data creates a origin" do
      assert {:ok, %Origin{} = origin} = Platforms.create_origin(@valid_attrs)
    end

    test "create_origin/1 with invalid data returns error changeset" do
      assert {:error, %Ecto.Changeset{}} = Platforms.create_origin(@invalid_attrs)
    end

    test "update_origin/2 with valid data updates the origin" do
      origin = origin_fixture()
      assert {:ok, %Origin{} = origin} = Platforms.update_origin(origin, @update_attrs)
    end

    test "update_origin/2 with invalid data returns error changeset" do
      origin = origin_fixture()
      assert {:error, %Ecto.Changeset{}} = Platforms.update_origin(origin, @invalid_attrs)
      assert origin == Platforms.get_origin!(origin.id)
    end

    test "delete_origin/1 deletes the origin" do
      origin = origin_fixture()
      assert {:ok, %Origin{}} = Platforms.delete_origin(origin)
      assert_raise Ecto.NoResultsError, fn -> Platforms.get_origin!(origin.id) end
    end

    test "change_origin/1 returns a origin changeset" do
      origin = origin_fixture()
      assert %Ecto.Changeset{} = Platforms.change_origin(origin)
    end
  end
end
