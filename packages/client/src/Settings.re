open Models;

let addColor = (color, array) => {
  switch (color |> ColorUtils.cssToColor) {
  | Some(rgb) => array->Belt.Array.concat([|rgb|])
  | None => array
  };
};

let initialColor = Color.make(~r=255, ~g=0, ~b=0);
let defaultColor = Css.lightgray;

let availableColors: array(Color.t) =
  Css.(
    [||]
    |> addColor(red)
    |> addColor(green)
    |> addColor(blue)
    |> addColor(orange)
    |> addColor(yellow)
    |> addColor(purple)
    |> addColor(brown)
    |> addColor(beige)
    |> addColor(teal)
    |> addColor(black)
    |> addColor(white)
  );

module Dimensions = {
  let rows = 16;
  let cols = 32;
};
