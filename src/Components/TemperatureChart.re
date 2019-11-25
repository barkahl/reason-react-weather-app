[@bs.deriving abstract]
type recor = {
  time: string,
  temperature: int,
};

let processData = data =>
  Array.of_list(
    List.map(
      (item: WeatherDecoder.hourlyWeather) =>
        recor(~time=item.time, ~temperature=item.temperature),
      data,
    ),
  );

[@react.component]
let make = (~data) =>
  BsRecharts.(
    <ResponsiveContainer height={Px(200.0)} width={Px(300.0)}>
      <LineChart data={processData(data)}>
        <Line _type=`monotone dataKey="temperature" stroke="#8884d8" />
        <CartesianGrid stroke="#ccc" />
        <XAxis dataKey="time" />
        <YAxis />
        <Tooltip />
      </LineChart>
    </ResponsiveContainer>
  );