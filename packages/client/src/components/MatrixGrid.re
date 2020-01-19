open Settings;

let pixelToCss = (~row, ~col, matrix) => {
  let coords = Coords.fromGrid(~row, ~col);
  let pixelColor =
    (matrix |> Matrix.getPixelColor(coords))
    ->Belt.Option.mapWithDefault(Settings.defaultColor, Color.colorToCss);

  Css.(
    style([
      width(px(Styles.pixelSize)),
      height(px(Styles.pixelSize)),
      backgroundColor(pixelColor),
      border(px(1), solid, black),
    ])
  );
};

[@react.component]
let make = (~matrix, ~dispatch, ~onPixelUpdate) => {
  <div>
    {Belt.Array.range(0, Dimensions.rows - 1)
     ->Belt.Array.map(row =>
         <div className="flex" key={row |> string_of_int}>
           {Belt.Array.range(0, Dimensions.cols - 1)
            ->Belt.Array.map(col =>
                <div
                  key={col |> string_of_int}
                  className={matrix |> pixelToCss(~row, ~col)}
                  onClick={_ => {
                    let coords = Coords.fromGrid(~row, ~col);
                    dispatch(State.PixelClicked(coords));
                    onPixelUpdate(coords);
                  }}
                />
              )
            ->React.array}
         </div>
       )
     ->React.array}
  </div>;
};
