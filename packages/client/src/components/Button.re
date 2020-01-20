[@react.component]
let make = (~onClick=?, ~children) => {
  <button
    ?onClick
    className="bg-teal-600 hover:bg-teal-500 text-white tracking-wider py-2 px-4 border-b-4 border-teal-800 hover:border-teal-600 rounded">
    children
  </button>;
};
