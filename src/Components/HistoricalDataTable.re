module Styles = {
  open Css;

  let container = style([margin(`auto)]);
  let column = style([paddingTop(`px(10)), paddingBottom(`px(10))]);
};

[@react.component]
let make = (~data: list(HistoricalWeatherDecoder.hourlyWeather)) =>
  <table className=Styles.container>
    <thead>
      <tr>
        <th className=Styles.column> {React.string("Time")} </th>
        <th className=Styles.column>
          {React.string("Temperature " ++ {js|[°C]|js})}
        </th>
        <th className=Styles.column> {React.string("Pressure [hPa]")} </th>
        <th className=Styles.column> {React.string("Description")} </th>
      </tr>
    </thead>
    <tbody>
      {React.array(
         Array.of_list(
           List.map(dataPerHour => <TableRow data=dataPerHour />, data),
         ),
       )}
    </tbody>
  </table>;
