import express from "express"
import * as http from "http"
import WebSocket from "ws"

const app = express()

const server = http.createServer(app)

const wss = new WebSocket.Server({ server })

interface ExtWebSocket extends WebSocket {
  isAlive?: boolean
}

wss.on("connection", (ws: ExtWebSocket) => {
  ws.isAlive = true

  ws.on("message", (message: string) => {
    console.log("received: %s", message)
    ws.send(`Hello, you sent -> ${message}`)
  })
})

setInterval(() => {
  wss.clients.forEach((ws: ExtWebSocket) => {
    if (!ws.isAlive) return ws.terminate()

    // ws.isAlive = false
    ws.ping("Are you listening?!", false)

    ws.send("Are you listening?!")
    console.log("Sending ping")
  })
}, 10000)

//start our server
server.listen(process.env.PORT || 8999, () => {
  const address = server.address()
  const port = (address as WebSocket.AddressInfo).port
  console.log(`Server started on port ${port} :)`)
})
