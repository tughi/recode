#include "test.h"

#line 1 "tests/02__any/002__malloc/test.code"
int32_t test__main() {
#line 2 "tests/02__any/002__malloc/test.code"
    void *mem;
#line 2 "tests/02__any/002__malloc/test.code"
    {
#line 2 "tests/02__any/002__malloc/test.code"
        uint64_t __001__ = 42u;
#line 2 "tests/02__any/002__malloc/test.code"
        mem = malloc(__001__);
    }
#line 4 "tests/02__any/002__malloc/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

