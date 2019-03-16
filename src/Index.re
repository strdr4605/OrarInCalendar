/* type messagesType = {
     message: string,
     greeting: string,
   };

   let messages = {
     message: "Hello! Click this text.",
     greeting: "Hello!"
   }

   ReactDOMRe.renderToElementWithId(<Component1 message=(messages.message) />, "index1");

   ReactDOMRe.renderToElementWithId(<Component2 greeting=(messages.greeting) />, "index2"); */

%raw
"import css from '../../../src/style.css'";

ReactDOMRe.renderToElementWithId(<Main />, "app");
