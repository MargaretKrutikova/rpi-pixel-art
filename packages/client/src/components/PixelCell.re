open State;

let pixelToCss = color => {
  let pixelColor =
    color->Belt.Option.mapWithDefault(
      Settings.defaultColor,
      Color.colorToCss,
    );

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
let make = (~row, ~col) => {
  let selector =
    React.useCallback2(
      (state: state) =>
        state.matrix |> Matrix.getPixelColor(Coords.fromGrid(~row, ~col)),
      (row, col),
    );
  let coords = Coords.fromGrid(~row, ~col);
  let dispatch = Store.useDispatch();
  let color = Store.useSelector(selector);

  <div
    key={col |> string_of_int}
    className={pixelToCss(color)}
    onClick={_ => dispatch(PixelClicked(coords))}
    onMouseOver={e => {
      ReactEvent.Mouse.preventDefault(e);
      dispatch(MouseMoved(coords));
    }}
  />;
};
