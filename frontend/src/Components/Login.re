open! ReasonApolloTypes;

let str = React.string;

module Auth = [%graphql
  {|
  mutation Auth ($email: String!, $password: String!) {
    auth(email: $email, password: $password) {
      token
      user {
        id
      }
    }
  }
|}
];

module AuthMutation = ReasonApollo.CreateMutation(Auth);

[@react.component]
let make = () => {

  let (state, send) = React.useState(() => Js.Dict.fromList([("email", ""), ("password", "")]));

  let onChange = (e: ReactEvent.Form.t): unit => {
    let name = e->ReactEvent.Form.target##name;
    let value = e->ReactEvent.Form.target##value;
    Js.Dict.set(state, name, value);
    send(state => state);
  };

  <div className="flex items-center justify-center py-12 px-4 sm:px-6 lg:px-8">
  
    <AuthMutation>
      {(mutation, _) => {
        let handleSubmit = evt => {
          ReactEvent.Form.preventDefault(evt);

          let authMutation = Auth.make(~email=Js.Dict.unsafeGet(state, "email"), ~password=Js.Dict.unsafeGet(state, "password"), ());

          let result = mutation(~variables=authMutation##variables, (), );

          result
          |> Js.Promise.then_(value => {
              
            {switch (value) {
              | Data(stuff) => Js.log(stuff)
              | Errors(_) => Js.log("ERROR")
              | EmptyResponse => Js.log("Empty")
              }}
              Js.Promise.resolve(value)
            }) |> ignore;
        };

        <div className="max-w-md w-full space-y-8">

          <form
            onSubmit=handleSubmit
            className="mt-8 space-y-6"
          >
            <input type_="hidden" name="remember" value="true" />
            <div className="rounded-md shadow-sm -space-y-px">
              <div>
                <label className="sr-only"> "Email address"->str </label>
                <input
                  id="email-address"
                  name="email"
                  type_="email"
                  autoComplete="email"
                  required=true
                  className="appearance-none rounded-none relative block w-full px-3 py-2 border border-gray-300 placeholder-gray-500 text-gray-900 rounded-t-md focus:outline-none focus:ring-indigo-500 focus:border-indigo-500 focus:z-10 sm:text-sm"
                  placeholder="Email address"
                  onChange
                />
              </div>
              <div>
                <label className="sr-only"> "Password"->str </label>
                <input
                  id="password"
                  name="password"
                  type_="password"
                  autoComplete="current-password"
                  required=true
                  className="appearance-none rounded-none relative block w-full px-3 py-2 border border-gray-300 placeholder-gray-500 text-gray-900 rounded-b-md focus:outline-none focus:ring-indigo-500 focus:border-indigo-500 focus:z-10 sm:text-sm"
                  placeholder="Password"
                  onChange
                />
              </div>
            </div>
            <div className="flex items-center justify-between">
              <div className="flex items-center">
                <input
                  id="remember_me"
                  name="remember_me"
                  type_="checkbox"
                  className="h-4 w-4 text-indigo-600 focus:ring-indigo-500 border-gray-300 rounded"
                />
                <label className="ml-2 block text-sm text-gray-900">
                  "Remember me"->str
                </label>
              </div>
              <div className="text-sm">
                <a
                  href="#"
                  className="font-medium text-indigo-600 hover:text-indigo-500">
                  "Forgot your password?"->str
                </a>
              </div>
            </div>
            <div>
            
              <button
                type_="submit"
                className="group relative w-full flex justify-center py-2 px-4 border border-transparent text-sm font-medium rounded-md text-white bg-indigo-600 hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-indigo-500">
                <span
                  className="absolute left-0 inset-y-0 flex items-center pl-3"
                  // <svg className="h-5 w-5 text-indigo-500 group-hover:text-indigo-400" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20" fill="currentColor" aria-hidden="true">
                  //   <path fill-rule="evenodd" d="M5 9V7a5 5 0 0110 0v2a2 2 0 012 2v5a2 2 0 01-2 2H5a2 2 0 01-2-2v-5a2 2 0 012-2zm8-2v2H7V7a3 3 0 016 0z" clip-rule="evenodd" />
                  // </svg>
                />
                "Sign in"->str
              </button>
            </div>
          </form>
        </div>
      }}
    </AuthMutation>
  </div>;
};
