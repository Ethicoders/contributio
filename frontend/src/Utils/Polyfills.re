module DOMTokenList = {
  type t;
  [@bs.send] external contains : (t, string) => bool = "contains";
};