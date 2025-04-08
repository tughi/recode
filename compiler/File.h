#ifndef __FILE_H__
#define __FILE_H__

#include "String.h"
#include "Writer.h"

extern Writer *stdout_writer;
extern Writer *stderr_writer;

void File__init();

Writer *File__create_writer(String *file_path);

#endif
