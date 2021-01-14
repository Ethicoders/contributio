let str = React.string;

module GetTask = [%graphql
  {|
    query getTask($id: ID!) {
      task(id: $id) {
        name
        content
        experience
      }
    }
|}
];

[@react.component]
let make = (~id) => {
  <div className="">
    {switch (GetTask.use({id: id})) {
     | {loading: true} => <span> "Loading task..."->str </span>
     | {error: Some(_error)} => "Error"->str
     | {called: false, data: Some(_), error: None, loading: false} =>
       "Do"->str
     | {called: true, data: Some({task}), loading: false} =>
       <>
         <Heading> {("Task " ++ task.name)->str} </Heading>
         " - "->str

         <Heading size=Small> "Experience: "->str </Heading>
         {(Js.Int.toString(task.experience) ++ " xp")->str}
         /* <a href={project.url} target="_blank"> "See on Origin"->str </a> */
         <Icon name=Github />
       </>
     }}
  </div>;
};
