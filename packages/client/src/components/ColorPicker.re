open State;

let selector = (model: state) => model.selectedColor;

[@react.component]
let make = (~className="") => {
  let selectedColor = Store.useSelector(selector);
  let dispatch = Store.useDispatch();

  <div className={Cn.make(["flex flex-wrap max-w-xs self-start", className])}>
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
           onClick={_ => dispatch(ColorSelected(rgbColor))}
         />
       )
     ->React.array}
  </div>;
};
