let component = ReasonReact.statelessComponent("Column");

let handleClick = (~colId) => Js.log("Column " ++ colId ++ " clicked!");

let make = (~columnInfo, ~colId, ~appSend, ~selectedRow, _children) => {
  ...component,
  render: _self => {
    let arrayItems =
      columnInfo
      |> Array.mapi((i, rowInfo) => {
           let rowId = string_of_int(i);
           <li key={string_of_int(i)}>
             <Row
               ids=(colId, rowId)
               rowInfo
               appSend
               isSelected={
                            if (i == selectedRow) {
                              true;
                            } else {
                              false;
                            }
                          }
             />
           </li>;
         });

    <div className=Styles.column>
      <ul> {ReasonReact.array(arrayItems)} </ul>
    </div>;
  },
};
