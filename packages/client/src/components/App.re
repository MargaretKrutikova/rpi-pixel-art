[@react.component]
let make = () => {
  let dispatch = State.Store.useDispatch();

  <>
    <main className="flex container mx-auto flex-col">
      <Header />
      <section
        className="flex container mx-auto justify-between flex-wrap items-center pt-12">
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
      </section>
    </main>
  </>;
};
