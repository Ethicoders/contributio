let str = React.string;

type names =
  | Github
  | User;

[@react.component]
let make = (~name: names) => {
  <i
    className={
      switch (name) {
      | Github => "cib-github"
      | User => "cil-user"
      }
    }
  />;
};
