#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String;

struct String {
    uint8_t *data;
    uintmax_t length;
};

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/08__string/004__assignment/test.code"
int32_t test__main() {
#line 4 "tests/08__string/004__assignment/test.code"
    struct String message = (struct String){.data = "I am a string!", .length = 14};
#line 5 "tests/08__string/004__assignment/test.code"
    if (message.length != 14) {
#line 6 "tests/08__string/004__assignment/test.code"
        return 1;
    }
#line 8 "tests/08__string/004__assignment/test.code"
    message = (struct String){.data = "I am a different string!", .length = 24};
#line 9 "tests/08__string/004__assignment/test.code"
    if (message.length != 24) {
#line 10 "tests/08__string/004__assignment/test.code"
        return 2;
    }
#line 12 "tests/08__string/004__assignment/test.code"
    struct String *message_ptr = &message;
#line 13 "tests/08__string/004__assignment/test.code"
    *message_ptr = (struct String){.data = "I am an even more different string!", .length = 35};
#line 14 "tests/08__string/004__assignment/test.code"
    if (message.length != 35) {
#line 15 "tests/08__string/004__assignment/test.code"
        return 3;
    }
#line 17 "tests/08__string/004__assignment/test.code"
    return 0;
}

