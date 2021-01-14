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

type entryType =
  | SignIn
  | SignUp;

[@react.component]
let make = () => {
  let (state, send) =
    React.useState(() =>
      Js.Dict.fromList([("email", ""), ("password", "")])
    );
  let (mutate, result) = Auth.use();

  let (entryType, setEntryType) = React.useState(() => SignIn);

  let onChange = (e: ReactEvent.Form.t): unit => {
    let name = e->ReactEvent.Form.target##name;
    let value = e->ReactEvent.Form.target##value;
    Js.Dict.set(state, name, value);
    send(state => state);
  };

  let handleSubmit = evt => {
    ReactEvent.Form.preventDefault(evt);

    mutate(
      ~update=
        (_, {data}) =>
          switch (data) {
          | Some(_) => ()
          | None => ()
          },
      {
        email: Js.Dict.unsafeGet(state, "email"),
        password: Js.Dict.unsafeGet(state, "password"),
      },
    )
    ->ignore;

    switch (result) {
    | {called: false} => Js.log("Not called... ")
    | {loading: true} => Js.log("Loading...")
    | {data: Some(_), error: None} => Js.log("Done.")
    | {error} =>
      Js.log(
        "Error loading data"
        ++ {
          switch (error) {
          | Some(error) => ": " ++ error.message
          | None => "?"
          };
        },
      )
    };
  };

  let baseClassNames =
    ClassName.create([|
      Value("flex-1"),
      Value("bg-gray-200"),
      Value("p-4"),
      Value("cursor-pointer")
    |]);

  let classNamesSignIn =
    ClassName.merge(
      baseClassNames,
      [|Toggleable("active", entryType == SignIn)|],
    );
  let classNamesSignUp =
    ClassName.merge(
      baseClassNames,
      [|Toggleable("active", entryType == SignUp), Value("text-right")|],
    );
  <>
    <ul className="flex">
      <li className={ClassName.output(classNamesSignIn)} onClick={_ => setEntryType(_ => SignIn)}>
        <Heading size=Small> "Sign In"->str </Heading>
      </li>
      <li className={ClassName.output(classNamesSignUp)} onClick={_ => setEntryType(_ => SignUp)}>
        <Heading size=Small> "Sign Up"->str </Heading>
      </li>
    </ul>
    <div
      className="flex items-center justify-center py-12 px-4 sm:px-6 lg:px-8">
      <div className="max-w-md w-full space-y-8">
        <form onSubmit=handleSubmit className="mt-8 space-y-6">
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
          // <div className="flex items-center justify-between">
          //   <div className="flex items-center">
          //     <input
          //       id="remember_me"
          //       name="remember_me"
          //       type_="checkbox"
          //       className="h-4 w-4 text-indigo-600 focus:ring-indigo-500 border-gray-300 rounded"
          //     />
          //     <label className="ml-2 block text-sm text-gray-900">
          //       "Remember me"->str
          //     </label>
          //   </div>
          //   <div className="text-sm">
          //     <a
          //       href="#"
          //       className="font-medium text-indigo-600 hover:text-indigo-500">
          //       "Forgot your password?"->str
          //     </a>
          //   </div>
          // </div>
          <div>
            <button
              type_="submit"
              className="group relative w-full flex justify-center py-2 px-4 border border-transparent text-sm font-medium rounded-md text-white bg-green-500 hover:bg-green-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-indigo-500">
              <span
                className="absolute left-0 inset-y-0 flex items-center pl-3"
              />
              {switch (entryType) {
               | SignIn => "Sign In"->str
               | SignUp => "Sign Up"->str
               }}
            </button>
          </div>
        </form>
      </div>
    </div>
  </>;
};
