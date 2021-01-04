[@bs.val] external entries: Js.t({..}) => array((string, _)) = "Object.entries";

module Obj = Js.Obj;
module Array = Js.Array;

let buildFrom = (uri, parts: list(string), args: Js.t('a)) => {
    let fields = entries(args);
    let queryArgs = if (Array.length(fields) > 0) {
        "?" ++ Array.joinWith("&", Array.map(((key, value)) => key ++ "=" ++ Js.String.make(value), fields))
    } else {
        ""
    }

    uri ++ List.join("/", parts) ++ queryArgs
}

let parseQueryArgs = (queryArgs: string) => {
    let out = Js.String.split("&", queryArgs) |> Array.map((arg) => {
        let split = Js.String.split("=", arg);
        (Array.unsafe_get(split, 0), Array.unsafe_get(split, 1))
    });
    Js.Dict.fromArray(out)
}