#include "Lexed_Source.h"
#include "Lexer.h"
#include <stdlib.h>

Lexed_Source tokenize(Source source) {
    size_t lexed_source_tokens_capacity = source.content.length * 3 / 5;

    Lexed_Source lexed_source = {
        .source = source,
        .tokens = malloc(lexed_source_tokens_capacity * sizeof(Token)),
    };

    Lexer *lexer = lexer_create(source);
    for (;;) {
        if (lexed_source.tokens_size == lexed_source_tokens_capacity) {
            lexed_source_tokens_capacity = lexed_source_tokens_capacity + lexed_source_tokens_capacity / 2;
            lexed_source.tokens = realloc(lexed_source.tokens, lexed_source_tokens_capacity * sizeof(Token));
        }
        Token token = lexer_next(lexer);
        lexed_source.tokens[lexed_source.tokens_size++] = token;
        if (token.kind == TOKEN_KIND__END_OF_FILE) {
            break;
        }
    }
    lexer_destroy(lexer);

    lexed_source.lines_size = lexed_source.tokens[lexed_source.tokens_size - 1].location.line;
    lexed_source.lines = malloc(lexed_source.lines_size * sizeof(Token *));
    lexed_source.lines[0] = &lexed_source.tokens[0];
    for (size_t i = 0, l = 1; i < lexed_source.tokens_size; i++) {
        if (lexed_source.tokens[i].kind == TOKEN_KIND__END_OF_LINE && i + 1 < lexed_source.tokens_size) {
            lexed_source.lines[l++] = &lexed_source.tokens[i + 1];
        }
    }
    return lexed_source;
}

void lexed_source_destroy(Lexed_Source lexed_source) {
    free(lexed_source.tokens);
    free(lexed_source.lines);
}
