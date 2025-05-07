@react.component
let make = () => {
  let url = RescriptReactRouter.useUrl();

  let parsedQueryArgs = Url.parseQueryArgs(url.search);

  let view =
    switch (url.path) {
    | list{"account", ..._} => <Layout><Account /></Layout>
    | list{"projects", ..._} => <Layout><Projects /></Layout>
    | list{"tasks", ..._} => <Layout><Tasks/></Layout>
    | list{"allow"} => <Allow code=Js.Dict.unsafeGet(parsedQueryArgs, "code") />
    | _ => <Layout><Home /></Layout>
    };

  <div className="bg-base-100">
      view
  </div>;
};
