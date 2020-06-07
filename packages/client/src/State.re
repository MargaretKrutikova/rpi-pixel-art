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
  | SetInitMatrix(Matrix.t)
  | ColorSelected(Color.t)
  | PixelClicked(Coords.t)
  | EraserSelected
  | MousePressed
  | MouseReleased
  | MouseMoved(Coords.t)
  | ClearMatrix
  | WebSocketMsg(MessageConverter.protocol);

type effect = ReasonReactElmish.Elmish.effect(action);

let initialState = {
  matrix: [||],
  isDragging: false,
  activeTool: Color(Settings.initialColor),
};

let initEffect = dispatch => {
  Api.getMatrixState()
  |> Js.Promise.(
       then_(matrix => SetInitMatrix(matrix) |> dispatch |> resolve)
     )
  |> ignore;
  None;
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

let drawColor = (color, coords, matrix) => {
  let pixel = Pixel.make(~coords, ~color);
  matrix |> Matrix.setPixel(pixel);
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

let processWebSocketMessage = (msg: MessageConverter.protocol, state) =>
  switch (msg) {
  | SetPixels(data) =>
    let matrix =
      data->Belt.Array.reduce(state.matrix, (matrix, pixel) =>
        Matrix.setPixel(pixel, matrix)
      );
    ({...state, matrix}, None);
  | ClearPixel(data) =>
    let matrix =
      data->Belt.Array.reduce(state.matrix, (matrix, pixel) =>
        Matrix.unsetPixel(pixel, matrix)
      );
    ({...state, matrix}, None);
  | ClearMatrix => ({...state, matrix: Matrix.empty()}, None)
  };

let reducer = (state, action): (state, option(effect)) =>
  switch (action) {
  | SetInitMatrix(matrix) => ({...state, matrix}, None)
  | PixelClicked(coords) => setPixel(coords, state)
  | ColorSelected(color) => ({...state, activeTool: Color(color)}, None)
  | MousePressed => ({...state, isDragging: true}, None)
  | MouseReleased => ({...state, isDragging: false}, None)
  | MouseMoved(coords) =>
    state.isDragging ? setPixel(coords, state) : (state, None)
  | ClearMatrix => (
      {...state, matrix: Matrix.empty()},
      Some(clearMatrixEffect),
    )
  | EraserSelected => ({...state, activeTool: Eraser}, None)
  | WebSocketMsg(msg) => processWebSocketMessage(msg, state)
  };

module Store = {
  include ReasonReactElmish.Elmish.Make({
    type model = state;
    type message = action;

    let update = reducer;
    let storeEnhancer = None;
    let initialModel = (initialState, Some(initEffect));
  });
};
