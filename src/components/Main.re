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
  let breedDict = (key, json) =>
    Json.Decode.(json |> field(key, array(string)));

  let breeds = (json): array(breed) =>
    Json.Decode.(
      json
      |> field("message", array(string))
      |> Array.map(name => {name, subBreeds: [||]})
    );

  let subBreeds = (breeds, json): array(breed) =>
    Json.Decode.(
      breeds
      |> Array.map(breed =>
           {
             ...breed,
             subBreeds: json |> field("message", breedDict(breed.name)),
           }
         )
    );
};

let component = ReasonReact.reducerComponent("MainComponent");

let handleClick = (_event, _self) => Js.log("clicked!");

let firstColumnInfo = ["Orar", "Despre", "Contact"];

let columns = [firstColumnInfo, firstColumnInfo, firstColumnInfo];

let selectFn = (self, action) => self.ReasonReact.send(action);

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
            Fetch.fetch("https://dog.ceo/api/breeds/list")
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.breeds |> Js.Promise.resolve)
            |> then_(breeds =>
                 Fetch.fetch("https://dog.ceo/api/breeds/list/all")
                 |> then_(Fetch.Response.json)
                 |> then_(json =>
                      json
                      |> Decode.subBreeds(breeds)
                      |> (breeds => self.send(BreedsFetched(breeds)))
                      |> resolve
                    )
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

  initialState: () => {data: Loading, selected: [||]},
  didMount: self => self.send(BreedsFetch),
  render: self => {
    switch (self.state.data) {
    | Error(err) => Js.log(err)
    | Loading => Js.log("Loading...")
    | Loaded(breeds) => Js.log(breeds)
    };

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
      <FetchExample />
    </div>;
  },
};
