let str = React.string;

module GetProjects = [%graphql
  {|
    query getProjects {
      projects {
        id
        name
        url
        description
        topics
        license
        languages
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
  <div className="p-2">
    <div className="hidden">
      <Heading size=Gigantic> "Projects"->str </Heading>
    </div>
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
         {switch (projects) {
          | [||] => "No projects yet!"->str
          | values =>
            values
            ->Belt.Array.map(project =>
                <Project
                  key={project.id}
                  id={project.id}
                  name={project.name}
                  description={project.description}
                  url={project.url}
                  maybeTopics={project.topics}
                  maybeLicense={project.license}
                  maybeLanguages={project.languages}
                />
              )
            ->React.array
          }}
       </div>
     | {data: None} => <div />
     }}
  </div>;
};
