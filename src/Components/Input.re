let initialQuery = "";
let initialSuggestions: list(SuggestionsDecoder.result) = [];

[@react.component]
let make = (~onSelect) => {
  let (query, setQuery) = React.useState(() => initialQuery);
  let (suggestions, setSuggestions) =
    React.useState(() => initialSuggestions);

  let fetchSuggestions = () => {
    let url = "http://localhost:8080/autocomplete?query=" ++ query;

    Js.Promise.(
      Fetch.fetch(url)
      |> then_(Fetch.Response.json)
      |> then_(json => {
           Js.log(json);
           json
           |> SuggestionsDecoder.decodeSuggestions
           |> (data => setSuggestions(_ => data.results))
           |> resolve;
         })
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
    <input
      type_="text"
      onChange={event => event->ReactEvent.Form.target##value->setQuery}
    />
    <ul>
      {React.array(
         Array.of_list(
           List.map(
             (suggestion: SuggestionsDecoder.result) =>
               <li
                 key={suggestion.name}
                 onClick={_event =>
                   onSelect(_currentLocation => suggestion.name)
                 }>
                 {ReasonReact.string(suggestion.name)}
               </li>,
             suggestions,
           ),
         ),
       )}
    </ul>
  </div>;
};