#ifndef __recode__logging_h__
#define __recode__logging_h__

#include <iomanip>
#include <iostream>

#define SGR_RESET "\033[0m"

#define SGR_ERROR "\033[37;41m"
#define SGR_INFO "\033[30;47m"
#define SGR_WARNING "\033[30;43m"

#define SGR_BLACK "\033[30m"
#define SGR_CYAN "\033[36m"
#define SGR_DEFAULT "\033[39m"
#define SGR_GREEN "\033[32m"
#define SGR_WHITE_BOLD "\033[37;1m"
#define SGR_YELLOW "\033[33m"

#define SGR_FAINT_DEFAULT "\033[2;39m"
#define SGR_FAINT_YELLOW "\033[2;33m"

#define LOG(level, message) std::cout << level << __FILE__ << ':' << __LINE__ << " -- " << message << SGR_RESET << std::endl

#define ERROR(message) LOG(SGR_ERROR, message)

#define WARNING(message) LOG(SGR_WARNING, message)

#define INFO(message) LOG(SGR_INFO, message)

#endif
