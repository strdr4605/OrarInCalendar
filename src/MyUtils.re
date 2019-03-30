let cssClasses = list =>
  list |> List.fold_left((names, name) => names ++ " " ++ name, "");
