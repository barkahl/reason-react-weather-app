let initialLocation = "";
let initialWeather = WeatherDecoder.inintialCurrentWeather;

[@react.component]
let make = () => {
  let (location, setLocation) = React.useState(() => initialLocation);
  let (weather, setWeather) = React.useState(() => initialWeather);

  let fetchWeather = () => {
    let url = "/current?query=" ++ location;
    Js.log(url);
    Js.Promise.(
      Fetch.fetch(url)
      |> then_(Fetch.Response.json)
      |> then_(json => {
           Js.log(json);
           json
           |> WeatherDecoder.decodeWeather
           |> (data => setWeather(_ => data.current))
           |> resolve;
         })
    )
    ->ignore;
    ();
  };

  React.useEffect1(
    () => {
      Js.log(location);
      if (String.length(location) > 0) {
        fetchWeather();
      };
      None;
    },
    [|location|],
  );

  <div>
    <Input onSelect=setLocation />
    <p> {React.string(location)} </p>
    <p> {React.string(string_of_int(weather.temperature))} </p>
  </div>;
};