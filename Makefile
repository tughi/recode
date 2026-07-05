CC = cc
CFLAGS = -std=c11 -Wall -Wextra -g -O2 -fno-strict-aliasing
RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LIBS := $(shell pkg-config --libs raylib)
SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)

BUILD = build
TARGET = $(BUILD)/Runner
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)
	@true

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(RAYLIB_LIBS) $(SDL_LIBS)

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) $(SDL_CFLAGS) -MMD -MP -c -o $@ $<

-include $(DEPS)

$(BUILD):
	mkdir -p $(BUILD)

test: $(TARGET)
	@tests/run

clean:
	rm -rf $(BUILD)

.PHONY: all clean test
