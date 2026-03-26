#ifndef __PARSER_H__
#define __PARSER_H__

#include "Parsed_Code.h"

Parsed_Package *parse_package(String *source_dir, String *package_name, String *binary_name);

#endif
