let str = React.string;

module GetUserProjects = [%graphql
  {|
    query getUserProjects {
      my {
        email
        projects {
          name
          url
          description
        }
      }
    }
|}
];

module GetUserProjectsQuery = ReasonApollo.CreateQuery(GetUserProjects);

[@react.component]
let make = () => {
  <div>
    <h1> "My Projects"->str </h1>
    <GetUserProjectsQuery>
      ...{({result, _}) =>
        <div>
          {switch (result) {
           | Error(e) =>
             Js.log(e);
             "Something Went Wrong"->str;
           | Loading => "Loading"->str
           | Data(details) =>
             switch (details##my##projects) {
             | Some(projects) =>
               <div className="grid grid-cols-3 gap-4">
                 {projects
                  ->Belt.Array.map(project =>
                      <Project
                        key={project##name}
                        name=project##name
                        url=project##url
                      />
                    )
                  ->React.array}
               </div>
             | None => <div> "No projects yet!"->str </div>
             }
           }}
        </div>
      }
    </GetUserProjectsQuery>
  </div>;
};
