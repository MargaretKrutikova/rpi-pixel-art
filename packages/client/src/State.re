type state = {
  selectedColor: Color.t,
  matrix: Matrix.t,
};

type action =
  | ColorSelected(Color.t)
  | PixelClicked(Coords.t);

let initialState = {selectedColor: Settings.initialColor, matrix: [||]};

let reducer = (state, action) =>
  switch (action) {
  | PixelClicked(coords) =>
    let matrix =
      state.matrix |> Matrix.setPixel({coords, color: state.selectedColor});
    {...state, matrix};
  | ColorSelected(color) => {...state, selectedColor: color}
  };
