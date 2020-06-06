import express from "express"
import * as http from "http"
import WebSocket from "ws"
import bodyParser from "body-parser"
import cors from "cors"
import { InMemoryMatrixState } from "./MatrixState"
import { IMatrixState, Protocol } from "./types"

const API_PORT = 8081
const WS_PORT = 8999

const app = express()
const server = http.createServer(app)
const matrixState: IMatrixState = new InMemoryMatrixState()

class WebSocketExt extends WebSocket {
  isAlive: boolean = false
  heartbeat = () => {
    this.isAlive = true
  }
}

const wss = new WebSocket.Server({ server })

wss.on("connection", (ws: WebSocketExt) => {
  ws.isAlive = true
  ws.on("pong", () => (ws.isAlive = true))
})

setInterval(() => {
  wss.clients.forEach((ws) => {
    const wsExt = ws as WebSocketExt
    if (wsExt.isAlive === false) return ws.terminate()

    wsExt.isAlive = false
    ws.ping()
  })
}, 30000)

const notifyWsClients = (message: string) => {
  wss.clients.forEach((ws: WebSocket) => {
    ws.send(message)
  })
}

server.listen(WS_PORT, () => {
  const address = server.address()
  const port = (address as WebSocket.AddressInfo).port
  console.log(`Server started on port ${port} :)`)
})

app.use(bodyParser.json()) // to support JSON-encoded bodies
app.use(
  bodyParser.urlencoded({
    // to support URL-encoded bodies
    extended: true,
  })
)
app.use(cors())

app.get("/matrix", (_, res) => {
  res.status(200).json({ matrix: matrixState.getMatrixState() })
})

app.post("/matrix", (req, res) => {
  const message: Protocol = req.body

  switch (matrixState.tryUpdateFromMessage(message)) {
    case "success": {
      res.status(200).json({ success: true })
      notifyWsClients(JSON.stringify(req.body))
      break
    }

    case "failure": {
      res.status(400).json({ success: false })
    }
  }
})

// start the Express server
app.listen(API_PORT, () => {
  console.log(`server started at http://localhost:${API_PORT}`)
})
