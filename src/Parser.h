#pragma once

#include "IR.h"

typedef enum {
    PARSE_MODE__RUN,
    PARSE_MODE__DEBUG,
    PARSE_MODE__PROFILE,
} Parse_Mode;

IR_Module *parse(Lexed_File lexed_file, Parse_Mode mode);
