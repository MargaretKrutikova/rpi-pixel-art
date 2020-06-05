type t;

let setPixel: t;
let clearPixel: t;
let clearMatrix: t;

let encode: t => Js.Json.t;
let decode: (t, Js.Json.t) => t;
