[%bs.raw {|require('rsuite/dist/styles/rsuite-default.css')|}];

type searchMode =
  | Current
  | Historical;

type date = Js.Date.t;

let initialLocation = "";
let initialWeather = CurrentWeatherDecoder.initialCurrentWeather;
let initialSearchMode = Current;
let initialHistoricalDate =
  ReasonDateFns.DateFns.(Js.Date.make() |> subDays(1)); // yesterday

module Styles = {
  open Css;

  let app =
    style([
      width(`px(800)),
      margin(`auto),
      marginTop(`px(10)),
      display(`flex),
      flexDirection(`column),
      alignItems(`center),
      selector(".rs-picker-date", [display(`block)]),
    ]);
  let input = style([width(`px(300)), margin(`px(10))]);
  let controls =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      width(`px(500)),
    ]);
  let datepicker =
    style([margin(`auto), display(`block), width(`px(150))]);
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
    <Input onSelect=setLocation className=Styles.input />
    <RsuiteUi.Toggle
      size=`lg
      checkedChildren={React.string("Historical")}
      unCheckedChildren={React.string("Current")}
      onChange={(checked, _event) =>
        setSearchMode(_ => checked ? Historical : Current)
      }
    />
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
    {switch (weather.current) {
     | None => ReasonReact.null
     | Some(data) => <WeatherStatus location weather=data />
     }}
    {searchMode === Historical
       ? <div>
           <RsuiteUi.DatePicker
             className=Styles.datepicker
             onChange={date => setHistoricalDate(_ => date)}
             cleanable=false
           />
           {switch (weather.historical) {
            | None => ReasonReact.null
            | Some(historical) =>
              <div>
                <TemperatureChart data={historical.hourly} />
                <HistoricalDataTable data={historical.hourly} />
              </div>
            }}
         </div>
       : ReasonReact.null}
  </div>;
};