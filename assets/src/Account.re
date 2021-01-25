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
    <nav className="">
      <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="flex items-center justify-between h-16">
          <div className="flex items-center">
            <div className="ml-10 flex items-baseline space-x-4">
              <Anchor target="/account/"> "Details"->str </Anchor>
              <Anchor target="/account/projects"> "My Projects"->str </Anchor>
              <Anchor target="/account/tasks"> "My Tasks"->str </Anchor>
            </div>
          </div>
        </div>
      </div>
    </nav>
    <hr />
    view
  </div>;
};
