[@bs.deriving abstract]
type dataItem = {
  time: string,
  temperature: int,
};

let processData = data =>
  Array.of_list(
    List.map(
      (item: HistoricalWeatherDecoder.hourlyWeather) =>
        dataItem(
          ~time=item.time |> Utils.formatTime,
          ~temperature=item.temperature,
        ),
      data,
    ),
  );

[@react.component]
let make = (~data, ~className) =>
  BsRecharts.(
    <ResponsiveContainer height={Px(300.0)} width={Px(600.0)} className>
      <LineChart data={processData(data)}>
        <Line _type=`monotone dataKey="temperature" stroke="#0074D9" />
        <CartesianGrid stroke="#ccc" />
        <XAxis dataKey="time" />
        <YAxis />
        <Tooltip />
      </LineChart>
    </ResponsiveContainer>
  );