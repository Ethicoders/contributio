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
      |> Js.Array.filter(item => item !== "")
      |> Js.Array.map(item => ClassName.Value(item));

  let baseClassNames = [|
    "-skew-x-6", 
    "transform", 
    "bg-opacity-10", 
    "hover:bg-none", 
    "inline-flex", 
    "items-center", 
    "px-4", 
    "py-2", 
    "border-2", 
    "text-sm", 
    "focus:outline-none", 
  |];

  let buttonClassNames =
    ClassName.overrideMatchingClasses(
      ClassName.create(
        (!disabled
          ? switch (type_) {
            | Danger => [|
                "hover:glow-danger",
                "border-danger",
                "text-current",
                "rounded-md",
                "focus:glow-danger",
              |]
            | Default => [|
                "hover:glow-default",
                "border-default",
                "text-current",
                "rounded-md",
                "focus:glow-default",
              |]
            | Primary => [|
                "hover:glow-primary",
                "border-primary",
                "text-current",
                "rounded-md",
                "focus:glow-primary",
              |]
            | Warning => [|
                "hover:glow-warning",
                "border-warning",
                "text-current",
                "rounded-md",
                "focus:glow-warning",
              |]
            }
          : [|"border-gray-500", "text-gray-500", "cursor-default", "rounded-md"|]
      ) |> Js.Array.concat(baseClassNames) |> Js.Array.map(item => ClassName.Value(item))
      )

    , classNameItems);
  <button
    onClick={disabled ? ignore : onClick}
    className={ClassName.output(buttonClassNames)}
  >
    <span className={ClassName.has(buttonClassNames, "-skew-x-0") ? "" : "skew-x-6 transform"}>children</span>
  </button>;
};
