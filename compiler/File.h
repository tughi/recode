/* Copyright (C) 2024 Stefan Selariu */

#ifndef __FILE_H__
#define __FILE_H__

#include "Writer.h"

Writer *create_file_writer(FILE *file);

extern Writer *stdout_writer;
extern Writer *stderr_writer;

void init_file_module();

#endif
