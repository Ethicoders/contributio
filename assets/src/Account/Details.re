let str = React.string;

module GetUserLinkedOrigins = [%graphql
  {|
    query getUserLinkedOrigins {
      my {
        usersOrigins {
          origin {
            url
          }
        }
      }
    }
|}
];

module GetOrigins = [%graphql
  {|
    query origins {
      origins {
        id
        url
      }
    }
|}
];

let url =
  Url.buildFrom(
    "https://github.com/",
    ["login", "oauth", "authorize"],
    {
      "client_id": Env.githubClientID,
      "redirect_uri": Js.Global.encodeURI(Env.allowEndpoint),
    },
  );

[@react.component]
let make = () => {
  let (_, add, _) = Toaster.useToast();

  let queryResult = GetUserLinkedOrigins.use();

  let handleClick = _ => {
    Window.onMessage("link:success", _ => {
      let _ = queryResult.refetch();
      ();
    });
    Window.open_(url, "GitHub");
  };

  let linkedOrigins =
    switch (queryResult) {
    | {loading: true} => [||]
    | {data: None} => [||]
    | {data: Some({my}), loading: false} =>
      Js.Array.map(
        (
          origin: GetUserLinkedOrigins.GetUserLinkedOrigins_inner.t_my_usersOrigins,
        ) =>
          origin.origin.url,
        my.usersOrigins,
      )
    };

  <div>
    <Alert>
      "You will need an account on a task's Origin to be able fulfil a contribution and get rewards. "
      ->str
    </Alert>
    <div>
      {switch (GetOrigins.use()) {
       | {loading: true} => "Loading..."->React.string
       | {data: Some({origins}), loading: false} =>
         switch (origins) {
         | [||] => "No linked origins yet!"->str
         | values =>
           <table className="min-w-full divide-y divide-main text-current">
             <thead className="bg-dark">
               <th
                 className="w-full px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
                 "URI"->str
               </th>
               <th
                 className="px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
                 "Family"->str
               </th>
               <th
                 className="px-6 py-3 text-left text-xs font-medium text-current uppercase tracking-wider">
                 "Actions"->str
               </th>
             </thead>
             <tbody
               className="background-main text-current divide-y divide-main border-main">
               {values
                ->Belt.Array.map(origin => {
                    <tr>
                      <td className="px-6 py-4 whitespace-nowrap">
                        origin.url->str
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap">
                        //  origin.family->str
                         "GitHub"->str </td>
                      <td className="px-6 py-4 whitespace-nowrap">
                        {if (Js.Array.includes(origin.url, linkedOrigins)) {
                           <Button
                             type_=Danger
                             onClick={_ =>
                               RevokeLinkedAccount.trigger(
                                 origin.id,
                                 _ => {
                                   add({title: "Origin link removed."});
                                   let _ = queryResult.refetch();
                                   ();
                                 },
                               )
                             }>
                             <Icon name=LinkBroken />
                           </Button>;
                         } else {
                           <Button type_=Primary onClick=handleClick>
                             <Icon name=Link />
                           </Button>;
                         }}
                      </td>
                    </tr>
                  })
                ->React.array}
             </tbody>
           </table>
         }
       | {data: None} => "No linked origins yet!"->str
       }}
    </div>
  </div>;
};
