#include "Parser.h"
#include "Lexer.h"
#include "Panic.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Source source;
    Lexer lexer;
    Token current;
    IR_Type_List *types;
    IR_Value_List function_values;
    IR_Value_List global_values;
    IR_Instruction_List forward_references;
} Parser;

static void advance(Parser *parser) {
    parser->current = lexer_next(&parser->lexer);
}

static void skip_spaces(Parser *parser) {
    while (parser->current.kind == TOKEN_KIND__SPACE) {
        advance(parser);
    }
}

static void skip_whitespace(Parser *parser) {
    while (parser->current.kind == TOKEN_KIND__SPACE || parser->current.kind == TOKEN_KIND__END_OF_LINE) {
        advance(parser);
    }
}

static Source_Location current_location(Parser *parser) {
    return parser->current.identifier.location;
}

static void print_parse_error(Parser *parser, Source_Location location, const char *format, ...) {
    fprintf(stderr, "%.*s:%zu:%zu: ", STRING(parser->source.path), location.line, location.column);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}

#define parse_error(parser, location, ...)                \
    do {                                                  \
        print_parse_error(parser, location, __VA_ARGS__); \
        panic();                                          \
    } while (0)
#define parse_error_current(parser, ...)                                  \
    do {                                                                  \
        print_parse_error(parser, current_location(parser), __VA_ARGS__); \
        panic();                                                          \
    } while (0)

static String expect_other(Parser *parser, char c) {
    if (parser->current.kind != TOKEN_KIND__OTHER || parser->current.other.value != c) {
        parse_error_current(parser, "Expected '%c'", c);
    }
    String lexeme = parser->current.other.lexeme;
    advance(parser);
    return lexeme;
}

static String expect_identifier(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__IDENTIFIER) {
        parse_error_current(parser, "Expected identifier");
    }
    String name = parser->current.identifier.lexeme;
    advance(parser);
    return name;
}

static IR_Type *parse_type(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__IDENTIFIER) {
        parse_error_current(parser, "Expected type");
    }
    Identifier_Token name = parser->current.identifier;
    advance(parser);
    if (string_equals_cstr(name.lexeme, "ptr")) {
        if (parser->current.kind != TOKEN_KIND__OTHER || parser->current.other.value != '<') {
            parse_error_current(parser, "Expected '<' after 'ptr'");
        }
        advance(parser);
        IR_Type *pointee = parse_type(parser);
        if (parser->current.kind != TOKEN_KIND__OTHER || parser->current.other.value != '>') {
            parse_error_current(parser, "Expected '>'");
        }
        advance(parser);
        return ir_type_intern_ptr(parser->types, pointee);
    }
    if (string_equals_cstr(name.lexeme, "bool")) {
        return ir_type_bool();
    }
    if (string_equals_cstr(name.lexeme, "i32")) {
        return ir_type_i32();
    }
    if (string_equals_cstr(name.lexeme, "void")) {
        return ir_type_void();
    }
    parse_error(parser, name.location, "Unknown type '%.*s'", STRING(name.lexeme));
}

static int64_t expect_integer(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__INTEGER) {
        parse_error_current(parser, "Expected integer");
    }
    int64_t value = parser->current.integer.value;
    advance(parser);
    return value;
}

static IR_Value *ir_value_list_lookup(IR_Value_List *list, String name) {
    for (size_t i = list->size; i > 0; i--) {
        IR_Value *value = list->items[i - 1];
        if (value->name.length == name.length && memcmp(value->name.content, name.content, name.length) == 0) {
            return value;
        }
    }
    return NULL;
}

static Variable_Token expect_variable(Parser *parser, char prefix) {
    if (parser->current.kind != TOKEN_KIND__VARIABLE || parser->current.variable.prefix != prefix) {
        parse_error_current(parser, "Expected '%c' variable", prefix);
    }
    Variable_Token variable = parser->current.variable;
    advance(parser);
    return variable;
}

static size_t expect_label(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__LABEL) {
        parse_error_current(parser, "Expected label");
    }
    size_t value = parser->current.label.value;
    advance(parser);
    return value;
}

static IR_Instruction *alloc_instruction(void) {
    IR_Instruction *instruction = malloc(sizeof(IR_Instruction));
    instruction->arguments = (IR_Value_List){0};
    return instruction;
}

static IR_Value *expect_value_reference(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__VARIABLE) {
        parse_error_current(parser, "Expected value reference");
    }
    Variable_Token variable = parser->current.variable;
    advance(parser);
    if (variable.prefix == '%') {
        IR_Value *value = ir_value_list_lookup(&parser->function_values, variable.lexeme);
        if (value != NULL) {
            return value;
        }
        IR_Instruction *placeholder = alloc_instruction();
        placeholder->kind = IR_INSTRUCTION__PLACEHOLDER;
        placeholder->location = variable.location;
        placeholder->result.name = variable.lexeme;
        placeholder->result.type = NULL;
        ir_value_list_add(&parser->function_values, &placeholder->result);
        ir_instruction_list_add(&parser->forward_references, placeholder);
        return &placeholder->result;
    }
    IR_Value *value = ir_value_list_lookup(&parser->global_values, variable.lexeme);
    if (value == NULL) {
        value = malloc(sizeof(IR_Value));
        value->name = variable.lexeme;
        value->type = NULL;
        ir_value_list_add(&parser->global_values, value);
    }
    return value;
}

static void error_prefix(Parser *parser, Source_Location location) {
    fprintf(stderr, "%.*s:%zu:%zu: ", STRING(parser->source.path), location.line, location.column);
}

static void expect_type(Parser *parser, Source_Location location, const char *what, IR_Type *expected, IR_Type *actual) {
    if (!ir_type_equals(expected, actual)) {
        error_prefix(parser, location);
        fprintf(stderr, "%s: expected ", what);
        ir_type_fprintf(stderr, expected);
        fputs(", got ", stderr);
        ir_type_fprintf(stderr, actual);
        fputc('\n', stderr);
        panic();
    }
}

static IR_Type *expect_ptr(Parser *parser, Source_Location location, const char *what, IR_Type *actual) {
    if (actual == NULL || actual->kind != IR_TYPE__PTR) {
        error_prefix(parser, location);
        fprintf(stderr, "%s: expected pointer, got ", what);
        ir_type_fprintf(stderr, actual);
        fputc('\n', stderr);
        panic();
    }
    return actual->pointee;
}

static IR_Block *alloc_block(size_t label, Source_Location location) {
    IR_Block *block = malloc(sizeof(IR_Block));
    block->label = label;
    block->location = location;
    block->instructions = (IR_Instruction_List){0};
    return block;
}

static IR_Instruction *parse_value_instruction(Parser *parser) {
    Variable_Token result_variable = expect_variable(parser, '%');
    String result_name = result_variable.lexeme;
    expect_other(parser, ':');
    skip_spaces(parser);
    IR_Type *result_type = parse_type(parser);
    skip_spaces(parser);
    expect_other(parser, '=');
    skip_spaces(parser);
    String mnemonic = expect_identifier(parser);

    IR_Instruction *instruction = NULL;
    for (size_t i = 0; i < parser->forward_references.size; i++) {
        IR_Instruction *placeholder = parser->forward_references.items[i];
        if (placeholder->result.name.length == result_name.length && memcmp(placeholder->result.name.content, result_name.content, result_name.length) == 0) {
            instruction = placeholder;
            parser->forward_references.items[i] = parser->forward_references.items[--parser->forward_references.size];
            break;
        }
    }
    if (instruction == NULL) {
        if (ir_value_list_lookup(&parser->function_values, result_name) != NULL) {
            parse_error(parser, result_variable.location, "Redefinition of '%.*s'", STRING(result_name));
        }
        instruction = alloc_instruction();
        instruction->result.name = result_name;
        ir_value_list_add(&parser->function_values, &instruction->result);
    }
    instruction->location = result_variable.location;
    instruction->result.type = result_type;

    if (string_equals_cstr(mnemonic, "add")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__ADD;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "alloc")) {
        skip_spaces(parser);
        instruction->alloc_instruction.element_type = parse_type(parser);
        instruction->kind = IR_INSTRUCTION__ALLOC;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "call")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));

        while (true) {
            skip_spaces(parser);
            if (parser->current.kind != TOKEN_KIND__VARIABLE) {
                break;
            }
            ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        }

        instruction->kind = IR_INSTRUCTION__CALL;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_eq")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_EQ;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_ge")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_GE;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_gt")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_GT;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_le")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_LE;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_lt")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_LT;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_ne")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_NE;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "const")) {
        skip_spaces(parser);
        instruction->kind = IR_INSTRUCTION__CONST;
        if (parser->current.kind == TOKEN_KIND__IDENTIFIER) {
            Identifier_Token literal = parser->current.identifier;
            if (string_equals_cstr(literal.lexeme, "true") || string_equals_cstr(literal.lexeme, "false")) {
                expect_type(parser, literal.location, "const bool literal", ir_type_bool(), result_type);
                instruction->const_instruction.value = string_equals_cstr(literal.lexeme, "true") ? 1 : 0;
                advance(parser);
                return instruction;
            }
            parse_error_current(parser, "Unknown const literal '%.*s'", STRING(literal.lexeme));
        }
        Source_Location literal_location = current_location(parser);
        bool negative = false;
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '-') {
            negative = true;
            advance(parser);
        }
        int64_t value = expect_integer(parser);
        expect_type(parser, literal_location, "const integer literal", ir_type_i32(), result_type);
        instruction->const_instruction.value = negative ? -value : value;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "div")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__DIV;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "load")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__LOAD;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "mod")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__MOD;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "mul")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__MUL;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "neg")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__NEG;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "not")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__NOT;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "phi")) {
        instruction->kind = IR_INSTRUCTION__PHI;
        instruction->phi_instruction.labels = NULL;
        size_t count = 0;
        while (true) {
            skip_spaces(parser);
            if (parser->current.kind != TOKEN_KIND__LABEL) {
                break;
            }
            size_t label = expect_label(parser);
            skip_spaces(parser);
            IR_Value *value = expect_value_reference(parser);

            instruction->phi_instruction.labels = realloc(instruction->phi_instruction.labels, (count + 1) * sizeof(size_t));
            instruction->phi_instruction.labels[count++] = label;
            ir_value_list_add(&instruction->arguments, value);
        }
        if (count == 0) {
            parse_error_current(parser, "Phi requires at least one entry");
        }
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "sub")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__SUB;
        return instruction;
    }

    parse_error_current(parser, "Unknown mnemonic '%.*s'", STRING(mnemonic));
}

static IR_Instruction *parse_br_instruction(Parser *parser) {
    skip_spaces(parser);
    IR_Value *condition = expect_value_reference(parser);
    skip_spaces(parser);
    size_t true_label = expect_label(parser);
    skip_spaces(parser);
    size_t false_label = expect_label(parser);

    IR_Instruction *instruction = alloc_instruction();
    instruction->result = (IR_Value){0};
    instruction->kind = IR_INSTRUCTION__BR;
    ir_value_list_add(&instruction->arguments, condition);
    instruction->br_instruction.true_label = true_label;
    instruction->br_instruction.false_label = false_label;
    return instruction;
}

static IR_Instruction *parse_jmp_instruction(Parser *parser) {
    skip_spaces(parser);
    size_t label = expect_label(parser);
    IR_Instruction *instruction = alloc_instruction();
    instruction->result = (IR_Value){0};
    instruction->kind = IR_INSTRUCTION__JMP;
    instruction->jmp_instruction.label = label;
    return instruction;
}

static IR_Instruction *parse_ret_instruction(Parser *parser) {
    skip_spaces(parser);
    IR_Instruction *instruction = alloc_instruction();
    instruction->result = (IR_Value){0};
    instruction->kind = IR_INSTRUCTION__RET;
    if (parser->current.kind != TOKEN_KIND__END_OF_LINE && parser->current.kind != TOKEN_KIND__END_OF_FILE) {
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
    }
    return instruction;
}

static IR_Instruction *parse_store_instruction(Parser *parser) {
    skip_spaces(parser);
    IR_Value *pointer = expect_value_reference(parser);
    skip_spaces(parser);
    IR_Value *value = expect_value_reference(parser);
    IR_Instruction *instruction = alloc_instruction();
    instruction->result = (IR_Value){0};
    instruction->kind = IR_INSTRUCTION__STORE;
    ir_value_list_add(&instruction->arguments, pointer);
    ir_value_list_add(&instruction->arguments, value);
    return instruction;
}

static IR_Instruction *parse_instruction(Parser *parser) {
    skip_spaces(parser);

    if (parser->current.kind == TOKEN_KIND__VARIABLE && parser->current.variable.prefix == '%') {
        return parse_value_instruction(parser);
    }

    if (parser->current.kind == TOKEN_KIND__IDENTIFIER) {
        Source_Location mnemonic_location = current_location(parser);
        String mnemonic = parser->current.identifier.lexeme;
        advance(parser);
        IR_Instruction *instruction = NULL;
        if (string_equals_cstr(mnemonic, "br")) {
            instruction = parse_br_instruction(parser);
        } else if (string_equals_cstr(mnemonic, "call")) {
            skip_spaces(parser);
            instruction = alloc_instruction();
            instruction->result = (IR_Value){.type = ir_type_void()};
            instruction->kind = IR_INSTRUCTION__CALL;
            ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
            while (true) {
                skip_spaces(parser);
                if (parser->current.kind != TOKEN_KIND__VARIABLE) {
                    break;
                }
                ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
            }
        } else if (string_equals_cstr(mnemonic, "jmp")) {
            instruction = parse_jmp_instruction(parser);
        } else if (string_equals_cstr(mnemonic, "ret")) {
            instruction = parse_ret_instruction(parser);
        } else if (string_equals_cstr(mnemonic, "store")) {
            instruction = parse_store_instruction(parser);
        } else {
            parse_error(parser, mnemonic_location, "Unknown mnemonic '%.*s'", STRING(mnemonic));
        }
        instruction->location = mnemonic_location;
        return instruction;
    }

    parse_error_current(parser, "Unexpected token in instruction");
}

static void check_instruction(Parser *parser, IR_Function *function, IR_Instruction *instruction) {
    Source_Location loc = instruction->location;
    switch (instruction->kind) {
    case IR_INSTRUCTION__ADD:
    case IR_INSTRUCTION__DIV:
    case IR_INSTRUCTION__MOD:
    case IR_INSTRUCTION__MUL:
    case IR_INSTRUCTION__SUB:
        expect_type(parser, loc, "operand 1", ir_type_i32(), instruction->arguments.items[0]->type);
        expect_type(parser, loc, "operand 2", ir_type_i32(), instruction->arguments.items[1]->type);
        expect_type(parser, loc, "result", ir_type_i32(), instruction->result.type);
        return;
    case IR_INSTRUCTION__ALLOC: {
        IR_Type *pointee = expect_ptr(parser, loc, "alloc result", instruction->result.type);
        expect_type(parser, loc, "alloc pointee", instruction->alloc_instruction.element_type, pointee);
        return;
    }
    case IR_INSTRUCTION__BR:
        expect_type(parser, loc, "br condition", ir_type_bool(), instruction->arguments.items[0]->type);
        return;
    case IR_INSTRUCTION__CALL:
        return;
    case IR_INSTRUCTION__CMP_EQ:
    case IR_INSTRUCTION__CMP_NE:
        expect_type(parser, loc, "comparison operands", instruction->arguments.items[0]->type, instruction->arguments.items[1]->type);
        expect_type(parser, loc, "result", ir_type_bool(), instruction->result.type);
        return;
    case IR_INSTRUCTION__CMP_GE:
    case IR_INSTRUCTION__CMP_GT:
    case IR_INSTRUCTION__CMP_LE:
    case IR_INSTRUCTION__CMP_LT:
        expect_type(parser, loc, "operand 1", ir_type_i32(), instruction->arguments.items[0]->type);
        expect_type(parser, loc, "operand 2", ir_type_i32(), instruction->arguments.items[1]->type);
        expect_type(parser, loc, "result", ir_type_bool(), instruction->result.type);
        return;
    case IR_INSTRUCTION__CONST:
        return;
    case IR_INSTRUCTION__JMP:
        return;
    case IR_INSTRUCTION__LOAD: {
        IR_Type *pointee = expect_ptr(parser, loc, "load pointer", instruction->arguments.items[0]->type);
        expect_type(parser, loc, "load result", pointee, instruction->result.type);
        return;
    }
    case IR_INSTRUCTION__NEG:
        expect_type(parser, loc, "operand", ir_type_i32(), instruction->arguments.items[0]->type);
        expect_type(parser, loc, "result", ir_type_i32(), instruction->result.type);
        return;
    case IR_INSTRUCTION__NOT:
        expect_type(parser, loc, "operand", ir_type_bool(), instruction->arguments.items[0]->type);
        expect_type(parser, loc, "result", ir_type_bool(), instruction->result.type);
        return;
    case IR_INSTRUCTION__PHI:
        for (size_t i = 0; i < instruction->arguments.size; i++) {
            expect_type(parser, loc, "phi incoming", instruction->result.type, instruction->arguments.items[i]->type);
        }
        return;
    case IR_INSTRUCTION__PLACEHOLDER:
        return;
    case IR_INSTRUCTION__RET:
        if (ir_type_equals(function->return_type, ir_type_void())) {
            if (instruction->arguments.size != 0) {
                parse_error(parser, loc, "void function must not return a value");
            }
        } else {
            expect_type(parser, loc, "ret value", function->return_type, instruction->arguments.items[0]->type);
        }
        return;
    case IR_INSTRUCTION__STORE: {
        IR_Type *pointee = expect_ptr(parser, loc, "store pointer", instruction->arguments.items[0]->type);
        expect_type(parser, loc, "store value", pointee, instruction->arguments.items[1]->type);
        return;
    }
    }
}

static void check_function(Parser *parser, IR_Function *function) {
    for (size_t b = 0; b < function->blocks.size; b++) {
        IR_Block *block = function->blocks.items[b];
        for (size_t i = 0; i < block->instructions.size; i++) {
            check_instruction(parser, function, block->instructions.items[i]);
        }
    }
}

static IR_Function parse_function(Parser *parser) {
    Variable_Token name_variable = expect_variable(parser, '$');
    String name = name_variable.lexeme;
    expect_other(parser, '(');

    IR_Function function;
    function.name = name;
    function.location = name_variable.location;
    function.parameters = (IR_Value_List){0};

    if (ir_value_list_lookup(&parser->global_values, name) == NULL) {
        IR_Value *function_value = malloc(sizeof(IR_Value));
        function_value->name = name;
        function_value->type = NULL;
        ir_value_list_add(&parser->global_values, function_value);
    }

    parser->function_values.size = 0;
    parser->forward_references.size = 0;

    skip_spaces(parser);
    while (parser->current.kind == TOKEN_KIND__VARIABLE && parser->current.variable.prefix == '%') {
        String parameter_name = expect_variable(parser, '%').lexeme;
        expect_other(parser, ':');
        skip_spaces(parser);
        IR_Type *parameter_type = parse_type(parser);

        IR_Value *parameter = malloc(sizeof(IR_Value));
        parameter->name = parameter_name;
        parameter->type = parameter_type;
        ir_value_list_add(&function.parameters, parameter);
        ir_value_list_add(&parser->function_values, parameter);

        skip_spaces(parser);
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ',') {
            advance(parser);
            skip_spaces(parser);
        }
    }

    expect_other(parser, ')');
    skip_spaces(parser);
    IR_Type *return_type = ir_type_void();
    if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ':') {
        advance(parser);
        skip_spaces(parser);
        return_type = parse_type(parser);
        skip_spaces(parser);
    }
    expect_other(parser, '{');

    function.return_type = return_type;
    function.blocks = (IR_Block_List){0};

    while (true) {
        skip_whitespace(parser);
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '}') {
            advance(parser);
            if (parser->forward_references.size > 0) {
                IR_Instruction *unresolved = parser->forward_references.items[0];
                parse_error(parser, unresolved->location, "Undefined value %.*s", STRING(unresolved->result.name));
            }
            break;
        }
        if (parser->current.kind == TOKEN_KIND__END_OF_FILE) {
            parse_error_current(parser, "Unexpected end of file inside function");
        }

        Source_Location label_location = current_location(parser);
        size_t label = expect_label(parser);
        expect_other(parser, ':');

        IR_Block *block = alloc_block(label, label_location);
        ir_block_list_add(&function.blocks, block);

        while (true) {
            skip_whitespace(parser);
            if (parser->current.kind == TOKEN_KIND__LABEL) {
                break;
            }
            if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '}') {
                break;
            }
            if (parser->current.kind == TOKEN_KIND__END_OF_FILE) {
                break;
            }

            if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '[') {
                advance(parser);
                while (parser->current.kind != TOKEN_KIND__OTHER || parser->current.other.value != ']') {
                    if (parser->current.kind == TOKEN_KIND__END_OF_FILE) {
                        parse_error_current(parser, "Unterminated live variables annotation");
                    }
                    advance(parser);
                }
                advance(parser);
                continue;
            }

            ir_instruction_list_add(&block->instructions, parse_instruction(parser));
        }
    }

    check_function(parser, &function);
    return function;
}

IR_Module *parse(Source source) {
    Parser parser;
    parser.source = source;
    parser.function_values = (IR_Value_List){0};
    parser.global_values = (IR_Value_List){0};
    parser.forward_references = (IR_Instruction_List){0};

    lexer_init(&parser.lexer, source.content);
    parser.current = lexer_next(&parser.lexer);

    IR_Module *module = malloc(sizeof(IR_Module));
    module->source = source;
    module->functions = (IR_Function_List){0};
    module->types = (IR_Type_List){0};
    parser.types = &module->types;

    while (true) {
        skip_whitespace(&parser);
        if (parser.current.kind == TOKEN_KIND__END_OF_FILE) {
            break;
        }

        ir_function_list_add(&module->functions, parse_function(&parser));
    }

    return module;
}
