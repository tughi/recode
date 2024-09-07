/* Copyright (C) 2024 Stefan Selariu */

#ifndef __PARSER_H__
#define __PARSER_H__

#include "Source.h"

typedef struct Parsed_Source {
    void *statements;
} Parsed_Source;

Parsed_Source *parse(Source *source);

#endif
