CC = cc
CFLAGS = -std=c11 -Wall -Wextra -g

BUILD = build
TARGET = $(BUILD)/Runner
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

-include $(DEPS)

$(BUILD):
	mkdir -p $(BUILD)

test: $(TARGET)
	@for f in tests/*.ir; do \
		echo "=== $$f ==="; \
		$(TARGET) $$f; \
	done

clean:
	rm -rf $(BUILD)

.PHONY: clean test
