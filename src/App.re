let initialLocation = "";
let initialWeather = WeatherDecoder.inintialCurrentWeather;

[@react.component]
let make = () => {
  let (location, setLocation) = React.useState(() => initialLocation);
  let (state, fetchCurrentWether) = WeatherStack.useApi();

  React.useEffect1(
    () => {
      if (String.length(location) > 0) {
        fetchCurrentWether(location);
      };
      None;
    },
    [|location|],
  );

  <div>
    <Input onSelect=setLocation />
    <p>
      {React.string(
         "current state: "
         ++ (
           switch (state.loadingState) {
           | Loading => "Loading..."
           | Success => "Success"
           | Error => "Error"
           }
         ),
       )}
    </p>
    <p> {React.string(location)} </p>
    <p> {React.string(string_of_int(state.weather.temperature))} </p>
    <ul>
      {React.array(
         Array.of_list(
           List.map(
             description =>
               <li key=description> {ReasonReact.string(description)} </li>,
             state.weather.weather_descriptions,
           ),
         ),
       )}
    </ul>
  </div>;
};