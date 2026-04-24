#include <dirent.h>

void *libc__open_dir(const char *name) {
    return opendir(name);
}

int libc__close_dir(void *dir) {
    return closedir(dir);
}

void *libc__read_dir(void *dir) {
    return readdir(dir);
}

const char *libc__get_dir_entry_name(void *entry) {
    return ((struct dirent *)entry)->d_name;
}
