let str = React.string;

let difficultyToHumanReadable = difficulty => {
  switch (difficulty) {
  | 1
  | 2
  | 3 => "Easy"
  | 4
  | 5
  | 6 => "Medium"
  | 7
  | 8
  | 9
  | 10 => "Hard"
  | _ => ""
  };
};

let timeToHumanReadable = time => {
  switch (time) {
  | 1
  | 2
  | 3 => "Quick"
  | 4
  | 5
  | 6 => "Medium"
  | 7
  | 8
  | 9
  | 10 => "Long"
  | _ => ""
  };
};

let showProject = (maybeProject: option(Types.projectData)) =>
  switch (maybeProject) {
  | Some(project) =>
    <Anchor target={"/projects/" ++ project.id}> project.name->str </Anchor>
  | None => React.null
  };

[@react.component]
let make =
    (
      ~id,
      ~name,
      ~content,
      // ~url,
      ~experience,
      ~difficulty,
      ~time,
      ~maybeProject=None,
    ) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading>
    content->str
    {showProject(maybeProject)}
    <div>
      <span className="rounded-sm border-green-500 border-2 p-0.5 m-0.5">
        <Icon name=Lightbulb />
        {difficultyToHumanReadable(difficulty)->str}
      </span>
      <span className="rounded-sm border-green-500 border-2 p-0.5 m-0.5">
        <Icon name=Timer />
        {timeToHumanReadable(time)->str}
      </span>
    </div>
    <div>
      <Anchor target={"/tasks/" ++ id}>
        <Button type_=Primary> <Icon name=Eye /> "See more"->str </Button>
      </Anchor>
      <a href="" target="_blank">
        <Button> <Icon name=ExternalLink /> </Button>
      </a>
    </div>
    <hr />
    <div>
      <Heading size=Small> "Rewards: "->str </Heading>
      <Experience amount={Js.Int.toString(experience)} />
    </div>
  </div>;
};
