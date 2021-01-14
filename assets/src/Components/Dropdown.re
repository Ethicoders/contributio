let str = React.string;

[@react.component]
let make = (~children, ~label="", ~button=None) => {
  let (isVisible, setVisible) = React.useState(() => false);

  let handleToggleOverlay = _ => setVisible(_ => !isVisible);

  let style =
    isVisible
      ? ReactDOM.Style.make(~display="block", ())
      : ReactDOM.Style.make(~display="none", ());

  let handleClickOutside = _ => {
    setVisible(_ => false);
  };
  let divRef = ClickOutside.useClickOutside(handleClickOutside);

  <div ref={ReactDOMRe.Ref.domRef(divRef)}>
    <div
      className="relative inline-block text-left"
      onClick={_ => handleToggleOverlay()}>
      {switch (button) {
       | None =>
         <button
           type_="button"
           className="inline-flex justify-center w-full rounded-md border border-gray-300 shadow-sm px-4 py-2 bg-white text-sm font-medium text-gray-700 hover:bg-gray-50 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-100 focus:ring-indigo-500">
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
      className="origin-top-right absolute right-0 mt-2 w-56 rounded-md shadow-lg bg-white ring-1 ring-black ring-opacity-5">
      <div className="py-1" role="menu"> children </div>
    </div>
  </div>;
};
