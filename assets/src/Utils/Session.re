let cookieExists: unit => int = [%bs.raw
  {|
    function() {
      document.cookie = 'ctiotoken=test';
      return document.cookie.indexOf('ctiotoken');
    }
  |}
];

let isConnected = () => {
  switch (cookieExists()) {
  | -1 => true
  | _ => false
  };
}