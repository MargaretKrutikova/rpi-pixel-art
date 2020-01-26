type t('a) = {
  operation: Operation.t,
  data: 'a,
};

let encode = (encodeData, {operation, data}) => {
  Json.Encode.(
    object_([
      ("operation", Operation.encode(operation)),
      ("data", encodeData(data)),
    ])
  );
};

let decode = (operation, decodeData, json) =>
  Json.Decode.{
    operation: json |> field("operation", Operation.decode(operation)),
    data: json |> field("data", decodeData),
  };
