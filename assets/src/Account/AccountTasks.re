let str = React.string;

module GetUserTasks = [%graphql
  {|
    query getUserTasks {
      my {
        projects {
          id
          name
          tasks {
            id
            name
            content
            status
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
    <div className="hidden">
      <Heading size=Gigantic> "My Tasks"->str </Heading>
    </div>
    {switch (GetUserTasks.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({my}), loading: false} =>
       my.projects
       ->Belt.Array.map(project => {
           switch (project.tasks) {
           | [||] => React.null
           | tasks =>
             <>
               <table className="min-w-full divide-y">
                 <thead className="bg-dark">
                   <th
                     className="w-full px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
                     <Checkbox label="Name" value="" onClick={_ => ()} />
                   </th>
                   <th
                     className="px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
                     "Project"->str
                   </th>
                   <th
                     className="px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
                     "Status"->str
                   </th>
                   <th
                     className="px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
                     "Actions"->str
                   </th>
                 </thead>
                 <tbody
                   className="background-main text-current divide-y divide-main border-main">
                   {tasks
                    ->Belt.Array.map(task => {
                        <tr>
                          <td className="px-6 py-4 whitespace-nowrap">
                            <Checkbox label={task.name} value={task.id} />
                          </td>
                          <td className="px-6 py-4 whitespace-nowrap">
                            <Anchor
                              className="text-primary"
                              target={"/projects/" ++ project.id}>
                              project.name->str
                            </Anchor>
                          </td>
                          <td className="px-6 py-4 whitespace-nowrap">
                            {task.status === 0
                               ? <span
                                   className="px-2 inline-flex text-xs leading-5 font-semibold rounded-full bg-green-100 text-green-800">
                                   "Opened"->str
                                 </span>
                               : <span
                                   className="px-2 inline-flex text-xs leading-5 font-semibold rounded-full bg-default text-current">
                                   "Closed"->str
                                 </span>}
                          </td>
                          <td className="px-6 py-4 whitespace-nowrap">
                            <Anchor target={"/account/tasks/" ++ task.id}>
                              <Button type_=Primary>
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
                        </tr>
                      })
                    ->React.array}
                 </tbody>
               </table>
             </>
           }
         })
       ->React.array
     | {data: None} => "No tasks yet!"->str
     }}
  </div>;
};
