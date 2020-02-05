open ReasonApolloQuery;
open Models;

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://rpi-pixel-art.herokuapp.com/v1/graphql",
    (),
  );

let client =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());

let getBoardsQueryObj: ApolloClient.queryObj = {
  "query": ApolloClient.gql(. Queries.BoardsQuery.query),
  "variables": Js.Json.null,
};

let toPixel = (p): Pixel.t =>
  Pixel.make(
    ~coords=Coords.make(~x=p##coordX, ~y=p##coordY),
    ~color=Color.make(~r=p##colorR, ~g=p##colorG, ~b=p##colorB),
  );

let toMatrix = (board): Matrix.t => board##pixels->Belt.Array.map(toPixel);

let getBoard = boardName => {
  let getBoardQueryObj: ApolloClient.queryObj = {
    "query": ApolloClient.gql(. Queries.BoardQuery.query),
    "variables": Queries.BoardQuery.makeVariables(~boardName, ()),
  };

  client##query(getBoardQueryObj)
  |> Js.Promise.then_((res: renderPropObjJS) => {
       let parsedResult =
         dataGet(res)
         ->Js.Nullable.toOption
         ->Belt.Option.getExn
         ->Queries.BoardQuery.parse;

       // TODO: Handle error
       let matrix = parsedResult##boards->Belt.Array.getExn(0)->toMatrix;
       Js.log2("Matrix", matrix);
       matrix |> Js.Promise.resolve;
     });
};
