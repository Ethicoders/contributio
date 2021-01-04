module RequestAccessToken = [%graphql
  {|
    query requestAccessToken($code: String!) {
      requestAccessToken(code: $code) {
        accessToken
      }
    }
   |}
];

module RequestAccessTokenQuery = ReasonApollo.CreateQuery(RequestAccessToken);

module AccountUpdate = [%graphql
  {|
    mutation updateUser($accessTokens: String) {
      updateUser(accessTokens: $accessTokens) {
        id
      }
    }
   |}
];

module AccountUpdateMutation = ReasonApollo.CreateMutation(AccountUpdate);

let str = React.string;

[@react.component]
let make = (~code) => {
  let requestAccessTokenQuery = RequestAccessToken.make(~code, ());
  <RequestAccessTokenQuery variables=requestAccessTokenQuery##variables>
    {({result}) =>
       <div>
         <h1> "Requesting access token"->str </h1>
         {switch (result) {
          | Error(e) =>
            Js.log(e);
            "Something Went Wrong"->str;
          | Loading => "Loading..."->str
          | Data(response) =>
            let updateAccountMutation =
              AccountUpdate.make(
                ~accessTokens=response##requestAccessToken##accessToken,
                (),
              );
            <AccountUpdateMutation>
              ...{(mutation, out) => {
                mutation(~variables=updateAccountMutation##variables, ())
                |> ignore;
                <div>
                  {switch (out.result) {
                   | NotCalled => "Not called"->str
                   | Error(e) =>
                     Js.log(e);
                     "Something Went Wrong"->str;
                   | Loading => "Loading..."->str
                   | Data(_) =>
                     Js.log("Success");
                     <div> "Done"->str </div>;
                   }}
                </div>;
              }}
            </AccountUpdateMutation>;
          }}
       </div>}
  </RequestAccessTokenQuery>;
};
