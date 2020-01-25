let run = (json, matrix: RpiLedMatrix.t) =>
  switch (MessageConverter.decode(json)) {
  | SetPixels(pixels) =>
    pixels->Belt.Array.reduce(matrix, (matrix, pixel) =>
      matrix
      ->RpiLedMatrix.fgColor(pixel.color)
      ->RpiLedMatrix.setPixel(pixel.coords.x, pixel.coords.y)
    )
  | ClearPixel(coords) => matrix
  | ClearMatrix => matrix
  | exception _ =>
    Js.log("Unable to decode incoming message");
    matrix;
  };
