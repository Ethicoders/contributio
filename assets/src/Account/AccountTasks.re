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
       my.projects
       ->Belt.Array.map(project => {
           switch (project.tasks) {
           | [||] => "No tasks yet!"->str
           | tasks =>
             <>
               <table className="min-w-full divide-y divide-gray-200">
                 <thead className="bg-gray-50">
                   <th
                     className="w-full px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                     <Checkbox label="Name" value="" onClick={_ => ()} />
                   </th>
                   <th
                     className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                     "Status"->str
                   </th>
                   <th
                     className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
                     "Actions"->str
                   </th>
                 </thead>
                 {tasks
                  ->Belt.Array.map(task => {
                      <tbody>
                        <td className="px-6 py-4 whitespace-nowrap">
                          <Checkbox
                            label={task.name}
                            value={task.id}
                            onClick=ignore
                          />
                        </td>
                        <td className="px-6 py-4 whitespace-nowrap">
                          <span
                            className="px-2 inline-flex text-xs leading-5 font-semibold rounded-full bg-green-100 text-green-800">
                            "Visible"->str
                          </span>
                        </td>
                        <td className="px-6 py-4 whitespace-nowrap">
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
                        </td>
                      </tbody>
                    })
                  ->React.array}
               </table>
             </>
           }
         })
       ->React.array
     | {data: None} => "No tasks yet!"->str
     }}
  </div>;
};
