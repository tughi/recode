#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String;

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct String *__make_String_value(struct String value);

void *malloc(uintmax_t size);

struct String str__concat(struct String self, struct String other);

bool str__equals(struct String self, struct String other);

int32_t main();

struct String *__make_String_value(struct String value) {
    struct String *result = (struct String *)malloc(sizeof(struct String));
    *result = value;
    return result;
}

#line 8 "tests/08__string/005__extensions/test.code"
struct String str__concat(struct String self, struct String other) {
#line 9 "tests/08__string/005__extensions/test.code"
    if (self.length == 0) {
#line 10 "tests/08__string/005__extensions/test.code"
        return other;
    }
#line 12 "tests/08__string/005__extensions/test.code"
    struct String result = (struct String){.data = ((uint8_t *) malloc(self.length + other.length)), .length = self.length + other.length};
#line 16 "tests/08__string/005__extensions/test.code"
    if (self.length > 0) {
#line 17 "tests/08__string/005__extensions/test.code"
        struct String self_copy = self;
#line 18 "tests/08__string/005__extensions/test.code"
        uint8_t *self_data = ((struct String *) (&self_copy))->data;
#line 19 "tests/08__string/005__extensions/test.code"
        uintmax_t index = 0;
#line 20 "tests/08__string/005__extensions/test.code"
        while (index < self.length) {
#line 21 "tests/08__string/005__extensions/test.code"
            result.data[index] = self_data[index];
#line 22 "tests/08__string/005__extensions/test.code"
            index = index + 1;
        }
    }
#line 25 "tests/08__string/005__extensions/test.code"
    if (other.length > 0) {
#line 26 "tests/08__string/005__extensions/test.code"
        struct String other_copy = other;
#line 27 "tests/08__string/005__extensions/test.code"
        uint8_t *other_data = ((struct String *) (&other_copy))->data;
#line 28 "tests/08__string/005__extensions/test.code"
        uintmax_t index = 0;
#line 29 "tests/08__string/005__extensions/test.code"
        while (index < other.length) {
#line 30 "tests/08__string/005__extensions/test.code"
            result.data[self.length + index] = other_data[index];
#line 31 "tests/08__string/005__extensions/test.code"
            index = index + 1;
        }
    }
#line 34 "tests/08__string/005__extensions/test.code"
    return *((struct String *) (&result));
}

#line 37 "tests/08__string/005__extensions/test.code"
bool str__equals(struct String self, struct String other) {
#line 38 "tests/08__string/005__extensions/test.code"
    if (self.length != other.length) {
#line 39 "tests/08__string/005__extensions/test.code"
        return false;
    }
#line 41 "tests/08__string/005__extensions/test.code"
    struct String self_copy = self;
#line 42 "tests/08__string/005__extensions/test.code"
    uint8_t *self_data = ((struct String *) (&self_copy))->data;
#line 43 "tests/08__string/005__extensions/test.code"
    struct String other_copy = other;
#line 44 "tests/08__string/005__extensions/test.code"
    uint8_t *other_data = ((struct String *) (&other_copy))->data;
#line 45 "tests/08__string/005__extensions/test.code"
    if (self_data == other_data) {
#line 46 "tests/08__string/005__extensions/test.code"
        return true;
    }
#line 48 "tests/08__string/005__extensions/test.code"
    uintmax_t index = 0;
#line 49 "tests/08__string/005__extensions/test.code"
    while (index < self.length) {
#line 50 "tests/08__string/005__extensions/test.code"
        if (self_data[index] != other_data[index]) {
#line 51 "tests/08__string/005__extensions/test.code"
            return false;
        }
#line 53 "tests/08__string/005__extensions/test.code"
        index = index + 1;
    }
#line 55 "tests/08__string/005__extensions/test.code"
    return true;
}

#line 58 "tests/08__string/005__extensions/test.code"
int32_t main() {
#line 59 "tests/08__string/005__extensions/test.code"
    struct String message = str__concat((struct String){.data = "Hello", .length = 5}, (struct String){.data = " world!", .length = 7});
#line 60 "tests/08__string/005__extensions/test.code"
    if (!str__equals(message, (struct String){.data = "Hello world!", .length = 12})) {
#line 61 "tests/08__string/005__extensions/test.code"
        return 1;
    }
#line 63 "tests/08__string/005__extensions/test.code"
    if (!str__equals((struct String){.data = "Hello", .length = 5}, (struct String){.data = "Hello", .length = 5})) {
#line 64 "tests/08__string/005__extensions/test.code"
        return 2;
    }
#line 66 "tests/08__string/005__extensions/test.code"
    if (str__concat((struct String){.data = 0, .length = 0}, (struct String){.data = 0, .length = 0}).length != 0) {
#line 67 "tests/08__string/005__extensions/test.code"
        return 3;
    }
#line 69 "tests/08__string/005__extensions/test.code"
    return 0;
}

