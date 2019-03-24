open Breed;

let component = ReasonReact.reducerComponent("MainComponent");

let firstColumnInfo = [|"Dogs", "Orar", "Despre", "Contact"|];

let createColumns = self => {
  let columns = self.ReasonReact.state.columns;
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
    <img
      height="340"
      width="500"
      src="https://images.dog.ceo/breeds/spaniel-blenheim/n02086646_2173.jpg"
    />
  </div>;
};

let make = _children => {
  ...component,
  reducer,
  initialState: () => {
    data: Loading,
    selected: [|0, (-1), (-1)|],
    columns: [|firstColumnInfo|],
  },
  didMount: self => self.send(BreedsFetch),
  render: self => {
    switch (self.state.data) {
    | Error(_err) => <div> {ReasonReact.string("An error occurred!")} </div>
    | Loading => <div> {ReasonReact.string("Loading...")} </div>
    | Loaded(_breeds) => createColumns(self)
    };
  },
};
