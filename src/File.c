#include "File.h"
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

static void split_lines(File *file) {
    size_t capacity = 0;
    size_t start = 0;
    for (size_t i = 0; i <= file->content.length; i++) {
        if (i < file->content.length && file->content.content[i] != '\n') {
            continue;
        }
        if (i == file->content.length && start == file->content.length && file->lines_size > 0) {
            break; // drop the empty line after a trailing newline
        }
        if (file->lines_size == capacity) {
            capacity = capacity == 0 ? 16 : capacity * 2;
            file->lines = realloc(file->lines, capacity * sizeof(String));
        }
        file->lines[file->lines_size++] = (String){file->content.content + start, i - start};
        start = i + 1;
    }
}

File load_file(String path) {
    FILE *stream = fopen(path.content, "r");
    if (!stream) {
        fprintf(stderr, "Cannot open: %.*s\n", STRING(path));
        panic();
    }
    String content = read_all(stream);
    fclose(stream);
    File file = {.path = path, .content = content};
    split_lines(&file);
    return file;
}

File load_file_from_stdin(void) {
    File file = {.path = string_from("<stdin>"), .content = read_all(stdin)};
    split_lines(&file);
    return file;
}
