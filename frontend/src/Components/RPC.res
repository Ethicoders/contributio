let str = React.string

type fetchable<'data> =
  | Pending
  | Success('data)
  | Failure(string)

@react.component
let make = (~prom: Promise.t<'a>, ~children) => {
  open Promise
  let (data, setData) = React.useState(() => Pending)
  React.useEffect1(() => {
    prom
    ->then(result => {
      switch result {
      | Ok(payload) => setData(_ => Success(payload))
      | Error(e) =>
        Js.log(e)
        setData(_ => Failure("Failed to fetch data"))
      }
      resolve()
    })
    ->ignore
    None
  }, [])

  <> {children(data)} </>
}
