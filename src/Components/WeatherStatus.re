module Styles = {
  open Css;

  let status =
    style([
      display(`flex),
      justifyContent(`spaceAround),
      width(`px(500)),
      margin(`px(10)),
      borderTopWidth(`px(1)),
      borderTopStyle(`solid),
      borderTopColor(rgba(0, 0, 0, 0.33)),
      borderBottomWidth(`px(1)),
      borderBottomStyle(`solid),
      borderBottomColor(rgba(0, 0, 0, 0.33)),
    ]);
  let item =
    style([
      marginTop(`px(10)),
      marginBottom(`px(10)),
      display(`flex),
      alignItems(`center),
      justifyContent(`center),
      fontSize(`px(20)),
    ]);
  let icons = style([display(`flex), justifyContent(`center)]);
  let descriptions = style([display(`flex), justifyContent(`center)]);
  let description = style([padding(`px(10))]);
  let icon = style([borderRadius(`px(3))]);
};

[@react.component]
let make = (~location, ~weather: CurrentWeatherDecoder.currentWeatherSchema) =>
  <section className=Styles.status>
    <span className=Styles.item>
      {React.string(string_of_int(weather.temperature) ++ {js|°C|js})}
    </span>
    <span className=Styles.item>
      {React.string(string_of_int(weather.pressure) ++ " hPa")}
    </span>
    <div className=Styles.item>
      <div className=Styles.icons>
        {React.array(
           Array.of_list(
             List.map(
               icon => <img src=icon className=Styles.icon />,
               weather.weather_icons,
             ),
           ),
         )}
      </div>
      <div className=Styles.descriptions>
        {React.array(
           Array.of_list(
             List.map(
               description =>
                 <p className=Styles.description>
                   {React.string(description)}
                 </p>,
               weather.weather_descriptions,
             ),
           ),
         )}
      </div>
    </div>
  </section>;