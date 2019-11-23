type loadingState =
  | Loading
  | Success
  | Error;

type state = {
  loadingState,
  weather: WeatherDecoder.current,
  location: WeatherDecoder.location,
};

let initialState = {
  loadingState: Success,
  weather: WeatherDecoder.inintialCurrentWeather,
  location: WeatherDecoder.initialLocation,
};

type action =
  | FetchWeather
  | FetchSuccess(WeatherDecoder.weather);

let reducer = (state, action) =>
  switch (action) {
  | FetchWeather => {...initialState, loadingState: Loading}
  | FetchSuccess(data) => {
      ...state,
      loadingState: Success,
      weather: data.current,
      location: data.location,
    }
  };

let fetchWeather = (location, dispatch) => {
  let url = "/api/current?query=" ++ location;

  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> WeatherDecoder.decodeWeather
         |> (data => dispatch(FetchSuccess(data)))
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