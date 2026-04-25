#include "test.h"
#include "token.h"

void *malloc(uintmax_t size);

#line 5 "tests/17__builtin_overload/003__user_string_wraps_builtin/token/string.code"
struct token_String token__string__anon(struct String lexeme) {
#line 6 "tests/17__builtin_overload/003__user_string_wraps_builtin/token/string.code"
    struct String lexeme_copy = lexeme;
#line 7 "tests/17__builtin_overload/003__user_string_wraps_builtin/token/string.code"
    {
#line 7 "tests/17__builtin_overload/003__user_string_wraps_builtin/token/string.code"
        struct token_String __001__ = (struct token_String){.lexeme = *((struct String *) (&lexeme_copy))};
#line 7 "tests/17__builtin_overload/003__user_string_wraps_builtin/token/string.code"
        return __001__;
#line 9 "tests/17__builtin_overload/003__user_string_wraps_builtin/token/string.code"
    }
#line 10 "tests/17__builtin_overload/003__user_string_wraps_builtin/token/string.code"
}

