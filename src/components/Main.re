open Breed;

let component = ReasonReact.reducerComponent("MainComponent");

let firstColumnInfo = [|"Dogs", "Orar", "Despre", "Contact"|];

let removeEmptyColumn = columns =>
  if (Array.length(columns) > 2 && Array.length(columns[2]) < 1) {
    columns
    |> Array.to_list
    |> List.rev
    |> List.tl
    |> List.rev
    |> Array.of_list;
  } else {
    columns;
  };

let createColumns = self => {
  let columns = removeEmptyColumn(self.ReasonReact.state.columns);
  let columnComponents =
    columns
    |> Array.mapi((i, columnInfo) => {
         let colId = string_of_int(i);
         <Column
           colId
           columnInfo
           key=colId
           appSend={self.ReasonReact.send}
           selectedRow={
                         if (Array.length(self.ReasonReact.state.selected) > i) {
                           self.ReasonReact.state.selected[i];
                         } else {
                           (-1);
                         }
                       }
         />;
       });
  <div className=Styles.main>
    {ReasonReact.array(columnComponents)}
    <img height="500" width="500" src={self.ReasonReact.state.image} />
  </div>;
};

let make = _children => {
  ...component,
  reducer,
  initialState: () => {
    breeds: Loading,
    selected: [|0, (-1), (-1)|],
    columns: [|firstColumnInfo|],
    image: "https://avatars0.githubusercontent.com/u/16056918",
  },
  didMount: self => self.send(BreedsFetch),
  render: self => {
    switch (self.state.breeds) {
    | Error(_err) => <div> {ReasonReact.string("An error occurred!")} </div>
    | Loading => <div> {ReasonReact.string("Loading...")} </div>
    | Loaded(_breeds) => createColumns(self)
    };
  },
};
