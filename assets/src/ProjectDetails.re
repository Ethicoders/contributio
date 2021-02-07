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
  <div className="">
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
         <Heading> {("Project " ++ project.name)->str} </Heading>
         " - "->str
         <a href={project.url} target="_blank"> "See on Origin"->str </a>
         <Icon name=Github />
         <div
           className="markdown text-current"
           dangerouslySetInnerHTML={"__html": Micromark.micromark(readme)}
         />
         <div>
           "Tasks"->str
           {project.tasks
            ->Belt.Array.map(task =>
                <Task
                  key={task.id}
                  name={task.name}
                  id={task.id}
                  content={task.content}
                  experience={task.experience}
                  difficulty={task.difficulty}
                  time={task.time}
                />
              )
            ->React.array}
         </div>
       </>;
     }}
  </div>;
};
