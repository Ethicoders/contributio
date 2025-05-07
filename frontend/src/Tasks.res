let str = React.string

@react.component
let make = () => {
  let url = RescriptReactRouter.useUrl()
  let view = switch url.path {
  | list{"projects", taskID} => <SingleTask taskID/>
  | _ => <AllTasks />
  }

  <div>
    view
  </div>

}
