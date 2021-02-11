let str = React.string;

type types =
  | Danger
  | Default
  | Primary
  | Warning;

[@react.component]
let make = (~children, ~className="", ~type_=Default) => {
  let classNameItems =
    ClassName.create(
      Js.String.split(" ", className)
      |> Js.Array.map(item => ClassName.Value(item)),
    );

  let alertClassNames =
    ClassName.merge(
      classNameItems,
      (
        switch (type_) {
        | Danger => [|
            "glass-danger",
            "text-current",
            /* "bg-danger-200",
               "border-danger-600",
               "text-danger-600", */
          |]
        | Default => [|
            "glass-default",
            "text-current",
            /* "bg-default-200",
               "border-default-600",
               "text-default-600", */
          |]
        | Primary => [|
            "glass-primary",
            "text-current",
            /* "bg-primary-200",
               "border-primary-600",
               "text-primary-600", */
          |]
        | Warning => [|
            "glass-warning",
            "text-current",
            /* "bg-warning-200",
               "border-warning-600",
               "text-warning-600", */
          |]
        }
      )
      |> Js.Array.map(item => ClassName.Value(item)),
    );
  <div className={"p-4" ++ ClassName.output(alertClassNames)}>
    children
  </div>;
};
