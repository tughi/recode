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

#line 3 "tests/08__string/003__length/test.code"
int32_t test__main() {
#line 4 "tests/08__string/003__length/test.code"
    struct String message = (struct String){.data = "I have a length!", .length = 16};
#line 5 "tests/08__string/003__length/test.code"
    if (message.length != 16) {
#line 6 "tests/08__string/003__length/test.code"
        return 1;
    }
#line 8 "tests/08__string/003__length/test.code"
    struct String *message_ptr = &message;
#line 9 "tests/08__string/003__length/test.code"
    return ((int32_t) message_ptr->length) - 16;
}

