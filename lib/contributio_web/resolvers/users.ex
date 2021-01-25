defmodule Resolvers.Users do
  require Logger
  alias Contributio.{Accounts, Market, Repo}
  alias ContributioWeb.Utils

  def get_user(%{id: id}, _info) do
    {:ok,
     Accounts.get_user(id) |> Repo.preload(:projects) |> Accounts.User.set_next_level_experience()}
  end

  def create(params, _info) do
    Accounts.create_user(params)
  end

  def update_current_user(params, %{context: %{current_user: current_user}}) do
    current_user
    |> Accounts.User.changeset(params)
    |> Repo.update!()

    {:ok, %{user: current_user}}
  end

  def update_current_user(_args, _info), do: {:error, "Not Authorized"}

  # Authorized context, can fetch sensitive data
  def get_current_user(_args, %{context: %{current_user: current_user}}) do
    {:ok, current_user |> Repo.preload([projects: :tasks])}
  end

  def get_current_user(_args, _info), do: {:error, "Not Authorized"}

  def authenticate(%{email: email, password: password}, _info) do
    case email
         |> Accounts.get_user_by_email()
         |> Bcrypt.check_pass(password, hash_key: :hash) do
      {:ok, user} ->
        {:ok, user |> set_user_token()}

      payload
      when payload in [{:error, "invalid user-identifier"}, {:error, "invalid password"}] ->
        {:error, "Invalid email or password."}
    end
  end

  # VCS part
  def request_access_token(%{code: code}, %{context: %{current_user: _current_user}}) do
    {:ok, fetch_access_token(code)}
  end

  def request_access_token(%{code: code}, _info) do
    {:ok, fetch_access_token(code)}
  end

  defp fetch_access_token(code) do
    case HTTPoison.post(
           "https://github.com/login/oauth/access_token",
           Jason.encode!(%{
             code: code,
             client_id: System.get_env("GITHUB_CLIENT_ID"),
             client_secret: System.get_env("GITHUB_CLIENT_SECRET")
           }),
           [{"Content-Type", "application/json"}]
         ) do
      {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
        %{access_token: body}

      {:error, %HTTPoison.Error{reason: reason}} ->
        IO.inspect(reason)
    end
  end

  def link_account(%{origin_id: origin_id, content: content}, %{
        context: %{current_user: current_user}
      }) do
    access_token = content

    user_origin_id = fetch_user_origin_data(access_token).id

    Accounts.upsert_user_origin(%{
      origin_id: origin_id,
      user_id: current_user.id,
      access_token: access_token,
      user_origin_id: user_origin_id
    })

    {:ok, current_user}
  end

  def link_account(_args, _info), do: {:error, "Not Authorized"}

  def create_linked_account(%{origin_id: origin_id, content: content}, _info) do
    access_token = content

    user_origin = fetch_user_origin_data(access_token)

    current_user =
      Accounts.get_or_create_user(%{
        name: user_origin.login,
        email: user_origin.email
      })

    Accounts.upsert_user_origin(%{
      origin_id: origin_id,
      user_id: current_user.id,
      access_token: access_token,
      user_origin_id: user_origin.id
    })

    {:ok, %{user: current_user |> set_user_token()}}
  end

  defp set_user_token(%Accounts.User{} = user) do
    token = Phoenix.Token.sign(ContributioWeb.Endpoint, "user auth", user.id)

    user
    |> Accounts.User.changeset(%{token: token})
    |> Repo.update!()
  end

  defp fetch_user_origin_data(access_token) do
    case HTTPoison.get(
           "https://api.github.com/user",
           "Content-Type": "application/json",
           Authorization: "token #{access_token}"
         ) do
      {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
        case Jason.decode!(body, keys: :atoms) do
          user -> user
        end

      {:error, %HTTPoison.Error{reason: reason}} ->
        IO.inspect(inspect(reason))
    end
  end

  def fetch_repositories(%{origin_id: origin_id}, %{
        context: %{current_user: %Accounts.User{} = current_user}
      }) do
    Logger.debug(inspect(current_user))
    access_token = Accounts.get_user_origin(origin_id, current_user.id).access_token

    case HTTPoison.get(
           "https://api.github.com/user/repos",
           ["Content-Type": "application/json", Authorization: "token #{access_token}"],
           params: %{type: "public"}
         ) do
      {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
        case Jason.decode!(body, keys: :atoms) do
          repos ->
            {:ok, Enum.map(repos, &%{&1 | url: &1.html_url, id: &1.full_name})}
        end

      {:error, %HTTPoison.Error{reason: reason}} ->
        IO.inspect(reason)
    end
  end

  def fetch_repositories(_args, _info), do: {:error, "Not Authorized"}

  def import_repositories(%{origin_id: origin_id, ids: ids}, %{
        context: %{current_user: current_user}
      }) do
    access_token = Accounts.get_user_origin(origin_id, current_user.id).access_token

    ids
    |> Enum.map(
      &case HTTPoison.get(
              "https://api.github.com/repos/#{&1}",
              ["Content-Type": "application/json", Authorization: "token #{access_token}"],
              params: %{type: "public"},
              hackney: [pool: :default]
            ) do
        {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
          case Jason.decode!(body, keys: :atoms) do
            repo ->
              case HTTPoison.get(
                     repo.languages_url,
                     ["Content-Type": "application/json"],
                     hackney: [pool: :default]
                   ) do
                {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
                  case Jason.decode!(body, keys: :atoms) do
                    languages ->
                      Market.create_project(%{
                        name: repo.name,
                        repo_id: repo.full_name,
                        description: repo.description,
                        url: repo.html_url,
                        languages: languages,
                        user_id: current_user.id
                      })
                  end
              end
          end

        {:error, %HTTPoison.Error{reason: reason}} ->
          IO.inspect(reason)
      end
    )

    {:ok, true}
  end

  def import_repositories(_args, _info), do: {:error, "Not Authorized"}

  def fetch_issues(%{origin_id: _origin_id, project_id: project_id}, %{
        context: %{current_user: _current_user}
      }) do
    # access_token = Accounts.get_user_origin(origin_id, current_user.id).access_token

    repo_id = Market.get_project!(project_id).repo_id

    case HTTPoison.get(
           "https://api.github.com/repos/#{repo_id}/issues",
           "Content-Type": "application/json"
         ) do
      {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
        case Jason.decode!(body, keys: :atoms) do
          issues ->
            {:ok, Enum.map(issues, &%{&1 | url: &1.html_url, id: &1.number})}
        end

      {:error, %HTTPoison.Error{reason: reason}} ->
        IO.inspect(reason)
    end
  end

  def fetch_issues(_args, _info), do: {:error, "Not Authorized"}

  def import_issues(%{origin_id: _origin_id, ids: ids, project_id: project_id}, %{
        context: %{current_user: _current_user}
      }) do
    # access_token = Accounts.get_user_origin(origin_id, current_user.id).access_token
    repo_id = Market.get_project!(project_id).repo_id

    ids
    |> Enum.map(
      &case HTTPoison.get(
              "https://api.github.com/repos/#{repo_id}/issues/#{&1}",
              ["Content-Type": "application/json"],
              hackney: [pool: :default]
            ) do
        {:ok, %HTTPoison.Response{status_code: 200, body: body}} ->
          case Jason.decode!(body, keys: :atoms) do
            issue ->
              Utils.extract_contributio_code_data(issue.body)
              |> Map.merge(%{
                name: issue.title,
                content: issue.body,
                url: issue.html_url,
                issue_id: Integer.to_string(issue.number),
                project_id: project_id
              })
              |> Contributio.Market.create_task()
          end

        {:error, %HTTPoison.Error{reason: reason}} ->
          IO.inspect(reason)
      end
    )

    {:ok, true}
  end

  def import_issues(_args, _info), do: {:error, "Not Authorized"}
end
