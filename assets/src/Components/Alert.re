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
    Js.log(ClassName.output(classNameItems));

  let alertClassNames =
    ClassName.merge(
      classNameItems,
      (
        switch (type_) {
        | Danger => [|
            "border-danger",
            "text-current",
            "bg-danger",
          |]
        | Default => [|
            "border-default",
            "text-current",
            "bg-default",
          |]
        | Primary => [|
            "border-primary",
            "text-current",
            "bg-primary",
          |]
        | Warning => [|
            "border-warning",
            "text-current",
            "bg-warning",
          |]
        }
      )
      |> Js.Array.map(item => ClassName.Value(item)),
    );
  <div className={"border-2 bg-opacity-10 p-4 rounded-md " ++ ClassName.output(alertClassNames)}>
    children
  </div>;
};
