let str = React.string

@react.component
let make = () => {
  let url = RescriptReactRouter.useUrl()
  let view = switch url.path {
  | list{"account", "projects"} => <AccountProjects />
  // | list{"account", "import"} => <Importer />
  | _ => <Details />
  }

  <div>
    {"Account"->str}
    <ul>
      <li>
        <Link to={Routes(Routes.Account(Home))}> {"Details"->str} </Link>
      </li>
      <li>
        <Link to={Routes(Routes.Account(Projects))}> {"My Projects"->str} </Link>
      </li>
    </ul>

    <hr />
    view
  </div>
}
