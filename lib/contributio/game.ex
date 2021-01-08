defmodule Contributio.Game do
  require Logger

  def get_level_experience(level) do
    exponent = 1.5
    base_xp = 100

    Float.floor(base_xp * (:math.pow(level, exponent)))
  end

  def get_experience_from_effort(time, difficulty) do
    time * difficulty
  end
end
