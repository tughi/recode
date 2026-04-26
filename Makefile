CC = cc
CFLAGS = -std=c11 -Wall -Wextra

BUILD = build
TARGET = $(BUILD)/Runner
SRCS = src/Runner.c src/File.c src/Lexer.c

$(TARGET): $(SRCS) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

.PHONY: clean
