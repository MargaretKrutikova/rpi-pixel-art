let connect = dispatch => {
  open WebSocket;
  let ws = WebSocketClient.make(ApiUrls.wsApi);

  let handleOpen = () => {
    Js.log(" OPEN");
    ();
  };

  let handleClose = _ => {
    Js.log("WEBSOCKET CLOSE");
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
  let handleError = _ => {
    Js.log("WEBSOCKET ERROR");
    ();
  };

  ws
  |> WebSocketClient.on @@
  Open(handleOpen)
  |> WebSocketClient.on @@
  Close(handleClose)
  |> WebSocketClient.on @@
  Message(handleMessage)
  |> WebSocketClient.on @@
  Error(handleError)
  |> ignore;
};
