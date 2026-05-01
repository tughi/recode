#include "Source.h"
#include "Panic.h"
#include <stdio.h>
#include <stdlib.h>

static String read_all(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    rewind(file);
    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    return (String){buffer, length};
}

Source load_source(String path) {
    FILE *file = fopen(path.content, "r");
    if (!file) {
        fprintf(stderr, "Cannot open: %.*s\n", STRING(path));
        panic();
    }
    String content = read_all(file);
    fclose(file);
    return (Source){path, content};
}

Source load_source_from_stdin(void) {
    return (Source){string_from("<stdin>"), read_all(stdin)};
}
