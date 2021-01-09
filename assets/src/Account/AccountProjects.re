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

[@react.component]
let make = () => {
  <div>
    <h1> "My Projects"->str </h1>
    {switch (GetUserProjects.use()) {
      | {loading: true} => "Loading..."->React.string
      | {data: Some({my}), loading: false} =>
        <div className="grid grid-cols-3 gap-4">
          {switch my.projects {
           | None => "No projects yet!"->str
          | Some(items) => items
          ->Belt.Array.map(project =>
              <Project
                key={project.name}
                name={project.name}
                url={project.url}
              />
            )
          ->React.array
          };}
        </div>
      | {data: None} => "No projects yet!"->str
      }}
  </div>;
};
