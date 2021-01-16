let cookieDidNotExpire: unit => bool = [%bs.raw
  {|
    function() {
      console.log(document.cookie.indexOf('ctiotokenexpire'));
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
