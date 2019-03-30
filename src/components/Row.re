let component = ReasonReact.statelessComponent("Row");

let handleClick = (~event, ~ids, ~appSend) => {
  appSend(Breed.Select(ids));
  event->ReactEvent.Mouse.stopPropagation;
};

let make = (~rowInfo, ~ids, ~appSend, ~isSelected, _children) => {
  ...component,
  render: _self => {
    <div
      className={MyUtils.cssClasses([
        Styles.row,
        if (isSelected) {Styles.selected} else {""},
      ])}
      onClick={event => handleClick(~event, ~ids, ~appSend)}>
      {ReasonReact.string(rowInfo)}
    </div>;
  },
};
