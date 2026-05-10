#include "Parser.h"
#include "Lexer.h"
#include "Panic.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Source source;
    Lexer *lexer;
    Token current;
    Token next;
    IR_Type_List *types;
    IR_Value_List function_values;
    IR_Value_List global_values;
    IR_Instruction_List forward_references;
    uint32_t function_frame_size;
    uint32_t globals_frame_size;
} Parser;

typedef union {
    IR_Function function;
    IR_Global_Variable global_variable;
    struct {
        IR_Value value;
        String name;
        Source_Location location;
        bool is_external;
    };
} IR_Global;

static void advance(Parser *parser) {
    parser->current = parser->next;
    parser->next = lexer_next(parser->lexer);
}

static void skip_spaces(Parser *parser, size_t count) {
    Source_Location location = parser->current.kind == TOKEN_KIND__SPACE ? parser->current.space.location : parser->current.identifier.location;
    size_t actual = 0;
    if (parser->current.kind == TOKEN_KIND__SPACE) {
        actual = parser->current.space.count;
        advance(parser);
    }
    if (actual != count) {
        fprintf(stderr, "%.*s:%zu:%zu: Expected %zu space(s), got %zu\n", STRING(parser->source.path), location.line, location.column, count, actual);
    }
}

static void skip_end_of_lines(Parser *parser) {
    while (parser->current.kind == TOKEN_KIND__END_OF_LINE) {
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
    if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '[') {
        advance(parser);
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '*') {
            advance(parser);
            expect_other(parser, ']');
            IR_Type *pointee = parse_type(parser);
            return ir_type_multipointer(parser->types, pointee);
        }
        IR_Type *pointee = parse_type(parser);
        expect_other(parser, ']');
        return ir_type_pointer(parser->types, pointee);
    }
    if (parser->current.kind != TOKEN_KIND__IDENTIFIER) {
        parse_error_current(parser, "Expected type");
    }
    Identifier_Token name = parser->current.identifier;
    advance(parser);
    if (string_equals_cstr(name.lexeme, "proc")) {
        skip_spaces(parser, 1);
        expect_other(parser, '(');

        IR_Type **param_types = NULL;
        size_t param_count = 0;
        if (!(parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ')') && !(parser->current.kind == TOKEN_KIND__SPACE && parser->next.kind == TOKEN_KIND__OTHER && parser->next.other.value == ')')) {
            skip_spaces(parser, 0);
            for (;;) {
                IR_Type *param_type = parse_type(parser);
                param_types = realloc(param_types, (param_count + 1) * sizeof(IR_Type *));
                param_types[param_count++] = param_type;
                skip_spaces(parser, 0);
                if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ',') {
                    advance(parser);
                    skip_spaces(parser, 1);
                } else {
                    break;
                }
            }
        }
        skip_spaces(parser, 0);
        expect_other(parser, ')');

        IR_Type *return_type;
        if ((parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ':') || (parser->current.kind == TOKEN_KIND__SPACE && parser->next.kind == TOKEN_KIND__OTHER && parser->next.other.value == ':')) {
            skip_spaces(parser, 0);
            expect_other(parser, ':');
            skip_spaces(parser, 1);
            return_type = parse_type(parser);
        } else {
            return_type = ir_type_void();
        }

        IR_Type *proc_type = ir_type_proc(parser->types, param_types, param_count, return_type);
        free(param_types);
        return proc_type;
    }
    if (string_equals_cstr(name.lexeme, "Any")) {
        return ir_type_any();
    }
    if (string_equals_cstr(name.lexeme, "bool")) {
        return ir_type_bool();
    }
    if (string_equals_cstr(name.lexeme, "i8")) {
        return ir_type_i8();
    }
    if (string_equals_cstr(name.lexeme, "i16")) {
        return ir_type_i16();
    }
    if (string_equals_cstr(name.lexeme, "i32")) {
        return ir_type_i32();
    }
    if (string_equals_cstr(name.lexeme, "i64")) {
        return ir_type_i64();
    }
    if (string_equals_cstr(name.lexeme, "isize")) {
        return ir_type_isize();
    }
    if (string_equals_cstr(name.lexeme, "u8")) {
        return ir_type_u8();
    }
    if (string_equals_cstr(name.lexeme, "u16")) {
        return ir_type_u16();
    }
    if (string_equals_cstr(name.lexeme, "u32")) {
        return ir_type_u32();
    }
    if (string_equals_cstr(name.lexeme, "u64")) {
        return ir_type_u64();
    }
    if (string_equals_cstr(name.lexeme, "usize")) {
        return ir_type_usize();
    }
    if (string_equals_cstr(name.lexeme, "void")) {
        return ir_type_void();
    }
    IR_Type *type = ir_type_named_lookup(parser->types, name.lexeme);
    if (type != NULL) {
        return type;
    }
    type = malloc(sizeof(IR_Type));
    type->kind = IR_TYPE__PLACEHOLDER;
    type->name = name.lexeme;
    type->location = name.location;
    ir_type_list_add(parser->types, type);
    return type;
}

static bool is_integer_value_in_range(IR_Type *type, uint64_t value, bool negative) {
    if (negative) {
        switch (type->kind) {
        case IR_TYPE__I8:
            return value <= 128;
        case IR_TYPE__I16:
            return value <= 32768;
        case IR_TYPE__I32:
            return value <= 2147483648ULL;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return value <= 9223372036854775808ULL;
        default:
            return false;
        }
    } else {
        switch (type->kind) {
        case IR_TYPE__I8:
            return value <= 127;
        case IR_TYPE__I16:
            return value <= 32767;
        case IR_TYPE__I32:
            return value <= 2147483647;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return value <= 9223372036854775807ULL;
        case IR_TYPE__U8:
            return value <= 255;
        case IR_TYPE__U16:
            return value <= 65535;
        case IR_TYPE__U32:
            return value <= 4294967295ULL;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return true;
        default:
            return true;
        }
    }
}

static uint64_t expect_integer(Parser *parser, IR_Type *type, bool negative) {
    if (parser->current.kind != TOKEN_KIND__INTEGER) {
        parse_error_current(parser, "Expected integer");
    }
    if (parser->current.integer.overflow) {
        parse_error_current(parser, "Integer literal is too large");
    }
    uint64_t value = parser->current.integer.value;
    if (!is_integer_value_in_range(type, value, negative)) {
        parse_error_current(parser, "Value out of range for %.*s type", STRING(type->name));
    }
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
    IR_Instruction *instruction = calloc(1, sizeof(IR_Instruction));
    return instruction;
}

static uint32_t slot_alignment(IR_Type *type) {
    size_t size = ir_type_size(type);
    if (size == 0) {
        return 1;
    }
    if (size >= 8) {
        return 8;
    }
    return (uint32_t)size;
}

static Frame_Slot reserve_frame_slot(uint32_t *frame_size, IR_Type *type) {
    uint32_t size = (uint32_t)ir_type_size(type);
    uint32_t alignment = slot_alignment(type);
    uint32_t offset = (*frame_size + alignment - 1) & ~(alignment - 1);
    *frame_size = offset + size;
    return (Frame_Slot){.offset = offset, .size = size};
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
        placeholder->result.kind = IR_VALUE__INSTRUCTION_RESULT;
        placeholder->result.name = variable.lexeme;
        placeholder->result.type = NULL;
        ir_value_list_add(&parser->function_values, &placeholder->result);
        ir_instruction_list_add(&parser->forward_references, placeholder);
        return &placeholder->result;
    }
    IR_Value *value = ir_value_list_lookup(&parser->global_values, variable.lexeme);
    if (value == NULL) {
        IR_Global *global = calloc(1, sizeof(IR_Global));
        global->value.kind = IR_VALUE__UNRESOLVED;
        global->value.name = variable.lexeme;
        ir_value_list_add(&parser->global_values, &global->value);
        value = &global->value;
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
        fprint_ir_type(stderr, expected);
        fputs(", got ", stderr);
        fprint_ir_type(stderr, actual);
        fputc('\n', stderr);
        panic();
    }
}

static IR_Type *expect_pointer_type(Parser *parser, Source_Location location, const char *what, IR_Type *actual) {
    if (actual == NULL || actual->kind != IR_TYPE__PTR) {
        error_prefix(parser, location);
        fprintf(stderr, "%s: expected pointer, got ", what);
        fprint_ir_type(stderr, actual);
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

static bool is_integer_type(IR_Type *type) {
    switch (type->kind) {
    case IR_TYPE__I8:
    case IR_TYPE__I16:
    case IR_TYPE__I32:
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
    case IR_TYPE__U8:
    case IR_TYPE__U16:
    case IR_TYPE__U32:
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        return true;
    default:
        return false;
    }
}

static IR_Instruction *parse_value_instruction(Parser *parser) {
    Variable_Token result_variable = expect_variable(parser, '%');
    String result_name = result_variable.lexeme;
    expect_other(parser, ':');
    skip_spaces(parser, 1);
    IR_Type *result_type = parse_type(parser);
    skip_spaces(parser, 1);
    expect_other(parser, '=');
    skip_spaces(parser, 1);
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
    instruction->result.kind = IR_VALUE__INSTRUCTION_RESULT;
    instruction->result.type = result_type;
    instruction->result.slot = reserve_frame_slot(&parser->function_frame_size, result_type);

    if (string_equals_cstr(mnemonic, "add")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__ADD;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "alloc")) {
        skip_spaces(parser, 1);
        IR_Type *element_type = parse_type(parser);
        instruction->alloc_instruction.element_type = element_type;
        instruction->alloc_instruction.payload_slot = reserve_frame_slot(&parser->function_frame_size, element_type);
        instruction->kind = IR_INSTRUCTION__ALLOC;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "call")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));

        while (parser->current.kind == TOKEN_KIND__SPACE) {
            skip_spaces(parser, 1);
            if (parser->current.kind != TOKEN_KIND__VARIABLE) {
                break;
            }
            ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        }

        instruction->kind = IR_INSTRUCTION__CALL;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cast")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CAST;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_eq")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_EQ;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_ge")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_GE;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_gt")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_GT;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_le")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_LE;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_lt")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_LT;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "cmp_ne")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__CMP_NE;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "const")) {
        skip_spaces(parser, 1);
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
        if (parser->current.kind == TOKEN_KIND__CHARACTER) {
            Character_Token literal = parser->current.character;
            expect_type(parser, literal.location, "const char literal", ir_type_u8(), result_type);
            instruction->const_instruction.value = literal.value;
            advance(parser);
            return instruction;
        }
        Source_Location literal_location = current_location(parser);
        bool negative = false;
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '-') {
            negative = true;
            advance(parser);
            skip_spaces(parser, 0);
        }
        uint64_t value = expect_integer(parser, result_type, negative);
        if (parser->current.kind == TOKEN_KIND__IDENTIFIER) {
            IR_Type *literal_type = parse_type(parser);
            if (literal_type != result_type) {
                parse_error(parser, literal_location, "Unexpected literal type");
            }
        }
        instruction->const_instruction.value = (int64_t)(negative ? -value : value);
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "div")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__DIV;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "load")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__LOAD;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "mod")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__MOD;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "mul")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__MUL;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "neg")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__NEG;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "not")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__NOT;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "offset")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        if (parser->current.kind == TOKEN_KIND__VARIABLE) {
            // indexed form: offset %ptr %index
            ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
            instruction->offset_instruction.struct_field = NULL;
            instruction->kind = IR_INSTRUCTION__OFFSET;
            return instruction;
        }
        if (parser->current.kind != TOKEN_KIND__IDENTIFIER) {
            parse_error_current(parser, "Expected struct type name or index variable");
        }
        Identifier_Token type_name = parser->current.identifier;
        advance(parser);
        IR_Type *struct_type = ir_type_named_lookup(parser->types, type_name.lexeme);
        if (struct_type == NULL || struct_type->kind != IR_TYPE__STRUCT) {
            parse_error(parser, type_name.location, "Unknown struct type '%.*s'", STRING(type_name.lexeme));
        }
        skip_spaces(parser, 0);
        expect_other(parser, '.');
        skip_spaces(parser, 0);
        if (parser->current.kind != TOKEN_KIND__IDENTIFIER) {
            parse_error_current(parser, "Expected field name");
        }
        Identifier_Token field_name = parser->current.identifier;
        advance(parser);
        IR_Struct_Field *struct_field = NULL;
        for (size_t i = 0; i < struct_type->struct_field_count; i++) {
            if (string_equals(struct_type->struct_fields[i]->name, field_name.lexeme)) {
                struct_field = struct_type->struct_fields[i];
                break;
            }
        }
        if (struct_field == NULL) {
            parse_error(parser, field_name.location, "Struct '%.*s' has no field '%.*s'", STRING(struct_type->name), STRING(field_name.lexeme));
        }
        instruction->offset_instruction.struct_field = struct_field;
        instruction->kind = IR_INSTRUCTION__OFFSET;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "phi")) {
        instruction->kind = IR_INSTRUCTION__PHI;
        instruction->phi_instruction.labels = NULL;
        size_t count = 0;
        while (parser->current.kind == TOKEN_KIND__SPACE) {
            skip_spaces(parser, 1);
            if (parser->current.kind != TOKEN_KIND__LABEL) {
                break;
            }
            size_t label = expect_label(parser);
            skip_spaces(parser, 1);
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

    if (string_equals_cstr(mnemonic, "struct")) {
        skip_spaces(parser, 1);
        IR_Type *struct_type = parse_type(parser);
        if (struct_type->kind != IR_TYPE__STRUCT) {
            parse_error(parser, result_variable.location, "Not a struct type");
        }
        if (struct_type != result_type) {
            parse_error(parser, result_variable.location, "Unexpected result type");
        }
        IR_Struct_Field **fields = calloc(struct_type->struct_field_count, sizeof(IR_Struct_Field *));
        size_t field_count = 0;
        while (parser->current.kind == TOKEN_KIND__SPACE) {
            if (parser->next.kind != TOKEN_KIND__OTHER || parser->next.other.value != '.') {
                break;
            }
            skip_spaces(parser, 1);
            advance(parser);
            if (parser->current.kind != TOKEN_KIND__IDENTIFIER) {
                parse_error_current(parser, "Expected field name");
            }
            Identifier_Token field_name = parser->current.identifier;
            advance(parser);
            IR_Struct_Field *field = NULL;
            for (size_t i = 0; i < struct_type->struct_field_count; i++) {
                if (string_equals(struct_type->struct_fields[i]->name, field_name.lexeme)) {
                    field = struct_type->struct_fields[i];
                    break;
                }
            }
            if (field == NULL) {
                parse_error(parser, field_name.location, "Struct '%.*s' has no field '%.*s'", STRING(struct_type->name), STRING(field_name.lexeme));
            }
            for (size_t i = 0; i < field_count; i++) {
                if (fields[i] == field) {
                    parse_error(parser, field_name.location, "Duplicate field initialization");
                }
            }
            skip_spaces(parser, 1);
            ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
            fields[field_count++] = field;
        }
        instruction->struct_instruction.fields = fields;
        instruction->kind = IR_INSTRUCTION__STRUCT;
        return instruction;
    }

    if (string_equals_cstr(mnemonic, "sub")) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
        instruction->kind = IR_INSTRUCTION__SUB;
        return instruction;
    }

    parse_error_current(parser, "Unknown mnemonic '%.*s'", STRING(mnemonic));
}

static IR_Instruction *parse_br_instruction(Parser *parser) {
    skip_spaces(parser, 1);
    IR_Value *condition = expect_value_reference(parser);
    skip_spaces(parser, 1);
    size_t true_label = expect_label(parser);
    skip_spaces(parser, 1);
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
    skip_spaces(parser, 1);
    size_t label = expect_label(parser);
    IR_Instruction *instruction = alloc_instruction();
    instruction->result = (IR_Value){0};
    instruction->kind = IR_INSTRUCTION__JMP;
    instruction->jmp_instruction.label = label;
    return instruction;
}

static IR_Instruction *parse_ret_instruction(Parser *parser) {
    IR_Instruction *instruction = alloc_instruction();
    instruction->result = (IR_Value){0};
    instruction->kind = IR_INSTRUCTION__RET;
    if (parser->current.kind == TOKEN_KIND__SPACE) {
        skip_spaces(parser, 1);
        ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
    }
    return instruction;
}

static IR_Instruction *parse_store_instruction(Parser *parser) {
    skip_spaces(parser, 1);
    IR_Value *pointer = expect_value_reference(parser);
    skip_spaces(parser, 1);
    IR_Value *value = expect_value_reference(parser);
    IR_Instruction *instruction = alloc_instruction();
    instruction->result = (IR_Value){0};
    instruction->kind = IR_INSTRUCTION__STORE;
    ir_value_list_add(&instruction->arguments, pointer);
    ir_value_list_add(&instruction->arguments, value);
    return instruction;
}

static IR_Instruction *parse_instruction(Parser *parser) {
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
            skip_spaces(parser, 1);
            instruction = alloc_instruction();
            instruction->result = (IR_Value){.type = ir_type_void()};
            instruction->kind = IR_INSTRUCTION__CALL;
            ir_value_list_add(&instruction->arguments, expect_value_reference(parser));
            while (parser->current.kind == TOKEN_KIND__SPACE) {
                skip_spaces(parser, 1);
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
    Source_Location location = instruction->location;
    switch (instruction->kind) {
    case IR_INSTRUCTION__ADD:
    case IR_INSTRUCTION__DIV:
    case IR_INSTRUCTION__MOD:
    case IR_INSTRUCTION__MUL:
    case IR_INSTRUCTION__SUB: {
        IR_Type *type = instruction->result.type;
        if (!is_integer_type(type)) {
            parse_error(parser, location, "arithmetic result must be an integer type");
        }
        expect_type(parser, location, "operand 1", type, instruction->arguments.items[0]->type);
        expect_type(parser, location, "operand 2", type, instruction->arguments.items[1]->type);
        return;
    }
    case IR_INSTRUCTION__ALLOC: {
        IR_Type *pointee = expect_pointer_type(parser, location, "alloc result", instruction->result.type);
        expect_type(parser, location, "alloc pointee", instruction->alloc_instruction.element_type, pointee);
        return;
    }
    case IR_INSTRUCTION__BR:
        expect_type(parser, location, "br condition", ir_type_bool(), instruction->arguments.items[0]->type);
        return;
    case IR_INSTRUCTION__CALL: {
        IR_Type *callee_type = instruction->arguments.items[0]->type;
        if (callee_type == NULL) {
            return;
        }
        IR_Type *proc_type = expect_pointer_type(parser, location, "call callee", callee_type);
        if (proc_type->kind != IR_TYPE__PROC) {
            parse_error(parser, location, "call callee must be ptr<proc>");
        }
        size_t arg_count = instruction->arguments.size - 1;
        if (arg_count != proc_type->proc.param_count) {
            parse_error(parser, location, "call argument count mismatch: expected %zu, got %zu", proc_type->proc.param_count, arg_count);
        }
        for (size_t i = 0; i < arg_count; i++) {
            expect_type(parser, location, "call argument", proc_type->proc.param_types[i], instruction->arguments.items[i + 1]->type);
        }
        if (instruction->result.type != NULL) {
            expect_type(parser, location, "call result", proc_type->proc.return_type, instruction->result.type);
        }
        return;
    }
    case IR_INSTRUCTION__CAST: {
        IR_Type *from_type = instruction->arguments.items[0]->type;
        IR_Type *to_type = instruction->result.type;
        if (is_integer_type(from_type) && is_integer_type(to_type)) {
            return;
        }
        if ((from_type->kind == IR_TYPE__MULTI_PTR || from_type->kind == IR_TYPE__PTR) && (to_type->kind == IR_TYPE__MULTI_PTR || to_type->kind == IR_TYPE__PTR)) {
            return;
        }
        parse_error(parser, location, "cast requires integer or pointer types");
    }
    case IR_INSTRUCTION__CMP_EQ:
    case IR_INSTRUCTION__CMP_NE:
        expect_type(parser, location, "comparison operands", instruction->arguments.items[0]->type, instruction->arguments.items[1]->type);
        expect_type(parser, location, "result", ir_type_bool(), instruction->result.type);
        return;
    case IR_INSTRUCTION__CMP_GE:
    case IR_INSTRUCTION__CMP_GT:
    case IR_INSTRUCTION__CMP_LE:
    case IR_INSTRUCTION__CMP_LT: {
        IR_Type *type = instruction->arguments.items[0]->type;
        if (!is_integer_type(type)) {
            parse_error(parser, location, "ordered comparison operands must be an integer type");
        }
        expect_type(parser, location, "operand 2", type, instruction->arguments.items[1]->type);
        expect_type(parser, location, "result", ir_type_bool(), instruction->result.type);
        return;
    }
    case IR_INSTRUCTION__CONST:
        return;
    case IR_INSTRUCTION__JMP:
        return;
    case IR_INSTRUCTION__LOAD: {
        IR_Type *pointee = expect_pointer_type(parser, location, "load pointer", instruction->arguments.items[0]->type);
        expect_type(parser, location, "load result", pointee, instruction->result.type);
        return;
    }
    case IR_INSTRUCTION__NEG: {
        IR_Type *type = instruction->result.type;
        if (!is_integer_type(type)) {
            parse_error(parser, location, "neg result must be an integer type");
        }
        expect_type(parser, location, "operand", type, instruction->arguments.items[0]->type);
        return;
    }
    case IR_INSTRUCTION__NOT:
        expect_type(parser, location, "operand", ir_type_bool(), instruction->arguments.items[0]->type);
        expect_type(parser, location, "result", ir_type_bool(), instruction->result.type);
        return;
    case IR_INSTRUCTION__OFFSET: {
        IR_Type *arg_type = instruction->arguments.items[0]->type;
        if (instruction->offset_instruction.struct_field == NULL) {
            // indexed form: [*]T %index → [T]
            if (arg_type == NULL || arg_type->kind != IR_TYPE__MULTI_PTR) {
                error_prefix(parser, location);
                fprintf(stderr, "offset indexed: expected [*]T pointer, got ");
                fprint_ir_type(stderr, arg_type);
                fputc('\n', stderr);
                panic();
            }
            if (!is_integer_type(instruction->arguments.items[1]->type)) {
                parse_error(parser, location, "offset index must be an integer type");
            }
            IR_Type *expected = ir_type_pointer(parser->types, arg_type->pointee);
            expect_type(parser, location, "offset result", expected, instruction->result.type);
        } else {
            // struct form: [T] Struct.field → [T_field]
            IR_Type *pointee = expect_pointer_type(parser, location, "offset struct pointer", arg_type);
            if (pointee->kind != IR_TYPE__STRUCT) {
                parse_error(parser, location, "offset pointer must point to a struct");
            }
            IR_Type *field_type = instruction->offset_instruction.struct_field->type;
            IR_Type *expected = ir_type_pointer(parser->types, field_type);
            expect_type(parser, location, "offset result", expected, instruction->result.type);
        }
        return;
    }
    case IR_INSTRUCTION__PHI:
        for (size_t i = 0; i < instruction->arguments.size; i++) {
            expect_type(parser, location, "phi incoming", instruction->result.type, instruction->arguments.items[i]->type);
        }
        return;
    case IR_INSTRUCTION__PLACEHOLDER:
        return;
    case IR_INSTRUCTION__RET:
        if (ir_type_equals(function->return_type, ir_type_void())) {
            if (instruction->arguments.size != 0) {
                parse_error(parser, location, "void function must not return a value");
            }
        } else {
            expect_type(parser, location, "ret value", function->return_type, instruction->arguments.items[0]->type);
        }
        return;
    case IR_INSTRUCTION__STORE: {
        IR_Type *pointee = expect_pointer_type(parser, location, "store pointer", instruction->arguments.items[0]->type);
        expect_type(parser, location, "store value", pointee, instruction->arguments.items[1]->type);
        return;
    }
    case IR_INSTRUCTION__STRUCT: {
        // IR_Type *struct_type = instruction->result.type;
        // if (instruction->arguments.size != struct_type->struct_field_count) {
        //     parse_error(parser, location, "Expecting %zu fields, not just %zu", struct_type->struct_field_count, instruction->arguments.size);
        // }
        for (size_t i = 0; i < instruction->arguments.size; i++) {
            IR_Struct_Field *field = instruction->struct_instruction.fields[i];
            expect_type(parser, location, "struct field value", field->type, instruction->arguments.items[i]->type);
        }
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

static void parse_type_declaration(Parser *parser) {
    advance(parser);
    skip_spaces(parser, 1);
    Source_Location name_location = current_location(parser);
    String name = expect_identifier(parser);
    skip_spaces(parser, 1);
    expect_other(parser, '=');
    skip_spaces(parser, 1);
    Source_Location body_location = current_location(parser);
    String type_kind = expect_identifier(parser);
    IR_Type *type = ir_type_named_lookup(parser->types, name);
    if (type == NULL) {
        type = malloc(sizeof(IR_Type));
        type->kind = IR_TYPE__PLACEHOLDER;
        type->name = name;
        ir_type_list_add(parser->types, type);
    } else if (type->kind != IR_TYPE__PLACEHOLDER) {
        parse_error(parser, name_location, "Redefinition of type '%.*s'", STRING(name));
    }
    type->location = name_location;
    if (string_equals_cstr(type_kind, "opaque")) {
        type->kind = IR_TYPE__OPAQUE;
        return;
    }
    if (!string_equals_cstr(type_kind, "struct")) {
        parse_error(parser, body_location, "Expected 'opaque' or 'struct', got '%.*s'", STRING(type_kind));
    }
    skip_spaces(parser, 1);
    expect_other(parser, '{');

    IR_Struct_Field **fields = NULL;
    size_t field_count = 0;

    while (true) {
        skip_end_of_lines(parser);
        if (parser->current.kind == TOKEN_KIND__SPACE && parser->next.kind == TOKEN_KIND__OTHER && parser->next.other.value == '}') {
            advance(parser);
        }
        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == '}') {
            advance(parser);
            break;
        }
        skip_spaces(parser, 2);
        Source_Location field_location = current_location(parser);
        String field_name = expect_identifier(parser);
        for (size_t i = 0; i < field_count; i++) {
            if (string_equals(fields[i]->name, field_name)) {
                parse_error(parser, field_location, "Duplicate field '%.*s'", STRING(field_name));
            }
        }
        expect_other(parser, ':');
        skip_spaces(parser, 1);
        Source_Location type_location = current_location(parser);
        IR_Type *field_type = parse_type(parser);
        if (field_type->kind == IR_TYPE__OPAQUE || field_type->kind == IR_TYPE__VOID) {
            parse_error(parser, type_location, "Unsupported struct field type");
        }
        IR_Struct_Field *field = malloc(sizeof(IR_Struct_Field));
        field->name = field_name;
        field->type = field_type;
        fields = realloc(fields, (field_count + 1) * sizeof(IR_Struct_Field *));
        fields[field_count++] = field;
    }

    if (field_count == 0) {
        parse_error(parser, name_location, "Struct '%.*s' must declare at least one field", STRING(name));
    }
    type->kind = IR_TYPE__STRUCT;
    type->struct_fields = fields;
    type->struct_field_count = field_count;
}

static IR_External_Function check_external_function(Parser *parser, IR_Function *function) {
    String name = function->name;
    IR_Type *return_type = function->return_type;
    size_t parameter_count = function->parameters.size;
    IR_Value **parameters = function->parameters.items;
    if (string_equals_cstr(name, "$exit")) {
        if (return_type == ir_type_void() && parameter_count == 1 && parameters[0]->type == ir_type_i32()) {
            return IR_EXTERNAL_FUNCTION__exit;
        }
    } else if (string_equals_cstr(name, "$fputc")) {
        if (return_type == ir_type_i32() && parameter_count == 2 && parameters[0]->type == ir_type_i32() && parameters[1]->type->kind == IR_TYPE__PTR && parameters[1]->type->pointee->kind == IR_TYPE__OPAQUE) {
            return IR_EXTERNAL_FUNCTION__fputc;
        }
    } else if (string_equals_cstr(name, "$free")) {
        if (return_type == ir_type_void() && parameter_count == 1 && parameters[0]->type == ir_type_pointer(parser->types, ir_type_any())) {
            return IR_EXTERNAL_FUNCTION__free;
        }
    } else if (string_equals_cstr(name, "$malloc")) {
        if (return_type == ir_type_pointer(parser->types, ir_type_any()) && parameter_count == 1 && parameters[0]->type == ir_type_usize()) {
            return IR_EXTERNAL_FUNCTION__malloc;
        }
    } else if (string_equals_cstr(name, "$realloc")) {
        if (return_type == ir_type_pointer(parser->types, ir_type_any()) && parameter_count == 2 && parameters[0]->type == ir_type_pointer(parser->types, ir_type_any()) && parameters[1]->type == ir_type_usize()) {
            return IR_EXTERNAL_FUNCTION__realloc;
        }
    }
    parse_error(parser, function->location, "Unsupported external function");
}

static void parse_external(Parser *parser, IR_Module *module) {
    Variable_Token name = expect_variable(parser, '$');
    skip_spaces(parser, 0);
    expect_other(parser, ':');
    skip_spaces(parser, 1);
    IR_Type *type = parse_type(parser);
    skip_spaces(parser, 1);
    expect_other(parser, '=');
    skip_spaces(parser, 1);
    String assignment = expect_identifier(parser);
    if (!string_equals_cstr(assignment, "external")) {
        parse_error(parser, name.location, "Expected 'external'");
    }

    IR_Value *global_value = ir_value_list_lookup(&parser->global_values, name.lexeme);
    IR_Global *global;
    if (global_value != NULL) {
        if (global_value->type != NULL) {
            parse_error(parser, name.location, "Redefinition of '%.*s'", STRING(name.lexeme));
        }
        global = (IR_Global *)global_value;
    } else {
        global = calloc(1, sizeof(IR_Global));
        ir_value_list_add(&parser->global_values, &global->value);
    }
    global->value.name = name.lexeme;
    global->value.type = type;
    global->name = name.lexeme;
    global->location = name.location;
    global->is_external = true;

    if (type->kind == IR_TYPE__PTR && type->pointee->kind == IR_TYPE__PROC) {
        IR_Function *function = &global->function;
        function->value.kind = IR_VALUE__FUNCTION;

        IR_Proc_Type *proc = &type->pointee->proc;
        function->return_type = proc->return_type;
        for (size_t i = 0; i < proc->param_count; i++) {
            IR_Value *param = calloc(1, sizeof(IR_Value));
            param->kind = IR_VALUE__INSTRUCTION_RESULT;
            param->type = proc->param_types[i];
            ir_value_list_add(&function->parameters, param);
        }

        function->which = check_external_function(parser, function);

        function->value.slot = reserve_frame_slot(&parser->globals_frame_size, type);
        ir_function_list_add(&module->functions, function);
    } else {
        IR_Global_Variable *variable = &global->global_variable;
        variable->value.kind = IR_VALUE__GLOBAL_VARIABLE;

        if (type->kind != IR_TYPE__PTR) {
            parse_error(parser, name.location, "External global variable '%.*s' must have a pointer type", STRING(name.lexeme));
        }
        variable->type = type->pointee;
        variable->value.slot = reserve_frame_slot(&parser->globals_frame_size, type);
        ir_global_variable_list_add(&module->global_variables, variable);
    }
}

static IR_Function *parse_function(Parser *parser) {
    Variable_Token function_name = expect_variable(parser, '$');
    expect_other(parser, '(');

    IR_Value *function_value = ir_value_list_lookup(&parser->global_values, function_name.lexeme);
    IR_Function *function;
    if (function_value != NULL) {
        if (function_value->type != NULL) {
            parse_error(parser, function_name.location, "Redefinition of '%.*s'", STRING(function_name.lexeme));
        }
        function = (IR_Function *)function_value;
    } else {
        function = calloc(1, sizeof(IR_Global));
        ir_value_list_add(&parser->global_values, &function->value);
    }
    function->value.kind = IR_VALUE__FUNCTION;
    function->value.name = function_name.lexeme;
    function->name = function_name.lexeme;
    function->location = function_name.location;

    parser->function_values.size = 0;
    parser->forward_references.size = 0;
    parser->function_frame_size = 0;

    while (parser->current.kind == TOKEN_KIND__VARIABLE && parser->current.variable.prefix == '%') {
        String parameter_name = expect_variable(parser, '%').lexeme;
        expect_other(parser, ':');
        skip_spaces(parser, 1);
        IR_Type *parameter_type = parse_type(parser);

        IR_Value *parameter = calloc(1, sizeof(IR_Value));
        parameter->kind = IR_VALUE__INSTRUCTION_RESULT;
        parameter->name = parameter_name;
        parameter->type = parameter_type;
        parameter->slot = reserve_frame_slot(&parser->function_frame_size, parameter_type);
        ir_value_list_add(&function->parameters, parameter);
        ir_value_list_add(&parser->function_values, parameter);

        if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ',') {
            advance(parser);
            skip_spaces(parser, 1);
        }
    }

    expect_other(parser, ')');
    IR_Type *return_type = ir_type_void();
    if (parser->current.kind == TOKEN_KIND__OTHER && parser->current.other.value == ':') {
        advance(parser);
        skip_spaces(parser, 1);
        return_type = parse_type(parser);
    }

    function->return_type = return_type;

    IR_Type **param_types = function->parameters.size > 0 ? malloc(function->parameters.size * sizeof(IR_Type *)) : NULL;
    for (size_t i = 0; i < function->parameters.size; i++) {
        param_types[i] = function->parameters.items[i]->type;
    }
    IR_Type *proc_type = ir_type_proc(parser->types, param_types, function->parameters.size, return_type);
    free(param_types);
    IR_Type *ptr_proc_type = ir_type_pointer(parser->types, proc_type);
    function->value.type = ptr_proc_type;
    function->value.slot = reserve_frame_slot(&parser->globals_frame_size, ptr_proc_type);

    skip_spaces(parser, 1);
    expect_other(parser, '{');
    advance(parser);

    while (true) {
        skip_end_of_lines(parser);
        skip_spaces(parser, 0);
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
        ir_block_list_add(&function->blocks, block);

        while (true) {
            skip_end_of_lines(parser);
            if (parser->current.kind != TOKEN_KIND__SPACE) {
                break;
            }
            if (parser->next.kind == TOKEN_KIND__END_OF_LINE || parser->next.kind == TOKEN_KIND__END_OF_FILE) {
                advance(parser);
                continue;
            }
            skip_spaces(parser, 2);

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

    function->frame_size = parser->function_frame_size;
    return function;
}

IR_Module *parse(Source source) {
    Parser parser;
    parser.source = source;
    parser.function_values = (IR_Value_List){0};
    parser.global_values = (IR_Value_List){0};
    parser.forward_references = (IR_Instruction_List){0};
    parser.function_frame_size = 0;
    parser.globals_frame_size = 0;

    parser.lexer = lexer_create(source);
    parser.current = lexer_next(parser.lexer);
    parser.next = lexer_next(parser.lexer);

    IR_Module *module = calloc(1, sizeof(IR_Module));
    module->source = source;
    parser.types = &module->types;

    while (true) {
        skip_end_of_lines(&parser);
        skip_spaces(&parser, 0);
        if (parser.current.kind == TOKEN_KIND__END_OF_FILE) {
            break;
        }

        if (parser.current.kind == TOKEN_KIND__IDENTIFIER && string_equals_cstr(parser.current.identifier.lexeme, "type")) {
            parse_type_declaration(&parser);
            continue;
        }

        if (parser.current.kind == TOKEN_KIND__VARIABLE && parser.current.variable.prefix == '$') {
            if (parser.next.kind == TOKEN_KIND__OTHER && parser.next.other.value == ':') {
                parse_external(&parser, module);
                continue;
            }
            ir_function_list_add(&module->functions, parse_function(&parser));
            continue;
        }

        parse_error_current(&parser, "Unexpected top-level token");
    }

    for (size_t i = 0; i < module->functions.size; i++) {
        check_function(&parser, module->functions.items[i]);
    }

    module->globals_size = parser.globals_frame_size;
    lexer_destroy(parser.lexer);
    return module;
}
