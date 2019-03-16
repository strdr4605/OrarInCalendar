let component = ReasonReact.statelessComponent("Column");

let handleClick = (_event, _self) => Js.log("Column clicked!");

let make = (~listInfo, _children) => {
  ...component,
  render: self => {
    let listItems =
      listInfo |> List.mapi((i, rowInfo) => <li key={string_of_int(i)}> <Row rowInfo /> </li>);

    <div onClick={self.handle(handleClick)}>
      {ReasonReact.string("Column")}
      <ul> {ReasonReact.array(Array.of_list(listItems))} </ul>
    </div>;
  },
};
