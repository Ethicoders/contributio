type project = {
  id: int,
  name: string,
  // repoID: int,
  description: string,
  // url: string,
  // languages: array<string>,
  userID: int,
  // :origin,: Contributio.Platforms.Origin
}

let projectSchema = S.object(s => {
  id: s.field("id", S.int),
  name: s.field("name", S.string),
  // repoID: s.field("repo_id", S.int),
  description: s.field("description", S.string),
  // url: s.field("url", S.string),
  userID: s.field("user_id", S.int),
  // languages: s.field("languages", S.array(S.string)),
})

let getProjects = async (): result<array<project>, _> => {
  let response = await Client.call("get_projects", [{"offset": 1, "limit": 10}])
  Js.log(response)
  response->Result.map(response => response->S.parseOrThrow(S.array(projectSchema)))
}

@react.component
let make = () => {
  module Projects = RPC

  open I18n

  <div>
    {"Projects"->tr}

    // <div className="grid grid-cols-3 gap-4">
    //   <div className="">
    //     <GetProjectsLanguagesQuery>
    //       ...{({result, _}) =>
    //         <>
    //           {switch (result) {
    //            | Error(e) =>
    //              Js.log(e);
    //              "Something Went Wrong"->str;
    //            | Loading => "Loading"->str
    //            | Data(data) =>
    //              <Select label="Language" options=data##languages />
    //            }}
    //         </>
    //       }
    //     </GetProjectsLanguagesQuery>
    //   </div>
    //   <div className=""> <InputGroup label="Search" /> </div>
    // </div>

    <Projects prom={getProjects()}>
      {result => {
        switch result {
        | Pending => "Loading"->tr
        | Failure(e) =>
          Js.log(e)
          "Something Went Wrong"->tr
        | Success([]) => <div> {"No projects yet!"->tr} </div>
        | Success(projects) =>
          <div className="grid grid-cols-3 gap-4">
            {projects
            ->Array.map(project =>
              <Link
                to={Routes(Projects(Some(project.name)))}
                className="card bg-base-100 w-96 shadow-sm"
                key={project.name}>
                <GridProject key={project.name} name=project.name description=project.description />
              </Link>
            )
            ->React.array}
          </div>
        }
      }}
    </Projects>
  </div>
}
