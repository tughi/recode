#include "File.h"
#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>

static void print_module(IR_Module *module) {
    for (size_t i = 0; i < module->functions.size; i++) {
        IR_Function *function = &module->functions.items[i];
        printf("%.*s(", (int)function->name.length, function->name.content);
        for (size_t j = 0; j < function->parameters.size; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%.*s: %.*s",
                   (int)function->parameters.items[j]->name.length, function->parameters.items[j]->name.content,
                   (int)function->parameters.items[j]->type.name.length, function->parameters.items[j]->type.name.content);
        }
        printf("): %.*s {\n",
               (int)function->return_type.name.length, function->return_type.name.content);
        for (size_t b = 0; b < function->blocks.size; b++) {
            IR_Block *block = function->blocks.items[b];
            printf("@%zu:\n", block->label);
            for (size_t k = 0; k < block->instructions.size; k++) {
                IR_Instruction *instruction = block->instructions.items[k];
                switch (instruction->kind) {
                case IR_INSTRUCTION__CALL:
                    printf("    %.*s: %.*s = call",
                           (int)instruction->result.name.length, instruction->result.name.content,
                           (int)instruction->result.type.name.length, instruction->result.type.name.content);
                    for (size_t l = 0; l < instruction->arguments.size; l++) {
                        IR_Value *argument = instruction->arguments.items[l];
                        printf(" %.*s", (int)argument->name.length, argument->name.content);
                    }
                    printf("\n");
                    break;
                case IR_INSTRUCTION__CONST:
                    printf("    %.*s: %.*s = const %.*s\n",
                           (int)instruction->result.name.length, instruction->result.name.content,
                           (int)instruction->result.type.name.length, instruction->result.type.name.content,
                           (int)instruction->const_instruction.integer_lexeme.length, instruction->const_instruction.integer_lexeme.content);
                    break;
                case IR_INSTRUCTION__RET:
                    printf("    ret %.*s\n",
                           (int)instruction->arguments.items[0]->name.length, instruction->arguments.items[0]->name.content);
                    break;
                }
            }
        }
        printf("}\n");
        if (i + 1 < module->functions.size) {
            printf("\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: Runner [<file>]\n");
        return 1;
    }

    String source;
    if (argc == 2) {
        String path = string_from(argv[1]);
        if (!string_ends_with(path, string_from(".ir"))) {
            fprintf(stderr, "Runner: file must have .ir extension\n");
            return 1;
        }

        FILE *file = fopen(path.content, "r");
        if (!file) {
            fprintf(stderr, "Cannot open: %s\n", path.content);
            return 1;
        }

        source = file_read(file);
        fclose(file);
    } else {
        source = file_read(stdin);
    }

    IR_Module *module = parse(source);
    print_module(module);

    return 0;
}
