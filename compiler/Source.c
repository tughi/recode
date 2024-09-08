/* Copyright (C) 2024 Stefan Selariu */

#include "Source.h"

Source *create_source(char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file: %s\n", file_path);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(file_size + 1);
    if (content == NULL) {
        fprintf(stderr, "Failed to read file: %s\n", file_path);
        exit(1);
    }

    if (fread(content, 1, file_size, file) != file_size) {
        fprintf(stderr, "Failed to read file: %s\n", file_path);
        exit(1);
    }
    content[file_size] = '\0';

    fclose(file);

    Source *source = malloc(sizeof(Source));
    if (source == NULL) {
        fprintf(stderr, "Failed to create source: %s\n", file_path);
        exit(1);
    }

    source->content = content;
    source->file_path = file_path;
    source->file_size = file_size;

    return source;
}
