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
        className="flex flex-col w-full md:w-64 text-current bg-gray-800 flex-shrink-0">
        <nav
          className="flex-grow md:block px-4 pb-4 md:pb-0 md:overflow-y-auto">
          <Anchor
            target="/account"
            className="block text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium my-1"
            activeClassNames="bg-gray-700 text-white">
            "Settings"->str
          </Anchor>
          <Anchor
            target="/account/projects"
            className="block text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium my-1"
            activeClassNames="bg-gray-700 text-white">
            "My Projects"->str
          </Anchor>
          <Anchor
            target="/account/tasks"
            className="block text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium my-1"
            activeClassNames="bg-gray-700 text-white">
            "My Tasks"->str
          </Anchor>
        </nav>
      </div>
      <div className="w-full p-2"> view </div>
    </div>
  </div>;
};
