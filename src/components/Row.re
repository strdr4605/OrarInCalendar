let component = ReasonReact.statelessComponent("Row");

let handleClick = (~event, ~ids, ~selectAction) => {
  let (colId, rowId) = ids;
  Js.log("c" ++ colId ++ "r" ++ rowId ++ " clicked!");
  selectAction((int_of_string(colId), int_of_string(rowId)));
  event->ReactEvent.Mouse.stopPropagation;
};

let make = (~rowInfo, ~ids, ~selectAction, ~isSelected, _children) => {
  ...component,
  render: _self => {
    <div
      className={Utils.cssClasses([
        Styles.row,
        if (isSelected) {
          Styles.selected;
        } else {
          "";
        },
      ])}
      onClick={event => handleClick(~event, ~ids, ~selectAction)}>
      {ReasonReact.string(rowInfo)}
    </div>;
  },
};
