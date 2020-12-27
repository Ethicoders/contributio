let str = React.string;

let url =
  Url.buildFrom(
    "https://github.com/",
    ["login", "oauth", "authorize"],
    {
      "client_id": Env.githubClientID,
      "redirect_uri": Js.Global.encodeURI(Env.allowEndpoint),
    },
  );
let handleClick = _ => Window.open_(url, "GitHub");

module GetUserProjects = [%graphql
  {|
    query getUserProjects {
      my {
        email
        projects {
          name
        }
      }
    }
|}
];

module GetUserProjectsQuery = ReasonApollo.CreateQuery(GetUserProjects);

[@react.component]
let make = () => {
  <div>
    "Account"->str
    <button
      className="inline-flex items-center px-4 py-2 border border-gray-300 rounded-md shadow-sm text-sm font-medium text-gray-700 bg-white hover:bg-gray-50 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-indigo-500"
      onClick=handleClick>
      "Authorize GitHub App"->str
    </button>
    <GetUserProjectsQuery>
      ...{({result, fetchMore}) =>
        <div>
          <h1> {"My Projects: "->str} </h1>
          {switch (result) {
           | Error(e) =>
             Js.log(e);
             "Something Went Wrong"->str;
           | Loading => "Loading"->str
           | Data(response) => <div></div>
           }}
        </div>
      }
    </GetUserProjectsQuery>
  </div>;
};
