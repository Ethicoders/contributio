let str = React.string;

type names =
  | Github;

[@react.component]
let make = (~name: names) => {
  <i
    className={
      switch (name) {
      | Github => "cib-github"
      }
    }
  />;
};
