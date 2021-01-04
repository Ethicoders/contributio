defmodule ContributioWeb.CodeTest do
  use ExUnit.Case
  alias ContributioWeb.Utils

  test "parse the code" do
    assert Utils.parse_contributio_code("ctio:") == nil
    assert Utils.parse_contributio_code("ctio:dif=1") == "dif=1"
  end

  test "extract code data" do
    assert Utils.extract_contributio_code_data("ctio:") == %{}
    assert Utils.extract_contributio_code_data("ctio:dif=1") == %{difficulty: "1"}
  end
end
