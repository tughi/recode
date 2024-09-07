/* Copyright (C) 2024 Stefan Selariu */

#include "Generator.h"

int32_t main(int32_t argc, char **argv) {
    /*
    TODO: Change CLI to "compile" or "run" a file
        - "compile" transpiles to C
        - "run" build and runs the binary
    */

    if (argc < 3) {
        fprintf(stderr, "Usage: %s SOURCE OUTPUT_FOLDER\n", argv[0]);
        return 1;
    }

    char *source_file_path = argv[1];
    FILE *source_file = fopen(source_file_path, "r");
    if (source_file == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", source_file_path);
        return 1;
    }

    char *output_file_path = argv[2];
    FILE *output_file;
    if (strcmp(output_file_path, "-") == 0) {
        output_file = stdout;
    } else {
        output_file = fopen(output_file_path, "w");
        if (output_file == NULL) {
            fprintf(stderr, "Cannot open file: %s\n", output_file_path);
            return 1;
        }
    }

    Source *source = Source__create(source_file, source_file_path);
    Parsed_Source *parsed_source = parse(source);
    Checked_Source *checked_source = check(parsed_source);
    generate(checked_source);

    fclose(source_file);
    return fclose(output_file);
}
