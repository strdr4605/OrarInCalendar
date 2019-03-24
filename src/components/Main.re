type subBreed = string;
type breed = {
  name: string,
  subBreeds: array(subBreed),
};
type data =
  | Loading
  | Error(Js.Promise.error)
  | Loaded(array(breed));

/* State declaration */
type state = {
  columns: array(array(string)),
  data,
  selected: array(int),
};

/* Action declaration */
type action =
  | Select((int, int))
  | BreedsFetch
  | BreedsFetched(array(breed))
  | BreedsFailedToFetch(Js.Promise.error);

module Decode = {
  let subBreeds = (json): array(breed) => {
    let breedsDict =
      Json.Decode.(json |> field("message", d => d |> dict(array(string))));
    breedsDict
    |> Js.Dict.keys
    |> Array.map(name => {
         let subBreeds =
           Js.Option.getWithDefault([||], Js.Dict.get(breedsDict, name));
         {name, subBreeds};
       });
  };
};

let sortBreeds = breeds => {
  breeds
  |> Array.sort((a, b) =>
       Array.length(b.subBreeds) - Array.length(a.subBreeds)
     );
  breeds;
};

let breedsFetching = state =>
  ReasonReact.UpdateWithSideEffects(
    {...state, data: Loading},
    self =>
      Js.Promise.(
        Fetch.fetch("https://dog.ceo/api/breeds/list/all")
        |> then_(Fetch.Response.json)
        |> then_(json =>
             json
             |> Decode.subBreeds
             |> sortBreeds
             |> (breeds => self.send(BreedsFetched(breeds)))
             |> resolve
           )
        |> catch(err =>
             Js.Promise.resolve(self.send(BreedsFailedToFetch(err)))
           )
        |> ignore
      ),
  );

let component = ReasonReact.reducerComponent("MainComponent");

let firstColumnInfo = [|"Dogs", "Orar", "Despre", "Contact"|];

let selectAction = (self, ids) => self.ReasonReact.send(Select(ids));

let createColumns = (self, breeds) => {
  let columns = self.ReasonReact.state.columns;
  let columnComponents =
    columns
    |> Array.mapi((i, columnInfo) => {
         let colId = string_of_int(i);
         <Column
           colId
           columnInfo
           key=colId
           selectAction={selectAction(self)}
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

  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Select((colId, rowId)) =>
      let selected = state.selected;
      selected[colId] = rowId;
      /* let columns = Array.append(state.columns); */
      ReasonReact.Update({...state, selected});
    | BreedsFetch => breedsFetching(state)
    | BreedsFetched(breeds) =>
      ReasonReact.Update({
        ...state,
        data: Loaded(breeds),
        columns:
          Array.append(
            state.columns,
            [|breeds |> Array.map(breed => breed.name)|],
          ),
      })
    | BreedsFailedToFetch(err) =>
      ReasonReact.Update({...state, data: Error(err)})
    },

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
    | Loaded(breeds) => createColumns(self, breeds)
    };
  },
};
