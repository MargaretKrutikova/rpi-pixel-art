open Client;

// TODO: Get from url
let boardName = "demo";

[@react.component]
let make = () => {
  let dispatch = State.Store.useDispatch();

  React.useEffect1(
    _ => {
      getBoard(boardName)
      |> Js.Promise.then_(res =>
           dispatch(MatrixFetched(res)) |> Js.Promise.resolve
         )
      |> ignore;
      None;
    },
    [||],
  );

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
