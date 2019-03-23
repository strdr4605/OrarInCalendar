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

let component = ReasonReact.reducerComponent("MainComponent");

let handleClick = (_event, _self) => Js.log("clicked!");

let firstColumnInfo = ["Orar", "Despre", "Contact"];

let columns = [firstColumnInfo, firstColumnInfo, firstColumnInfo];

let selectFn = (self, action) => self.ReasonReact.send(action);

let createColumns = breeds => {
  breeds
  |> Array.sort((a, b) =>
       Array.length(b.subBreeds) - Array.length(a.subBreeds)
     );
  let sortedBreedNames =
    breeds |> Array.to_list |> List.map(breed => breed.name);

  let columns = [["Dogs", ...firstColumnInfo], sortedBreedNames, breeds[1].subBreeds |> Array.to_list ];
  let columnComponents =
    columns
    |> List.mapi((i, columnInfo) => {
         let colId = string_of_int(i);
         <Column
           colId
           columnInfo
           key=colId
           /* selectFn={selectFn(self)} */
         />;
       });
  <div className=Styles.main>
    {ReasonReact.array(Array.of_list(columnComponents))}
    <img height="340" width="500" src="https://images.dog.ceo/breeds/spaniel-blenheim/n02086646_2173.jpg" />
  </div>;
};

let make = _children => {
  ...component,

  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Select((colId, rowId)) =>
      ReasonReact.Update({...state, selected: [|colId, rowId|]})
    | BreedsFetch =>
      ReasonReact.UpdateWithSideEffects(
        {...state, data: Loading},
        self =>
          Js.Promise.(
            Fetch.fetch("https://dog.ceo/api/breeds/list/all")
            |> then_(Fetch.Response.json)
            |> then_(json =>
                 json
                 |> Decode.subBreeds
                 |> (breeds => self.send(BreedsFetched(breeds)))
                 |> resolve
               )
            |> catch(err =>
                 Js.Promise.resolve(self.send(BreedsFailedToFetch(err)))
               )
            |> ignore
          ),
      )
    | BreedsFetched(breeds) =>
      ReasonReact.Update({...state, data: Loaded(breeds)})
    | BreedsFailedToFetch(err) =>
      ReasonReact.Update({...state, data: Error(err)})
    },

  initialState: () => {data: Loading, selected: [||], columns: [||]},
  didMount: self => self.send(BreedsFetch),
  render: self => {
    switch (self.state.data) {
    | Error(_err) => <div> {ReasonReact.string("An error occurred!")} </div>
    | Loading => <div> {ReasonReact.string("Loading...")} </div>
    | Loaded(breeds) => createColumns(breeds)
    };
  },
};
