let rec join = (char: string, list: list(string)): string => {
  switch (list) {
  | [] => raise(Failure("Passed an empty list"))
  | [tail] => tail
  | [head, ...tail] => head ++ char ++ join(char, tail)
  };
};
