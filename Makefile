CC = cc
CFLAGS = -std=c11 -Wall -Wextra -g
RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LIBS := $(shell pkg-config --libs raylib)
SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)

BUILD = build
TARGET = $(BUILD)/Runner
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(RAYLIB_LIBS) $(SDL_LIBS)

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) $(SDL_CFLAGS) -MMD -MP -c -o $@ $<

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
		expected=$$(sed -n 's/^; exit: \([0-9][0-9]*\)$$/\1/p' $$f | head -1); \
		: $${expected:=0}; \
		args=$$(sed -n 's/^; args: \(.*\)$$/\1/p' $$f | head -1); \
		eval "set -- $$args"; \
		$(TARGET) $$f "$$@" >/dev/null; actual=$$?; \
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
