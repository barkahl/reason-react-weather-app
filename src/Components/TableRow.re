let formatWeatherDescriptions = descriptions =>
  Belt.List.reduce(descriptions, "", (acc, curr) =>
    switch (acc) {
    | "" => curr
    | str => str ++ ", " ++ curr
    }
  );

[@react.component]
let make = (~data: HistoricalWeatherDecoder.hourlyWeather) =>
  <tr>
    <td> {React.string(data.time)} </td>
    <td> {React.string(string_of_int(data.temperature))} </td>
    <td> {React.string(string_of_int(data.pressure))} </td>
    <td>
      {React.string(formatWeatherDescriptions(data.weather_descriptions))}
    </td>
  </tr>;