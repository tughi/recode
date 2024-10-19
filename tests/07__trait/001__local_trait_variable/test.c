#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Animal;

struct Animal {
    void *self;
    int32_t (*legs)(void *self);
};

int32_t main();

#line 5 "tests/07__trait/001__local_trait_variable/test.code"
int32_t main() {
#line 6 "tests/07__trait/001__local_trait_variable/test.code"
    struct Animal animal;
#line 7 "tests/07__trait/001__local_trait_variable/test.code"
    return 0;
}

