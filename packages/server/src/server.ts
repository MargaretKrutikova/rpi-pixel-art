import express from "express"
import * as http from "http"
import WebSocket from "ws"
import bodyParser from "body-parser"
import cors from "cors"

const API_PORT = 8095
const WS_PORT = 8999

const app = express()
const server = http.createServer(app)
const wss = new WebSocket.Server({ server })

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
    extended: true
  })
)
app.use(cors())

app.post("/matrix", (req, res) => {
  res.status(200).json({ success: true })
  notifyWsClients(JSON.stringify(req.body))
})

// start the Express server
app.listen(API_PORT, () => {
  console.log(`server started at http://localhost:${API_PORT}`)
})
