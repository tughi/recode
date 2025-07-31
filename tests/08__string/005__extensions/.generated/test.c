#include "test.h"

#line 3 "tests/08__string/005__extensions/test.code"
struct String str__concat(struct String self, struct String other) {
#line 4 "tests/08__string/005__extensions/test.code"
    if (self.length == 0) {
#line 5 "tests/08__string/005__extensions/test.code"
        return other;
    }
#line 7 "tests/08__string/005__extensions/test.code"
    struct String result = (struct String){.data = ((uint8_t *) malloc(self.length + other.length)), .length = self.length + other.length};
#line 11 "tests/08__string/005__extensions/test.code"
    if (self.length > 0) {
#line 12 "tests/08__string/005__extensions/test.code"
        struct String self_copy = self;
#line 13 "tests/08__string/005__extensions/test.code"
        uint8_t *self_data = ((struct String *) (&self_copy))->data;
#line 14 "tests/08__string/005__extensions/test.code"
        uintmax_t index = 0;
#line 15 "tests/08__string/005__extensions/test.code"
        while (index < self.length) {
#line 16 "tests/08__string/005__extensions/test.code"
            result.data[index] = self_data[index];
#line 17 "tests/08__string/005__extensions/test.code"
            index = index + 1;
        }
    }
#line 20 "tests/08__string/005__extensions/test.code"
    if (other.length > 0) {
#line 21 "tests/08__string/005__extensions/test.code"
        struct String other_copy = other;
#line 22 "tests/08__string/005__extensions/test.code"
        uint8_t *other_data = ((struct String *) (&other_copy))->data;
#line 23 "tests/08__string/005__extensions/test.code"
        uintmax_t index = 0;
#line 24 "tests/08__string/005__extensions/test.code"
        while (index < other.length) {
#line 25 "tests/08__string/005__extensions/test.code"
            result.data[self.length + index] = other_data[index];
#line 26 "tests/08__string/005__extensions/test.code"
            index = index + 1;
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
    uintmax_t index = 0;
#line 44 "tests/08__string/005__extensions/test.code"
    while (index < self.length) {
#line 45 "tests/08__string/005__extensions/test.code"
        if (self_data[index] != other_data[index]) {
#line 46 "tests/08__string/005__extensions/test.code"
            return false;
        }
#line 48 "tests/08__string/005__extensions/test.code"
        index = index + 1;
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
    if (str__concat((struct String){.data = 0, .length = 0}, (struct String){.data = 0, .length = 0}).length != 0) {
#line 62 "tests/08__string/005__extensions/test.code"
        return 3;
    }
#line 64 "tests/08__string/005__extensions/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

