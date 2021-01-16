type window;

let open_: (string, string) => unit = [%bs.raw
  {|
    function(target, title) {
      window.open(target, title, `scrollbars=no,resizable=no,status=no,location=no,toolbar=no,menubar=no`);
    }
  |}
];

let close: unit => unit = [%bs.raw
  {|
    function() {
      window.close();
    }
  |}
];

module MessageEvent = {
  type t;
  [@bs.get] external data: t => 'a;
};

let onMessage: (string, MessageEvent.t => unit) => unit = [%bs.raw
  {|
    function(event, callback) {
      window.addEventListener("message", function(e) {
        if (e.data === event) {
          callback();
        }
      });
    }
  |}
];

let postMessage: string => unit = [%bs.raw
  {|
    function(event) {
      console.log(window.opener);
      alert(event);
      window.opener.postMessage(event);
    }
  |}
];
