[@react.component]
let make = (~data: list(WeatherDecoder.hourlyWeather)) =>
  <table>
    <thead>
      <tr>
        <th> {React.string("Time")} </th>
        <th> {React.string("Temperature")} </th>
        <th> {React.string("Pressure")} </th>
        <th> {React.string("Description")} </th>
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