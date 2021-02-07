let str = React.string;

module LinkAccountGQL = [%graphql
  {|
    mutation linkAccount($originId: Int!, $content: String!) {
      linkAccount(originId: $originId, content: $content) {
        id
      }
    }
   |}
];

[@react.component]
let make = (~content, ~onDone) => {
  let (mutate, result) = LinkAccountGQL.use();

  mutate(
    ~update=
      (_, {data}) =>
        switch (data) {
        | Some(_) => ()
        | None => ()
        },
    {originId: 1, content: content},
  )
  ->ignore;

  switch (result) {
  | {called: false} => <> "Not called... "->React.string </>
  | {loading: true} => "Loading..."->str
  | {data: Some(_), error: None} =>
    onDone();
    "Done."->str;
  | {error} =>
    <>
      "Error loading data"->str
      {switch (error) {
       | Some(error) => React.string(": " ++ error.message)
       | None => React.null
       }}
    </>
  };
};
