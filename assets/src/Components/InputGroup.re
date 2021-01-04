let str = React.string;

[@react.component]
let make = (~label) => {
  <div>
    <label className="block text-sm font-medium text-gray-700">
    label->str
    </label>
    <div className="mt-1 relative rounded-md shadow-sm">
      <div
        className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
        <span
          className="text-gray-500 sm:text-sm"
          /* $ */
        />
      </div>
      <input
        type_="text"
        className="focus:ring-indigo-500 focus:border-indigo-500 block w-full pl-7 pr-12 sm:text-sm border-gray-300 rounded-md"
      />
    </div>
  </div>;
};
