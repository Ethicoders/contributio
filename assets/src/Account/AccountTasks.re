let str = React.string;

module GetUserTasks = [%graphql
  {|
    query getUserTasks {
      my {
        projects {
          tasks {
            id
            name
            content
          }
        }
      }
    }
|}
];

[@react.component]
let make = () => {
  let (_, add, _) = Toaster.useToast();
  <div>
    <h1> "My Tasks"->str </h1>
    {switch (GetUserTasks.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({my}), loading: false} =>
       <div>
         {my.projects
          ->Belt.Array.map(project => {
              switch (project.tasks) {
              | [||] => "No tasks yet!"->str
              | tasks =>
                <>
                  <div className="flex items-stretch">
                    <div className="flex-grow">
                      <Checkbox label="Name" value="" onClick={_ => ()} />
                    </div>
                    <div> "Actions"->str </div>
                  </div>
                  {tasks
                   ->Belt.Array.map(task => {
                       <div className="flex items-stretch">
                         <div className="flex-grow">
                           <Checkbox
                             label={task.name}
                             value={task.id}
                             onClick=ignore
                           />
                         </div>
                         <div>
                           <Anchor target={"/account/tasks/" ++ task.id}>
                             <Button type_=Primary onClick=ignore>
                               <Icon name=Pencil />
                             </Button>
                           </Anchor>
                           <Button
                             type_=Danger
                             onClick={_ =>
                               DeleteTask.trigger(task.id, _ =>
                                 add({title: "Task deleted."})
                               )
                             }>
                             <Icon name=Trash />
                           </Button>
                         </div>
                       </div>
                     })
                   ->React.array}
                </>
              }
            })
          ->React.array}
       </div>
     | {data: None} => "No tasks yet!"->str
     }}
  </div>;
};
