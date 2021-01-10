let str = React.string;

[@react.component]
let make = (~name, ~url) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading>name->str</Heading>
    " - "->str
    <a href=url target="_blank"> "See"->str </a>
  </div>;
};
