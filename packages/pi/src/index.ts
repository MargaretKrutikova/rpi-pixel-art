import { LedMatrix } from "rpi-led-matrix"
import { matrixOptions, runtimeOptions } from "./MatrixConfig"
import WebSocket from "ws"

const wait = (t: number) => new Promise(ok => setTimeout(ok, t))
;(async () => {
  try {
    const matrix = new LedMatrix(matrixOptions, runtimeOptions)
    matrix.clear().brightness(100)
    matrix.sync()
    const ws = new WebSocket("ws://192.168.1.188:8999")

    ws.onmessage = async message => {
      await draw(message.data as string)
    }

    const drawPixels = (pixels: MatrixPixel[]) => {
      console.log("REDRAWING")
      pixels.forEach(pixel => {
        matrix.fgColor(pixel.color).setPixel(pixel.x, pixel.y)
      })

      matrix.sync()
    }

    const draw = async (data: string) => {
      try {
        drawPixels(JSON.parse(data))
      } catch (error) {
        console.error(`${__filename} caught: `, error)
      }
    }

    await wait(999999999)
  } catch (error) {
    console.error(`${__filename} caught: `, error)
  }
})()

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
