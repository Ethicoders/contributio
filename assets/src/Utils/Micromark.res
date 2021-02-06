@bs.module("micromark")
external micromark: string => string = "default"

let str = React.string

let render = markdown => {
  Js.String.replaceByRe(%re("/<!--[\s\S]*?-->/g"), "", markdown)
}

@react.component
let make = (~markdown) => {
  <div dangerouslySetInnerHTML={"__html": micromark(markdown)} />
}
