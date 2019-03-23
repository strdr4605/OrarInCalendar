let component = ReasonReact.statelessComponent("Row");

let handleClick = (~event, ~ids) => {
  let (colId, rowId) = ids;
  Js.log("c" ++ colId ++ "r" ++ rowId ++ " clicked!");
  event->ReactEvent.Mouse.stopPropagation;
};

let isSelected = ((colId, rowId)) =>
  colId == "1" && rowId == "2" || colId == "0" && rowId == "0";

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
      ])}>
      // onClick={event => handleClick(~event, ~ids)}
       {ReasonReact.string(rowInfo)} </div>;
  },
};