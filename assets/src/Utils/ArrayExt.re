let removeFromArray = (item, values) => {
  let _ =
    Js.Array.removeCountInPlace(
      ~pos=Js.Array.indexOf(item, values),
      ~count=1,
      values,
    );
  values;
};
