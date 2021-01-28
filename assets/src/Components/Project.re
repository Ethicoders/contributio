let str = React.string;

[@react.component]
let make = (~id, ~name, ~description, ~url) => {
  <div className="card px-4 pb-4 pt-2 border-2 rounded-md relative">
    <Anchor target={"/projects/" ++ id} className="text-primary">
      <Heading> name->str </Heading>
    </Anchor>
    <div className="absolute right-2 top-2">
      <a href=url target="_blank">
        <Button> <Icon name=ExternalLink /> </Button>
      </a>
    </div>
    description->str
  </div>;
};
