let str = React.string;

[@react.component]
let make = (~label, ~iconName, ~onChange=ignore) => {
  <div>
    <label className="block text-sm font-medium text-current hidden">
      label->str
    </label>
    <div className="mt-1 relative rounded-md shadow-sm">
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
        className="text-current border bg-transparent block w-full pl-7 pr-12 sm:text-sm rounded-md py-2"
      />
    </div>
  </div>;
};
