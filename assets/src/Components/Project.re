let str = React.string;

[@react.component]
let make = (~id, ~name, ~description, ~url) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading>
    " - "->str
    description->str
    <Anchor target={"/projects/" ++ id}>
      <Button onClick={_ => ()}> "See more"->str </Button>
    </Anchor>
    <a href={url} target="_blank"> "See on Origin"->str </a>
    <Icon name=Github />
  </div>;
};
