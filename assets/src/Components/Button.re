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
      Js.String.split(" ", className)
      |> Js.Array.map(item => ClassName.Value(item));

  let buttonClassNames =
    ClassName.overrideMatchingClasses(
      ClassName.create(
        (!disabled
          ? switch (type_) {
            | Danger => [|
                "hover:glow-danger",
                "border-danger",
                "bg-danger",
                "text-current",
                "rounded-md",
              |]
            | Default => [|
                "hover:glow-default",
                "border-default",
                "bg-default",
                "text-current",
                "rounded-md",
              |]
            | Primary => [|
                "hover:glow-primary",
                "border-primary",
                "bg-primary",
                "text-current",
                "rounded-md",
              |]
            | Warning => [|
                "hover:glow-warning",
                "border-warning",
                "bg-warning",
                "text-current",
                "rounded-md",
              |]
            }
          : [|"border-gray-500", "text-gray-500", "cursor-default", "rounded-md"|]
      )|> Js.Array.map(item => ClassName.Value(item))
      )

    , classNameItems);
  <button
    onClick={disabled ? ignore : onClick}
    className={
      "-skew-x-6 transform bg-opacity-10 hover:bg-none inline-flex items-center px-4 py-2 border-2 text-sm focus:outline-none focus:ring-2 focus:ring-offset-2 "
      ++ ClassName.output(buttonClassNames)
    }>
    <span className="skew-x-6 transform">children</span>
  </button>;
};
