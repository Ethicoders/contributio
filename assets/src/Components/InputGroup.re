let str = React.string;

[@react.component]
let make = (~label, ~iconName, ~onChange=ignore) => {
  <div className="border-2 border-default bg-default bg-opacity-10 rounded-md hover:glow-default">
    <label className="block text-sm font-medium text-current hidden">
      label->str
    </label>
    <div className="relative rounded-md shadow-sm">
      <div
        className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
        <span className="text-gray-500 sm:text-sm">
          <Icon name=iconName />
        </span>
      </div>
      <input
        onChange={(e: ReactEvent.Form.t): unit => {
          let value = e->ReactEvent.Form.target##value;
          onChange(value);
        }}
        placeholder=label
        type_="text"
        className="bg-transparent text-current block w-full pl-7 pr-12 sm:text-sm py-2 pl-9 outline-none "
      />
    </div>
  </div>;
};
