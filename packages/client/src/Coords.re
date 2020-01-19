type t = {
  x: int,
  y: int,
};

let make = (~x, ~y) => {x, y};
let fromGrid = (~row, ~col) => {x: col, y: row};

let areEqual = (left, right) => left.x == right.x && left.y == right.y;
