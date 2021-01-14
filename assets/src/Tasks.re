let str = React.string;

module GetTasks = [%graphql
  {|
    query getTasks {
      tasks {
        id
        name
        content
        experience
        project {
          name
        }
      }
    }
|}
];

[@react.component]
let make = () => {
  <div>
    <Heading size=Big> "Tasks"->str </Heading>
    {switch (GetTasks.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({tasks}), loading: false} =>
       <div className="grid grid-cols-3 gap-4">

           {tasks
            ->Js.Array2.map(task =>
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
         //  {switch (tasks) {
         //   | Some(items) =>
         //     items
         //     ->Js.Array2.map(task =>
         //         <Task
         //           key={task.name}
         //           name={task.name}
         //           content={task.content}
         //           // url={task.url}
         //           project={task.project}
         //         />
         //       )
         //     ->React.array
         //   | None => "No tasks yet!"->str
         //   }}
     | {data: None} => <div />
     }}
  </div>;
};
