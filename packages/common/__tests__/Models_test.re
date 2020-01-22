open Jest;
open Models;

let () =
  describe("Models", () => {
    open Expect;

    test("Coords value is encoded and decoded correctly", () => {
      let coords = Coords.make(~x=42, ~y=24);
      let json = coords |> Coords.encode;
      let decoded = json |> Coords.decode;

      expect(decoded) |> toEqual(coords);
    });

    test("Color value is encoded and decoded correctly", () => {
      let color = Color.make(~r=242, ~g=63, ~b=90);
      let json = color |> Color.encode;
      let decoded = json |> Color.decode;

      expect(decoded) |> toEqual(color);
    });

    test("Pixel value is encoded and decoded correctly", () => {
      let pixel =
        Pixel.make(
          ~color=Color.make(~r=242, ~g=63, ~b=90),
          ~coords=Coords.make(~x=34, ~y=54),
        );
      let json = pixel |> Pixel.encode;
      let decoded = json |> Pixel.decode;

      expect(decoded) |> toEqual(pixel);
    });
  });
