## Build docker image

Build a new docker image:

```sh
cd packages/server
docker build -t rpi-pixel-art/server .
```

Check the newly built image to get the image ID:

```sh
docker images
```

Then:

```sh
docker tag <IMAGE ID> margaretkru/rpi-led-matrix-server:latest

docker push margaretkru/rpi-led-matrix-server:latest
```

Update the image on the server:

```sh
docker pull margaretkru/rpi-led-matrix-server
docker-compose down
docker-compose up -d
docker image prune
```

To run it locally:

```sh
docker run -p 8095:8080 -p 8990:8999 -d rpi-pixel-art/server

```
