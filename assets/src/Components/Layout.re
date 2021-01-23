let str = React.string;

[@react.component]
let make = (~children) => {
  let (isVisible, setVisible) = React.useState(() => false);

  let handleToggleOverlay = _ => setVisible(_ => !isVisible);

  let handleOnSignIn = _ => {
    Js.log("in!");
    setVisible(_ => false);
  };
  <>
    <nav className="bg-gray-800">
      <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="flex items-center justify-between h-16">
          <div className="flex items-center">
            <div className="flex-shrink-0">
              <Anchor target="/">
                <Logo />
                <span className="text-green-500 text-shadow-lg font-bold">
                  "ontributio"->str
                </span>
              </Anchor>
            </div>
            <div className="hidden md:block">
              <div className="ml-10 flex items-baseline space-x-4">
                <Anchor
                  target="/operation"
                  className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
                  "Operation"->str
                </Anchor>
                <Anchor
                  target="/projects"
                  className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
                  "Projects"->str
                </Anchor>
                <Anchor
                  target="/tasks"
                  className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
                  "Tasks"->str
                </Anchor>
                <Anchor
                  target="/users"
                  className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
                  "Users"->str
                </Anchor>
              </div>
            </div>
          </div>
          <div className="hidden md:block">
            <div className="ml-4 flex items-center md:ml-6">
              <button
                className="bg-gray-800 p-1 rounded-full text-gray-400 hover:text-white focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-800 focus:ring-white">
                <span className="sr-only"> "View notifications"->str </span>
              </button>
              /* <svg className="h-6 w-6" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                   <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 17h5l-1.405-1.405A2.032 2.032 0 0118 14.158V11a6.002 6.002 0 00-4-5.659V5a2 2 0 10-4 0v.341C7.67 6.165 6 8.388 6 11v3.159c0 .538-.214 1.055-.595 1.436L4 17h5m6 0v1a3 3 0 11-6 0v-1m6 0H9" />
                 </svg> */
              <div className="ml-3 relative">
                <div className="">
                  {Session.isConnected()
                     ? <>
                         <Dropdown
                           button={
                             Some(
                               <button
                                 className="max-w-xs bg-gray-800 rounded-full flex items-center text-sm focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-800 focus:ring-white"
                                 id="user-menu">
                                 <span className="sr-only">
                                   "Open user menu"->str
                                 </span>
                                 <span
                                   className="h-8 w-8 max-w-xs bg-gray-200 rounded-full flex justify-center items-center text-sm focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-800 focus:ring-white">
                                   <Icon name=User />
                                 </span>
                               </button>,
                             )
                           }>
                           <Anchor
                             className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                             target="/account">
                             "Settings"->str
                           </Anchor>
                           <Anchor
                             className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                             target="/account/projects">
                             "My Projects"->str
                           </Anchor>
                           <Anchor
                             className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                             target="/account/tasks">
                             "My Tasks"->str
                           </Anchor>
                           <button
                             onClick={e => {
                               Session.logout();
                               Router.goTo(e, "/");
                             }}
                             className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                             role="menuitem">
                             "Sign out"->str
                           </button>
                         </Dropdown>
                         /* <button
                              className="max-w-xs bg-gray-800 rounded-full flex items-center text-sm focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-800 focus:ring-white"
                              id="user-menu">
                              <span className="sr-only">
                                "Open user menu"->str
                              </span>
                              <span
                                className="h-8 w-8 max-w-xs bg-gray-200 rounded-full flex items-center text-sm focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-800 focus:ring-white">
                                /* className="h-8 w-8 rounded-full" */
                                 <Icon name=User /> </span>
                            </button>
                            <div
                              className="origin-top-right absolute right-0 mt-2 w-48 rounded-md shadow-lg py-1 bg-white ring-1 ring-black ring-opacity-5"
                              role="menu">
                              <Anchor
                                className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                                target="/account">
                                "Settings"->str
                              </Anchor>
                              <Anchor
                                className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                                target="/account/projects">
                                "My Projects"->str
                              </Anchor>
                              <Anchor
                                className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                                target="/account/tasks">
                                "My Tasks"->str
                              </Anchor>
                              <a
                                href="#"
                                /* onClick={e => TBD} */
                                className="block px-4 py-2 text-sm text-gray-700 hover:bg-gray-100"
                                role="menuitem">
                                "Sign out"->str
                              </a>
                            </div> */
                       </>
                     : <>
                         <Button type_=Primary onClick=handleToggleOverlay>
                           "Entry"->str
                         </Button>
                         <Overlay onClose=handleToggleOverlay isVisible>
                           <Login onSignIn=handleOnSignIn />
                         </Overlay>
                       </>}
                </div>
              </div>
            </div>
          </div>
        </div>
        <div className="-mr-2 flex md:hidden">
          <button
            className="bg-gray-800 inline-flex items-center justify-center p-2 rounded-md text-gray-400 hover:text-white hover:bg-gray-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-800 focus:ring-white">
            <span className="sr-only"> "Open main menu"->str </span>
          </button>
        </div>
      </div>
      /* <svg className="block h-6 w-6" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
           <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 6h16M4 12h16M4 18h16" />
         </svg> */
      /* <svg className="hidden h-6 w-6" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor">
           <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12" />
         </svg> */
      <div className="hidden md:hidden">
        <div className="px-2 pt-2 pb-3 space-y-1 sm:px-3">
          <a
            href="#"
            className="bg-gray-900 text-white block px-3 py-2 rounded-md text-base font-medium">
            "Dashboard"->str
          </a>
          <a
            href="#"
            className="text-gray-300 hover:bg-gray-700 hover:text-white block px-3 py-2 rounded-md text-base font-medium">
            "Team"->str
          </a>
          <a
            href="#"
            className="text-gray-300 hover:bg-gray-700 hover:text-white block px-3 py-2 rounded-md text-base font-medium">
            "Projects"->str
          </a>
          <a
            href="#"
            className="text-gray-300 hover:bg-gray-700 hover:text-white block px-3 py-2 rounded-md text-base font-medium">
            "Calendar"->str
          </a>
          <a
            href="#"
            className="text-gray-300 hover:bg-gray-700 hover:text-white block px-3 py-2 rounded-md text-base font-medium">
            "Reports"->str
          </a>
        </div>
        <div className="pt-4 pb-3 border-t border-gray-700">
          <div className="flex items-center px-5">
            <div
              className="flex-shrink-0"
              /* <img
                   className="h-10 w-10 rounded-full"
                   alt=""
                 /> */
            />
            <div className="ml-3">
              <div
                className="text-base font-medium leading-none text-white"
                /* "Tom Cook"->str */
              />
              <div
                className="text-sm font-medium leading-none text-gray-400"
                /* "tom@example.com"->str */
              />
            </div>
            <button
              className="ml-auto bg-gray-800 flex-shrink-0 p-1 rounded-full text-gray-400 hover:text-white focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-offset-gray-800 focus:ring-white">
              <span className="sr-only"> "View notifications"->str </span>
            </button>
          </div>
          /* <svg className="h-6 w-6" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" aria-hidden="true">
               <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 17h5l-1.405-1.405A2.032 2.032 0 0118 14.158V11a6.002 6.002 0 00-4-5.659V5a2 2 0 10-4 0v.341C7.67 6.165 6 8.388 6 11v3.159c0 .538-.214 1.055-.595 1.436L4 17h5m6 0v1a3 3 0 11-6 0v-1m6 0H9" />
             </svg> */
          <div className="mt-3 px-2 space-y-1">
            <a
              href="#"
              className="block px-3 py-2 rounded-md text-base font-medium text-gray-400 hover:text-white hover:bg-gray-700">
              "Your Profile"->str
            </a>
            <a
              href="#"
              className="block px-3 py-2 rounded-md text-base font-medium text-gray-400 hover:text-white hover:bg-gray-700">
              "Settings"->str
            </a>
            <a
              href="#"
              className="block px-3 py-2 rounded-md text-base font-medium text-gray-400 hover:text-white hover:bg-gray-700">
              "Sign out"->str
            </a>
          </div>
        </div>
      </div>
    </nav>
    /* <header className="bg-white shadow">
         <div className="max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8">
           <h1 className="text-3xl font-bold leading-tight text-gray-900">
             "Dashboard"->str
           </h1>
         </div>
       </header> */
    <main className="min-h-screen">
      <div className="max-w-7xl mx-auto py-6 sm:px-6 lg:px-8"> children </div>
    </main>
    <footer className="w-full">
      <div className="bg-gray-700">
        <div
          className="max-w-6xl m-auto text-gray-800 flex flex-wrap justify-center">
          <div className="p-5 w-48 ">
            <Anchor
              target="/operation"
              className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
              "Operation"->str
            </Anchor>
          </div>
          /* <div class="text-xs uppercase text-gray-500 font-medium">Home</div>
             <a class="my-3 block" href="/#">Services <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Products <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">About Us <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Pricing <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Partners <span class="text-teal-600 text-xs p-1">New</span></a>  */
          <div className="p-5 w-48 ">
            <Anchor
              target="/projects"
              className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
              "Projects"->str
            </Anchor>
          </div>
          /* <div class="text-xs uppercase text-gray-500 font-medium">User</div>
             <a class="my-3 block" href="/#">Sign in <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">New Account <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Demo <span class="text-teal-600 text-xs p-1">New</span></a><a class="my-3 block" href="/#">Career <span class="text-teal-600 text-xs p-1">We're hiring</span></a><a class="my-3 block" href="/#">Surveys <span class="text-teal-600 text-xs p-1">New</span></a>  */
          <div className="p-5 w-48 ">
            <Anchor
              target="/tasks"
              className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
              "Tasks"->str
            </Anchor>
          </div>
          <div className="p-5 w-48">
            <Anchor
              target="/users"
              className="text-gray-300 hover:bg-gray-700 hover:text-white px-3 py-2 rounded-md text-sm font-medium">
              "Users"->str
            </Anchor>
          </div>
        </div>
      </div>
      /* <div class="text-xs uppercase text-gray-500 font-medium">Resources</div>
         <a class="my-3 block" href="/#">Documentation <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Tutorials <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Support <span class="text-teal-600 text-xs p-1">New</span></a>  */
      /* <div class="p-5 w-48 ">
            <div class="text-xs uppercase text-gray-500 font-medium">Product</div>
            <a class="my-3 block" href="/#">Our Products <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Great Deals <span class="text-teal-600 text-xs p-1">New</span></a><a class="my-3 block" href="/#">Analytics <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Mobile <span class="text-teal-600 text-xs p-1"></span></a>
         </div>
         <div class="p-5 w-48 ">
            <div class="text-xs uppercase text-gray-500 font-medium">Support</div>
            <a class="my-3 block" href="/#">Help Center <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Privacy Policy <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">Conditions <span class="text-teal-600 text-xs p-1"></span></a>
         </div>
         <div class="p-5 w-48 ">
            <div class="text-xs uppercase text-gray-500 font-medium">Contact us</div>
            <a class="my-3 block" href="/#">XXX XXXX, Floor 4 San Francisco, CA <span class="text-teal-600 text-xs p-1"></span></a><a class="my-3 block" href="/#">contact@company.com <span class="text-teal-600 text-xs p-1"></span></a>
         </div> */
      <div className="bg-gray-800">
        <div
          className="flex pb-5 px-3 m-auto pt-5 border-black	 border-t text-white text-sm flex-col
       md:flex-row max-w-6xl">
          <div className="mt-2"> "Contributio 2021"->str </div>
          <div
            className="md:flex-auto md:flex-row-reverse mt-2 flex-row flex"
          />
        </div>
      </div>
    </footer>
  </>;
};
