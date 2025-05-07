let str = React.string

@react.component
let make = (~name, ~description) => {
  <div className="card bg-base-100 w-96 shadow-sm">
    <figure>
      <img
        src="https://img.daisyui.com/images/stock/photo-1606107557195-0e29a4b5b4aa.webp" alt="Shoes"
      />
    </figure>
    <div className="card-body">
      <h2 className="card-title">
        {name->str}
        // <div className="badge badge-secondary"> NEW </div>
      </h2>
      <p> {description->str} </p>
      <div className="card-actions justify-end">
        <div className="badge badge-outline"> {str("Fashion")} </div>
        <div className="badge badge-outline"> {str("Products")} </div>
      </div>
    </div>
  </div>
}
