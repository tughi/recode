#ifndef __PARSER_H__
#define __PARSER_H__

#include "Parsed_Code.h"

Parsed_Package *parse_package(String *project_dir, String *package_dir, String *package_name);

#endif
