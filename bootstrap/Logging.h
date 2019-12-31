#ifndef __recode__logging_h__
#define __recode__logging_h__

#include <stdio.h>
#include <stdlib.h>

#define SGR_RESET "\033[0m"

#define SGR_ERROR "\033[0;37;41m"
#define SGR_INFO "\033[0;30;47m"
#define SGR_WARNING "\033[0;30;43m"

#define SGR_BLACK "\033[0;30m"
#define SGR_CYAN "\033[0;36m"
#define SGR_DEFAULT "\033[0;39m"
#define SGR_GREEN "\033[0;32m"
#define SGR_WHITE_BOLD "\033[0;1;37m"
#define SGR_YELLOW "\033[0;33m"

#define SGR_FAINT_DEFAULT "\033[0;2;39m"
#define SGR_FAINT_YELLOW "\033[0;2;33m"

#define LOG(level, source_file, source_line, format, ...) fprintf(stderr, "%s%s:%d -- ", level, source_file, source_line); printf(format, __VA_ARGS__); printf("%s\n", SGR_RESET)

#define ERROR(source_file, source_line, format, ...) LOG(SGR_ERROR, source_file, source_line, format, __VA_ARGS__)

#define WARNING(source_file, source_line, format, ...) LOG(SGR_WARNING, source_file, source_line, format, __VA_ARGS__)

#define INFO(source_file, source_line, format, ...) LOG(SGR_INFO, source_file, source_line, format, __VA_ARGS__)

#define PANIC(source_file, source_line, format, ...) ERROR(source_file, source_line, format, __VA_ARGS__); exit(1)

#endif
