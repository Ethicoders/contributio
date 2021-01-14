let str = React.string;


[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let parsedQueryArgs = Url.parseQueryArgs(url.search);

  let view =
    switch (url.path) {
    | ["account", ..._] when Session.isConnected() => <Layout><Account /></Layout>
    | ["operation"] => <Layout><Operation /></Layout>
    | ["projects"] => <Layout><Projects /></Layout>
    | ["projects", id] => <Layout><ProjectDetails id /></Layout>
    | ["tasks"] => <Layout><Tasks /></Layout>
    | ["tasks", id] => <Layout><TaskDetails id /></Layout>
    | ["users"] => <Layout><Users /></Layout>
    | ["allow"] => <Allow code=Js.Dict.unsafeGet(parsedQueryArgs, "code") />
    | _ => <Layout><Home /></Layout>
    };

  <div>
    <ApolloClient.React.ApolloProvider client=Client.instance>
      view
    </ApolloClient.React.ApolloProvider>
  </div>;
};
