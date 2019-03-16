let component = ReasonReact.statelessComponent("Column");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~info, _children) => {
  ...component,
  render: self => {
    let listItems =
      info |> List.mapi((i, row) => <li key={string_of_int(i)}> {ReasonReact.string(row)} </li>);

    <div onClick={self.handle(handleClick)}>
      {ReasonReact.string("Column")}
      <ul> {ReasonReact.array(Array.of_list(listItems))} </ul>
    </div>;
  },
};
