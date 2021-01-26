let str = React.string;

[@react.component]
let make = (~name, ~level, ~currentExperience, ~nextLevelExperience) => {
  let experienceRatio =
    Js.Int.toString(currentExperience)
    ++ "/"
    ++ Js.Int.toString(nextLevelExperience);
  let style =
    ReactDOM.Style.make(
      ~width=
        (
          float_of_int(currentExperience)
          /. float_of_int(nextLevelExperience)
          *. 100.0
          |> Js.Float.toString
        )
        ++ "%",
      (),
    );
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading>
    {j|Level $level|j}->str
    <div className="relative leading-4 border-black border">
      <span className="invisible"> experienceRatio->str </span>
      <div style className="absolute top-0 bg-green-500 h-full">
        experienceRatio->str
      </div>
    </div>
  </div>;
};
