FROM elixir:latest

# Install required packages
RUN apt-get update && \
    apt-get install -y postgresql-client inotify-tools && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install Elixir dependencies
RUN mix local.hex --force && \
    mix archive.install hex phx_new 1.5.3 --force && \
    mix local.rebar --force

# Set environment variables
ENV APP_HOME /app

# Create and set the working directory
RUN mkdir -p $APP_HOME
WORKDIR $APP_HOME

# Copy the application code
COPY . $APP_HOME

# Install application dependencies
RUN mix deps.get

# Expose the Phoenix server port
EXPOSE 4000

# Start the Phoenix server
CMD ["mix", "phx.server"]
