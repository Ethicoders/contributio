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
      ~disabled=false,
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
        !disabled
          ? switch (type_) {
            | Danger => [|
                "hover:glow-danger",
                "hover:text-current",
                "glass-danger",
                "hover:bg-danger",
                "text-current",
              |]
            | Default => [|
                "hover:glow-default",
                "hover:text-current",
                "glass-default",
                "hover:bg-default",
                "text-current",
              |]
            | Primary => [|
                "hover:glow-primary",
                "hover:text-current",
                "glass-primary",
                "hover:bg-primary",
                "text-current",
              |]
            | Warning => [|
                "hover:glow-warning",
                "hover:text-current",
                "glass-warning",
                "hover:bg-warning",
                "text-current",
              |]
            }
          : [|"border-gray-500", "text-gray-500", "cursor-default"|]
      )
      |> Js.Array.map(item => ClassName.Value(item)),
    );
  <button
    onClick={disabled ? ignore : onClick}
    className={
      "hover:bg-none transition inline-flex items-center px-4 py-2 border border-transparent rounded-md text-sm focus:outline-none focus:ring-2 focus:ring-offset-2 "
      ++ ClassName.output(buttonClassNames)
    }>
    children
  </button>;
};
