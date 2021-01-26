type types =
  | Danger
  | Default
  | Primary
  | Warning;

[@react.component]
let make = (~type_: types=Default, ~children=React.null, ~onClick=ignore) => {
  let buttonClassNames =
    ClassName.create([|
      Value(
        switch (type_) {
        | Danger => "bg-red-400"
        | Default => "bg-gray-400"
        | Primary => "bg-green-400"
        | Warning => "bg-yellow-400"
        },
      ),
    |]);
  <button
    onClick
    className={
      "inline-flex items-center px-4 py-2 border border-transparent rounded-md shadow-sm text-sm font-medium text-white focus:outline-none focus:ring-2 focus:ring-offset-2 "
      ++ ClassName.output(buttonClassNames)
    }>
    children
  </button>;
};
