open Webapi.Dom;

let handleScrollBeyondLimit = (e: Dom.wheelEvent, fn) => {
  Functions.debounce(~fn={_ => fn(e)});
};

let useScroll = (~modifier=0, ~watched, onScroll: Dom.wheelEvent => unit) => {
  let elementRef = React.useRef(Js.Nullable.null);
  let handleScroll = (e: Dom.wheelEvent) => {
    elementRef.current
    ->Js.Nullable.toOption
    ->Belt.Option.map(refValue => {
        let boundingClient =
          Webapi.Dom.Element.getBoundingClientRect(refValue);

        let windowBottom =
          Webapi.Dom.Window.scrollY(Webapi.Dom.window)
          +. (
            Webapi.Dom.Window.innerHeight(Webapi.Dom.window) |> float_of_int
          );
        let bottom = Webapi.Dom.DomRect.bottom(boundingClient);

        if (windowBottom > bottom +. float_of_int(modifier)) {
          handleScrollBeyondLimit(e, onScroll)();
        };
      })
    ->ignore;
  };

  React.useEffect1(() => {
    Document.addWheelEventListener(handleScroll, document);
    Some(() => Document.removeWheelEventListener(handleScroll, document));
  }, [|watched|]);

  // React.useEffect(() => {
  //   Document.addWheelEventListener(handleScroll, document);
  //   Some(() => Document.removeWheelEventListener(handleScroll, document));
  // });

  elementRef;
};
