let component = ReasonReact.statelessComponent("Row");

let handleClick = (~event, ~rowId) => {
  Js.log("Row " ++ rowId ++ " clicked!");
  event->ReactEvent.Mouse.stopPropagation;
};

let make = (~rowInfo, ~rowId, _children) => {
  ...component,
  render: _self => {
    <div className=Styles.row onClick={event => handleClick(~event, ~rowId)}>
      {ReasonReact.string(rowInfo)}
    </div>;
  },
};
