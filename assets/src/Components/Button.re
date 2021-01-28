type types =
  | Danger
  | Default
  | Primary
  | Warning;

[@react.component]
let make =
    (
      ~className="",
      ~type_: types=Default,
      ~children=React.null,
      ~onClick=ignore,
    ) => {
  let classNameItems =
    ClassName.create(
      Js.String.split(" ", className)
      |> Js.Array.map(item => ClassName.Value(item)),
    );

  let buttonClassNames =
    ClassName.merge(
      classNameItems,
      (
        switch (type_) {
        | Danger => [|"hover:bg-danger", "border-danger", "text-danger"|]
        | Default => [|"hover:bg-default", "border-default", "text-default"|]
        | Primary => [|"hover:bg-primary", "border-primary", "text-primary"|]
        | Warning => [|"hover:bg-warning", "border-warning", "text-warning"|]
        }
      )
      |> Js.Array.map(item => ClassName.Value(item)),
    );
  <button
    onClick
    className={
      "transition hover:text-current inline-flex items-center px-4 py-2 border border-transparent rounded-md shadow-sm text-sm font-medium focus:outline-none focus:ring-2 focus:ring-offset-2 "
      ++ ClassName.output(buttonClassNames)
    }>
    children
  </button>;
};
