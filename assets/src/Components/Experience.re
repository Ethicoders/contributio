let str = React.string;

[@react.component]
let make = (~amount) => {
  <div> <span className="font-bold text-primary"> "XP "->str </span> amount->str </div>;
};
