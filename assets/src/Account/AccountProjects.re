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
    <h1> "My Projects"->str </h1>
    <Anchor target="/account/import/projects">
      "Import Repositories"->str
    </Anchor>
    {switch (GetUserProjects.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({my}), loading: false} =>
       <div className="grid grid-cols-3 gap-4">
         {switch (my.projects) {
          | [||] => "No projects yet!"->str
          | values =>
            <div>
              <div className="flex items-stretch">
                <div className="flex-grow">
                  <Checkbox label="Name" value="" onClick={_ => ()} />
                </div>
                <div> "Actions"->str </div>
              </div>
              {values
               ->Belt.Array.map(project => {
                   let castedProject: Types.projectData = {
                     id: project.id,
                     name: project.name,
                   };
                   <div className="flex items-stretch">
                     <div className="flex-grow">
                       <Checkbox
                         label={project.name}
                         value={project.id}
                         onClick={_ => ()}
                       />
                     </div>
                     <div>
                       <Anchor
                         target={"/account/projects/" ++ castedProject.id}>
                         <Button type_=Primary onClick=ignore>
                           <Icon name=Pencil />
                         </Button>
                       </Anchor>
                       <Anchor
                         target={
                           "/account/import/projects/"
                           ++ castedProject.id
                           ++ "/tasks"
                         }>
                         <Button onClick=ignore> <Icon name=Import /> </Button>
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
                     </div>
                   </div>;
                 })
               ->React.array}
            </div>
          }}
       </div>
     | {data: None} => "No projects yet!"->str
     }}
  </div>;
};
