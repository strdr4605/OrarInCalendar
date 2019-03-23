let component = ReasonReact.statelessComponent("Row");

let handleClick = (~event, ~ids) => {
  let (colId, rowId) = ids;
  Js.log("c" ++ colId ++ "r" ++ rowId ++ " clicked!");
  event->ReactEvent.Mouse.stopPropagation;
};

let isSelected = ids =>
  switch (ids) {
  | ("1", "1")
  | ("0", "0")
  | ("2", "0") => true
  | (_, _) => false
  };

let make = (~rowInfo, ~ids: (string, string), _children) => {
  ...component,
  render: _self => {
    <div
      className={Utils.cssClasses([
        Styles.row,
        if (isSelected(ids)) {
          Styles.selected;
        } else {
          "";
        },
      ])}
      onClick={event => handleClick(~event, ~ids)}>
      {ReasonReact.string(rowInfo)}
    </div>;
  },
};
