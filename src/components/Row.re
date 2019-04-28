let component = ReasonReact.statelessComponent("Row");

let handleClick = (~event, ~ids, ~appSend) => {
  appSend(Breed.Select(ids));
  event->ReactEvent.Mouse.stopPropagation;
};

let make = (~rowInfo, ~ids, ~appSend, ~isSelected, _children) => {
  ...component,
  render: _self => {
    <div
      className={Cn.make([
        Styles.row,
        Styles.selected->Cn.ifTrue(isSelected),
      ])}
      onClick={event => handleClick(~event, ~ids, ~appSend)}>
      {ReasonReact.string(rowInfo)}
    </div>;
  },
};
