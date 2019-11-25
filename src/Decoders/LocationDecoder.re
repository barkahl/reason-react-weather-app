type locationSchema = {
  name: string,
  country: string,
  region: string,
  lat: string,
  lon: string,
  timezone_id: string,
  localtime: string,
  localtime_epoch: int,
  utc_offset: string,
};

type location = option(locationSchema);

let decodeLocation = json =>
  Json.Decode.{
    name: json |> field("name", string),
    country: json |> field("country", string),
    region: json |> field("region", string),
    lat: json |> field("lat", string),
    lon: json |> field("lon", string),
    timezone_id: json |> field("timezone_id", string),
    localtime: json |> field("localtime", string),
    localtime_epoch: json |> field("localtime_epoch", int),
    utc_offset: json |> field("utc_offset", string),
  };