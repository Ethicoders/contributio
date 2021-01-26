let str = React.string;

[@react.component]
let make = (~className="", ~activeClassNames="active", ~target, ~children) => {
  let url = ReasonReactRouter.useUrl();

  let path =
    if (Js.List.length(url.path) > 0) {
      "/" ++ List.join("/", url.path);
    } else {
      "";
    };
  let classNameItems =
    Js.String.split(" ", className)
    |> Js.Array.map(item => ClassName.Value(item));

  let activeClassNameItems =
    Js.String.split(" ", activeClassNames)
    |> Js.Array.map(item => ClassName.Value(item));

  let baseClassNames =
    if (path == target) {
      ClassName.merge(
        ClassName.create(classNameItems),
        activeClassNameItems,
      );
    } else {
      ClassName.create(classNameItems);
    };

  <a
    href=target
    onClick={e => Router.goTo(e, target)}
    className={ClassName.output(baseClassNames)}>
    children
  </a>;
};
