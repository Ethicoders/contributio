let str = React.string;

type sizes =
  | Huge
  | Big
  | Medium
  | Small;

[@react.component]
let make = (~size: sizes=Small, ~children=React.null) => {
  switch size {
  | Huge => <h1 className="text-6xl font-normal leading-normal mt-0 mb-2 text-gray-800">children</h1>
  | Big => <h2 className="text-5xl font-normal leading-normal mt-0 mb-2 text-gray-800">children</h2>
  | Medium => <h3 className="text-4xl font-normal leading-normal mt-0 mb-2 text-gray-800">children</h3>
  | Small => <h4 className="text-3xl font-normal leading-normal mt-0 mb-2 text-gray-800">children</h4>
  };
};
