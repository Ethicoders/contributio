module SetProjectVisibility = %graphql(`
    mutation setProjectVisibility($id: String!, $status: Int!) {
      setProjectVisibility(id: $id, status: $status) {
        project {
          id
        }
      }
    }
   `)

let trigger = (id: string, status, onDone) =>
  Client.instance.mutate(~mutation=module(SetProjectVisibility), {id: id, status})
  ->Promise.then(result =>
    Promise.resolve(
      switch result {
      | Ok(_) =>
        onDone()
        React.null
      | Error(_) => React.null
      },
    )
  )
  ->ignore
