let str = React.string;

[@react.component]
let make = (~id, ~name, ~content, ~experience) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading>
    content->str
    // project.name->str
    // " - "->str
    // <a href=url target="_blank"> "See"->str </a>
    <Anchor target={"/tasks/" ++ id}>
      <Button onClick={_ => ()}> "See more"->str </Button>
    </Anchor>
    <div>
      <Heading size=Small> "Experience: "->str </Heading>
      {(Js.Int.toString(experience) ++ " xp")->str}
      <Heading size=Small> "Rewards: "->str </Heading>
    </div>
  </div>;
};
