[@bs.val]
external unsafeParseInt: (string, int) => Js.Null.t(float) = "parseInt";

type t = {
  r: int,
  g: int,
  b: int,
};

let make = (~r, ~g, ~b) => {r, g, b};

let stringToHex = string => {
  let radix = 16;
  unsafeParseInt(string, radix)
  ->Js.Null.toOption
  ->Belt.Option.map(result =>
      switch (result->Js.Float.isNaN) {
      | false => Some(result->int_of_float)
      | _ => None
      }
    )
  ->Belt.Option.flatMap(res => res);
};

let hexToRgb = (hex): option(t) => {
  let parse = (ind, array) =>
    array
    ->Belt.Array.get(ind)
    ->Belt.Option.map(stringToHex)
    ->Belt.Option.flatMap(res => res);

  let parseColor = array => {
    switch (array |> parse(1), array |> parse(2), array |> parse(3)) {
    | (Some(r), Some(g), Some(b)) => {r, g, b}->Some
    | _ => None
    };
  };

  let regex = [%re "/^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i"];
  (hex |> Js.String.match(regex))
  ->Belt.Option.map(parseColor)
  ->Belt.Option.flatMap(res => res);
};

let cssToColor = (color: Css.Types.Color.t) => {
  switch (color) {
  | `hex(str) => hexToRgb(str)
  | _ => None
  };
};

let colorToCss = ({r, g, b}) => `rgb((r, g, b));
