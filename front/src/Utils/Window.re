let open_: (string, string) => unit = [%bs.raw
  {|
    function(target, title) {
      window.open(target, title, `scrollbars=no,resizable=no,status=no,location=no,toolbar=no,menubar=no`);
    }
  |}
];