open Models;

type t = array(Pixel.t);

let getPixel = (coords, matrix: t) => {
  matrix->Belt.Array.keep(pixel => coords == pixel.coords)->Belt.Array.get(0);
};

let getPixelColor = (coords, matrix: t) =>
  (matrix |> getPixel(coords))->Belt.Option.map(pixel => pixel.color);

let unsetPixel = (coords, matrix: t) =>
  switch (matrix |> getPixel(coords)) {
  | None => matrix
  | Some(pixel) => matrix->Belt.Array.keep(p => p.coords != pixel.coords)
  };

let setPixel = (pixel: Pixel.t, matrix) => {
  switch (matrix |> getPixel(pixel.coords)) {
  | None => matrix->Belt.Array.concat([|pixel|])
  | Some(p) =>
    if (p.color === pixel.color) {
      matrix;
    } else {
      matrix
      ->Belt.Array.keep(p => p.coords != pixel.coords)
      ->Belt.Array.concat([|pixel|]);
    }
  };
};

let empty = (): t => [||];

let decode = JsonUtils.decodeArray(Pixel.decode);
