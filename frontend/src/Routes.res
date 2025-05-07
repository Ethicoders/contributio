type accountRoutes =
  | Home
  | Projects

type routes =
  | Home
  | Account(accountRoutes)
  | Projects(option<string>)
  | Tasks(option<string>)

let buildPath = route => {
  {
    switch route {
    | Home => "/"
    | Projects(project) =>
      "/projects" ++
      switch project {
      | Some(project) => "/" ++ project
      | None => ""
      }
    | Account(subroute) =>
      "/account" ++
      switch subroute {
      | Home => ""
      | Projects => "/projects"
      }
    | Tasks(task) => "/tasks" ++ switch task {
      | Some(task) => "/" ++ task
      | None => ""
      }
    }
  }
}
