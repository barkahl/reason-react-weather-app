type loadingState =
  | Loading
  | Idle
  | Error;

type state = {
  loadingState,
  current: WeatherDecoder.current,
  location: WeatherDecoder.location,
  historical: WeatherDecoder.historicalContent,
};

type historicalSchema = {
  current: WeatherDecoder.current,
  location: WeatherDecoder.location,
  historical: WeatherDecoder.historicalContent,
};

let initialState = {
  loadingState: Idle,
  current: WeatherDecoder.inintialCurrentWeather,
  location: WeatherDecoder.initialLocation,
  historical: WeatherDecoder.initialHistoricalContent,
};

type action =
  | FetchWeather
  | FetchCurrentWeatherSuccess(WeatherDecoder.currentWeather)
  | FetchHistoricalWeatherSuccess(historicalSchema)
  | FetchError;

let reducer = (state, action) =>
  switch (action) {
  | FetchWeather => {...initialState, loadingState: Loading}
  | FetchCurrentWeatherSuccess(data) => {
      ...state,
      loadingState: Idle,
      current: data.current,
      location: data.location,
    }
  | FetchHistoricalWeatherSuccess((data: historicalSchema)) => {
      ...state,
      loadingState: Idle,
      current: data.current,
      location: data.location,
      historical: data.historical,
    }
  | FetchError => {...state, loadingState: Error}
  };

let fetchCurrentWeather = (location, dispatch) => {
  let url = "/api/current?query=" ++ location;

  dispatch(FetchWeather);

  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> WeatherDecoder.decodeCurrentWeatherResponse
         |> (data => dispatch(FetchCurrentWeatherSuccess(data)))
         |> resolve
       )
  )
  ->ignore;
  ();
};

let fetchHistoricalWeather = (location, date, dispatch) => {
  let formattedDate = date |> ReasonDateFns.DateFns.format("yyyy-MM-dd");
  Js.log(formattedDate);
  let url =
    "/api/historical?query="
    ++ location
    ++ "&historical_date="
    ++ formattedDate
    ++ "&hourly=1";

  dispatch(FetchWeather);

  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> WeatherDecoder.decodeHistoricalWeatherResponse
         |> (
           data => {
             switch (Js.Dict.get(data.historical, formattedDate)) {
             | None => dispatch(FetchError)
             | Some(hdata) =>
               Js.log(hdata);
               dispatch(
                 FetchHistoricalWeatherSuccess({
                   current: data.current,
                   location: data.location,
                   historical: hdata,
                 }),
               );
             };
           }
         )
         |> resolve
       )
  )
  ->ignore;
  ();
};

let useApi = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let makeCurrentWeatherRequest = location =>
    fetchCurrentWeather(location, dispatch);
  let makeHistoricalWeatherRequest = (location, date) =>
    fetchHistoricalWeather(location, date, dispatch);

  (state, makeCurrentWeatherRequest, makeHistoricalWeatherRequest);
};