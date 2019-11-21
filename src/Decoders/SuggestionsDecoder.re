type request = {
  query: string,
  results: int,
};

type result = {
  country: string,
  lat: string,
  lon: string,
  name: string,
  region: string,
  timezone_id: string,
  utc_offset: string,
};

type suggestions = {
  request,
  results: list(result),
};

let decodeRequest = json =>
  Json.Decode.{
    query: json |> field("query", string),
    results: json |> field("results", int),
  };

let decodeResult = json =>
  Json.Decode.{
    country: json |> field("country", string),
    lat: json |> field("lat", string),
    lon: json |> field("lon", string),
    name: json |> field("name", string),
    region: json |> field("region", string),
    timezone_id: json |> field("timezone_id", string),
    utc_offset: json |> field("utc_offset", string),
  };

let decodeSuggestions = json =>
  Json.Decode.{
    request: json |> field("request", decodeRequest),
    results: json |> field("results", list(decodeResult)),
  };