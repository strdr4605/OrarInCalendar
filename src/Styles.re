open Css;

global("html, body, ul", [margin(zero), padding(zero), color(white)]);
global("ul", [listStyleType(none)]);
global("li", [margin2(~v=px(1), ~h=zero)]);

let main = style([backgroundColor(hex("00BCEA")), display(flexBox), minHeight(vh(100.))]);
let column =
  style([
    padding(px(2)),
    backgroundColor(hex("F4ED7C")),
    width(px(100)),
    display(flexBox),
    flexDirection(column),
    margin(px(1)),
  ]);
let row =
  style([
    display(flexBox),
    alignItems(center),
    height(px(27)),
    backgroundColor(hex("F95E59")),
    border(px(2), solid, hex("DD4C39")),
    borderRadius(px(3)),
    paddingLeft(px(5)),
  ]);
