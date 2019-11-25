let initialQuery = "";
let initialSuggestions: list(string) = [];

let mapToRsuiteUiDataItem = suggestions =>
  List.map(
    item =>
      RsuiteUi.RsuiteTypes.DataItemType.make(
        ~value=item,
        ~label=React.string(item),
        (),
      ),
    suggestions,
  );

[@react.component]
let make = (~onSelect) => {
  let (query, setQuery) = React.useState(() => initialQuery);
  let (suggestions, setSuggestions) =
    React.useState(() => initialSuggestions);

  let fetchSuggestions = () => {
    let url = "/api/autocomplete?query=" ++ query;

    Js.Promise.(
      Fetch.fetch(url)
      |> then_(Fetch.Response.json)
      |> then_(json =>
           json
           |> SuggestionsDecoder.decodeSuggestions
           |> (
             data =>
               setSuggestions(_ =>
                 List.map(
                   (item: SuggestionsDecoder.result) => item.name,
                   data.results,
                 )
               )
           )
           |> resolve
         )
    )
    ->ignore;
    ();
  };

  React.useEffect1(
    () => {
      if (String.length(query) > 2) {
        fetchSuggestions();
      } else {
        setSuggestions(_ => initialSuggestions);
      };
      None;
    },
    [|query|],
  );

  <div>
    <RsuiteUi.AutoComplete
      data={Array.of_list(suggestions->mapToRsuiteUiDataItem)}
      onChange={(value, _event) => setQuery(_ => value)}
      onSelect=RsuiteUi.RsuiteTypes.DataItemType.(
        (item: t, _event) => onSelect(_ => item->valueGet)
      )
    />
  </div>;
};