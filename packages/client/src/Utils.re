open Models;

let gridPositionToCoords = (~row, ~col) => Coords.make(~x=col, ~y=row);
