let str = React.string;

module GetTask = [%graphql
  {|
    query getTask($id: ID!) {
      task(id: $id) {
        name
        content
        experience
        project {
          id
          name
        }
      }
    }
|}
];

[@react.component]
let make = (~id) => {
  <div className="relative p-1 text-current">
    {switch (GetTask.use({id: id})) {
     | {loading: true} => <span> "Loading task..."->str </span>
     | {error: Some(_error)} => "Error"->str
     | {called: true, data: None, error: None, loading: false} => "Do"->str
     | {called: false, data: None, error: None, loading: false} => "Do"->str
     | {called: false, data: Some(_), error: None, loading: false} =>
       "Do"->str
     | {called: true, data: Some({task}), loading: false} =>
       <>
         <Heading size=Huge> {("Task " ++ task.name)->str} </Heading>
         <div className="text-xs mt-1">
           <Anchor
             className="text-primary" target={"/projects/" ++ task.project.id}>
             task.project.name->str
           </Anchor>
         </div>
         <div className="absolute right-2 top-2">
           <a href="" target="_blank">
             <Button> <Icon name=ExternalLink /> </Button>
           </a>
         </div>
         <div
           className="markdown text-current my-3"
           dangerouslySetInnerHTML={"__html": Micromark.render(task.content)}
         />
         <hr className="my-2" />
         <div> <Experience amount={Js.Int.toString(task.experience)} /> </div>
       </>
     }}
  </div>;
};
