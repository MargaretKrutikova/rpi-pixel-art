let pixelToJson = ({coords, color}: Matrix.pixel) => {
  let payload = Js.Dict.empty();
  let {x, y}: Coords.t = coords;
  let {r, g, b}: Color.t = color;

  let intToJson = val_ => Js.Json.string(val_ |> string_of_int);
  Js.Dict.set(payload, "x", intToJson(x));
  Js.Dict.set(payload, "y", intToJson(y));
  Js.Dict.set(payload, "r", intToJson(r));
  Js.Dict.set(payload, "g", intToJson(g));
  Js.Dict.set(payload, "b", intToJson(b));

  payload |> Js.Json.object_;
};

let url = "http://localhost:8095/pixel";

let sendPixelToLedMatrix = pixel => {
  let payload = pixel |> pixelToJson |> Js.Json.stringify;
  Js.Promise.(
    Fetch.fetchWithInit(
      url,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(payload),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
  );
};
