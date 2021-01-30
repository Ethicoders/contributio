let str = React.string;

type sizes =
  | Gigantic
  | Huge
  | Big
  | Medium
  | Small
  | Mini;

[@react.component]
let make = (~size: sizes=Medium, ~children=React.null) => {
  switch size {
  | Gigantic => <h1 className="text-5xl font-normal mt-0">children</h1>
  | Huge => <h2 className="text-4xl font-normal mt-0">children</h2>
  | Big => <h3 className="text-3xl font-normal mt-0">children</h3>
  | Medium => <h4 className="text-2xl font-normal mt-0">children</h4>
  | Small => <h5 className="text-1xl font-normal mt-0">children</h5>
  | Mini => <h6 className="text-l font-normal mt-0">children</h6>
  };
};
