open ApolloHooks;
open Queries;

[@react.component]
let make = () => {
  let (boardsQuery, _) = useQuery(BoardsQuery.definition);

  <div>
    {switch (boardsQuery) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       <div>
         {data##boards
          ->Belt.Array.map(b => <div> {React.string(b##name)} </div>)
          ->React.array}
       </div>
     | NoData
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
  </div>;
};
