/* Copyright (C) 2024 Stefan Selariu */

#include "Checker.h"
#include "File.h"
#include "Generator.h"
#include "Parser.h"

void help_recode() {
    fprintf(stderr, "Available commands:\n");
    fprintf(stderr, "   \033[1mcode\033[0m    compiles whole program\n");
    fprintf(stderr, "   \033[1mmodule\033[0m  compiles one module\n");
}

Source *read_source_file(int32_t argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: recode %s <file>\n", argv[1]);
        exit(1);
    }

    char *file_path = argv[2];
    if (strstr(file_path, ".code") == NULL) {
        fprintf(stderr, "Expected a .code file\n");
        exit(1);
    }

    return Source__create(String__create_from(file_path));
}

void recode_code(int32_t argc, char **argv) {
    Source *source = read_source_file(argc, argv);
    Parsed_Source *parsed_source = parse(source);
    Checked_Source *checked_source = check(parsed_source);
    generate(stdout_writer, checked_source);
    fflush(stdout);
}

void recode_module(int32_t argc, char **argv) {
    fprintf(stderr, "Not implemented yet\n");
}

int32_t main(int32_t argc, char **argv) {
    File__init();

    if (argc == 1) {
        help_recode();
    } else if (strcmp(argv[1], "code") == 0) {
        recode_code(argc, argv);
    } else if (strcmp(argv[1], "module") == 0) {
        recode_module(argc, argv);
    } else {
        fprintf(stderr, "Unknown command: %s\n\n", argv[1]);
        help_recode();
        return 1;
    }

    return 0;
}
