let str = React.string;

module GetProjects = [%graphql
  {|
    query getProjects($after: String, $search: String, $languages: String, $topic: String) {
      projects(after: $after, first: 6, search: $search, languages: $languages, topic: $topic) {
        edges {
          node {
            id
            name
            url
            description
            topics
            license
            languages
          }
          cursor
        }
        pageInfo {
          hasNextPage
          hasPreviousPage
          startCursor
          endCursor
        }
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

// type ref('a) = {
//   mutable contents: 'a,
// };

[@react.component]
let make = () => {
  let emptyLanguage: Select.item = {label: "Language", value: None};

  let (languageIndex, setLanguage) = React.useState(() => 0);
  let (languagesArray, setLanguages) =
    React.useState(() => [|emptyLanguage|]);
  let (searchString, setSearchString) = React.useState(() => "");
  let canFetch = ref(false);
  let maybeNextCursor = ref(None);

  let queryResult =
    GetProjects.use({
      after: None,
      languages: languagesArray[languageIndex].value,
      search: searchString == "" ? None : Some(searchString),
      topic: None,
    });

  let elementRef =
    OnScroll.useScroll(
      ~modifier=100,
      ~watched=maybeNextCursor,
      _ => {
        Js.log2(canFetch^, Belt.Option.getWithDefault(maybeNextCursor^, ""));
        // two problems:
        // - request is executed twice
        // - cursor is not updated (depends on above, IMO)
        if (canFetch^
            && Belt.Option.getWithDefault(maybeNextCursor^, "") !== "") {
          canFetch := false;
          queryResult.fetchMore(
            ~updateQuery=
              (previousData, {fetchMoreResult}) => {
                switch (fetchMoreResult) {
                | Some({projects}) =>
                  Js.log("fetchingmore");
                  if (Belt.Option.getExn(projects).pageInfo.hasNextPage) {
                    maybeNextCursor :=
                      Belt.Option.getExn(projects).pageInfo.endCursor;
                    Js.log2(
                      Belt.Option.getExn(projects).pageInfo.endCursor,
                      maybeNextCursor,
                    );
                  };
                  canFetch := true;
                  {
                    projects:
                      switch (previousData.projects) {
                      | Some(data) =>
                        Some({
                          ...data,
                          edges:
                            Some(
                              Belt.Array.concat(
                                Belt.Option.getExn(data.edges),
                                Belt.Option.getExn(
                                  Belt.Option.getExn(projects).edges,
                                ),
                              ),
                            ),
                        })
                      | None => None
                      },
                  };
                | None => previousData
                }
              },
            ~variables={
              after: maybeNextCursor^,
              languages: languagesArray[languageIndex].value,
              search: searchString == "" ? None : Some(searchString),
              topic: None,
            },
            (),
          )
          ->ignore;
        };
      },
    );

  /* {
    switch (queryResult) {
    | {data: None} => ()
    | {loading: true} => ()
    | {data: Some({projects}), loading: false} =>
      switch (projects) {
      | None => ()
      | Some(payload) =>
        Js.log2("recalled", payload.pageInfo.hasNextPage);
        maybeNextCursor :=
          payload.pageInfo.hasNextPage ? payload.pageInfo.endCursor : Some("");
        canFetch := true;
      }
    };
  }; */

  // let topic = "";
  <div className="p-2" ref={ReactDOM.Ref.domRef(elementRef)}>
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
         switch languages {
         | [||] => "No languages yet!"->str
         | values => 
         let selectItems =
           values
           |> Js.Array.map(item => {
                let item: Select.item = {label: item, value: Some(item)};
                item;
              });
         if (Js.Array.length(languagesArray) == 1) {
           setLanguages(currentLanguages =>
             Belt.Array.concat(currentLanguages, selectItems)
           );
         };
         <Select
           label="Language"
           items=languagesArray
           onChange={value => {
             //  setNextCursor(_ => None);
             maybeNextCursor := None;
             setLanguage(_ => value);
           }}
           selected=languageIndex
         />;
         }
       }}
      <div className="">
        <InputGroup
          iconName=Icon.Search
          onChange={value => setSearchString(_ => value)}
          label="Search"
        />
      </div>
    </div>
    /* {switch (queryResult) {
     | {loading: true} => "Loading..."->React.string
     | {data: None} => React.null
     | {data: Some({projects}), loading: false} =>
       let values =
         switch (projects) {
         | None => [||]
         | Some(any) =>
           switch (any.edges) {
           | None => [||]
           | Some(values) =>
             values->Belt.Array.map(value =>
               switch (value) {
               | None => None
               | Some(project) => Some(project.node)
               }
             )
           }
         };
       <>
         <div className="grid grid-cols-3 gap-4">
           {switch (values) {
            | [||] => "No results!"->str
            | values =>
              values
              ->Belt.Array.map(project =>
                  switch (project) {
                  | None => React.null
                  | Some(project) =>
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
                  }
                )
              ->React.array
            }}
         </div>
       </>;
     }} */
  </div>;
};
