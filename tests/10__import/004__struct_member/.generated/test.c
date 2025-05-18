#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 7 "tests/10__import/004__struct_member/test.code"
int32_t test__main() {
#line 8 "tests/10__import/004__struct_member/test.code"
    struct test_Token token = (struct test_Token){.span = (struct source_Span){.start = 0, .end = 42}};
#line 9 "tests/10__import/004__struct_member/test.code"
    return token.span.end - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

