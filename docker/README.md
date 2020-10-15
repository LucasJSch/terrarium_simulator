# Docker

## Build the image

1. Install docker. If you are using Ubuntu 18.04 you can follow these steps:

```bash
sudo apt-get update
sudo apt-get remove docker docker-engine docker.io
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker
```

To check the installation, run:

```bash
docker run hello-world
```

2. Build the image. Assuming `{REPO_PATH}` as the base repository path, run:

```bash
cd {REPO_PATH}/docker
./build.sh
```

## Run the container

To run the container, execute:

```bash
cd {REPO_PATH}/docker
./run.sh
```

You should see that the prompt is inside the _course_ folder.
