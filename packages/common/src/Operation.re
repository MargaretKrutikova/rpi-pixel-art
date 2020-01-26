type t = string;

let setPixel = "SET_PIXELS";
let clearPixel = "CLEAR_PIXELS";
let clearMatrix = "CLEAR_MATRIX";

let encode = (operation: t) => Json.Encode.string(operation);
let decode = (expected: t, json) =>
  switch (Json.Decode.string(json)) {
  | message when message == expected => expected
  | exception e => raise(e)
  | msg =>
    raise(
      Json.Decode.DecodeError(
        "Expected to receive: "
        ++ expected
        ++ " as operation value, instead received: "
        ++ msg,
      ),
    )
  };
