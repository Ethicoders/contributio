let str = React.string;

module GetTasks = %graphql(`
    query getTasks {
      tasks {
        id
        name
        content
        experience
        difficulty
        time
        project {
          id
          name
        }
      }
    }
`)

@react.component
let make = () => {
  <div>
    <div className="hidden">
      <Heading size=Gigantic> {"Tasks"->str} </Heading>
    </div>
    {switch (GetTasks.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: None} => React.null
     | {data: Some({tasks}), loading: false, fetchMore: _} =>
      {Js.log("in")};
       <div className="grid grid-cols-4 gap-4 p-2">
         {switch (tasks) {
          | [] => "No tasks yet!"->str
          | values =>
            values
            ->Js.Array2.map(task => {
                let project: Types.projectData = {
                  id: task.project.id,
                  name: task.project.name,
                };

                <Task
                  key={task.id}
                  name={task.name}
                  id={task.id}
                  content={task.content}
                  experience={task.experience}
                  difficulty={task.difficulty}
                  time={task.time}
                  maybeProject={Some(project)}
                />;
              })
            ->React.array
          }}
       </div>
     }}
  </div>;
};
