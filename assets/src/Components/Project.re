let str = React.string;

[@react.component]
let make = (~name, ~url) => {
  <div className="p-4 border-2 rounded-sm">
    name->str
    " - "->str
    <a href=url target="_blank"> "See"->str </a>
  </div>;
};
