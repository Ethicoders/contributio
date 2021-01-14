let str = React.string;

module GetProject = [%graphql
  {|
    query getProject($id: ID!) {
      project(id: $id) {
        name
        url
        description
        languages
        tasks {
          id
          name
          content
          experience
        }
      }
    }
|}
];

[@react.component]
let make = (~id) => {
  <div className="">
    {switch (GetProject.use({id: id})) {
     | {loading: true} => <span> "Loading project..."->str </span>
     | {error: Some(_error)} => "Error"->str
     | {called: false, data: Some(_), error: None, loading: false} =>
       "Do"->str
     | {called: true, data: Some({project}), loading: false} =>
       <>
         <Heading> {("Project " ++ project.name)->str} </Heading>
         " - "->str
         <a href={project.url} target="_blank"> "See on Origin"->str </a>
         <Icon name=Github />
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
                />
              )
            ->React.array}
         </div>
       </>
     }}
  </div>;
};
