/* let str = React.string;

module SetUserAccessTokenGQL = [%graphql
  {|
    mutation setUserAccessToken($vendor: String!, $content: String!) {
      setUserAccessToken(vendor: $vendor, content: $content) {
        id
      }
    }
   |}
];

[@react.component]
let make = (~accessToken) => {
  let (mutate, result) = SetUserAccessTokenGQL.use();

  mutate(
    ~update=
      (_, {data}) =>
        switch (data) {
        | Some(_) => ()
        | None => ()
        },
        {
          vendor: "github", content: accessToken
        },
  )
  ->ignore

  switch (result) {
  | {called: false} =>
    <>
      "Not called... "->React.string
    </>
  | {loading: true} => "Loading..."->str
  | {data: Some(_), error: None} => "Done."->str
  | {error} =>
    <>
      "Error loading data"->str
      {switch (error) {
      | Some(error) => React.string(": " ++ error.message)
      | None => React.null
      }}
    </>
  };
    
}; */