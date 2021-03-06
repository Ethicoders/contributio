let str = React.string;

type directions =
  | TopLeft
  | TopRight
  | BottomLeft
  | BottomRight;

let resolvePosition = (position) => switch position {
| TopLeft => "origin-top-right"
| TopRight => "origin-top-right"
| BottomLeft => "right-0"
| BottomRight => "left-0"
};

[@react.component]
let make = (~children, ~label="", ~button=None, ~position=BottomLeft) => {
  let (isVisible, setVisible) = React.useState(() => false);
  let (position, _setPosition) = React.useState(() => position);

  /* let handleResize = _e => {
    Js.log("in");
  };
  let _ = Resize.useResize(handleResize); */

  
  let handleToggleMenu = (_e: ReactEvent.Mouse.t) => {
    /* setPosition(_ => e->ReactEvent.Mouse.target##offsetLeft === 0 ? BottomLeft : BottomRight); */
    setVisible(_ => !isVisible);
  };

  let style =
    isVisible
      ? ReactDOM.Style.make(~display="block", ())
      : ReactDOM.Style.make(~display="none", ());

  let handleClickOutside = _ => {
    setVisible(_ => false);
  };
  let divRef = ClickOutside.useClickOutside(handleClickOutside);

  <div className="relative inline-block" ref={ReactDOMRe.Ref.domRef(divRef)}>
    <div
      className="relative inline-block text-left"
      onClick={e => handleToggleMenu(e)}>
      {switch (button) {
       | None =>
         <button
           type_="button"
           className="bg-default bg-opacity-10 hover:glow-default inline-flex justify-center w-full rounded-md border-2 border-default shadow-sm px-4 py-2 text-sm font-medium text-gray-700 focus:outline-none">
           label->str
           <svg
             className="-mr-1 ml-2 h-5 w-5"
             xmlns="http://www.w3.org/2000/svg"
             viewBox="0 0 20 20"
             fill="currentColor">
             <path
               d="M5.293 7.293a1 1 0 011.414 0L10 10.586l3.293-3.293a1 1 0 111.414 1.414l-4 4a1 1 0 01-1.414 0l-4-4a1 1 0 010-1.414z"
             />
           </svg>
         </button>
       | Some(element) => element
       }}
    </div>
    <div
      style
      className={resolvePosition(position) ++ " absolute mt-2 w-56 rounded-md shadow-lg bg-white z-10"}>
      <div className="py-1" role="menu" onClick={_ => setVisible(_ => false)}>
        children
      </div>
    </div>
  </div>;
};
