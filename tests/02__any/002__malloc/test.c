#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

void *malloc(uint64_t size);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/02__any/002__malloc/test.code"
int32_t test__main() {
#line 4 "tests/02__any/002__malloc/test.code"
    void *mem = malloc(42u);
#line 6 "tests/02__any/002__malloc/test.code"
    return 0;
}

