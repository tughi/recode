/* Copyright (C) 2024 Stefan Selariu */

#ifndef __BUILTINS_H__
#define __BUILTINS_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define panic()                                                              \
    fprintf(stderr, "%s:%d: \033[0;91mPanic!\033[0m\n", __FILE__, __LINE__); \
    exit(1);

#define todo(message)                                                                   \
    fprintf(stderr, "%s:%d: \033[0;95mTODO: %s\033[0m\n", __FILE__, __LINE__, message); \
    exit(1);

#endif
