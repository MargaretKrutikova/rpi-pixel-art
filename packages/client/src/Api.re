let sendPixelToLedMatrix = (protocol: MessageConverter.protocol) => {
  let payload = protocol |> MessageConverter.encode |> Js.Json.stringify;
  Js.Promise.(
    Fetch.fetchWithInit(
      ApiUrls.restApi ++ "matrix",
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

let decodeMatrix = Json.Decode.field("matrix", Matrix.decode);

let getMatrixState = (): Js.Promise.t(Matrix.t) => {
  Js.Promise.(
    Fetch.fetchWithInit(
      ApiUrls.restApi ++ "matrix",
      Fetch.RequestInit.make(
        ~method_=Get,
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => decodeMatrix(json) |> resolve)
  );
};
