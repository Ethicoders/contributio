let str = React.string

type requestAccessTokenResponse = {accessToken: string}

let requestAccessToken = async (code): result<requestAccessTokenResponse, _> => {
  let response = await Client.call("request_access_token", [{"code": code}])
  response->Result.map(response =>
    response->S.parseOrThrow(
      S.object(s => ({
        accessToken: s.field("access_token", S.string),
      })),
    )
  )
}

let updateAccount = async (accessToken): result<unit, _> => {
  let response = await Client.call("update_user", [{"access_tokens": accessToken}])
  response->Result.map(_ => ())
}

@react.component
let make = (~code) => {
  module RequestAccessToken = RPC

  // let requestAccessTokenQuery = RequestAccessToken.make(~code, ());
  <RequestAccessToken prom={requestAccessToken(code)}>
    {result =>
      <div>
        <h1> {"Requesting access token"->str} </h1>
        {switch result {
        | Pending => <div> {"Fetching access token..."->str} </div>
        | Failure(e) =>
          Js.log(e)
          "Something Went Wrong"->str
        | Success(response) =>
          module AccountUpdate = RPC
          // let updateAccountMutation =
          //   AccountUpdate.make(
          //     ~accessTokens=response##requestAccessToken##accessToken,
          //     (),
          //   );
          <AccountUpdate prom={updateAccount(response.accessToken)}>
            {response => {
              <div>
                {switch response {
                | Failure(e) =>
                  Js.log(e)
                  "Something Went Wrong"->str
                | Pending => "Loading..."->str
                | Success(_) =>
                  Js.log("Success")
                  <div> {"Done"->str} </div>
                }}
              </div>
            }}
          </AccountUpdate>
        }}
      </div>}
  </RequestAccessToken>
}
