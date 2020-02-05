module BoardsQuery = [%graphql
  {|
    query BoardsQuery {
      boards {
        id
        name
      }
    }
  |}
];

module BoardQuery = [%graphql
  {|
    query Boards($boardName: String!)
      {
        boards(where: { name: { _eq: $boardName }})
          {
            id
            name
            pixels
              {
                coordX
                coordY
                colorR
                colorG
                colorB
              }
          }
      }
  |}
];

// mutation UpdatePixel {
//   update_pixels(where: {_and: [
//     {board: {name: {_eq: "demo"}}}
//     {coordX: {_eq: 0}}
//     {coordY: {_eq: 1}}
//   ]}
//   _set: {colorR:255}
//   )
//   {
//     affected_rows
//   }
// }
// mutation AddPixels {
//   insert_pixels(objects:
//     [
//     {coordX: 0, coordY: 2, colorR: 0, colorG: 0, colorB: 255, board: {data: {name: "demo"}, on_conflict: {constraint: boards_name_key, update_columns: name}}}
//     {coordX: 0, coordY: 3, colorR: 0, colorG: 128, colorB: 128, board: {data: {name: "demo"}, on_conflict: {constraint: boards_name_key, update_columns: name}}}
//     ]
//   ) {
//     affected_rows
//   }
// }
// mutation AddPixel {
//   insert_pixels(objects: {coordX: 0, coordY: 1, colorR: 0, colorG: 255, colorB: 0, board: {data: {name: "demo"}, on_conflict: {constraint: boards_name_key, update_columns: name}}}) {
//     affected_rows
//   }
