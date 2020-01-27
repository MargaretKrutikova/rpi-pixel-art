import { LedMatrix } from "rpi-led-matrix"
import WebSocket from "ws"

import { matrixOptions, runtimeOptions } from "./MatrixConfig"
import { Protocol, SetPixelsData, ClearPixelsData } from "./Types"

const wait = (t: number) => new Promise(ok => setTimeout(ok, t))
;(async () => {
  try {
    const matrix = new LedMatrix(matrixOptions, runtimeOptions)
    matrix.clear().brightness(100)
    matrix.sync()
    const ws = new WebSocket("ws://rpi-matrix.margareta.dev/ws/", undefined, {
      followRedirects: true
    } as any)

    ws.onmessage = async message => {
      await draw(message.data as string)
    }

    const drawPixels = (pixels: SetPixelsData) => {
      console.log("SETTING PIXELS")
      pixels.forEach(({ color, coords }) =>
        matrix.fgColor(color).setPixel(coords.x, coords.y)
      )
      matrix.sync()
    }

    const clearPixels = (pixels: ClearPixelsData) => {
      console.log("CLEARING PIXELS")
      pixels.forEach(({ x, y }) => matrix.clear(x, y, x, y))
      matrix.sync()
    }

    const clearMatrix = () => {
      console.log("CLEARING MATRIX")
      matrix.clear()
      matrix.sync()
    }

    const draw = async (data: string) => {
      try {
        const protocol: Protocol = JSON.parse(data)
        console.log(data)
        switch (protocol.operation) {
          case "SET_PIXELS":
            drawPixels(protocol.data)
            return
          case "CLEAR_PIXELS":
            clearPixels(protocol.data)
            return
          case "CLEAR_MATRIX":
            clearMatrix()
            return
          default:
            const operation = (protocol as any).operation
            throw new Error(`Unknown operation format: ${operation}`)
        }
      } catch (error) {
        console.error(`${__filename} caught: `, error)
      }
    }

    await wait(999999999)
  } catch (error) {
    console.error(`${__filename} caught: `, error)
  }
})()
