let str = React.string;

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let view =
    switch (url.path) {
    | ["account", "projects"] => <AccountProjects />
    | ["account", "import", "projects"] => <ImportProjects />
    | ["account", "tasks"] => <AccountTasks />
    | ["account", "import", "projects", projectId, "tasks"] =>
      <ImportTasks projectId />
    | _ => <Details />
    };

  <div>
    <div className="md:flex flex-col md:flex-row md:min-h-screen w-full">
      <div
        className="flex flex-col w-full md:w-64 text-current bg-dark flex-shrink-0">
        <nav
          className="flex-grow md:block px-4 pb-4 md:pb-0 md:overflow-y-auto">
          <Anchor
            target="/account"
            className="block my-1 text-current bg-dark hover:filter-lighten-50 px-3 py-2 rounded-md text-sm font-medium"
            activeClassNames="filter-lighten-75">
            "Settings"->str
          </Anchor>
          <Anchor
            target="/account/projects"
            className="block my-1 text-current bg-dark hover:filter-lighten-50 px-3 py-2 rounded-md text-sm font-medium"
            activeClassNames="filter-lighten-75">
            "My Projects"->str
          </Anchor>
          <Anchor
            target="/account/tasks"
            className="block my-1 text-current bg-dark hover:filter-lighten-50 px-3 py-2 rounded-md text-sm font-medium"
            activeClassNames="filter-lighten-75">
            "My Tasks"->str
          </Anchor>
        </nav>
      </div>
      <div className="w-full p-2"> view </div>
    </div>
  </div>;
};
