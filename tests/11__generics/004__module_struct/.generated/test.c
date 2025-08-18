#include "test.h"
#include "collections.h"

void *malloc(uintmax_t size);

#line 3 "tests/11__generics/004__module_struct/test.code"
int32_t test__main() {
#line 4 "tests/11__generics/004__module_struct/test.code"
    struct collections_List__i32__u32 list = (struct collections_List__i32__u32){};
#line 5 "tests/11__generics/004__module_struct/test.code"
    {
#line 5 "tests/11__generics/004__module_struct/test.code"
        int32_t __001__ = 0;
#line 5 "tests/11__generics/004__module_struct/test.code"
        return __001__;
#line 5 "tests/11__generics/004__module_struct/test.code"
    }
#line 6 "tests/11__generics/004__module_struct/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

