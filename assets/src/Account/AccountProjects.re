let str = React.string;

module GetUserProjects = [%graphql
  {|
    query getUserProjects {
      my {
        projects {
          id
          name
          url
          description
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
      <Heading size=Gigantic> "My Projects"->str </Heading>
    </div>
    <Anchor target="/account/import/projects">
      "Import Repositories"->str
    </Anchor>
    {switch (GetUserProjects.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({my}), loading: false} =>
       switch (my.projects) {
       | [||] => "No projects yet!"->str
       | values =>
         <table className="min-w-full divide-y divide-main text-current">
           <thead className="bg-gray-800">
             <th
               className="w-full px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
               <Checkbox label="Name" value="" />
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
           <tbody className="background-main text-current divide-y divide-main border-main">
             {values
              ->Belt.Array.map(project => {
                  let castedProject: Types.projectData = {
                    id: project.id,
                    name: project.name,
                  };
                  <tr>
                    <td className="px-6 py-4 whitespace-nowrap">
                      <Checkbox
                        label={project.name}
                        value={project.id}
                        onClick={_ => ()}
                      />
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap">
                      <span
                        className="px-2 inline-flex text-xs leading-5 font-semibold rounded-full bg-green-100 text-green-800">
                        "Visible"->str
                      </span>
                    </td>
                    <td className="px-6 py-4 whitespace-nowrap">
                      <Anchor
                        target={"/account/projects/" ++ castedProject.id}>
                        <Button type_=Primary> <Icon name=Pencil /> </Button>
                      </Anchor>
                      <Anchor
                        target={
                          "/account/import/projects/"
                          ++ castedProject.id
                          ++ "/tasks"
                        }>
                        <Button> <Icon name=Import /> </Button>
                      </Anchor>
                      <Button
                        type_=Danger
                        onClick={_ =>
                          DeleteProject.trigger(castedProject.id, _ =>
                            add({title: "Project deleted."})
                          )
                        }>
                        <Icon name=Trash />
                      </Button>
                    </td>
                  </tr>;
                })
              ->React.array}
           </tbody>
         </table>
       }
     | {data: None} => "No projects yet!"->str
     }}
  </div>;
};
