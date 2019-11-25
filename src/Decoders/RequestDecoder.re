type request = {
  type_: string,
  query: string,
  language: string,
  unit: string,
};

let decodeRequest = json =>
  Json.Decode.{
    type_: json |> field("type", string),
    query: json |> field("query", string),
    language: json |> field("language", string),
    unit: json |> field("unit", string),
  };