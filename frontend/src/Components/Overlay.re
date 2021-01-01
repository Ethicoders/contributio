open Polyfills;

let str = React.string;

type elmt = ReasonReact.reactElement;

[@react.component]
let make =
    (
      ~children: ReasonReact.reactElement,
      ~footer=None,
      ~title,
      ~isVisible=false,
      ~onClose,
    ) => {
  let style =
    isVisible
      ? ReactDOM.Style.make(~display="block", ())
      : ReactDOM.Style.make(~display="none", ());
  <div
    className="fixed z-10 inset-0 overflow-y-auto"
    style
    onClick={(e: ReactEvent.Mouse.t) =>
      if (e->ReactEvent.Mouse.target##classList
          ->DOMTokenList.contains("absolute")) {
        onClose();
      }
    }>
    <div
      className="flex items-end justify-center min-h-screen pt-4 px-4 pb-20 text-center sm:block sm:p-0">
      <div className="fixed inset-0 transition-opacity">
        <div className="absolute inset-0 bg-gray-500 opacity-75" />
      </div>
      // <span className="hidden sm:inline-block sm:align-middle sm:h-screen">&#8203;</span>
      <div
        className="inline-block align-bottom bg-white rounded-lg text-left overflow-hidden shadow-xl transform transition-all sm:my-8 sm:align-middle sm:max-w-lg sm:w-full"
        role="dialog">
        <div className="bg-white px-4 pt-5 pb-4 sm:p-6 sm:pb-4">
          <div className="sm:flex sm:items-start">
            <div className="w-full text-center sm:mt-0 sm:text-left">
              <h3
                className="text-lg leading-6 font-medium text-gray-900"
                id="modal-headline">
                title
              </h3>
              <div className="mt-2"> children </div>
            </div>
          </div>
        </div>
        {switch (footer) {
         | Some(elmt) =>
           <div
             className="bg-gray-50 px-4 py-3 sm:px-6 sm:flex sm:flex-row-reverse">
             elmt
           </div>
         | None => React.null
         }}
      </div>
    </div>
  </div>;
};
