defmodule Contributio.Platforms.Generic do
  use HTTPoison.Base

  # Define behaviours which user modules have to implement, with type annotations
  @callback get_uri() :: String.t()

  defmacro __using__(_params) do
    quote do
      @behaviour Contributio.Platforms.Generic

      def process_request_url(url) do
        get_uri() <> url
      end

      def process_response_body(body) do
        body
        |> Jason.decode!()
        |> Enum.map(fn {k, v} -> {String.to_atom(k), v} end)
      end

      # def get(endpoint, access_token, params) do
      #   HTTPoison.get(
      #     endpoint,
      #     ["Content-Type": "application/json", Authorization: "token #{access_token}"],
      #     params: params
      #   )
      # end

      # def get!(endpoint, access_token, params) do
      #   HTTPoison.get!(
      #     endpoint,
      #     ["Content-Type": "application/json", Authorization: "token #{access_token}"],
      #     params: params
      #   )
      # end

      # Defoverridable makes the given functions in the current module overridable
      # Without defoverridable, new definitions of greet will not be picked up
      # defoverridable [shout: 0, greet: 1]
    end
  end
end
