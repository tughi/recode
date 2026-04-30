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
	@if [ -t 1 ]; then \
		green=$$(printf '\033[32m'); red=$$(printf '\033[31m'); bold=$$(printf '\033[1m'); reset=$$(printf '\033[0m'); \
	else \
		green=; red=; bold=; reset=; \
	fi; \
	pass=0; fail=0; total=0; \
	for f in tests/*.ir; do \
		total=$$((total + 1)); \
		expected=$$(sed -n '1s/^; exit: \([0-9][0-9]*\)$$/\1/p' $$f); \
		: $${expected:=0}; \
		$(TARGET) $$f >/dev/null; actual=$$?; \
		if [ "$$actual" = "$$expected" ]; then \
			printf '%sPASS%s %s\n' "$$green" "$$reset" "$$f"; \
			pass=$$((pass + 1)); \
		else \
			printf '%sFAIL%s %s (got %s, expected %s)\n' "$$red" "$$reset" "$$f" "$$actual" "$$expected"; \
			fail=$$((fail + 1)); \
		fi; \
	done; \
	if [ $$fail -eq 0 ]; then color="$$bold$$green"; else color="$$bold$$red"; fi; \
	printf '%s%d/%d passed%s\n' "$$color" "$$pass" "$$total" "$$reset"; \
	[ $$fail -eq 0 ]

clean:
	rm -rf $(BUILD)

.PHONY: clean test
