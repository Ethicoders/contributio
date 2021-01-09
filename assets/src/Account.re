let str = React.string;

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let view =
    switch (url.path) {
    | ["account", "projects"] => <AccountProjects />
    | ["account", "import"] => <Importer />
    | _ => <Details />
    };

  <div>
    "Account"->str
    <ul>
      <li> <Anchor target="/account/"> "Details"->str </Anchor> </li>
      <li> <Anchor target="/account/projects"> "My Projects"->str </Anchor> </li>
      <li> <Anchor target="/account/import"> "Import"->str </Anchor> </li>
    </ul>
    
    <hr/>
    view
  </div>;
};
