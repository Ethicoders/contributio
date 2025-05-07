@val @scope(("window", "someLib"))
external call: unit => unit = "call"

let open_: (string, string) => unit = %raw(`
  function(target, title) {
    window.open(target, title, "scrollbars=no,resizable=no,status=no,location=no,toolbar=no,menubar=no");
  }
`);
