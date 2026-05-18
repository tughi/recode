#include "Debugger.h"
#include "IR.h"
#include "Interpreter.h"
#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DEBUGGER_MODE__STEP,
    DEBUGGER_MODE__NEXT,
    DEBUGGER_MODE__CONTINUE,
} Debugger_Mode;

typedef struct Debugger {
    Observer observer;
    IR_Module *module;
    Debugger_Mode mode;
    size_t next_depth;
    IR_Instruction_List breakpoints;
} Debugger;

static bool is_breakpoint(Debugger *debugger, IR_Instruction *instruction) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i] == instruction) {
            return true;
        }
    }
    return false;
}

static IR_Instruction *find_instruction_at_line(IR_Module *module, size_t line) {
    for (size_t f = 0; f < module->functions.size; f++) {
        IR_Function *function = module->functions.items[f];
        for (size_t b = 0; b < function->blocks.size; b++) {
            IR_Block *block = function->blocks.items[b];
            for (size_t i = 0; i < block->instructions.size; i++) {
                IR_Instruction *instruction = block->instructions.items[i];
                if (instruction->location.line == line) {
                    return instruction;
                }
            }
        }
    }
    return NULL;
}

static IR_Instruction *add_breakpoint_at_line(Debugger *debugger, size_t line) {
    IR_Instruction *instruction = find_instruction_at_line(debugger->module, line);
    if (instruction == NULL || is_breakpoint(debugger, instruction)) {
        return instruction;
    }
    ir_instruction_list_add(&debugger->breakpoints, instruction);
    return instruction;
}

static bool remove_breakpoint_at_line(Debugger *debugger, size_t line) {
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        if (debugger->breakpoints.items[i]->location.line == line) {
            debugger->breakpoints.items[i] = debugger->breakpoints.items[--debugger->breakpoints.size];
            return true;
        }
    }
    return false;
}

static void list_breakpoints(Debugger *debugger) {
    if (debugger->breakpoints.size == 0) {
        fprintf(stderr, "No breakpoints\n");
        return;
    }
    for (size_t i = 0; i < debugger->breakpoints.size; i++) {
        IR_Instruction *instruction = debugger->breakpoints.items[i];
        fprintf(stderr, "  %.*s:%zu\n", STRING(instruction->location.source), instruction->location.line);
    }
}

static void break_command(Debugger *debugger, Call_Frame *frame, const char *arg) {
    while (*arg == ' ') {
        arg++;
    }
    IR_Instruction *instruction;
    if (*arg == '\0') {
        instruction = frame->instruction;
        if (!is_breakpoint(debugger, instruction)) {
            ir_instruction_list_add(&debugger->breakpoints, instruction);
        }
    } else {
        size_t line = (size_t)atoi(arg);
        if (line == 0) {
            fprintf(stderr, "Usage: b [<line>]\n");
            return;
        }
        instruction = add_breakpoint_at_line(debugger, line);
        if (instruction == NULL) {
            fprintf(stderr, "No instruction at line %zu\n", line);
            return;
        }
    }
    fprintf(stderr, "Breakpoint at %.*s:%zu\n", STRING(instruction->location.source), instruction->location.line);
}

static void delete_command(Debugger *debugger, const char *arg) {
    while (*arg == ' ') {
        arg++;
    }
    size_t line = (size_t)atoi(arg);
    if (line == 0) {
        fprintf(stderr, "Usage: d <line>\n");
        return;
    }
    if (!remove_breakpoint_at_line(debugger, line)) {
        fprintf(stderr, "No breakpoint at line %zu\n", line);
    }
}

static size_t frame_depth(Call_Frame *frame) {
    size_t depth = 0;
    for (Call_Frame *f = frame; f != NULL; f = f->caller) {
        depth++;
    }
    return depth;
}

static String source_line(Lexed_Source *lexed_source, size_t line) {
    if (line < 1 || line > lexed_source->lines_size) {
        return (String){NULL, 0};
    }
    Token *line_token = lexed_source->lines[line - 1];
    if (line_token->kind == TOKEN_KIND__SPACE) {
        line_token++;
    }
    const char *line_content = line_token->lexeme.content;
    while (line_token->kind != TOKEN_KIND__END_OF_LINE && line_token->kind != TOKEN_KIND__END_OF_FILE) {
        line_token++;
    }
    return (String){
        .content = line_content,
        .length = (size_t)(line_token->lexeme.content - line_content),
    };
}

static void print_backtrace(Call_Frame *frame) {
    size_t i = 0;
    for (Call_Frame *f = frame; f != NULL; f = f->caller) {
        fprintf(stderr, "  #%zu %.*s at %.*s:%zu\n", i++, STRING(f->function->name), STRING(f->instruction->location.source), f->instruction->location.line);
    }
}

static IR_Value *lookup_local(IR_Function *function, String name) {
    for (size_t i = 0; i < function->parameters.size; i++) {
        if (string_equals(function->parameters.items[i]->name, name)) {
            return function->parameters.items[i];
        }
    }
    for (size_t b = 0; b < function->blocks.size; b++) {
        IR_Block *block = function->blocks.items[b];
        for (size_t i = 0; i < block->instructions.size; i++) {
            IR_Instruction *instruction = block->instructions.items[i];
            if (instruction->result.name.length > 0 && string_equals(instruction->result.name, name)) {
                return &instruction->result;
            }
        }
    }
    return NULL;
}

static IR_Value *lookup_global(IR_Module *module, String name) {
    for (size_t i = 0; i < module->global_variables.size; i++) {
        if (string_equals(module->global_variables.items[i]->name, name)) {
            return &module->global_variables.items[i]->value;
        }
    }
    for (size_t i = 0; i < module->functions.size; i++) {
        if (string_equals(module->functions.items[i]->name, name)) {
            return &module->functions.items[i]->value;
        }
    }
    return NULL;
}

static void print_typed(IR_Type *type, uint8_t *address) {
    switch (type->kind) {
    case IR_TYPE__BOOL:
        fprintf(stderr, "%s", *(uint8_t *)address ? "true" : "false");
        break;
    case IR_TYPE__I8:
        fprintf(stderr, "%d", *(int8_t *)address);
        break;
    case IR_TYPE__I16:
        fprintf(stderr, "%d", *(int16_t *)address);
        break;
    case IR_TYPE__I32:
        fprintf(stderr, "%d", *(int32_t *)address);
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        fprintf(stderr, "%lld", *(int64_t *)address);
        break;
    case IR_TYPE__U8:
        fprintf(stderr, "%u", *(uint8_t *)address);
        break;
    case IR_TYPE__U16:
        fprintf(stderr, "%u", *(uint16_t *)address);
        break;
    case IR_TYPE__U32:
        fprintf(stderr, "%u", *(uint32_t *)address);
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        fprintf(stderr, "%llu", *(uint64_t *)address);
        break;
    case IR_TYPE__PTR:
    case IR_TYPE__MULTI_PTR:
    case IR_TYPE__PROC:
        fprintf(stderr, "%p", *(void **)address);
        break;
    case IR_TYPE__STRUCT: {
        fprintf(stderr, "{");
        size_t offset = 0;
        for (size_t i = 0; i < type->struct_field_count; i++) {
            IR_Struct_Field *field = type->struct_fields[i];
            fprintf(stderr, "%s .%.*s = ", i == 0 ? "" : ",", STRING(field->name));
            print_typed(field->type, address + offset);
            offset += ir_type_size(field->type);
        }
        fprintf(stderr, " }");
        break;
    }
    case IR_TYPE__VOID:
        fprintf(stderr, "(void)");
        break;
    default:
        fprintf(stderr, "<%zu bytes @ %p>", ir_type_size(type), (void *)address);
        break;
    }
}

static void print_value(Call_Frame *frame, IR_Value *value) {
    uint8_t *base = value->name.content[0] == '$' ? frame->globals_data : frame->frame_data;
    uint8_t *address = base + value->slot.offset;
    fprintf(stderr, "%.*s: ", STRING(value->name));
    fprint_ir_type(stderr, value->type);
    fprintf(stderr, " = ");
    print_typed(value->type, address);
    fprintf(stderr, "\n");
}

static void print_command(Debugger *debugger, Call_Frame *frame, const char *arg) {
    while (*arg == ' ') {
        arg++;
    }
    if (*arg == '\0') {
        fprintf(stderr, "Usage: p <%%name|$name>\n");
        return;
    }
    String name = string_from(arg);
    IR_Value *value;
    if (name.content[0] == '$') {
        value = lookup_global(debugger->module, name);
    } else if (name.content[0] == '%') {
        value = lookup_local(frame->function, name);
    } else {
        fprintf(stderr, "Names must start with '%%' or '$'\n");
        return;
    }
    if (value == NULL) {
        fprintf(stderr, "No value named '%.*s'\n", STRING(name));
        return;
    }
    print_value(frame, value);
}

static void debugger_on_step(Observer *observer, Call_Frame *current_frame) {
    Debugger *debugger = (Debugger *)observer;

    size_t depth = frame_depth(current_frame);
    bool at_breakpoint = is_breakpoint(debugger, current_frame->instruction);
    if (debugger->mode == DEBUGGER_MODE__CONTINUE && !at_breakpoint) {
        return;
    }
    if (debugger->mode == DEBUGGER_MODE__NEXT && depth > debugger->next_depth && !at_breakpoint) {
        return;
    }

    IR_Function *function = current_frame->function;
    IR_Instruction *instruction = current_frame->instruction;
    String instructio_line = source_line(&debugger->module->lexed_source, instruction->location.line);
    fprintf(stderr, "%.*s:%zu > %.*s > @%zu > %.*s\n", STRING(instruction->location.source), instruction->location.line, STRING(function->name), current_frame->block->label, STRING(instructio_line));

    char buffer[256];
    while (true) {
        fprintf(stderr, ">>> ");
        fflush(stderr);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            debugger->mode = DEBUGGER_MODE__CONTINUE;
            return;
        }
        char *command = buffer;
        while (*command == ' ' || *command == '\t') {
            command++;
        }
        size_t length = strlen(command);
        while (length > 0 && (command[length - 1] == ' ' || command[length - 1] == '\n' || command[length - 1] == '\t')) {
            command[--length] = '\0';
        }
        if (length == 0 || strcmp(command, "s") == 0) {
            debugger->mode = DEBUGGER_MODE__STEP;
            return;
        }
        if (strcmp(command, "n") == 0) {
            debugger->mode = DEBUGGER_MODE__NEXT;
            debugger->next_depth = depth;
            return;
        }
        if (strcmp(command, "c") == 0) {
            debugger->mode = DEBUGGER_MODE__CONTINUE;
            return;
        }
        if (strcmp(command, "t") == 0) {
            print_backtrace(current_frame);
            continue;
        }
        if (command[0] == 'p' && (command[1] == ' ' || command[1] == '\0')) {
            print_command(debugger, current_frame, command + 1);
            continue;
        }
        if (command[0] == 'b' && (command[1] == ' ' || command[1] == '\0')) {
            break_command(debugger, current_frame, command + 1);
            continue;
        }
        if (command[0] == 'd' && (command[1] == ' ' || command[1] == '\0')) {
            delete_command(debugger, command + 1);
            continue;
        }
        if (strcmp(command, "l") == 0) {
            list_breakpoints(debugger);
            continue;
        }
        if (strcmp(command, "q") == 0) {
            exit(0);
        }
        if (strcmp(command, "h") == 0 || strcmp(command, "?") == 0) {
            fprintf(stderr, "  s, <enter>  step one instruction\n");
            fprintf(stderr, "  n           step over calls at the current depth\n");
            fprintf(stderr, "  c           run until completion\n");
            fprintf(stderr, "  b [<line>]  set a breakpoint at <line> (or at the current instruction)\n");
            fprintf(stderr, "  d <line>    delete the breakpoint at <line>\n");
            fprintf(stderr, "  l           list all breakpoints\n");
            fprintf(stderr, "  p <name>    print the value of %%name or $name\n");
            fprintf(stderr, "  t           print call backtrace\n");
            fprintf(stderr, "  q           exit the debugger\n");
            continue;
        }
        fprintf(stderr, "Unknown command '%s' (type 'h' for help)\n", command);
    }
}

int64_t debug(IR_Module *module, int argc, char *argv[]) {
    Debugger debugger = {
        .observer = {.on_step = debugger_on_step},
        .module = module,
        .mode = DEBUGGER_MODE__STEP,
        .next_depth = 0,
    };
    return interpret(module, argc, argv, &debugger.observer);
}
