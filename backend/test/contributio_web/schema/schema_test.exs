defmodule Contributio.SchemaTest do
  use ContributioWeb.ConnCase

  use ExUnit.Case, async: true
  alias ContributioWeb.Router
  import Plug.Test

  @opts Router.init([])
  def send(body) do
    conn =
      Plug.Test.conn(:post, "/api", Jason.encode!(body))
      |> put_req_header("content-type", "application/json")
      |> put_req_header("user-agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:137.0) Gecko/20100101 Firefox/137.0")
      |> put_req_header("accept", "*/*")
      |> put_req_header("accept-language", "fr-FR,en-US;q=0.7,en;q=0.3")
      |> put_req_header("sec-fetch-dest", "empty")
      |> put_req_header("sec-fetch-mode", "cors")
      |> put_req_header("sec-fetch-site", "same-site")
      |> put_req_header("priority", "u=4")
      |> put_req_header("referer", "http://localhost:1234/")

    Router.call(conn, @opts)
  end

  @opts Router.init([])
  test "call API with unexpected operation" do
    json_body = %{
      "operation" => "some_operation",
      "payload" => [%{"key" => "value"}, %{"key2" => "value2"}]
    }

    response =
      send(json_body)

    assert response.status == 500
    assert Jason.decode!(response.resp_body) == %{"result" => "invalid"}
  end

  @opts Router.init([])
  test "call API with invalid payload" do
    json_body = %{
      "operation" => "some_operation",
      "payload" => ["invalid_payload"]
    }

    response =
      send(json_body)

    assert response.status == 500
    assert Jason.decode!(response.resp_body) == %{"result" => "invalid"}
  end

  @opts Router.init([])
  test "call API with unexpected issue" do
    Mox.defmock(Contributio.MockRPC, for: Contributio.RPC.Behaviour)
    Mox.expect(Contributio.MockRPC, :get_users, fn ->
      {:error, "unexpected issue"}
    end)
    Application.put_env(:contributio, :rpc_impl, Contributio.MockRPC)

    json_body = %{
      "operation" => "get_users",
      "payload" => []
    }

    response =
      send(json_body)

    assert response.status == 500
    assert Jason.decode!(response.resp_body) == %{"result" => "operation_error"}
  end

  @opts Router.init([])
  test "call API with JSON body" do
    json_body = %{
      "operation" => "get_users",
      "payload" => []
    }

    response =
      send(json_body)

    assert response.status == 200
    assert Jason.decode!(response.resp_body) == []
  end

  @opts Router.init([])
  test "can get projects passing offset and limit" do
    json_body = %{
      "operation" => "get_projects",
      "payload" => [%{"offset" => 1, "limit" => 10}]
    }

    response =
      send(json_body)

    assert response.status == 200
    assert Jason.decode!(response.resp_body) == []
  end
end
