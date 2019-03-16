let component = ReasonReact.statelessComponent("Row");

let handleClick = (event, _self) => {
  Js.log("Row clicked!");
  event->ReactEvent.Mouse.stopPropagation;
};

let make = (~rowInfo, _children) => {
  ...component,
  render: self => {
    <div className="Row" onClick={self.handle(handleClick)}> {ReasonReact.string(rowInfo)} </div>;
  },
};
