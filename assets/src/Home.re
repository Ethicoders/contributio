let str = React.string;

[@react.component]
let make = () => {
  <>
    <section className="relative h-screen flex flex-col">
      <div
        className="home-argument argument-maintainer text-6xl p-10 text-center">
        "Boost your projects visibility"->str
      </div>
      <div className="inset-0 m-auto z-10 w-28 h-28">
        <Button className="home-cta bg-primary" type_=Primary>
          "Start using Contributio"->str
        </Button>
      </div>
      <div
        className="home-argument argument-contributor text-6xl p-10 text-center">
        "Get rewarded for your contributions"->str
      </div>
    </section>
    /* <p>
         "Contributio is a tool made to help Open Source projects to improve their visibility and increase their amount of contributions.
       Devs willing to spare some time to contribute to Open Source projects will be able to find projects depending on some criteria, such as
       the used programming languages, the kind of tasks, effort to put into them, and many more!"
         ->str
       </p> */
    <section>
      <Heading> "What projects are eligible to Contributio?"->str </Heading>
      <p>
        "Any project that complies with the "->str
        <a href="https://opensource.org/osd" target="_blank">
          "Open Source Definition"->str
        </a>
        " can be added to Contributio projects list!"->str
      </p>
    </section>
    <section>
      <Heading> "For maintainers"->str </Heading>
      "Put focus on your projects"->str
      <br />
      "Get help from anyone"->str
      <br />
      "Get traction thanks to the reward system"->str
      <br />
      <Heading> "For contributors"->str </Heading>
      "Find projects from multiple platforms easily"->str
      <br />
      "Showcase your skills"->str
      <br />
      "Get rewarded for your completions"->str
      <br />
    </section>
  </>;
};
