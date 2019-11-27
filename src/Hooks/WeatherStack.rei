type loadingState =
  | Loading
  | Idle
  | Error;

type state = {
  loadingState,
  current: CurrentWeatherDecoder.current,
  location: LocationDecoder.location,
  historical: option(HistoricalWeatherDecoder.historicalWeatherSchema),
};

let useApi:
  unit =>
  (state, string => unit, (string, ReasonDateFns.DateFns.date) => unit);
