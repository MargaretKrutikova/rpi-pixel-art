open State;

let pixelToCss = color => {
  let pixelColor =
    color->Belt.Option.mapWithDefault(
      Settings.defaultColor,
      ColorUtils.colorToCss,
    );

  Css.(
    style([
      width(px(Styles.pixelSize)),
      height(px(Styles.pixelSize)),
      backgroundColor(pixelColor),
      border(px(1), solid, rgb(240, 240, 240)),
    ])
  );
};

[@react.component]
let make = (~row, ~col) => {
  let selector =
    React.useCallback2(
      (state: state) =>
        state.matrix
        |> Matrix.getPixelColor(Utils.gridPositionToCoords(~row, ~col)),
      (row, col),
    );
  let coords = Utils.gridPositionToCoords(~row, ~col);
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
