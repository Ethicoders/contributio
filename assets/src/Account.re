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
    <li> <a href="/account/"> "Details"->str </a> </li>
    <li> <a href="/account/projects"> "My Projects"->str </a> </li>
    </ul>
    
    <hr/>
    view
  </div>;
};
