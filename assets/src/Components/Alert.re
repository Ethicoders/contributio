let str = React.string;

[@react.component]
let make = (~children) => {
  <div className="border-l-2 border-fuchsia-600">
    children
  </div>
};