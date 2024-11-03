#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

void *malloc(uint64_t size);

#line 1 "tests/02__any/002__malloc/test.code"
int32_t main() {
#line 2 "tests/02__any/002__malloc/test.code"
    void *mem = malloc(42u);
#line 4 "tests/02__any/002__malloc/test.code"
    return 0;
}

