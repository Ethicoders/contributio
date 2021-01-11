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

// Absolutely disgusting but "Language" was
// added twice to the list :|
let addLanguageOption = languages => {
  let _ =
    if (!Js.Array.includes("Language", languages)) {
      let _ = Js.Array.unshift("Language", languages);
      ();
    };
  ();
};

[@react.component]
let make = () => {
  let (language, setLanguage) = React.useState(() => "Language");
  <div>
    <Heading size=Big> "Projects"->str </Heading>
    <div className="grid grid-cols-3 gap-4">
      {switch (GetProjectsLanguages.use()) {
       | {loading: true} => <span> "Loading languages..."->str </span>
       | {data: None} => <span> "No languages yet"->str </span>
       | {error: Some(_error)} => "Error"->str
       | {called: false, data: Some(_), error: None, loading: false} =>
         "Do"->str
       | {called: true, data: Some({languages}), loading: false} =>
         addLanguageOption(languages);
         <Select
           label="Language"
           options=languages
           onChange={value => setLanguage(_ => value)}
           selected=language
         />;
       }}
      <div className=""> <InputGroup label="Search" /> </div>
    </div>
    {switch (GetProjects.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({projects}), loading: false} =>
       <div className="grid grid-cols-3 gap-4">
         /* {switch (projects) {
            | None => "No projects yet!"->str
            | Some(items) => */

           {projects
            ->Belt.Array.map(project =>
                <Project
                  key={project.name}
                  name={project.name}
                  url={project.url}
                />
              )
            ->React.array}
         </div>
     /* }} */
     | {data: None} => <div />
     }}
  </div>;
};
