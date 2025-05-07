// [@bs.val] external githubClientID : string = "process.env.GITHUB_CLIENT_ID";
// [@bs.val] external allowEndpoint : string = "process.env.ALLOW_ENDPOINT";
type env = {
  @as("GITHUB_CLIENT_ID")
  githubClientID: string,
  @as("ALLOW_ENDPOINT")
  allowEndpoint: string,
}
@val @scope("process") external env: env = "env"