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

    if (Session.isConnected()) {
      <LinkAccount
        content=response.requestAccessToken.accessToken
        onDone={() => {
          Window.postMessage("link:success");
          Window.close();
        }}
      />;
    } else {
      {
        CreateAccount.trigger(
          response.requestAccessToken.accessToken,
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
