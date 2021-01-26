let str = React.string;

type names =
  | ExternalLink
  | Eye
  | Import
  | Github
  | Gitlab
  | Lightbulb
  | Link
  | Pencil
  | Timer
  | Trash
  | User;

type sizes =
  | Small
  | Medium
  | Large
  | ExtraLarge
  | EvenLarger(int);

type colors =
  | Default
  | Black
  | White
  | Red
  | Green
  | Blue
  | Custom(string);

[@react.component]
let make = (~name: names, ~size: sizes=Small, ~color: colors=Default) => {
  <i
    className={
      (
        switch (name) {
        | ExternalLink => "cil-external-link"
        | Eye => "cil-eye"
        | Import => "cil-arrow-thick-from-top"
        | Github => "cib-github"
        | Gitlab => "cib-gitlab"
        | Lightbulb => "cil-lightbulb"
        | Link => "cil-link"
        | Pencil => "cil-pencil"
        | Timer => "cil-av-timer"
        | Trash => "cil-trash"
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
      ++ " "
      ++ (
        switch (color) {
        | Default => "text-current"
        | Black => "text-black"
        | White => "text-white"
        | Red => "text-red-800"
        | Green => "text-green-800"
        | Blue => "text-blue-800"
        | Custom(modifier) => "text-" ++ modifier
        }
      )
    }
  />;
};
