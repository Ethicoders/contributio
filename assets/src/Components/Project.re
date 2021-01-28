let str = React.string;

[@react.component]
let make =
    (
      ~id,
      ~name,
      ~description,
      ~url,
      ~maybeLanguages,
      ~maybeTopics,
      ~maybeLicense,
    ) => {
  <div className="card px-4 pb-4 pt-2 border-2 rounded-md relative">
    <Anchor target={"/projects/" ++ id} className="text-primary">
      <Heading> name->str </Heading>
    </Anchor>
    <div className="absolute right-2 top-2">
      <a href=url target="_blank">
        <Button> <Icon name=ExternalLink /> </Button>
      </a>
    </div>
    <div className="text-sm">
      {switch (Js.Json.decodeObject(maybeLanguages)) {
       | Some(languages) =>
         Js.Dict.keys(languages)
         ->Belt.Array.map(language =>
             <> <span className="text-current m-1"> language->str </span> </>
           )
         ->React.array
       | None => React.null
       }}
    </div>
    <div className="text-sm">
      {switch (maybeTopics) {
       | None => React.null
       | Some(topics) =>
         topics
         ->Belt.Array.map(topic =>
             <>
               <Icon name=Tag />
               <span className="text-current m-1"> topic->str </span>
             </>
           )
         ->React.array
       }}
    </div>
    <div>
      {switch (maybeLicense) {
       | None => React.null
       | Some(license) => license->str
       }}
    </div>
    <div className="text-current"> description->str </div>
  </div>;
};
