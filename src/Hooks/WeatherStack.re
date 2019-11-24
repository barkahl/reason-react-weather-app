type loadingState =
  | Loading
  | Idle
  | Error;

type state = {
  loadingState,
  current: WeatherDecoder.current,
  location: WeatherDecoder.location,
  historical: WeatherDecoder.historical,
};

let initialState = {
  loadingState: Idle,
  current: WeatherDecoder.inintialCurrentWeather,
  location: WeatherDecoder.initialLocation,
  historical: WeatherDecoder.initialHistoricalWeather,
};

type action =
  | FetchWeather
  | FetchCurrentWeatherSuccess(WeatherDecoder.currentWeather)
  | FetchHistoricalWeatherSuccess(WeatherDecoder.historicalWeather);

let reducer = (state, action) =>
  switch (action) {
  | FetchWeather => {...initialState, loadingState: Loading}
  | FetchCurrentWeatherSuccess(data) => {
      ...state,
      loadingState: Idle,
      current: data.current,
      location: data.location,
    }
  | FetchHistoricalWeatherSuccess(data) => {
      ...state,
      loadingState: Idle,
      current: data.current,
      location: data.location,
      historical: data.historical,
    }
  };

let fetchWeather = (location, dispatch) => {
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

let useApi = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let makeRequest = location => fetchWeather(location, dispatch);

  (state, makeRequest);
};