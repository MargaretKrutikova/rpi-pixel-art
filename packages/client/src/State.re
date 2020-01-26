open Models;

type tool =
  | Color(Color.t)
  | Eraser;

type state = {
  matrix: Matrix.t,
  activeTool: tool,
  isDragging: bool,
};

type action =
  | ColorSelected(Color.t)
  | PixelClicked(Coords.t)
  | EraserSelected
  | MousePressed
  | MouseReleased
  | MouseMoved(Coords.t)
  | ClearMatrix;

let initialState = {
  matrix: [||],
  isDragging: false,
  activeTool: Color(Settings.initialColor),
};

let setPixelEffect = (pixel, _) => {
  Api.sendPixelToLedMatrix(MessageConverter.SetPixels([|pixel|])) |> ignore;
  None;
};

let clearPixelEffect = (coords, _) => {
  Api.sendPixelToLedMatrix(MessageConverter.ClearPixel([|coords|])) |> ignore;
  None;
};

let clearMatrixEffect = _ => {
  Api.sendPixelToLedMatrix(MessageConverter.ClearMatrix) |> ignore;
  None;
};

let setPixel = (coords, state) => {
  switch (state.activeTool) {
  | Color(color) =>
    let pixel = Pixel.make(~coords, ~color);
    let matrix = state.matrix |> Matrix.setPixel(pixel);
    ({...state, matrix}, Some(setPixelEffect(pixel)));
  | Eraser =>
    let matrix = state.matrix |> Matrix.unsetPixel(coords);
    ({...state, matrix}, Some(clearPixelEffect(coords)));
  };
};

let reducer = (state, action) =>
  switch (action) {
  | PixelClicked(coords) => setPixel(coords, state)
  | ColorSelected(color) => ({...state, activeTool: Color(color)}, None)
  | MousePressed => ({...state, isDragging: true}, None)
  | MouseReleased => ({...state, isDragging: false}, None)
  | MouseMoved(coords) =>
    state.isDragging ? setPixel(coords, state) : (state, None)
  | ClearMatrix => ({...state, matrix: [||]}, Some(clearMatrixEffect))
  | EraserSelected => ({...state, activeTool: Eraser}, None)
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
