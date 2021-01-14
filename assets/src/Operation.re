let str = React.string;

[@react.component]
let make = () => {
  <div>
    <Heading size=Big> "How does it work?"->str </Heading>
    "First of all, you'll need to create a Contributio account. When it's done, head to your account details.
    From there, bind a Version Constrol System platform account such as GitHub, GitLab, Bitbucket,...
    Your account is now fully setup!
    A note for what comes next: you don't have to choose between being a Maintainer or a Contributor. You can freely import your own repositories and work on other people's."
    ->str
    <section>
      <Heading> "As a Maintainer"->str </Heading>
      "Contributio allows you to define trackable projects from various origins.
      From your account, go to 'Import' and choose an origin. You'll get a list of repositories you may want to import as Contributio projects.
      Pick the repositories, import them and voilà! You now have tracked projects and related issues will be automatically imported when created.
      "
      ->str
    </section>
    <section>
      <Heading> "As a Contributor"->str </Heading>
      "You can browse projects and tasks, filter by used language, etc. When you create a submission, maintainers will review your code and validate it.
      If it satisfies the criteria, it will be merged and you'll get rewarded for that with experience and more (TBD!).
      Even if your submission isn't validated, you'll get a portion of the experience when it is closed, as Contributio considers that any work provided should be rewarded."
      ->str
    </section>
    <Heading size=Big> "Wording"->str </Heading>
    <table>
      <thead>
        <tr> <th> "Contributio"->str </th> <th> "VCS"->str </th> </tr>
      </thead>
      <tbody>
        <tr> <td> "Project"->str </td> <td> "Repository"->str </td> </tr>
        <tr> <td> "Task"->str </td> <td> "Issue"->str </td> </tr>
        <tr>
          <td> "Submission"->str </td>
          <td> "Pull/merge request"->str </td>
        </tr>
      </tbody>
    </table>
  </div>;
};
