#include "test.h"
#include "token.h"

void *malloc(uintmax_t size);

#line 3 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
int32_t test__main() {
#line 4 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
    struct token_String label = token__string__anon((struct String){.data = "forty-two", .length = 9});
#line 5 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
    if (label.lexeme.length == 9u) {
#line 6 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
        {
#line 6 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
            int32_t __001__ = 0;
#line 6 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
            return __001__;
#line 6 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
        }
#line 7 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
    }
#line 8 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
    {
#line 8 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
        int32_t __002__ = 1;
#line 8 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
        return __002__;
#line 8 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
    }
#line 9 "tests/17__builtin_overload/003__user_string_wraps_builtin/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

