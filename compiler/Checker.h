/* Copyright (C) 2024 Stefan Selariu */

#ifndef __CHECKER_H__
#define __CHECKER_H__

#include "Parser.h"

typedef struct Checked_Source {
    void *statements;
} Checked_Source;

Checked_Source *check(Parsed_Source *parsed_source);

#endif
