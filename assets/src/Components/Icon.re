let str = React.string;

type names =
  | Github
  | User;

type sizes =
  | Small
  | Medium
  | Large
  | ExtraLarge
  | EvenLarger(int);

[@react.component]
let make = (~onClick=None, ~name: names, ~size: sizes=Small) => {
  <i
    onClick={e =>
      switch (onClick) {
      | Some(callback) => callback(e)
      | None => ()
      }
    }
    className={
      (
        switch (name) {
        | Github => "cib-github"
        | User => "cil-user"
        }
      )
      ++ " "
      ++ (
        switch (size) {
        | Small => "text-sm"
        | Medium => "text-base"
        | Large => "text-lg"
        | ExtraLarge => "text-xl"
        | EvenLarger(modifier) =>
          "text-" ++ Js.Int.toString(modifier) ++ "xl"
        }
      )
    }
  />;
};
