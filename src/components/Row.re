let component = ReasonReact.statelessComponent("Row");

let handleClick = (~event, ~ids, ~appSend) => {
  let (colId, rowId) = ids;
  Js.log("c" ++ colId ++ "r" ++ rowId ++ " clicked!");
  let intIds = (int_of_string(colId), int_of_string(rowId));
  appSend(Breed.Select(intIds));
  event->ReactEvent.Mouse.stopPropagation;
};

let make = (~rowInfo, ~ids, ~appSend, ~isSelected, _children) => {
  ...component,
  render: _self => {
    <div
      className={Utils.cssClasses([
        Styles.row,
        if (isSelected) {Styles.selected} else {""},
      ])}
      onClick={event => handleClick(~event, ~ids, ~appSend)}>
      {ReasonReact.string(rowInfo)}
    </div>;
  },
};
