let str = React.string;

[@react.component]
let make = (~value, ~label, ~onClick=ignore) => {
  <label className="cursor-pointer flex justify-start items-start">
    <div
      className="hover:glow-default border-2 border-default rounded w-6 h-6 flex flex-shrink-0 justify-center items-center mr-2 focus-within:border-primary-500">
      <input
        onClick={_ => onClick(value)}
        className="opacity-0 absolute cursor-pointer"
        type_="checkbox"
        value
      />
      <svg
        className="fill-primary hidden w-4 h-4 text-green-500 pointer-events-none"
        viewBox="0 0 20 20">
        <path d="M0 11l2-2 5 5L18 3l2 2L7 18z" />
      </svg>
    </div>
    <div className="select-none"> label->str </div>
  </label>;
};
