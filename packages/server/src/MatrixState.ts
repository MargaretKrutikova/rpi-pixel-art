import {
  IMatrixState,
  Matrix,
  SetPixelsData,
  ClearPixelsData,
  Pixel,
  Coords,
  Protocol,
  UpdateMessageResult,
} from "./types"

const equalCoords = (coordLeft: Coords, coordRight: Coords) =>
  coordLeft.x === coordRight.x && coordLeft.y === coordRight.y

const getPixel = (coords: Coords, matrix: Matrix): Pixel | undefined =>
  matrix.find((pixel) => equalCoords(pixel.coords, coords))

const unsetPixel = (matrix: Matrix, coords: Coords) => {
  const pixel = getPixel(coords, matrix)
  return pixel
    ? matrix.filter((pixel) => !equalCoords(pixel.coords, coords))
    : matrix
}

const setPixel = (matrix: Matrix, newPixel: Pixel) => {
  const existingPixel = getPixel(newPixel.coords, matrix)
  if (existingPixel) {
    return matrix.map((pixel) =>
      equalCoords(pixel.coords, newPixel.coords) ? newPixel : pixel
    )
  } else {
    return [...matrix, newPixel]
  }
}

export class InMemoryMatrixState implements IMatrixState {
  private state: Matrix = []

  getMatrixState = () => {
    return [...this.state]
  }

  tryUpdateFromMessage = (message: Protocol): UpdateMessageResult => {
    try {
      switch (message.operation) {
        case "SET_PIXELS":
          this.setPixels(message.data)
          return "success"

        case "CLEAR_PIXELS":
          this.clearPixels(message.data)
          return "success"

        case "CLEAR_MATRIX":
          this.clearMatrix()
          return "success"

        default:
          const operation = (message as any).operation
          console.log(`Unknown operation format: ${operation}`)
          return "failure"
      }
    } catch (error) {
      console.error(`${__filename} caught: `, error)
      return "failure"
    }
  }
  private clearMatrix = () => {
    this.state = []
  }
  private clearPixels = (data: ClearPixelsData) => {
    const newState = data.reduce(unsetPixel, this.state)
    this.state = newState
  }
  private setPixels = (data: SetPixelsData) => {
    const newState = data.reduce(setPixel, this.state)
    this.state = newState
  }
}
