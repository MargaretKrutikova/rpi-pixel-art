[%bs.raw {|require("./index.css")|}];

/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://rpi-pixel-art.herokuapp.com/v1/graphql",
    (),
  );

let client =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());

ReactDOMRe.renderToElementWithId(
  <ApolloHooks.Provider client>
    <State.Store.ElmishProvider> <App /> </State.Store.ElmishProvider>
  </ApolloHooks.Provider>,
  "root",
);
