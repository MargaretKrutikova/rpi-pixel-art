open Models;

type protocol =
  | SetPixel(Pixel.t)
  | ClearPixel(Coords.t)
  | ClearMatrix;

module type MsgConfig = {
  include Serializable;
  let operation: Operation.t;
  let toProtocol: t => protocol;
};

module ProtocolMsg =
       (Config: MsgConfig)
       : {
         type t = Message.t(Config.t);
         let make: Config.t => t;

         let encode: t => Js.Json.t;
         let decode: Js.Json.t => protocol;
       } => {
  type t = Message.t(Config.t);
  let make = (data): t => {operation: Config.operation, data};

  let encode = (msg: t) => msg |> Message.encode(Config.encode);
  let decode = (json): protocol => {
    let msg = json |> Message.decode(Config.operation, Config.decode);
    Config.toProtocol(msg.data);
  };
};

module SetPixelMessage =
  ProtocolMsg({
    include Pixel;
    let operation = Operation.setPixel;
    let toProtocol = data => SetPixel(data);
  });

module ClearPixelMessage =
  ProtocolMsg({
    include Coords;
    let operation = Operation.clearPixel;
    let toProtocol = data => ClearPixel(data);
  });

module ClearMatrixMessage =
  ProtocolMsg({
    type t = unit;
    let encode = () => Js.Json.object_(Js.Dict.empty());
    let decode = _ => ();
    let toProtocol = () => ClearMatrix;
    let operation = Operation.clearMatrix;
  });

let encode = msg =>
  switch (msg) {
  | SetPixel(data) => SetPixelMessage.make(data) |> SetPixelMessage.encode
  | ClearPixel(data) =>
    ClearPixelMessage.make(data) |> ClearPixelMessage.encode
  | ClearMatrix => ClearMatrixMessage.make() |> ClearMatrixMessage.encode
  };

let decode = json =>
  json
  |> Json.Decode.oneOf([
       SetPixelMessage.decode,
       ClearPixelMessage.decode,
       ClearMatrixMessage.decode,
     ]);
