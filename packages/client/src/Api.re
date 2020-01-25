open Models;

let url = "http://localhost:8095/pixel";

let sendPixelToLedMatrix = pixel => {
  let payload = pixel |> Pixel.encode |> Js.Json.stringify;
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
