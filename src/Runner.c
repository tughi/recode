#include "File.h"
#include "Lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const char *token_kind_name(Token_Kind kind) {
    switch (kind) {
    case TOKEN_KIND__CHARACTER:
        return "CHARACTER";
    case TOKEN_KIND__END_OF_FILE:
        return "END_OF_FILE";
    case TOKEN_KIND__END_OF_LINE:
        return "END_OF_LINE";
    case TOKEN_KIND__ERROR:
        return "ERROR";
    case TOKEN_KIND__IDENTIFIER:
        return "IDENTIFIER";
    case TOKEN_KIND__INTEGER:
        return "INTEGER";
    case TOKEN_KIND__OTHER:
        return "OTHER";
    case TOKEN_KIND__SPACE:
        return "SPACE";
    case TOKEN_KIND__STRING:
        return "STRING";
    }
    return "UNKNOWN";
}

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

    Lexer lexer;
    lexer_init(&lexer, source);

    for (bool repeat = true; repeat;) {
        Token token = lexer_next(&lexer);
        switch (token.kind) {
        case TOKEN_KIND__END_OF_FILE:
            repeat = false;
        case TOKEN_KIND__END_OF_LINE:
            printf("%-12s\n", token_kind_name(token.kind));
            break;
        case TOKEN_KIND__SPACE:
            printf("%-12s  count=%zu\n", token_kind_name(token.kind), token.space.count);
            break;
        default:
            printf("%-12s  '%.*s'\n", token_kind_name(token.kind), (int)token.identifier.lexeme.length, token.identifier.lexeme.content);
            break;
        }
    }

    return 0;
}
