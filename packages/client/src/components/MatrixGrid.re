open Settings;
open State;
[@bs.val] external setTimeout: (unit => unit, int) => float = "setTimeout";

let selector = (model: state) => model.matrix;

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
let make = () => {
  let matrix = Store.useSelector(selector);
  let dispatch = Store.useDispatch();

  <div
    onMouseDown={_ => dispatch(State.MousePressed)}
    onMouseUp={_ => dispatch(MouseReleased)}>
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
                    dispatch(PixelClicked(coords));
                  }}
                  onMouseMove={_ => {
                    let coords = Coords.fromGrid(~row, ~col);
                    setTimeout(() => dispatch(MouseMoved(coords)), 0)
                    |> ignore;
                  }}
                />
              )
            ->React.array}
         </div>
       )
     ->React.array}
  </div>;
};
