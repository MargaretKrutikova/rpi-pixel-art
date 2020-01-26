let encodeArray = (encode, array: array('a)) =>
  array->Belt.Array.map(encode)->Js.Json.array;

let decodeArray = (decode, json) =>
  Js.Json.decodeArray(json)
  ->Belt.Option.mapWithDefault([||], array => array->Belt.Array.map(decode));
