open Models;

type state = {
  selectedColor: Color.t,
  matrix: Matrix.t,
  isDragging: bool,
};

type action =
  | ColorSelected(Color.t)
  | PixelClicked(Coords.t)
  | MousePressed
  | MouseReleased
  | MouseMoved(Coords.t)
  | ClearMatrix;

let initialState = {
  selectedColor: Settings.initialColor,
  matrix: [||],
  isDragging: false,
};

let setPixelEffect = (pixel, _) => {
  Api.sendPixelToLedMatrix(pixel) |> ignore;
  None;
};

let clearMatrixEffect = _ => {
  None;
};

let setPixel = (coords, state) => {
  let pixel = Pixel.make(~coords, ~color=state.selectedColor);
  let matrix = state.matrix |> Matrix.setPixel(pixel);
  ({...state, matrix}, Some(setPixelEffect(pixel)));
};

let reducer = (state, action) =>
  switch (action) {
  | PixelClicked(coords) => setPixel(coords, state)
  | ColorSelected(color) => ({...state, selectedColor: color}, None)
  | MousePressed => ({...state, isDragging: true}, None)
  | MouseReleased => ({...state, isDragging: false}, None)
  | MouseMoved(coords) =>
    state.isDragging ? setPixel(coords, state) : (state, None)
  | ClearMatrix => ({...state, matrix: [||]}, Some(clearMatrixEffect))
  };

module Store = {
  include ReasonReactElmish.Elmish.Make({
    type model = state;
    type message = action;

    let update = reducer;
    let storeEnhancer = None;
    let initialModel = (initialState, None);
  });
};
