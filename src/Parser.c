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
        placeholder->result.type.name = (String){0};
        ir_value_list_add(&parser->function_values, &placeholder->result);
        ir_instruction_list_add(&parser->forward_references, placeholder);
        return &placeholder->result;
    }
    IR_Value *value = ir_value_list_lookup(&parser->global_values, variable.lexeme);
    if (value == NULL) {
        value = malloc(sizeof(IR_Value));
        value->name = variable.lexeme;
        value->type.name = (String){0};
        ir_value_list_add(&parser->global_values, value);
    }
    return value;
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
    String result_type_name = expect_identifier(parser);
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
    instruction->result.type.name = result_type_name;

    if (string_equals_cstr(mnemonic, "add")) {
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__ADD;
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
            String literal = parser->current.identifier.lexeme;
            if (string_equals_cstr(literal, "true")) {
                instruction->const_instruction.value = 1;
                advance(parser);
                return instruction;
            }
            if (string_equals_cstr(literal, "false")) {
                instruction->const_instruction.value = 0;
                advance(parser);
                return instruction;
            }
            parse_error_current(parser, "Unknown const literal '%.*s'", STRING(literal));
        }
        bool negative = false;
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '-') {
            negative = true;
            advance(parser);
        }
        int64_t value = expect_integer(parser);
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
    ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
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
        if (string_equals_cstr(mnemonic, "br")) {
            return parse_br_instruction(parser);
        }
        if (string_equals_cstr(mnemonic, "jmp")) {
            return parse_jmp_instruction(parser);
        }
        if (string_equals_cstr(mnemonic, "ret")) {
            return parse_ret_instruction(parser);
        }
        parse_error(parser, mnemonic_location, "Unknown mnemonic '%.*s'", STRING(mnemonic));
    }

    parse_error_current(parser, "Unexpected token in instruction");
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
        function_value->type.name = (String){0};
        ir_value_list_add(&parser->global_values, function_value);
    }

    parser->function_values.size = 0;
    parser->forward_references.size = 0;

    skip_spaces(parser);
    while (parser->current.kind == TOKEN_KIND__VARIABLE && parser->current.variable.prefix == '%') {
        String parameter_name = expect_variable(parser, '%').lexeme;
        expect_other(parser, ':');
        skip_spaces(parser);
        String parameter_type = expect_identifier(parser);

        IR_Value *parameter = malloc(sizeof(IR_Value));
        parameter->name = parameter_name;
        parameter->type.name = parameter_type;
        ir_value_list_add(&function.parameters, parameter);
        ir_value_list_add(&parser->function_values, parameter);

        skip_spaces(parser);
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ',') {
            advance(parser);
            skip_spaces(parser);
        }
    }

    expect_other(parser, ')');
    expect_other(parser, ':');
    skip_spaces(parser);
    String return_type_name = expect_identifier(parser);
    skip_spaces(parser);
    expect_other(parser, '{');

    function.return_type.name = return_type_name;
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

            ir_instruction_list_add(&block->instructions, parse_instruction(parser));
        }
    }

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

    while (true) {
        skip_whitespace(&parser);
        if (parser.current.kind == TOKEN_KIND__END_OF_FILE) {
            break;
        }

        ir_function_list_add(&module->functions, parse_function(&parser));
    }

    return module;
}
