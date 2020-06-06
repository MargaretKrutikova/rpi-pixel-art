[%bs.raw {|require("./index.css")|}];

Subscription.connect(State.Store.dispatch);

ReactDOMRe.renderToElementWithId(
  <State.Store.ElmishProvider> <App /> </State.Store.ElmishProvider>,
  "root",
);
