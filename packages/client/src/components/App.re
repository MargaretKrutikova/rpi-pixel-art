[@react.component]
let make = () => {
  <main className="flex container mx-auto justify-between">
    <MatrixGrid />
    <div className="flex flex-col items-start ">
      <ColorPicker className="mb-6" />
      <Button> {"Clear" |> React.string} </Button>
    </div>
  </main>;
};
