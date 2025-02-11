# Base image
FROM gcc:11.3.0

# Set workdir
WORKDIR /app

# Copy source files to the container
COPY src /app/src
COPY Makefile docker_task.sh /app

# Set container run command
CMD ["./docker_task.sh"]
