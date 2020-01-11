import {
  GpioMapping,
  LedMatrix,
  MatrixOptions,
  RuntimeOptions
} from "rpi-led-matrix"

export const matrixOptions: MatrixOptions = {
  ...LedMatrix.defaultMatrixOptions(),
  rows: 16,
  cols: 32,
  chainLength: 1,
  hardwareMapping: GpioMapping.AdafruitHat,
  parallel: 1
}

export const runtimeOptions: RuntimeOptions = {
  ...LedMatrix.defaultRuntimeOptions()
}
