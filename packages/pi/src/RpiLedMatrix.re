open Models;

type t;
[@bs.module "rpi-led-matrix"] [@bs.new] external make: unit => t = "LedMatrix";
[@bs.send] external setPixel: (t, int, int) => t = "setPixel";
[@bs.send] external fgColor: (t, Color.t) => t = "fgColor";
