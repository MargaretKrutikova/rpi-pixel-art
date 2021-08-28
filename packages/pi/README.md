# Options for the demo

`examples-api-use`

`--led-rows 16 --led-cols 32 --led-gpio-mapping=adafruit-hat`

# Demos

sudo ./demo --led-brightness=50 -D 0

sudo ./demo --led-brightness=50 -D 4

sudo ./demo --led-brightness=50 -D 5

sudo ./demo --led-brightness=50 -D 6

## Conway's game of life

`sudo ./demo --led-brightness=50 -D 7`

## Volume bars

`sudo ./demo --led-brightness=50 -D 9`

## Evolution of color

`sudo ./demo --led-brightness=50 -D 10`

## Brightness pulse generator

`sudo ./demo --led-brightness=30 -D 11`

# Other examples

## Clock:

```c
  matrix_options.rows = 16;
  matrix_options.cols = 32;
  matrix_options.hardware_mapping = "adafruit-hat";
```

`sudo ./clock -f ../fonts/6x13B.bdf -y 1 -x 1 -d "%H:%M" --led-brightness=50`

# Utils

## Scrolling text

`sudo ./text-scroller -f ../fonts/9x18.bdf -C150,150,150 -y -2 -s 3 "The quick brown fox jumps over the lazy dog"`

Variation: `sudo ./text-scroller -f ../fonts/7x13B.bdf -C150,150,150 -s 3 "The quick brown fox jumps over the lazy dog"`

## Image viewer

Copy files from mac to pi

```
scp source  pi@192.168.1.151:images/file.name
```

Two mario figures walk: `sudo ./led-image-viewer --led-brightness=50 ../../images/walk.gif`

Cube animation: `sudo ./led-image-viewer --led-rows 32 --led-brightness=50 ../../images/cube.gif`

# Custom example
