let str = React.string;

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let parsedQueryArgs = Url.parseQueryArgs(url.search);

  let view =
    switch (url.path) {
    | ["account"] => <Layout><Account /></Layout>
    | ["allow"] => <Allow code=Js.Dict.unsafeGet(parsedQueryArgs, "code") />
    | _ => <Layout><Home /></Layout>
    };

  <div>
    <ReasonApollo.Provider client=Client.instance>  
      view
    </ReasonApollo.Provider>
  </div>;
};
