let component = ReasonReact.statelessComponent("MainComponent");

let handleClick = (_event, _self) => Js.log("clicked!");

let firstColumnInfo = ["Orar", "Despre", "Contact"];

let columns = [firstColumnInfo, firstColumnInfo];

let make = _children => {
  ...component,
  render: _self => {
    let columnComponents =
      columns
      |> List.mapi((i, columnInfo) => {
           let colId = "c" ++ string_of_int(i);
           <Column colId columnInfo key=colId />;
         });
    <div className=Styles.main> {ReasonReact.array(Array.of_list(columnComponents))} </div>;
  },
};
