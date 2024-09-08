/* Copyright (C) 2024 Stefan Selariu */

#include "File.h"
#include "Generator.h"
#include "Tokenizer.h"

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

    return create_source(file_path);
}

void recode_code(int32_t argc, char **argv) {
    Source *code_file = read_source_file(argc, argv);

    Writer *stdout_writer = create_file_writer(stdout);

    Tokenizer *tokenizer = create_tokenizer(code_file);
    Token *token;
    while (token = pTokenizer__next(tokenizer)) {
        pWriter__write__location(stdout_writer, token->location);
        pWriter__write__cstring(stdout_writer, ": ");
        pWriter__write__token_type(stdout_writer, token->type);
        pWriter__end_line(stdout_writer);
        if (token->type == TOKEN_END_OF_FILE) {
            break;
        }
    }
}

void recode_module(int32_t argc, char **argv) {
    fprintf(stderr, "Not implemented yet\n");
}

int32_t main(int32_t argc, char **argv) {
    if (argc == 1) {
        help_recode();
    } else if (strcmp(argv[1], "code") == 0) {
        recode_code(argc, argv);
    } else if (strcmp(argv[1], "module") == 0) {
        recode_module(argc, argv);
    } else {
        fprintf(stderr, "Unknown command: %s\n\n", argv[1]);
        help_recode();
    }

    return 0;
}
