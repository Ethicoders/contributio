let call = async (operation: string, payload: array<'a>) => {
  open Fetch
  try {
    Js.log({"operation": operation, "payload": payload}
        ->RescriptCore.JSON.stringifyAny
        ->RescriptCore.Option.getExn
        ->Body.string)
    let resp = await Fetch.fetch(
      "http://localhost:4000/api",
      {
        method: #POST,
        credentials: #"include",
        mode: #cors,
        body: {"operation": operation, "payload": payload}
        ->RescriptCore.JSON.stringifyAny
        ->RescriptCore.Option.getExn
        ->Body.string,
        headers: Headers.fromObject({
          "Content-Type": "application/json",
          "Accept": "application/json",
        }),
      },
    );
    Js.log(resp);

    if Response.ok(resp) {
      Ok(await Response.json(resp))
    } else {
      Error("Request failed: " ++ Response.statusText(resp))
    }
  } catch {
  | _ => Error(`Request failed for operation "${operation}"!`)
  }
}
