[%bs.raw {|require("./index.css")|}];

open Client;

ReactDOMRe.renderToElementWithId(
  <ApolloHooks.Provider client>
    <State.Store.ElmishProvider> <App /> </State.Store.ElmishProvider>
  </ApolloHooks.Provider>,
  "root",
);
