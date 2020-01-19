[@react.component]
let make = () => {
  let dispatch = State.Store.useDispatch();

  <main className="flex container mx-auto justify-between">
    <MatrixGrid />
    <ColorPicker />
    <button> {"Clear" |> React.string} </button>
  </main>;
};
