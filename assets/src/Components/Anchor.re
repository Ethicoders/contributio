let str = React.string;

[@react.component]
let make = (~className="", ~target, ~children) => {
  <a
    href=target
    onClick={e => Router.goTo(e, target)}
    className>
    children
  </a>
};