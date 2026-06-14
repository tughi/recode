#include "File.h"

#include <dirent.h>
#include <sys/stat.h>

static void file_write_char(FILE *file, char c) {
    fputc(c, file);
}

static Writer *create_file_writer(FILE *file) {
    return Writer__create(file, (void (*)(void *, char))file_write_char);
}

Writer *stdout_writer = NULL;
Writer *stderr_writer = NULL;

void File__init() {
    stdout_writer = create_file_writer(stdout);
    stderr_writer = create_file_writer(stderr);
}

Writer *File__create_writer(String *file_path) {
    FILE *file = fopen(file_path->data, "w");
    if (file == NULL) {
        panic();
    }
    return create_file_writer(file);
}

bool Path__exists(String *file_path) {
    struct stat path_stat;
    return stat(file_path->data, &path_stat) == 0;
}

bool Path__is_directory(String *file_path) {
    struct stat path_stat;
    stat(file_path->data, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

String *Path__get_parent(String *path) {
    String *parent = String__create_copy(path);
    size_t length = parent->length;
    while (length > 0 && parent->data[length - 1] != '/') {
        length--;
    }
    parent->length = length;
    parent->data[length] = '\0';
    return parent;
}

String **Path__get_children(String *path) {
    DIR *dir = opendir(path->data);
    if (dir == NULL) {
        return NULL;
    }

    size_t children_size = 10;
    String **children = malloc(sizeof(String *) * children_size);
    size_t children_length = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (children_length >= children_size - 1) {
            children_size *= 2;
            children = realloc(children, sizeof(String *) * children_size);
            if (children == NULL) {
                panic();
            }
        }
        children[children_length++] = String__create_from(entry->d_name);
    }
    children[children_length] = NULL;

    closedir(dir);

    return children;
}
