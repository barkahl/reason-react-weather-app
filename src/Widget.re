let initialLocation = "";

[@react.component]
let make = () => {
  let (location, setLocation) = React.useState(() => initialLocation);

  <div>
    <Input onSelect=setLocation />
    <span> {React.string(location)} </span>
  </div>;
};