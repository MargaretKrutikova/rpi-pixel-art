[@react.component]
let make = () => {
  let dispatch = State.Store.useDispatch();

  <>
    <main className="flex container mx-auto flex-col pb-12">
      <Header />
      <section
        className="flex flex-col items-center lg:flex-row lg:justify-between lg:items-start container mx-auto pt-12">
        <MatrixGrid />
        <div
          className="flex flex-col md:flex-row items-center lg:items-start lg:flex-col pt-8 lg:pt-0">
          <ColorPicker className="mb-4 md:mb-0 lg:mb-6" />
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
