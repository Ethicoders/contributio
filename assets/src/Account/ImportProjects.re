let str = React.string;

module FetchRepositories = [%graphql
  {|
    query fetchRepositories($originId: Int!) {
      fetchRepositories(originId: $originId) {
        id
        url
        name
        fullName
      }
    }
|}
];

module ImportRepositories = [%graphql
  {|
  mutation importRepositories ($originId: Int!, $ids: [Int!]!) {
    importRepositories(originId: $originId, ids: $ids)
  }
|}
];

[@react.component]
let make = () => {
  let (ids, setIDs) = React.useState(_ => [||]);
  let (mutate, _mutationResult) = ImportRepositories.use();

  <div>
    <h1> "My Repositories"->str </h1>
    <div className="px-2">
      <svg
        className="absolute z-50 m-1 text-blue-400"
        width="24"
        height="24"
        viewBox="0 0 24 24"
        fill="currentColor"
        xmlns="http://www.w3.org/2000/svg">
        <path
          d="M14.71 14H15.5L20.49 19L19 20.49L14 15.5V14.71L13.73 14.43C12.59 15.41 11.11 16 9.5 16C5.90997 16 3 13.09 3 9.5C3 5.90997 5.90997 3 9.5 3C13.09 3 16 5.90997 16 9.5C16 11.11 15.41 12.59 14.43 13.73L14.71 14ZM5 9.5C5 11.99 7.01001 14 9.5 14C11.99 14 14 11.99 14 9.5C14 7.01001 11.99 5 9.5 5C7.01001 5 5 7.01001 5 9.5Z"
          fill="black"
          fillOpacity="0.54"
        />
      </svg>
      <input
        type_="text"
        className="pl-8 p-1 bg-gray-200 w-full rounded relative"
        placeholder="Search..."
      />
    </div>
    {switch (FetchRepositories.use({originId: 1})) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({fetchRepositories}), loading: false} =>
       let handleClick = _ => {
         let result = mutate({originId: 1, ids});

         result
         |> Js.Promise.then_(value => {Js.Promise.resolve(value)})
         |> ignore;
       };
       let removeFromArray = (item, values) => {
         let _ =
           Js.Array.removeCountInPlace(
             ~pos=Js.Array.indexOf(item, values),
             ~count=1,
             values,
           );
         values;
       };

       let handleCheckboxClick = id => {
         setIDs(previousIDs => {
           Js.Array.includes(id, previousIDs)
             ? removeFromArray(id, previousIDs)
             : Js.Array.concat([|id|], previousIDs)
         });
       };

       <>
         <ul>
           {fetchRepositories
            ->Belt.Array.map(repo =>
                <li>
                  <input
                    onClick={_ => handleCheckboxClick(repo.id)}
                    type_="checkbox"
                    value={repo.id->Belt.Int.toString}
                  />
                  repo.fullName->str
                  " - "->str
                  <a href={repo.url} target="_blank"> "See"->str </a>
                </li>
              )
            ->React.array}
         </ul>
         <div className="max-w-md w-full space-y-8">
           <button
             onClick=handleClick
             className="inline-flex items-center px-4 py-2 border border-transparent rounded-md shadow-sm text-sm font-medium text-white bg-indigo-600 hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-indigo-500">
             "Import"->str
           </button>
         </div>
       </>;
     }}
  </div>;
};
