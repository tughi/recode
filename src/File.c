#include "File.h"
#include <stdlib.h>

String file_read(FILE *file) {
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    rewind(file);
    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    String str = {buffer, length};
    return str;
}
