[@react.component]
let make = () => {
  let dispatch = State.Store.useDispatch();

  <main className="flex container mx-auto justify-between">
    <MatrixGrid />
    <div className="flex flex-col items-start ">
      <ColorPicker className="mb-6" />
      <div className="flex justify-between">
        <div className="mr-4"> <Eraser /> </div>
        <Button onClick={_ => dispatch(State.ClearMatrix)}>
          {"Clear" |> React.string}
        </Button>
      </div>
    </div>
  </main>;
};
