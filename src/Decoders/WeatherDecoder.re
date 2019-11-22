type request = {
  type_: string,
  query: string,
  language: string,
  unit: string,
};

type location = {
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

type current = {
  observation_time: string,
  temperature: int,
  weather_code: int,
  weather_icons: list(string),
  weather_descriptions: list(string),
  wind_speed: int,
  wind_degree: int,
  wind_dir: string,
  pressure: int,
  precip: float,
  humidity: int,
  cloudcover: int,
  feelslike: int,
  uv_index: int,
  visibility: int,
};

type weather = {
  request,
  location,
  current,
};

let inintialCurrentWeather = {
  observation_time: "",
  temperature: 0,
  weather_code: 0,
  weather_icons: [],
  weather_descriptions: [],
  wind_speed: 0,
  wind_degree: 0,
  wind_dir: "",
  pressure: 0,
  precip: 0.0,
  humidity: 0,
  cloudcover: 0,
  feelslike: 0,
  uv_index: 0,
  visibility: 0,
};

let decodeRequest = json =>
  Json.Decode.{
    type_: json |> field("type", string),
    query: json |> field("query", string),
    language: json |> field("language", string),
    unit: json |> field("unit", string),
  };

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

let decodeCurrent = json =>
  Json.Decode.{
    observation_time: json |> field("observation_time", string),
    temperature: json |> field("temperature", int),
    weather_code: json |> field("weather_code", int),
    weather_icons: json |> field("weather_icons", list(string)),
    weather_descriptions:
      json |> field("weather_descriptions", list(string)),
    wind_speed: json |> field("wind_speed", int),
    wind_degree: json |> field("wind_degree", int),
    wind_dir: json |> field("wind_dir", string),
    pressure: json |> field("pressure", int),
    precip: json |> field("precip", float),
    humidity: json |> field("humidity", int),
    cloudcover: json |> field("cloudcover", int),
    feelslike: json |> field("feelslike", int),
    uv_index: json |> field("uv_index", int),
    visibility: json |> field("visibility", int),
  };

let decodeWeather = json =>
  Json.Decode.{
    request: json |> field("request", decodeRequest),
    location: json |> field("location", decodeLocation),
    current: json |> field("current", decodeCurrent),
  };