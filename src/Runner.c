#include "Interpreter.h"
#include "Parser.h"
#include "Source.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: Runner IR [args...]\n");
        return 1;
    }

    Source source;
    String path = string_from(argv[1]);
    if (string_equals_cstr(path, "-")) {
        source = load_source_from_stdin();
    } else {
        if (!string_ends_with(path, string_from(".ir"))) {
            fprintf(stderr, "Runner: file must have .ir extension\n");
            return 1;
        }
        source = load_source(path);
    }

    IR_Module *module = parse(source);

    return (int)interpret(module, argc - 1, argv + 1);
}
