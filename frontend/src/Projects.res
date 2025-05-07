let str = React.string

@react.component
let make = () => {
  let url = RescriptReactRouter.useUrl()
  let view = switch url.path {
  | list{"projects", projectID} => <SingleProject projectID/>
  | _ => <AllProjects />
  }

  <div>
    view
  </div>

}
