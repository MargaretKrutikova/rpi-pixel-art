```sh
docker build -t rpi-pixel-art/server .
docker run -p 8095:8080 -p 8990:8999 -d rpi-pixel-art/server
docker images
docker tag <IMAGE ID> margaretkru/rpi-led-matrix-server:latest
docker push margaretkru/rpi-led-matrix-server:latest
```
