let str = React.string;

[@react.component]
let make = () => {
  <div>
    "Homepage"->str
    <table className="min-w-full divide-y divide-gray-200">
      <thead className="bg-gray-50">
        <tr>
          <th
            scope="col"
            className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
            "Name"->str
          </th>
          <th
            scope="col"
            className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
            "Title"->str
          </th>
          <th
            scope="col"
            className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
            "Status"->str
          </th>
          <th
            scope="col"
            className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">
            "Role"->str
          </th>
          <th scope="col" className="relative px-6 py-3">
            <span className="sr-only"> "Edit"->str </span>
          </th>
        </tr>
      </thead>
      <tbody className="bg-white divide-y divide-gray-200">
        <tr>
          <td className="px-6 py-4 whitespace-nowrap">
            <div className="flex items-center">
              <div className="flex-shrink-0 h-10 w-10" />
              <div className="ml-4">
                <div className="text-sm font-medium text-gray-900">
                  "Jane Cooper"->str
                </div>
                <div className="text-sm text-gray-500">
                  "jane.cooper@example.com"->str
                </div>
              </div>
            </div>
          </td>
          <td className="px-6 py-4 whitespace-nowrap">
            <div className="text-sm text-gray-900">
              "Regional Paradigm Technician"->str
            </div>
            <div className="text-sm text-gray-500"> "Optimization"->str </div>
          </td>
          <td className="px-6 py-4 whitespace-nowrap">
            <span
              className="px-2 inline-flex text-xs leading-5 font-semibold rounded-full bg-green-100 text-green-800">
              "Active"->str
            </span>
          </td>
          <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
            "Admin"->str
          </td>
          <td
            className="px-6 py-4 whitespace-nowrap text-right text-sm font-medium">
            <a href="#" className="text-indigo-600 hover:text-indigo-900">
              "Edit"->str
            </a>
          </td>
        </tr>
      </tbody>
    </table>
  </div>;
};
