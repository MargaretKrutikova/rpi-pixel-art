open Jest;
open MessageConverter;
open Models;

let () =
  describe("MessageConverter", () => {
    Expect.(
      test("Protocol value is encoded and decoded correctly", () => {
        let pixels: setPixelsData = [|
          {
            color: Color.make(~r=23, ~g=56, ~b=55),
            coords: Coords.make(~x=34, ~y=35),
          },
        |];
        let protocol = SetPixels(pixels);
        let json = protocol |> encode;
        let decoded = json |> decode;

        expect(decoded) |> toEqual(protocol);
      })
    )
  });
