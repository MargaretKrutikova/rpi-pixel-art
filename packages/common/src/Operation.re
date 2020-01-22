type t = string;

let setPixel = "SET_PIXEL";
let clearPixel = "CLEAR_PIXEL";
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
