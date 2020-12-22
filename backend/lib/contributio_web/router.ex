defmodule ContributioWeb.Router do
  use ContributioWeb, :router

  pipeline :browser do
    plug :accepts, ["html"]
    plug :fetch_session
    plug :fetch_flash
    plug :protect_from_forgery
    plug :put_secure_browser_headers
  end

  pipeline :api do
    plug CORSPlug, origin: "*"
    plug :accepts, ["json"]
  end

  scope "/", ContributioWeb do
    pipe_through :browser # Use the default browser stack

    get "/", PageController, :index

    get "/allow", APIAllowController, :index
  end

  scope "/" do
    pipe_through :api

    forward "/graph", Absinthe.Plug, schema: Contributio.Schema
    forward "/graphiql", Absinthe.Plug.GraphiQL, schema: Contributio.Schema
  end

  # Enables LiveDashboard only for development
  #
  # If you want to use the LiveDashboard in production, you should put
  # it behind authentication and allow only admins to access it.
  # If your application does not have an admins-only section yet,
  # you can use Plug.BasicAuth to set up some basic authentication
  # as long as you are also using SSL (which you should anyway).
  if Mix.env() in [:dev, :test] do
    import Phoenix.LiveDashboard.Router

    scope "/" do
      pipe_through :browser
      live_dashboard "/dashboard", metrics: ContributioWeb.Telemetry
    end
  end
end
