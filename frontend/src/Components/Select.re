let str = React.string;

[@react.component]
let make = (~label, ~options) => {
  let (isVisible, setVisible) = React.useState(() => false);

  let handleToggleList = _ => setVisible(_ => !isVisible);

  let style =
    isVisible
      ? ReactDOM.Style.make(~display="block", ())
      : ReactDOM.Style.make(~display="none", ());
  <div>
    <label
      id="listbox-label" className="block text-sm font-medium text-gray-700">
      label->str
    </label>
    <div className="mt-1 relative">
      <button
        onClick=handleToggleList
        type_="button"
        className="relative w-full bg-white border border-gray-300 rounded-md shadow-sm pl-3 pr-10 py-2 text-left cursor-default focus:outline-none focus:ring-1 focus:ring-indigo-500 focus:border-indigo-500 sm:text-sm">
        <span className="flex items-center">
          <span className="ml-3 block truncate" /*{options[0] ? ->str}*/ />
        </span>
        <span
          className="ml-3 absolute inset-y-0 right-0 flex items-center pr-2 pointer-events-none">
          <svg
            className="h-5 w-5 text-gray-400"
            xmlns="http://www.w3.org/2000/svg"
            viewBox="0 0 20 20"
            fill="currentColor">
            <path
              d="M10 3a1 1 0 01.707.293l3 3a1 1 0 01-1.414 1.414L10 5.414 7.707 7.707a1 1 0 01-1.414-1.414l3-3A1 1 0 0110 3zm-3.707 9.293a1 1 0 011.414 0L10 14.586l2.293-2.293a1 1 0 011.414 1.414l-3 3a1 1 0 01-1.414 0l-3-3a1 1 0 010-1.414z"
            />
          </svg>
        </span>
      </button>
      <div
        className="absolute mt-1 w-full rounded-md bg-white shadow-lg" style>
        <ul
          role="listbox"
          className="max-h-56 rounded-md py-1 text-base ring-1 ring-black ring-opacity-5 overflow-auto focus:outline-none sm:text-sm">
          <li
            id="listbox-item-0"
            role="option"
            className="text-gray-900 cursor-default select-none relative py-2 pl-3 pr-9">
            {options
             ->Belt.Array.map(option =>
                 <div className="flex items-center" key=option>
                   <span
                     className="ml-3 block font-normal truncate" key=option>
                     option->str
                   </span>
                 </div>
               )
             ->React.array}
            <span
              className="absolute inset-y-0 right-0 flex items-center pr-4">
              <svg
                className="h-5 w-5"
                xmlns="http://www.w3.org/2000/svg"
                viewBox="0 0 20 20"
                fill="currentColor">
                <path
                  d="M16.707 5.293a1 1 0 010 1.414l-8 8a1 1 0 01-1.414 0l-4-4a1 1 0 011.414-1.414L8 12.586l7.293-7.293a1 1 0 011.414 0z"
                />
              </svg>
            </span>
          </li>
        </ul>
      </div>
    </div>
  </div>;
};
