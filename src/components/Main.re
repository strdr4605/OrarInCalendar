let component = ReasonReact.statelessComponent("MainComponent");

let handleClick = (_event, _self) => Js.log("clicked!");

let firstColumnInfo = ["Orar", "Despre", "Contact"];

let make = _children => {
  ...component,
  render: _self =>
    <div className="Main"> {ReasonReact.string("Main")} <Column listInfo=firstColumnInfo /> </div>,
};
