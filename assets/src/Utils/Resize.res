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
    Webapi.Dom.Window.addEventListener("resize", onResize, window);
    Some(
      () => Document.removeEventListener("resize", onResize, document),
    );
  });

  elementRef;
};