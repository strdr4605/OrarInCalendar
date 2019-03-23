/* State declaration */
type state = {selected: array(int)};

/* Action declaration */
type action =
  | Select((int, int));

let component = ReasonReact.reducerComponent("MainComponent");

// let handleClick = (_event, _self) => Js.log("clicked!");

let firstColumnInfo = ["Orar", "Despre", "Contact"];

let columns = [firstColumnInfo, firstColumnInfo, firstColumnInfo];

let make = _children => {
  ...component,

  /* State transitions */
  reducer: (action, _state) =>
    switch (action) {
    | Select((colId, rowId)) =>
      Js.log(
        "SELECTED : " ++ string_of_int(colId) ++ " " ++ string_of_int(rowId),
      );
      ReasonReact.Update({selected: [|colId, rowId|]});
    },

  initialState: () => {selected: [||]},
  render: self => {
    let columnComponents =
      columns
      |> List.mapi((i, columnInfo) => {
           let colId = string_of_int(i);
           <Column
             colId
             columnInfo
             key=colId
             selectFn={(colId, rowId) => self.send(Select((colId, rowId)))}
           />;
         });
    <div className=Styles.main>
      {ReasonReact.array(Array.of_list(columnComponents))}
    </div>;
  },
};