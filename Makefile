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
	@pass=0; fail=0; total=0; \
	for f in tests/*.ir; do \
		total=$$((total + 1)); \
		expected=$$(sed -n '1s/^; exit: \([0-9][0-9]*\)$$/\1/p' $$f); \
		: $${expected:=0}; \
		$(TARGET) $$f >/dev/null; actual=$$?; \
		if [ "$$actual" = "$$expected" ]; then \
			echo "PASS $$f"; \
			pass=$$((pass + 1)); \
		else \
			echo "FAIL $$f (got $$actual, expected $$expected)"; \
			fail=$$((fail + 1)); \
		fi; \
	done; \
	echo "$$pass/$$total passed"; \
	[ $$fail -eq 0 ]

clean:
	rm -rf $(BUILD)

.PHONY: clean test
