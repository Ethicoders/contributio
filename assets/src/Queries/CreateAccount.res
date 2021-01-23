let str = React.string

module Promise = {
  let then_ = (promise, f) => Js.Promise.then_(f, promise)
  let ignore: Js.Promise.t<_> => unit = ignore
}

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
  ->Promise.then_(result =>
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
