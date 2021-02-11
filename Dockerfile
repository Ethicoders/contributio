FROM elixir:1.10.3
ENV DEBIAN_FRONTEND=noninteractive

# Install hex
RUN mix local.hex --force

# Install rebar
RUN mix local.rebar --force

# Install the Phoenix framework itself
RUN wget https://github.com/phoenixframework/archives/raw/master/phoenix_new.ez
RUN mix archive.install ./phoenix_new.ez

# Install NodeJS and the NPM
#RUN curl -sL https://deb.nodesource.com/setup_14.x | bash -
#RUN apt-get install -y -q nodejs

# Suggested https://hexdocs.pm/phoenix/installation.html
RUN apt-get update && apt-get install -y \
    inotify-tools \
 && rm -rf /var/lib/apt/lists/*

# When this image is run, make /app the current working directory
WORKDIR /app

CMD mix deps.get && mix phx.server