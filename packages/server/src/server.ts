import express from "express"
import * as http from "http"
import WebSocket from "ws"
import bodyParser from "body-parser"
import cors from "cors"

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

const sendPixel = (pixel: MatrixPixel) => {
  const pixels = [pixel]
  wss.clients.forEach((ws: ExtWebSocket) => {
    ws.send(JSON.stringify(pixels))
  })
}

//start our server
server.listen(process.env.PORT || 8999, () => {
  const address = server.address()
  const port = (address as WebSocket.AddressInfo).port
  console.log(`Server started on port ${port} :)`)
})

//---------------------------------------------------

const port = 8095 // default port to listen

// define a route handler for the default home page
app.get("/", (_, res) => {
  res.send("Hello world!")
})

app.use(bodyParser.json()) // to support JSON-encoded bodies
app.use(
  bodyParser.urlencoded({
    // to support URL-encoded bodies
    extended: true
  })
)
app.use(cors())

app.post("/pixel", (req, res) => {
  const pixel: MatrixPixel = {
    x: parseInt(req.body.x),
    y: parseInt(req.body.y),
    color: {
      r: parseInt(req.body.r),
      g: parseInt(req.body.g),
      b: parseInt(req.body.b)
    }
  }

  console.log(pixel)
  res.status(200).json({ success: true })
  sendPixel(pixel)
})

// start the Express server
app.listen(port, () => {
  console.log(`server started at http://localhost:${port}`)
})
