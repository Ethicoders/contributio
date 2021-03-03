open Webapi.Dom;

let useResize = (onResize) => {
  let elementRef = React.useRef(Js.Nullable.null);
//   let handleResize = (e) => {
//     elementRef.current
//     ->Js.Nullable.toOption
//     ->Belt.Option.map(_ =>
//         onResize(e)
//       )
//     ->ignore;
//   };

  React.useEffect0(() => {
    Document.addEventListener("resize", onResize, document);
    Document.addEventListener("scroll", (_) => Js.log("rsz"), document)
    Some(
      () => Document.removeEventListener("resize", onResize, document),
    );
  });

  elementRef;
};