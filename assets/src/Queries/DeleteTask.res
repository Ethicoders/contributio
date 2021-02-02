module DeleteTaskQuery = %graphql(`
    mutation deleteTask($id: String!) {
      deleteTask(id: $id) {
        id
      }
    }
   `)

let trigger = (id: string, onDone) =>
  Client.instance.mutate(~mutation=module(DeleteTaskQuery), {id: id})
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
