let str = React.string;

[@react.component]
let make = (~children) => {
  <div className="bg-green-200 border-l-4 border-green-600 text-green-600 p-4">
    children
  </div>
};