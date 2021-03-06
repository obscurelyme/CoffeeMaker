# CoffeeMaker Docs

### Detecting Memory Leaks

I use [Dr. Memory](https://drmemory.org/) in order to find memory leaks for this project.
I've found that using Dr. Memory as is can be quite slow. So I use the following options to limit the scope to just
finding memory leaks.

```bash
drmemory -leaks_only -- path/to/exe
```

### Docker

I created a [docker image](https://hub.docker.com/r/obscurelyme/coffeemaker) that contains a basic developer environment needed to build this project. This image is pulled in for CI/CD purposes but it can also be used in conjunction with a local setup in case you do not want to install all of the developer tools on your machine directly.

```bash
docker pull obscurelyme/coffeemaker

docker run -i -t obscurelyme/coffeemaker /bin/bash

git clone https://github.com/obscurelyme/CoffeeMaker.git
```

Once you've done this once, you can rename the container to whatever you wish on your local docker installation.

```
docker container rename [GENERATED_NAME] [NAME_YOU_WANT]
```

Once you've done that, subsequent runs of the container would look like...

```
docker start -i [CONTAINER_NAME]
```

I recommend that you have the [Docker extension](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker) installed if working with VS Code.

To push any updates

```
docker push obscurelyme/coffeemaker:latest
```

# Linux with SDL2-Mixer

To leverage SDL2-Mixer

```sh
sudo apt install libmpg123-dev
```

# Assets

Assets can be copy overed from [Google Drive](https://drive.google.com/drive/folders/1p6DR6DBM-Piak81ub66MXonAL9pEK6e4?usp=sharing)
They should not be commited to version control.
