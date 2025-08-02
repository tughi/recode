#include "test.h"

void *malloc(uintmax_t size);

#line 3 "tests/08__string/005__extensions/test.code"
struct String str__concat(struct String self, struct String other) {
#line 4 "tests/08__string/005__extensions/test.code"
    if (self.length == 0u) {
#line 5 "tests/08__string/005__extensions/test.code"
        return other;
    }
#line 7 "tests/08__string/005__extensions/test.code"
    struct String result;
#line 7 "tests/08__string/005__extensions/test.code"
    {
#line 8 "tests/08__string/005__extensions/test.code"
        uintmax_t __001__ = self.length + other.length;
#line 8 "tests/08__string/005__extensions/test.code"
        uint8_t *__002__ = ((uint8_t *) malloc(__001__));
#line 9 "tests/08__string/005__extensions/test.code"
        uintmax_t __003__ = self.length + other.length;
#line 7 "tests/08__string/005__extensions/test.code"
        result = (struct String){.data = __002__, .length = __003__};
    }
#line 11 "tests/08__string/005__extensions/test.code"
    if (self.length > 0u) {
#line 12 "tests/08__string/005__extensions/test.code"
        struct String self_copy = self;
#line 13 "tests/08__string/005__extensions/test.code"
        uint8_t *self_data = ((struct String *) (&self_copy))->data;
#line 14 "tests/08__string/005__extensions/test.code"
        uintmax_t index = 0u;
#line 15 "tests/08__string/005__extensions/test.code"
        while (index < self.length) {
#line 16 "tests/08__string/005__extensions/test.code"
            {
#line 16 "tests/08__string/005__extensions/test.code"
                uintmax_t __001__ = index;
#line 16 "tests/08__string/005__extensions/test.code"
                uintmax_t __002__ = index;
#line 16 "tests/08__string/005__extensions/test.code"
                result.data[__001__] = self_data[__002__];
            }
#line 17 "tests/08__string/005__extensions/test.code"
            index = index + 1u;
        }
    }
#line 20 "tests/08__string/005__extensions/test.code"
    if (other.length > 0u) {
#line 21 "tests/08__string/005__extensions/test.code"
        struct String other_copy = other;
#line 22 "tests/08__string/005__extensions/test.code"
        uint8_t *other_data = ((struct String *) (&other_copy))->data;
#line 23 "tests/08__string/005__extensions/test.code"
        uintmax_t index = 0u;
#line 24 "tests/08__string/005__extensions/test.code"
        while (index < other.length) {
#line 25 "tests/08__string/005__extensions/test.code"
            {
#line 25 "tests/08__string/005__extensions/test.code"
                uintmax_t __001__ = self.length + index;
#line 25 "tests/08__string/005__extensions/test.code"
                uintmax_t __002__ = index;
#line 25 "tests/08__string/005__extensions/test.code"
                result.data[__001__] = other_data[__002__];
            }
#line 26 "tests/08__string/005__extensions/test.code"
            index = index + 1u;
        }
    }
#line 29 "tests/08__string/005__extensions/test.code"
    return *((struct String *) (&result));
}

#line 32 "tests/08__string/005__extensions/test.code"
bool str__equals(struct String self, struct String other) {
#line 33 "tests/08__string/005__extensions/test.code"
    if (self.length != other.length) {
#line 34 "tests/08__string/005__extensions/test.code"
        return false;
    }
#line 36 "tests/08__string/005__extensions/test.code"
    struct String self_copy = self;
#line 37 "tests/08__string/005__extensions/test.code"
    uint8_t *self_data = ((struct String *) (&self_copy))->data;
#line 38 "tests/08__string/005__extensions/test.code"
    struct String other_copy = other;
#line 39 "tests/08__string/005__extensions/test.code"
    uint8_t *other_data = ((struct String *) (&other_copy))->data;
#line 40 "tests/08__string/005__extensions/test.code"
    if (self_data == other_data) {
#line 41 "tests/08__string/005__extensions/test.code"
        return true;
    }
#line 43 "tests/08__string/005__extensions/test.code"
    uintmax_t index = 0u;
#line 44 "tests/08__string/005__extensions/test.code"
    while (index < self.length) {
#line 45 "tests/08__string/005__extensions/test.code"
        {
#line 45 "tests/08__string/005__extensions/test.code"
            uintmax_t __001__ = index;
#line 45 "tests/08__string/005__extensions/test.code"
            uintmax_t __002__ = index;
#line 45 "tests/08__string/005__extensions/test.code"
            if (self_data[__001__] != other_data[__002__]) {
#line 46 "tests/08__string/005__extensions/test.code"
                return false;
            }
        }
#line 48 "tests/08__string/005__extensions/test.code"
        index = index + 1u;
    }
#line 50 "tests/08__string/005__extensions/test.code"
    return true;
}

#line 53 "tests/08__string/005__extensions/test.code"
int32_t test__main() {
#line 54 "tests/08__string/005__extensions/test.code"
    struct String message;
#line 54 "tests/08__string/005__extensions/test.code"
    {
#line 54 "tests/08__string/005__extensions/test.code"
        struct String __001__ = (struct String){.data = "Hello", .length = 5};
#line 54 "tests/08__string/005__extensions/test.code"
        struct String __002__ = (struct String){.data = " world!", .length = 7};
#line 54 "tests/08__string/005__extensions/test.code"
        message = str__concat(__001__, __002__);
    }
#line 55 "tests/08__string/005__extensions/test.code"
    {
#line 55 "tests/08__string/005__extensions/test.code"
        struct String __001__ = message;
#line 55 "tests/08__string/005__extensions/test.code"
        struct String __002__ = (struct String){.data = "Hello world!", .length = 12};
#line 55 "tests/08__string/005__extensions/test.code"
        if (!str__equals(__001__, __002__)) {
#line 56 "tests/08__string/005__extensions/test.code"
            return 1;
        }
    }
#line 58 "tests/08__string/005__extensions/test.code"
    {
#line 58 "tests/08__string/005__extensions/test.code"
        struct String __001__ = (struct String){.data = "Hello", .length = 5};
#line 58 "tests/08__string/005__extensions/test.code"
        struct String __002__ = (struct String){.data = "Hello", .length = 5};
#line 58 "tests/08__string/005__extensions/test.code"
        if (!str__equals(__001__, __002__)) {
#line 59 "tests/08__string/005__extensions/test.code"
            return 2;
        }
    }
#line 61 "tests/08__string/005__extensions/test.code"
    {
#line 61 "tests/08__string/005__extensions/test.code"
        struct String __001__ = (struct String){.data = 0, .length = 0};
#line 61 "tests/08__string/005__extensions/test.code"
        struct String __002__ = (struct String){.data = 0, .length = 0};
#line 61 "tests/08__string/005__extensions/test.code"
        if (str__concat(__001__, __002__).length != 0u) {
#line 62 "tests/08__string/005__extensions/test.code"
            return 3;
        }
    }
#line 64 "tests/08__string/005__extensions/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

