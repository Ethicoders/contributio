module DeleteProjectQuery = %graphql(`
    mutation deleteProject($id: String!) {
      deleteProject(id: $id) {
        id
      }
    }
   `)

let trigger = (id: string, onDone) =>
  Client.instance.mutate(~mutation=module(DeleteProjectQuery), {id: id})
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
