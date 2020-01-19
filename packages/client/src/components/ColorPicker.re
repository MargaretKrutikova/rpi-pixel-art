[@react.component]
let make = (~dispatch, ~selectedColor) => {
  <div className="flex flex-wrap max-w-xs self-start">
    {Settings.availableColors
     ->Belt.Array.mapWithIndex((ind, rgbColor) =>
         <div
           key={ind |> string_of_int}
           className={Cn.make([
             Css.(
               style([
                 width(px(Styles.colorSquareSize)),
                 height(px(Styles.colorSquareSize)),
                 backgroundColor(rgbColor |> Color.colorToCss),
               ])
             ),
             "border-2 mr-1 mb-1",
             Cn.ifTrue("border-gray-500 ", selectedColor != rgbColor),
             Cn.ifTrue("shadow-outline", selectedColor == rgbColor),
           ])}
           onClick={_ => dispatch(State.ColorSelected(rgbColor))}
         />
       )
     ->React.array}
  </div>;
};
