defmodule ContributioWeb.Utils do
  require Logger

  def parse_contributio_code(string) do
    case Regex.run(~r/ctio:([\S]+)/, string) do
      nil -> %{}
      items -> Enum.at(items, 1) |> URI.query_decoder() |> Enum.into(%{})
    end
  end

  def extract_contributio_code_data(string) do
    code_fields = %{"dif" => %{cast: &(&1 |> String.to_integer()), key: :difficulty}}
    aliases = Map.keys(code_fields)

    parse_contributio_code(string)
    |> Map.take(aliases)
    |> Map.new(fn {key, value} ->
      {code_fields[key].key, apply(code_fields[key][:cast], [value])}
    end)
  end

  def map_keys_to_atom(map), do: Map.new(map, fn {key, value} -> {String.to_atom(key), value} end)
end
