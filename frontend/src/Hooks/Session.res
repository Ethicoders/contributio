type user = {
  id: int,
  name: string,
  email: string,
}

type session =
  | Authenticated(user)
  | Unauthenticated

let userSchema = S.object(s => {
  id: s.field("id", S.int),
  name: s.field("name", S.string),
  email: s.field("email", S.string),
})

let getCurrentUser = async (): result<user, _> => {
  let response = await Client.call("me", [])
  response->Result.map(response => response->S.parseOrThrow(userSchema))
}

let useSession = () => {
  let (session, setSession) = React.useState(() => Unauthenticated)

  React.useEffect(() => {
    open Promise
    getCurrentUser()
    ->then(result => {
      resolve(
        switch result {
        | Ok(user) => setSession(_ => Authenticated(user))
        | Error(_) => setSession(_ => Unauthenticated)
        },
      )
    })
    ->ignore
    None
  }, [])

  session
}
