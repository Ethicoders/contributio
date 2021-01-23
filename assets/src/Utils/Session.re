let cookieDidNotExpire: unit => bool = [%bs.raw
  {|
    function() {
      if (-1 === document.cookie.indexOf('ctiotokenexpire')) {
        return false;
      }
      var out = /ctiotokenexpire=([^;]*)/.exec(document.cookie);
      return new Date(out[1]) >= new Date();
    }
  |}
];

let isConnected = () => {
  cookieDidNotExpire();
};

let logout: unit => unit = [%bs.raw
  {|
    function() {
      document.cookie = 'ctiotokenexpire= ; expires = Thu, 01 Jan 1970 00:00:00 GMT';
    }
  |}
];
