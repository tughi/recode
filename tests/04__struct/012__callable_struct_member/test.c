#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Function;

struct Function {
    int32_t (*run)();
};

int32_t forty_two();

int32_t main();

#line 5 "tests/04__struct/012__callable_struct_member/test.code"
int32_t forty_two() {
#line 6 "tests/04__struct/012__callable_struct_member/test.code"
    return 42;
}

#line 9 "tests/04__struct/012__callable_struct_member/test.code"
int32_t main() {
#line 10 "tests/04__struct/012__callable_struct_member/test.code"
    struct Function function = (struct Function){.run = forty_two};
#line 12 "tests/04__struct/012__callable_struct_member/test.code"
    return function.run() - 42;
}

