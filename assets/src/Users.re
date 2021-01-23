let str = React.string;

module GetUsers = [%graphql
  {|
    query getUsers {
      users {
        name
        level
        currentExperience
        nextLevelExperience
      }
    }
|}
];

[@react.component]
let make = () => {
  <div>
    <Heading size=Big> "Users"->str </Heading>
    {switch (GetUsers.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({users}), loading: false} =>
       <div className="grid grid-cols-3 gap-4">
         {switch (users) {
          | [||] => "No users yet!"->str
          | values =>
            values
            ->Js.Array2.map(user =>
                <User
                  key={user.name}
                  name={user.name}
                  level={user.level}
                  currentExperience={user.currentExperience}
                  nextLevelExperience={user.nextLevelExperience}
                />
              )
            ->React.array
          }}
       </div>
     | {data: None} => <div />
     }}
  </div>;
};
