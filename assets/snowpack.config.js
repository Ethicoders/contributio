/** @type {import("snowpack").SnowpackUserConfig } */
module.exports = {
  mount: {
    public: { url: "/", static: true },
    src: { url: "/js" },
  },
  plugins: [
    "@snowpack/plugin-react-refresh",
    "@snowpack/plugin-dotenv",
    [
      "@snowpack/plugin-run-script",
      {
        cmd: "bsb -make-world",
        watch: "$1 -w",
      },
    ],
    "@snowpack/plugin-postcss",
    "snowpack-graphql-ppx",
    [
      "snowpack-plugin-rollup-bundle",
      {
        entrypoints: [
          "@coreui/icons/fonts/CoreUI-Icons-Brand.eot",
          "@coreui/icons/fonts/CoreUI-Icons-Brand.ttf",
          "@coreui/icons/fonts/CoreUI-Icons-Brand.svg",
          "@coreui/icons/fonts/CoreUI-Icons-Brand.woff",
          "@coreui/icons/fonts/CoreUI-Icons-Free.eot",
          "@coreui/icons/fonts/CoreUI-Icons-Free.ttf",
          "@coreui/icons/fonts/CoreUI-Icons-Free.svg",
          "@coreui/icons/fonts/CoreUI-Icons-Free.woff",
        ],
        emitHtmlFiles: true,
        extendConfig: (config) => {
          config.inputOptions.input = "../priv/static/js/index.bs.js";
          config.outputOptions = {
            dir: "../priv/static/js",
          };
          return config;
        },
      },
    ],
  ],
  packageOptions: {
    knownEntrypoints: [
      "@coreui/icons/fonts/CoreUI-Icons-Brand.eot",
      "@coreui/icons/fonts/CoreUI-Icons-Brand.ttf",
      "@coreui/icons/fonts/CoreUI-Icons-Brand.svg",
      "@coreui/icons/fonts/CoreUI-Icons-Brand.woff",
      "@coreui/icons/fonts/CoreUI-Icons-Free.eot",
      "@coreui/icons/fonts/CoreUI-Icons-Free.ttf",
      "@coreui/icons/fonts/CoreUI-Icons-Free.svg",
      "@coreui/icons/fonts/CoreUI-Icons-Free.woff",
    ],
  },
  devOptions: {
    /* ... */
  },
  buildOptions: {
    out: "../priv/static",
    /* ... */
  },
  alias: {
    /* ... */
  },
};
