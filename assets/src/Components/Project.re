let str = React.string;

[@react.component]
let make = (~id, ~name, ~description, ~url) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading>
    " - "->str
    description->str
    <div>
      <Anchor target={"/projects/" ++ id}>
        <Button type_=Primary> <Icon name=Eye /> "See more"->str </Button>
      </Anchor>
      <a href=url target="_blank">
        <Button> <Icon name=ExternalLink /> </Button>
      </a>
    </div>
  </div>;
};
