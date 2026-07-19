#include "Debugger.h"
#include "File.h"
#include "Interpreter.h"
#include "Parser.h"
#include "Profiler.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    bool debug_mode = false;
    bool profile_mode = false;
    const char *profile_path = NULL;
    int arg_index = 1;
    while (arg_index < argc) {
        if (strcmp(argv[arg_index], "-d") == 0) {
            debug_mode = true;
            arg_index++;
        } else if (strcmp(argv[arg_index], "-p") == 0) {
            profile_mode = true;
            arg_index++;
        } else if (strcmp(argv[arg_index], "-o") == 0) {
            if (arg_index + 1 >= argc) {
                fprintf(stderr, "Runner: -o requires an output file\n");
                return 1;
            }
            profile_mode = true;
            profile_path = argv[arg_index + 1];
            arg_index += 2;
        } else {
            break;
        }
    }

    if (arg_index >= argc) {
        fprintf(stderr, "Usage: Runner [-d | -p [-o FILE]] IR [args...]\n");
        return 1;
    }
    if (debug_mode && profile_mode) {
        fprintf(stderr, "Runner: -d and -p cannot be combined\n");
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

    Parse_Mode parse_mode = debug_mode ? PARSE_MODE__DEBUG : (profile_mode ? PARSE_MODE__PROFILE : PARSE_MODE__RUN);
    IR_Module *module = parse(tokenize(file), parse_mode);

    if (debug_mode) {
        return (int)debug(module, argc - arg_index, argv + arg_index);
    }
    int64_t result = interpret(module, argc - arg_index, argv + arg_index, NULL, profile_mode);
    if (profile_mode) {
        if (profile_path != NULL) {
            profile_save(module, profile_path);
        } else {
            profile_show(module);
        }
    }
    return (int)result;
}
