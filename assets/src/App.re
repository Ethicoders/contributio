let str = React.string;


[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let parsedQueryArgs = Url.parseQueryArgs(url.search);

  let view =
    switch (url.path) {
    | ["account", ..._] => <Layout><Account /></Layout>
    | ["projects"] => <Layout><Projects /></Layout>
    | ["allow"] => <Allow code=Js.Dict.unsafeGet(parsedQueryArgs, "code") />
    | _ => <Layout><Home /></Layout>
    };

  <div>
    <ApolloClient.React.ApolloProvider client=Client.instance>
      view
    </ApolloClient.React.ApolloProvider>
  </div>;
};
