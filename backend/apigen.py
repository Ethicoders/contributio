import os
from tree_sitter import Language, Parser
import tree_sitter_elixir

LANGUAGE = Language(tree_sitter_elixir.language())
parser = Parser(LANGUAGE)


def extract_public_functions(file_path):
    with open(file_path, "r") as f:
        code = f.read()

    tree = parser.parse(bytes(code, "utf8"))
    root_node = tree.root_node

    public_functions = []

    for node in root_node.children[0].children:
        if node.type == "do_block":
            for node in node.children:
                if node.type == "call":
                    if (
                        node.children[0].type == "identifier"
                        and node.children[0].text.decode("utf8") != "defp"
                    ):
                        identifier = node.children[1].children[0]
                        function_name = identifier.children[0].text.decode("utf8")

                        parameters = [
                            param.text.decode("utf8")
                            for param in identifier.children[1].children
                            if param.type == "identifier"
                        ]

                        public_functions.append(
                            {"name": function_name, "parameters": parameters}
                        )

    return public_functions


if __name__ == "__main__":
    file_path = "./lib/contributio_web/schema/rpc_impl.ex"

    if not os.path.exists(file_path):
        print(f"File not found: {file_path}")
    else:
        functions = extract_public_functions(file_path)
        print("Public functions and their parameters:")
        for func in functions:
            function_name_camel = ''.join(
                word.capitalize() if i > 0 else word
                for i, word in enumerate(func['name'].split('_'))
            )
            parameters = ', '.join(func['parameters'])
            print(f"let {function_name_camel} = async ({parameters}) => {{}}")
