type astro = {
  sunrise: string,
  sunset: string,
  moonrise: string,
  moonset: string,
  moon_phase: string,
  moon_illumination: int,
};

type hourlyWeather = {
  time: string,
  temperature: int,
  wind_speed: int,
  wind_degree: int,
  wind_dir: string,
  weather_code: int,
  weather_icons: list(string),
  weather_descriptions: list(string),
  precip: float,
  humidity: int,
  visibility: int,
  pressure: int,
  cloudcover: int,
  heatindex: int,
  dewpoint: int,
  windchill: int,
  windgust: int,
  feelslike: int,
  chanceofrain: int,
  chanceofremdry: int,
  chanceofwindy: int,
  chanceofovercast: int,
  chanceofsunshine: int,
  chanceoffrost: int,
  chanceofhightemp: int,
  chanceoffog: int,
  chanceofsnow: int,
  chanceofthunder: int,
  uv_index: int,
};

type historicalWeatherSchema = {
  astro,
  date: string,
  date_epoch: int,
  mintemp: int,
  maxtemp: int,
  avgtemp: int,
  totalsnow: int,
  sunhour: float,
  uv_index: int,
  hourly: list(hourlyWeather),
};

type historical = option(Js.Dict.t(historicalWeatherSchema));

type response = {
  request: RequestDecoder.request,
  location: LocationDecoder.location,
  current: CurrentWeatherDecoder.current,
  historical,
};

let decodeAstro = json =>
  Json.Decode.{
    sunrise: json |> field("sunrise", string),
    sunset: json |> field("sunset", string),
    moonrise: json |> field("moonrise", string),
    moonset: json |> field("moonset", string),
    moon_phase: json |> field("moon_phase", string),
    moon_illumination: json |> field("moon_illumination", int),
  };

let decodeHourly = json =>
  Json.Decode.{
    time: json |> field("time", string),
    temperature: json |> field("temperature", int),
    wind_speed: json |> field("wind_speed", int),
    wind_degree: json |> field("wind_degree", int),
    wind_dir: json |> field("wind_dir", string),
    weather_code: json |> field("weather_code", int),
    weather_icons: json |> field("weather_icons", list(string)),
    weather_descriptions:
      json |> field("weather_descriptions", list(string)),
    precip: json |> field("precip", float),
    humidity: json |> field("humidity", int),
    visibility: json |> field("visibility", int),
    pressure: json |> field("pressure", int),
    cloudcover: json |> field("cloudcover", int),
    heatindex: json |> field("heatindex", int),
    dewpoint: json |> field("dewpoint", int),
    windchill: json |> field("windchill", int),
    windgust: json |> field("windgust", int),
    feelslike: json |> field("feelslike", int),
    chanceofrain: json |> field("chanceofrain", int),
    chanceofremdry: json |> field("chanceofremdry", int),
    chanceofwindy: json |> field("chanceofwindy", int),
    chanceofovercast: json |> field("chanceofovercast", int),
    chanceofsunshine: json |> field("chanceofsunshine", int),
    chanceoffrost: json |> field("chanceoffrost", int),
    chanceofhightemp: json |> field("chanceofhightemp", int),
    chanceoffog: json |> field("chanceoffog", int),
    chanceofsnow: json |> field("chanceofsnow", int),
    chanceofthunder: json |> field("chanceofthunder", int),
    uv_index: json |> field("uv_index", int),
  };

let decodeHistoricalContent = json =>
  Json.Decode.{
    astro: json |> field("astro", decodeAstro),
    date: json |> field("date", string),
    date_epoch: json |> field("date_epoch", int),
    mintemp: json |> field("mintemp", int),
    maxtemp: json |> field("maxtemp", int),
    avgtemp: json |> field("avgtemp", int),
    totalsnow: json |> field("totalsnow", int),
    sunhour: json |> field("sunhour", float),
    uv_index: json |> field("uv_index", int),
    hourly: json |> field("hourly", list(decodeHourly)),
  };

let decodeHistorical = json =>
  json |> Json.Decode.(dict(decodeHistoricalContent));

let decodeResponse = json =>
  Json.Decode.{
    request: json |> field("request", RequestDecoder.decodeRequest),
    location:
      json |> field("location", optional(LocationDecoder.decodeLocation)),
    current:
      json |> field("current", optional(CurrentWeatherDecoder.decodeCurrent)),
    historical: json |> field("historical", optional(decodeHistorical)),
  };