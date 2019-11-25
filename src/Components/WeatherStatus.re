module Styles = {
  open Css;

  let container = style([margin(`px(10))]);
};

[@react.component]
let make = (~location, ~weather: CurrentWeatherDecoder.currentWeatherSchema) =>
  <div className=Styles.container>
    <h1> {React.string(location)} </h1>
    {React.array(
       Array.of_list(
         List.map(
           description => <p> {React.string(description)} </p>,
           weather.weather_descriptions,
         ),
       ),
     )}
    {React.array(
       Array.of_list(
         List.map(icon => <img src=icon />, weather.weather_icons),
       ),
     )}
    <p>
      {React.string(string_of_int(weather.temperature) ++ {js|°C|js})}
    </p>
  </div>;