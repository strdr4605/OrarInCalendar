let component = ReasonReact.statelessComponent("Column");

let handleClick = (_event, _self) => Js.log("Column clicked!");

let make = (~listInfo, _children) => {
  ...component,
  render: self => {
    let listItems =
      listInfo |> List.mapi((i, rowInfo) => <li key={string_of_int(i)}> <Row rowInfo /> </li>);

    <div className=Styles.column onClick={self.handle(handleClick)}>
      <ul> {ReasonReact.array(Array.of_list(listItems))} </ul>
    </div>;
  },
};
