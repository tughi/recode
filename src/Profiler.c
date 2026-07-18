#include "Profiler.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t line;
    uint64_t count;
} Line_Count;

static int compare_functions(const void *a, const void *b) {
    const IR_Function *function_a = *(IR_Function *const *)a;
    const IR_Function *function_b = *(IR_Function *const *)b;
    if (function_a->profile.exclusive_time != function_b->profile.exclusive_time) {
        return function_a->profile.exclusive_time > function_b->profile.exclusive_time ? -1 : 1;
    }
    if (function_a->profile.calls != function_b->profile.calls) {
        return function_a->profile.calls > function_b->profile.calls ? -1 : 1;
    }
    return 0;
}

static int compare_line_counts(const void *a, const void *b) {
    const Line_Count *line_a = a;
    const Line_Count *line_b = b;
    if (line_a->count != line_b->count) {
        return line_a->count > line_b->count ? -1 : 1;
    }
    return line_a->line < line_b->line ? -1 : 1;
}

static uint64_t function_instruction_count(IR_Function *function) {
    uint64_t count = 0;
    for (size_t i = 0; i < function->blocks.size; i++) {
        IR_Block *block = function->blocks.items[i];
        count += block->execution_count * block->instructions.size;
    }
    return count;
}

void profile_report(IR_Module *module) {
    IR_Function **functions = malloc(module->functions.size * sizeof(IR_Function *));
    size_t functions_size = 0;
    for (size_t i = 0; i < module->functions.size; i++) {
        IR_Function *function = module->functions.items[i];
        if (function->profile.calls > 0) {
            functions[functions_size++] = function;
        }
    }
    qsort(functions, functions_size, sizeof(IR_Function *), compare_functions);

    fprintf(stderr, "\nFunctions, by self time:\n");
    fprintf(stderr, "     self (ms)    total (ms)        calls  instructions  function\n");
    for (size_t i = 0; i < functions_size; i++) {
        IR_Function *function = functions[i];
        fprintf(stderr, "%14.3f%14.3f%13" PRIu64, (double)function->profile.exclusive_time / 1e6, (double)function->profile.inclusive_time / 1e6, function->profile.calls);
        if (function->is_external) {
            fprintf(stderr, "%14s", "-");
        } else {
            fprintf(stderr, "%14" PRIu64, function_instruction_count(function));
        }
        fprintf(stderr, "  %.*s\n", STRING(function->name));
    }
    free(functions);

    File *file = &module->lexed_file.file;
    Line_Count *line_counts = calloc(file->lines_size + 1, sizeof(Line_Count));
    for (size_t i = 0; i <= file->lines_size; i++) {
        line_counts[i].line = i;
    }
    for (size_t i = 0; i < module->functions.size; i++) {
        IR_Function *function = module->functions.items[i];
        if (function->is_external) {
            continue;
        }
        for (size_t j = 0; j < function->blocks.size; j++) {
            IR_Block *block = function->blocks.items[j];
            for (size_t k = 0; k < block->instructions.size; k++) {
                size_t line = block->instructions.items[k]->location.line;
                if (line <= file->lines_size) {
                    line_counts[line].count += block->execution_count;
                }
            }
        }
    }
    qsort(line_counts, file->lines_size + 1, sizeof(Line_Count), compare_line_counts);

    fprintf(stderr, "\nHottest lines:\n");
    fprintf(stderr, "  executions  line\n");
    for (size_t i = 0; i < file->lines_size + 1 && i < 20; i++) {
        if (line_counts[i].count == 0) {
            break;
        }
        String text = file->lines[line_counts[i].line - 1];
        fprintf(stderr, "%12" PRIu64 "  %4zu: %.*s\n", line_counts[i].count, line_counts[i].line, STRING(text));
    }
    free(line_counts);
}
