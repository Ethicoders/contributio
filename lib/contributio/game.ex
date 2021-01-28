defmodule Contributio.Game do
  require Logger

  def get_level_experience(level) do
    exponent = 1.2
    base_xp = 100

    floor(base_xp * (:math.pow(level, exponent)))
  end

  def get_experience_from_effort(time, difficulty) do
    time * difficulty
  end

  # Could be a recursive function to handle cases where we get XP for more than one level up
  def add_experience_to_current_level(level, current_experience, experience_to_add) do
    experience_to_next = get_level_experience(level)
    added_experience = current_experience + experience_to_add
    new_level = if (added_experience >= experience_to_next), do: level + 1, else: level
    new_experience = if (added_experience >= experience_to_next), do: added_experience - experience_to_next, else: added_experience
    %{level: new_level, current_experience: new_experience}
  end
end
