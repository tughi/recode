#include "test.h"

void *malloc(uintmax_t size);

#line 3 "tests/08__string/005__extensions/test.code"
struct String str__concat(struct String self, struct String other) {
#line 4 "tests/08__string/005__extensions/test.code"
    if (self.length == 0u) {
#line 5 "tests/08__string/005__extensions/test.code"
        {
#line 5 "tests/08__string/005__extensions/test.code"
            struct String __001__ = other;
#line 5 "tests/08__string/005__extensions/test.code"
            return __001__;
#line 5 "tests/08__string/005__extensions/test.code"
        }
#line 6 "tests/08__string/005__extensions/test.code"
    }
#line 7 "tests/08__string/005__extensions/test.code"
    struct String result = (struct String){.data = ((uint8_t *) malloc(self.length + other.length)), .length = self.length + other.length};
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
            result.data[index] = self_data[index];
#line 17 "tests/08__string/005__extensions/test.code"
            index = index + 1u;
#line 18 "tests/08__string/005__extensions/test.code"
        }
#line 19 "tests/08__string/005__extensions/test.code"
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
            result.data[self.length + index] = other_data[index];
#line 26 "tests/08__string/005__extensions/test.code"
            index = index + 1u;
#line 27 "tests/08__string/005__extensions/test.code"
        }
#line 28 "tests/08__string/005__extensions/test.code"
    }
#line 29 "tests/08__string/005__extensions/test.code"
    {
#line 29 "tests/08__string/005__extensions/test.code"
        struct String __002__ = *((struct String *) (&result));
#line 29 "tests/08__string/005__extensions/test.code"
        return __002__;
#line 29 "tests/08__string/005__extensions/test.code"
    }
#line 30 "tests/08__string/005__extensions/test.code"
}

#line 32 "tests/08__string/005__extensions/test.code"
bool str__equals(struct String self, struct String other) {
#line 33 "tests/08__string/005__extensions/test.code"
    if (self.length != other.length) {
#line 34 "tests/08__string/005__extensions/test.code"
        {
#line 34 "tests/08__string/005__extensions/test.code"
            bool __001__ = false;
#line 34 "tests/08__string/005__extensions/test.code"
            return __001__;
#line 34 "tests/08__string/005__extensions/test.code"
        }
#line 35 "tests/08__string/005__extensions/test.code"
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
        {
#line 41 "tests/08__string/005__extensions/test.code"
            bool __002__ = true;
#line 41 "tests/08__string/005__extensions/test.code"
            return __002__;
#line 41 "tests/08__string/005__extensions/test.code"
        }
#line 42 "tests/08__string/005__extensions/test.code"
    }
#line 43 "tests/08__string/005__extensions/test.code"
    uintmax_t index = 0u;
#line 44 "tests/08__string/005__extensions/test.code"
    while (index < self.length) {
#line 45 "tests/08__string/005__extensions/test.code"
        if (self_data[index] != other_data[index]) {
#line 46 "tests/08__string/005__extensions/test.code"
            {
#line 46 "tests/08__string/005__extensions/test.code"
                bool __003__ = false;
#line 46 "tests/08__string/005__extensions/test.code"
                return __003__;
#line 46 "tests/08__string/005__extensions/test.code"
            }
#line 47 "tests/08__string/005__extensions/test.code"
        }
#line 48 "tests/08__string/005__extensions/test.code"
        index = index + 1u;
#line 49 "tests/08__string/005__extensions/test.code"
    }
#line 50 "tests/08__string/005__extensions/test.code"
    {
#line 50 "tests/08__string/005__extensions/test.code"
        bool __004__ = true;
#line 50 "tests/08__string/005__extensions/test.code"
        return __004__;
#line 50 "tests/08__string/005__extensions/test.code"
    }
#line 51 "tests/08__string/005__extensions/test.code"
}

#line 53 "tests/08__string/005__extensions/test.code"
int32_t test__main() {
#line 54 "tests/08__string/005__extensions/test.code"
    struct String message = str__concat((struct String){.data = "Hello", .length = 5}, (struct String){.data = " world!", .length = 7});
#line 55 "tests/08__string/005__extensions/test.code"
    if (!str__equals(message, (struct String){.data = "Hello world!", .length = 12})) {
#line 56 "tests/08__string/005__extensions/test.code"
        {
#line 56 "tests/08__string/005__extensions/test.code"
            int32_t __001__ = 1;
#line 56 "tests/08__string/005__extensions/test.code"
            return __001__;
#line 56 "tests/08__string/005__extensions/test.code"
        }
#line 57 "tests/08__string/005__extensions/test.code"
    }
#line 58 "tests/08__string/005__extensions/test.code"
    if (!str__equals((struct String){.data = "Hello", .length = 5}, (struct String){.data = "Hello", .length = 5})) {
#line 59 "tests/08__string/005__extensions/test.code"
        {
#line 59 "tests/08__string/005__extensions/test.code"
            int32_t __002__ = 2;
#line 59 "tests/08__string/005__extensions/test.code"
            return __002__;
#line 59 "tests/08__string/005__extensions/test.code"
        }
#line 60 "tests/08__string/005__extensions/test.code"
    }
#line 61 "tests/08__string/005__extensions/test.code"
    if (str__concat((struct String){.data = 0, .length = 0}, (struct String){.data = 0, .length = 0}).length != 0u) {
#line 62 "tests/08__string/005__extensions/test.code"
        {
#line 62 "tests/08__string/005__extensions/test.code"
            int32_t __003__ = 3;
#line 62 "tests/08__string/005__extensions/test.code"
            return __003__;
#line 62 "tests/08__string/005__extensions/test.code"
        }
#line 63 "tests/08__string/005__extensions/test.code"
    }
#line 64 "tests/08__string/005__extensions/test.code"
    {
#line 64 "tests/08__string/005__extensions/test.code"
        int32_t __004__ = 0;
#line 64 "tests/08__string/005__extensions/test.code"
        return __004__;
#line 64 "tests/08__string/005__extensions/test.code"
    }
#line 65 "tests/08__string/005__extensions/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

