let component = ReasonReact.statelessComponent("Column");

let make = (~columnInfo, ~colId, ~appSend, ~selectedRow, _children) => {
  ...component,
  ReasonReact.render: _self => {
    let arrayItems =
      columnInfo
      |> Array.mapi((i, rowInfo) =>
           <li key={string_of_int(i)}>
             <Row
               ids=(colId, i)
               rowInfo
               appSend
               isSelected={i == selectedRow}
             />
           </li>
         );
    <div className=Styles.column>
      <ul> {ReasonReact.array(arrayItems)} </ul>
    </div>;
  },
};
