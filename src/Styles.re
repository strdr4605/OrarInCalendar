open Css;

global(
  "html, body, ul",
  [
    margin(zero),
    padding(zero),
    color(hex("FFFFFF" /* "FFF8DC" */)),
    fontFamily("Arial, Helvetica, sans-serif"),
  ],
);
global("ul", [listStyleType(none)]);
global("li", [margin2(~v=px(1), ~h=zero)]);

let main =
  style([
    backgroundColor(hex("FFFFFF" /* "FFF8DC" */)),
    display(flexBox),
    minHeight(vh(100.)),
    maxHeight(vh(100.)),
  ]);
let column =
  style([
    padding(px(2)),
    borderRadius(px(2)),
    backgroundColor(hex("EEEEEE")),
    /* backgroundColor(hex("DCB360")), */
    width(px(100)),
    display(flexBox),
    flexDirection(column),
    margin(px(1)),
    width(px(200)),
    overflow(scroll),
  ]);
let row =
  style([
    display(flexBox),
    alignItems(center),
    height(px(34)),
    backgroundColor(hex("1991DB")),
    /* backgroundColor(hex("0B5CBC")), */
    border(px(2), solid, hex("CCCCCC")),
    /* border(px(1), solid, hex("DFD9D7")), */
    borderRadius(px(3)),
    paddingLeft(px(5)),
  ]);

let selected = style([backgroundColor(hex("07F767"))]);
