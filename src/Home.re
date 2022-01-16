let str = React.string;
let logo: string = [%raw "require('./assets/logo.png')"];

type pageView =
  | Dashboard
  | MyRecipe;

[@react.component]
let make = () => {
  let (statePage, setStatePage) = React.useState(() => Dashboard);

  <div>
    <nav className="bg-gray-800">
      <div className="max-w-7xl mx-auto px-2 sm:px-6 lg:px-8">
        <div className="relative flex items-center justify-between h-16">
          <div
            className="absolute inset-y-0 left-0 flex items-center sm:hidden">
            <button
              type_="button"
              className="inline-flex items-center justify-center p-2 rounded-md text-gray-400 hover:text-white hover:bg-gray-700 focus:outline-none focus:ring-2 focus:ring-inset focus:ring-white"
              ariaControls="mobile-menu"
              ariaExpanded=false>
              <svg
                className="hidden h-6 w-6"
                xmlns="http://www.w3.org/2000/svg"
                fill="none"
                viewBox="0 0 24 24"
                stroke="currentColor"
                ariaHidden=true>
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth="2"
                  d="M6 18L18 6M6 6l12 12"
                />
              </svg>
            </button>
          </div>
          <div
            className="flex-1 flex items-center justify-center sm:items-stretch sm:justify-start">
            <div className="flex-shrink-0 flex items-center">
              <img
                className="hidden lg:block h-8 w-auto"
                src="https://tailwindui.com/img/logos/workflow-logo-indigo-500-mark-white-text.svg"
                alt="Workflow"
              />
            </div>
            <div className="hidden sm:block sm:ml-6">
              <div
                className="flex space-x-4"
                onClick={_ => setStatePage(_ => Dashboard)}>
                <a
                  href="#"
                  className="bg-gray-900 text-white px-3 py-2 rounded-md text-sm font-medium">
                  {"Dashboard" |> str}
                </a>
              </div>
            </div>
          </div>
          <div
            className="absolute inset-y-0 right-0 flex items-center pr-2 sm:static sm:inset-auto sm:ml-6 sm:pr-0">
            <div className="ml-3 relative">
              <div>
                <div
                  className="flex space-x-4"
                  onClick={_ => setStatePage(_ => MyRecipe)}>
                  <a
                    href="#"
                    className="bg-gray-900 text-white px-3 py-2 rounded-md text-sm font-medium">
                    {"My Recipe" |> str}
                  </a>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </nav>
    // Navbar End
    <div className="h-fit flex justify-center items-center">
      <div className="w-8/12 rounded overflow-hidden shadow-lg px-4 py-8">
        {switch (statePage) {
         | Dashboard => <RecipeForm />
         | MyRecipe => <RecipeList />
         }}
      </div>
    </div>
  </div>;
};
