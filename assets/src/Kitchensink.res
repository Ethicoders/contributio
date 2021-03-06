let str = React.string

@bs.scope("JSON") @bs.val
external parse: string => Js.Json.t = "parse"

let levels = ["default", "primary", "warning", "danger"]

let resolveWith = (values, index) => {
  values[index]
}

let item = parse(`{"Elixir": 1, "ReScript": 1}`)

@react.component
let make = () => {
  <div className="p-2 text-current">
    <div className="py-3">
      <Heading>{"Alert"->str}</Heading>
      {levels
      |> Js.Array.mapi((_level, index) =>
        <Alert
          className="my-1"
          type_={resolveWith([Alert.Default, Alert.Primary, Alert.Warning, Alert.Danger], index)}>
          {"This is an alert"->str}
        </Alert>
      )
      |> React.array}
    </div>
    <div className="py-3">
      <Heading>{"Button"->str}</Heading>
      {levels
      |> Js.Array.mapi((_level, index) =>
        <Button
          className="mx-1"
          type_={resolveWith(
            [Button.Default, Button.Primary, Button.Warning, Button.Danger],
            index,
          )}>
          {"Proceed"->str}
        </Button>
      )
      |> React.array}
      <Button className="mx-1" disabled=true> {"Disabled"->str} </Button>
    </div>
    <div className="py-3">
      <Heading>{"Button Group"->str}</Heading>
      <ButtonGroup
        buttonsData=[
          {label: "Test", value: "test", activeClassNames: None},
          {label: "Bla", value: "bla", activeClassNames: None},
        ]
      />
    </div>
    <div className="py-3"> 
      <Heading>{"Checkbox"->str}</Heading>
      <Checkbox label="Checkbox" value="test" /> 
    </div>
    <div className="py-3"> 
      <Heading>{"Dropdown"->str}</Heading>
      <Dropdown position={Dropdown.BottomRight}> {"This is a dropdown"->str} </Dropdown> 
    </div>
    <div className="py-3"> 
      <Heading>{"Experience"->str}</Heading>
      <Experience amount="12" /> 
    </div>
    <div className="py-3"> 
      <Heading>{"Input Group"->str}</Heading>
      <InputGroup label="Test" iconName=Icon.Search /> 
    </div>
    <div className="py-3">
      <Heading>{"Project"->str}</Heading>
      <Project
        id="12"
        name="Test"
        description="This is a project"
        url="#"
        maybeLanguages=item
        maybeTopics=Some(["elixir", "rescript"])
        maybeLicense=None
      />
    </div>
    <div className="py-3">
      <Heading>{"Select"->str}</Heading>
      <Select
        label="Select" items=[{label: "Test", value: Some("test")}] selected=0 onChange=ignore
      />
    </div>
    <div className="py-3">
      <Heading>{"Task"->str}</Heading>
      <Task
        id="12"
        name="Task"
        content="This is a task"
        experience=12
        difficulty=1
        status=1
        time=4
        maybeProject=None
      />
    </div>
  </div>
}
