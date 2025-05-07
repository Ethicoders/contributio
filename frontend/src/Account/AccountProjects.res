let str = React.string

type project = {
  id: int,
  name: string,
  repoID: int,
  description: string,
  url: string,
  languages: array<string>,
  userID: int,
  // :origin,: Contributio.Platforms.Origin
}

let projectSchema = S.object(s => {
  id: s.field("id", S.int),
  name: s.field("name", S.string),
  repoID: s.field("repo_id", S.int),
  description: s.field("description", S.string),
  url: s.field("url", S.string),
  userID: s.field("user_id", S.int),
  languages: s.field("languages", S.array(S.string)),
})

let getUserProjects = async (): result<array<project>, _> => {
  let response = await Client.call("get_projects", [{"belongs_to": 1}])
  Js.log(response)
  response->Result.map(response => response->S.parseOrThrow(S.array(projectSchema)))
}

@react.component
let make = () => {
  module Projects = RPC

  <div>
    <h1> {str("My Projects")} </h1>
    <Projects prom={getUserProjects()}>
      {data => {
        switch data {
        | Pending => <div> {str("Fetching projects...")} </div>
        | Success([]) => <div> {str("Ugh... empty!")} </div>
        | Success(projects) =>
          <div>
            <ul>
              {projects
              ->Array.map(project => {
                <li key={project.name}>
                  <Link to={Routes(Projects(Some(Int.toString(project.id))))}>
                    {str(project.name)}
                  </Link>
                </li>
              })
              ->React.array}
            </ul>
          </div>
        | Failure(_e) => <div> {str("Failed fetching projects.")} </div>
        }
      }}
    </Projects>
  </div>
}
