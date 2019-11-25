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

type historicalContent = {
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

type historical = Js.Dict.t(historicalContent);

type currentWeather = {
  request,
  location,
  current,
};

type historicalWeather = {
  request,
  location,
  current,
  historical,
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

let initialLocation = {
  name: "",
  country: "",
  region: "",
  lat: "",
  lon: "",
  timezone_id: "",
  localtime: "",
  localtime_epoch: 0,
  utc_offset: "",
};

let initialAstro = {
  sunrise: "",
  sunset: "",
  moonrise: "",
  moonset: "",
  moon_phase: "",
  moon_illumination: 0,
};

let initialHistoricalContent = {
  astro: initialAstro,
  date: "",
  date_epoch: 0,
  mintemp: 0,
  maxtemp: 0,
  avgtemp: 0,
  totalsnow: 0,
  sunhour: 0.0,
  uv_index: 0,
  hourly: [],
};

let emptyObject = Js.Dict.empty();
Js.Dict.set(emptyObject, "", initialHistoricalContent);
let initialHistoricalWeather = emptyObject;

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
  json |> Json.Decode.dict(decodeHistoricalContent);

let decodeCurrentWeatherResponse = json =>
  Json.Decode.{
    request: json |> field("request", decodeRequest),
    location: json |> field("location", decodeLocation),
    current: json |> field("current", decodeCurrent),
  };

let decodeHistoricalWeatherResponse = json =>
  Json.Decode.{
    request: json |> field("request", decodeRequest),
    location: json |> field("location", decodeLocation),
    current: json |> field("current", decodeCurrent),
    historical: json |> field("historical", decodeHistorical),
  };