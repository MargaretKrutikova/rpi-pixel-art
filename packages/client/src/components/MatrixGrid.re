open Settings;
open State;

[@react.component]
let make = () => {
  let dispatch = Store.useDispatch();
  <div
    className="border-2 border-gray-800"
    onMouseDown={_ => dispatch(MousePressed)}
    onMouseUp={_ => dispatch(MouseReleased)}>
    {Belt.Array.range(0, Dimensions.rows - 1)
     ->Belt.Array.map(row =>
         <div className="flex" key={row |> string_of_int}>
           {Belt.Array.range(0, Dimensions.cols - 1)
            ->Belt.Array.map(col =>
                <PixelCell key={col |> string_of_int} row col />
              )
            ->React.array}
         </div>
       )
     ->React.array}
  </div>;
};
