SRC_DIR = compiler
BUILD_DIR = build/compiler

C_FILES = $(shell find $(SRC_DIR) -name '*.c')

OBJECT_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_FILES))
BIN_FILE = $(BUILD_DIR)/ReCode

.PHONY: all
all: $(BIN_FILE)
	$(BIN_FILE) code tests/01__basics/001__first_function/test.code

$(BIN_FILE): $(OBJECT_FILES)
	cc -g -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	cc -c -ansi -pedantic -Wno-declaration-after-statement -Werror=return-type -Werror=builtin-declaration-mismatch -MD -g -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

-include $(OBJECT_FILES:.o=.d)
