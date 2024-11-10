#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String;

struct String {
    uint8_t *data;
    uintmax_t length;
};

int32_t main();

#line 1 "tests/08__string/004__assignment/test.code"
int32_t main() {
#line 2 "tests/08__string/004__assignment/test.code"
    struct String message = (struct String){.data = "I am a string!", .length = 14};
#line 3 "tests/08__string/004__assignment/test.code"
    if (message.length != 14) {
#line 4 "tests/08__string/004__assignment/test.code"
        return 1;
    }
#line 6 "tests/08__string/004__assignment/test.code"
    message = (struct String){.data = "I am a different string!", .length = 24};
#line 7 "tests/08__string/004__assignment/test.code"
    if (message.length != 24) {
#line 8 "tests/08__string/004__assignment/test.code"
        return 2;
    }
#line 10 "tests/08__string/004__assignment/test.code"
    struct String *message_ptr = &message;
#line 11 "tests/08__string/004__assignment/test.code"
    *message_ptr = (struct String){.data = "I am an even more different string!", .length = 35};
#line 12 "tests/08__string/004__assignment/test.code"
    if (message.length != 35) {
#line 13 "tests/08__string/004__assignment/test.code"
        return 3;
    }
#line 15 "tests/08__string/004__assignment/test.code"
    return 0;
}

