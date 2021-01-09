type types =
  | Primary
  | Warning
  | Default;

[@react.component]
let make = (~type_: types=Default, ~children=React.null, ~onClick) => {
  let buttonClassNames =
    ClassName.create([|
      Value(
        switch (type_) {
        | Primary => "bg-green-500"
        | Warning => "bg-yellow-500"
        | Default => "bg-gray-500"
        },
      ),
    |]);
  <button onClick className={"p-2 rounded-sm " ++ ClassName.output(buttonClassNames)}> children </button>;
};
