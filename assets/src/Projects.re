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

module GetProjectsLanguages = [%graphql
  {|
    query getProjectsLanguages {
      languages
    }
|}
];

[@react.component]
let make = () => {
  <div>

      "Projects"->str
      <div className="grid grid-cols-3 gap-4">
        <div className="">
          {switch (GetProjects.use()) {
           | {loading: true} => "Loading..."->React.string
           | {data: Some({projects}), loading: false} =>
             <div className="grid grid-cols-3 gap-4">
               {switch projects {
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
           | {data: None} => <div />
           }}
        </div>
        {switch (GetProjectsLanguages.use()) {
         | {data: Some({languages})} => <Select label="Language" options=languages />
         | {data: None} => <div />
         }}
        <div className=""> <InputGroup label="Search" /> </div>
      </div>
    </div>;
};
