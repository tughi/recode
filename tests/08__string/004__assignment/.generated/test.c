#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/08__string/004__assignment/test.code"
int32_t test__main() {
#line 2 "tests/08__string/004__assignment/test.code"
    struct String message = (struct String){.data = "I am a string!", .length = 14};
#line 3 "tests/08__string/004__assignment/test.code"
    if (message.length != 14u) {
#line 4 "tests/08__string/004__assignment/test.code"
        {
#line 4 "tests/08__string/004__assignment/test.code"
            int32_t __001__ = 1;
#line 4 "tests/08__string/004__assignment/test.code"
            return __001__;
#line 4 "tests/08__string/004__assignment/test.code"
        }
#line 5 "tests/08__string/004__assignment/test.code"
    }
#line 6 "tests/08__string/004__assignment/test.code"
    message = (struct String){.data = "I am a different string!", .length = 24};
#line 7 "tests/08__string/004__assignment/test.code"
    if (message.length != 24u) {
#line 8 "tests/08__string/004__assignment/test.code"
        {
#line 8 "tests/08__string/004__assignment/test.code"
            int32_t __002__ = 2;
#line 8 "tests/08__string/004__assignment/test.code"
            return __002__;
#line 8 "tests/08__string/004__assignment/test.code"
        }
#line 9 "tests/08__string/004__assignment/test.code"
    }
#line 10 "tests/08__string/004__assignment/test.code"
    struct String *message_ptr = &message;
#line 11 "tests/08__string/004__assignment/test.code"
    *message_ptr = (struct String){.data = "I am an even more different string!", .length = 35};
#line 12 "tests/08__string/004__assignment/test.code"
    if (message.length != 35u) {
#line 13 "tests/08__string/004__assignment/test.code"
        {
#line 13 "tests/08__string/004__assignment/test.code"
            int32_t __003__ = 3;
#line 13 "tests/08__string/004__assignment/test.code"
            return __003__;
#line 13 "tests/08__string/004__assignment/test.code"
        }
#line 14 "tests/08__string/004__assignment/test.code"
    }
#line 15 "tests/08__string/004__assignment/test.code"
    {
#line 15 "tests/08__string/004__assignment/test.code"
        int32_t __004__ = 0;
#line 15 "tests/08__string/004__assignment/test.code"
        return __004__;
#line 15 "tests/08__string/004__assignment/test.code"
    }
#line 16 "tests/08__string/004__assignment/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

