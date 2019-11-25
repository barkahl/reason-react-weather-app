[%bs.raw {|require('rsuite/dist/styles/rsuite-default.css')|}];

type searchMode =
  | Current
  | Historical;

type date = Js.Date.t;

let initialLocation = "";
let initialWeather = WeatherDecoder.inintialCurrentWeather;
let initialSearchMode = Current;
let initialHistoricalDate = Js.Date.make();

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
  let (searchMode, setSearchMode) = React.useState(() => initialSearchMode);
  let (historicalDate, setHistoricalDate) =
    React.useState(() => initialHistoricalDate);
  let (weather, fetchCurrentWeather, fetchHistoricalWeather) =
    WeatherStack.useApi();

  React.useEffect1(
    () => {
      if (String.length(location) > 0) {
        switch (searchMode) {
        | Current => fetchCurrentWeather(location)
        | Historical => fetchHistoricalWeather(location, historicalDate)
        };
      };
      None;
    },
    [|location|],
  );

  React.useEffect1(
    () => {
      if (String.length(location) > 0) {
        fetchHistoricalWeather(location, historicalDate);
      };
      None;
    },
    [|historicalDate|],
  );

  <div className=Styles.app>
    <div className=Styles.controls>
      <Input onSelect=setLocation />
      <RsuiteUi.Toggle
        size=`lg
        checkedChildren={React.string("Historical")}
        unCheckedChildren={React.string("Current")}
        onChange={(checked, _event) =>
          setSearchMode(_ => checked ? Historical : Current)
        }
      />
      {searchMode === Historical
         ? <RsuiteUi.DatePicker
             className=Styles.datepicker
             onChange={date => setHistoricalDate(_ => date)}
           />
         : ReasonReact.null}
    </div>
    <p>
      {React.string(
         "current state: "
         ++ (
           switch (weather.loadingState) {
           | Loading => "Loading..."
           | Idle => "Idle"
           | Error => "Error"
           }
         ),
       )}
    </p>
    <p> {React.string(location)} </p>
    <p> {React.string(string_of_int(weather.current.temperature))} </p>
    <ul>
      {React.array(
         Array.of_list(
           List.map(
             description =>
               <li key=description> {ReasonReact.string(description)} </li>,
             weather.current.weather_descriptions,
           ),
         ),
       )}
    </ul>
    {searchMode === Historical
       ? <HistoricalDataTable data={weather.historical.hourly} />
       : ReasonReact.null}
  </div>;
};