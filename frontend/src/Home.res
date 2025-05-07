let str = React.string;

@react.component
let make = () => {
  <div className="p-8 font-sans">
    <header className="mb-8">
      <h1 className="text-4xl font-bold text-gray-800">{"Contributio"->str}</h1>
      <p className="text-lg text-gray-600">{"Making Open Source discovery and contributions easier."->str}</p>
    </header>
    <main>
      <section className="mb-8">
        <h2 className="text-2xl font-semibold text-gray-800">{"What is Contributio?"->str}</h2>
        <p className="text-gray-600">{"Contributio is a tool designed to help developers find and contribute to Open Source projects effortlessly."->str}</p>
      </section>
      <section className="mb-8">
        <h2 className="text-2xl font-semibold text-gray-800">{"How it works?"->str}</h2>
        <ul className="list-disc list-inside text-gray-600">
          <li>{"Discover projects based on your interests."->str}</li>
          <li>{"Get guidance on how to contribute."->str}</li>
          <li>{"Make meaningful contributions to the Open Source community."->str}</li>
        </ul>
      </section>
      <section>
        <h2 className="text-2xl font-semibold text-gray-800">{"Guides"->str}</h2>
        <p className="text-gray-600">{"Explore our beginner-friendly guides to get started with the Open Source world."->str}</p>
        <button className="btn btn-primary mt-4">{"View Guides"->str}</button>
      </section>
    </main>
  </div>;
};
