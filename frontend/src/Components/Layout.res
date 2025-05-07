let str = React.string
open I18n

let blur: Dom.element => unit = %raw(`
  (target) => {
    target.blur();
  }
`)

module UserDropdown = {
  @react.component
  let make = () => {
    let session = Session.useSession()

    let (isVisible, setVisible) = React.useState(() => false)
    let ref = React.useRef(Nullable.null)

    let handleToggleOverlay = _ => {
      setVisible(_ => !isVisible)
    }
    let onClickMenuitem = (e: ReactEvent.Mouse.t) => {
      let target = e->JsxEvent.Mouse.target->DOM.targetToDOM
      blur(target)
    }

    switch session {
    | Authenticated(user) =>
      <div id="user" ref={ReactDOM.Ref.domRef(ref)} className="dropdown dropdown-end">
        <div tabIndex={0} role="button" className="btn btn-ghost btn-circle avatar">
          <div className="w-10 rounded-full">
            <img
              alt="User avatar"
              src="https://img.daisyui.com/images/stock/photo-1534528741775-53994a69daeb.webp"
            />
          </div>
        </div>
        <div></div>
        <ul
          tabIndex={0}
          className="menu menu-sm dropdown-content bg-base-100 rounded-box z-1 mt-3 w-52 p-2 shadow">
          <li>
            <Link className="justify-between" onClick={onClickMenuitem} to={Routes(Account(Home))}>
              {tr("account")}
              <span className="badge"> {"New"->str} </span>
            </Link>
          </li>
          <li>
            <Link className="justify-between" onClick={onClickMenuitem} to={Routes(Account(Projects))}>
              {"My projects"->str}
            </Link>
          </li>
          <li>
            <a> {tr("logout")} </a>
          </li>
        </ul>
      </div>
    | Unauthenticated =>
      <div>
        <Overlay onClose=handleToggleOverlay isVisible>
          <Login />
        </Overlay>
        <div className="btn btn-ghost btn-circle avatar" onClick=handleToggleOverlay>
          <div className="w-10 rounded-full">
            <img
              alt="Silhouette"
              src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fofcan.org%2Fwp-content%2Fuploads%2F2021%2F01%2F100-1006688_headshot-silhouette-placeholder-image-person-free-1.png&f=1&nofb=1&ipt=c23bf200fef5198ba7e6221853d6dbcfc28df0c69801a4979487fa3b744ecf41"
            />
          </div>
        </div>
      </div>
    }
  }
}

@react.component
let make = (~children) => {
  <div>
    <nav className="navbar bg-gray-800 shadow-sm">
      <div className="flex">
        <Link className="btn btn-ghost text-xl" to={Routes(Home)}> {"Contributio"->str} </Link>
      </div>
      <div className="flex-1 gap-2">
        <Link className="btn btn-ghost" to={Routes(Projects(None))}> {tr("projects")} </Link>
        <Link className="btn btn-ghost" to={Routes(Tasks(None))}> {tr("tasks")} </Link>
      </div>
      <div className="flex gap-2">
        <input placeholder="Search" className="input input-bordered w-24 md:w-auto" />
        <UserDropdown />
      </div>
    </nav>

    <main>
      <div className="max-w-7xl mx-auto py-6 sm:px-6 lg:px-8"> children </div>
    </main>
  </div>
}
