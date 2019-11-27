module Styles = {
  open Css;

  let icon = style([width(`px(30))]);
  let row =
    style([
      borderTopWidth(`px(1)),
      borderTopColor(rgba(0, 0, 0, 0.33)),
      borderTopStyle(`solid),
    ]);
  let cell =
    style([
      paddingTop(`px(10)),
      paddingBottom(`px(10)),
      paddingLeft(`px(30)),
      paddingRight(`px(30)),
      textAlign(`center),
    ]);
};

[@react.component]
let make = (~data: HistoricalWeatherDecoder.hourlyWeather) =>
  <tr className=Styles.row>
    <td className=Styles.cell>
      {React.string(data.time |> Utils.formatTime)}
    </td>
    <td className=Styles.cell>
      {React.string(string_of_int(data.temperature))}
    </td>
    <td className=Styles.cell>
      {React.string(string_of_int(data.pressure))}
    </td>
    <td className=Styles.cell>
      {React.string(
         Utils.formatWeatherDescriptions(data.weather_descriptions),
       )}
    </td>
    <td className=Styles.cell>
      {React.array(
         Array.of_list(
           List.map(
             icon => <img src=icon className=Styles.icon />,
             data.weather_icons,
           ),
         ),
       )}
    </td>
  </tr>;
