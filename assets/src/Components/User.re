let str = React.string;

[@react.component]
let make = (~id, ~name, ~level, ~currentExperience, ~nextLevelExperience) => {
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
  <div className="card px-4 pb-4 pt-2 border-2 rounded-sm">
    <Anchor target={"/users/" ++ id} className="text-primary">
      <Heading> name->str </Heading>
    </Anchor>
    <span className="text-current">{j|Level $level|j}->str</span>
    <div className="relative leading-4 border-black border">
      <span className="invisible"> experienceRatio->str </span>
      <div style className="absolute top-0 bg-green-500 h-full">
        experienceRatio->str
      </div>
    </div>
  </div>;
};
