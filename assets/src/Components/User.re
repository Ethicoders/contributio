let str = React.string;

[@react.component]
let make = (~name, ~level) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading> {j|Level $level|j}->str
  </div>;
};
