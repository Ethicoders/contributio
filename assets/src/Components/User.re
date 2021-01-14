let str = React.string;

[@react.component]
let make = (~name, ~level, ~currentExperience, ~nextLevelExperience) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading>
    {j|Level $level|j}->str
    <div>
      {(
         "Experience: "
         ++ Js.Int.toString(currentExperience)
         ++ "/"
         ++ Js.Int.toString(nextLevelExperience)
       )
       ->str}
    </div>
  </div>;
};
