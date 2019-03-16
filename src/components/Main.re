let component = ReasonReact.statelessComponent("MainComponent");

let handleClick = (_event, _self) => Js.log("clicked!");

let firstColumnInfo = ["Orar", "Despre", "Contact"];

let make = _children => {
  ...component,
  render: _self => <div> {ReasonReact.string("Main")} <Column info=firstColumnInfo /> </div>,
};
