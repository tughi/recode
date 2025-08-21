#ifndef __CHECKER_H__
#define __CHECKER_H__

#include "Checked_Code.h"
#include "Parsed_Code.h"

Checked_Source *check(Parsed_Package *parsed_builtin_package, Parsed_Package *parsed_main_package);

#endif
