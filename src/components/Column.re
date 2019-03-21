let component = ReasonReact.statelessComponent("Column");

let handleClick = (~colId) => Js.log("Column " ++ colId ++ " clicked!");

let make = (~columnInfo, ~colId, _children) => {
  ...component,
  render: _self => {
    let listItems =
      columnInfo
      |> List.mapi((i, rowInfo) => {
           let rowId = colId ++ "r" ++ string_of_int(i);
           <li key={string_of_int(i)}> <Row rowId rowInfo /> </li>;
         });

    <div className=Styles.column onClick={_event => handleClick(~colId)}>
      <ul> {ReasonReact.array(Array.of_list(listItems))} </ul>
    </div>;
  },
};
