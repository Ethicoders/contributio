type classNameItem =
  | Value(string)
  | Toggleable(string, bool);

module StrCmp =
  Belt.Id.MakeComparable({
    type t = classNameItem;
    let cmp = Pervasives.compare;
  });

module Helpers = {
  let isEnabled = item =>
    switch (item) {
    | Value(_) => true
    | Toggleable(_, enabled) => enabled
    };

  let getClassName = item =>
    switch (item) {
    | Value(className) => className
    | Toggleable(className, _) => className
    };

  let getClassNameFamily = item => switch item {
    | Value(className) => Js.String.split("-", className)[0]
    | Toggleable(className, _) => Js.String.split("-", className)[0]
  };
};

let create = (classNames: array(classNameItem)) => {
  Belt.MutableSet.fromArray(classNames, ~id=(module StrCmp));
};

let append = (set, value: classNameItem) => {
  set->Belt.MutableSet.add(value);
};

let merge = (set, classNames: array(classNameItem)) => {
  let copy = set->Belt.MutableSet.copy;
  copy->Belt.MutableSet.mergeMany(classNames);
  create(copy |> Belt.MutableSet.toArray);
};

let overrideMatchingClasses = (set, classNames: array(classNameItem)) => {
  let copy = set->Belt.MutableSet.copy;
  let classNamesFamilies = Js.Array.map((item) => Helpers.getClassNameFamily(item), classNames)
  merge(copy |> Belt.MutableSet.toArray |> Js.Array.filter(item => {
    !Js.Array.includes(Helpers.getClassNameFamily(item), classNamesFamilies)
  }) |> create, classNames)
};

let output = set =>
  set->Belt.MutableSet.toArray
  |> Js.Array.filter(Helpers.isEnabled)
  |> Js.Array.map(Helpers.getClassName)
  |> Js.Array.joinWith(" ");
