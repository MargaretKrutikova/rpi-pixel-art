[@react.component]
let make = () => {
  let dispatch = State.Store.useDispatch();

  <main className="flex container mx-auto justify-between">
    <MatrixGrid />
    <div className="flex flex-col items-start ">
      <ColorPicker className="mb-6" />
      <Eraser onClick={_ => dispatch(State.EraserSelected)} />
      <Button onClick={_ => dispatch(State.ClearMatrix)}>
        {"Clear" |> React.string}
      </Button>
    </div>
  </main>;
};
