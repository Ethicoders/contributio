let str = React.string

type buttonData = {
  label: string,
  value: string,
  activeClassNames: option<string>,
}

@react.component
let make = (~icon=None, ~buttonsData: array<buttonData>, ~onChange=ignore) => {
  let (active, setActive) = React.useState(() => None)
  let classNameItems =
    ["border-none", "rounded-none"] |> Js.Array.map(item => ClassName.Value(item))

  let baseClassNames = ClassName.create(classNameItems)

  <div className="border border-default rounded-md inline-block">
    {switch icon {
    | None => React.null
    | Some(iconName) => <span className="mx-2 text-default"><Icon name=iconName /></span>
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
}
