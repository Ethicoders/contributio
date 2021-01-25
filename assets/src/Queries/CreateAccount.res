let str = React.string

module CreateLinkedAccount = %graphql(`
    mutation createLinkedAccount($originId: Int!, $content: String!) {
      createLinkedAccount(originId: $originId, content: $content) {
        user {
          id
        }
      }
    }
   `)

let trigger = (accessToken, onDone) =>
  Client.instance.mutate(~mutation=module(CreateLinkedAccount), {originId: 1, content: accessToken})
  ->Promise.Promise.then_(result =>
    Js.Promise.resolve(
      switch result {
      | Ok(_) =>
        onDone()
        React.null
      | Error(_) => React.null
      },
    )
  )
  ->ignore
