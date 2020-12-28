defmodule Contributio.Platforms.GitHub do
  use Contributio.Platforms.Generic

  def get_uri() do
    "https://api.github.com"
  end
end
