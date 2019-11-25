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

type historicalSchema = {
  current: CurrentWeatherDecoder.current,
  location: LocationDecoder.location,
  historical: option(HistoricalWeatherDecoder.historicalWeatherSchema),
};

let initialState = {
  loadingState: Idle,
  current: None,
  location: None,
  historical: None,
};

type action =
  | FetchWeather
  | FetchCurrentWeatherSuccess(CurrentWeatherDecoder.response)
  | FetchHistoricalWeatherSuccess(historicalSchema)
  | FetchError;

let reducer = (state, action) =>
  switch (action) {
  | FetchWeather => {...initialState, loadingState: Loading}
  | FetchCurrentWeatherSuccess((data: CurrentWeatherDecoder.response)) => {
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
         |> CurrentWeatherDecoder.decodeResponse
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
         |> HistoricalWeatherDecoder.decodeResponse
         |> (
           data =>
             switch (data.historical) {
             | None => dispatch(FetchError)
             | Some(historical) =>
               dispatch(
                 FetchHistoricalWeatherSuccess({
                   location: data.location,
                   current: data.current,
                   historical: Js.Dict.get(historical, formattedDate),
                 }),
               )
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