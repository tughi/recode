#include "test.h"
#include "source.h"

void *malloc(uintmax_t size);

#line 3 "tests/16__optional/007__import/test.code"
int32_t test__main() {
#line 4 "tests/16__optional/007__import/test.code"
    struct source_Item__opt has_item = (struct source_Item__opt){.variant = 1, .variant_1 = (struct source_Item){.value = 42}};
#line 5 "tests/16__optional/007__import/test.code"
    struct source_Item__opt no_item = (struct source_Item__opt){.variant = 0};
#line 7 "tests/16__optional/007__import/test.code"
    if (has_item.variant == 1) {
#line 8 "tests/16__optional/007__import/test.code"
        if (no_item.variant == 0) {
#line 9 "tests/16__optional/007__import/test.code"
            {
#line 9 "tests/16__optional/007__import/test.code"
                int32_t __001__ = has_item.variant_1.value - 42;
#line 9 "tests/16__optional/007__import/test.code"
                return __001__;
#line 9 "tests/16__optional/007__import/test.code"
            }
#line 10 "tests/16__optional/007__import/test.code"
        }
#line 11 "tests/16__optional/007__import/test.code"
    }
#line 13 "tests/16__optional/007__import/test.code"
    {
#line 13 "tests/16__optional/007__import/test.code"
        int32_t __002__ = 1;
#line 13 "tests/16__optional/007__import/test.code"
        return __002__;
#line 13 "tests/16__optional/007__import/test.code"
    }
#line 14 "tests/16__optional/007__import/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

