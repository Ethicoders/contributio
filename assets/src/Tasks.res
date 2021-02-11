let str = React.string

module GetTasks = %graphql(`
    query getTasks($after: String, $difficulty: [Int!], $time: [Int!], $status: Int) {
      tasks(after: $after, first: 6, difficulty: $difficulty, time: $time, status: $status) {
        edges {
          node {
            id
            name
            content
            experience
            difficulty
            time
            status
            project {
              id
              name
            }
          }
          cursor
        }
        pageInfo {
          hasNextPage
          hasPreviousPage
          startCursor
          endCursor
        }
      }
    }
`)

@react.component
let make = () => {
  let (difficulty, setDifficulty) = React.useState(() => None)
  let (time, setTime) = React.useState(() => None)
  let (status, setStatus) = React.useState(() => Some("0"))
  <div>
    <div className="hidden"> <Heading size=Gigantic> {"Tasks"->str} </Heading> </div>
    <div className="p-2">
      <span className="mx-1">
        <ButtonGroup
          icon=Some(Icon.Lightbulb)
          onChange={newDifficulty => setDifficulty(_ => newDifficulty)}
          buttonsData=[
            {label: "Easy", value: "1-3", activeClassNames: Some("bg-green-500")},
            {label: "Medium", value: "4-6", activeClassNames: Some("bg-orange-500")},
            {label: "Hard", value: "7-10", activeClassNames: Some("bg-red-500")},
          ]
        />
      </span>
      <span>
        <ButtonGroup
          icon=Some(Icon.Timer)
          onChange={newTime => setTime(_ => newTime)}
          buttonsData=[
            {label: "Quick", value: "1-3", activeClassNames: Some("bg-green-500")},
            {label: "Medium", value: "4-6", activeClassNames: Some("bg-orange-500")},
            {label: "Long", value: "7-10", activeClassNames: Some("bg-red-500")},
          ]
        />
      </span>
      <span>
        <ButtonGroup
          value=status
          onChange={newStatus => setStatus(_ => newStatus)}
          buttonsData=[
            {label: "Opened", value: "0", activeClassNames: Some("bg-green-500")},
            {label: "Closed", value: "1", activeClassNames: Some("bg-green-500")},
          ]
        />
      </span>
    </div>
    {switch GetTasks.use({
      status: switch status {
      | None => None
      | Some(status) => Some(int_of_string(status))
      },
      difficulty: switch difficulty {
      | None => None
      | Some(difficulty) => Some(Js.String.split("-", difficulty)->Belt.Array.map(int_of_string))
      },
      time: switch time {
      | None => None
      | Some(time) => Some(Js.String.split("-", time)->Belt.Array.map(int_of_string))
      },
      after: None,
    }) {
    | {loading: true} => "Loading..."->React.string
    | {data: None} => React.null
    | {data: Some({tasks}), loading: false, fetchMore: _} =>
      let values = switch tasks {
      | None => []
      | Some(any) =>
        switch any.edges {
        | None => []
        | Some(values) =>
          values->Belt.Array.map(value =>
            switch value {
            | None => None
            | Some(task) => Some(task.node)
            }
          )
        }
      }
      <div className="grid grid-cols-4 gap-4 p-2">
        {switch values {
        | [] => "No results!"->str
        | values =>
          values
          ->Js.Array2.map(maybeTask => {
            switch maybeTask {
            | None => React.null
            | Some(task) => {
                let project: Types.projectData = {
                  id: task.project.id,
                  name: task.project.name,
                }

                <Task
                  key={task.id}
                  name={task.name}
                  id={task.id}
                  content={task.content}
                  experience={task.experience}
                  difficulty={task.difficulty}
                  status={task.status}
                  time={task.time}
                  maybeProject={Some(project)}
                />
              }
            }
          })
          ->React.array
        }}
      </div>
    }}
  </div>
}
