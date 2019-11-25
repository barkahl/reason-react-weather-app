[%bs.raw {|require('rsuite/dist/styles/rsuite-default.css')|}];

let initialLocation = "";
let initialWeather = WeatherDecoder.inintialCurrentWeather;

module Styles = {
  open Css;

  let app = style([]);
  let controls =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      width(`px(500)),
    ]);
  let datepicker = style([]);
};

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

  <div className=Styles.app>
    <div className=Styles.controls>
      <Input onSelect=setLocation />
      <RsuiteUi.Toggle
        size=`lg
        checkedChildren={React.string("Historical")}
        unCheckedChildren={React.string("Current")}
      />
      <RsuiteUi.DatePicker className=Styles.datepicker />
    </div>
    <p>
      {React.string(
         "current state: "
         ++ (
           switch (state.loadingState) {
           | Loading => "Loading..."
           | Idle => "Idle"
           | Error => "Error"
           }
         ),
       )}
    </p>
    <p> {React.string(location)} </p>
    <p> {React.string(string_of_int(state.current.temperature))} </p>
    <ul>
      {React.array(
         Array.of_list(
           List.map(
             description =>
               <li key=description> {ReasonReact.string(description)} </li>,
             state.current.weather_descriptions,
           ),
         ),
       )}
    </ul>
  </div>;
};