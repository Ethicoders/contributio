let str = React.string;

module RequestAccessToken = [%graphql
  {|
    query requestAccessToken($originId: Int!, $code: String!) {
      requestAccessToken(originId: $originId, code: $code) {
        accessToken
      }
    }
   |}
];

[@react.component]
let make = (~code) => {
  switch (RequestAccessToken.use({originId: 1, code: code})) {
  | {data: Some(response)} =>
    let accessToken =
      Js.Dict.unsafeGet(
        Url.parseQueryArgs(response.requestAccessToken.accessToken),
        "access_token",
      );
    <LinkAccount accessToken onDone={() => Window.close()} />;

  | {data: None} => <div> "Loading..."->str </div>
  };
};
