#include "Debugger.h"
#include "File.h"
#include "Interpreter.h"
#include "Parser.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    bool debug_mode = false;
    int arg_index = 1;
    if (arg_index < argc && strcmp(argv[arg_index], "-d") == 0) {
        debug_mode = true;
        arg_index++;
    }

    if (arg_index >= argc) {
        fprintf(stderr, "Usage: Runner [-d] IR [args...]\n");
        return 1;
    }

    File file;
    String path = string_from(argv[arg_index]);
    if (string_equals_cstr(path, "-")) {
        file = load_file_from_stdin();
    } else {
        if (!string_ends_with(path, string_from(".ir"))) {
            fprintf(stderr, "Runner: file must have .ir extension\n");
            return 1;
        }
        file = load_file(path);
    }

    IR_Module *module = parse(tokenize(file), debug_mode);

    if (debug_mode) {
        return (int)debug(module, argc - arg_index, argv + arg_index);
    }
    return (int)interpret(module, argc - arg_index, argv + arg_index, NULL);
}
