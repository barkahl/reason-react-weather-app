let formatTime = time =>
  ReasonDateFns.DateFns.(
    Js.Date.make()
    |> setHours(float_of_string(time) /. 100.)
    |> setMinutes(0.)
    |> format("HH:mm")
  );