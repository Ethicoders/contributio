let str = React.string

type buttonData = {
  label: string,
  value: string,
  activeClassNames: option<string>,
}

@react.component
let make = (~icon=None, ~buttonsData: array<buttonData>, ~value=None, ~onChange=ignore) => {
  let (active, setActive) = React.useState(() => value)
  let classNameItems =
    [
      "border-none",
      "rounded-none",
      "bg-transparent",
      "hover:glow-none",
      "focus:glow-none",
      "hover:bg-opacity-10",
      "hover:bg-default",
      "focus:bg-opacity-10",
      "focus:bg-default",
      "-skew-x-0",
    ] |> Js.Array.map(item => ClassName.Value(item))

  let baseClassNames = ClassName.create(classNameItems)

  <div
    className="border-2 bg-default bg-opacity-10 border-default rounded-md inline-block hover:glow-default">
    <div className="">
      {switch icon {
      | None => React.null
      | Some(iconName) => <span className="mx-2 text-default"> <Icon name=iconName /> </span>
      }}
      {buttonsData
      ->Js.Array2.map(buttonData => {
        let activeClassNameItems = switch buttonData.activeClassNames {
        | Some(activeClassNames) =>
          Js.String.split(" ", activeClassNames) |> Js.Array.map(item => ClassName.Value(item))
        | None => []
        }

        let finalClassNames = switch active {
        | None => baseClassNames
        | Some(activeValue) =>
          activeValue === buttonData.value
            ? ClassName.merge(baseClassNames, activeClassNameItems)
            : baseClassNames
        }

        <Button
          className={ClassName.output(finalClassNames)}
          onClick={_ => {
            let newActive = switch active {
            | None => Some(buttonData.value)
            | Some(activeValue) => activeValue === buttonData.value ? None : Some(buttonData.value)
            }
            setActive(_ => newActive)
            onChange(newActive)
          }}>
          {buttonData.label->str}
        </Button>
      })
      ->React.array}
    </div>
  </div>
}
