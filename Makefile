# Docker image name
DOCKER_IMAGE =  corecpp2023

# Docker container name
DOCKER_CONTAINER = corecpp2023-container

.PHONY: all build run clean

all: build

# Build target - builds the Docker image
build:
	docker build -t $(DOCKER_IMAGE) .

# Run target - runs a Docker container and mounts the current directory as /workdir
run:
	docker run -it --rm -v $(PWD):/workdir --name $(DOCKER_CONTAINER) $(DOCKER_IMAGE)

# Clean target - removes the Docker container and image
clean:
	docker stop $(DOCKER_CONTAINER) >/dev/null 2>&1 || true
	docker rm $(DOCKER_CONTAINER) >/dev/null 2>&1 || true
	docker rmi $(DOCKER_IMAGE) >/dev/null 2>&1 || true