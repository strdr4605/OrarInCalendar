let component = ReasonReact.statelessComponent("Column");

let handleClick = (~colId) => Js.log("Column " ++ colId ++ " clicked!");

let make = (~columnInfo, ~colId, _children) => {
  ...component,
  render: _self => {
    let arrayItems =
      columnInfo
      |> Array.mapi((i, rowInfo) => {
           let rowId = string_of_int(i);
           <li key={string_of_int(i)}>
             <Row ids=(colId, rowId) rowInfo />
           </li>;
         });

    <div className=Styles.column>
      <ul> {ReasonReact.array(arrayItems)} </ul>
    </div>;
  },
};
