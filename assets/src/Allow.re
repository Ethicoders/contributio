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
  switch (RequestAccessToken.use({originId: 1, code})) {
  | {data: Some(response)} =>
    let accessToken =
      Js.Dict.unsafeGet(
        Url.parseQueryArgs(response.requestAccessToken.accessToken),
        "access_token",
      );

    if (Session.isConnected()) {
      <LinkAccount
        accessToken
        onDone={() => {
          Window.postMessage("link:success");
          Window.close();
        }}
      />;
    } else {
      {
        CreateAccount.trigger(
          accessToken,
          () => {
            Window.postMessage("link:success");
            Window.close();
          },
        );
      };
      React.null;
    };

  | {data: None} => <div> "Loading..."->str </div>
  };
};
