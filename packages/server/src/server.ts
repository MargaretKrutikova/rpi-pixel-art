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

type Color = {
  r: number
  g: number
  b: number
}

type MatrixPixel = {
  x: number
  y: number
  color: Color
}

const MATRIX_ROWS = 16
const MATRIX_COLS = 32

const getCoords = (position: number) => {
  const y = Math.floor(position / MATRIX_COLS)
  const x = position - y * MATRIX_COLS
  return { x, y }
}

const genColorValue = () => {
  const r = Math.random()
  return Math.ceil(r * 255)
}

const genColor = (): Color => ({
  r: genColorValue(),
  g: genColorValue(),
  b: genColorValue()
})

setInterval(() => {
  wss.clients.forEach((ws: ExtWebSocket) => {
    if (!ws.isAlive) return ws.terminate()

    const pixels: MatrixPixel[] = Array.from(
      new Array(MATRIX_COLS * MATRIX_ROWS).keys()
    ).map(position => {
      const coords = getCoords(position)
      return {
        x: coords.x,
        y: coords.y,
        color: genColor()
      }
    })

    ws.send(JSON.stringify(pixels))
    // ws.isAlive = false
    //ws.ping("Are you listening?!", false)

    console.log("Sending ping")
  })
}, 3000)

//start our server
server.listen(process.env.PORT || 8999, () => {
  const address = server.address()
  const port = (address as WebSocket.AddressInfo).port
  console.log(`Server started on port ${port} :)`)
})
