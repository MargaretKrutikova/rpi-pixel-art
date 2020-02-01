module Color = {
  type t = {
    r: int,
    g: int,
    b: int,
  };
  let make = (~r, ~g, ~b) => {r, g, b};

  let decode = json =>
    Json.Decode.{
      r: json |> field("r", int),
      g: json |> field("g", int),
      b: json |> field("b", int),
    };

  let encode = ({r, g, b}) => {
    Json.Encode.(
      object_([("r", int(r)), ("g", int(g)), ("b", int(b))])
    );
  };
};

module Coords = {
  type t = {
    x: int,
    y: int,
  };
  let make = (~x, ~y) => {x, y};

  let decode = json =>
    Json.Decode.{x: json |> field("x", int), y: json |> field("y", int)};

  let encode = ({x, y}) => {
    Json.Encode.(object_([("x", int(x)), ("y", int(y))]));
  };
};

module Pixel = {
  type t = {
    coords: Coords.t,
    color: Color.t,
  };

  let make = (~coords, ~color) => {coords, color};

  let decode = json =>
    Json.Decode.{
      coords: json |> field("coords", Coords.decode),
      color: json |> field("color", Color.decode),
    };

  let encode = ({coords, color}) => {
    Json.Encode.(
      object_([
        ("coords", Coords.encode(coords)),
        ("color", Color.encode(color)),
      ])
    );
  };
};
