#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/08__string/003__length/test.code"
int32_t test__main() {
#line 2 "tests/08__string/003__length/test.code"
    struct String message = (struct String){.data = "I have a length!", .length = 16};
#line 3 "tests/08__string/003__length/test.code"
    if (message.length != 16u) {
#line 4 "tests/08__string/003__length/test.code"
        {
#line 4 "tests/08__string/003__length/test.code"
            int32_t __001__ = 1;
#line 4 "tests/08__string/003__length/test.code"
            return __001__;
#line 4 "tests/08__string/003__length/test.code"
        }
#line 5 "tests/08__string/003__length/test.code"
    }
#line 6 "tests/08__string/003__length/test.code"
    struct String *message_ptr = &message;
#line 7 "tests/08__string/003__length/test.code"
    {
#line 7 "tests/08__string/003__length/test.code"
        int32_t __002__ = ((int32_t) message_ptr->length) - 16;
#line 7 "tests/08__string/003__length/test.code"
        return __002__;
#line 7 "tests/08__string/003__length/test.code"
    }
#line 8 "tests/08__string/003__length/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

