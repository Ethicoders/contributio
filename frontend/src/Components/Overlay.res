let str = React.string

@react.component
let make = (~children: React.element, ~footer=None, ~isVisible=false, ~onClose) => {
  let activeClass = if isVisible {
    "block"
  } else {
    "hidden"
  }
  let ref = React.useRef(Nullable.null)

  <div
    className={`fixed z-10 inset-0 overflow-y-auto ${activeClass}`}
    onClick={(e: ReactEvent.Mouse.t) => {
      let target = e->JsxEvent.Mouse.target->DOM.targetToDOM

      switch ref.current->Js.Nullable.toOption {
      | Some(el) if el == target => onClose()
      | _ => ()
      }
    }}>
    <div
      className="flex items-end justify-center min-h-screen pt-4 px-4 pb-20 text-center sm:block sm:p-0">
      <div className="fixed inset-0 transition-opacity">
        <div className="absolute inset-0 bg-gray-500/50" ref={ReactDOM.Ref.domRef(ref)}>
          <div
            className="inline-block align-bottom rounded-lg text-left overflow-hidden shadow-xl transform transition-all sm:my-8 sm:align-middle sm:max-w-lg sm:w-full"
            role="dialog">
            <div className="bg-base-100 px-4 pt-5 pb-4 sm:p-6 sm:pb-4">
              <div className="sm:flex sm:items-start">
                <div className="w-full text-center sm:mt-0 sm:text-left">
                  // <h3 className="text-lg leading-6 font-medium text-gray-900" id="modal-headline">
                  //   title
                  // </h3>
                  <div className="mt-2"> children </div>
                </div>
              </div>
            </div>
            {switch footer {
            | Some(elmt) =>
              <div className="bg-gray-50 px-4 py-3 sm:px-6 sm:flex sm:flex-row-reverse"> elmt </div>
            | None => React.null
            }}
          </div>
        </div>
      </div>
      // <span className="hidden sm:inline-block sm:align-middle sm:h-screen">&#8203;</span>
    </div>
  </div>
}
