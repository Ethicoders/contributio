module Promise = {
  let then_ = (promise, f) => Js.Promise.then_(f, promise)
  let ignore: Js.Promise.t<_> => unit = ignore
}