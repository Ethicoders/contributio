let str = React.string;

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let view =
    switch (url.path) {
    | ["account"] => <Account />
    | _ => <Layout><Home /></Layout>
    };

  <div>
    <ReasonApollo.Provider client=Client.instance>  
      view
    </ReasonApollo.Provider>
  </div>;
};
