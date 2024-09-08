/* Copyright (C) 2024 Stefan Selariu */

#ifndef __FILE_H__
#define __FILE_H__

#include "Writer.h"

extern Writer *stdout_writer;
extern Writer *stderr_writer;

void File__init();

#endif
