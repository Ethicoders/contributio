let str = React.string;

type toastConfig = {title: string};

type toastConfigs = array(toastConfig);

type toastState = {toasts: toastConfigs};

type toastActions =
  | Add(toastConfig)
  | Remove(int);

let initialToastState: toastState = {toasts: [||]};

type dispatch = toastActions => unit;
type contextValue = (toastState, dispatch);

let initValue: contextValue = (initialToastState, ignore);

let context = React.createContext(initValue);

let useToast = () => {
  let (toasts, dispatch) = React.useContext(context);

  let remove = index => Remove(index)->dispatch;

  let add = toast => Add(toast)->dispatch;

  (toasts, add, remove);
};

let reducer = (state: toastState, action) =>
  switch (action) {
  | Add(toast) =>
    let _ = Js.Array.push(toast, state.toasts);
    {toasts: state.toasts};
  | Remove(index) =>
    let _ = Js.Array.removeFromInPlace(~pos=index, state.toasts);
    {toasts: state.toasts};
  };

module ToastProvider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(context);
};

module Toast = {
  [@react.component]
  let make = (~title, ~onClickRemove) => {
    <div className="flex justify-center">
      <div
        className="w-full px-6 py-3 shadow-2xl flex flex-col items-center border-t
            sm:w-auto sm:m-4 sm:rounded-lg sm:flex-row sm:border bg-green-600 border-green-600 text-white">
        <div> title->str </div>
        <div className="flex mt-2 sm:mt-0 sm:ml-4">
          <button
            onClick=onClickRemove
            className="px-3 py-2 hover:bg-green-700 transition ease-in-out duration-300">
            "Dismiss"->str
          </button>
        </div>
      </div>
    </div>;
  };
};

[@react.component]
let make = (~children) => {
  let (state, dispatch) = React.useReducer(reducer, initialToastState);

  <ToastProvider value=(state, dispatch)>
    children
    {Array.mapi(
       (index, toast: toastConfig) =>
         <Toast
           title={toast.title}
           onClickRemove={_ => Remove(index)->dispatch}
         />,
       state.toasts,
     )
     |> React.array}
  </ToastProvider>;
};
