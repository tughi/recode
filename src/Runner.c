#include "File.h"
#include "Interpreter.h"
#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: Runner [<file>]\n");
        return 1;
    }

    String source;
    if (argc == 2) {
        String path = string_from(argv[1]);
        if (!string_ends_with(path, string_from(".ir"))) {
            fprintf(stderr, "Runner: file must have .ir extension\n");
            return 1;
        }

        FILE *file = fopen(path.content, "r");
        if (!file) {
            fprintf(stderr, "Cannot open: %s\n", path.content);
            return 1;
        }

        source = file_read(file);
        fclose(file);
    } else {
        source = file_read(stdin);
    }

    IR_Module *module = parse(source);

    return (int)interpret(module);
}
