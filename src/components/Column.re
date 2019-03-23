let component = ReasonReact.statelessComponent("Column");

let handleClick = (~colId) => Js.log("Column " ++ colId ++ " clicked!");

let make = (~columnInfo, ~colId, /* ~selectFn, */ _children) => {
  ...component,
  render: _self => {
    let listItems =
      columnInfo
      |> List.mapi((i, rowInfo) => {
           let rowId = string_of_int(i);
           <li key={string_of_int(i)}>
             <Row ids=(colId, rowId) rowInfo />
           </li>;
         });

    <div
      className=Styles.column
      /* onClick={_event => selectFn(Main.Select((int_of_string(colId), 0)))} */
      >
      <ul> {ReasonReact.array(Array.of_list(listItems))} </ul>
    </div>;
  },
};
