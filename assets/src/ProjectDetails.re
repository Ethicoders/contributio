let str = React.string;

module GetProject = [%graphql
  {|
    query getProject($id: ID!) {
      project(id: $id) {
        name
        url
        description
        repoId
        languages
        tasks {
          id
          status
          name
          content
          experience
          difficulty
          time
        }
      }
    }
|}
];

exception Not_Found;

[@react.component]
let make = (~id) => {
  let (readme, setReadme) = React.useState(() => "");
  <div className="p-1 relative text-current">
    {switch (GetProject.use({id: id})) {
     | {loading: true} => <span> "Loading project..."->str </span>
     | {error: Some(_error)} => "Error"->str
     | {called: true, data: None, error: None, loading: false} => "Do"->str
     | {called: false, data: None, error: None, loading: false} => "Do"->str
     | {called: false, data: Some(_), error: None, loading: false} =>
       "Do"->str
     | {called: true, data: Some({project}), loading: false} =>
       let _ =
         Js.Promise.(
           Fetch.fetch(
             "https://raw.githubusercontent.com/"
             ++ project.repoId
             ++ "/README.md",
           )
           |> then_(response =>
                switch (Fetch.Response.status(response)) {
                | 200 => resolve(response)
                | _ => reject(Not_Found)
                }
              )
           |> then_(Fetch.Response.text)
           |> then_(text => setReadme(_ => text) |> resolve)
           |> catch(_ => resolve())
         );
       <>
         <Heading size=Huge> {("Project " ++ project.name)->str} </Heading>

         <div className="absolute right-2 top-2">
           <a href=project.url target="_blank">
             <Button> <Icon name=ExternalLink /> </Button>
           </a>
         </div>
         <div
           className="markdown text-current"
           dangerouslySetInnerHTML={"__html": Micromark.micromark(readme)}
         />
         <div className="">
           <Heading> "Tasks"->str </Heading>
           {project.tasks
            ->Belt.Array.map(task =>
                <div className="my-1">
                  <Task
                    key={task.id}
                    name={task.name}
                    id={task.id}
                    status={task.status}
                    content={task.content}
                    experience={task.experience}
                    difficulty={task.difficulty}
                    time={task.time}
                  />
                </div>
              )
            ->React.array}
         </div>
       </>;
     }}
  </div>;
};
