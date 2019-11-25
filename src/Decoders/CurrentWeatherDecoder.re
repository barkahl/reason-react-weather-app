type currentWeatherSchema = {
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

type current = option(currentWeatherSchema);

type response = {
  request: RequestDecoder.request,
  location: LocationDecoder.location,
  current,
};

let initialCurrentWeather = None;

let initialLocation = None;

let initialHistoricalContent = None;

let initialHistoricalWeather = None;

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

let decodeResponse = json =>
  Json.Decode.{
    request: json |> field("request", RequestDecoder.decodeRequest),
    location:
      json |> optional(field("location", LocationDecoder.decodeLocation)),
    current: json |> optional(field("current", decodeCurrent)),
  };