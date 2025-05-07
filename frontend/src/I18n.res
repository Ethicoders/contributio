let translations = Dict.fromArray([("home", "Home"), ("account", "Account"), ("projects", "Projects")]);





let lang = "en"; // This should be dynamically set based on user preference
// let bla = translations[lang]["account"]

let t = (key): string => {
  switch (Dict.get(translations, key)) {
  | Some(value) => value
  | None => key // Fallback to the key if translation is not found
  }
};

let tr = (key) => React.string(t(key));