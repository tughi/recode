#include "Parser.h"
#include "Lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Lexer lexer;
    Token current;
    IR_Value_List function_values;
    IR_Value_List global_values;
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

static size_t current_position(Parser *parser) {
    return parser->current.identifier.source_position;
}

static String expect_other(Parser *parser, char c) {
    if (parser->current.kind != TOKEN_KIND__OTHER || parser->current.other.value != c) {
        fprintf(stderr, "Parser: expected '%c' at position %zu\n", c, current_position(parser));
        exit(1);
    }
    String lexeme = parser->current.other.lexeme;
    advance(parser);
    return lexeme;
}

static String expect_identifier(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__IDENTIFIER) {
        fprintf(stderr, "Parser: expected identifier at position %zu\n", current_position(parser));
        exit(1);
    }
    String name = parser->current.identifier.lexeme;
    advance(parser);
    return name;
}

static int64_t expect_integer(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__INTEGER) {
        fprintf(stderr, "Parser: expected integer at position %zu\n", current_position(parser));
        exit(1);
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
        fprintf(stderr, "Parser: expected '%c' variable at position %zu\n", prefix, current_position(parser));
        exit(1);
    }
    Variable_Token variable = parser->current.variable;
    advance(parser);
    return variable;
}

static size_t expect_label(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__LABEL) {
        fprintf(stderr, "Parser: expected label at position %zu\n", current_position(parser));
        exit(1);
    }
    size_t value = parser->current.label.value;
    advance(parser);
    return value;
}

static IR_Value *expect_value_reference(Parser *parser) {
    if (parser->current.kind != TOKEN_KIND__VARIABLE) {
        fprintf(stderr, "Parser: expected value reference at position %zu\n", current_position(parser));
        exit(1);
    }
    Variable_Token variable = parser->current.variable;
    advance(parser);
    if (variable.prefix == '%') {
        IR_Value *value = ir_value_list_lookup(&parser->function_values, variable.lexeme);
        if (value == NULL) {
            fprintf(stderr, "Parser: undefined value '%.*s' at position %zu\n", (int)variable.lexeme.length, variable.lexeme.content, variable.source_position);
            exit(1);
        }
        return value;
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

static IR_Block *alloc_block(size_t label) {
    IR_Block *block = malloc(sizeof(IR_Block));
    block->label = label;
    block->instructions = (IR_Instruction_List){0};
    return block;
}

static IR_Instruction *alloc_instruction(void) {
    IR_Instruction *instruction = malloc(sizeof(IR_Instruction));
    instruction->arguments = (IR_Value_List){0};
    return instruction;
}

static IR_Instruction *parse_value_instruction(Parser *parser) {
    String result_name = expect_variable(parser, '%').lexeme;
    expect_other(parser, ':');
    skip_spaces(parser);
    String result_type_name = expect_identifier(parser);
    skip_spaces(parser);
    expect_other(parser, '=');
    skip_spaces(parser);
    String mnemonic = expect_identifier(parser);

    IR_Instruction *instruction = alloc_instruction();
    instruction->result.name = result_name;
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
            fprintf(stderr, "Parser: unknown const literal '%.*s' at position %zu\n", (int)literal.length, literal.content, current_position(parser));
            exit(1);
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
            fprintf(stderr, "Parser: phi requires at least one entry at position %zu\n", current_position(parser));
            exit(1);
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

    fprintf(stderr, "Parser: unknown mnemonic '%.*s' at position %zu\n", (int)mnemonic.length, mnemonic.content, current_position(parser));
    exit(1);
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
        IR_Instruction *instruction = parse_value_instruction(parser);
        ir_value_list_add(&parser->function_values, &instruction->result);
        return instruction;
    }

    if (parser->current.kind == TOKEN_KIND__IDENTIFIER) {
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
        fprintf(stderr, "Parser: unknown mnemonic '%.*s' at position %zu\n", (int)mnemonic.length, mnemonic.content, current_position(parser));
        exit(1);
    }

    fprintf(stderr, "Parser: unexpected token in instruction at position %zu\n", current_position(parser));
    exit(1);
}

static IR_Function parse_function(Parser *parser) {
    String name = expect_variable(parser, '$').lexeme;
    expect_other(parser, '(');

    IR_Function function;
    function.name = name;
    function.parameters = (IR_Value_List){0};

    if (ir_value_list_lookup(&parser->global_values, name) == NULL) {
        IR_Value *function_value = malloc(sizeof(IR_Value));
        function_value->name = name;
        function_value->type.name = (String){0};
        ir_value_list_add(&parser->global_values, function_value);
    }

    parser->function_values.size = 0;

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
            break;
        }
        if (parser->current.kind == TOKEN_KIND__END_OF_FILE) {
            fprintf(stderr, "Parser: unexpected end of file inside function\n");
            exit(1);
        }

        size_t label = expect_label(parser);
        expect_other(parser, ':');

        IR_Block *block = alloc_block(label);
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

IR_Module *parse(String source) {
    Parser parser;
    parser.function_values = (IR_Value_List){0};
    parser.global_values = (IR_Value_List){0};

    lexer_init(&parser.lexer, source);
    parser.current = lexer_next(&parser.lexer);

    IR_Module *module = malloc(sizeof(IR_Module));
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
