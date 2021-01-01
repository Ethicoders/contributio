let str = React.string;

[@react.component]
let make = (~name, ~url) => {
  <div>
    name->str
    " - "->str
    <a href=url target="_blank"> "See"->str </a>
  </div>;
};
