let url = "http://localhost:8095/matrix";

let sendPixelToLedMatrix = (protocol: MessageConverter.protocol) => {
  let payload = protocol |> MessageConverter.encode |> Js.Json.stringify;
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
