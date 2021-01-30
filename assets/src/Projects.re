let str = React.string;

module GetProjects = [%graphql
  {|
    query getProjects($search: String, $languages: String, $topic: String) {
      projects(search: $search, languages: $languages, topic: $topic) {
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


[@react.component]
let make = () => {
  let emptyLanguage: Select.item = {label: "Language", value: None};
  let (languageIndex, setLanguage) = React.useState(() => 0);
  let (languagesArray, setLanguages) =
    React.useState(() => [|emptyLanguage|]);
  // let topic = "";
  let (searchString, setSearchString) = React.useState(() => "");
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
         let selectItems =
           languages
           |> Js.Array.map(item => {
                let item: Select.item = {label: item, value: Some(item)};
                item;
              });
         if (Js.Array.length(languagesArray) == 1) {
           setLanguages(currentLanguages =>
             Js.Array.concat(selectItems, currentLanguages)
           );
         };
         <Select
           label="Language"
           items=languagesArray
           onChange={value => setLanguage(_ => value)}
           selected=languageIndex
         />;
       }}
      <div className="">
        <InputGroup
          iconName=Icon.Search
          onChange={value => setSearchString(_ => value)}
          label="Search"
        />
      </div>
    </div>
    {switch (
       GetProjects.use({
         languages: languagesArray[languageIndex].value,
         search: searchString == "" ? None : Some(searchString),
         topic: None,
       })
     ) {
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
