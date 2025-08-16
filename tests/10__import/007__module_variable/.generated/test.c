#include "test.h"
#include "numbers.h"

void *malloc(uintmax_t size);

#line 3 "tests/10__import/007__module_variable/test.code"
int32_t test__main() {
#line 4 "tests/10__import/007__module_variable/test.code"
    return numbers__forty_two - 42;
#line 5 "tests/10__import/007__module_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

