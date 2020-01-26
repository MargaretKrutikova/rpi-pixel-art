export type Color = {
  r: number
  g: number
  b: number
}

export type Coords = {
  x: number
  y: number
}

export type Pixel = {
  coords: Coords
  color: Color
}

type Operation = "SET_PIXELS" | "CLEAR_PIXELS" | "CLEAR_MATRIX"

type Message<T, O extends Operation> = {
  operation: O
  data: T
}

export type SetPixelsData = ReadonlyArray<Pixel>
export type ClearPixelsData = ReadonlyArray<Coords>

export type Protocol =
  | Message<SetPixelsData, "SET_PIXELS">
  | Message<ClearPixelsData, "CLEAR_PIXELS">
  | Message<void, "CLEAR_MATRIX">
