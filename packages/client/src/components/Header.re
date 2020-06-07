[@react.component]
let make = () => {
  <header className="pt-8">
    <div
      className="flex-col sm:flex-row flex items-center justify-between border-b pb-8">
      <h1
        className="text-3xl leading-tight font-sans md:text-5xl text-gray-800 text-center">
        {"Draw on my LED matrix" |> React.string}
      </h1>
      <div className="mt-4 sm:mt-0">
        <a className="mr-8 font-sans text-xl"> {React.string("Draw")} </a>
        <a className="font-sans text-xl"> {React.string("WTF")} </a>
      </div>
    </div>
  </header>;
};
