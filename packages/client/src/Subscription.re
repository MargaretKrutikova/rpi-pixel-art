let connect = dispatch => {
  let ws = WebSocket.WebSocket.make("ws://rpi-matrix.margareta.dev/ws/");
  let handleOpen = () => {
    Js.log("OPEN");
    ();
  };
  let handleClose = evt => {
    ();
  };
  let handleMessage = evt => {
    let mag = evt |> Obj.magic;
    switch (mag##data |> Json.parse) {
    | None => ignore()
    | Some(data) =>
      let decoded = MessageConverter.decode(data);
      dispatch(State.WebSocketMsg(decoded));
      Js.log(decoded);
    };
    ();
  };
  let handleError = evt => {
    ();
  };
  WebSocket.(
    ws
    |> WebSocket.on @@
    Open(handleOpen)
    |> WebSocket.on @@
    Close(handleClose)
    |> WebSocket.on @@
    Message(handleMessage)
    |> WebSocket.on @@
    Error(handleError)
    |> ignore
  );
};
