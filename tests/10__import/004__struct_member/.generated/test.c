#include "test.h"
#include "source.h"

void *malloc(uintmax_t size);

#line 7 "tests/10__import/004__struct_member/test.code"
int32_t test__main() {
#line 8 "tests/10__import/004__struct_member/test.code"
    struct test_Token token;
#line 8 "tests/10__import/004__struct_member/test.code"
    {
#line 8 "tests/10__import/004__struct_member/test.code"
        int32_t __001__ = 0;
#line 8 "tests/10__import/004__struct_member/test.code"
        int32_t __002__ = 42;
#line 8 "tests/10__import/004__struct_member/test.code"
        struct source_Span __003__ = (struct source_Span){.start = __001__, .end = __002__};
#line 8 "tests/10__import/004__struct_member/test.code"
        token = (struct test_Token){.span = __003__};
    }
#line 9 "tests/10__import/004__struct_member/test.code"
    return token.span.end - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

