#pragma once

#include <stdio.h>
#include <stdlib.h>

#define panic()                                                                  \
    do {                                                                         \
        fprintf(stderr, "%s:%d: \033[0;91mPanic!\033[0m\n", __FILE__, __LINE__); \
        exit(1);                                                                 \
    } while (0)

#define todo(message)                                                                       \
    do {                                                                                    \
        fprintf(stderr, "%s:%d: \033[0;95mTODO: %s\033[0m\n", __FILE__, __LINE__, message); \
        exit(1);                                                                            \
    } while (0)
