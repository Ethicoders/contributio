let str = React.string;

module GetProjects = [%graphql
  {|
    query getProjects {
      projects {
        name
        url
        description
      }
    }
|}
];

module GetProjectsQuery = ReasonApollo.CreateQuery(GetProjects);

module GetProjectsLanguages = [%graphql
  {|
    query getProjectsLanguages {
      languages
    }
|}
];

module GetProjectsLanguagesQuery =
  ReasonApollo.CreateQuery(GetProjectsLanguages);

[@react.component]
let make = () => {
  <div>
    "Projects"->str
    <div className="grid grid-cols-3 gap-4">
      <div className="">
        <GetProjectsLanguagesQuery>
          ...{({result, _}) =>
            <>
              {switch (result) {
               | Error(e) =>
                 Js.log(e);
                 "Something Went Wrong"->str;
               | Loading => "Loading"->str
               | Data(data) =>
                 <Select label="Language" options=data##languages />
               }}
            </>
          }
        </GetProjectsLanguagesQuery>
      </div>
      <div className=""> <InputGroup label="Search" /> </div>
    </div>
    <GetProjectsQuery>
      ...{({result, _}) =>
        <div>
          {switch (result) {
           | Error(e) =>
             Js.log(e);
             "Something Went Wrong"->str;
           | Loading => "Loading"->str
           | Data(data) =>
             switch (data##projects) {
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
    </GetProjectsQuery>
  </div>;
};
