#ifndef __FILE_H__
#define __FILE_H__

#include "String.h"
#include "Writer.h"

extern Writer *stdout_writer;
extern Writer *stderr_writer;

void File__init();

Writer *File__create_writer(String *file_path);

bool Path__exists(String *path);
bool Path__is_directory(String *path);
String *Path__get_parent(String *path);
String **Path__get_children(String *path);

#endif
