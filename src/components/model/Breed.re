type subBreed = string;
type breed = {
  name: string,
  subBreeds: array(subBreed),
};
type breeds =
  | Loading
  | Error(Js.Promise.error)
  | Loaded(array(breed));

/* State declaration */
type state = {
  columns: array(array(string)),
  breeds,
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
    {...state, breeds: Loading},
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

let selectAction = (state, ids) => {
  let (colId, rowId) = ids;
  let selected = state.selected;
  selected[colId] = rowId;
  if (colId == 1) {
    selected[2] = (-1);
  };
  if (selected[0] == 0) {
    let column1 =
      switch (state.breeds) {
      | Loaded(breeds) => breeds |> Array.map(breed => breed.name)
      | _ => [||]
      };
    let columns = [|state.columns[0], column1|];
    if (selected[1] != (-1)) {
      let column2 =
        switch (state.breeds) {
        | Loaded(breeds) => breeds[selected[1]].subBreeds
        | _ => [||]
        };
      let columns = Array.append(columns, [|column2|]);
      ReasonReact.Update({...state, selected, columns});
    } else {
      ReasonReact.Update({...state, selected, columns});
    };
  } else {
    let selected = [|state.selected[0], (-1), (-1)|];
    ReasonReact.Update({...state, selected, columns: [|state.columns[0]|]});
  };
};

let reducer = (action, state) =>
  switch (action) {
  | Select(ids) => selectAction(state, ids)
  | BreedsFetch => breedsFetching(state)
  | BreedsFetched(breeds) =>
    ReasonReact.Update({
      ...state,
      breeds: Loaded(breeds),
      columns:
        Array.append(
          state.columns,
          [|breeds |> Array.map(breed => breed.name)|],
        ),
    })
  | BreedsFailedToFetch(err) =>
    ReasonReact.Update({...state, breeds: Error(err)})
  };
