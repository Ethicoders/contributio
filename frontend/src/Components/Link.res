type target =
  | Path(string)
  | Routes(Routes.routes)

@react.component
let make = (~children, ~className=?, ~onClick=?, ~to) => {
  let path = switch to {
  | Path(path) => path
  | Routes(routes) => Routes.buildPath(routes)
  }
  <a
    className={switch className {
    | Some(className) => className
    | None => ""
    }}
    href={path}
    onClick={e => {
      ReactEvent.Mouse.preventDefault(e)
      RescriptReactRouter.push(path)

      switch onClick {
      | Some(onClick) => onClick(e)
      | None => ()
      }
    }}>
    {children}
  </a>
}
