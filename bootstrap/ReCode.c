/* Copyright (C) 2023 Stefan Selariu */

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct File;
struct String;
struct Source;
struct Source_Location;
enum Token_Kind {
	Token_Kind__CHARACTER,
	Token_Kind__COMMENT,
	Token_Kind__END_OF_FILE,
	Token_Kind__END_OF_LINE,
	Token_Kind__ERROR,
	Token_Kind__IDENTIFIER,
	Token_Kind__INTEGER,
	Token_Kind__KEYWORD,
	Token_Kind__OTHER,
	Token_Kind__SPACE,
	Token_Kind__STRING
};
struct Token;
struct Character_Token;
struct Comment_Token;
struct End_Of_File_Token;
struct End_Of_Line_Token;
struct Error_Token;
struct Identifier_Token;
struct Integer_Token;
struct Other_Token;
struct Space_Token;
struct String_Token;
struct Scanner;
struct Parsed_Source;
enum Parsed_Type_Kind {
	Parsed_Type_Kind__FUNCTION,
	Parsed_Type_Kind__NAMED,
	Parsed_Type_Kind__POINTER,
	Parsed_Type_Kind__STRUCT
};
struct Parsed_Type;
struct Parsed_Function_Parameter;
struct Parsed_Function_Type;
struct Parsed_Named_Type;
struct Parsed_Pointer_Type;
struct Parsed_Struct_Type;
enum Parsed_Expression_Kind {
	Parsed_Expression_Kind__ADD,
	Parsed_Expression_Kind__ADDRESS_OF,
	Parsed_Expression_Kind__ARRAY_ACCESS,
	Parsed_Expression_Kind__BOOL,
	Parsed_Expression_Kind__CALL,
	Parsed_Expression_Kind__CAST,
	Parsed_Expression_Kind__CHARACTER,
	Parsed_Expression_Kind__DEREFERENCE,
	Parsed_Expression_Kind__DIVIDE,
	Parsed_Expression_Kind__EQUALS,
	Parsed_Expression_Kind__GREATER,
	Parsed_Expression_Kind__GREATER_OR_EQUALS,
	Parsed_Expression_Kind__GROUP,
	Parsed_Expression_Kind__INTEGER,
	Parsed_Expression_Kind__LESS,
	Parsed_Expression_Kind__LESS_OR_EQUALS,
	Parsed_Expression_Kind__LOGIC_AND,
	Parsed_Expression_Kind__LOGIC_OR,
	Parsed_Expression_Kind__MEMBER_ACCESS,
	Parsed_Expression_Kind__MINUS,
	Parsed_Expression_Kind__MODULO,
	Parsed_Expression_Kind__MULTIPLY,
	Parsed_Expression_Kind__NOT,
	Parsed_Expression_Kind__NOT_EQUALS,
	Parsed_Expression_Kind__NULL,
	Parsed_Expression_Kind__SIZEOF,
	Parsed_Expression_Kind__STRING,
	Parsed_Expression_Kind__SUBSTRACT,
	Parsed_Expression_Kind__SYMBOL
};
struct Parsed_Expression;
struct Parsed_Binary_Expression;
struct Parsed_Unary_Expression;
struct Parsed_Literal_Expression;
struct Parsed_Add_Expression;
struct Parsed_Address_Of_Expression;
struct Parsed_Array_Access_Expression;
struct Parsed_Bool_Expression;
struct Parsed_Call_Argument;
struct Parsed_Call_Expression;
struct Parsed_Cast_Expression;
struct Parsed_Character_Expression;
struct Parsed_Dereference_Expression;
struct Parsed_Divide_Expression;
struct Parsed_Equals_Expression;
struct Parsed_Greater_Expression;
struct Parsed_Greater_Or_Equals_Expression;
struct Parsed_Group_Expression;
struct Parsed_Integer_Expression;
struct Parsed_Less_Expression;
struct Parsed_Less_Or_Equals_Expression;
struct Parsed_Logic_And_Expression;
struct Parsed_Logic_Or_Expression;
struct Parsed_Member_Access_Expression;
struct Parsed_Minus_Expression;
struct Parsed_Modulo_Expression;
struct Parsed_Multiply_Expression;
struct Parsed_Not_Expression;
struct Parsed_Not_Equals_Expression;
struct Parsed_Null_Expression;
struct Parsed_Sizeof_Expression;
struct Parsed_String_Expression;
struct Parsed_Substract_Expression;
struct Parsed_Symbol_Expression;
enum Parsed_Statement_Kind {
	Parsed_Statement_Kind__ASSIGNMENT,
	Parsed_Statement_Kind__BLOCK,
	Parsed_Statement_Kind__BREAK,
	Parsed_Statement_Kind__ENUM,
	Parsed_Statement_Kind__EXPRESSION,
	Parsed_Statement_Kind__FUNCTION,
	Parsed_Statement_Kind__IF,
	Parsed_Statement_Kind__OPAQUE_TYPE,
	Parsed_Statement_Kind__RETURN,
	Parsed_Statement_Kind__STRUCT,
	Parsed_Statement_Kind__VARIABLE,
	Parsed_Statement_Kind__WHILE
};
struct Parsed_Statement;
struct Parsed_Named_Statement;
struct Parsed_Assignment_Statement;
struct Parsed_Block_Statement;
struct Parsed_Break_Statement;
struct Parsed_Enum_Member;
struct Parsed_Enum_Statement;
struct Parsed_Expression_Statement;
struct Parsed_Function_Statement;
struct Parsed_If_Statement;
struct Parsed_Opaque_Type_Statement;
struct Parsed_Return_Statement;
struct Parsed_Struct_Member;
struct Parsed_Struct_Statement;
struct Parsed_Variable_Statement;
struct Parsed_While_Statement;
struct Parsed_Statements;
struct Parser;
enum Checked_Type_Kind {
	Checked_Type_Kind__BOOL,
	Checked_Type_Kind__CHAR,
	Checked_Type_Kind__I16,
	Checked_Type_Kind__I32,
	Checked_Type_Kind__I64,
	Checked_Type_Kind__I8,
	Checked_Type_Kind__USIZE,
	Checked_Type_Kind__U16,
	Checked_Type_Kind__U32,
	Checked_Type_Kind__U64,
	Checked_Type_Kind__U8,
	Checked_Type_Kind__VOID,
	Checked_Type_Kind__NULL,
	Checked_Type_Kind__DEFINED,
	Checked_Type_Kind__ENUM,
	Checked_Type_Kind__OPAQUE,
	Checked_Type_Kind__STRUCT,
	Checked_Type_Kind__FUNCTION,
	Checked_Type_Kind__POINTER
};
struct Checked_Type;
struct Checked_Named_Type;
struct Checked_Enum_Member;
struct Checked_Enum_Type;
struct Checked_Function_Parameter;
struct Checked_Function_Type;
struct Checked_Opaque_Type;
struct Checked_Pointer_Type;
struct Checked_Defined_Type;
struct Checked_Struct_Member;
struct Checked_Struct_Type;
enum Checked_Symbol_Kind {
	Checked_Symbol_Kind__ENUM_MEMBER,
	Checked_Symbol_Kind__FUNCTION,
	Checked_Symbol_Kind__FUNCTION_PARAMETER,
	Checked_Symbol_Kind__TYPE,
	Checked_Symbol_Kind__VARIABLE
};
struct Checked_Symbol;
struct Checked_Enum_Member_Symbol;
struct Checked_Function_Symbol;
struct Checked_Function_Parameter_Symbol;
struct Checked_Type_Symbol;
struct Checked_Variable_Symbol;
struct Checked_Symbols;
enum Checked_Expression_Kind {
	Checked_Expression_Kind__ADD,
	Checked_Expression_Kind__ADDRESS_OF,
	Checked_Expression_Kind__ARRAY_ACCESS,
	Checked_Expression_Kind__BOOL,
	Checked_Expression_Kind__CALL,
	Checked_Expression_Kind__CAST,
	Checked_Expression_Kind__CHARACTER,
	Checked_Expression_Kind__DEREFERENCE,
	Checked_Expression_Kind__DIVIDE,
	Checked_Expression_Kind__EQUALS,
	Checked_Expression_Kind__GREATER,
	Checked_Expression_Kind__GREATER_OR_EQUALS,
	Checked_Expression_Kind__GROUP,
	Checked_Expression_Kind__INTEGER,
	Checked_Expression_Kind__LESS,
	Checked_Expression_Kind__LESS_OR_EQUALS,
	Checked_Expression_Kind__LOGIC_AND,
	Checked_Expression_Kind__LOGIC_OR,
	Checked_Expression_Kind__MEMBER_ACCESS,
	Checked_Expression_Kind__MINUS,
	Checked_Expression_Kind__MODULO,
	Checked_Expression_Kind__MULTIPLY,
	Checked_Expression_Kind__NOT,
	Checked_Expression_Kind__NOT_EQUALS,
	Checked_Expression_Kind__NULL,
	Checked_Expression_Kind__SIZEOF,
	Checked_Expression_Kind__STRING,
	Checked_Expression_Kind__SUBSTRACT,
	Checked_Expression_Kind__SYMBOL
};
struct Checked_Expression;
struct Checked_Binary_Expression;
struct Checked_Unary_Expression;
struct Checked_Add_Expression;
struct Checked_Address_Of_Expression;
struct Checked_Array_Access_Expression;
struct Checked_Bool_Expression;
struct Checked_Call_Argument;
struct Checked_Call_Expression;
struct Checked_Cast_Expression;
struct Checked_Character_Expression;
struct Checked_Dereference_Expression;
struct Checked_Divide_Expression;
struct Checked_Equals_Expression;
struct Checked_Greater_Expression;
struct Checked_Greater_Or_Equals_Expression;
struct Checked_Group_Expression;
struct Checked_Integer_Expression;
struct Checked_Less_Expression;
struct Checked_Less_Or_Equals_Expression;
struct Checked_Logic_And_Expression;
struct Checked_Logic_Or_Expression;
struct Checked_Member_Access_Expression;
struct Checked_Minus_Expression;
struct Checked_Modulo_Expression;
struct Checked_Multiply_Expression;
struct Checked_Not_Expression;
struct Checked_Not_Equals_Expression;
struct Checked_Null_Expression;
struct Checked_Sizeof_Expression;
struct Checked_String_Expression;
struct Checked_Substract_Expression;
struct Checked_Symbol_Expression;
enum Checked_Statement_Kind {
	Checked_Statement_Kind__ASSIGNMENT,
	Checked_Statement_Kind__BLOCK,
	Checked_Statement_Kind__BREAK,
	Checked_Statement_Kind__EXPRESSION,
	Checked_Statement_Kind__GOTO,
	Checked_Statement_Kind__IF,
	Checked_Statement_Kind__LABEL,
	Checked_Statement_Kind__RETURN,
	Checked_Statement_Kind__VARIABLE,
	Checked_Statement_Kind__WHILE
};
struct Checked_Statement;
struct Checked_Assignment_Statement;
struct Checked_Block_Statement;
struct Checked_Break_Statement;
struct Checked_Expression_Statement;
struct Checked_Goto_Statement;
struct Checked_If_Statement;
struct Checked_Label_Statement;
struct Checked_Return_Statement;
struct Checked_Variable_Statement;
struct Checked_While_Statement;
struct Checked_Statements;
struct Checked_Source;
struct Checker_Context;
struct Checker;
struct Generator;
struct Counter;

struct String {
	char* data;
	size_t data_size;
	size_t length;
};

struct Source {
	struct String* content;
	char* path;
};

struct Source_Location {
	struct Source* source;
	uint16_t line;
	uint16_t column;
};

struct Token {
	enum Token_Kind kind;
	struct Source_Location* location;
	struct String* lexeme;
	struct Token* next_token;
};

struct Character_Token {
	struct Token super;
	char value;
};

struct Comment_Token {
	struct Token super;
};

struct End_Of_File_Token {
	struct Token super;
};

struct End_Of_Line_Token {
	struct Token super;
};

struct Error_Token {
	struct Token super;
};

struct Identifier_Token {
	struct Token super;
};

struct Integer_Token {
	struct Token super;
	uint64_t value;
};

struct Other_Token {
	struct Token super;
};

struct Space_Token {
	struct Token super;
	uint16_t count;
};

struct String_Token {
	struct Token super;
	struct String* value;
};

struct Scanner {
	struct Source* source;
	size_t current_char_index;
	uint16_t current_line;
	uint16_t current_column;
	struct Token* current_token;
};

struct Parsed_Source {
	struct Parsed_Statements* statements;
};

struct Parsed_Type {
	enum Parsed_Type_Kind kind;
	struct Source_Location* location;
};

struct Parsed_Function_Parameter {
	struct Source_Location* location;
	struct String* name;
	struct Parsed_Type* type;
	struct Parsed_Function_Parameter* next_parameter;
};

struct Parsed_Function_Type {
	struct Parsed_Type super;
	struct Parsed_Function_Parameter* first_parameter;
	struct Parsed_Type* return_type;
};

struct Parsed_Named_Type {
	struct Parsed_Type super;
	struct String* name;
};

struct Parsed_Pointer_Type {
	struct Parsed_Type super;
	struct Parsed_Type* other_type;
};

struct Parsed_Struct_Type {
	struct Parsed_Type super;
	struct Parsed_Type* other_type;
};

struct Parsed_Expression {
	enum Parsed_Expression_Kind kind;
	struct Source_Location* location;
};

struct Parsed_Binary_Expression {
	struct Parsed_Expression super;
	struct Parsed_Expression* left_expression;
	struct Parsed_Expression* right_expression;
};

struct Parsed_Unary_Expression {
	struct Parsed_Expression super;
	struct Parsed_Expression* other_expression;
};

struct Parsed_Literal_Expression {
	struct Parsed_Expression super;
	struct Token* literal;
};

struct Parsed_Add_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Address_Of_Expression {
	struct Parsed_Unary_Expression super;
};

struct Parsed_Array_Access_Expression {
	struct Parsed_Expression super;
	struct Parsed_Expression* array_expression;
	struct Parsed_Expression* index_expression;
};

struct Parsed_Bool_Expression {
	struct Parsed_Literal_Expression super;
	bool value;
};

struct Parsed_Call_Argument {
	struct Parsed_Expression* expression;
	struct Parsed_Call_Argument* next_argument;
};

struct Parsed_Call_Expression {
	struct Parsed_Expression super;
	struct Parsed_Expression* callee_expression;
	struct Parsed_Call_Argument* first_argument;
};

struct Parsed_Cast_Expression {
	struct Parsed_Unary_Expression super;
	struct Parsed_Type* type;
};

struct Parsed_Character_Expression {
	struct Parsed_Literal_Expression super;
	char value;
};

struct Parsed_Dereference_Expression {
	struct Parsed_Expression super;
	struct Parsed_Expression* value_expression;
};

struct Parsed_Divide_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Equals_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Greater_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Greater_Or_Equals_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Group_Expression {
	struct Parsed_Expression super;
	struct Parsed_Expression* other_expression;
};

struct Parsed_Integer_Expression {
	struct Parsed_Literal_Expression super;
	uint64_t value;
};

struct Parsed_Less_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Less_Or_Equals_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Logic_And_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Logic_Or_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Member_Access_Expression {
	struct Parsed_Expression super;
	struct Parsed_Expression* object_expression;
	struct Token* member_name;
};

struct Parsed_Minus_Expression {
	struct Parsed_Unary_Expression super;
};

struct Parsed_Modulo_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Multiply_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Not_Expression {
	struct Parsed_Unary_Expression super;
};

struct Parsed_Not_Equals_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Null_Expression {
	struct Parsed_Literal_Expression super;
};

struct Parsed_Sizeof_Expression {
	struct Parsed_Expression super;
	struct Parsed_Type* type;
};

struct Parsed_String_Expression {
	struct Parsed_Literal_Expression super;
	struct String* value;
};

struct Parsed_Substract_Expression {
	struct Parsed_Binary_Expression super;
};

struct Parsed_Symbol_Expression {
	struct Parsed_Expression super;
	struct Token* name;
};

struct Parsed_Statement {
	enum Parsed_Statement_Kind kind;
	struct Source_Location* location;
	struct Parsed_Statement* next_statement;
};

struct Parsed_Named_Statement {
	struct Parsed_Statement super;
	struct Token* name;
};

struct Parsed_Assignment_Statement {
	struct Parsed_Statement super;
	struct Parsed_Expression* object_expression;
	struct Parsed_Expression* value_expression;
};

struct Parsed_Block_Statement {
	struct Parsed_Statement super;
	struct Parsed_Statements* statements;
};

struct Parsed_Break_Statement {
	struct Parsed_Statement super;
};

struct Parsed_Enum_Member {
	struct Token* name;
	struct Parsed_Enum_Member* next_member;
};

struct Parsed_Enum_Statement {
	struct Parsed_Named_Statement super;
	struct Parsed_Enum_Member* first_member;
};

struct Parsed_Expression_Statement {
	struct Parsed_Statement super;
	struct Parsed_Expression* expression;
};

struct Parsed_Function_Statement {
	struct Parsed_Named_Statement super;
	struct Parsed_Function_Parameter* first_parameter;
	struct Parsed_Type* return_type;
	struct Parsed_Statements* statements;
	bool is_external;
};

struct Parsed_If_Statement {
	struct Parsed_Statement super;
	struct Parsed_Expression* condition_expression;
	struct Parsed_Statement* true_statement;
	struct Parsed_Statement* false_statement;
};

struct Parsed_Opaque_Type_Statement {
	struct Parsed_Named_Statement super;
};

struct Parsed_Return_Statement {
	struct Parsed_Statement super;
	struct Parsed_Expression* expression;
};

struct Parsed_Struct_Member {
	struct Token* name;
	struct Parsed_Type* type;
	struct Parsed_Struct_Member* next_member;
};

struct Parsed_Struct_Statement {
	struct Parsed_Named_Statement super;
	struct Parsed_Struct_Member* first_member;
};

struct Parsed_Variable_Statement {
	struct Parsed_Named_Statement super;
	struct Parsed_Type* type;
	struct Parsed_Expression* expression;
	bool is_external;
};

struct Parsed_While_Statement {
	struct Parsed_Statement super;
	struct Parsed_Expression* condition_expression;
	struct Parsed_Statement* body_statement;
};

struct Parsed_Statements {
	struct Parsed_Statement* first_statement;
	struct Parsed_Statement* last_statement;
	bool has_globals;
};

struct Parser {
	struct Scanner* scanner;
	struct Parsed_Source* compilation_unit;
	uint16_t current_identation;
};

struct Checked_Type {
	enum Checked_Type_Kind kind;
	struct Source_Location* location;
	struct Checked_Type* next_type;
};

struct Checked_Named_Type {
	struct Checked_Type super;
	struct String* name;
};

struct Checked_Enum_Member {
	struct Source_Location* location;
	struct String* name;
	struct Checked_Symbol* symbol;
	struct Checked_Enum_Member* next_member;
};

struct Checked_Enum_Type {
	struct Checked_Named_Type super;
	struct Checked_Enum_Member* first_member;
};

struct Checked_Function_Parameter {
	struct Source_Location* location;
	struct String* name;
	struct Checked_Type* type;
	struct Checked_Function_Parameter* next_parameter;
};

struct Checked_Function_Type {
	struct Checked_Type super;
	struct Checked_Function_Parameter* first_parameter;
	struct Checked_Type* return_type;
};

struct Checked_Opaque_Type {
	struct Checked_Named_Type super;
};

struct Checked_Pointer_Type {
	struct Checked_Type super;
	struct Checked_Type* other_type;
};

struct Checked_Defined_Type {
	struct Checked_Type super;
	struct Checked_Named_Type* defined_type;
};

struct Checked_Struct_Member {
	struct Source_Location* location;
	struct String* name;
	struct Checked_Type* type;
	struct Checked_Struct_Member* next_member;
};

struct Checked_Struct_Type {
	struct Checked_Named_Type super;
	struct Checked_Struct_Type* super_type;
	struct Checked_Struct_Member* first_member;
};

struct Checked_Symbol {
	enum Checked_Symbol_Kind kind;
	struct Source_Location* location;
	struct String* name;
	struct Checked_Type* type;
	struct Checked_Symbol* prev_symbol;
	struct Checked_Symbol* next_symbol;
};

struct Checked_Enum_Member_Symbol {
	struct Checked_Symbol super;
};

struct Checked_Function_Symbol {
	struct Checked_Symbol super;
	struct Checked_Function_Type* function_type;
	struct Checked_Statements* checked_statements;
};

struct Checked_Function_Parameter_Symbol {
	struct Checked_Symbol super;
};

struct Checked_Type_Symbol {
	struct Checked_Symbol super;
	struct Checked_Named_Type* named_type;
};

struct Checked_Variable_Symbol {
	struct Checked_Symbol super;
};

struct Checked_Symbols {
	struct Checked_Symbols* parent;
	struct Checked_Symbol* first_symbol;
	struct Checked_Symbol* last_symbol;
};

struct Checked_Expression {
	enum Checked_Expression_Kind kind;
	struct Source_Location* location;
	struct Checked_Type* type;
};

struct Checked_Binary_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* left_expression;
	struct Checked_Expression* right_expression;
};

struct Checked_Unary_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* other_expression;
};

struct Checked_Add_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Address_Of_Expression {
	struct Checked_Unary_Expression super;
};

struct Checked_Array_Access_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* array_expression;
	struct Checked_Expression* index_expression;
};

struct Checked_Bool_Expression {
	struct Checked_Expression super;
	bool value;
};

struct Checked_Call_Argument {
	struct Checked_Expression* expression;
	struct Checked_Call_Argument* next_argument;
};

struct Checked_Call_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* callee_expression;
	struct Checked_Call_Argument* first_argument;
};

struct Checked_Cast_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* other_expression;
};

struct Checked_Character_Expression {
	struct Checked_Expression super;
	char value;
};

struct Checked_Dereference_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* value_expression;
};

struct Checked_Divide_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Equals_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Greater_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Greater_Or_Equals_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Group_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* other_expression;
};

struct Checked_Integer_Expression {
	struct Checked_Expression super;
	uint64_t value;
};

struct Checked_Less_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Less_Or_Equals_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Logic_And_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Logic_Or_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Member_Access_Expression {
	struct Checked_Expression super;
	struct Checked_Expression* object_expression;
	struct Checked_Struct_Member* member;
};

struct Checked_Minus_Expression {
	struct Checked_Unary_Expression super;
};

struct Checked_Modulo_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Multiply_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Not_Expression {
	struct Checked_Unary_Expression super;
};

struct Checked_Not_Equals_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Null_Expression {
	struct Checked_Expression super;
};

struct Checked_Sizeof_Expression {
	struct Checked_Expression super;
	struct Checked_Type* sized_type;
};

struct Checked_String_Expression {
	struct Checked_Expression super;
	struct String* value;
};

struct Checked_Substract_Expression {
	struct Checked_Binary_Expression super;
};

struct Checked_Symbol_Expression {
	struct Checked_Expression super;
	struct Checked_Symbol* symbol;
};

struct Checked_Statement {
	enum Checked_Statement_Kind kind;
	struct Source_Location* location;
	struct Checked_Statement* next_statement;
};

struct Checked_Assignment_Statement {
	struct Checked_Statement super;
	struct Checked_Expression* object_expression;
	struct Checked_Expression* value_expression;
};

struct Checked_Block_Statement {
	struct Checked_Statement super;
	struct Checker_Context* context;
	struct String* label;
};

struct Checked_Break_Statement {
	struct Checked_Statement super;
};

struct Checked_Expression_Statement {
	struct Checked_Statement super;
	struct Checked_Expression* expression;
};

struct Checked_Goto_Statement {
	struct Checked_Statement super;
	struct String* label;
};

struct Checked_If_Statement {
	struct Checked_Statement super;
	struct Checked_Expression* condition_expression;
	struct Checked_Statement* true_statement;
	struct Checked_Statement* false_statement;
};

struct Checked_Label_Statement {
	struct Checked_Statement super;
	struct String* label;
};

struct Checked_Return_Statement {
	struct Checked_Statement super;
	struct Checked_Expression* expression;
};

struct Checked_Variable_Statement {
	struct Checked_Statement super;
	struct Checked_Variable_Symbol* variable;
	struct Checked_Expression* expression;
	bool is_external;
};

struct Checked_While_Statement {
	struct Checked_Statement super;
	struct Checked_Expression* condition_expression;
	struct Checked_Statement* body_statement;
};

struct Checked_Statements {
	struct Checked_Symbols* symbols;
	struct Checked_Statement* first_statement;
	struct Checked_Statement* last_statement;
};

struct Checked_Source {
	struct Checked_Symbol* first_symbol;
	struct Checked_Statements* statements;
};

struct Checker_Context {
	struct Checker_Context* parent;
	struct Checked_Symbols* symbols;
	struct Checked_Statements* statements;
	struct Counter* function_counter;
	struct Checked_Type* function_return_type;
};

struct Checker {
	struct Checked_Named_Type* first_type;
	struct Checked_Named_Type* last_type;
	struct Checked_Named_Type* last_builting_type;
	struct Checker_Context* root_context;
	struct Checker_Context* current_context;
};

struct Generator {
	struct File* file;
	uint16_t identation;
};

struct Counter {
	int16_t value;
};

extern struct File* stdin;
extern struct File* stdout;
extern struct File* stderr;

struct File* fopen(char* file_name, char* mode);
int32_t fclose(struct File* stream);
int32_t fgetc(struct File* stream);
int32_t fputc(int32_t c, struct File* stream);
int32_t fputs(char* s, struct File* stream);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);
void abort();
struct String* String__create_empty(size_t data_size);
struct String* String__create();
void String__delete(struct String* self);
struct String* String__append_char(struct String* self, char ch);
struct String* String__append_cstring(struct String* self, char* s);
size_t cstring_length(char* s);
struct String* String__create_from(char* data);
struct String* String__append_i16(struct String* self, int16_t value);
struct String* String__append_string(struct String* self, struct String* other);
bool String__equals_cstring(struct String* self, char* s);
bool String__equals_string(struct String* self, struct String* other);
void File__write_char(struct File* self, char c);
void File__write_cstring(struct File* self, char* s);
void File__write_i32(struct File* self, int32_t value);
void File__write_u64(struct File* self, uint64_t value);
void File__write_string(struct File* self, struct String* string);
void error(struct String* message);
void warning(struct String* message);
void TODO(char* message);
struct Source* Source__create(struct File* file, char* file_path);
struct Source_Location* Source_Location__create(struct Source* source, uint16_t line, uint16_t column);
struct String* String__append_source_location(struct String* self, struct Source_Location* location);
void File__write_source_location(struct File* self, struct Source_Location* location);
void Source_Location__error(struct Source_Location* self, struct String* message);
void Source_Location__warning(struct Source_Location* self, struct String* message);
struct Token* Token__create_kind(enum Token_Kind kind, size_t kind_size, struct Source_Location* location, struct String* lexeme);
void Token__error(struct Token* self, struct String* message);
void Token__warning(struct Token* self, struct String* message);
struct Character_Token* Character_Token__create(struct Source_Location* location, struct String* lexeme, char value);
struct Comment_Token* Comment_Token__create(struct Source_Location* location, struct String* lexeme);
struct End_Of_File_Token* End_Of_File_Token__create(struct Source_Location* location, struct String* lexeme);
struct End_Of_Line_Token* End_Of_Line_Token__create(struct Source_Location* location, struct String* lexeme);
struct Error_Token* Error_Token__create(struct Source_Location* location, struct String* lexeme);
struct Identifier_Token* Identifier_Token__create(struct Source_Location* location, struct String* lexeme);
struct Integer_Token* Integer_Token__create(struct Source_Location* location, struct String* lexeme, uint64_t value);
struct Other_Token* Other_Token__create(struct Source_Location* location, struct String* lexeme);
struct Space_Token* Space_Token__create(struct Source_Location* location, struct String* lexeme, uint16_t count);
struct String_Token* String_Token__create(struct Source_Location* location, struct String* lexeme, struct String* value);
bool Token__is_anything(struct Token* self);
bool Token__is_character(struct Token* self);
bool Token__is_comment(struct Token* self);
bool Token__is_end_of_file(struct Token* self);
bool Token__is_end_of_line(struct Token* self);
bool Token__is_identifier(struct Token* self);
bool Token__is_integer(struct Token* self);
bool Token__is_keyword(struct Token* self, char* lexeme);
bool Token__is_break(struct Token* self);
bool Token__is_else(struct Token* self);
bool Token__is_enum(struct Token* self);
bool Token__is_external(struct Token* self);
bool Token__is_false(struct Token* self);
bool Token__is_func(struct Token* self);
bool Token__is_if(struct Token* self);
bool Token__is_let(struct Token* self);
bool Token__is_null(struct Token* self);
bool Token__is_return(struct Token* self);
bool Token__is_sizeof(struct Token* self);
bool Token__is_struct(struct Token* self);
bool Token__is_true(struct Token* self);
bool Token__is_undefined(struct Token* self);
bool Token__is_while(struct Token* self);
bool Token__is_other(struct Token* self, char* lexeme);
bool Token__is_ampersand(struct Token* self);
bool Token__is_asterisk(struct Token* self);
bool Token__is_closing_brace(struct Token* self);
bool Token__is_closing_bracket(struct Token* self);
bool Token__is_closing_paren(struct Token* self);
bool Token__is_colon(struct Token* self);
bool Token__is_comma(struct Token* self);
bool Token__is_dot(struct Token* self);
bool Token__is_equals(struct Token* self);
bool Token__is_exclamation_mark(struct Token* self);
bool Token__is_greater_than(struct Token* self);
bool Token__is_less_than(struct Token* self);
bool Token__is_minus(struct Token* self);
bool Token__is_opening_brace(struct Token* self);
bool Token__is_opening_bracket(struct Token* self);
bool Token__is_opening_paren(struct Token* self);
bool Token__is_percent(struct Token* self);
bool Token__is_plus(struct Token* self);
bool Token__is_slash(struct Token* self);
bool Token__is_vertical_bar(struct Token* self);
bool Token__is_space(struct Token* self);
bool Token__is_string(struct Token* self);
void File__write_token(struct File* stream, struct Token* token);
char Scanner__peek_char(struct Scanner* self);
char Scanner__next_char(struct Scanner* self);
char escape_char_value(char c);
bool char_is_end_of_line(char c);
struct Token* Scanner__scan_character_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme);
struct Token* Scanner__scan_comment_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme);
bool char_is_identifier_start(char c);
bool char_is_identifier_letter(char c);
struct Token* Scanner__scan_identifier_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme);
bool char_is_digit(char c);
struct Token* Scanner__scan_integer_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme);
bool char_is_space(char c);
struct Token* Scanner__scan_space_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme);
struct Token* Scanner__scan_string_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme);
struct Token* Scanner__scan_token(struct Scanner* self);
struct Token* Scanner__next_token(struct Scanner* self);
struct Token* Scanner__peek_token(struct Scanner* self, uint8_t offset);
struct Scanner* Scanner__create(struct Source* source);
struct Parsed_Type* Parsed_Type__create_kind(enum Parsed_Type_Kind kind, size_t kind_size, struct Source_Location* location);
struct Parsed_Function_Parameter* Parsed_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Parsed_Type* type);
struct Parsed_Function_Type* Parsed_Function_Type__create(struct Source_Location* location, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* return_type);
struct Parsed_Named_Type* Parsed_Named_Type__create(struct Token* name);
struct Parsed_Pointer_Type* Parsed_Pointer_Type__create(struct Parsed_Type* other_type);
struct Parsed_Struct_Type* Parsed_Struct_Type__create(struct Source_Location* location, struct Parsed_Type* other_type);
struct Parsed_Expression* Parsed_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location);
struct Parsed_Binary_Expression* Parsed_Binary_Expression__create_kind(enum Parsed_Expression_Kind kind, struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Unary_Expression* Parsed_Unary_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Parsed_Expression* other_expression);
struct Parsed_Literal_Expression* Parsed_Literal_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Token* literal);
struct Parsed_Add_Expression* Parsed_Add_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression);
struct Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(struct Parsed_Expression* array_expression, struct Parsed_Expression* index_expression);
struct Parsed_Bool_Expression* Parsed_Bool_Expression__create(struct Token* literal, bool value);
struct Parsed_Call_Argument* Parsed_Call_Argument__create(struct Parsed_Expression* expression);
struct Parsed_Call_Expression* Parsed_Call_Expression__create(struct Parsed_Expression* callee_expression);
struct Parsed_Cast_Expression* Parsed_Cast_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression, struct Parsed_Type* type);
struct Parsed_Character_Expression* Parsed_Character_Expression__create(struct Character_Token* literal);
struct Parsed_Dereference_Expression* Parsed_Dereference_Expression__create(struct Parsed_Expression* value_expression);
struct Parsed_Divide_Expression* Parsed_Divide_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Equals_Expression* Parsed_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Greater_Expression* Parsed_Greater_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Group_Expression* Parsed_Group_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression);
struct Parsed_Integer_Expression* Parsed_Integer_Expression__create(struct Integer_Token* literal);
struct Parsed_Less_Expression* Parsed_Less_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(struct Parsed_Expression* object_expression, struct Token* member_name);
struct Parsed_Minus_Expression* Parsed_Minus_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression);
struct Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Not_Expression* Parsed_Not_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression);
struct Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Null_Expression* Parsed_Null_Expression__create(struct Token* literal);
struct Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(struct Source_Location* location, struct Parsed_Type* type);
struct Parsed_String_Expression* Parsed_String_Expression__create(struct String_Token* literal);
struct Parsed_Substract_Expression* Parsed_Substract_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression);
struct Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(struct Token* name);
struct Parsed_Statement* Parsed_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location);
struct Parsed_Named_Statement* Parsed_Named_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location, struct Token* name);
struct Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(struct Parsed_Expression* object_expression, struct Parsed_Expression* value_expression);
struct Parsed_Block_Statement* Parsed_Block_Statement__create(struct Source_Location* location, struct Parsed_Statements* statements);
struct Parsed_Statement* Parsed_Break_Statement__create(struct Source_Location* location);
struct Parsed_Enum_Member* Parsed_Enum_Member__create(struct Token* name);
struct Parsed_Enum_Statement* Parsed_Enum_Statement__create(struct Source_Location* location, struct Token* name);
struct Parsed_Expression_Statement* Parsed_Expression_Statement__create(struct Parsed_Expression* expression);
struct Parsed_Statement* Parsed_Function_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* resturn_type, struct Parsed_Statements* statements, bool is_external);
struct Parsed_Statement* Parsed_If_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* true_statement, struct Parsed_Statement* false_statement);
struct Parsed_Opaque_Type_Statement* Parsed_Opaque_Type_Statement__create(struct Source_Location* location, struct Token* name);
struct Parsed_Statement* Parsed_Return_Statement__create(struct Source_Location* location, struct Parsed_Expression* expression);
struct Parsed_Struct_Member* Parsed_Struct_Member__create(struct Token* name, struct Parsed_Type* type);
struct Parsed_Struct_Statement* Parsed_Struct_Statement__create(struct Source_Location* location, struct Token* name);
struct Parsed_Variable_Statement* Parsed_Variable_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Type* type, bool is_external);
struct Parsed_Statement* Parsed_While_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* body_statement);
struct Parsed_Statements* Parsed_Statements__create(bool has_globals);
void Parsed_Statements__append(struct Parsed_Statements* self, struct Parsed_Statement* statement);
struct Parsed_Source* Parsed_Compilation_Unit__create();
void Parser__error(struct Parser* self, struct String* message);
void Parser__warning(struct Parser* self, struct String* message);
struct Token* Parser__peek_token(struct Parser* self, uint8_t offset);
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token*), bool first_required, bool (*second_is)(struct Token*), bool second_required, bool (*third_is)(struct Token*));
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token*), bool first_required, bool (*second_is)(struct Token*));
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token*));
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token*));
void Parser__consume_comment(struct Parser* self);
void Parser__consume_space(struct Parser* self, uint16_t count);
void Parser__consume_end_of_line(struct Parser* self);
bool Parser__consume_empty_line(struct Parser* self);
struct Parsed_Expression* Parser__parse_primary_expression(struct Parser* self);
struct Parsed_Expression* Parser__parse_access_expression(struct Parser* self);
struct Parsed_Expression* Parser__parse_unary_expression(struct Parser* self);
bool Token__is_mutliplication(struct Token* self);
struct Parsed_Expression* Parser__parse_multiplication_expression(struct Parser* self);
bool Token__is_addition(struct Token* self);
struct Parsed_Expression* Parser__parse_addition_expression(struct Parser* self);
struct Parsed_Expression* Parser__parse_comparison_expression(struct Parser* self);
struct Parsed_Expression* Parser__parse_equality_expression(struct Parser* self);
struct Parsed_Expression* Parser__parse_logic_and_expression(struct Parser* self);
struct Parsed_Expression* Parser__parse_logic_or_expression(struct Parser* self);
struct Parsed_Expression* Parser__parse_expression(struct Parser* self);
struct Parsed_Statement* Parser__parse_struct(struct Parser* self);
struct Parsed_Statement* Parser__parse_opaque_type(struct Parser* self);
struct Parsed_Statement* Parser__parse_enum(struct Parser* self);
struct Parsed_Type* Parser__parse_type(struct Parser* self);
struct Parsed_Statement* Parser__parse_variable(struct Parser* self);
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self);
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self);
struct Parsed_Statement* Parser__parse_function(struct Parser* self);
struct Parsed_Statement* Parser__parse_external_function(struct Parser* self);
struct Parsed_Statement* Parser__parse_return_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_break_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_if_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_while_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_statement(struct Parser* self);
void Parser__parse_statements(struct Parser* self, struct Parsed_Statements* statements);
void Parser__parse_source(struct Parser* self, struct Source* source);
struct Parsed_Source* parse(struct Source* source);
struct Checked_Type* Checked_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location);
void Checked_Type__expect_same_type(struct Checked_Type* self, struct Checked_Type* other_type, struct Source_Location* location);
bool Checked_Type__is_scalar_type(struct Checked_Type* self);
void Checked_Type__expect_scalar_type(struct Checked_Type* self, struct Source_Location* location);
struct Checked_Named_Type* Checked_Named_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name);
struct Checked_Enum_Member* Checked_Enum_Member__create(struct Source_Location* location, struct String* name);
struct Checked_Enum_Type* Checked_Enum_Type__create(struct Source_Location* location, struct String* name);
struct Checked_Enum_Member* Checked_Enum_Type__find_member(struct Checked_Enum_Type* self, struct String* name);
struct Checked_Function_Parameter* Checked_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct Checked_Function_Parameter* first_parameter, struct Checked_Type* return_type);
bool Checked_Function_Type__equals(struct Checked_Function_Type* self, struct Checked_Type* other_type);
struct Checked_Opaque_Type* Checked_Opaque_Type__create(struct Source_Location* location, struct String* name);
struct Checked_Pointer_Type* Checked_Pointer_Type__create(struct Source_Location* location, struct Checked_Type* other_type);
bool Checked_Pointer_Type__equals(struct Checked_Pointer_Type* self, struct Checked_Type* other_type);
struct Checked_Defined_Type* Checked_Defined_Type__create(struct Checked_Named_Type* defined_type);
struct Checked_Struct_Member* Checked_Struct_Member__create(struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Struct_Type* Checked_Struct_Type__create(struct Source_Location* location, struct String* name);
struct Checked_Struct_Member* Checked_Struct_Type__find_member(struct Checked_Struct_Type* self, struct String* name);
bool Checked_Struct_Type__equals(struct Checked_Struct_Type* self, struct Checked_Type* other_type);
bool Checked_Type__equals(struct Checked_Type* self, struct Checked_Type* other_type);
struct String* String__append_checked_type(struct String* self, struct Checked_Type* type);
void File__write_checked_function_symbol(struct File* self, struct Checked_Function_Symbol* function_symbol);
void File__write_checked_function_parameter(struct File* self, struct Checked_Function_Parameter* parameter);
void File__write_checked_type(struct File* self, struct Checked_Type* type);
struct Checked_Symbol* Checked_Symbol__create_kind(enum Checked_Symbol_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Enum_Member_Symbol* Checked_Enum_Member_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Function_Symbol* Checked_Function_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Function_Type* function_type);
struct Checked_Function_Parameter_Symbol* Checked_Function_Parameter_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Type_Symbol* Checked_Type_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Named_Type* named_type);
struct Checked_Variable_Symbol* Checked_Variable__create(struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Symbols* Checked_Symbols__create(struct Checked_Symbols* parent);
struct Checked_Symbol* Checked_Symbols__find_sibling_symbol(struct Checked_Symbols* self, struct String* name);
void Checked_Symbols__append_symbol(struct Checked_Symbols* self, struct Checked_Symbol* symbol);
struct Checked_Symbol* Checked_Symbols__find_symbol(struct Checked_Symbols* self, struct String* name);
struct Checked_Expression* Checked_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type);
struct Checked_Binary_Expression* Checked_Binary_Expression__create_kind(enum Checked_Expression_Kind kind, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Unary_Expression* Checked_Unary_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression);
struct Checked_Add_Expression* Checked_Add_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Address_Of_Expression* Checked_Address_Of_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression);
struct Checked_Array_Access_Expression* Checked_Array_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* array_expression, struct Checked_Expression* index_expression);
struct Checked_Bool_Expression* Checked_Bool_Expression__create(struct Source_Location* location, struct Checked_Type* type, bool value);
struct Checked_Call_Argument* Checked_Call_Argument__create(struct Checked_Expression* expression);
struct Checked_Call_Expression* Checked_Call_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* callee_expression, struct Checked_Call_Argument* first_argument);
struct Checked_Cast_Expression* Checked_Cast_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression);
struct Checked_Character_Expression* Checked_Character_Expression__create(struct Source_Location* location, struct Checked_Type* type, char value);
struct Checked_Dereference_Expression* Checked_Dereference_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* value_expression);
struct Checked_Divide_Expression* Checked_Divide_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Equals_Expression* Checked_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Greater_Expression* Checked_Greater_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Greater_Or_Equals_Expression* Checked_Greater_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Group_Expression* Checked_Group_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression);
struct Checked_Integer_Expression* Checked_Integer_Expression__create(struct Source_Location* location, struct Checked_Type* type, uint64_t value);
struct Checked_Less_Expression* Checked_Less_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Less_Or_Equals_Expression* Checked_Less_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Logic_And_Expression* Checked_Logic_And_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Logic_Or_Expression* Checked_Logic_Or_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Member_Access_Expression* Checked_Member_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* object_expression, struct Checked_Struct_Member* member);
struct Checked_Minus_Expression* Checked_Minus_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression);
struct Checked_Modulo_Expression* Checked_Modulo_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Multiply_Expression* Checked_Multiply_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Not_Expression* Checked_Not_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression);
struct Checked_Not_Equals_Expression* Checked_Not_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Null_Expression* Checked_Null_Expression__create(struct Source_Location* location, struct Checked_Type* type);
struct Checked_Sizeof_Expression* Checked_Sizeof_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Type* sized_type);
struct Checked_String_Expression* Checked_String_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct String* value);
struct Checked_Substract_Expression* Checked_Substract_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression);
struct Checked_Symbol_Expression* Checked_Symbol_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Symbol* symbol);
struct Checked_Statement* Checked_Statement__create_kind(enum Checked_Statement_Kind kind, size_t kind_size, struct Source_Location* location);
struct Checked_Assignment_Statement* Checked_Assignment_Statement__create(struct Source_Location* location, struct Checked_Expression* object_expression, struct Checked_Expression* value_expression);
struct Checked_Block_Statement* Checked_Block_Statement__create(struct Source_Location* location, struct Checker_Context* context, struct String* label);
struct Checked_Break_Statement* Checked_Break_Statement__create(struct Source_Location* location);
struct Checked_Expression_Statement* Checked_Expression_Statement__create(struct Source_Location* location, struct Checked_Expression* expression);
struct Checked_Goto_Statement* Checked_Goto_Statement__create(struct Source_Location* location, struct String* label);
struct Checked_If_Statement* Checked_If_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* true_statement, struct Checked_Statement* false_statement);
struct Checked_Label_Statement* Checked_Label_Statement__create(struct Source_Location* location, struct String* label);
struct Checked_Return_Statement* Checked_Return_Statement__create(struct Source_Location* location, struct Checked_Expression* expression);
struct Checked_Variable_Statement* Checked_Variable_Statement__create(struct Source_Location* location, struct Checked_Variable_Symbol* variable, struct Checked_Expression* expression, bool is_external);
struct Checked_While_Statement* Checked_While_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* body_statement);
struct Checked_Statements* Checked_Statements__create(struct Checked_Symbols* symbols);
void Checked_Statements__append(struct Checked_Statements* self, struct Checked_Statement* statement);
struct Checker_Context* Checker_Context__create(struct Checker_Context* parent);
struct Checker* Checker__create();
void Checker__append_type(struct Checker* self, struct Checked_Named_Type* type);
struct Checked_Named_Type* Checker__find_type(struct Checker* self, struct String* name);
struct Checked_Named_Type* Checker__get_builtin_type(struct Checker* self, enum Checked_Type_Kind kind);
struct Checked_Type* Checker__resolve_type(struct Checker* self, struct Parsed_Type* parsed_type);
struct Checked_Expression* Checker__check_add_expression(struct Checker* self, struct Parsed_Add_Expression* parsed_expression);
struct Checked_Expression* Checker__check_address_of_expression(struct Checker* self, struct Parsed_Address_Of_Expression* parsed_expression);
struct Checked_Expression* Checker__check_array_access_expression(struct Checker* self, struct Parsed_Array_Access_Expression* parsed_expression);
struct Checked_Expression* Checker__check_bool_expression(struct Checker* self, struct Parsed_Bool_Expression* parsed_expression);
struct Checked_Expression* Checker__check_call_expression(struct Checker* self, struct Parsed_Call_Expression* parsed_expression);
struct Checked_Expression* Checker__check_cast_expression(struct Checker* self, struct Parsed_Cast_Expression* parsed_expression);
struct Checked_Expression* Checker__check_character_expression(struct Checker* self, struct Parsed_Character_Expression* parsed_expression);
struct Checked_Expression* Checker__check_dereference_expression(struct Checker* self, struct Parsed_Dereference_Expression* parsed_expression);
struct Checked_Expression* Checker__check_divide_expression(struct Checker* self, struct Parsed_Divide_Expression* parsed_expression);
struct Checked_Expression* Checker__check_equals_expression(struct Checker* self, struct Parsed_Equals_Expression* parsed_expression);
struct Checked_Expression* Checker__check_greater_expression(struct Checker* self, struct Parsed_Greater_Expression* parsed_expression);
struct Checked_Expression* Checker__check_greater_or_equals_expression(struct Checker* self, struct Parsed_Greater_Or_Equals_Expression* parsed_expression);
struct Checked_Expression* Checker__check_group_expression(struct Checker* self, struct Parsed_Group_Expression* parsed_expression);
struct Checked_Expression* Checker__check_integer_expression(struct Checker* self, struct Parsed_Integer_Expression* parsed_expression);
struct Checked_Expression* Checker__check_less_expression(struct Checker* self, struct Parsed_Less_Expression* parsed_expression);
struct Checked_Expression* Checker__check_less_or_equals_expression(struct Checker* self, struct Parsed_Less_Or_Equals_Expression* parsed_expression);
struct Checked_Expression* Checker__check_logic_and_expression(struct Checker* self, struct Parsed_Logic_And_Expression* parsed_expression);
struct Checked_Expression* Checker__check_logic_or_expression(struct Checker* self, struct Parsed_Logic_Or_Expression* parsed_expression);
struct Checked_Expression* Checker__check_member_access_expression(struct Checker* self, struct Parsed_Member_Access_Expression* parsed_expression);
struct Checked_Expression* Checker__check_struct_member_access_expression(struct Checker* self, struct Checked_Expression* object_expression, struct Checked_Struct_Type* struct_type, struct Token* member_name);
struct Checked_Expression* Checker__check_minus_expression(struct Checker* self, struct Parsed_Minus_Expression* parsed_expression);
struct Checked_Expression* Checker__check_modulo_expression(struct Checker* self, struct Parsed_Modulo_Expression* parsed_expression);
struct Checked_Expression* Checker__check_multiply_expression(struct Checker* self, struct Parsed_Multiply_Expression* parsed_expression);
struct Checked_Expression* Checker__check_not_expression(struct Checker* self, struct Parsed_Not_Expression* parsed_expression);
struct Checked_Expression* Checker__check_not_equals_expression(struct Checker* self, struct Parsed_Not_Equals_Expression* parsed_expression);
struct Checked_Expression* Checker__check_null_expression(struct Checker* self, struct Parsed_Null_Expression* parsed_expression);
struct Checked_Expression* Checker__check_sizeof_expression(struct Checker* self, struct Parsed_Sizeof_Expression* parsed_expression);
struct Checked_Expression* Checker__check_string_expression(struct Checker* self, struct Parsed_String_Expression* parsed_expression);
struct Checked_Expression* Checker__check_substract_expression(struct Checker* self, struct Parsed_Substract_Expression* parsed_expression);
struct Checked_Expression* Checker__check_symbol_expression(struct Checker* self, struct Parsed_Symbol_Expression* parsed_expression);
struct Checked_Expression* Checker__check_expression(struct Checker* self, struct Parsed_Expression* parsed_expression);
void Checker__check_enum_statement(struct Checker* self, struct Parsed_Enum_Statement* parsed_statement);
void Checker__create_opaque_type(struct Checker* self, struct Parsed_Opaque_Type_Statement* parsed_statement);
void Checker__create_struct_type(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement);
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement);
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement);
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement);
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement);
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement);
struct Checked_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement);
struct Checked_Block_Statement* Checker__check_if_condition(struct Checker* self, struct Parsed_Expression* parsed_expression, struct String* then_label, struct String* else_label);
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement);
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement);
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement);
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement);
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement);
void Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements);
void Checker__check_function_definition(struct Checker* self, struct Parsed_Function_Statement* parsed_statement);
struct Checked_Source* Checker__check_source(struct Checker* self, struct Parsed_Source* parsed_source);
struct Checked_Source* check(struct Parsed_Source* parsed_source);
void Generator__write_source_location(struct Generator* self, struct Source_Location* location);
void Generator__generate_add_expression(struct Generator* self, struct Checked_Add_Expression* expression);
void Generator__generate_address_of_expression(struct Generator* self, struct Checked_Address_Of_Expression* expression);
void Generator__generate_array_access_expression(struct Generator* self, struct Checked_Array_Access_Expression* expression);
void Generator__generate_bool_expression(struct Generator* self, struct Checked_Bool_Expression* expression);
void Generator__generate_call_expression(struct Generator* self, struct Checked_Call_Expression* expression);
void Generator__generate_cast_expression(struct Generator* self, struct Checked_Cast_Expression* expression);
void File__write_octal_escaped_char(struct File* stream, char value);
void File__write_escaped_char(struct File* stream, char ch);
void Generator__generate_character_expression(struct Generator* self, struct Checked_Character_Expression* expression);
void Generator__generate_dereference_expression(struct Generator* self, struct Checked_Dereference_Expression* expression);
void Generator__generate_divide_expression(struct Generator* self, struct Checked_Divide_Expression* expression);
void Generator__generate_equals_expression(struct Generator* self, struct Checked_Equals_Expression* expression);
void Generator__generate_greater_expression(struct Generator* self, struct Checked_Greater_Expression* expression);
void Generator__generate_greater_or_equals_expression(struct Generator* self, struct Checked_Greater_Or_Equals_Expression* expression);
void Generator__generate_group_expression(struct Generator* self, struct Checked_Group_Expression* expression);
void Generator__generate_integer_expression(struct Generator* self, struct Checked_Integer_Expression* expression);
void Generator__generate_less_expression(struct Generator* self, struct Checked_Less_Expression* expression);
void Generator__generate_less_or_equals_expression(struct Generator* self, struct Checked_Less_Or_Equals_Expression* expression);
void Generator__generate_logic_and_expression(struct Generator* self, struct Checked_Logic_And_Expression* expression);
void Generator__generate_logic_or_expression(struct Generator* self, struct Checked_Logic_Or_Expression* expression);
void Generator__generate_member_access_expression(struct Generator* self, struct Checked_Member_Access_Expression* expression);
void Generator__generate_minus_expression(struct Generator* self, struct Checked_Minus_Expression* expression);
void Generator__generate_modulo_expression(struct Generator* self, struct Checked_Modulo_Expression* expression);
void Generator__generate_multiply_expression(struct Generator* self, struct Checked_Multiply_Expression* expression);
void Generator__generate_not_expression(struct Generator* self, struct Checked_Not_Expression* expression);
void Generator__generate_not_equals_expression(struct Generator* self, struct Checked_Not_Equals_Expression* expression);
void Generator__generate_null_expression(struct Generator* self, struct Checked_Null_Expression* expression);
void Generator__generate_sizeof_expression(struct Generator* self, struct Checked_Sizeof_Expression* expression);
void Generator__generate_string_expression(struct Generator* self, struct Checked_String_Expression* expression);
void Generator__generate_substract_expression(struct Generator* self, struct Checked_Substract_Expression* expression);
void Generator__generate_symbol_expression(struct Generator* self, struct Checked_Symbol_Expression* expression);
void Generator__generate_expression(struct Generator* self, struct Checked_Expression* expression);
void Generator__write_identation(struct Generator* self);
void Generator__generate_assignment_statement(struct Generator* self, struct Checked_Assignment_Statement* statement);
void Generator__generate_block_statement(struct Generator* self, struct Checked_Block_Statement* statement);
void Generator__generate_break_statement(struct Generator* self, struct Checked_Break_Statement* statement);
void Generator__generate_expression_statement(struct Generator* self, struct Checked_Expression_Statement* statement);
void Generator__generate_goto_statement(struct Generator* self, struct Checked_Goto_Statement* statement);
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement);
void Generator__generate_label_statement(struct Generator* self, struct Checked_Label_Statement* statement);
void Generator__generate_return_statement(struct Generator* self, struct Checked_Return_Statement* statement);
void Generator__generate_variable_statement(struct Generator* self, struct Checked_Variable_Statement* statement);
void Generator__generate_while_statement(struct Generator* self, struct Checked_While_Statement* statement);
void Generator__generate_statement(struct Generator* self, struct Checked_Statement* statement);
void Generator__generate_statements(struct Generator* self, struct Checked_Statements* statements);
void Generator__generate_enum(struct Generator* self, struct Checked_Enum_Type* enum_type);
void Generator__declare_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol);
void Generator__generate_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol);
void Generator__declare_opaque_type(struct Generator* self, struct Checked_Opaque_Type* opaque_type);
void Generator__declare_struct(struct Generator* self, struct Checked_Struct_Type* struct_type);
void Generator__generate_struct(struct Generator* self, struct Checked_Struct_Type* struct_type);
void generate(struct File* file, struct Checked_Source* checked_source);
struct Counter* Counter__create();
int16_t Counter__next(struct Counter* self);
struct Counter* Counter__reset(struct Counter* self);
int32_t main(int32_t argc, char** argv);

#line 35 "bootstrap/stage0/ReCode.code"
struct String* String__create_empty(size_t data_size) { struct String* string;
#line 36 "bootstrap/stage0/ReCode.code"
    string = ((struct String*) malloc(sizeof(struct String)));
#line 37 "bootstrap/stage0/ReCode.code"
    string->data = ((char*) malloc(data_size));
#line 38 "bootstrap/stage0/ReCode.code"
    string->data_size = data_size;
#line 39 "bootstrap/stage0/ReCode.code"
    string->length = ((size_t) 0);
#line 40 "bootstrap/stage0/ReCode.code"
    return string;}

#line 43 "bootstrap/stage0/ReCode.code"
struct String* String__create() {
#line 44 "bootstrap/stage0/ReCode.code"
    return String__create_empty(((size_t) 16));}

#line 47 "bootstrap/stage0/ReCode.code"
void String__delete(struct String* self) {
#line 48 "bootstrap/stage0/ReCode.code"
    free(((void*) self->data));
#line 49 "bootstrap/stage0/ReCode.code"
    free(((void*) self));}

#line 52 "bootstrap/stage0/ReCode.code"
struct String* String__append_char(struct String* self, char ch) {
#line 53 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->length >= self->data_size) {
#line 53 "bootstrap/stage0/ReCode.code"
            {
#line 54 "bootstrap/stage0/ReCode.code"
                self->data_size = self->data_size + ((size_t) 16);
#line 55 "bootstrap/stage0/ReCode.code"
                self->data = ((char*) realloc(((void*) self->data), self->data_size));
            } goto if__end__1; } if__end__1: ;
    }
#line 57 "bootstrap/stage0/ReCode.code"
    self->data[self->length] = ch;
#line 58 "bootstrap/stage0/ReCode.code"
    self->length = self->length + ((size_t) 1);
#line 59 "bootstrap/stage0/ReCode.code"
    return self;}

#line 62 "bootstrap/stage0/ReCode.code"
struct String* String__append_cstring(struct String* self, char* s) { size_t index;
#line 63 "bootstrap/stage0/ReCode.code"
    index = ((size_t) 0);
#line 64 "bootstrap/stage0/ReCode.code"
    while (true) { char c;
#line 65 "bootstrap/stage0/ReCode.code"
        c = s[index];
#line 66 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (c == '\0') {
#line 66 "bootstrap/stage0/ReCode.code"
                {
#line 67 "bootstrap/stage0/ReCode.code"
                    return self;
                } goto if__end__1; } if__end__1: ;
        }
#line 69 "bootstrap/stage0/ReCode.code"
        String__append_char(self, c);
#line 70 "bootstrap/stage0/ReCode.code"
        index = index + ((size_t) 1);
    }}

#line 74 "bootstrap/stage0/ReCode.code"
size_t cstring_length(char* s) { size_t length;
#line 75 "bootstrap/stage0/ReCode.code"
    length = ((size_t) 0);
#line 76 "bootstrap/stage0/ReCode.code"
    while (true) { uint8_t c;
#line 77 "bootstrap/stage0/ReCode.code"
        c = ((uint8_t) s[length]);
#line 78 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (c == ((uint8_t) 0)) {
#line 78 "bootstrap/stage0/ReCode.code"
                {
#line 79 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 81 "bootstrap/stage0/ReCode.code"
        length = length + ((size_t) 1);
    }
#line 83 "bootstrap/stage0/ReCode.code"
    return length;}

#line 86 "bootstrap/stage0/ReCode.code"
struct String* String__create_from(char* data) { size_t string_length; struct String* string;
#line 87 "bootstrap/stage0/ReCode.code"
    string_length = cstring_length(data);
#line 88 "bootstrap/stage0/ReCode.code"
    string = String__create_empty(string_length);
#line 89 "bootstrap/stage0/ReCode.code"
    String__append_cstring(string, data);
#line 90 "bootstrap/stage0/ReCode.code"
    return string;}

#line 93 "bootstrap/stage0/ReCode.code"
struct String* String__append_i16(struct String* self, int16_t value) {
#line 94 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (value < ((int16_t) 0)) {
#line 94 "bootstrap/stage0/ReCode.code"
            {
#line 95 "bootstrap/stage0/ReCode.code"
                String__append_char(self, '-');
#line 96 "bootstrap/stage0/ReCode.code"
                String__append_i16(self, -value);
            } goto if__end__1; } if__else__1: ;
#line 97 "bootstrap/stage0/ReCode.code"
        {
#line 98 "bootstrap/stage0/ReCode.code"
            if__start__2: { if (value >= ((int16_t) 10)) {
#line 98 "bootstrap/stage0/ReCode.code"
                    {
#line 99 "bootstrap/stage0/ReCode.code"
                        String__append_i16(self, value / ((int16_t) 10));
                    } goto if__end__2; } if__end__2: ;
            }
#line 101 "bootstrap/stage0/ReCode.code"
            String__append_char(self, ((char) (value % ((int16_t) 10))) + '0');
        } if__end__1: ;
    }
#line 103 "bootstrap/stage0/ReCode.code"
    return self;}

#line 106 "bootstrap/stage0/ReCode.code"
struct String* String__append_string(struct String* self, struct String* other) { size_t index;
#line 107 "bootstrap/stage0/ReCode.code"
    index = ((size_t) 0);
#line 108 "bootstrap/stage0/ReCode.code"
    while (index < other->length) {
#line 109 "bootstrap/stage0/ReCode.code"
        String__append_char(self, other->data[index]);
#line 110 "bootstrap/stage0/ReCode.code"
        index = index + ((size_t) 1);
    }
#line 112 "bootstrap/stage0/ReCode.code"
    return self;}

#line 115 "bootstrap/stage0/ReCode.code"
bool String__equals_cstring(struct String* self, char* s) { size_t length; size_t index;
#line 116 "bootstrap/stage0/ReCode.code"
    length = cstring_length(s);
#line 117 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->length != length) {
#line 117 "bootstrap/stage0/ReCode.code"
            {
#line 118 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 121 "bootstrap/stage0/ReCode.code"
    index = ((size_t) 0);
#line 122 "bootstrap/stage0/ReCode.code"
    while (index < length) {
#line 123 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (self->data[index] != s[index]) {
#line 123 "bootstrap/stage0/ReCode.code"
                {
#line 124 "bootstrap/stage0/ReCode.code"
                    return false;
                } goto if__end__2; } if__end__2: ;
        }
#line 126 "bootstrap/stage0/ReCode.code"
        index = index + ((size_t) 1);
    }
#line 129 "bootstrap/stage0/ReCode.code"
    return true;}

#line 132 "bootstrap/stage0/ReCode.code"
bool String__equals_string(struct String* self, struct String* other) { size_t index;
#line 133 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->length != other->length) {
#line 133 "bootstrap/stage0/ReCode.code"
            {
#line 134 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 137 "bootstrap/stage0/ReCode.code"
    index = ((size_t) 0);
#line 138 "bootstrap/stage0/ReCode.code"
    while (index < self->length) {
#line 139 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (self->data[index] != other->data[index]) {
#line 139 "bootstrap/stage0/ReCode.code"
                {
#line 140 "bootstrap/stage0/ReCode.code"
                    return false;
                } goto if__end__2; } if__end__2: ;
        }
#line 142 "bootstrap/stage0/ReCode.code"
        index = index + ((size_t) 1);
    }
#line 145 "bootstrap/stage0/ReCode.code"
    return true;}

#line 152 "bootstrap/stage0/ReCode.code"
void File__write_char(struct File* self, char c) {
#line 153 "bootstrap/stage0/ReCode.code"
    fputc(((int32_t) c), self);}

#line 156 "bootstrap/stage0/ReCode.code"
void File__write_cstring(struct File* self, char* s) {
#line 157 "bootstrap/stage0/ReCode.code"
    fputs(s, self);}

#line 160 "bootstrap/stage0/ReCode.code"
void File__write_i32(struct File* self, int32_t value) {
#line 161 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (value < 0) {
#line 161 "bootstrap/stage0/ReCode.code"
            {
#line 162 "bootstrap/stage0/ReCode.code"
                File__write_char(self, '-');
#line 163 "bootstrap/stage0/ReCode.code"
                File__write_i32(self, -value);
            } goto if__end__1; } if__else__1: ;
#line 164 "bootstrap/stage0/ReCode.code"
        {
#line 165 "bootstrap/stage0/ReCode.code"
            if__start__2: { if (value >= 10) {
#line 165 "bootstrap/stage0/ReCode.code"
                    {
#line 166 "bootstrap/stage0/ReCode.code"
                        File__write_i32(self, value / 10);
                    } goto if__end__2; } if__end__2: ;
            }
#line 168 "bootstrap/stage0/ReCode.code"
            File__write_char(self, ((char) (value % 10)) + '0');
        } if__end__1: ;
    }}

#line 172 "bootstrap/stage0/ReCode.code"
void File__write_u64(struct File* self, uint64_t value) {
#line 173 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (value >= ((uint64_t) 10)) {
#line 173 "bootstrap/stage0/ReCode.code"
            {
#line 174 "bootstrap/stage0/ReCode.code"
                File__write_u64(self, value / ((uint64_t) 10));
            } goto if__end__1; } if__end__1: ;
    }
#line 176 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ((char) (value % ((uint64_t) 10))) + '0');}

#line 179 "bootstrap/stage0/ReCode.code"
void File__write_string(struct File* self, struct String* string) { size_t index;
#line 180 "bootstrap/stage0/ReCode.code"
    index = ((size_t) 0);
#line 181 "bootstrap/stage0/ReCode.code"
    while (index < string->length) {
#line 182 "bootstrap/stage0/ReCode.code"
        File__write_char(self, string->data[index]);
#line 183 "bootstrap/stage0/ReCode.code"
        index = index + ((size_t) 1);
    }}

#line 187 "bootstrap/stage0/ReCode.code"
void error(struct String* message) {
#line 188 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;91m");
#line 189 "bootstrap/stage0/ReCode.code"
    File__write_string(stderr, message);
#line 190 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");}

#line 193 "bootstrap/stage0/ReCode.code"
void warning(struct String* message) {
#line 194 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;93m");
#line 195 "bootstrap/stage0/ReCode.code"
    File__write_string(stderr, message);
#line 196 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");}

#line 199 "bootstrap/stage0/ReCode.code"
void TODO(char* message) {
#line 200 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;95mTODO: ");
#line 201 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, message);
#line 202 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");}

#line 214 "bootstrap/stage0/ReCode.code"
struct Source* Source__create(struct File* file, char* file_path) { struct String* file_content; struct Source* source;
#line 215 "bootstrap/stage0/ReCode.code"
    file_content = String__create();
#line 217 "bootstrap/stage0/ReCode.code"
    while (true) { int32_t ch;
#line 218 "bootstrap/stage0/ReCode.code"
        ch = fgetc(file);
#line 219 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (ch == -1) {
#line 219 "bootstrap/stage0/ReCode.code"
                {
#line 220 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 222 "bootstrap/stage0/ReCode.code"
        String__append_char(file_content, ((char) ch));
    }
#line 225 "bootstrap/stage0/ReCode.code"
    String__append_char(file_content, '\0');
#line 227 "bootstrap/stage0/ReCode.code"
    source = ((struct Source*) malloc(sizeof(struct Source)));
#line 228 "bootstrap/stage0/ReCode.code"
    source->content = file_content;
#line 229 "bootstrap/stage0/ReCode.code"
    source->path = file_path;
#line 231 "bootstrap/stage0/ReCode.code"
    return source;}

#line 244 "bootstrap/stage0/ReCode.code"
struct Source_Location* Source_Location__create(struct Source* source, uint16_t line, uint16_t column) { struct Source_Location* source_location;
#line 245 "bootstrap/stage0/ReCode.code"
    source_location = ((struct Source_Location*) malloc(sizeof(struct Source_Location)));
#line 246 "bootstrap/stage0/ReCode.code"
    source_location->source = source;
#line 247 "bootstrap/stage0/ReCode.code"
    source_location->line = line;
#line 248 "bootstrap/stage0/ReCode.code"
    source_location->column = column;
#line 249 "bootstrap/stage0/ReCode.code"
    return source_location;}

#line 252 "bootstrap/stage0/ReCode.code"
struct String* String__append_source_location(struct String* self, struct Source_Location* location) {
#line 253 "bootstrap/stage0/ReCode.code"
    String__append_cstring(self, location->source->path);
#line 254 "bootstrap/stage0/ReCode.code"
    String__append_char(self, ':');
#line 255 "bootstrap/stage0/ReCode.code"
    String__append_i16(self, ((int16_t) location->line));
#line 256 "bootstrap/stage0/ReCode.code"
    String__append_char(self, ':');
#line 257 "bootstrap/stage0/ReCode.code"
    String__append_i16(self, ((int16_t) location->column));
#line 258 "bootstrap/stage0/ReCode.code"
    return self;}

#line 261 "bootstrap/stage0/ReCode.code"
void File__write_source_location(struct File* self, struct Source_Location* location) {
#line 262 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (location != NULL) {
#line 262 "bootstrap/stage0/ReCode.code"
            {
#line 263 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, location->source->path);
#line 264 "bootstrap/stage0/ReCode.code"
                File__write_char(self, ':');
#line 265 "bootstrap/stage0/ReCode.code"
                File__write_i32(self, ((int32_t) location->line));
#line 266 "bootstrap/stage0/ReCode.code"
                File__write_char(self, ':');
#line 267 "bootstrap/stage0/ReCode.code"
                File__write_i32(self, ((int32_t) location->column));
#line 268 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, ": ");
            } goto if__end__1; } if__end__1: ;
    }}

#line 272 "bootstrap/stage0/ReCode.code"
void Source_Location__error(struct Source_Location* self, struct String* message) {
#line 273 "bootstrap/stage0/ReCode.code"
    File__write_source_location(stderr, self);
#line 274 "bootstrap/stage0/ReCode.code"
    error(message);}

#line 277 "bootstrap/stage0/ReCode.code"
void Source_Location__warning(struct Source_Location* self, struct String* message) {
#line 278 "bootstrap/stage0/ReCode.code"
    File__write_source_location(stderr, self);
#line 279 "bootstrap/stage0/ReCode.code"
    warning(message);}

#line 307 "bootstrap/stage0/ReCode.code"
struct Token* Token__create_kind(enum Token_Kind kind, size_t kind_size, struct Source_Location* location, struct String* lexeme) { struct Token* token;
#line 308 "bootstrap/stage0/ReCode.code"
    token = ((struct Token*) malloc(kind_size));
#line 309 "bootstrap/stage0/ReCode.code"
    token->kind = kind;
#line 310 "bootstrap/stage0/ReCode.code"
    token->location = location;
#line 311 "bootstrap/stage0/ReCode.code"
    token->lexeme = lexeme;
#line 312 "bootstrap/stage0/ReCode.code"
    token->next_token = NULL;
#line 313 "bootstrap/stage0/ReCode.code"
    return token;}

#line 316 "bootstrap/stage0/ReCode.code"
void Token__error(struct Token* self, struct String* message) {
#line 317 "bootstrap/stage0/ReCode.code"
    Source_Location__error(self->location, message);}

#line 320 "bootstrap/stage0/ReCode.code"
void Token__warning(struct Token* self, struct String* message) {
#line 321 "bootstrap/stage0/ReCode.code"
    Source_Location__warning(self->location, message);}

#line 329 "bootstrap/stage0/ReCode.code"
struct Character_Token* Character_Token__create(struct Source_Location* location, struct String* lexeme, char value) { struct Character_Token* token;
#line 330 "bootstrap/stage0/ReCode.code"
    token = ((struct Character_Token*) Token__create_kind(Token_Kind__CHARACTER, sizeof(struct Character_Token), location, lexeme));
#line 331 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 332 "bootstrap/stage0/ReCode.code"
    return token;}

#line 339 "bootstrap/stage0/ReCode.code"
struct Comment_Token* Comment_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 340 "bootstrap/stage0/ReCode.code"
    return ((struct Comment_Token*) Token__create_kind(Token_Kind__COMMENT, sizeof(struct Comment_Token), location, lexeme));}

#line 347 "bootstrap/stage0/ReCode.code"
struct End_Of_File_Token* End_Of_File_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 348 "bootstrap/stage0/ReCode.code"
    return ((struct End_Of_File_Token*) Token__create_kind(Token_Kind__END_OF_FILE, sizeof(struct End_Of_File_Token), location, lexeme));}

#line 355 "bootstrap/stage0/ReCode.code"
struct End_Of_Line_Token* End_Of_Line_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 356 "bootstrap/stage0/ReCode.code"
    return ((struct End_Of_Line_Token*) Token__create_kind(Token_Kind__END_OF_LINE, sizeof(struct End_Of_Line_Token), location, lexeme));}

#line 363 "bootstrap/stage0/ReCode.code"
struct Error_Token* Error_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 364 "bootstrap/stage0/ReCode.code"
    return ((struct Error_Token*) Token__create_kind(Token_Kind__ERROR, sizeof(struct Error_Token), location, lexeme));}

#line 371 "bootstrap/stage0/ReCode.code"
struct Identifier_Token* Identifier_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 372 "bootstrap/stage0/ReCode.code"
    return ((struct Identifier_Token*) Token__create_kind(Token_Kind__IDENTIFIER, sizeof(struct Identifier_Token), location, lexeme));}

#line 380 "bootstrap/stage0/ReCode.code"
struct Integer_Token* Integer_Token__create(struct Source_Location* location, struct String* lexeme, uint64_t value) { struct Integer_Token* token;
#line 381 "bootstrap/stage0/ReCode.code"
    token = ((struct Integer_Token*) Token__create_kind(Token_Kind__INTEGER, sizeof(struct Integer_Token), location, lexeme));
#line 382 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 383 "bootstrap/stage0/ReCode.code"
    return token;}

#line 390 "bootstrap/stage0/ReCode.code"
struct Other_Token* Other_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 391 "bootstrap/stage0/ReCode.code"
    return ((struct Other_Token*) Token__create_kind(Token_Kind__OTHER, sizeof(struct Other_Token), location, lexeme));}

#line 399 "bootstrap/stage0/ReCode.code"
struct Space_Token* Space_Token__create(struct Source_Location* location, struct String* lexeme, uint16_t count) { struct Space_Token* token;
#line 400 "bootstrap/stage0/ReCode.code"
    token = ((struct Space_Token*) Token__create_kind(Token_Kind__SPACE, sizeof(struct Space_Token), location, lexeme));
#line 401 "bootstrap/stage0/ReCode.code"
    token->count = count;
#line 402 "bootstrap/stage0/ReCode.code"
    return token;}

#line 410 "bootstrap/stage0/ReCode.code"
struct String_Token* String_Token__create(struct Source_Location* location, struct String* lexeme, struct String* value) { struct String_Token* token;
#line 411 "bootstrap/stage0/ReCode.code"
    token = ((struct String_Token*) Token__create_kind(Token_Kind__STRING, sizeof(struct String_Token), location, lexeme));
#line 412 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 413 "bootstrap/stage0/ReCode.code"
    return token;}

#line 416 "bootstrap/stage0/ReCode.code"
bool Token__is_anything(struct Token* self) {
#line 417 "bootstrap/stage0/ReCode.code"
    return self != NULL;}

#line 420 "bootstrap/stage0/ReCode.code"
bool Token__is_character(struct Token* self) {
#line 421 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__CHARACTER;}

#line 424 "bootstrap/stage0/ReCode.code"
bool Token__is_comment(struct Token* self) {
#line 425 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__COMMENT;}

#line 428 "bootstrap/stage0/ReCode.code"
bool Token__is_end_of_file(struct Token* self) {
#line 429 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__END_OF_FILE;}

#line 432 "bootstrap/stage0/ReCode.code"
bool Token__is_end_of_line(struct Token* self) {
#line 433 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__END_OF_LINE || self->kind == Token_Kind__END_OF_FILE;}

#line 436 "bootstrap/stage0/ReCode.code"
bool Token__is_identifier(struct Token* self) {
#line 437 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__IDENTIFIER;}

#line 440 "bootstrap/stage0/ReCode.code"
bool Token__is_integer(struct Token* self) {
#line 441 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__INTEGER;}

#line 444 "bootstrap/stage0/ReCode.code"
bool Token__is_keyword(struct Token* self, char* lexeme) {
#line 445 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);}

#line 448 "bootstrap/stage0/ReCode.code"
bool Token__is_break(struct Token* self) {
#line 449 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "break");}

#line 452 "bootstrap/stage0/ReCode.code"
bool Token__is_else(struct Token* self) {
#line 453 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "else");}

#line 456 "bootstrap/stage0/ReCode.code"
bool Token__is_enum(struct Token* self) {
#line 457 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "enum");}

#line 460 "bootstrap/stage0/ReCode.code"
bool Token__is_external(struct Token* self) {
#line 461 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "external");}

#line 464 "bootstrap/stage0/ReCode.code"
bool Token__is_false(struct Token* self) {
#line 465 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "false");}

#line 468 "bootstrap/stage0/ReCode.code"
bool Token__is_func(struct Token* self) {
#line 469 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "func");}

#line 472 "bootstrap/stage0/ReCode.code"
bool Token__is_if(struct Token* self) {
#line 473 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "if");}

#line 476 "bootstrap/stage0/ReCode.code"
bool Token__is_let(struct Token* self) {
#line 477 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "let");}

#line 480 "bootstrap/stage0/ReCode.code"
bool Token__is_null(struct Token* self) {
#line 481 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "null");}

#line 484 "bootstrap/stage0/ReCode.code"
bool Token__is_return(struct Token* self) {
#line 485 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "return");}

#line 488 "bootstrap/stage0/ReCode.code"
bool Token__is_sizeof(struct Token* self) {
#line 489 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "sizeof");}

#line 492 "bootstrap/stage0/ReCode.code"
bool Token__is_struct(struct Token* self) {
#line 493 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "struct");}

#line 496 "bootstrap/stage0/ReCode.code"
bool Token__is_true(struct Token* self) {
#line 497 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "true");}

#line 500 "bootstrap/stage0/ReCode.code"
bool Token__is_undefined(struct Token* self) {
#line 501 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "undefined");}

#line 504 "bootstrap/stage0/ReCode.code"
bool Token__is_while(struct Token* self) {
#line 505 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "while");}

#line 508 "bootstrap/stage0/ReCode.code"
bool Token__is_other(struct Token* self, char* lexeme) {
#line 509 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__OTHER && String__equals_cstring(self->lexeme, lexeme);}

#line 512 "bootstrap/stage0/ReCode.code"
bool Token__is_ampersand(struct Token* self) {
#line 513 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "&");}

#line 516 "bootstrap/stage0/ReCode.code"
bool Token__is_asterisk(struct Token* self) {
#line 517 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "*");}

#line 520 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_brace(struct Token* self) {
#line 521 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "}");}

#line 524 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_bracket(struct Token* self) {
#line 525 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "]");}

#line 528 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_paren(struct Token* self) {
#line 529 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ")");}

#line 532 "bootstrap/stage0/ReCode.code"
bool Token__is_colon(struct Token* self) {
#line 533 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ":");}

#line 536 "bootstrap/stage0/ReCode.code"
bool Token__is_comma(struct Token* self) {
#line 537 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ",");}

#line 540 "bootstrap/stage0/ReCode.code"
bool Token__is_dot(struct Token* self) {
#line 541 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ".");}

#line 544 "bootstrap/stage0/ReCode.code"
bool Token__is_equals(struct Token* self) {
#line 545 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "=");}

#line 548 "bootstrap/stage0/ReCode.code"
bool Token__is_exclamation_mark(struct Token* self) {
#line 549 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "!");}

#line 552 "bootstrap/stage0/ReCode.code"
bool Token__is_greater_than(struct Token* self) {
#line 553 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ">");}

#line 556 "bootstrap/stage0/ReCode.code"
bool Token__is_less_than(struct Token* self) {
#line 557 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "<");}

#line 560 "bootstrap/stage0/ReCode.code"
bool Token__is_minus(struct Token* self) {
#line 561 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "-");}

#line 564 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_brace(struct Token* self) {
#line 565 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "{");}

#line 568 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_bracket(struct Token* self) {
#line 569 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "[");}

#line 572 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_paren(struct Token* self) {
#line 573 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "(");}

#line 576 "bootstrap/stage0/ReCode.code"
bool Token__is_percent(struct Token* self) {
#line 577 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "%");}

#line 580 "bootstrap/stage0/ReCode.code"
bool Token__is_plus(struct Token* self) {
#line 581 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "+");}

#line 584 "bootstrap/stage0/ReCode.code"
bool Token__is_slash(struct Token* self) {
#line 585 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "/");}

#line 588 "bootstrap/stage0/ReCode.code"
bool Token__is_vertical_bar(struct Token* self) {
#line 589 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "|");}

#line 592 "bootstrap/stage0/ReCode.code"
bool Token__is_space(struct Token* self) {
#line 593 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__SPACE;}

#line 596 "bootstrap/stage0/ReCode.code"
bool Token__is_string(struct Token* self) {
#line 597 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__STRING;}

#line 600 "bootstrap/stage0/ReCode.code"
void File__write_token(struct File* stream, struct Token* token) { bool colored;
#line 601 "bootstrap/stage0/ReCode.code"
    colored = token->kind == Token_Kind__COMMENT || token->kind == Token_Kind__ERROR || token->kind == Token_Kind__OTHER;
#line 602 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (colored) {
#line 602 "bootstrap/stage0/ReCode.code"
            {
#line 603 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (token->kind == Token_Kind__OTHER) {
#line 603 "bootstrap/stage0/ReCode.code"
                        {
#line 604 "bootstrap/stage0/ReCode.code"
                            File__write_cstring(stream, "\33[2;33m");
                        } goto if__end__2; } if__else__2: ;
#line 605 "bootstrap/stage0/ReCode.code"
                    if__start__3: { if (token->kind == Token_Kind__COMMENT) {
#line 605 "bootstrap/stage0/ReCode.code"
                            {
#line 606 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(stream, "\33[2;37m");
                            } goto if__end__3; } if__else__3: ;
#line 607 "bootstrap/stage0/ReCode.code"
                        if__start__4: { if (token->kind == Token_Kind__ERROR) {
#line 607 "bootstrap/stage0/ReCode.code"
                                {
#line 608 "bootstrap/stage0/ReCode.code"
                                    File__write_cstring(stream, "\33[2;31m");
                                } goto if__end__4; } if__end__4: ;
                        } if__end__3: ;
                    } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 611 "bootstrap/stage0/ReCode.code"
    File__write_string(stream, token->lexeme);
#line 612 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (colored) {
#line 612 "bootstrap/stage0/ReCode.code"
            {
#line 613 "bootstrap/stage0/ReCode.code"
                File__write_cstring(stream, "\33[0m");
            } goto if__end__5; } if__end__5: ;
    }}

#line 629 "bootstrap/stage0/ReCode.code"
char Scanner__peek_char(struct Scanner* self) {
#line 630 "bootstrap/stage0/ReCode.code"
    return self->source->content->data[self->current_char_index];}

#line 633 "bootstrap/stage0/ReCode.code"
char Scanner__next_char(struct Scanner* self) { char next_char;
#line 634 "bootstrap/stage0/ReCode.code"
    next_char = Scanner__peek_char(self);
#line 635 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (next_char != '\0') {
#line 635 "bootstrap/stage0/ReCode.code"
            {
#line 636 "bootstrap/stage0/ReCode.code"
                self->current_char_index = self->current_char_index + ((size_t) 1);
#line 637 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (next_char == '\n') {
#line 637 "bootstrap/stage0/ReCode.code"
                        {
#line 638 "bootstrap/stage0/ReCode.code"
                            self->current_line = self->current_line + ((uint16_t) 1);
#line 639 "bootstrap/stage0/ReCode.code"
                            self->current_column = ((uint16_t) 1);
                        } goto if__end__2; } if__else__2: ;
#line 640 "bootstrap/stage0/ReCode.code"
                    {
#line 641 "bootstrap/stage0/ReCode.code"
                        self->current_column = self->current_column + ((uint16_t) 1);
                    } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 644 "bootstrap/stage0/ReCode.code"
    return next_char;}

#line 647 "bootstrap/stage0/ReCode.code"
char escape_char_value(char c) {
#line 648 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (c == 'n') {
#line 648 "bootstrap/stage0/ReCode.code"
            {
#line 649 "bootstrap/stage0/ReCode.code"
                return '\n';
            } goto if__end__1; } if__end__1: ;
    }
#line 651 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (c == '\"') {
#line 651 "bootstrap/stage0/ReCode.code"
            {
#line 652 "bootstrap/stage0/ReCode.code"
                return '\"';
            } goto if__end__2; } if__end__2: ;
    }
#line 654 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (c == '\'') {
#line 654 "bootstrap/stage0/ReCode.code"
            {
#line 655 "bootstrap/stage0/ReCode.code"
                return '\'';
            } goto if__end__3; } if__end__3: ;
    }
#line 657 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (c == '\\') {
#line 657 "bootstrap/stage0/ReCode.code"
            {
#line 658 "bootstrap/stage0/ReCode.code"
                return '\\';
            } goto if__end__4; } if__end__4: ;
    }
#line 660 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (c == 't') {
#line 660 "bootstrap/stage0/ReCode.code"
            {
#line 661 "bootstrap/stage0/ReCode.code"
                return '\t';
            } goto if__end__5; } if__end__5: ;
    }
#line 663 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (c == '0') {
#line 663 "bootstrap/stage0/ReCode.code"
            {
#line 664 "bootstrap/stage0/ReCode.code"
                return '\0';
            } goto if__end__6; } if__end__6: ;
    }
#line 666 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (c == 'e') {
#line 666 "bootstrap/stage0/ReCode.code"
            {
#line 667 "bootstrap/stage0/ReCode.code"
                return '\33';
            } goto if__end__7; } if__end__7: ;
    }
#line 669 "bootstrap/stage0/ReCode.code"
    return -((char) 1);}

#line 672 "bootstrap/stage0/ReCode.code"
bool char_is_end_of_line(char c) {
#line 673 "bootstrap/stage0/ReCode.code"
    return c == '\n' || c == '\0';}

#line 676 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_character_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { char next_char; char value;
#line 677 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Scanner__next_char(self) != '\'') {
#line 677 "bootstrap/stage0/ReCode.code"
            {
#line 678 "bootstrap/stage0/ReCode.code"
                Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 679 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 681 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\'');
#line 683 "bootstrap/stage0/ReCode.code"
    next_char = Scanner__peek_char(self);
#line 684 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__2; } } if__then__2__3: {
#line 684 "bootstrap/stage0/ReCode.code"
            {
#line 685 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
            } goto if__end__2; } if__end__2: ;
    }
#line 688 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 689 "bootstrap/stage0/ReCode.code"
    value = next_char;
#line 691 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (value == '\'') {
#line 691 "bootstrap/stage0/ReCode.code"
            {
#line 692 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
            } goto if__end__4; } if__end__4: ;
    }
#line 695 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (value == '\\') {
#line 695 "bootstrap/stage0/ReCode.code"
            {
#line 696 "bootstrap/stage0/ReCode.code"
                next_char = Scanner__peek_char(self);
#line 697 "bootstrap/stage0/ReCode.code"
                if__start__6: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__6; } } if__then__6__7: {
#line 697 "bootstrap/stage0/ReCode.code"
                        {
#line 698 "bootstrap/stage0/ReCode.code"
                            return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                        } goto if__end__6; } if__end__6: ;
                }
#line 701 "bootstrap/stage0/ReCode.code"
                String__append_char(token_lexeme, Scanner__next_char(self));
#line 703 "bootstrap/stage0/ReCode.code"
                value = escape_char_value(next_char);
#line 704 "bootstrap/stage0/ReCode.code"
                if__start__8: { if (value == -((char) 1)) {
#line 704 "bootstrap/stage0/ReCode.code"
                        {
#line 705 "bootstrap/stage0/ReCode.code"
                            return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                        } goto if__end__8; } if__end__8: ;
                }
            } goto if__end__5; } if__end__5: ;
    }
#line 709 "bootstrap/stage0/ReCode.code"
    if__start__9: { if (Scanner__peek_char(self) != '\'') {
#line 709 "bootstrap/stage0/ReCode.code"
            {
#line 710 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
            } goto if__end__9; } if__end__9: ;
    }
#line 713 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 714 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Character_Token__create(source_location, token_lexeme, value));}

#line 717 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_comment_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 718 "bootstrap/stage0/ReCode.code"
    while (!(char_is_end_of_line(Scanner__peek_char(self)))) {
#line 719 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 721 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Comment_Token__create(source_location, token_lexeme));}

#line 724 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_start(char c) {
#line 725 "bootstrap/stage0/ReCode.code"
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';}

#line 728 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_letter(char c) {
#line 729 "bootstrap/stage0/ReCode.code"
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');}

#line 732 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_identifier_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 733 "bootstrap/stage0/ReCode.code"
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
#line 734 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 736 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Identifier_Token__create(source_location, token_lexeme));}

#line 739 "bootstrap/stage0/ReCode.code"
bool char_is_digit(char c) {
#line 740 "bootstrap/stage0/ReCode.code"
    return c >= '0' && c <= '9';}

#line 743 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_integer_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { uint64_t value;
#line 744 "bootstrap/stage0/ReCode.code"
    value = ((uint64_t) 0);
#line 745 "bootstrap/stage0/ReCode.code"
    while (char_is_digit(Scanner__peek_char(self))) { char c;
#line 746 "bootstrap/stage0/ReCode.code"
        c = Scanner__next_char(self);
#line 747 "bootstrap/stage0/ReCode.code"
        value = value * ((uint64_t) 10) + ((uint64_t) (c - '0'));
#line 748 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, c);
    }
#line 750 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Integer_Token__create(source_location, token_lexeme, value));}

#line 753 "bootstrap/stage0/ReCode.code"
bool char_is_space(char c) {
#line 754 "bootstrap/stage0/ReCode.code"
    return c == ' ';}

#line 757 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_space_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { uint16_t count;
#line 758 "bootstrap/stage0/ReCode.code"
    count = ((uint16_t) 0);
#line 759 "bootstrap/stage0/ReCode.code"
    while (char_is_space(Scanner__peek_char(self))) {
#line 760 "bootstrap/stage0/ReCode.code"
        count = count + ((uint16_t) 1);
#line 761 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 763 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Space_Token__create(source_location, token_lexeme, count));}

#line 766 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_string_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { struct String* value;
#line 767 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Scanner__next_char(self) != '\"') {
#line 767 "bootstrap/stage0/ReCode.code"
            {
#line 768 "bootstrap/stage0/ReCode.code"
                Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 769 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 771 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\"');
#line 773 "bootstrap/stage0/ReCode.code"
    value = String__create();
#line 775 "bootstrap/stage0/ReCode.code"
    while (true) { char next_char;
#line 776 "bootstrap/stage0/ReCode.code"
        next_char = Scanner__peek_char(self);
#line 777 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__2; } } if__then__2__3: {
#line 777 "bootstrap/stage0/ReCode.code"
                {
#line 778 "bootstrap/stage0/ReCode.code"
                    return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                } goto if__end__2; } if__end__2: ;
        }
#line 781 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 783 "bootstrap/stage0/ReCode.code"
        if__start__4: { if (next_char == '\"') {
#line 783 "bootstrap/stage0/ReCode.code"
                {
#line 784 "bootstrap/stage0/ReCode.code"
                    return ((struct Token*) String_Token__create(source_location, token_lexeme, value));
                } goto if__end__4; } if__end__4: ;
        }
#line 787 "bootstrap/stage0/ReCode.code"
        if__start__5: { if (next_char == '\\') {
#line 787 "bootstrap/stage0/ReCode.code"
                {
#line 788 "bootstrap/stage0/ReCode.code"
                    next_char = Scanner__peek_char(self);
#line 789 "bootstrap/stage0/ReCode.code"
                    if__start__6: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__6; } } if__then__6__7: {
#line 789 "bootstrap/stage0/ReCode.code"
                            {
#line 790 "bootstrap/stage0/ReCode.code"
                                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                            } goto if__end__6; } if__end__6: ;
                    }
#line 793 "bootstrap/stage0/ReCode.code"
                    String__append_char(token_lexeme, Scanner__next_char(self));
#line 795 "bootstrap/stage0/ReCode.code"
                    next_char = escape_char_value(next_char);
#line 796 "bootstrap/stage0/ReCode.code"
                    if__start__8: { if (next_char == -((char) 1)) {
#line 796 "bootstrap/stage0/ReCode.code"
                            {
#line 797 "bootstrap/stage0/ReCode.code"
                                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                            } goto if__end__8; } if__end__8: ;
                    }
                } goto if__end__5; } if__end__5: ;
        }
#line 801 "bootstrap/stage0/ReCode.code"
        String__append_char(value, next_char);
    }}

#line 805 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_token(struct Scanner* self) { struct Source_Location* source_location; struct String* token_lexeme; char next_char;
#line 806 "bootstrap/stage0/ReCode.code"
    source_location = Source_Location__create(self->source, self->current_line, self->current_column);
#line 807 "bootstrap/stage0/ReCode.code"
    token_lexeme = String__create();
#line 809 "bootstrap/stage0/ReCode.code"
    next_char = Scanner__peek_char(self);
#line 811 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (char_is_identifier_start(next_char)) {
#line 811 "bootstrap/stage0/ReCode.code"
            {
#line 812 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_identifier_token(self, source_location, token_lexeme);
            } goto if__end__1; } if__end__1: ;
    }
#line 815 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (char_is_digit(next_char)) {
#line 815 "bootstrap/stage0/ReCode.code"
            {
#line 816 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_integer_token(self, source_location, token_lexeme);
            } goto if__end__2; } if__end__2: ;
    }
#line 819 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (char_is_space(next_char)) {
#line 819 "bootstrap/stage0/ReCode.code"
            {
#line 820 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_space_token(self, source_location, token_lexeme);
            } goto if__end__3; } if__end__3: ;
    }
#line 823 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (next_char == '\'') {
#line 823 "bootstrap/stage0/ReCode.code"
            {
#line 824 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_character_token(self, source_location, token_lexeme);
            } goto if__end__4; } if__end__4: ;
    }
#line 827 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (next_char == '\"') {
#line 827 "bootstrap/stage0/ReCode.code"
            {
#line 828 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_string_token(self, source_location, token_lexeme);
            } goto if__end__5; } if__end__5: ;
    }
#line 831 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (next_char == '\\') {
#line 831 "bootstrap/stage0/ReCode.code"
            {
#line 832 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_comment_token(self, source_location, token_lexeme);
            } goto if__end__6; } if__end__6: ;
    }
#line 835 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (next_char == '\n') {
#line 835 "bootstrap/stage0/ReCode.code"
            {
#line 836 "bootstrap/stage0/ReCode.code"
                String__append_char(token_lexeme, Scanner__next_char(self));
#line 837 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) End_Of_Line_Token__create(source_location, token_lexeme));
            } goto if__end__7; } if__end__7: ;
    }
#line 840 "bootstrap/stage0/ReCode.code"
    if__start__8: { if (next_char == '\0') {
#line 840 "bootstrap/stage0/ReCode.code"
            {
#line 841 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) End_Of_File_Token__create(source_location, token_lexeme));
            } goto if__end__8; } if__end__8: ;
    }
#line 844 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 845 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Other_Token__create(source_location, token_lexeme));}

#line 848 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__next_token(struct Scanner* self) {
#line 849 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->current_token->next_token == NULL) {
#line 849 "bootstrap/stage0/ReCode.code"
            {
#line 850 "bootstrap/stage0/ReCode.code"
                self->current_token->next_token = Scanner__scan_token(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 852 "bootstrap/stage0/ReCode.code"
    self->current_token = self->current_token->next_token;
#line 853 "bootstrap/stage0/ReCode.code"
    return self->current_token;}

#line 856 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__peek_token(struct Scanner* self, uint8_t offset) { struct Token* token;
#line 857 "bootstrap/stage0/ReCode.code"
    token = self->current_token;
#line 858 "bootstrap/stage0/ReCode.code"
    while (offset > ((uint8_t) 0)) {
#line 859 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (token->next_token == NULL) {
#line 859 "bootstrap/stage0/ReCode.code"
                {
#line 860 "bootstrap/stage0/ReCode.code"
                    token->next_token = Scanner__scan_token(self);
                } goto if__end__1; } if__end__1: ;
        }
#line 862 "bootstrap/stage0/ReCode.code"
        token = token->next_token;
#line 863 "bootstrap/stage0/ReCode.code"
        offset = offset - ((uint8_t) 1);
    }
#line 865 "bootstrap/stage0/ReCode.code"
    return token;}

#line 868 "bootstrap/stage0/ReCode.code"
struct Scanner* Scanner__create(struct Source* source) { struct Scanner* scanner;
#line 869 "bootstrap/stage0/ReCode.code"
    scanner = ((struct Scanner*) malloc(sizeof(struct Scanner)));
#line 870 "bootstrap/stage0/ReCode.code"
    scanner->source = source;
#line 871 "bootstrap/stage0/ReCode.code"
    scanner->current_char_index = ((size_t) 0);
#line 872 "bootstrap/stage0/ReCode.code"
    scanner->current_line = ((uint16_t) 1);
#line 873 "bootstrap/stage0/ReCode.code"
    scanner->current_column = ((uint16_t) 1);
#line 875 "bootstrap/stage0/ReCode.code"
    scanner->current_token = Scanner__scan_token(scanner);
#line 877 "bootstrap/stage0/ReCode.code"
    return scanner;}

#line 900 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Type__create_kind(enum Parsed_Type_Kind kind, size_t kind_size, struct Source_Location* location) { struct Parsed_Type* type;
#line 901 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Type*) malloc(kind_size));
#line 902 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 903 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 904 "bootstrap/stage0/ReCode.code"
    return type;}

#line 914 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parsed_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Parsed_Type* type) { struct Parsed_Function_Parameter* parameter;
#line 915 "bootstrap/stage0/ReCode.code"
    parameter = ((struct Parsed_Function_Parameter*) malloc(sizeof(struct Parsed_Function_Parameter)));
#line 916 "bootstrap/stage0/ReCode.code"
    parameter->location = location;
#line 917 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 918 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 919 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 920 "bootstrap/stage0/ReCode.code"
    return parameter;}

#line 929 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Type* Parsed_Function_Type__create(struct Source_Location* location, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* return_type) { struct Parsed_Function_Type* type;
#line 930 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Function_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__FUNCTION, sizeof(struct Parsed_Function_Type), location));
#line 931 "bootstrap/stage0/ReCode.code"
    type->first_parameter = first_parameter;
#line 932 "bootstrap/stage0/ReCode.code"
    type->return_type = return_type;
#line 933 "bootstrap/stage0/ReCode.code"
    return type;}

#line 941 "bootstrap/stage0/ReCode.code"
struct Parsed_Named_Type* Parsed_Named_Type__create(struct Token* name) { struct Parsed_Named_Type* type;
#line 942 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Named_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__NAMED, sizeof(struct Parsed_Named_Type), name->location));
#line 943 "bootstrap/stage0/ReCode.code"
    type->name = name->lexeme;
#line 944 "bootstrap/stage0/ReCode.code"
    return type;}

#line 952 "bootstrap/stage0/ReCode.code"
struct Parsed_Pointer_Type* Parsed_Pointer_Type__create(struct Parsed_Type* other_type) { struct Parsed_Pointer_Type* type;
#line 953 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Pointer_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__POINTER, sizeof(struct Parsed_Pointer_Type), other_type->location));
#line 954 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 955 "bootstrap/stage0/ReCode.code"
    return type;}

#line 963 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Type* Parsed_Struct_Type__create(struct Source_Location* location, struct Parsed_Type* other_type) { struct Parsed_Struct_Type* type;
#line 964 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Struct_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__STRUCT, sizeof(struct Parsed_Struct_Type), location));
#line 965 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 966 "bootstrap/stage0/ReCode.code"
    return type;}

#line 1006 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parsed_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location) { struct Parsed_Expression* expression;
#line 1007 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Expression*) malloc(kind_size));
#line 1008 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 1009 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 1010 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1019 "bootstrap/stage0/ReCode.code"
struct Parsed_Binary_Expression* Parsed_Binary_Expression__create_kind(enum Parsed_Expression_Kind kind, struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) { struct Parsed_Binary_Expression* expression;
#line 1020 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Binary_Expression*) Parsed_Expression__create_kind(kind, sizeof(struct Parsed_Binary_Expression), left_expression->location));
#line 1021 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 1022 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 1023 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1031 "bootstrap/stage0/ReCode.code"
struct Parsed_Unary_Expression* Parsed_Unary_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Parsed_Expression* other_expression) { struct Parsed_Unary_Expression* expression;
#line 1032 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Unary_Expression*) Parsed_Expression__create_kind(kind, kind_size, location));
#line 1033 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1034 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1042 "bootstrap/stage0/ReCode.code"
struct Parsed_Literal_Expression* Parsed_Literal_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Token* literal) { struct Parsed_Literal_Expression* expression;
#line 1043 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Literal_Expression*) Parsed_Expression__create_kind(kind, kind_size, literal->location));
#line 1044 "bootstrap/stage0/ReCode.code"
    expression->literal = literal;
#line 1045 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1052 "bootstrap/stage0/ReCode.code"
struct Parsed_Add_Expression* Parsed_Add_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1053 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Add_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__ADD, left_expression, right_expression));}

#line 1060 "bootstrap/stage0/ReCode.code"
struct Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1061 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Address_Of_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__ADDRESS_OF, sizeof(struct Parsed_Address_Of_Expression), location, other_expression));}

#line 1070 "bootstrap/stage0/ReCode.code"
struct Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(struct Parsed_Expression* array_expression, struct Parsed_Expression* index_expression) { struct Parsed_Array_Access_Expression* expression;
#line 1071 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Array_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__ARRAY_ACCESS, sizeof(struct Parsed_Array_Access_Expression), array_expression->location));
#line 1072 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 1073 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 1074 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1082 "bootstrap/stage0/ReCode.code"
struct Parsed_Bool_Expression* Parsed_Bool_Expression__create(struct Token* literal, bool value) { struct Parsed_Bool_Expression* expression;
#line 1083 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Bool_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__BOOL, sizeof(struct Parsed_Bool_Expression), literal));
#line 1084 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 1085 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1093 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Argument* Parsed_Call_Argument__create(struct Parsed_Expression* expression) { struct Parsed_Call_Argument* argument;
#line 1094 "bootstrap/stage0/ReCode.code"
    argument = ((struct Parsed_Call_Argument*) malloc(sizeof(struct Parsed_Call_Argument)));
#line 1095 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 1096 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 1097 "bootstrap/stage0/ReCode.code"
    return argument;}

#line 1106 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Expression* Parsed_Call_Expression__create(struct Parsed_Expression* callee_expression) { struct Parsed_Call_Expression* expression;
#line 1107 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Call_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__CALL, sizeof(struct Parsed_Call_Expression), callee_expression->location));
#line 1108 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 1109 "bootstrap/stage0/ReCode.code"
    expression->first_argument = NULL;
#line 1110 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1118 "bootstrap/stage0/ReCode.code"
struct Parsed_Cast_Expression* Parsed_Cast_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression, struct Parsed_Type* type) { struct Parsed_Cast_Expression* expression;
#line 1119 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Cast_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__CAST, sizeof(struct Parsed_Cast_Expression), location, other_expression));
#line 1120 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1121 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1129 "bootstrap/stage0/ReCode.code"
struct Parsed_Character_Expression* Parsed_Character_Expression__create(struct Character_Token* literal) { struct Parsed_Character_Expression* expression;
#line 1130 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Character_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__CHARACTER, sizeof(struct Parsed_Character_Expression), ((struct Token*) literal)));
#line 1131 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1132 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1140 "bootstrap/stage0/ReCode.code"
struct Parsed_Dereference_Expression* Parsed_Dereference_Expression__create(struct Parsed_Expression* value_expression) { struct Parsed_Dereference_Expression* expression;
#line 1141 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Dereference_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__DEREFERENCE, sizeof(struct Parsed_Dereference_Expression), value_expression->location));
#line 1142 "bootstrap/stage0/ReCode.code"
    expression->value_expression = value_expression;
#line 1143 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1150 "bootstrap/stage0/ReCode.code"
struct Parsed_Divide_Expression* Parsed_Divide_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1151 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Divide_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__DIVIDE, left_expression, right_expression));}

#line 1158 "bootstrap/stage0/ReCode.code"
struct Parsed_Equals_Expression* Parsed_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1159 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__EQUALS, left_expression, right_expression));}

#line 1166 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Expression* Parsed_Greater_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1167 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Greater_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER, left_expression, right_expression));}

#line 1174 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1175 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Greater_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER_OR_EQUALS, left_expression, right_expression));}

#line 1183 "bootstrap/stage0/ReCode.code"
struct Parsed_Group_Expression* Parsed_Group_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) { struct Parsed_Group_Expression* expression;
#line 1184 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Group_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__GROUP, sizeof(struct Parsed_Group_Expression), location));
#line 1185 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1186 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1194 "bootstrap/stage0/ReCode.code"
struct Parsed_Integer_Expression* Parsed_Integer_Expression__create(struct Integer_Token* literal) { struct Parsed_Integer_Expression* expression;
#line 1195 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Integer_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__INTEGER, sizeof(struct Parsed_Integer_Expression), ((struct Token*) literal)));
#line 1196 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1197 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1204 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Expression* Parsed_Less_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1205 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Less_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS, left_expression, right_expression));}

#line 1212 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1213 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Less_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS_OR_EQUALS, left_expression, right_expression));}

#line 1220 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1221 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Logic_And_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_AND, left_expression, right_expression));}

#line 1228 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1229 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Logic_Or_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_OR, left_expression, right_expression));}

#line 1238 "bootstrap/stage0/ReCode.code"
struct Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(struct Parsed_Expression* object_expression, struct Token* member_name) { struct Parsed_Member_Access_Expression* expression;
#line 1239 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Member_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__MEMBER_ACCESS, sizeof(struct Parsed_Member_Access_Expression), object_expression->location));
#line 1240 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 1241 "bootstrap/stage0/ReCode.code"
    expression->member_name = member_name;
#line 1242 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1249 "bootstrap/stage0/ReCode.code"
struct Parsed_Minus_Expression* Parsed_Minus_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1250 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Minus_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__MINUS, sizeof(struct Parsed_Minus_Expression), location, other_expression));}

#line 1257 "bootstrap/stage0/ReCode.code"
struct Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1258 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Modulo_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MODULO, left_expression, right_expression));}

#line 1265 "bootstrap/stage0/ReCode.code"
struct Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1266 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Multiply_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MULTIPLY, left_expression, right_expression));}

#line 1273 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Expression* Parsed_Not_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1274 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Not_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__NOT, sizeof(struct Parsed_Not_Expression), location, other_expression));}

#line 1281 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1282 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Not_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__NOT_EQUALS, left_expression, right_expression));}

#line 1289 "bootstrap/stage0/ReCode.code"
struct Parsed_Null_Expression* Parsed_Null_Expression__create(struct Token* literal) {
#line 1290 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Null_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__NULL, sizeof(struct Parsed_Null_Expression), literal));}

#line 1298 "bootstrap/stage0/ReCode.code"
struct Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(struct Source_Location* location, struct Parsed_Type* type) { struct Parsed_Sizeof_Expression* expression;
#line 1299 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Sizeof_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SIZEOF, sizeof(struct Parsed_Sizeof_Expression), location));
#line 1300 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1301 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1309 "bootstrap/stage0/ReCode.code"
struct Parsed_String_Expression* Parsed_String_Expression__create(struct String_Token* literal) { struct Parsed_String_Expression* expression;
#line 1310 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_String_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__STRING, sizeof(struct Parsed_String_Expression), ((struct Token*) literal)));
#line 1311 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1312 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1319 "bootstrap/stage0/ReCode.code"
struct Parsed_Substract_Expression* Parsed_Substract_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1320 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Substract_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__SUBSTRACT, left_expression, right_expression));}

#line 1328 "bootstrap/stage0/ReCode.code"
struct Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(struct Token* name) { struct Parsed_Symbol_Expression* expression;
#line 1329 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Symbol_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SYMBOL, sizeof(struct Parsed_Symbol_Expression), name->location));
#line 1330 "bootstrap/stage0/ReCode.code"
    expression->name = name;
#line 1331 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1355 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location) { struct Parsed_Statement* statement;
#line 1356 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Statement*) malloc(kind_size));
#line 1357 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 1358 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 1359 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 1360 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1368 "bootstrap/stage0/ReCode.code"
struct Parsed_Named_Statement* Parsed_Named_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location, struct Token* name) { struct Parsed_Named_Statement* statement;
#line 1369 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Named_Statement*) Parsed_Statement__create_kind(kind, kind_size, location));
#line 1370 "bootstrap/stage0/ReCode.code"
    statement->name = name;
#line 1371 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1380 "bootstrap/stage0/ReCode.code"
struct Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(struct Parsed_Expression* object_expression, struct Parsed_Expression* value_expression) { struct Parsed_Assignment_Statement* statement;
#line 1381 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Assignment_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__ASSIGNMENT, sizeof(struct Parsed_Assignment_Statement), object_expression->location));
#line 1382 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 1383 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 1384 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1392 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parsed_Block_Statement__create(struct Source_Location* location, struct Parsed_Statements* statements) { struct Parsed_Block_Statement* statement;
#line 1393 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Block_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__BLOCK, sizeof(struct Parsed_Block_Statement), location));
#line 1394 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1395 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1402 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Break_Statement__create(struct Source_Location* location) {
#line 1403 "bootstrap/stage0/ReCode.code"
    return Parsed_Statement__create_kind(Parsed_Statement_Kind__BREAK, sizeof(struct Parsed_Break_Statement), location);}

#line 1411 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Member* Parsed_Enum_Member__create(struct Token* name) { struct Parsed_Enum_Member* member;
#line 1412 "bootstrap/stage0/ReCode.code"
    member = ((struct Parsed_Enum_Member*) malloc(sizeof(struct Parsed_Enum_Member)));
#line 1413 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1414 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1415 "bootstrap/stage0/ReCode.code"
    return member;}

#line 1423 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Statement* Parsed_Enum_Statement__create(struct Source_Location* location, struct Token* name) { struct Parsed_Enum_Statement* statement;
#line 1424 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Enum_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__ENUM, sizeof(struct Parsed_Enum_Statement), location, name));
#line 1425 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1426 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1434 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression_Statement* Parsed_Expression_Statement__create(struct Parsed_Expression* expression) { struct Parsed_Expression_Statement* statement;
#line 1435 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Expression_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__EXPRESSION, sizeof(struct Parsed_Expression_Statement), expression->location));
#line 1436 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1437 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1448 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Function_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* resturn_type, struct Parsed_Statements* statements, bool is_external) { struct Parsed_Function_Statement* statement;
#line 1449 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Function_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__FUNCTION, sizeof(struct Parsed_Function_Statement), location, name));
#line 1450 "bootstrap/stage0/ReCode.code"
    statement->first_parameter = first_parameter;
#line 1451 "bootstrap/stage0/ReCode.code"
    statement->return_type = resturn_type;
#line 1452 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1453 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1454 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1464 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_If_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* true_statement, struct Parsed_Statement* false_statement) { struct Parsed_If_Statement* statement;
#line 1465 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_If_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__IF, sizeof(struct Parsed_If_Statement), location));
#line 1466 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1467 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 1468 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 1469 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1476 "bootstrap/stage0/ReCode.code"
struct Parsed_Opaque_Type_Statement* Parsed_Opaque_Type_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1477 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Opaque_Type_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__OPAQUE_TYPE, sizeof(struct Parsed_Opaque_Type_Statement), location, name));}

#line 1485 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Return_Statement__create(struct Source_Location* location, struct Parsed_Expression* expression) { struct Parsed_Return_Statement* statement;
#line 1486 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Return_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__RETURN, sizeof(struct Parsed_Return_Statement), location));
#line 1487 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1488 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1497 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Member* Parsed_Struct_Member__create(struct Token* name, struct Parsed_Type* type) { struct Parsed_Struct_Member* member;
#line 1498 "bootstrap/stage0/ReCode.code"
    member = ((struct Parsed_Struct_Member*) malloc(sizeof(struct Parsed_Struct_Member)));
#line 1499 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1500 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 1501 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1502 "bootstrap/stage0/ReCode.code"
    return member;}

#line 1510 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Statement* Parsed_Struct_Statement__create(struct Source_Location* location, struct Token* name) { struct Parsed_Struct_Statement* statement;
#line 1511 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Struct_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__STRUCT, sizeof(struct Parsed_Struct_Statement), location, name));
#line 1512 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1513 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1523 "bootstrap/stage0/ReCode.code"
struct Parsed_Variable_Statement* Parsed_Variable_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Type* type, bool is_external) { struct Parsed_Variable_Statement* statement;
#line 1524 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Variable_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__VARIABLE, sizeof(struct Parsed_Variable_Statement), location, name));
#line 1525 "bootstrap/stage0/ReCode.code"
    statement->type = type;
#line 1526 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1527 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1536 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_While_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* body_statement) { struct Parsed_While_Statement* statement;
#line 1537 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_While_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__WHILE, sizeof(struct Parsed_While_Statement), location));
#line 1538 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1539 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 1540 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1549 "bootstrap/stage0/ReCode.code"
struct Parsed_Statements* Parsed_Statements__create(bool has_globals) { struct Parsed_Statements* statements;
#line 1550 "bootstrap/stage0/ReCode.code"
    statements = ((struct Parsed_Statements*) malloc(sizeof(struct Parsed_Statements)));
#line 1551 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 1552 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 1553 "bootstrap/stage0/ReCode.code"
    statements->has_globals = has_globals;
#line 1554 "bootstrap/stage0/ReCode.code"
    return statements;}

#line 1557 "bootstrap/stage0/ReCode.code"
void Parsed_Statements__append(struct Parsed_Statements* self, struct Parsed_Statement* statement) {
#line 1558 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->first_statement == NULL) {
#line 1558 "bootstrap/stage0/ReCode.code"
            {
#line 1559 "bootstrap/stage0/ReCode.code"
                self->first_statement = statement;
            } goto if__end__1; } if__else__1: ;
#line 1560 "bootstrap/stage0/ReCode.code"
        {
#line 1561 "bootstrap/stage0/ReCode.code"
            self->last_statement->next_statement = statement;
        } if__end__1: ;
    }
#line 1563 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;}

#line 1566 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* Parsed_Compilation_Unit__create() { struct Parsed_Source* compilation_unit;
#line 1567 "bootstrap/stage0/ReCode.code"
    compilation_unit = ((struct Parsed_Source*) malloc(sizeof(struct Parsed_Source)));
#line 1568 "bootstrap/stage0/ReCode.code"
    compilation_unit->statements = Parsed_Statements__create(true);
#line 1569 "bootstrap/stage0/ReCode.code"
    return compilation_unit;}

#line 1582 "bootstrap/stage0/ReCode.code"
void Parser__error(struct Parser* self, struct String* message) {
#line 1583 "bootstrap/stage0/ReCode.code"
    Token__error(self->scanner->current_token, message);}

#line 1586 "bootstrap/stage0/ReCode.code"
void Parser__warning(struct Parser* self, struct String* message) {
#line 1587 "bootstrap/stage0/ReCode.code"
    Token__warning(self->scanner->current_token, message);}

#line 1590 "bootstrap/stage0/ReCode.code"
struct Token* Parser__peek_token(struct Parser* self, uint8_t offset) {
#line 1591 "bootstrap/stage0/ReCode.code"
    return Scanner__peek_token(self->scanner, offset);}

#line 1594 "bootstrap/stage0/ReCode.code"
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token*), bool first_required, bool (*second_is)(struct Token*), bool second_required, bool (*third_is)(struct Token*)) { uint8_t peek_offset;
#line 1595 "bootstrap/stage0/ReCode.code"
    peek_offset = ((uint8_t) 0);
#line 1596 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (first_is(Parser__peek_token(self, peek_offset))) {
#line 1596 "bootstrap/stage0/ReCode.code"
            {
#line 1597 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + ((uint8_t) 1);
            } goto if__end__1; } if__else__1: ;
#line 1598 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (first_required) {
#line 1598 "bootstrap/stage0/ReCode.code"
                {
#line 1599 "bootstrap/stage0/ReCode.code"
                    return false;
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 1601 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (second_is != NULL) {
#line 1601 "bootstrap/stage0/ReCode.code"
            {
#line 1602 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (second_is(Parser__peek_token(self, peek_offset))) {
#line 1602 "bootstrap/stage0/ReCode.code"
                        {
#line 1603 "bootstrap/stage0/ReCode.code"
                            peek_offset = peek_offset + ((uint8_t) 1);
                        } goto if__end__4; } if__else__4: ;
#line 1604 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (second_required) {
#line 1604 "bootstrap/stage0/ReCode.code"
                            {
#line 1605 "bootstrap/stage0/ReCode.code"
                                return false;
                            } goto if__end__5; } if__end__5: ;
                    } if__end__4: ;
                }
            } goto if__end__3; } if__end__3: ;
    }
#line 1608 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (third_is != NULL) {
#line 1608 "bootstrap/stage0/ReCode.code"
            {
#line 1609 "bootstrap/stage0/ReCode.code"
                return third_is(Parser__peek_token(self, peek_offset));
            } goto if__end__6; } if__end__6: ;
    }
#line 1611 "bootstrap/stage0/ReCode.code"
    return true;}

#line 1614 "bootstrap/stage0/ReCode.code"
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token*), bool first_required, bool (*second_is)(struct Token*)) {
#line 1615 "bootstrap/stage0/ReCode.code"
    return Parser__matches_three(self, first_is, first_required, second_is, true, NULL);}

#line 1618 "bootstrap/stage0/ReCode.code"
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token*)) {
#line 1619 "bootstrap/stage0/ReCode.code"
    return Parser__matches_two(self, first_is, true, NULL);}

#line 1622 "bootstrap/stage0/ReCode.code"
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token*)) {
#line 1623 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, check)) {
#line 1623 "bootstrap/stage0/ReCode.code"
            { struct Token* token;
#line 1624 "bootstrap/stage0/ReCode.code"
                token = self->scanner->current_token;
#line 1625 "bootstrap/stage0/ReCode.code"
                Scanner__next_token(self->scanner);
#line 1626 "bootstrap/stage0/ReCode.code"
                return token;
            } goto if__end__1; } if__end__1: ;
    }
#line 1628 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unexpected token"));
#line 1629 "bootstrap/stage0/ReCode.code"
    abort();}

#line 1632 "bootstrap/stage0/ReCode.code"
void Parser__consume_comment(struct Parser* self) {
#line 1633 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_comment);}

#line 1636 "bootstrap/stage0/ReCode.code"
void Parser__consume_space(struct Parser* self, uint16_t count) {
#line 1637 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_space)) {
#line 1637 "bootstrap/stage0/ReCode.code"
            { struct Space_Token* token;
#line 1638 "bootstrap/stage0/ReCode.code"
                token = ((struct Space_Token*) Parser__consume_token(self, Token__is_space));
#line 1639 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (token->count != count) {
#line 1639 "bootstrap/stage0/ReCode.code"
                        { struct String* message;
#line 1640 "bootstrap/stage0/ReCode.code"
                            message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), ((int16_t) token->count)), " spaces where "), ((int16_t) count)), " were expected");
#line 1641 "bootstrap/stage0/ReCode.code"
                            Token__warning(((struct Token*) token), message);
#line 1642 "bootstrap/stage0/ReCode.code"
                            String__delete(message);
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 1644 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (count > ((uint16_t) 0)) {
#line 1644 "bootstrap/stage0/ReCode.code"
                { struct String* message;
#line 1645 "bootstrap/stage0/ReCode.code"
                    message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), ((int16_t) 0)), " spaces where "), ((int16_t) count)), " were expected");
#line 1646 "bootstrap/stage0/ReCode.code"
                    Parser__warning(self, message);
#line 1647 "bootstrap/stage0/ReCode.code"
                    String__delete(message);
                } goto if__end__3; } if__end__3: ;
        } if__end__1: ;
    }}

#line 1651 "bootstrap/stage0/ReCode.code"
void Parser__consume_end_of_line(struct Parser* self) { struct Token* token;
#line 1652 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1652 "bootstrap/stage0/ReCode.code"
            {
#line 1653 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1654 "bootstrap/stage0/ReCode.code"
                Parser__consume_comment(self);
            } goto if__end__1; } if__else__1: ;
#line 1655 "bootstrap/stage0/ReCode.code"
        {
#line 1656 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, ((uint16_t) 0));
        } if__end__1: ;
    }
#line 1658 "bootstrap/stage0/ReCode.code"
    token = Parser__consume_token(self, Token__is_end_of_line);
#line 1659 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Token__is_end_of_file(token)) {
#line 1659 "bootstrap/stage0/ReCode.code"
            {
#line 1660 "bootstrap/stage0/ReCode.code"
                Token__warning(token, String__create_from("Unexpected end of file"));
            } goto if__end__2; } if__end__2: ;
    }}

#line 1664 "bootstrap/stage0/ReCode.code"
bool Parser__consume_empty_line(struct Parser* self) {
#line 1665 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_end_of_file)) {
#line 1665 "bootstrap/stage0/ReCode.code"
            {
#line 1666 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 1668 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 1668 "bootstrap/stage0/ReCode.code"
            {
#line 1669 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1669 "bootstrap/stage0/ReCode.code"
                        {
#line 1670 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 1671 "bootstrap/stage0/ReCode.code"
                            Parser__consume_comment(self);
                        } goto if__end__3; } if__else__3: ;
#line 1672 "bootstrap/stage0/ReCode.code"
                    {
#line 1673 "bootstrap/stage0/ReCode.code"
                        Parser__consume_space(self, ((uint16_t) 0));
                    } if__end__3: ;
                }
#line 1675 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_end_of_line);
#line 1676 "bootstrap/stage0/ReCode.code"
                return true;
            } goto if__end__2; } if__end__2: ;
    }
#line 1678 "bootstrap/stage0/ReCode.code"
    return false;}

#line 1689 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_primary_expression(struct Parser* self) {
#line 1690 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_true)) {
#line 1690 "bootstrap/stage0/ReCode.code"
            {
#line 1691 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true));
            } goto if__end__1; } if__end__1: ;
    }
#line 1693 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_null)) {
#line 1693 "bootstrap/stage0/ReCode.code"
            {
#line 1694 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null)));
            } goto if__end__2; } if__end__2: ;
    }
#line 1696 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (Parser__matches_one(self, Token__is_false)) {
#line 1696 "bootstrap/stage0/ReCode.code"
            {
#line 1697 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false));
            } goto if__end__3; } if__end__3: ;
    }
#line 1699 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (Parser__matches_one(self, Token__is_identifier)) {
#line 1699 "bootstrap/stage0/ReCode.code"
            {
#line 1700 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier)));
            } goto if__end__4; } if__end__4: ;
    }
#line 1702 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (Parser__matches_one(self, Token__is_integer)) {
#line 1702 "bootstrap/stage0/ReCode.code"
            {
#line 1703 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Integer_Expression__create(((struct Integer_Token*) Parser__consume_token(self, Token__is_integer))));
            } goto if__end__5; } if__end__5: ;
    }
#line 1705 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (Parser__matches_one(self, Token__is_character)) {
#line 1705 "bootstrap/stage0/ReCode.code"
            {
#line 1706 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Character_Expression__create(((struct Character_Token*) Parser__consume_token(self, Token__is_character))));
            } goto if__end__6; } if__end__6: ;
    }
#line 1708 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (Parser__matches_one(self, Token__is_string)) {
#line 1708 "bootstrap/stage0/ReCode.code"
            {
#line 1709 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_String_Expression__create(((struct String_Token*) Parser__consume_token(self, Token__is_string))));
            } goto if__end__7; } if__end__7: ;
    }
#line 1711 "bootstrap/stage0/ReCode.code"
    if__start__8: { if (Parser__matches_one(self, Token__is_opening_paren)) {
#line 1711 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1712 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1713 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1714 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_expression(self);
#line 1715 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1716 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 1717 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Group_Expression__create(location, expression));
            } goto if__end__8; } if__end__8: ;
    }
#line 1719 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unsupported primary expression"));
#line 1720 "bootstrap/stage0/ReCode.code"
    abort();}

#line 1725 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_access_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1726 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_primary_expression(self);
#line 1727 "bootstrap/stage0/ReCode.code"
    while (true) { struct Parsed_Expression* old_expression;
#line 1728 "bootstrap/stage0/ReCode.code"
        old_expression = expression;
#line 1729 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_dot)) {
#line 1729 "bootstrap/stage0/ReCode.code"
                {
#line 1730 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1731 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_dot);
#line 1732 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1733 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1733 "bootstrap/stage0/ReCode.code"
                            {
#line 1734 "bootstrap/stage0/ReCode.code"
                                Parser__consume_token(self, Token__is_asterisk);
#line 1735 "bootstrap/stage0/ReCode.code"
                                expression = ((struct Parsed_Expression*) Parsed_Dereference_Expression__create(expression));
                            } goto if__end__2; } if__else__2: ;
#line 1736 "bootstrap/stage0/ReCode.code"
                        { struct Token* name;
#line 1737 "bootstrap/stage0/ReCode.code"
                            name = Parser__consume_token(self, Token__is_identifier);
#line 1738 "bootstrap/stage0/ReCode.code"
                            if__start__3: { if (String__equals_cstring(name->lexeme, "as")) {
#line 1738 "bootstrap/stage0/ReCode.code"
                                    { struct Parsed_Type* type;
#line 1739 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_space(self, ((uint16_t) 0));
#line 1740 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_token(self, Token__is_opening_paren);
#line 1741 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_space(self, ((uint16_t) 0));
#line 1742 "bootstrap/stage0/ReCode.code"
                                        type = Parser__parse_type(self);
#line 1743 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_space(self, ((uint16_t) 0));
#line 1744 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_token(self, Token__is_closing_paren);
#line 1745 "bootstrap/stage0/ReCode.code"
                                        expression = ((struct Parsed_Expression*) Parsed_Cast_Expression__create(name->location, expression, type));
                                    } goto if__end__3; } if__else__3: ;
#line 1746 "bootstrap/stage0/ReCode.code"
                                {
#line 1747 "bootstrap/stage0/ReCode.code"
                                    expression = ((struct Parsed_Expression*) Parsed_Member_Access_Expression__create(expression, name));
                                } if__end__3: ;
                            }
                        } if__end__2: ;
                    }
                } goto if__end__1; } if__end__1: ;
        }
#line 1751 "bootstrap/stage0/ReCode.code"
        if__start__4: { if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
#line 1751 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Call_Expression* call_expression;
#line 1752 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1753 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_opening_paren);
#line 1754 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1755 "bootstrap/stage0/ReCode.code"
                    call_expression = Parsed_Call_Expression__create(expression);
#line 1756 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (!(Parser__matches_one(self, Token__is_closing_paren))) {
#line 1756 "bootstrap/stage0/ReCode.code"
                            { struct Parsed_Call_Argument* last_argument;
#line 1757 "bootstrap/stage0/ReCode.code"
                                last_argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1758 "bootstrap/stage0/ReCode.code"
                                call_expression->first_argument = last_argument;
#line 1759 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 0));
#line 1760 "bootstrap/stage0/ReCode.code"
                                while (Parser__matches_one(self, Token__is_comma)) { struct Parsed_Call_Argument* argument;
#line 1761 "bootstrap/stage0/ReCode.code"
                                    Parser__consume_token(self, Token__is_comma);
#line 1762 "bootstrap/stage0/ReCode.code"
                                    Parser__consume_space(self, ((uint16_t) 1));
#line 1763 "bootstrap/stage0/ReCode.code"
                                    argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1764 "bootstrap/stage0/ReCode.code"
                                    last_argument->next_argument = argument;
#line 1765 "bootstrap/stage0/ReCode.code"
                                    last_argument = argument;
#line 1766 "bootstrap/stage0/ReCode.code"
                                    Parser__consume_space(self, ((uint16_t) 0));
                                }
                            } goto if__end__5; } if__end__5: ;
                    }
#line 1769 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) call_expression);
#line 1770 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_closing_paren);
                } goto if__end__4; } if__end__4: ;
        }
#line 1772 "bootstrap/stage0/ReCode.code"
        if__start__6: { if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
#line 1772 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* index_expression;
#line 1773 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1774 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_opening_bracket);
#line 1775 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1776 "bootstrap/stage0/ReCode.code"
                    index_expression = Parser__parse_expression(self);
#line 1777 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1778 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_closing_bracket);
#line 1779 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Array_Access_Expression__create(expression, index_expression));
                } goto if__end__6; } if__end__6: ;
        }
#line 1781 "bootstrap/stage0/ReCode.code"
        if__start__7: { if (old_expression == expression) {
#line 1781 "bootstrap/stage0/ReCode.code"
                {
#line 1782 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__7; } if__end__7: ;
        }
    }
#line 1785 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1794 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_unary_expression(struct Parser* self) {
#line 1795 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_minus)) {
#line 1795 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1796 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_minus)->location;
#line 1797 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1798 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_unary_expression(self);
#line 1799 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Minus_Expression__create(location, expression));
            } goto if__end__1; } if__end__1: ;
    }
#line 1801 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_exclamation_mark)) {
#line 1801 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1802 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_exclamation_mark)->location;
#line 1803 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1804 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_unary_expression(self);
#line 1805 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Not_Expression__create(location, expression));
            } goto if__end__2; } if__end__2: ;
    }
#line 1807 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (Parser__matches_one(self, Token__is_ampersand)) {
#line 1807 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1808 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_ampersand)->location;
#line 1809 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1810 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_unary_expression(self);
#line 1811 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Address_Of_Expression__create(location, expression));
            } goto if__end__3; } if__end__3: ;
    }
#line 1813 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (Parser__matches_one(self, Token__is_sizeof)) {
#line 1813 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Type* type;
#line 1814 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_sizeof)->location;
#line 1815 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1816 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_opening_paren);
#line 1817 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1818 "bootstrap/stage0/ReCode.code"
                type = Parser__parse_type(self);
#line 1819 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1820 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 1821 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Sizeof_Expression__create(location, type));
            } goto if__end__4; } if__end__4: ;
    }
#line 1823 "bootstrap/stage0/ReCode.code"
    return Parser__parse_access_expression(self);}

#line 1826 "bootstrap/stage0/ReCode.code"
bool Token__is_mutliplication(struct Token* self) {
#line 1827 "bootstrap/stage0/ReCode.code"
    return Token__is_asterisk(self) || Token__is_slash(self) || Token__is_percent(self);}

#line 1832 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_multiplication_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1833 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_unary_expression(self);
#line 1834 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
#line 1835 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1836 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1836 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1837 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_asterisk);
#line 1838 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1839 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_unary_expression(self);
#line 1840 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Multiply_Expression__create(expression, right_expression));
                } goto if__end__1; } if__else__1: ;
#line 1841 "bootstrap/stage0/ReCode.code"
            if__start__2: { if (Parser__matches_one(self, Token__is_slash)) {
#line 1841 "bootstrap/stage0/ReCode.code"
                    { struct Parsed_Expression* right_expression;
#line 1842 "bootstrap/stage0/ReCode.code"
                        Parser__consume_token(self, Token__is_slash);
#line 1843 "bootstrap/stage0/ReCode.code"
                        Parser__consume_space(self, ((uint16_t) 1));
#line 1844 "bootstrap/stage0/ReCode.code"
                        right_expression = Parser__parse_unary_expression(self);
#line 1845 "bootstrap/stage0/ReCode.code"
                        expression = ((struct Parsed_Expression*) Parsed_Divide_Expression__create(expression, right_expression));
                    } goto if__end__2; } if__else__2: ;
#line 1846 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1847 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_percent);
#line 1848 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1849 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_unary_expression(self);
#line 1850 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Modulo_Expression__create(expression, right_expression));
                } if__end__2: ;
            } if__end__1: ;
        }
    }
#line 1853 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1856 "bootstrap/stage0/ReCode.code"
bool Token__is_addition(struct Token* self) {
#line 1857 "bootstrap/stage0/ReCode.code"
    return Token__is_plus(self) || Token__is_minus(self);}

#line 1862 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_addition_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1863 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_multiplication_expression(self);
#line 1864 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
#line 1865 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1866 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (Parser__matches_one(self, Token__is_plus)) {
#line 1866 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1867 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_plus);
#line 1868 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1869 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_multiplication_expression(self);
#line 1870 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Add_Expression__create(expression, right_expression));
                } goto if__end__1; } if__else__1: ;
#line 1871 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Expression* right_expression;
#line 1872 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_minus);
#line 1873 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1874 "bootstrap/stage0/ReCode.code"
                right_expression = Parser__parse_multiplication_expression(self);
#line 1875 "bootstrap/stage0/ReCode.code"
                expression = ((struct Parsed_Expression*) Parsed_Substract_Expression__create(expression, right_expression));
            } if__end__1: ;
        }
    }
#line 1878 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1883 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_comparison_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1884 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_addition_expression(self);
#line 1885 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
#line 1885 "bootstrap/stage0/ReCode.code"
            {
#line 1886 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1887 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_less_than);
#line 1888 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (Parser__matches_one(self, Token__is_equals)) {
#line 1888 "bootstrap/stage0/ReCode.code"
                        { struct Parsed_Expression* right_expression;
#line 1889 "bootstrap/stage0/ReCode.code"
                            Parser__consume_token(self, Token__is_equals);
#line 1890 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, ((uint16_t) 1));
#line 1891 "bootstrap/stage0/ReCode.code"
                            right_expression = Parser__parse_addition_expression(self);
#line 1892 "bootstrap/stage0/ReCode.code"
                            expression = ((struct Parsed_Expression*) Parsed_Less_Or_Equals_Expression__create(expression, right_expression));
                        } goto if__end__2; } if__else__2: ;
#line 1893 "bootstrap/stage0/ReCode.code"
                    { struct Parsed_Expression* right_expression;
#line 1894 "bootstrap/stage0/ReCode.code"
                        Parser__consume_space(self, ((uint16_t) 1));
#line 1895 "bootstrap/stage0/ReCode.code"
                        right_expression = Parser__parse_addition_expression(self);
#line 1896 "bootstrap/stage0/ReCode.code"
                        expression = ((struct Parsed_Expression*) Parsed_Less_Expression__create(expression, right_expression));
                    } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 1898 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
#line 1898 "bootstrap/stage0/ReCode.code"
                {
#line 1899 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1900 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_greater_than);
#line 1901 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (Parser__matches_one(self, Token__is_equals)) {
#line 1901 "bootstrap/stage0/ReCode.code"
                            { struct Parsed_Expression* right_expression;
#line 1902 "bootstrap/stage0/ReCode.code"
                                Parser__consume_token(self, Token__is_equals);
#line 1903 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 1));
#line 1904 "bootstrap/stage0/ReCode.code"
                                right_expression = Parser__parse_addition_expression(self);
#line 1905 "bootstrap/stage0/ReCode.code"
                                expression = ((struct Parsed_Expression*) Parsed_Greater_Or_Equals_Expression__create(expression, right_expression));
                            } goto if__end__4; } if__else__4: ;
#line 1906 "bootstrap/stage0/ReCode.code"
                        { struct Parsed_Expression* right_expression;
#line 1907 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, ((uint16_t) 1));
#line 1908 "bootstrap/stage0/ReCode.code"
                            right_expression = Parser__parse_addition_expression(self);
#line 1909 "bootstrap/stage0/ReCode.code"
                            expression = ((struct Parsed_Expression*) Parsed_Greater_Expression__create(expression, right_expression));
                        } if__end__4: ;
                    }
                } goto if__end__3; } if__end__3: ;
        } if__end__1: ;
    }
#line 1912 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1917 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_equality_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1918 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_comparison_expression(self);
#line 1919 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
#line 1919 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Expression* right_expression;
#line 1920 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1921 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_equals);
#line 1922 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_equals);
#line 1923 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1924 "bootstrap/stage0/ReCode.code"
                right_expression = Parser__parse_comparison_expression(self);
#line 1925 "bootstrap/stage0/ReCode.code"
                expression = ((struct Parsed_Expression*) Parsed_Equals_Expression__create(expression, right_expression));
            } goto if__end__1; } if__else__1: ;
#line 1926 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
#line 1926 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1927 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1928 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_exclamation_mark);
#line 1929 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_equals);
#line 1930 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1931 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_comparison_expression(self);
#line 1932 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Not_Equals_Expression__create(expression, right_expression));
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 1934 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1939 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_and_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1940 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_equality_expression(self);
#line 1941 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_ampersand, true, Token__is_ampersand)) { struct Parsed_Expression* right_expression;
#line 1942 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1943 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1944 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1945 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1946 "bootstrap/stage0/ReCode.code"
        right_expression = Parser__parse_equality_expression(self);
#line 1947 "bootstrap/stage0/ReCode.code"
        expression = ((struct Parsed_Expression*) Parsed_Logic_And_Expression__create(expression, right_expression));
    }
#line 1949 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1954 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_or_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1955 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_logic_and_expression(self);
#line 1956 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_vertical_bar, true, Token__is_vertical_bar)) { struct Parsed_Expression* right_expression;
#line 1957 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1958 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1959 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1960 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1961 "bootstrap/stage0/ReCode.code"
        right_expression = Parser__parse_logic_and_expression(self);
#line 1962 "bootstrap/stage0/ReCode.code"
        expression = ((struct Parsed_Expression*) Parsed_Logic_Or_Expression__create(expression, right_expression));
    }
#line 1964 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1969 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_expression(struct Parser* self) {
#line 1970 "bootstrap/stage0/ReCode.code"
    return Parser__parse_logic_or_expression(self);}

#line 1975 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_struct(struct Parser* self) { struct Token* name; struct Parsed_Struct_Statement* struct_statement; struct Parsed_Struct_Member* last_member;
#line 1976 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_struct);
#line 1977 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 1978 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 1979 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 1980 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 1981 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 1982 "bootstrap/stage0/ReCode.code"
    struct_statement = Parsed_Struct_Statement__create(name->location, name);
#line 1983 "bootstrap/stage0/ReCode.code"
    last_member = NULL;
#line 1984 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 1985 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 1988 "bootstrap/stage0/ReCode.code"
    while (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace))) { struct Token* name; struct Parsed_Type* type; struct Parsed_Struct_Member* member;
#line 1989 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 1990 "bootstrap/stage0/ReCode.code"
        name = Parser__consume_token(self, Token__is_identifier);
#line 1991 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 0));
#line 1992 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_colon);
#line 1993 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1994 "bootstrap/stage0/ReCode.code"
        type = Parser__parse_type(self);
#line 1995 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 1996 "bootstrap/stage0/ReCode.code"
        member = Parsed_Struct_Member__create(name, type);
#line 1997 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (last_member == NULL) {
#line 1997 "bootstrap/stage0/ReCode.code"
                {
#line 1998 "bootstrap/stage0/ReCode.code"
                    struct_statement->first_member = member;
#line 1999 "bootstrap/stage0/ReCode.code"
                    last_member = member;
                } goto if__end__1; } if__else__1: ;
#line 2000 "bootstrap/stage0/ReCode.code"
            {
#line 2001 "bootstrap/stage0/ReCode.code"
                last_member->next_member = member;
#line 2002 "bootstrap/stage0/ReCode.code"
                last_member = member;
            } if__end__1: ;
        }
#line 2004 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2008 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2009 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2010 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2011 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) struct_statement);}

#line 2016 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_opaque_type(struct Parser* self) { struct Token* name;
#line 2017 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_external);
#line 2018 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2019 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_struct);
#line 2020 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2021 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2022 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) Parsed_Opaque_Type_Statement__create(name->location, name));}

#line 2027 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_enum(struct Parser* self) { struct Token* name; struct Parsed_Enum_Statement* enum_statement; struct Parsed_Enum_Member* last_member;
#line 2028 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_enum);
#line 2029 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2030 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2031 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2032 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2033 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2034 "bootstrap/stage0/ReCode.code"
    enum_statement = Parsed_Enum_Statement__create(name->location, name);
#line 2035 "bootstrap/stage0/ReCode.code"
    last_member = NULL;
#line 2036 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 2037 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 2040 "bootstrap/stage0/ReCode.code"
    while (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace))) { struct Token* name; struct Parsed_Enum_Member* member;
#line 2041 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2042 "bootstrap/stage0/ReCode.code"
        name = Parser__consume_token(self, Token__is_identifier);
#line 2043 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2044 "bootstrap/stage0/ReCode.code"
        member = Parsed_Enum_Member__create(name);
#line 2045 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (last_member == NULL) {
#line 2045 "bootstrap/stage0/ReCode.code"
                {
#line 2046 "bootstrap/stage0/ReCode.code"
                    enum_statement->first_member = member;
#line 2047 "bootstrap/stage0/ReCode.code"
                    last_member = member;
                } goto if__end__1; } if__else__1: ;
#line 2048 "bootstrap/stage0/ReCode.code"
            {
#line 2049 "bootstrap/stage0/ReCode.code"
                last_member->next_member = member;
#line 2050 "bootstrap/stage0/ReCode.code"
                last_member = member;
            } if__end__1: ;
        }
#line 2052 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2056 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2057 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2058 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2059 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) enum_statement);}

#line 2065 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parser__parse_type(struct Parser* self) {
#line 2066 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_three(self, Token__is_opening_paren, true, Token__is_space, false, Token__is_func)) {
#line 2066 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Function_Parameter* first_parameter; struct Parsed_Type* return_type;
#line 2067 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 2068 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2069 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_func);
#line 2070 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2071 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_opening_paren);
#line 2072 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2073 "bootstrap/stage0/ReCode.code"
                first_parameter = NULL;
#line 2074 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (!(Parser__matches_one(self, Token__is_closing_paren))) {
#line 2074 "bootstrap/stage0/ReCode.code"
                        { struct Parsed_Type* type; struct Parsed_Function_Parameter* last_parameter;
#line 2075 "bootstrap/stage0/ReCode.code"
                            type = Parser__parse_type(self);
#line 2076 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, ((uint16_t) 0));
#line 2077 "bootstrap/stage0/ReCode.code"
                            first_parameter = Parsed_Function_Parameter__create(type->location, NULL, type);
#line 2078 "bootstrap/stage0/ReCode.code"
                            last_parameter = first_parameter;
#line 2079 "bootstrap/stage0/ReCode.code"
                            while (!(Parser__matches_one(self, Token__is_closing_paren))) { struct Parsed_Type* type;
#line 2080 "bootstrap/stage0/ReCode.code"
                                Parser__consume_token(self, Token__is_comma);
#line 2081 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 1));
#line 2082 "bootstrap/stage0/ReCode.code"
                                type = Parser__parse_type(self);
#line 2083 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 0));
#line 2084 "bootstrap/stage0/ReCode.code"
                                last_parameter->next_parameter = Parsed_Function_Parameter__create(type->location, NULL, type);
#line 2085 "bootstrap/stage0/ReCode.code"
                                last_parameter = last_parameter->next_parameter;
                            }
                        } goto if__end__2; } if__end__2: ;
                }
#line 2088 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 2089 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2090 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_minus);
#line 2091 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2092 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_greater_than);
#line 2093 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2094 "bootstrap/stage0/ReCode.code"
                return_type = Parser__parse_type(self);
#line 2095 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2096 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 2097 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Type*) Parsed_Function_Type__create(location, first_parameter, return_type));
            } goto if__end__1; } if__else__1: ;
#line 2098 "bootstrap/stage0/ReCode.code"
        { struct Token* name; struct Parsed_Type* type;
#line 2099 "bootstrap/stage0/ReCode.code"
            name = Parser__consume_token(self, Token__is_identifier);
#line 2100 "bootstrap/stage0/ReCode.code"
            type = ((struct Parsed_Type*) Parsed_Named_Type__create(name));
#line 2101 "bootstrap/stage0/ReCode.code"
            while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
#line 2102 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2103 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_asterisk);
#line 2104 "bootstrap/stage0/ReCode.code"
                type = ((struct Parsed_Type*) Parsed_Pointer_Type__create(type));
            }
#line 2106 "bootstrap/stage0/ReCode.code"
            return type;
        } if__end__1: ;
    }}

#line 2112 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_variable(struct Parser* self) { struct Token* name; struct Parsed_Type* type; bool is_external; struct Parsed_Expression* value_expression; struct Parsed_Variable_Statement* variable_statement;
#line 2113 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_let);
#line 2114 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2115 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2116 "bootstrap/stage0/ReCode.code"
    type = NULL;
#line 2117 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_colon)) {
#line 2117 "bootstrap/stage0/ReCode.code"
            {
#line 2118 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2119 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_colon);
#line 2120 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2121 "bootstrap/stage0/ReCode.code"
                type = Parser__parse_type(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 2123 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2124 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_equals);
#line 2125 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2127 "bootstrap/stage0/ReCode.code"
    ;
#line 2128 "bootstrap/stage0/ReCode.code"
    ;
#line 2129 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_external)) {
#line 2129 "bootstrap/stage0/ReCode.code"
            {
#line 2130 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_external);
#line 2131 "bootstrap/stage0/ReCode.code"
                value_expression = NULL;
#line 2132 "bootstrap/stage0/ReCode.code"
                is_external = true;
            } goto if__end__2; } if__else__2: ;
#line 2133 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (Parser__matches_one(self, Token__is_undefined)) {
#line 2133 "bootstrap/stage0/ReCode.code"
                {
#line 2134 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_undefined);
#line 2135 "bootstrap/stage0/ReCode.code"
                    value_expression = NULL;
#line 2136 "bootstrap/stage0/ReCode.code"
                    is_external = false;
                } goto if__end__3; } if__else__3: ;
#line 2137 "bootstrap/stage0/ReCode.code"
            {
#line 2138 "bootstrap/stage0/ReCode.code"
                value_expression = Parser__parse_expression(self);
#line 2139 "bootstrap/stage0/ReCode.code"
                is_external = false;
            } if__end__3: ;
        } if__end__2: ;
    }
#line 2141 "bootstrap/stage0/ReCode.code"
    variable_statement = Parsed_Variable_Statement__create(name->location, name, type, is_external);
#line 2142 "bootstrap/stage0/ReCode.code"
    variable_statement->expression = value_expression;
#line 2143 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) variable_statement);}

#line 2148 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Statements* statements;
#line 2149 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_opening_brace)->location;
#line 2150 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2151 "bootstrap/stage0/ReCode.code"
    statements = Parsed_Statements__create(false);
#line 2152 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 2153 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2154 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2155 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2156 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2157 "bootstrap/stage0/ReCode.code"
    return Parsed_Block_Statement__create(location, statements);}

#line 2162 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self) { struct Token* name; struct Parsed_Type* type;
#line 2163 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2164 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2165 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_colon);
#line 2166 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2167 "bootstrap/stage0/ReCode.code"
    type = Parser__parse_type(self);
#line 2168 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Parameter__create(name->location, name->lexeme, type);}

#line 2173 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_function(struct Parser* self) { struct Token* name; struct Parsed_Function_Parameter* first_parameter; struct Parsed_Type* return_type; struct Parsed_Statements* statements;
#line 2174 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2175 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2176 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2177 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2178 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2179 "bootstrap/stage0/ReCode.code"
    first_parameter = NULL;
#line 2180 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren))) {
#line 2180 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Function_Parameter* last_parameter;
#line 2181 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2182 "bootstrap/stage0/ReCode.code"
                first_parameter = Parser__parse_function_parameter(self);
#line 2183 "bootstrap/stage0/ReCode.code"
                last_parameter = first_parameter;
#line 2184 "bootstrap/stage0/ReCode.code"
                while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2185 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 2186 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_comma);
#line 2187 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 2188 "bootstrap/stage0/ReCode.code"
                    last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2189 "bootstrap/stage0/ReCode.code"
                    last_parameter = last_parameter->next_parameter;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 2192 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2193 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2194 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2195 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2196 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2197 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2198 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2199 "bootstrap/stage0/ReCode.code"
    return_type = Parser__parse_type(self);
#line 2200 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2201 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2202 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2203 "bootstrap/stage0/ReCode.code"
    statements = Parsed_Statements__create(false);
#line 2204 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 2205 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2206 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2207 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2208 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2209 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, statements, false);}

#line 2214 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_external_function(struct Parser* self) { struct Token* name; struct Parsed_Function_Parameter* first_parameter; struct Parsed_Type* return_type;
#line 2215 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_external);
#line 2216 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2217 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2218 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2219 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2220 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2221 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2222 "bootstrap/stage0/ReCode.code"
    first_parameter = NULL;
#line 2223 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren))) {
#line 2223 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Function_Parameter* last_parameter;
#line 2224 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2225 "bootstrap/stage0/ReCode.code"
                first_parameter = Parser__parse_function_parameter(self);
#line 2226 "bootstrap/stage0/ReCode.code"
                last_parameter = first_parameter;
#line 2227 "bootstrap/stage0/ReCode.code"
                while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2228 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 2229 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_comma);
#line 2230 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 2231 "bootstrap/stage0/ReCode.code"
                    last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2232 "bootstrap/stage0/ReCode.code"
                    last_parameter = last_parameter->next_parameter;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 2235 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2236 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2237 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2238 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2239 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2240 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2241 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2242 "bootstrap/stage0/ReCode.code"
    return_type = Parser__parse_type(self);
#line 2243 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, NULL, true);}

#line 2248 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_return_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Expression* expression;
#line 2249 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_return)->location;
#line 2250 "bootstrap/stage0/ReCode.code"
    expression = NULL;
#line 2251 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line))) {
#line 2251 "bootstrap/stage0/ReCode.code"
            {
#line 2252 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2253 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_expression(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 2255 "bootstrap/stage0/ReCode.code"
    return Parsed_Return_Statement__create(location, expression);}

#line 2260 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_break_statement(struct Parser* self) { struct Source_Location* location;
#line 2261 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_break)->location;
#line 2262 "bootstrap/stage0/ReCode.code"
    return Parsed_Break_Statement__create(location);}

#line 2267 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_if_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Expression* condition_expression; struct Parsed_Statement* true_statement; struct Parsed_Statement* false_statement;
#line 2268 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_if)->location;
#line 2269 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2270 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2271 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2272 "bootstrap/stage0/ReCode.code"
    condition_expression = Parser__parse_expression(self);
#line 2273 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2274 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2275 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2276 "bootstrap/stage0/ReCode.code"
    true_statement = ((struct Parsed_Statement*) Parser__parse_block_statement(self));
#line 2277 "bootstrap/stage0/ReCode.code"
    false_statement = NULL;
#line 2278 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
#line 2278 "bootstrap/stage0/ReCode.code"
            {
#line 2279 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2280 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_else);
#line 2281 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2282 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (Parser__matches_one(self, Token__is_if)) {
#line 2282 "bootstrap/stage0/ReCode.code"
                        {
#line 2283 "bootstrap/stage0/ReCode.code"
                            false_statement = Parser__parse_if_statement(self);
                        } goto if__end__2; } if__else__2: ;
#line 2284 "bootstrap/stage0/ReCode.code"
                    {
#line 2285 "bootstrap/stage0/ReCode.code"
                        false_statement = ((struct Parsed_Statement*) Parser__parse_block_statement(self));
                    } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 2288 "bootstrap/stage0/ReCode.code"
    return Parsed_If_Statement__create(location, condition_expression, true_statement, false_statement);}

#line 2293 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_while_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Expression* condition_expression; struct Parsed_Statement* body_statement;
#line 2294 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_while)->location;
#line 2295 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2296 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2297 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2298 "bootstrap/stage0/ReCode.code"
    condition_expression = Parser__parse_expression(self);
#line 2299 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2300 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2301 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2302 "bootstrap/stage0/ReCode.code"
    body_statement = ((struct Parsed_Statement*) Parser__parse_block_statement(self));
#line 2303 "bootstrap/stage0/ReCode.code"
    return Parsed_While_Statement__create(location, condition_expression, body_statement);}

#line 2315 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_statement(struct Parser* self) { struct Parsed_Expression* expression;
#line 2316 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2318 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_if)) {
#line 2318 "bootstrap/stage0/ReCode.code"
            {
#line 2319 "bootstrap/stage0/ReCode.code"
                return Parser__parse_if_statement(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 2322 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_while)) {
#line 2322 "bootstrap/stage0/ReCode.code"
            {
#line 2323 "bootstrap/stage0/ReCode.code"
                return Parser__parse_while_statement(self);
            } goto if__end__2; } if__end__2: ;
    }
#line 2326 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (Parser__matches_one(self, Token__is_return)) {
#line 2326 "bootstrap/stage0/ReCode.code"
            {
#line 2327 "bootstrap/stage0/ReCode.code"
                return Parser__parse_return_statement(self);
            } goto if__end__3; } if__end__3: ;
    }
#line 2330 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (Parser__matches_one(self, Token__is_break)) {
#line 2330 "bootstrap/stage0/ReCode.code"
            {
#line 2331 "bootstrap/stage0/ReCode.code"
                return Parser__parse_break_statement(self);
            } goto if__end__4; } if__end__4: ;
    }
#line 2334 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (Parser__matches_one(self, Token__is_let)) {
#line 2334 "bootstrap/stage0/ReCode.code"
            {
#line 2335 "bootstrap/stage0/ReCode.code"
                return Parser__parse_variable(self);
            } goto if__end__5; } if__end__5: ;
    }
#line 2338 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (Parser__matches_three(self, Token__is_external, true, Token__is_space, true, Token__is_func)) {
#line 2338 "bootstrap/stage0/ReCode.code"
            {
#line 2339 "bootstrap/stage0/ReCode.code"
                return Parser__parse_external_function(self);
            } goto if__end__6; } if__end__6: ;
    }
#line 2342 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (Parser__matches_one(self, Token__is_func)) {
#line 2342 "bootstrap/stage0/ReCode.code"
            {
#line 2343 "bootstrap/stage0/ReCode.code"
                return Parser__parse_function(self);
            } goto if__end__7; } if__end__7: ;
    }
#line 2346 "bootstrap/stage0/ReCode.code"
    if__start__8: { if (Parser__matches_three(self, Token__is_external, true, Token__is_space, true, Token__is_struct)) {
#line 2346 "bootstrap/stage0/ReCode.code"
            {
#line 2347 "bootstrap/stage0/ReCode.code"
                return Parser__parse_opaque_type(self);
            } goto if__end__8; } if__end__8: ;
    }
#line 2350 "bootstrap/stage0/ReCode.code"
    if__start__9: { if (Parser__matches_one(self, Token__is_struct)) {
#line 2350 "bootstrap/stage0/ReCode.code"
            {
#line 2351 "bootstrap/stage0/ReCode.code"
                return Parser__parse_struct(self);
            } goto if__end__9; } if__end__9: ;
    }
#line 2354 "bootstrap/stage0/ReCode.code"
    if__start__10: { if (Parser__matches_one(self, Token__is_enum)) {
#line 2354 "bootstrap/stage0/ReCode.code"
            {
#line 2355 "bootstrap/stage0/ReCode.code"
                return Parser__parse_enum(self);
            } goto if__end__10; } if__end__10: ;
    }
#line 2358 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_access_expression(self);
#line 2359 "bootstrap/stage0/ReCode.code"
    if__start__11: { if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2359 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Expression* value_expression;
#line 2360 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2361 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_equals);
#line 2362 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2363 "bootstrap/stage0/ReCode.code"
                value_expression = Parser__parse_expression(self);
#line 2364 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Statement*) Parsed_Assignment_Statement__create(expression, value_expression));
            } goto if__end__11; } if__end__11: ;
    }
#line 2366 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) Parsed_Expression_Statement__create(expression));}

#line 2371 "bootstrap/stage0/ReCode.code"
void Parser__parse_statements(struct Parser* self, struct Parsed_Statements* statements) {
#line 2372 "bootstrap/stage0/ReCode.code"
    while (true) { struct Parsed_Statement* statement;
#line 2373 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
#line 2377 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (statements->has_globals) {
#line 2377 "bootstrap/stage0/ReCode.code"
                {
#line 2378 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 2378 "bootstrap/stage0/ReCode.code"
                            {
#line 2379 "bootstrap/stage0/ReCode.code"
                                return;
                            } goto if__end__2; } if__end__2: ;
                    }
                } goto if__end__1; } if__else__1: ;
#line 2381 "bootstrap/stage0/ReCode.code"
            {
#line 2382 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2382 "bootstrap/stage0/ReCode.code"
                        {
#line 2383 "bootstrap/stage0/ReCode.code"
                            return;
                        } goto if__end__3; } if__end__3: ;
                }
            } if__end__1: ;
        }
#line 2387 "bootstrap/stage0/ReCode.code"
        statement = Parser__parse_statement(self);
#line 2389 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2391 "bootstrap/stage0/ReCode.code"
        Parsed_Statements__append(statements, statement);
    }}

#line 2395 "bootstrap/stage0/ReCode.code"
void Parser__parse_source(struct Parser* self, struct Source* source) { struct Scanner* other_scanner; struct Token* last_token;
#line 2396 "bootstrap/stage0/ReCode.code"
    other_scanner = self->scanner;
#line 2398 "bootstrap/stage0/ReCode.code"
    self->scanner = Scanner__create(source);
#line 2400 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, self->compilation_unit->statements);
#line 2402 "bootstrap/stage0/ReCode.code"
    last_token = Parser__peek_token(self, ((uint8_t) 0));
#line 2403 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Token__is_end_of_file(last_token))) {
#line 2403 "bootstrap/stage0/ReCode.code"
            {
#line 2404 "bootstrap/stage0/ReCode.code"
                Parser__error(self, String__create_from("Scanner didn\'t reach end of file"));
#line 2405 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__else__1: ;
#line 2406 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (last_token->location->column != ((uint16_t) 1)) {
#line 2406 "bootstrap/stage0/ReCode.code"
                {
#line 2407 "bootstrap/stage0/ReCode.code"
                    Parser__warning(self, String__create_from("No new line at the end of file"));
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 2410 "bootstrap/stage0/ReCode.code"
    self->scanner = other_scanner;}

#line 2413 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* parse(struct Source* source) { struct Parser parser;
#line 2414 "bootstrap/stage0/ReCode.code"
    ;
#line 2415 "bootstrap/stage0/ReCode.code"
    parser.scanner = NULL;
#line 2416 "bootstrap/stage0/ReCode.code"
    parser.compilation_unit = Parsed_Compilation_Unit__create();
#line 2417 "bootstrap/stage0/ReCode.code"
    parser.current_identation = ((uint16_t) 0);
#line 2419 "bootstrap/stage0/ReCode.code"
    Parser__parse_source(&parser, source);
#line 2421 "bootstrap/stage0/ReCode.code"
    return parser.compilation_unit;}

#line 2459 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checked_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location) { struct Checked_Type* type;
#line 2460 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Type*) malloc(kind_size));
#line 2461 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 2462 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 2463 "bootstrap/stage0/ReCode.code"
    type->next_type = NULL;
#line 2464 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2467 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_same_type(struct Checked_Type* self, struct Checked_Type* other_type, struct Source_Location* location) {
#line 2468 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->kind == Checked_Type_Kind__POINTER) { if (other_type->kind == Checked_Type_Kind__NULL) {
#line 2468 "bootstrap/stage0/ReCode.code"
                {
#line 2469 "bootstrap/stage0/ReCode.code"
                    return;
                } goto if__end__1; } } if__end__1: ;
    }
#line 2471 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->kind == Checked_Type_Kind__FUNCTION) { if (other_type->kind == Checked_Type_Kind__NULL) {
#line 2471 "bootstrap/stage0/ReCode.code"
                {
#line 2472 "bootstrap/stage0/ReCode.code"
                    return;
                } goto if__end__2; } } if__end__2: ;
    }
#line 2474 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (!(Checked_Type__equals(self, other_type))) {
#line 2474 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 2475 "bootstrap/stage0/ReCode.code"
                message = String__create_from("Unexpected type. Got \"");
#line 2476 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, other_type);
#line 2477 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" instead of \"");
#line 2478 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, self);
#line 2479 "bootstrap/stage0/ReCode.code"
                String__append_char(message, '\"');
#line 2480 "bootstrap/stage0/ReCode.code"
                Source_Location__error(location, message);
#line 2481 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__3; } if__end__3: ;
    }}

#line 2485 "bootstrap/stage0/ReCode.code"
bool Checked_Type__is_scalar_type(struct Checked_Type* self) {
#line 2486 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->kind == Checked_Type_Kind__CHAR) {
#line 2486 "bootstrap/stage0/ReCode.code"
            {
#line 2487 "bootstrap/stage0/ReCode.code"
                return true;
            } goto if__end__1; } if__else__1: ;
#line 2488 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (self->kind == Checked_Type_Kind__I16) {
#line 2488 "bootstrap/stage0/ReCode.code"
                {
#line 2489 "bootstrap/stage0/ReCode.code"
                    return true;
                } goto if__end__2; } if__else__2: ;
#line 2490 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (self->kind == Checked_Type_Kind__I32) {
#line 2490 "bootstrap/stage0/ReCode.code"
                    {
#line 2491 "bootstrap/stage0/ReCode.code"
                        return true;
                    } goto if__end__3; } if__else__3: ;
#line 2492 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (self->kind == Checked_Type_Kind__I64) {
#line 2492 "bootstrap/stage0/ReCode.code"
                        {
#line 2493 "bootstrap/stage0/ReCode.code"
                            return true;
                        } goto if__end__4; } if__else__4: ;
#line 2494 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (self->kind == Checked_Type_Kind__I8) {
#line 2494 "bootstrap/stage0/ReCode.code"
                            {
#line 2495 "bootstrap/stage0/ReCode.code"
                                return true;
                            } goto if__end__5; } if__else__5: ;
#line 2496 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (self->kind == Checked_Type_Kind__U16) {
#line 2496 "bootstrap/stage0/ReCode.code"
                                {
#line 2497 "bootstrap/stage0/ReCode.code"
                                    return true;
                                } goto if__end__6; } if__else__6: ;
#line 2498 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (self->kind == Checked_Type_Kind__U32) {
#line 2498 "bootstrap/stage0/ReCode.code"
                                    {
#line 2499 "bootstrap/stage0/ReCode.code"
                                        return true;
                                    } goto if__end__7; } if__else__7: ;
#line 2500 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (self->kind == Checked_Type_Kind__U64) {
#line 2500 "bootstrap/stage0/ReCode.code"
                                        {
#line 2501 "bootstrap/stage0/ReCode.code"
                                            return true;
                                        } goto if__end__8; } if__else__8: ;
#line 2502 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (self->kind == Checked_Type_Kind__U8) {
#line 2502 "bootstrap/stage0/ReCode.code"
                                            {
#line 2503 "bootstrap/stage0/ReCode.code"
                                                return true;
                                            } goto if__end__9; } if__else__9: ;
#line 2504 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (self->kind == Checked_Type_Kind__USIZE) {
#line 2504 "bootstrap/stage0/ReCode.code"
                                                {
#line 2505 "bootstrap/stage0/ReCode.code"
                                                    return true;
                                                } goto if__end__10; } if__else__10: ;
#line 2506 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (self->kind == Checked_Type_Kind__ENUM) {
#line 2506 "bootstrap/stage0/ReCode.code"
                                                    {
#line 2507 "bootstrap/stage0/ReCode.code"
                                                        return true;
                                                    } goto if__end__11; } if__end__11: ;
                                            } if__end__10: ;
                                        } if__end__9: ;
                                    } if__end__8: ;
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }
#line 2509 "bootstrap/stage0/ReCode.code"
    return false;}

#line 2512 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_scalar_type(struct Checked_Type* self, struct Source_Location* location) {
#line 2513 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Checked_Type__is_scalar_type(self))) {
#line 2513 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 2514 "bootstrap/stage0/ReCode.code"
                message = String__create_from("Type \"");
#line 2515 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, self);
#line 2516 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" is not a scalar type");
#line 2517 "bootstrap/stage0/ReCode.code"
                Source_Location__error(location, message);
#line 2518 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }}

#line 2527 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checked_Named_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name) { struct Checked_Named_Type* type;
#line 2528 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Named_Type*) Checked_Type__create_kind(kind, kind_size, location));
#line 2529 "bootstrap/stage0/ReCode.code"
    type->name = name;
#line 2530 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2540 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Member__create(struct Source_Location* location, struct String* name) { struct Checked_Enum_Member* member;
#line 2541 "bootstrap/stage0/ReCode.code"
    member = ((struct Checked_Enum_Member*) malloc(sizeof(struct Checked_Enum_Member)));
#line 2542 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2543 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2544 "bootstrap/stage0/ReCode.code"
    member->symbol = NULL;
#line 2545 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2546 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2554 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Type* Checked_Enum_Type__create(struct Source_Location* location, struct String* name) { struct Checked_Enum_Type* type;
#line 2555 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Enum_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__ENUM, sizeof(struct Checked_Enum_Type), location, name));
#line 2556 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2557 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2560 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Type__find_member(struct Checked_Enum_Type* self, struct String* name) { struct Checked_Enum_Member* member;
#line 2561 "bootstrap/stage0/ReCode.code"
    member = self->first_member;
#line 2562 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2563 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, member->name)) {
#line 2563 "bootstrap/stage0/ReCode.code"
                {
#line 2564 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 2566 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2568 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2578 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter* Checked_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) { struct Checked_Function_Parameter* parameter;
#line 2579 "bootstrap/stage0/ReCode.code"
    parameter = ((struct Checked_Function_Parameter*) malloc(sizeof(struct Checked_Function_Parameter)));
#line 2580 "bootstrap/stage0/ReCode.code"
    parameter->location = location;
#line 2581 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 2582 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 2583 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 2584 "bootstrap/stage0/ReCode.code"
    return parameter;}

#line 2593 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct Checked_Function_Parameter* first_parameter, struct Checked_Type* return_type) { struct Checked_Function_Type* type;
#line 2594 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Function_Type*) Checked_Type__create_kind(Checked_Type_Kind__FUNCTION, sizeof(struct Checked_Function_Type), location));
#line 2595 "bootstrap/stage0/ReCode.code"
    type->first_parameter = first_parameter;
#line 2596 "bootstrap/stage0/ReCode.code"
    type->return_type = return_type;
#line 2597 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2600 "bootstrap/stage0/ReCode.code"
bool Checked_Function_Type__equals(struct Checked_Function_Type* self, struct Checked_Type* other_type) { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* self_parameter; struct Checked_Function_Parameter* function_parameter;
#line 2601 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type->kind != self->super.kind) {
#line 2601 "bootstrap/stage0/ReCode.code"
            {
#line 2602 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 2604 "bootstrap/stage0/ReCode.code"
    function_type = ((struct Checked_Function_Type*) other_type);
#line 2605 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (!(Checked_Type__equals(self->return_type, function_type->return_type))) {
#line 2605 "bootstrap/stage0/ReCode.code"
            {
#line 2606 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__2; } if__end__2: ;
    }
#line 2608 "bootstrap/stage0/ReCode.code"
    self_parameter = self->first_parameter;
#line 2609 "bootstrap/stage0/ReCode.code"
    function_parameter = function_type->first_parameter;
#line 2610 "bootstrap/stage0/ReCode.code"
    while (self_parameter != NULL && function_parameter != NULL) {
#line 2611 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (!(Checked_Type__equals(self_parameter->type, function_parameter->type))) {
#line 2611 "bootstrap/stage0/ReCode.code"
                {
#line 2612 "bootstrap/stage0/ReCode.code"
                    return false;
                } goto if__end__3; } if__end__3: ;
        }
#line 2614 "bootstrap/stage0/ReCode.code"
        self_parameter = self_parameter->next_parameter;
#line 2615 "bootstrap/stage0/ReCode.code"
        function_parameter = function_parameter->next_parameter;
    }
#line 2617 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (!(self_parameter != NULL)) { if (!(function_parameter != NULL)) { goto if__end__4; } } if__then__4__5: {
#line 2617 "bootstrap/stage0/ReCode.code"
            {
#line 2618 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__4; } if__end__4: ;
    }
#line 2620 "bootstrap/stage0/ReCode.code"
    return true;}

#line 2627 "bootstrap/stage0/ReCode.code"
struct Checked_Opaque_Type* Checked_Opaque_Type__create(struct Source_Location* location, struct String* name) {
#line 2628 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Opaque_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__OPAQUE, sizeof(struct Checked_Opaque_Type), location, name));}

#line 2636 "bootstrap/stage0/ReCode.code"
struct Checked_Pointer_Type* Checked_Pointer_Type__create(struct Source_Location* location, struct Checked_Type* other_type) { struct Checked_Pointer_Type* type;
#line 2637 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Pointer_Type*) Checked_Type__create_kind(Checked_Type_Kind__POINTER, sizeof(struct Checked_Pointer_Type), location));
#line 2638 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 2639 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2642 "bootstrap/stage0/ReCode.code"
bool Checked_Pointer_Type__equals(struct Checked_Pointer_Type* self, struct Checked_Type* other_type) {
#line 2643 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type->kind != self->super.kind) {
#line 2643 "bootstrap/stage0/ReCode.code"
            {
#line 2644 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 2646 "bootstrap/stage0/ReCode.code"
    return Checked_Type__equals(self->other_type, ((struct Checked_Pointer_Type*) other_type)->other_type);}

#line 2654 "bootstrap/stage0/ReCode.code"
struct Checked_Defined_Type* Checked_Defined_Type__create(struct Checked_Named_Type* defined_type) { struct Checked_Defined_Type* type;
#line 2655 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Defined_Type*) Checked_Type__create_kind(Checked_Type_Kind__DEFINED, sizeof(struct Checked_Defined_Type), defined_type->super.location));
#line 2656 "bootstrap/stage0/ReCode.code"
    type->defined_type = defined_type;
#line 2657 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2667 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Member__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) { struct Checked_Struct_Member* member;
#line 2668 "bootstrap/stage0/ReCode.code"
    member = ((struct Checked_Struct_Member*) malloc(sizeof(struct Checked_Struct_Member)));
#line 2669 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2670 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2671 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 2672 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2673 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2682 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Type* Checked_Struct_Type__create(struct Source_Location* location, struct String* name) { struct Checked_Struct_Type* type;
#line 2683 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Struct_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__STRUCT, sizeof(struct Checked_Struct_Type), location, name));
#line 2684 "bootstrap/stage0/ReCode.code"
    type->super_type = NULL;
#line 2685 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2686 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2689 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Type__find_member(struct Checked_Struct_Type* self, struct String* name) { struct Checked_Struct_Member* member;
#line 2690 "bootstrap/stage0/ReCode.code"
    member = self->first_member;
#line 2691 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2692 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, member->name)) {
#line 2692 "bootstrap/stage0/ReCode.code"
                {
#line 2693 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 2695 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2697 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2700 "bootstrap/stage0/ReCode.code"
bool Checked_Struct_Type__equals(struct Checked_Struct_Type* self, struct Checked_Type* other_type) {
#line 2701 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->super.super.kind != other_type->kind) {
#line 2701 "bootstrap/stage0/ReCode.code"
            {
#line 2702 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 2704 "bootstrap/stage0/ReCode.code"
    return String__equals_string(self->super.name, ((struct Checked_Struct_Type*) other_type)->super.name);}

#line 2707 "bootstrap/stage0/ReCode.code"
bool Checked_Type__equals(struct Checked_Type* self, struct Checked_Type* other_type) {
#line 2708 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self == other_type) {
#line 2708 "bootstrap/stage0/ReCode.code"
            {
#line 2709 "bootstrap/stage0/ReCode.code"
                return true;
            } goto if__end__1; } if__end__1: ;
    }
#line 2711 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->kind != other_type->kind) {
#line 2711 "bootstrap/stage0/ReCode.code"
            {
#line 2712 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__2; } if__end__2: ;
    }
#line 2714 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (self->kind == Checked_Type_Kind__FUNCTION) {
#line 2714 "bootstrap/stage0/ReCode.code"
            {
#line 2715 "bootstrap/stage0/ReCode.code"
                return Checked_Function_Type__equals(((struct Checked_Function_Type*) self), other_type);
            } goto if__end__3; } if__end__3: ;
    }
#line 2717 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (self->kind == Checked_Type_Kind__POINTER) {
#line 2717 "bootstrap/stage0/ReCode.code"
            {
#line 2718 "bootstrap/stage0/ReCode.code"
                return Checked_Pointer_Type__equals(((struct Checked_Pointer_Type*) self), other_type);
            } goto if__end__4; } if__end__4: ;
    }
#line 2720 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (self->kind == Checked_Type_Kind__STRUCT) {
#line 2720 "bootstrap/stage0/ReCode.code"
            {
#line 2721 "bootstrap/stage0/ReCode.code"
                return Checked_Struct_Type__equals(((struct Checked_Struct_Type*) self), other_type);
            } goto if__end__5; } if__end__5: ;
    }
#line 2723 "bootstrap/stage0/ReCode.code"
    Source_Location__error(self->location, String__create_from("Unsupported type"));
#line 2724 "bootstrap/stage0/ReCode.code"
    abort();}

#line 2727 "bootstrap/stage0/ReCode.code"
struct String* String__append_checked_type(struct String* self, struct Checked_Type* type) {
#line 2728 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (type->kind <= Checked_Type_Kind__NULL) {
#line 2728 "bootstrap/stage0/ReCode.code"
            { struct Checked_Named_Type* named_type;
#line 2729 "bootstrap/stage0/ReCode.code"
                named_type = ((struct Checked_Named_Type*) type);
#line 2730 "bootstrap/stage0/ReCode.code"
                String__append_string(self, named_type->name);
            } goto if__end__1; } if__else__1: ;
#line 2731 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2731 "bootstrap/stage0/ReCode.code"
                { struct Checked_Struct_Type* struct_type;
#line 2732 "bootstrap/stage0/ReCode.code"
                    struct_type = ((struct Checked_Struct_Type*) type);
#line 2733 "bootstrap/stage0/ReCode.code"
                    String__append_cstring(self, "struct ");
#line 2734 "bootstrap/stage0/ReCode.code"
                    String__append_string(self, struct_type->super.name);
                } goto if__end__2; } if__else__2: ;
#line 2735 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (type->kind == Checked_Type_Kind__FUNCTION) {
#line 2735 "bootstrap/stage0/ReCode.code"
                    { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* function_parameter;
#line 2736 "bootstrap/stage0/ReCode.code"
                        function_type = ((struct Checked_Function_Type*) type);
#line 2737 "bootstrap/stage0/ReCode.code"
                        String__append_cstring(self, "(func (");
#line 2738 "bootstrap/stage0/ReCode.code"
                        function_parameter = function_type->first_parameter;
#line 2739 "bootstrap/stage0/ReCode.code"
                        while (function_parameter != NULL) {
#line 2740 "bootstrap/stage0/ReCode.code"
                            String__append_checked_type(self, function_parameter->type);
#line 2741 "bootstrap/stage0/ReCode.code"
                            function_parameter = function_parameter->next_parameter;
#line 2742 "bootstrap/stage0/ReCode.code"
                            if__start__4: { if (function_parameter != NULL) {
#line 2742 "bootstrap/stage0/ReCode.code"
                                    {
#line 2743 "bootstrap/stage0/ReCode.code"
                                        String__append_cstring(self, ", ");
                                    } goto if__end__4; } if__end__4: ;
                            }
                        }
#line 2746 "bootstrap/stage0/ReCode.code"
                        String__append_cstring(self, ") -> ");
#line 2747 "bootstrap/stage0/ReCode.code"
                        String__append_checked_type(self, function_type->return_type);
#line 2748 "bootstrap/stage0/ReCode.code"
                        String__append_char(self, ')');
                    } goto if__end__3; } if__else__3: ;
#line 2749 "bootstrap/stage0/ReCode.code"
                if__start__5: { if (type->kind == Checked_Type_Kind__ENUM) {
#line 2749 "bootstrap/stage0/ReCode.code"
                        { struct Checked_Enum_Type* enum_type;
#line 2750 "bootstrap/stage0/ReCode.code"
                            enum_type = ((struct Checked_Enum_Type*) type);
#line 2751 "bootstrap/stage0/ReCode.code"
                            String__append_cstring(self, "enum ");
#line 2752 "bootstrap/stage0/ReCode.code"
                            String__append_string(self, enum_type->super.name);
                        } goto if__end__5; } if__else__5: ;
#line 2753 "bootstrap/stage0/ReCode.code"
                    if__start__6: { if (type->kind == Checked_Type_Kind__POINTER) {
#line 2753 "bootstrap/stage0/ReCode.code"
                            { struct Checked_Pointer_Type* pointer_type;
#line 2754 "bootstrap/stage0/ReCode.code"
                                pointer_type = ((struct Checked_Pointer_Type*) type);
#line 2755 "bootstrap/stage0/ReCode.code"
                                String__append_checked_type(self, pointer_type->other_type);
#line 2756 "bootstrap/stage0/ReCode.code"
                                String__append_char(self, '*');
                            } goto if__end__6; } if__else__6: ;
#line 2757 "bootstrap/stage0/ReCode.code"
                        {
#line 2758 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2759 "bootstrap/stage0/ReCode.code"
                            abort();
                        } if__end__6: ;
                    } if__end__5: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }
#line 2761 "bootstrap/stage0/ReCode.code"
    return self;}

#line 2764 "bootstrap/stage0/ReCode.code"
void File__write_checked_function_symbol(struct File* self, struct Checked_Function_Symbol* function_symbol) { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* function_parameter;
#line 2765 "bootstrap/stage0/ReCode.code"
    function_type = function_symbol->function_type;
#line 2766 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self, function_type->return_type);
#line 2767 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ' ');
#line 2768 "bootstrap/stage0/ReCode.code"
    File__write_string(self, function_symbol->super.name);
#line 2769 "bootstrap/stage0/ReCode.code"
    File__write_char(self, '(');
#line 2770 "bootstrap/stage0/ReCode.code"
    function_parameter = function_type->first_parameter;
#line 2771 "bootstrap/stage0/ReCode.code"
    while (function_parameter != NULL) {
#line 2772 "bootstrap/stage0/ReCode.code"
        File__write_checked_function_parameter(self, function_parameter);
#line 2773 "bootstrap/stage0/ReCode.code"
        function_parameter = function_parameter->next_parameter;
#line 2774 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (function_parameter != NULL) {
#line 2774 "bootstrap/stage0/ReCode.code"
                {
#line 2775 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self, ", ");
                } goto if__end__1; } if__end__1: ;
        }
    }
#line 2778 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ')');}

#line 2781 "bootstrap/stage0/ReCode.code"
void File__write_checked_function_parameter(struct File* self, struct Checked_Function_Parameter* parameter) {
#line 2782 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parameter->type->kind == Checked_Type_Kind__FUNCTION) {
#line 2782 "bootstrap/stage0/ReCode.code"
            { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* function_parameter;
#line 2783 "bootstrap/stage0/ReCode.code"
                function_type = ((struct Checked_Function_Type*) parameter->type);
#line 2784 "bootstrap/stage0/ReCode.code"
                File__write_checked_type(self, function_type->return_type);
#line 2785 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, " (*");
#line 2786 "bootstrap/stage0/ReCode.code"
                File__write_string(self, parameter->name);
#line 2787 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, ")(");
#line 2788 "bootstrap/stage0/ReCode.code"
                function_parameter = function_type->first_parameter;
#line 2789 "bootstrap/stage0/ReCode.code"
                while (function_parameter != NULL) {
#line 2790 "bootstrap/stage0/ReCode.code"
                    File__write_checked_function_parameter(self, function_parameter);
#line 2791 "bootstrap/stage0/ReCode.code"
                    function_parameter = function_parameter->next_parameter;
#line 2792 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (function_parameter != NULL) {
#line 2792 "bootstrap/stage0/ReCode.code"
                            {
#line 2793 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(self, ", ");
                            } goto if__end__2; } if__end__2: ;
                    }
                }
#line 2796 "bootstrap/stage0/ReCode.code"
                File__write_char(self, ')');
            } goto if__end__1; } if__else__1: ;
#line 2797 "bootstrap/stage0/ReCode.code"
        {
#line 2798 "bootstrap/stage0/ReCode.code"
            File__write_checked_type(self, parameter->type);
#line 2799 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parameter->name != NULL) {
#line 2799 "bootstrap/stage0/ReCode.code"
                    {
#line 2800 "bootstrap/stage0/ReCode.code"
                        File__write_char(self, ' ');
#line 2801 "bootstrap/stage0/ReCode.code"
                        File__write_string(self, parameter->name);
                    } goto if__end__3; } if__end__3: ;
            }
        } if__end__1: ;
    }}

#line 2806 "bootstrap/stage0/ReCode.code"
void File__write_checked_type(struct File* self, struct Checked_Type* type) {
#line 2807 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (type == NULL) {
#line 2807 "bootstrap/stage0/ReCode.code"
            {
#line 2808 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, "null");
            } goto if__end__1; } if__else__1: ;
#line 2809 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (type->kind == Checked_Type_Kind__I16) {
#line 2809 "bootstrap/stage0/ReCode.code"
                {
#line 2810 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self, "int16_t");
                } goto if__end__2; } if__else__2: ;
#line 2811 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (type->kind == Checked_Type_Kind__I32) {
#line 2811 "bootstrap/stage0/ReCode.code"
                    {
#line 2812 "bootstrap/stage0/ReCode.code"
                        File__write_cstring(self, "int32_t");
                    } goto if__end__3; } if__else__3: ;
#line 2813 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (type->kind == Checked_Type_Kind__I64) {
#line 2813 "bootstrap/stage0/ReCode.code"
                        {
#line 2814 "bootstrap/stage0/ReCode.code"
                            File__write_cstring(self, "int64_t");
                        } goto if__end__4; } if__else__4: ;
#line 2815 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (type->kind == Checked_Type_Kind__I8) {
#line 2815 "bootstrap/stage0/ReCode.code"
                            {
#line 2816 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(self, "int8_t");
                            } goto if__end__5; } if__else__5: ;
#line 2817 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (type->kind == Checked_Type_Kind__U16) {
#line 2817 "bootstrap/stage0/ReCode.code"
                                {
#line 2818 "bootstrap/stage0/ReCode.code"
                                    File__write_cstring(self, "uint16_t");
                                } goto if__end__6; } if__else__6: ;
#line 2819 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (type->kind == Checked_Type_Kind__U32) {
#line 2819 "bootstrap/stage0/ReCode.code"
                                    {
#line 2820 "bootstrap/stage0/ReCode.code"
                                        File__write_cstring(self, "uint32_t");
                                    } goto if__end__7; } if__else__7: ;
#line 2821 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (type->kind == Checked_Type_Kind__U64) {
#line 2821 "bootstrap/stage0/ReCode.code"
                                        {
#line 2822 "bootstrap/stage0/ReCode.code"
                                            File__write_cstring(self, "uint64_t");
                                        } goto if__end__8; } if__else__8: ;
#line 2823 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (type->kind == Checked_Type_Kind__U8) {
#line 2823 "bootstrap/stage0/ReCode.code"
                                            {
#line 2824 "bootstrap/stage0/ReCode.code"
                                                File__write_cstring(self, "uint8_t");
                                            } goto if__end__9; } if__else__9: ;
#line 2825 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (type->kind == Checked_Type_Kind__USIZE) {
#line 2825 "bootstrap/stage0/ReCode.code"
                                                {
#line 2826 "bootstrap/stage0/ReCode.code"
                                                    File__write_cstring(self, "size_t");
                                                } goto if__end__10; } if__else__10: ;
#line 2827 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (type->kind <= Checked_Type_Kind__NULL) {
#line 2827 "bootstrap/stage0/ReCode.code"
                                                    { struct Checked_Named_Type* named_type;
#line 2828 "bootstrap/stage0/ReCode.code"
                                                        named_type = ((struct Checked_Named_Type*) type);
#line 2829 "bootstrap/stage0/ReCode.code"
                                                        File__write_string(self, named_type->name);
                                                    } goto if__end__11; } if__else__11: ;
#line 2830 "bootstrap/stage0/ReCode.code"
                                                if__start__12: { if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2830 "bootstrap/stage0/ReCode.code"
                                                        { struct Checked_Struct_Type* struct_type;
#line 2831 "bootstrap/stage0/ReCode.code"
                                                            struct_type = ((struct Checked_Struct_Type*) type);
#line 2832 "bootstrap/stage0/ReCode.code"
                                                            File__write_cstring(self, "struct ");
#line 2833 "bootstrap/stage0/ReCode.code"
                                                            File__write_string(self, struct_type->super.name);
                                                        } goto if__end__12; } if__else__12: ;
#line 2834 "bootstrap/stage0/ReCode.code"
                                                    if__start__13: { if (type->kind == Checked_Type_Kind__OPAQUE) {
#line 2834 "bootstrap/stage0/ReCode.code"
                                                            { struct Checked_Opaque_Type* opaque_type;
#line 2835 "bootstrap/stage0/ReCode.code"
                                                                opaque_type = ((struct Checked_Opaque_Type*) type);
#line 2836 "bootstrap/stage0/ReCode.code"
                                                                File__write_cstring(self, "struct ");
#line 2837 "bootstrap/stage0/ReCode.code"
                                                                File__write_string(self, opaque_type->super.name);
                                                            } goto if__end__13; } if__else__13: ;
#line 2838 "bootstrap/stage0/ReCode.code"
                                                        if__start__14: { if (type->kind == Checked_Type_Kind__ENUM) {
#line 2838 "bootstrap/stage0/ReCode.code"
                                                                { struct Checked_Enum_Type* enum_type;
#line 2839 "bootstrap/stage0/ReCode.code"
                                                                    enum_type = ((struct Checked_Enum_Type*) type);
#line 2840 "bootstrap/stage0/ReCode.code"
                                                                    File__write_cstring(self, "enum ");
#line 2841 "bootstrap/stage0/ReCode.code"
                                                                    File__write_string(self, enum_type->super.name);
                                                                } goto if__end__14; } if__else__14: ;
#line 2842 "bootstrap/stage0/ReCode.code"
                                                            if__start__15: { if (type->kind == Checked_Type_Kind__POINTER) {
#line 2842 "bootstrap/stage0/ReCode.code"
                                                                    { struct Checked_Pointer_Type* pointer_type;
#line 2843 "bootstrap/stage0/ReCode.code"
                                                                        pointer_type = ((struct Checked_Pointer_Type*) type);
#line 2844 "bootstrap/stage0/ReCode.code"
                                                                        File__write_checked_type(self, pointer_type->other_type);
#line 2845 "bootstrap/stage0/ReCode.code"
                                                                        File__write_char(self, '*');
                                                                    } goto if__end__15; } if__else__15: ;
#line 2846 "bootstrap/stage0/ReCode.code"
                                                                {
#line 2847 "bootstrap/stage0/ReCode.code"
                                                                    Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2848 "bootstrap/stage0/ReCode.code"
                                                                    abort();
                                                                } if__end__15: ;
                                                            } if__end__14: ;
                                                        } if__end__13: ;
                                                    } if__end__12: ;
                                                } if__end__11: ;
                                            } if__end__10: ;
                                        } if__end__9: ;
                                    } if__end__8: ;
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }}

#line 2873 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbol__create_kind(enum Checked_Symbol_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name, struct Checked_Type* type) { struct Checked_Symbol* symbol;
#line 2874 "bootstrap/stage0/ReCode.code"
    symbol = ((struct Checked_Symbol*) malloc(kind_size));
#line 2875 "bootstrap/stage0/ReCode.code"
    symbol->kind = kind;
#line 2876 "bootstrap/stage0/ReCode.code"
    symbol->location = location;
#line 2877 "bootstrap/stage0/ReCode.code"
    symbol->name = name;
#line 2878 "bootstrap/stage0/ReCode.code"
    symbol->type = type;
#line 2879 "bootstrap/stage0/ReCode.code"
    symbol->prev_symbol = NULL;
#line 2880 "bootstrap/stage0/ReCode.code"
    symbol->next_symbol = NULL;
#line 2881 "bootstrap/stage0/ReCode.code"
    return symbol;}

#line 2888 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member_Symbol* Checked_Enum_Member_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2889 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Enum_Member_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__ENUM_MEMBER, sizeof(struct Checked_Enum_Member_Symbol), location, name, type));}

#line 2898 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Symbol* Checked_Function_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Function_Type* function_type) { struct Checked_Function_Symbol* symbol;
#line 2899 "bootstrap/stage0/ReCode.code"
    symbol = ((struct Checked_Function_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION, sizeof(struct Checked_Function_Symbol), location, name, ((struct Checked_Type*) function_type)));
#line 2900 "bootstrap/stage0/ReCode.code"
    symbol->function_type = function_type;
#line 2901 "bootstrap/stage0/ReCode.code"
    symbol->checked_statements = NULL;
#line 2902 "bootstrap/stage0/ReCode.code"
    return symbol;}

#line 2909 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter_Symbol* Checked_Function_Parameter_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2910 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Function_Parameter_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION_PARAMETER, sizeof(struct Checked_Function_Parameter_Symbol), location, name, type));}

#line 2918 "bootstrap/stage0/ReCode.code"
struct Checked_Type_Symbol* Checked_Type_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Named_Type* named_type) { struct Checked_Type_Symbol* symbol;
#line 2919 "bootstrap/stage0/ReCode.code"
    symbol = ((struct Checked_Type_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__TYPE, sizeof(struct Checked_Type_Symbol), location, name, ((struct Checked_Type*) Checked_Defined_Type__create(named_type))));
#line 2920 "bootstrap/stage0/ReCode.code"
    symbol->named_type = named_type;
#line 2921 "bootstrap/stage0/ReCode.code"
    return symbol;}

#line 2928 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Symbol* Checked_Variable__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2929 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Variable_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__VARIABLE, sizeof(struct Checked_Variable_Symbol), location, name, type));}

#line 2938 "bootstrap/stage0/ReCode.code"
struct Checked_Symbols* Checked_Symbols__create(struct Checked_Symbols* parent) { struct Checked_Symbols* symbols;
#line 2939 "bootstrap/stage0/ReCode.code"
    symbols = ((struct Checked_Symbols*) malloc(sizeof(struct Checked_Symbols)));
#line 2940 "bootstrap/stage0/ReCode.code"
    symbols->parent = parent;
#line 2941 "bootstrap/stage0/ReCode.code"
    symbols->first_symbol = NULL;
#line 2942 "bootstrap/stage0/ReCode.code"
    symbols->last_symbol = NULL;
#line 2943 "bootstrap/stage0/ReCode.code"
    return symbols;}

#line 2946 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_sibling_symbol(struct Checked_Symbols* self, struct String* name) { struct Checked_Symbol* symbol;
#line 2947 "bootstrap/stage0/ReCode.code"
    symbol = self->first_symbol;
#line 2948 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 2949 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, symbol->name)) {
#line 2949 "bootstrap/stage0/ReCode.code"
                {
#line 2950 "bootstrap/stage0/ReCode.code"
                    return symbol;
                } goto if__end__1; } if__end__1: ;
        }
#line 2952 "bootstrap/stage0/ReCode.code"
        symbol = symbol->next_symbol;
    }
#line 2954 "bootstrap/stage0/ReCode.code"
    return NULL;}

#line 2957 "bootstrap/stage0/ReCode.code"
void Checked_Symbols__append_symbol(struct Checked_Symbols* self, struct Checked_Symbol* symbol) { struct Checked_Symbol* other_symbol;
#line 2958 "bootstrap/stage0/ReCode.code"
    other_symbol = Checked_Symbols__find_sibling_symbol(self, symbol->name);
#line 2959 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_symbol != NULL) {
#line 2959 "bootstrap/stage0/ReCode.code"
            {
#line 2960 "bootstrap/stage0/ReCode.code"
                Source_Location__error(symbol->location, String__append_source_location(String__create_from("Symbol declared first here: "), other_symbol->location));
#line 2961 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 2964 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->last_symbol == NULL) {
#line 2964 "bootstrap/stage0/ReCode.code"
            {
#line 2965 "bootstrap/stage0/ReCode.code"
                self->first_symbol = symbol;
            } goto if__end__2; } if__else__2: ;
#line 2966 "bootstrap/stage0/ReCode.code"
        {
#line 2967 "bootstrap/stage0/ReCode.code"
            self->last_symbol->next_symbol = symbol;
#line 2968 "bootstrap/stage0/ReCode.code"
            symbol->prev_symbol = self->last_symbol;
        } if__end__2: ;
    }
#line 2970 "bootstrap/stage0/ReCode.code"
    self->last_symbol = symbol;}

#line 2973 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_symbol(struct Checked_Symbols* self, struct String* name) { struct Checked_Symbol* symbol;
#line 2974 "bootstrap/stage0/ReCode.code"
    symbol = self->last_symbol;
#line 2975 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 2976 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, symbol->name)) {
#line 2976 "bootstrap/stage0/ReCode.code"
                {
#line 2977 "bootstrap/stage0/ReCode.code"
                    return symbol;
                } goto if__end__1; } if__end__1: ;
        }
#line 2979 "bootstrap/stage0/ReCode.code"
        symbol = symbol->prev_symbol;
    }
#line 2981 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->parent != NULL) {
#line 2981 "bootstrap/stage0/ReCode.code"
            {
#line 2982 "bootstrap/stage0/ReCode.code"
                return Checked_Symbols__find_symbol(self->parent, name);
            } goto if__end__2; } if__end__2: ;
    }
#line 2984 "bootstrap/stage0/ReCode.code"
    return NULL;}

#line 3029 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checked_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type) { struct Checked_Expression* expression;
#line 3030 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Expression*) malloc(kind_size));
#line 3031 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 3032 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 3033 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 3034 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3043 "bootstrap/stage0/ReCode.code"
struct Checked_Binary_Expression* Checked_Binary_Expression__create_kind(enum Checked_Expression_Kind kind, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) { struct Checked_Binary_Expression* expression;
#line 3044 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Binary_Expression*) Checked_Expression__create_kind(kind, sizeof(struct Checked_Binary_Expression), location, type));
#line 3045 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 3046 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 3047 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3055 "bootstrap/stage0/ReCode.code"
struct Checked_Unary_Expression* Checked_Unary_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) { struct Checked_Unary_Expression* expression;
#line 3056 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Unary_Expression*) Checked_Expression__create_kind(kind, kind_size, location, type));
#line 3057 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3058 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3065 "bootstrap/stage0/ReCode.code"
struct Checked_Add_Expression* Checked_Add_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3066 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Add_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__ADD, location, type, left_expression, right_expression));}

#line 3073 "bootstrap/stage0/ReCode.code"
struct Checked_Address_Of_Expression* Checked_Address_Of_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3074 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Address_Of_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__ADDRESS_OF, sizeof(struct Checked_Address_Of_Expression), location, type, other_expression));}

#line 3083 "bootstrap/stage0/ReCode.code"
struct Checked_Array_Access_Expression* Checked_Array_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* array_expression, struct Checked_Expression* index_expression) { struct Checked_Array_Access_Expression* expression;
#line 3084 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Array_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__ARRAY_ACCESS, sizeof(struct Checked_Array_Access_Expression), location, type));
#line 3085 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 3086 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 3087 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3095 "bootstrap/stage0/ReCode.code"
struct Checked_Bool_Expression* Checked_Bool_Expression__create(struct Source_Location* location, struct Checked_Type* type, bool value) { struct Checked_Bool_Expression* expression;
#line 3096 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Bool_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__BOOL, sizeof(struct Checked_Bool_Expression), location, type));
#line 3097 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3098 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3106 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Argument* Checked_Call_Argument__create(struct Checked_Expression* expression) { struct Checked_Call_Argument* argument;
#line 3107 "bootstrap/stage0/ReCode.code"
    argument = ((struct Checked_Call_Argument*) malloc(sizeof(struct Checked_Call_Argument)));
#line 3108 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 3109 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 3110 "bootstrap/stage0/ReCode.code"
    return argument;}

#line 3119 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Expression* Checked_Call_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* callee_expression, struct Checked_Call_Argument* first_argument) { struct Checked_Call_Expression* expression;
#line 3120 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Call_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CALL, sizeof(struct Checked_Call_Expression), location, type));
#line 3121 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 3122 "bootstrap/stage0/ReCode.code"
    expression->first_argument = first_argument;
#line 3123 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3131 "bootstrap/stage0/ReCode.code"
struct Checked_Cast_Expression* Checked_Cast_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) { struct Checked_Cast_Expression* expression;
#line 3132 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Cast_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CAST, sizeof(struct Checked_Cast_Expression), location, type));
#line 3133 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3134 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3142 "bootstrap/stage0/ReCode.code"
struct Checked_Character_Expression* Checked_Character_Expression__create(struct Source_Location* location, struct Checked_Type* type, char value) { struct Checked_Character_Expression* expression;
#line 3143 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Character_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CHARACTER, sizeof(struct Checked_Character_Expression), location, type));
#line 3144 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3145 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3153 "bootstrap/stage0/ReCode.code"
struct Checked_Dereference_Expression* Checked_Dereference_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* value_expression) { struct Checked_Dereference_Expression* expression;
#line 3154 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Dereference_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__DEREFERENCE, sizeof(struct Checked_Dereference_Expression), location, type));
#line 3155 "bootstrap/stage0/ReCode.code"
    expression->value_expression = value_expression;
#line 3156 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3163 "bootstrap/stage0/ReCode.code"
struct Checked_Divide_Expression* Checked_Divide_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3164 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Divide_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__DIVIDE, location, type, left_expression, right_expression));}

#line 3171 "bootstrap/stage0/ReCode.code"
struct Checked_Equals_Expression* Checked_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3172 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__EQUALS, location, type, left_expression, right_expression));}

#line 3179 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Expression* Checked_Greater_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3180 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Greater_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER, location, type, left_expression, right_expression));}

#line 3187 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Or_Equals_Expression* Checked_Greater_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3188 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Greater_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER_OR_EQUALS, location, type, left_expression, right_expression));}

#line 3196 "bootstrap/stage0/ReCode.code"
struct Checked_Group_Expression* Checked_Group_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) { struct Checked_Group_Expression* expression;
#line 3197 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Group_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__GROUP, sizeof(struct Checked_Group_Expression), location, type));
#line 3198 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3199 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3207 "bootstrap/stage0/ReCode.code"
struct Checked_Integer_Expression* Checked_Integer_Expression__create(struct Source_Location* location, struct Checked_Type* type, uint64_t value) { struct Checked_Integer_Expression* expression;
#line 3208 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Integer_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__INTEGER, sizeof(struct Checked_Integer_Expression), location, type));
#line 3209 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3210 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3217 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Expression* Checked_Less_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3218 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Less_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS, location, type, left_expression, right_expression));}

#line 3225 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Or_Equals_Expression* Checked_Less_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3226 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Less_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS_OR_EQUALS, location, type, left_expression, right_expression));}

#line 3233 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_And_Expression* Checked_Logic_And_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3234 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Logic_And_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_AND, location, type, left_expression, right_expression));}

#line 3241 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_Or_Expression* Checked_Logic_Or_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3242 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Logic_Or_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_OR, location, type, left_expression, right_expression));}

#line 3251 "bootstrap/stage0/ReCode.code"
struct Checked_Member_Access_Expression* Checked_Member_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* object_expression, struct Checked_Struct_Member* member) { struct Checked_Member_Access_Expression* expression;
#line 3252 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Member_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__MEMBER_ACCESS, sizeof(struct Checked_Member_Access_Expression), location, type));
#line 3253 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 3254 "bootstrap/stage0/ReCode.code"
    expression->member = member;
#line 3255 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3262 "bootstrap/stage0/ReCode.code"
struct Checked_Minus_Expression* Checked_Minus_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3263 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Minus_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__MINUS, sizeof(struct Checked_Minus_Expression), location, type, other_expression));}

#line 3270 "bootstrap/stage0/ReCode.code"
struct Checked_Modulo_Expression* Checked_Modulo_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3271 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Modulo_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MODULO, location, type, left_expression, right_expression));}

#line 3278 "bootstrap/stage0/ReCode.code"
struct Checked_Multiply_Expression* Checked_Multiply_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3279 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Multiply_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MULTIPLY, location, type, left_expression, right_expression));}

#line 3286 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Expression* Checked_Not_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3287 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Not_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__NOT, sizeof(struct Checked_Not_Expression), location, type, other_expression));}

#line 3294 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Equals_Expression* Checked_Not_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3295 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Not_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__NOT_EQUALS, location, type, left_expression, right_expression));}

#line 3302 "bootstrap/stage0/ReCode.code"
struct Checked_Null_Expression* Checked_Null_Expression__create(struct Source_Location* location, struct Checked_Type* type) {
#line 3303 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Null_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__NULL, sizeof(struct Checked_Null_Expression), location, type));}

#line 3311 "bootstrap/stage0/ReCode.code"
struct Checked_Sizeof_Expression* Checked_Sizeof_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Type* sized_type) { struct Checked_Sizeof_Expression* expression;
#line 3312 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Sizeof_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SIZEOF, sizeof(struct Checked_Sizeof_Expression), location, type));
#line 3313 "bootstrap/stage0/ReCode.code"
    expression->sized_type = sized_type;
#line 3314 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3322 "bootstrap/stage0/ReCode.code"
struct Checked_String_Expression* Checked_String_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct String* value) { struct Checked_String_Expression* expression;
#line 3323 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_String_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__STRING, sizeof(struct Checked_String_Expression), location, type));
#line 3324 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3325 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3332 "bootstrap/stage0/ReCode.code"
struct Checked_Substract_Expression* Checked_Substract_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3333 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Substract_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__SUBSTRACT, location, type, left_expression, right_expression));}

#line 3341 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol_Expression* Checked_Symbol_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Symbol* symbol) { struct Checked_Symbol_Expression* expression;
#line 3342 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Symbol_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SYMBOL, sizeof(struct Checked_Symbol_Expression), location, type));
#line 3343 "bootstrap/stage0/ReCode.code"
    expression->symbol = symbol;
#line 3344 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3370 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checked_Statement__create_kind(enum Checked_Statement_Kind kind, size_t kind_size, struct Source_Location* location) { struct Checked_Statement* statement;
#line 3371 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Statement*) malloc(kind_size));
#line 3372 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 3373 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 3374 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 3375 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3384 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checked_Assignment_Statement__create(struct Source_Location* location, struct Checked_Expression* object_expression, struct Checked_Expression* value_expression) { struct Checked_Assignment_Statement* statement;
#line 3385 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Assignment_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__ASSIGNMENT, sizeof(struct Checked_Assignment_Statement), location));
#line 3386 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 3387 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 3388 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3397 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checked_Block_Statement__create(struct Source_Location* location, struct Checker_Context* context, struct String* label) { struct Checked_Block_Statement* statement;
#line 3398 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Block_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BLOCK, sizeof(struct Checked_Block_Statement), location));
#line 3399 "bootstrap/stage0/ReCode.code"
    statement->context = context;
#line 3400 "bootstrap/stage0/ReCode.code"
    statement->label = label;
#line 3401 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3408 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checked_Break_Statement__create(struct Source_Location* location) {
#line 3409 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Break_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BREAK, sizeof(struct Checked_Break_Statement), location));}

#line 3417 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checked_Expression_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) { struct Checked_Expression_Statement* statement;
#line 3418 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Expression_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__EXPRESSION, sizeof(struct Checked_Expression_Statement), location));
#line 3419 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3420 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3428 "bootstrap/stage0/ReCode.code"
struct Checked_Goto_Statement* Checked_Goto_Statement__create(struct Source_Location* location, struct String* label) { struct Checked_Goto_Statement* statement;
#line 3429 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Goto_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__GOTO, sizeof(struct Checked_Goto_Statement), location));
#line 3430 "bootstrap/stage0/ReCode.code"
    statement->label = label;
#line 3431 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3441 "bootstrap/stage0/ReCode.code"
struct Checked_If_Statement* Checked_If_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* true_statement, struct Checked_Statement* false_statement) { struct Checked_If_Statement* statement;
#line 3442 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_If_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__IF, sizeof(struct Checked_If_Statement), location));
#line 3443 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3444 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 3445 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 3446 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3454 "bootstrap/stage0/ReCode.code"
struct Checked_Label_Statement* Checked_Label_Statement__create(struct Source_Location* location, struct String* label) { struct Checked_Label_Statement* statement;
#line 3455 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Label_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__LABEL, sizeof(struct Checked_Label_Statement), location));
#line 3456 "bootstrap/stage0/ReCode.code"
    statement->label = label;
#line 3457 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3465 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checked_Return_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) { struct Checked_Return_Statement* statement;
#line 3466 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Return_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__RETURN, sizeof(struct Checked_Return_Statement), location));
#line 3467 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3468 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3478 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checked_Variable_Statement__create(struct Source_Location* location, struct Checked_Variable_Symbol* variable, struct Checked_Expression* expression, bool is_external) { struct Checked_Variable_Statement* statement;
#line 3479 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Variable_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__VARIABLE, sizeof(struct Checked_Variable_Statement), location));
#line 3480 "bootstrap/stage0/ReCode.code"
    statement->variable = variable;
#line 3481 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3482 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 3483 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3492 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checked_While_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* body_statement) { struct Checked_While_Statement* statement;
#line 3493 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_While_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__WHILE, sizeof(struct Checked_While_Statement), location));
#line 3494 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3495 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 3496 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3505 "bootstrap/stage0/ReCode.code"
struct Checked_Statements* Checked_Statements__create(struct Checked_Symbols* symbols) { struct Checked_Statements* statements;
#line 3506 "bootstrap/stage0/ReCode.code"
    statements = ((struct Checked_Statements*) malloc(sizeof(struct Checked_Statements)));
#line 3507 "bootstrap/stage0/ReCode.code"
    statements->symbols = symbols;
#line 3508 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 3509 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 3510 "bootstrap/stage0/ReCode.code"
    return statements;}

#line 3513 "bootstrap/stage0/ReCode.code"
void Checked_Statements__append(struct Checked_Statements* self, struct Checked_Statement* statement) {
#line 3514 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->first_statement == NULL) {
#line 3514 "bootstrap/stage0/ReCode.code"
            {
#line 3515 "bootstrap/stage0/ReCode.code"
                self->first_statement = statement;
            } goto if__end__1; } if__else__1: ;
#line 3516 "bootstrap/stage0/ReCode.code"
        {
#line 3517 "bootstrap/stage0/ReCode.code"
            self->last_statement->next_statement = statement;
        } if__end__1: ;
    }
#line 3519 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;}

#line 3544 "bootstrap/stage0/ReCode.code"
struct Checker_Context* Checker_Context__create(struct Checker_Context* parent) { struct Checker_Context* context;
#line 3545 "bootstrap/stage0/ReCode.code"
    context = ((struct Checker_Context*) malloc(sizeof(struct Checker_Context)));
#line 3546 "bootstrap/stage0/ReCode.code"
    context->parent = parent;
#line 3547 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parent == NULL) {
#line 3547 "bootstrap/stage0/ReCode.code"
            {
#line 3548 "bootstrap/stage0/ReCode.code"
                context->symbols = Checked_Symbols__create(NULL);
#line 3549 "bootstrap/stage0/ReCode.code"
                context->function_counter = Counter__create();
#line 3550 "bootstrap/stage0/ReCode.code"
                context->function_return_type = NULL;
            } goto if__end__1; } if__else__1: ;
#line 3551 "bootstrap/stage0/ReCode.code"
        {
#line 3552 "bootstrap/stage0/ReCode.code"
            context->symbols = Checked_Symbols__create(parent->symbols);
#line 3553 "bootstrap/stage0/ReCode.code"
            context->function_counter = parent->function_counter;
#line 3554 "bootstrap/stage0/ReCode.code"
            context->function_return_type = parent->function_return_type;
        } if__end__1: ;
    }
#line 3556 "bootstrap/stage0/ReCode.code"
    context->statements = Checked_Statements__create(context->symbols);
#line 3557 "bootstrap/stage0/ReCode.code"
    return context;}

#line 3569 "bootstrap/stage0/ReCode.code"
struct Checker* Checker__create() { struct Checker* checker; struct Source_Location* location;
#line 3570 "bootstrap/stage0/ReCode.code"
    checker = ((struct Checker*) malloc(sizeof(struct Checker)));
#line 3571 "bootstrap/stage0/ReCode.code"
    checker->first_type = NULL;
#line 3572 "bootstrap/stage0/ReCode.code"
    checker->last_type = NULL;
#line 3573 "bootstrap/stage0/ReCode.code"
    checker->root_context = Checker_Context__create(NULL);
#line 3574 "bootstrap/stage0/ReCode.code"
    checker->current_context = checker->root_context;
#line 3576 "bootstrap/stage0/ReCode.code"
    location = Source_Location__create(NULL, ((uint16_t) 0), ((uint16_t) 1));
#line 3577 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__BOOL, sizeof(struct Checked_Named_Type), location, String__create_from("bool")));
#line 3578 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__CHAR, sizeof(struct Checked_Named_Type), location, String__create_from("char")));
#line 3579 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I16, sizeof(struct Checked_Named_Type), location, String__create_from("i16")));
#line 3580 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I32, sizeof(struct Checked_Named_Type), location, String__create_from("i32")));
#line 3581 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I64, sizeof(struct Checked_Named_Type), location, String__create_from("i64")));
#line 3582 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I8, sizeof(struct Checked_Named_Type), location, String__create_from("i8")));
#line 3583 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U16, sizeof(struct Checked_Named_Type), location, String__create_from("u16")));
#line 3584 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U32, sizeof(struct Checked_Named_Type), location, String__create_from("u32")));
#line 3585 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U64, sizeof(struct Checked_Named_Type), location, String__create_from("u64")));
#line 3586 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U8, sizeof(struct Checked_Named_Type), location, String__create_from("u8")));
#line 3587 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__USIZE, sizeof(struct Checked_Named_Type), location, String__create_from("usize")));
#line 3588 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__VOID, sizeof(struct Checked_Named_Type), location, String__create_from("void")));
#line 3589 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__NULL, sizeof(struct Checked_Named_Type), location, String__create_from("null")));
#line 3590 "bootstrap/stage0/ReCode.code"
    checker->last_builting_type = checker->last_type;
#line 3592 "bootstrap/stage0/ReCode.code"
    return checker;}

#line 3595 "bootstrap/stage0/ReCode.code"
void Checker__append_type(struct Checker* self, struct Checked_Named_Type* type) {
#line 3596 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->first_type == NULL) {
#line 3596 "bootstrap/stage0/ReCode.code"
            {
#line 3597 "bootstrap/stage0/ReCode.code"
                self->first_type = type;
            } goto if__end__1; } if__else__1: ;
#line 3598 "bootstrap/stage0/ReCode.code"
        {
#line 3599 "bootstrap/stage0/ReCode.code"
            self->last_type->super.next_type = ((struct Checked_Type*) type);
        } if__end__1: ;
    }
#line 3601 "bootstrap/stage0/ReCode.code"
    self->last_type = type;
#line 3603 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->root_context->symbols, ((struct Checked_Symbol*) Checked_Type_Symbol__create(type->super.location, type->name, type)));}

#line 3606 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__find_type(struct Checker* self, struct String* name) { struct Checked_Named_Type* type;
#line 3607 "bootstrap/stage0/ReCode.code"
    type = self->first_type;
#line 3608 "bootstrap/stage0/ReCode.code"
    while (type != NULL) {
#line 3609 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, type->name)) {
#line 3609 "bootstrap/stage0/ReCode.code"
                {
#line 3610 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 3612 "bootstrap/stage0/ReCode.code"
        type = ((struct Checked_Named_Type*) type->super.next_type);
    }
#line 3614 "bootstrap/stage0/ReCode.code"
    return type;}

#line 3617 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__get_builtin_type(struct Checker* self, enum Checked_Type_Kind kind) { struct Checked_Named_Type* type; struct Checked_Named_Type* custom_type;
#line 3618 "bootstrap/stage0/ReCode.code"
    type = self->first_type;
#line 3619 "bootstrap/stage0/ReCode.code"
    custom_type = ((struct Checked_Named_Type*) self->last_builting_type->super.next_type);
#line 3620 "bootstrap/stage0/ReCode.code"
    while (type != custom_type) {
#line 3621 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (type->super.kind == kind) {
#line 3621 "bootstrap/stage0/ReCode.code"
                {
#line 3622 "bootstrap/stage0/ReCode.code"
                    return type;
                } goto if__end__1; } if__end__1: ;
        }
#line 3624 "bootstrap/stage0/ReCode.code"
        type = ((struct Checked_Named_Type*) type->super.next_type);
    }
#line 3626 "bootstrap/stage0/ReCode.code"
    error(String__create_from("No such builtin type"));
#line 3627 "bootstrap/stage0/ReCode.code"
    abort();}

#line 3630 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checker__resolve_type(struct Checker* self, struct Parsed_Type* parsed_type) {
#line 3631 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_type->kind == Parsed_Type_Kind__NAMED) {
#line 3631 "bootstrap/stage0/ReCode.code"
            { struct Checked_Named_Type* type;
#line 3632 "bootstrap/stage0/ReCode.code"
                type = Checker__find_type(self, ((struct Parsed_Named_Type*) parsed_type)->name);
#line 3633 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (type != NULL) {
#line 3633 "bootstrap/stage0/ReCode.code"
                        {
#line 3634 "bootstrap/stage0/ReCode.code"
                            return ((struct Checked_Type*) type);
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 3637 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (parsed_type->kind == Parsed_Type_Kind__POINTER) {
#line 3637 "bootstrap/stage0/ReCode.code"
            {
#line 3638 "bootstrap/stage0/ReCode.code"
                return ((struct Checked_Type*) Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((struct Parsed_Pointer_Type*) parsed_type)->other_type)));
            } goto if__end__3; } if__end__3: ;
    }
#line 3640 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (parsed_type->kind == Parsed_Type_Kind__STRUCT) {
#line 3640 "bootstrap/stage0/ReCode.code"
            { struct Checked_Type* type;
#line 3641 "bootstrap/stage0/ReCode.code"
                type = Checker__resolve_type(self, ((struct Parsed_Struct_Type*) parsed_type)->other_type);
#line 3642 "bootstrap/stage0/ReCode.code"
                if__start__5: { if (type->kind != Checked_Type_Kind__STRUCT) {
#line 3642 "bootstrap/stage0/ReCode.code"
                        {
#line 3643 "bootstrap/stage0/ReCode.code"
                            TODO("Report unexpected type");
#line 3644 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__5; } if__end__5: ;
                }
#line 3646 "bootstrap/stage0/ReCode.code"
                return type;
            } goto if__end__4; } if__end__4: ;
    }
#line 3648 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (parsed_type->kind == Parsed_Type_Kind__FUNCTION) {
#line 3648 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Function_Type* parsed_function_type; struct Checked_Function_Parameter* first_parameter; struct Parsed_Function_Parameter* parsed_parameter; struct Checked_Type* return_type;
#line 3649 "bootstrap/stage0/ReCode.code"
                parsed_function_type = ((struct Parsed_Function_Type*) parsed_type);
#line 3650 "bootstrap/stage0/ReCode.code"
                first_parameter = NULL;
#line 3651 "bootstrap/stage0/ReCode.code"
                parsed_parameter = parsed_function_type->first_parameter;
#line 3652 "bootstrap/stage0/ReCode.code"
                if__start__7: { if (parsed_parameter != NULL) {
#line 3652 "bootstrap/stage0/ReCode.code"
                        { struct Checked_Function_Parameter* last_parameter;
#line 3653 "bootstrap/stage0/ReCode.code"
                            first_parameter = Checked_Function_Parameter__create(parsed_parameter->location, NULL, Checker__resolve_type(self, parsed_parameter->type));
#line 3654 "bootstrap/stage0/ReCode.code"
                            last_parameter = first_parameter;
#line 3655 "bootstrap/stage0/ReCode.code"
                            parsed_parameter = parsed_parameter->next_parameter;
#line 3656 "bootstrap/stage0/ReCode.code"
                            while (parsed_parameter != NULL) { struct Checked_Function_Parameter* parameter;
#line 3657 "bootstrap/stage0/ReCode.code"
                                parameter = Checked_Function_Parameter__create(parsed_parameter->location, NULL, Checker__resolve_type(self, parsed_parameter->type));
#line 3658 "bootstrap/stage0/ReCode.code"
                                last_parameter->next_parameter = parameter;
#line 3659 "bootstrap/stage0/ReCode.code"
                                last_parameter = parameter;
#line 3660 "bootstrap/stage0/ReCode.code"
                                parsed_parameter = parsed_parameter->next_parameter;
                            }
                        } goto if__end__7; } if__end__7: ;
                }
#line 3663 "bootstrap/stage0/ReCode.code"
                return_type = Checker__resolve_type(self, parsed_function_type->return_type);
#line 3664 "bootstrap/stage0/ReCode.code"
                return ((struct Checked_Type*) Checked_Function_Type__create(parsed_type->location, first_parameter, return_type));
            } goto if__end__6; } if__end__6: ;
    }
#line 3666 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_type->location, String__create_from("Undefined type"));
#line 3667 "bootstrap/stage0/ReCode.code"
    abort();}

#line 3670 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_add_expression(struct Checker* self, struct Parsed_Add_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3671 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3672 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3673 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3674 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3675 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3678 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_address_of_expression(struct Checker* self, struct Parsed_Address_Of_Expression* parsed_expression) { struct Checked_Expression* other_expression;
#line 3679 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3680 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_expression->kind != Checked_Expression_Kind__SYMBOL) {
#line 3680 "bootstrap/stage0/ReCode.code"
            {
#line 3681 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.super.location, String__create_from("Not a symbol"));
#line 3682 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3684 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Address_Of_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checked_Pointer_Type__create(other_expression->location, other_expression->type)), other_expression));}

#line 3687 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_array_access_expression(struct Checker* self, struct Parsed_Array_Access_Expression* parsed_expression) { struct Checked_Expression* array_expression; struct Checked_Type* array_type; struct Checked_Type* type; struct Checked_Expression* index_expression;
#line 3688 "bootstrap/stage0/ReCode.code"
    array_expression = Checker__check_expression(self, parsed_expression->array_expression);
#line 3689 "bootstrap/stage0/ReCode.code"
    array_type = array_expression->type;
#line 3690 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (array_type->kind != Checked_Type_Kind__POINTER) {
#line 3690 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 3691 "bootstrap/stage0/ReCode.code"
                message = String__create();
#line 3692 "bootstrap/stage0/ReCode.code"
                String__append_char(message, '\"');
#line 3693 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, array_type);
#line 3694 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" is not a pointer type.");
#line 3695 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->array_expression->location, message);
#line 3696 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3698 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Pointer_Type*) array_type)->other_type;
#line 3699 "bootstrap/stage0/ReCode.code"
    index_expression = Checker__check_expression(self, parsed_expression->index_expression);
#line 3700 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE)), index_expression->type, index_expression->location);
#line 3701 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression));}

#line 3704 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_bool_expression(struct Checker* self, struct Parsed_Bool_Expression* parsed_expression) { struct Checked_Type* expression_type; bool value;
#line 3705 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL));
#line 3706 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3707 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3710 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_call_expression(struct Checker* self, struct Parsed_Call_Expression* parsed_expression) { struct Checked_Expression* callee_expression; struct Checked_Type* callee_type; struct Checked_Function_Type* function_type; struct Checked_Call_Argument* first_argument;
#line 3711 "bootstrap/stage0/ReCode.code"
    callee_expression = Checker__check_expression(self, parsed_expression->callee_expression);
#line 3712 "bootstrap/stage0/ReCode.code"
    callee_type = callee_expression->type;
#line 3713 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (callee_type->kind != Checked_Type_Kind__FUNCTION) {
#line 3713 "bootstrap/stage0/ReCode.code"
            {
#line 3714 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.location, String__create_from("Not a function"));
#line 3715 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3717 "bootstrap/stage0/ReCode.code"
    function_type = ((struct Checked_Function_Type*) callee_type);
#line 3718 "bootstrap/stage0/ReCode.code"
    first_argument = NULL;
#line 3719 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (!(parsed_expression->first_argument != NULL)) { if (!(function_type->first_parameter != NULL)) { goto if__end__2; } } if__then__2__3: {
#line 3719 "bootstrap/stage0/ReCode.code"
            { struct Checked_Call_Argument* last_argument; struct Checked_Function_Parameter* function_parameter; struct Parsed_Call_Argument* parsed_argument;
#line 3720 "bootstrap/stage0/ReCode.code"
                last_argument = NULL;
#line 3721 "bootstrap/stage0/ReCode.code"
                function_parameter = function_type->first_parameter;
#line 3722 "bootstrap/stage0/ReCode.code"
                parsed_argument = parsed_expression->first_argument;
#line 3723 "bootstrap/stage0/ReCode.code"
                while (function_parameter != NULL && parsed_argument != NULL) { struct Checked_Expression* argument_expression; struct Checked_Call_Argument* argument;
#line 3724 "bootstrap/stage0/ReCode.code"
                    argument_expression = Checker__check_expression(self, parsed_argument->expression);
#line 3725 "bootstrap/stage0/ReCode.code"
                    Checked_Type__expect_same_type(function_parameter->type, argument_expression->type, argument_expression->location);
#line 3726 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (argument_expression->kind == Checked_Expression_Kind__SYMBOL) { if (((struct Checked_Symbol_Expression*) argument_expression)->symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 3726 "bootstrap/stage0/ReCode.code"
                                {
#line 3727 "bootstrap/stage0/ReCode.code"
                                    TODO("Create callable expression stored in a temp variable");
                                } goto if__end__4; } } if__end__4: ;
                    }
#line 3729 "bootstrap/stage0/ReCode.code"
                    argument = Checked_Call_Argument__create(argument_expression);
#line 3730 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (last_argument == NULL) {
#line 3730 "bootstrap/stage0/ReCode.code"
                            {
#line 3731 "bootstrap/stage0/ReCode.code"
                                first_argument = argument;
                            } goto if__end__5; } if__else__5: ;
#line 3732 "bootstrap/stage0/ReCode.code"
                        {
#line 3733 "bootstrap/stage0/ReCode.code"
                            last_argument->next_argument = argument;
                        } if__end__5: ;
                    }
#line 3735 "bootstrap/stage0/ReCode.code"
                    last_argument = argument;
#line 3736 "bootstrap/stage0/ReCode.code"
                    function_parameter = function_parameter->next_parameter;
#line 3737 "bootstrap/stage0/ReCode.code"
                    parsed_argument = parsed_argument->next_argument;
                }
#line 3739 "bootstrap/stage0/ReCode.code"
                if__start__6: { if (function_parameter != NULL) {
#line 3739 "bootstrap/stage0/ReCode.code"
                        {
#line 3740 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(parsed_expression->super.location, String__create_from("Report too few arguments"));
#line 3741 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__6; } if__end__6: ;
                }
#line 3743 "bootstrap/stage0/ReCode.code"
                if__start__7: { if (parsed_argument != NULL) {
#line 3743 "bootstrap/stage0/ReCode.code"
                        {
#line 3744 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(parsed_expression->super.location, String__create_from("Report too many arguments"));
#line 3745 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__7; } if__end__7: ;
                }
            } goto if__end__2; } if__end__2: ;
    }
#line 3748 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Call_Expression__create(parsed_expression->super.location, function_type->return_type, callee_expression, first_argument));}

#line 3751 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_cast_expression(struct Checker* self, struct Parsed_Cast_Expression* parsed_expression) { struct Checked_Type* type; struct Checked_Expression* other_expression; struct Checked_Type* other_type; bool can_cast;
#line 3752 "bootstrap/stage0/ReCode.code"
    type = Checker__resolve_type(self, parsed_expression->type);
#line 3753 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3754 "bootstrap/stage0/ReCode.code"
    other_type = other_expression->type;
#line 3755 "bootstrap/stage0/ReCode.code"
    can_cast = false;
#line 3756 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (type->kind == Checked_Type_Kind__POINTER) {
#line 3756 "bootstrap/stage0/ReCode.code"
            {
#line 3757 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (other_type->kind == Checked_Type_Kind__POINTER) {
#line 3757 "bootstrap/stage0/ReCode.code"
                        {
#line 3758 "bootstrap/stage0/ReCode.code"
                            can_cast = true;
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 3760 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (Checked_Type__is_scalar_type(type)) {
#line 3760 "bootstrap/stage0/ReCode.code"
                {
#line 3761 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (Checked_Type__is_scalar_type(type)) {
#line 3761 "bootstrap/stage0/ReCode.code"
                            {
#line 3762 "bootstrap/stage0/ReCode.code"
                                can_cast = true;
                            } goto if__end__4; } if__end__4: ;
                    }
                } goto if__end__3; } if__end__3: ;
        } if__end__1: ;
    }
#line 3765 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (Checked_Type__equals(type, other_type)) {
#line 3765 "bootstrap/stage0/ReCode.code"
            {
#line 3766 "bootstrap/stage0/ReCode.code"
                Source_Location__warning(parsed_expression->super.super.location, String__create_from("Redundant cast"));
            } goto if__end__5; } if__end__5: ;
    }
#line 3768 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (!(can_cast)) {
#line 3768 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 3769 "bootstrap/stage0/ReCode.code"
                message = String__create_from("Cannot cast \"");
#line 3770 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, other_expression->type);
#line 3771 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" to \"");
#line 3772 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, type);
#line 3773 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\".");
#line 3774 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.super.location, message);
#line 3775 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__6; } if__end__6: ;
    }
#line 3777 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Cast_Expression__create(parsed_expression->super.super.location, type, other_expression));}

#line 3780 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_character_expression(struct Checker* self, struct Parsed_Character_Expression* parsed_expression) { struct Checked_Type* expression_type; char value;
#line 3781 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR));
#line 3782 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3783 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3786 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_dereference_expression(struct Checker* self, struct Parsed_Dereference_Expression* parsed_expression) { struct Checked_Expression* value_expression; struct Checked_Type* value_type;
#line 3787 "bootstrap/stage0/ReCode.code"
    value_expression = Checker__check_expression(self, parsed_expression->value_expression);
#line 3788 "bootstrap/stage0/ReCode.code"
    value_type = value_expression->type;
#line 3789 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (value_type->kind != Checked_Type_Kind__POINTER) {
#line 3789 "bootstrap/stage0/ReCode.code"
            {
#line 3790 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.location, String__create_from("Not a pointer value"));
#line 3791 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3793 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Dereference_Expression__create(parsed_expression->super.location, ((struct Checked_Pointer_Type*) value_type)->other_type, value_expression));}

#line 3796 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_divide_expression(struct Checker* self, struct Parsed_Divide_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3797 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3798 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3799 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3800 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3801 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3804 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_equals_expression(struct Checker* self, struct Parsed_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3805 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3806 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3807 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3808 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3811 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_expression(struct Checker* self, struct Parsed_Greater_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3812 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3813 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3814 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3815 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3816 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Greater_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3819 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_or_equals_expression(struct Checker* self, struct Parsed_Greater_Or_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3820 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3821 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3822 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3823 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3824 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3827 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_group_expression(struct Checker* self, struct Parsed_Group_Expression* parsed_expression) { struct Checked_Expression* other_expression;
#line 3828 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->other_expression);
#line 3829 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression));}

#line 3832 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_integer_expression(struct Checker* self, struct Parsed_Integer_Expression* parsed_expression) { struct Checked_Type* expression_type; uint64_t value;
#line 3833 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__I32));
#line 3834 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3835 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3838 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_expression(struct Checker* self, struct Parsed_Less_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3839 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3840 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3841 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3842 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3843 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Less_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3846 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_or_equals_expression(struct Checker* self, struct Parsed_Less_Or_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3847 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3848 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3849 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3850 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3851 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3854 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_and_expression(struct Checker* self, struct Parsed_Logic_And_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3855 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3856 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression->type, left_expression->location);
#line 3857 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3858 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3859 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3862 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_or_expression(struct Checker* self, struct Parsed_Logic_Or_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3863 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3864 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression->type, left_expression->location);
#line 3865 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3866 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3867 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3870 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_member_access_expression(struct Checker* self, struct Parsed_Member_Access_Expression* parsed_expression) { struct Checked_Expression* object_expression; struct Checked_Type* object_type;
#line 3871 "bootstrap/stage0/ReCode.code"
    object_expression = Checker__check_expression(self, parsed_expression->object_expression);
#line 3872 "bootstrap/stage0/ReCode.code"
    object_type = object_expression->type;
#line 3873 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (object_type->kind == Checked_Type_Kind__POINTER) {
#line 3873 "bootstrap/stage0/ReCode.code"
            {
#line 3874 "bootstrap/stage0/ReCode.code"
                object_type = ((struct Checked_Pointer_Type*) object_type)->other_type;
#line 3875 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3875 "bootstrap/stage0/ReCode.code"
                        {
#line 3876 "bootstrap/stage0/ReCode.code"
                            return Checker__check_struct_member_access_expression(self, object_expression, ((struct Checked_Struct_Type*) object_type), parsed_expression->member_name);
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 3878 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3878 "bootstrap/stage0/ReCode.code"
                {
#line 3879 "bootstrap/stage0/ReCode.code"
                    return Checker__check_struct_member_access_expression(self, object_expression, ((struct Checked_Struct_Type*) object_type), parsed_expression->member_name);
                } goto if__end__3; } if__else__3: ;
#line 3880 "bootstrap/stage0/ReCode.code"
            if__start__4: { if (object_type->kind == Checked_Type_Kind__DEFINED) {
#line 3880 "bootstrap/stage0/ReCode.code"
                    { struct Checked_Named_Type* defined_type;
#line 3881 "bootstrap/stage0/ReCode.code"
                        defined_type = ((struct Checked_Defined_Type*) object_type)->defined_type;
#line 3882 "bootstrap/stage0/ReCode.code"
                        if__start__5: { if (defined_type->super.kind == Checked_Type_Kind__ENUM) {
#line 3882 "bootstrap/stage0/ReCode.code"
                                { struct Checked_Enum_Type* enum_type; struct Checked_Enum_Member* enum_member;
#line 3883 "bootstrap/stage0/ReCode.code"
                                    enum_type = ((struct Checked_Enum_Type*) defined_type);
#line 3884 "bootstrap/stage0/ReCode.code"
                                    enum_member = Checked_Enum_Type__find_member(enum_type, parsed_expression->member_name->lexeme);
#line 3885 "bootstrap/stage0/ReCode.code"
                                    if__start__6: { if (enum_member == NULL) {
#line 3885 "bootstrap/stage0/ReCode.code"
                                            {
#line 3886 "bootstrap/stage0/ReCode.code"
                                                Source_Location__error(object_expression->location, String__create_from("No such enum members"));
#line 3887 "bootstrap/stage0/ReCode.code"
                                                abort();
                                            } goto if__end__6; } if__end__6: ;
                                    }
#line 3889 "bootstrap/stage0/ReCode.code"
                                    return ((struct Checked_Expression*) Checked_Symbol_Expression__create(object_expression->location, ((struct Checked_Type*) enum_type), enum_member->symbol));
                                } goto if__end__5; } if__end__5: ;
                        }
#line 3891 "bootstrap/stage0/ReCode.code"
                        Source_Location__error(object_expression->location, String__create_from("Type has no members"));
#line 3892 "bootstrap/stage0/ReCode.code"
                        abort();
                    } goto if__end__4; } if__end__4: ;
            } if__end__3: ;
        } if__end__1: ;
    }
#line 3894 "bootstrap/stage0/ReCode.code"
    Source_Location__error(object_expression->location, String__create_from("Unsupported type"));
#line 3895 "bootstrap/stage0/ReCode.code"
    abort();}

#line 3898 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_struct_member_access_expression(struct Checker* self, struct Checked_Expression* object_expression, struct Checked_Struct_Type* struct_type, struct Token* member_name) { struct Checked_Struct_Member* member;
#line 3899 "bootstrap/stage0/ReCode.code"
    member = Checked_Struct_Type__find_member(struct_type, member_name->lexeme);
#line 3900 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (member == NULL) {
#line 3900 "bootstrap/stage0/ReCode.code"
            {
#line 3901 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (struct_type->super_type != NULL) {
#line 3901 "bootstrap/stage0/ReCode.code"
                        {
#line 3902 "bootstrap/stage0/ReCode.code"
                            object_expression = ((struct Checked_Expression*) Checked_Member_Access_Expression__create(object_expression->location, struct_type->first_member->type, object_expression, struct_type->first_member));
#line 3903 "bootstrap/stage0/ReCode.code"
                            return Checker__check_struct_member_access_expression(self, object_expression, struct_type->super_type, member_name);
                        } goto if__end__2; } if__end__2: ;
                }
#line 3905 "bootstrap/stage0/ReCode.code"
                Source_Location__error(member_name->location, String__create_from("No such struct member"));
#line 3906 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3908 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Member_Access_Expression__create(object_expression->location, member->type, object_expression, member));}

#line 3911 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_minus_expression(struct Checker* self, struct Parsed_Minus_Expression* parsed_expression) { struct Checked_Expression* other_expression; struct Checked_Type* other_expression_type;
#line 3912 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3913 "bootstrap/stage0/ReCode.code"
    other_expression_type = other_expression->type;
#line 3914 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(other_expression_type, other_expression->location);
#line 3915 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression));}

#line 3918 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_modulo_expression(struct Checker* self, struct Parsed_Modulo_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3919 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3920 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3921 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3922 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3923 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3926 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_multiply_expression(struct Checker* self, struct Parsed_Multiply_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3927 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3928 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3929 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3930 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3931 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3934 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_expression(struct Checker* self, struct Parsed_Not_Expression* parsed_expression) { struct Checked_Expression* other_expression; struct Checked_Type* other_expression_type;
#line 3935 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3936 "bootstrap/stage0/ReCode.code"
    other_expression_type = other_expression->type;
#line 3937 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), other_expression_type, other_expression->location);
#line 3938 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression));}

#line 3941 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_equals_expression(struct Checker* self, struct Parsed_Not_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3942 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3943 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3944 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3945 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3948 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_null_expression(struct Checker* self, struct Parsed_Null_Expression* parsed_expression) { struct Checked_Type* expression_type;
#line 3949 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__NULL));
#line 3950 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type));}

#line 3953 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_sizeof_expression(struct Checker* self, struct Parsed_Sizeof_Expression* parsed_expression) { struct Checked_Type* expression_type; struct Checked_Type* sized_type;
#line 3954 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE));
#line 3955 "bootstrap/stage0/ReCode.code"
    sized_type = Checker__resolve_type(self, parsed_expression->type);
#line 3956 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type));}

#line 3959 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_string_expression(struct Checker* self, struct Parsed_String_Expression* parsed_expression) { struct Checked_Type* char_type; struct Checked_Type* expression_type; struct String* value;
#line 3960 "bootstrap/stage0/ReCode.code"
    char_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR));
#line 3961 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type));
#line 3962 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3963 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3966 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_substract_expression(struct Checker* self, struct Parsed_Substract_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3967 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3968 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3969 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3970 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3971 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3974 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_symbol_expression(struct Checker* self, struct Parsed_Symbol_Expression* parsed_expression) { struct Checked_Symbol* symbol;
#line 3975 "bootstrap/stage0/ReCode.code"
    symbol = Checked_Symbols__find_symbol(self->current_context->symbols, parsed_expression->name->lexeme);
#line 3976 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (symbol == NULL) {
#line 3976 "bootstrap/stage0/ReCode.code"
            {
#line 3977 "bootstrap/stage0/ReCode.code"
                Token__error(parsed_expression->name, String__create_from("Undefined symbol"));
#line 3978 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3980 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (symbol->type == NULL) {
#line 3980 "bootstrap/stage0/ReCode.code"
            {
#line 3981 "bootstrap/stage0/ReCode.code"
                Token__error(parsed_expression->name, String__create_from("Symbol without type"));
#line 3982 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__2; } if__end__2: ;
    }
#line 3984 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol));}

#line 3987 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_expression(struct Checker* self, struct Parsed_Expression* parsed_expression) {
#line 3988 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_expression->kind == Parsed_Expression_Kind__ADD) {
#line 3988 "bootstrap/stage0/ReCode.code"
            {
#line 3989 "bootstrap/stage0/ReCode.code"
                return Checker__check_add_expression(self, ((struct Parsed_Add_Expression*) parsed_expression));
            } goto if__end__1; } if__else__1: ;
#line 3990 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (parsed_expression->kind == Parsed_Expression_Kind__ADDRESS_OF) {
#line 3990 "bootstrap/stage0/ReCode.code"
                {
#line 3991 "bootstrap/stage0/ReCode.code"
                    return Checker__check_address_of_expression(self, ((struct Parsed_Address_Of_Expression*) parsed_expression));
                } goto if__end__2; } if__else__2: ;
#line 3992 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parsed_expression->kind == Parsed_Expression_Kind__ARRAY_ACCESS) {
#line 3992 "bootstrap/stage0/ReCode.code"
                    {
#line 3993 "bootstrap/stage0/ReCode.code"
                        return Checker__check_array_access_expression(self, ((struct Parsed_Array_Access_Expression*) parsed_expression));
                    } goto if__end__3; } if__else__3: ;
#line 3994 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (parsed_expression->kind == Parsed_Expression_Kind__BOOL) {
#line 3994 "bootstrap/stage0/ReCode.code"
                        {
#line 3995 "bootstrap/stage0/ReCode.code"
                            return Checker__check_bool_expression(self, ((struct Parsed_Bool_Expression*) parsed_expression));
                        } goto if__end__4; } if__else__4: ;
#line 3996 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (parsed_expression->kind == Parsed_Expression_Kind__CALL) {
#line 3996 "bootstrap/stage0/ReCode.code"
                            {
#line 3997 "bootstrap/stage0/ReCode.code"
                                return Checker__check_call_expression(self, ((struct Parsed_Call_Expression*) parsed_expression));
                            } goto if__end__5; } if__else__5: ;
#line 3998 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (parsed_expression->kind == Parsed_Expression_Kind__CAST) {
#line 3998 "bootstrap/stage0/ReCode.code"
                                {
#line 3999 "bootstrap/stage0/ReCode.code"
                                    return Checker__check_cast_expression(self, ((struct Parsed_Cast_Expression*) parsed_expression));
                                } goto if__end__6; } if__else__6: ;
#line 4000 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (parsed_expression->kind == Parsed_Expression_Kind__CHARACTER) {
#line 4000 "bootstrap/stage0/ReCode.code"
                                    {
#line 4001 "bootstrap/stage0/ReCode.code"
                                        return Checker__check_character_expression(self, ((struct Parsed_Character_Expression*) parsed_expression));
                                    } goto if__end__7; } if__else__7: ;
#line 4002 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (parsed_expression->kind == Parsed_Expression_Kind__DEREFERENCE) {
#line 4002 "bootstrap/stage0/ReCode.code"
                                        {
#line 4003 "bootstrap/stage0/ReCode.code"
                                            return Checker__check_dereference_expression(self, ((struct Parsed_Dereference_Expression*) parsed_expression));
                                        } goto if__end__8; } if__else__8: ;
#line 4004 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (parsed_expression->kind == Parsed_Expression_Kind__DIVIDE) {
#line 4004 "bootstrap/stage0/ReCode.code"
                                            {
#line 4005 "bootstrap/stage0/ReCode.code"
                                                return Checker__check_divide_expression(self, ((struct Parsed_Divide_Expression*) parsed_expression));
                                            } goto if__end__9; } if__else__9: ;
#line 4006 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (parsed_expression->kind == Parsed_Expression_Kind__EQUALS) {
#line 4006 "bootstrap/stage0/ReCode.code"
                                                {
#line 4007 "bootstrap/stage0/ReCode.code"
                                                    return Checker__check_equals_expression(self, ((struct Parsed_Equals_Expression*) parsed_expression));
                                                } goto if__end__10; } if__else__10: ;
#line 4008 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (parsed_expression->kind == Parsed_Expression_Kind__GREATER) {
#line 4008 "bootstrap/stage0/ReCode.code"
                                                    {
#line 4009 "bootstrap/stage0/ReCode.code"
                                                        return Checker__check_greater_expression(self, ((struct Parsed_Greater_Expression*) parsed_expression));
                                                    } goto if__end__11; } if__else__11: ;
#line 4010 "bootstrap/stage0/ReCode.code"
                                                if__start__12: { if (parsed_expression->kind == Parsed_Expression_Kind__GREATER_OR_EQUALS) {
#line 4010 "bootstrap/stage0/ReCode.code"
                                                        {
#line 4011 "bootstrap/stage0/ReCode.code"
                                                            return Checker__check_greater_or_equals_expression(self, ((struct Parsed_Greater_Or_Equals_Expression*) parsed_expression));
                                                        } goto if__end__12; } if__else__12: ;
#line 4012 "bootstrap/stage0/ReCode.code"
                                                    if__start__13: { if (parsed_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 4012 "bootstrap/stage0/ReCode.code"
                                                            {
#line 4013 "bootstrap/stage0/ReCode.code"
                                                                return Checker__check_group_expression(self, ((struct Parsed_Group_Expression*) parsed_expression));
                                                            } goto if__end__13; } if__else__13: ;
#line 4014 "bootstrap/stage0/ReCode.code"
                                                        if__start__14: { if (parsed_expression->kind == Parsed_Expression_Kind__INTEGER) {
#line 4014 "bootstrap/stage0/ReCode.code"
                                                                {
#line 4015 "bootstrap/stage0/ReCode.code"
                                                                    return Checker__check_integer_expression(self, ((struct Parsed_Integer_Expression*) parsed_expression));
                                                                } goto if__end__14; } if__else__14: ;
#line 4016 "bootstrap/stage0/ReCode.code"
                                                            if__start__15: { if (parsed_expression->kind == Parsed_Expression_Kind__LESS) {
#line 4016 "bootstrap/stage0/ReCode.code"
                                                                    {
#line 4017 "bootstrap/stage0/ReCode.code"
                                                                        return Checker__check_less_expression(self, ((struct Parsed_Less_Expression*) parsed_expression));
                                                                    } goto if__end__15; } if__else__15: ;
#line 4018 "bootstrap/stage0/ReCode.code"
                                                                if__start__16: { if (parsed_expression->kind == Parsed_Expression_Kind__LESS_OR_EQUALS) {
#line 4018 "bootstrap/stage0/ReCode.code"
                                                                        {
#line 4019 "bootstrap/stage0/ReCode.code"
                                                                            return Checker__check_less_or_equals_expression(self, ((struct Parsed_Less_Or_Equals_Expression*) parsed_expression));
                                                                        } goto if__end__16; } if__else__16: ;
#line 4020 "bootstrap/stage0/ReCode.code"
                                                                    if__start__17: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 4020 "bootstrap/stage0/ReCode.code"
                                                                            {
#line 4021 "bootstrap/stage0/ReCode.code"
                                                                                return Checker__check_logic_and_expression(self, ((struct Parsed_Logic_And_Expression*) parsed_expression));
                                                                            } goto if__end__17; } if__else__17: ;
#line 4022 "bootstrap/stage0/ReCode.code"
                                                                        if__start__18: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 4022 "bootstrap/stage0/ReCode.code"
                                                                                {
#line 4023 "bootstrap/stage0/ReCode.code"
                                                                                    return Checker__check_logic_or_expression(self, ((struct Parsed_Logic_Or_Expression*) parsed_expression));
                                                                                } goto if__end__18; } if__else__18: ;
#line 4024 "bootstrap/stage0/ReCode.code"
                                                                            if__start__19: { if (parsed_expression->kind == Parsed_Expression_Kind__MEMBER_ACCESS) {
#line 4024 "bootstrap/stage0/ReCode.code"
                                                                                    {
#line 4025 "bootstrap/stage0/ReCode.code"
                                                                                        return Checker__check_member_access_expression(self, ((struct Parsed_Member_Access_Expression*) parsed_expression));
                                                                                    } goto if__end__19; } if__else__19: ;
#line 4026 "bootstrap/stage0/ReCode.code"
                                                                                if__start__20: { if (parsed_expression->kind == Parsed_Expression_Kind__MINUS) {
#line 4026 "bootstrap/stage0/ReCode.code"
                                                                                        {
#line 4027 "bootstrap/stage0/ReCode.code"
                                                                                            return Checker__check_minus_expression(self, ((struct Parsed_Minus_Expression*) parsed_expression));
                                                                                        } goto if__end__20; } if__else__20: ;
#line 4028 "bootstrap/stage0/ReCode.code"
                                                                                    if__start__21: { if (parsed_expression->kind == Parsed_Expression_Kind__MODULO) {
#line 4028 "bootstrap/stage0/ReCode.code"
                                                                                            {
#line 4029 "bootstrap/stage0/ReCode.code"
                                                                                                return Checker__check_modulo_expression(self, ((struct Parsed_Modulo_Expression*) parsed_expression));
                                                                                            } goto if__end__21; } if__else__21: ;
#line 4030 "bootstrap/stage0/ReCode.code"
                                                                                        if__start__22: { if (parsed_expression->kind == Parsed_Expression_Kind__MULTIPLY) {
#line 4030 "bootstrap/stage0/ReCode.code"
                                                                                                {
#line 4031 "bootstrap/stage0/ReCode.code"
                                                                                                    return Checker__check_multiply_expression(self, ((struct Parsed_Multiply_Expression*) parsed_expression));
                                                                                                } goto if__end__22; } if__else__22: ;
#line 4032 "bootstrap/stage0/ReCode.code"
                                                                                            if__start__23: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) {
#line 4032 "bootstrap/stage0/ReCode.code"
                                                                                                    {
#line 4033 "bootstrap/stage0/ReCode.code"
                                                                                                        return Checker__check_not_expression(self, ((struct Parsed_Not_Expression*) parsed_expression));
                                                                                                    } goto if__end__23; } if__else__23: ;
#line 4034 "bootstrap/stage0/ReCode.code"
                                                                                                if__start__24: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT_EQUALS) {
#line 4034 "bootstrap/stage0/ReCode.code"
                                                                                                        {
#line 4035 "bootstrap/stage0/ReCode.code"
                                                                                                            return Checker__check_not_equals_expression(self, ((struct Parsed_Not_Equals_Expression*) parsed_expression));
                                                                                                        } goto if__end__24; } if__else__24: ;
#line 4036 "bootstrap/stage0/ReCode.code"
                                                                                                    if__start__25: { if (parsed_expression->kind == Parsed_Expression_Kind__NULL) {
#line 4036 "bootstrap/stage0/ReCode.code"
                                                                                                            {
#line 4037 "bootstrap/stage0/ReCode.code"
                                                                                                                return Checker__check_null_expression(self, ((struct Parsed_Null_Expression*) parsed_expression));
                                                                                                            } goto if__end__25; } if__else__25: ;
#line 4038 "bootstrap/stage0/ReCode.code"
                                                                                                        if__start__26: { if (parsed_expression->kind == Parsed_Expression_Kind__SIZEOF) {
#line 4038 "bootstrap/stage0/ReCode.code"
                                                                                                                {
#line 4039 "bootstrap/stage0/ReCode.code"
                                                                                                                    return Checker__check_sizeof_expression(self, ((struct Parsed_Sizeof_Expression*) parsed_expression));
                                                                                                                } goto if__end__26; } if__else__26: ;
#line 4040 "bootstrap/stage0/ReCode.code"
                                                                                                            if__start__27: { if (parsed_expression->kind == Parsed_Expression_Kind__STRING) {
#line 4040 "bootstrap/stage0/ReCode.code"
                                                                                                                    {
#line 4041 "bootstrap/stage0/ReCode.code"
                                                                                                                        return Checker__check_string_expression(self, ((struct Parsed_String_Expression*) parsed_expression));
                                                                                                                    } goto if__end__27; } if__else__27: ;
#line 4042 "bootstrap/stage0/ReCode.code"
                                                                                                                if__start__28: { if (parsed_expression->kind == Parsed_Expression_Kind__SUBSTRACT) {
#line 4042 "bootstrap/stage0/ReCode.code"
                                                                                                                        {
#line 4043 "bootstrap/stage0/ReCode.code"
                                                                                                                            return Checker__check_substract_expression(self, ((struct Parsed_Substract_Expression*) parsed_expression));
                                                                                                                        } goto if__end__28; } if__else__28: ;
#line 4044 "bootstrap/stage0/ReCode.code"
                                                                                                                    if__start__29: { if (parsed_expression->kind == Parsed_Expression_Kind__SYMBOL) {
#line 4044 "bootstrap/stage0/ReCode.code"
                                                                                                                            {
#line 4045 "bootstrap/stage0/ReCode.code"
                                                                                                                                return Checker__check_symbol_expression(self, ((struct Parsed_Symbol_Expression*) parsed_expression));
                                                                                                                            } goto if__end__29; } if__end__29: ;
                                                                                                                    } if__end__28: ;
                                                                                                                } if__end__27: ;
                                                                                                            } if__end__26: ;
                                                                                                        } if__end__25: ;
                                                                                                    } if__end__24: ;
                                                                                                } if__end__23: ;
                                                                                            } if__end__22: ;
                                                                                        } if__end__21: ;
                                                                                    } if__end__20: ;
                                                                                } if__end__19: ;
                                                                            } if__end__18: ;
                                                                        } if__end__17: ;
                                                                    } if__end__16: ;
                                                                } if__end__15: ;
                                                            } if__end__14: ;
                                                        } if__end__13: ;
                                                    } if__end__12: ;
                                                } if__end__11: ;
                                            } if__end__10: ;
                                        } if__end__9: ;
                                    } if__end__8: ;
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }
#line 4047 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_expression->location, String__append_i16(String__create_from("Unsupported expression kind: "), ((int16_t) parsed_expression->kind)));
#line 4048 "bootstrap/stage0/ReCode.code"
    abort();}

#line 4051 "bootstrap/stage0/ReCode.code"
void Checker__check_enum_statement(struct Checker* self, struct Parsed_Enum_Statement* parsed_statement) { struct Checked_Enum_Type* enum_type; struct Checked_Enum_Member* last_enum_member; struct Parsed_Enum_Member* parsed_enum_member;
#line 4052 "bootstrap/stage0/ReCode.code"
    enum_type = Checked_Enum_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4053 "bootstrap/stage0/ReCode.code"
    Checker__append_type(self, ((struct Checked_Named_Type*) enum_type));
#line 4055 "bootstrap/stage0/ReCode.code"
    last_enum_member = NULL;
#line 4056 "bootstrap/stage0/ReCode.code"
    parsed_enum_member = parsed_statement->first_member;
#line 4057 "bootstrap/stage0/ReCode.code"
    while (parsed_enum_member != NULL) { struct Checked_Enum_Member* enum_member; struct String* enum_member_symbol_name;
#line 4058 "bootstrap/stage0/ReCode.code"
        enum_member = Checked_Enum_Member__create(parsed_enum_member->name->location, parsed_enum_member->name->lexeme);
#line 4059 "bootstrap/stage0/ReCode.code"
        enum_member_symbol_name = String__append_string(String__append_cstring(String__append_string(String__create(), enum_type->super.name), "__"), enum_member->name);
#line 4060 "bootstrap/stage0/ReCode.code"
        enum_member->symbol = ((struct Checked_Symbol*) Checked_Enum_Member_Symbol__create(enum_member->location, enum_member_symbol_name, ((struct Checked_Type*) enum_type)));
#line 4061 "bootstrap/stage0/ReCode.code"
        Checked_Symbols__append_symbol(self->root_context->symbols, enum_member->symbol);
#line 4062 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (last_enum_member == NULL) {
#line 4062 "bootstrap/stage0/ReCode.code"
                {
#line 4063 "bootstrap/stage0/ReCode.code"
                    enum_type->first_member = enum_member;
                } goto if__end__1; } if__else__1: ;
#line 4064 "bootstrap/stage0/ReCode.code"
            {
#line 4065 "bootstrap/stage0/ReCode.code"
                last_enum_member->next_member = enum_member;
            } if__end__1: ;
        }
#line 4067 "bootstrap/stage0/ReCode.code"
        last_enum_member = enum_member;
#line 4068 "bootstrap/stage0/ReCode.code"
        parsed_enum_member = parsed_enum_member->next_member;
    }}

#line 4072 "bootstrap/stage0/ReCode.code"
void Checker__create_opaque_type(struct Checker* self, struct Parsed_Opaque_Type_Statement* parsed_statement) { struct Checked_Named_Type* other_type;
#line 4073 "bootstrap/stage0/ReCode.code"
    other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4074 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type != NULL) {
#line 4074 "bootstrap/stage0/ReCode.code"
            {
#line 4075 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4076 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__else__1: ;
#line 4077 "bootstrap/stage0/ReCode.code"
        { struct Checked_Opaque_Type* opaque_type;
#line 4078 "bootstrap/stage0/ReCode.code"
            opaque_type = Checked_Opaque_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4079 "bootstrap/stage0/ReCode.code"
            Checker__append_type(self, ((struct Checked_Named_Type*) opaque_type));
        } if__end__1: ;
    }}

#line 4083 "bootstrap/stage0/ReCode.code"
void Checker__create_struct_type(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) { struct Checked_Named_Type* other_type;
#line 4084 "bootstrap/stage0/ReCode.code"
    other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4085 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type != NULL) {
#line 4085 "bootstrap/stage0/ReCode.code"
            {
#line 4086 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4087 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__else__1: ;
#line 4088 "bootstrap/stage0/ReCode.code"
        { struct Checked_Struct_Type* struct_type;
#line 4089 "bootstrap/stage0/ReCode.code"
            struct_type = Checked_Struct_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4090 "bootstrap/stage0/ReCode.code"
            Checker__append_type(self, ((struct Checked_Named_Type*) struct_type));
        } if__end__1: ;
    }}

#line 4094 "bootstrap/stage0/ReCode.code"
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) { struct Checked_Struct_Type* struct_type;
#line 4095 "bootstrap/stage0/ReCode.code"
    struct_type = ((struct Checked_Struct_Type*) Checker__find_type(self, parsed_statement->super.name->lexeme));
#line 4096 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->first_member != NULL) {
#line 4096 "bootstrap/stage0/ReCode.code"
            { struct Checked_Struct_Member* last_struct_member; struct Parsed_Struct_Member* parsed_member;
#line 4097 "bootstrap/stage0/ReCode.code"
                last_struct_member = NULL;
#line 4098 "bootstrap/stage0/ReCode.code"
                parsed_member = parsed_statement->first_member;
#line 4099 "bootstrap/stage0/ReCode.code"
                while (parsed_member != NULL) { struct Checked_Struct_Member* struct_member; struct Checked_Type* struct_member_type;
#line 4100 "bootstrap/stage0/ReCode.code"
                    struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
#line 4101 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (struct_member != NULL) {
#line 4101 "bootstrap/stage0/ReCode.code"
                            {
#line 4102 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_member->name->location, String__append_source_location(String__create_from("Struct member declared first here: "), struct_member->location));
#line 4103 "bootstrap/stage0/ReCode.code"
                                abort();
                            } goto if__end__2; } if__end__2: ;
                    }
#line 4105 "bootstrap/stage0/ReCode.code"
                    struct_member_type = Checker__resolve_type(self, parsed_member->type);
#line 4106 "bootstrap/stage0/ReCode.code"
                    struct_member = Checked_Struct_Member__create(parsed_member->name->location, parsed_member->name->lexeme, struct_member_type);
#line 4107 "bootstrap/stage0/ReCode.code"
                    if__start__3: { if (String__equals_cstring(struct_member->name, "super")) {
#line 4107 "bootstrap/stage0/ReCode.code"
                            { struct Checked_Struct_Type* struct_super_type; struct Checked_Struct_Type* other_struct_type;
#line 4108 "bootstrap/stage0/ReCode.code"
                                if__start__4: { if (struct_type->first_member != NULL) {
#line 4108 "bootstrap/stage0/ReCode.code"
                                        {
#line 4109 "bootstrap/stage0/ReCode.code"
                                            Source_Location__error(parsed_member->name->location, String__create_from("Must be the first struct member"));
#line 4110 "bootstrap/stage0/ReCode.code"
                                            abort();
                                        } goto if__end__4; } if__end__4: ;
                                }
#line 4112 "bootstrap/stage0/ReCode.code"
                                if__start__5: { if (struct_member->type->kind != Checked_Type_Kind__STRUCT) {
#line 4112 "bootstrap/stage0/ReCode.code"
                                        {
#line 4113 "bootstrap/stage0/ReCode.code"
                                            Source_Location__error(parsed_member->type->location, String__create_from("Must be a struct"));
#line 4114 "bootstrap/stage0/ReCode.code"
                                            abort();
                                        } goto if__end__5; } if__end__5: ;
                                }
#line 4116 "bootstrap/stage0/ReCode.code"
                                struct_super_type = ((struct Checked_Struct_Type*) struct_member->type);
#line 4117 "bootstrap/stage0/ReCode.code"
                                other_struct_type = struct_super_type;
#line 4118 "bootstrap/stage0/ReCode.code"
                                while (other_struct_type != NULL) {
#line 4119 "bootstrap/stage0/ReCode.code"
                                    if__start__6: { if (other_struct_type == struct_type) {
#line 4119 "bootstrap/stage0/ReCode.code"
                                            {
#line 4120 "bootstrap/stage0/ReCode.code"
                                                Source_Location__error(parsed_member->type->location, String__create_from("Type recursivity"));
#line 4121 "bootstrap/stage0/ReCode.code"
                                                abort();
                                            } goto if__end__6; } if__end__6: ;
                                    }
#line 4123 "bootstrap/stage0/ReCode.code"
                                    other_struct_type = other_struct_type->super_type;
                                }
#line 4125 "bootstrap/stage0/ReCode.code"
                                struct_type->super_type = struct_super_type;
                            } goto if__end__3; } if__end__3: ;
                    }
#line 4127 "bootstrap/stage0/ReCode.code"
                    if__start__7: { if (last_struct_member == NULL) {
#line 4127 "bootstrap/stage0/ReCode.code"
                            {
#line 4128 "bootstrap/stage0/ReCode.code"
                                struct_type->first_member = struct_member;
                            } goto if__end__7; } if__else__7: ;
#line 4129 "bootstrap/stage0/ReCode.code"
                        {
#line 4130 "bootstrap/stage0/ReCode.code"
                            last_struct_member->next_member = struct_member;
                        } if__end__7: ;
                    }
#line 4132 "bootstrap/stage0/ReCode.code"
                    last_struct_member = struct_member;
#line 4133 "bootstrap/stage0/ReCode.code"
                    parsed_member = parsed_member->next_member;
                }
            } goto if__end__1; } if__end__1: ;
    }}

#line 4138 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement) { struct Checked_Expression* object_expression; struct Checked_Expression* value_expression;
#line 4139 "bootstrap/stage0/ReCode.code"
    object_expression = Checker__check_expression(self, parsed_statement->object_expression);
#line 4140 "bootstrap/stage0/ReCode.code"
    value_expression = Checker__check_expression(self, parsed_statement->value_expression);
#line 4141 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(object_expression->type, value_expression->type, value_expression->location);
#line 4142 "bootstrap/stage0/ReCode.code"
    return Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);}

#line 4145 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement) { struct Checker_Context* context;
#line 4146 "bootstrap/stage0/ReCode.code"
    context = Checker_Context__create(self->current_context);
#line 4147 "bootstrap/stage0/ReCode.code"
    self->current_context = context;
#line 4148 "bootstrap/stage0/ReCode.code"
    Checker__check_statements(self, parsed_statement->statements);
#line 4149 "bootstrap/stage0/ReCode.code"
    self->current_context = context->parent;
#line 4150 "bootstrap/stage0/ReCode.code"
    return Checked_Block_Statement__create(parsed_statement->super.location, context, NULL);}

#line 4153 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement) {
#line 4154 "bootstrap/stage0/ReCode.code"
    return Checked_Break_Statement__create(parsed_statement->super.location);}

#line 4157 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement) { struct Checked_Expression* expression;
#line 4158 "bootstrap/stage0/ReCode.code"
    expression = Checker__check_expression(self, parsed_statement->expression);
#line 4159 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Checked_Type__equals(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__VOID)), expression->type))) {
#line 4159 "bootstrap/stage0/ReCode.code"
            {
            } goto if__end__1; } if__end__1: ;
    }
#line 4162 "bootstrap/stage0/ReCode.code"
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);}

#line 4165 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement) { int16_t labels_count; struct String* wrapper_label; struct String* wrapper_end_label; struct String* then_label; struct String* else_label; struct Checker_Context* wrapper_context; struct Checked_Block_Statement* wrapper_block; struct Checked_Block_Statement* then_block; struct Checker_Context* current_context;
#line 4166 "bootstrap/stage0/ReCode.code"
    labels_count = Counter__next(self->current_context->function_counter);
#line 4167 "bootstrap/stage0/ReCode.code"
    wrapper_label = String__append_i16(String__create_from("if__start__"), labels_count);
#line 4168 "bootstrap/stage0/ReCode.code"
    wrapper_end_label = String__append_i16(String__create_from("if__end__"), labels_count);
#line 4169 "bootstrap/stage0/ReCode.code"
    then_label = String__append_i16(String__create_from("if__then__"), labels_count);
#line 4170 "bootstrap/stage0/ReCode.code"
    else_label = wrapper_end_label;
#line 4171 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->false_statement != NULL) {
#line 4171 "bootstrap/stage0/ReCode.code"
            {
#line 4172 "bootstrap/stage0/ReCode.code"
                else_label = String__append_i16(String__create_from("if__else__"), labels_count);
            } goto if__end__1; } if__end__1: ;
    }
#line 4175 "bootstrap/stage0/ReCode.code"
    wrapper_context = Checker_Context__create(self->current_context);
#line 4176 "bootstrap/stage0/ReCode.code"
    self->current_context = wrapper_context;
#line 4178 "bootstrap/stage0/ReCode.code"
    wrapper_block = Checked_Block_Statement__create(parsed_statement->super.location, wrapper_context, wrapper_label);
#line 4180 "bootstrap/stage0/ReCode.code"
    then_block = Checker__check_if_condition(self, parsed_statement->condition_expression, then_label, else_label);
#line 4182 "bootstrap/stage0/ReCode.code"
    current_context = self->current_context;
#line 4183 "bootstrap/stage0/ReCode.code"
    self->current_context = then_block->context;
#line 4184 "bootstrap/stage0/ReCode.code"
    Checked_Statements__append(then_block->context->statements, Checker__check_statement(self, parsed_statement->true_statement));
#line 4185 "bootstrap/stage0/ReCode.code"
    Checked_Statements__append(then_block->context->statements, ((struct Checked_Statement*) Checked_Goto_Statement__create(NULL, wrapper_end_label)));
#line 4186 "bootstrap/stage0/ReCode.code"
    self->current_context = current_context;
#line 4188 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (parsed_statement->false_statement != NULL) {
#line 4188 "bootstrap/stage0/ReCode.code"
            {
#line 4189 "bootstrap/stage0/ReCode.code"
                Checked_Statements__append(wrapper_block->context->statements, ((struct Checked_Statement*) Checked_Label_Statement__create(NULL, else_label)));
#line 4190 "bootstrap/stage0/ReCode.code"
                Checked_Statements__append(wrapper_block->context->statements, Checker__check_statement(self, parsed_statement->false_statement));
            } goto if__end__2; } if__end__2: ;
    }
#line 4193 "bootstrap/stage0/ReCode.code"
    Checked_Statements__append(wrapper_block->context->statements, ((struct Checked_Statement*) Checked_Label_Statement__create(NULL, wrapper_end_label)));
#line 4195 "bootstrap/stage0/ReCode.code"
    self->current_context = wrapper_context->parent;
#line 4197 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Statement*) wrapper_block);}

#line 4201 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checker__check_if_condition(struct Checker* self, struct Parsed_Expression* parsed_expression, struct String* then_label, struct String* else_label) { struct Checker_Context* initial_context; struct Checked_Block_Statement* then_block;
#line 4202 "bootstrap/stage0/ReCode.code"
    initial_context = self->current_context;
#line 4203 "bootstrap/stage0/ReCode.code"
    ;
#line 4204 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 4204 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Logic_And_Expression* parsed_binary_expression; struct Checked_Block_Statement* first_expression_block;
#line 4205 "bootstrap/stage0/ReCode.code"
                parsed_binary_expression = ((struct Parsed_Logic_And_Expression*) parsed_expression);
#line 4206 "bootstrap/stage0/ReCode.code"
                first_expression_block = Checker__check_if_condition(self, parsed_binary_expression->super.left_expression, then_label, else_label);
#line 4207 "bootstrap/stage0/ReCode.code"
                self->current_context = first_expression_block->context;
#line 4208 "bootstrap/stage0/ReCode.code"
                then_block = Checker__check_if_condition(self, parsed_binary_expression->super.right_expression, then_label, else_label);
            } goto if__end__1; } if__else__1: ;
#line 4209 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 4209 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Logic_Or_Expression* parsed_binary_expression; struct String* new_then_label; struct Checked_Block_Statement* first_expression_block; struct Checked_Block_Statement* second_expression_block;
#line 4210 "bootstrap/stage0/ReCode.code"
                    parsed_binary_expression = ((struct Parsed_Logic_Or_Expression*) parsed_expression);
#line 4211 "bootstrap/stage0/ReCode.code"
                    new_then_label = String__append_i16(String__append_cstring(String__append_string(String__create(), then_label), "__"), Counter__next(self->current_context->function_counter));
#line 4212 "bootstrap/stage0/ReCode.code"
                    first_expression_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.left_expression)), else_label, new_then_label);
#line 4213 "bootstrap/stage0/ReCode.code"
                    self->current_context = first_expression_block->context;
#line 4214 "bootstrap/stage0/ReCode.code"
                    second_expression_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.right_expression)), else_label, new_then_label);
#line 4215 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(second_expression_block->context->statements, ((struct Checked_Statement*) Checked_Goto_Statement__create(NULL, else_label)));
#line 4216 "bootstrap/stage0/ReCode.code"
                    then_block = Checked_Block_Statement__create(NULL, Checker_Context__create(initial_context), new_then_label);
#line 4217 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(initial_context->statements, ((struct Checked_Statement*) then_block));
                } goto if__end__2; } if__else__2: ;
#line 4218 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parsed_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 4218 "bootstrap/stage0/ReCode.code"
                    {
#line 4219 "bootstrap/stage0/ReCode.code"
                        then_block = Checker__check_if_condition(self, ((struct Parsed_Group_Expression*) parsed_expression)->other_expression, then_label, else_label);
                    } goto if__end__3; } if__else__3: ;
#line 4220 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 4220 "bootstrap/stage0/ReCode.code"
                            {
#line 4221 "bootstrap/stage0/ReCode.code"
                                then_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, ((struct Parsed_Group_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression)->other_expression)), then_label, else_label);
                            } goto if__end__4; } } if__else__4: ;
#line 4222 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__NOT) {
#line 4222 "bootstrap/stage0/ReCode.code"
                                {
#line 4223 "bootstrap/stage0/ReCode.code"
                                    then_block = Checker__check_if_condition(self, ((struct Parsed_Not_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression)->super.other_expression, then_label, else_label);
                                } goto if__end__5; } } if__else__5: ;
#line 4224 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 4224 "bootstrap/stage0/ReCode.code"
                                    { struct Parsed_Logic_Or_Expression* parsed_binary_expression;
#line 4225 "bootstrap/stage0/ReCode.code"
                                        parsed_binary_expression = ((struct Parsed_Logic_Or_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression);
#line 4226 "bootstrap/stage0/ReCode.code"
                                        then_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Logic_And_Expression__create(((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.left_expression)), ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.right_expression)))), then_label, else_label);
                                    } goto if__end__6; } } if__else__6: ;
#line 4227 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 4227 "bootstrap/stage0/ReCode.code"
                                        { struct Parsed_Logic_And_Expression* parsed_binary_expression;
#line 4228 "bootstrap/stage0/ReCode.code"
                                            parsed_binary_expression = ((struct Parsed_Logic_And_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression);
#line 4229 "bootstrap/stage0/ReCode.code"
                                            then_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Logic_Or_Expression__create(((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.left_expression)), ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.right_expression)))), then_label, else_label);
                                        } goto if__end__7; } } if__else__7: ;
#line 4230 "bootstrap/stage0/ReCode.code"
                                { struct Checked_Expression* checked_expression;
#line 4231 "bootstrap/stage0/ReCode.code"
                                    checked_expression = Checker__check_expression(self, parsed_expression);
#line 4232 "bootstrap/stage0/ReCode.code"
                                    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), checked_expression->type, checked_expression->location);
#line 4233 "bootstrap/stage0/ReCode.code"
                                    then_block = Checked_Block_Statement__create(NULL, Checker_Context__create(self->current_context), NULL);
#line 4234 "bootstrap/stage0/ReCode.code"
                                    Checked_Statements__append(self->current_context->statements, ((struct Checked_Statement*) Checked_If_Statement__create(NULL, checked_expression, ((struct Checked_Statement*) then_block), NULL)));
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }
#line 4236 "bootstrap/stage0/ReCode.code"
    self->current_context = initial_context;
#line 4237 "bootstrap/stage0/ReCode.code"
    return then_block;}

#line 4240 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement) { struct Checked_Expression* expression;
#line 4241 "bootstrap/stage0/ReCode.code"
    expression = NULL;
#line 4242 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->expression != NULL) {
#line 4242 "bootstrap/stage0/ReCode.code"
            {
#line 4243 "bootstrap/stage0/ReCode.code"
                expression = Checker__check_expression(self, parsed_statement->expression);
#line 4244 "bootstrap/stage0/ReCode.code"
                Checked_Type__expect_same_type(self->current_context->function_return_type, expression->type, expression->location);
            } goto if__end__1; } if__else__1: ;
#line 4245 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (self->current_context->function_return_type->kind != Checked_Type_Kind__VOID) {
#line 4245 "bootstrap/stage0/ReCode.code"
                {
#line 4246 "bootstrap/stage0/ReCode.code"
                    Source_Location__error(parsed_statement->super.location, String__create_from("Missing expression"));
#line 4247 "bootstrap/stage0/ReCode.code"
                    abort();
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 4249 "bootstrap/stage0/ReCode.code"
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);}

#line 4252 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement) { struct Checked_Type* type; struct Checked_Expression* expression; struct Checked_Variable_Symbol* variable;
#line 4253 "bootstrap/stage0/ReCode.code"
    type = NULL;
#line 4254 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->type != NULL) {
#line 4254 "bootstrap/stage0/ReCode.code"
            {
#line 4255 "bootstrap/stage0/ReCode.code"
                type = Checker__resolve_type(self, parsed_statement->type);
#line 4256 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (type->kind == Checked_Type_Kind__OPAQUE) {
#line 4256 "bootstrap/stage0/ReCode.code"
                        {
#line 4257 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(parsed_statement->super.super.location, String__create_from("Variable cannot have an opaque type"));
#line 4258 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 4261 "bootstrap/stage0/ReCode.code"
    expression = NULL;
#line 4262 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (parsed_statement->expression != NULL) {
#line 4262 "bootstrap/stage0/ReCode.code"
            {
#line 4263 "bootstrap/stage0/ReCode.code"
                expression = Checker__check_expression(self, parsed_statement->expression);
#line 4264 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (type != NULL) {
#line 4264 "bootstrap/stage0/ReCode.code"
                        {
#line 4265 "bootstrap/stage0/ReCode.code"
                            Checked_Type__expect_same_type(type, expression->type, expression->location);
#line 4266 "bootstrap/stage0/ReCode.code"
                            if__start__5: { if (expression->type->kind != Checked_Type_Kind__NULL) {
#line 4266 "bootstrap/stage0/ReCode.code"
                                    {
#line 4267 "bootstrap/stage0/ReCode.code"
                                        Source_Location__warning(parsed_statement->type->location, String__create_from("Redundant type declaration"));
                                    } goto if__end__5; } if__end__5: ;
                            }
                        } goto if__end__4; } if__else__4: ;
#line 4269 "bootstrap/stage0/ReCode.code"
                    {
#line 4270 "bootstrap/stage0/ReCode.code"
                        type = expression->type;
                    } if__end__4: ;
                }
            } goto if__end__3; } if__end__3: ;
    }
#line 4273 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (!(type == NULL)) { if (!(type->kind == Checked_Type_Kind__NULL)) { goto if__end__6; } } if__then__6__7: {
#line 4273 "bootstrap/stage0/ReCode.code"
            {
#line 4274 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_statement->super.super.location, String__create_from("Unknown variable type"));
#line 4275 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__6; } if__end__6: ;
    }
#line 4277 "bootstrap/stage0/ReCode.code"
    variable = Checked_Variable__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
#line 4278 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->current_context->symbols, ((struct Checked_Symbol*) variable));
#line 4279 "bootstrap/stage0/ReCode.code"
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);}

#line 4282 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement) { struct Checked_Expression* condition_expression; struct Checked_Statement* body_statement;
#line 4283 "bootstrap/stage0/ReCode.code"
    condition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4284 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), condition_expression->type, condition_expression->location);
#line 4285 "bootstrap/stage0/ReCode.code"
    body_statement = Checker__check_statement(self, parsed_statement->body_statement);
#line 4286 "bootstrap/stage0/ReCode.code"
    return Checked_While_Statement__create(parsed_statement->super.location, condition_expression, body_statement);}

#line 4289 "bootstrap/stage0/ReCode.code"
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) { struct String* function_name; struct Checked_Type* function_return_type; struct Checked_Function_Parameter* function_first_parameter; struct Parsed_Function_Parameter* parsed_parameter; struct Checked_Function_Type* function_type; struct Checked_Symbol* other_symbol;
#line 4290 "bootstrap/stage0/ReCode.code"
    function_name = parsed_statement->super.name->lexeme;
#line 4291 "bootstrap/stage0/ReCode.code"
    function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 4292 "bootstrap/stage0/ReCode.code"
    function_first_parameter = NULL;
#line 4293 "bootstrap/stage0/ReCode.code"
    parsed_parameter = parsed_statement->first_parameter;
#line 4294 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_parameter != NULL) {
#line 4294 "bootstrap/stage0/ReCode.code"
            { struct Checked_Function_Parameter* function_last_parameter;
#line 4295 "bootstrap/stage0/ReCode.code"
                function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->location, parsed_parameter->name, Checker__resolve_type(self, parsed_parameter->type));
#line 4296 "bootstrap/stage0/ReCode.code"
                function_last_parameter = function_first_parameter;
#line 4297 "bootstrap/stage0/ReCode.code"
                parsed_parameter = parsed_parameter->next_parameter;
#line 4298 "bootstrap/stage0/ReCode.code"
                while (parsed_parameter != NULL) { struct Checked_Function_Parameter* function_parameter;
#line 4299 "bootstrap/stage0/ReCode.code"
                    function_parameter = Checked_Function_Parameter__create(parsed_parameter->location, parsed_parameter->name, Checker__resolve_type(self, parsed_parameter->type));
#line 4300 "bootstrap/stage0/ReCode.code"
                    function_last_parameter->next_parameter = function_parameter;
#line 4301 "bootstrap/stage0/ReCode.code"
                    function_last_parameter = function_parameter;
#line 4302 "bootstrap/stage0/ReCode.code"
                    parsed_parameter = parsed_parameter->next_parameter;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 4305 "bootstrap/stage0/ReCode.code"
    function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_first_parameter, function_return_type);
#line 4307 "bootstrap/stage0/ReCode.code"
    other_symbol = Checked_Symbols__find_sibling_symbol(self->root_context->symbols, function_name);
#line 4308 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (other_symbol != NULL) {
#line 4308 "bootstrap/stage0/ReCode.code"
            {
#line 4309 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (!(other_symbol->kind != Checked_Symbol_Kind__FUNCTION)) { if (Checked_Type__equals(((struct Checked_Type*) function_type), ((struct Checked_Type*) ((struct Checked_Function_Symbol*) other_symbol)->function_type))) { goto if__else__3; } } if__then__3__4: {
#line 4309 "bootstrap/stage0/ReCode.code"
                        {
#line 4310 "bootstrap/stage0/ReCode.code"
                            TODO("Report overloaded function");
#line 4311 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__3; } if__else__3: ;
#line 4312 "bootstrap/stage0/ReCode.code"
                    {
#line 4313 "bootstrap/stage0/ReCode.code"
                        Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Function declared first here: "), other_symbol->location));
#line 4314 "bootstrap/stage0/ReCode.code"
                        abort();
                    } if__end__3: ;
                }
            } goto if__end__2; } if__else__2: ;
#line 4316 "bootstrap/stage0/ReCode.code"
        {
#line 4317 "bootstrap/stage0/ReCode.code"
            Checked_Symbols__append_symbol(self->root_context->symbols, ((struct Checked_Symbol*) Checked_Function_Symbol__create(parsed_statement->super.name->location, function_name, function_type)));
        } if__end__2: ;
    }}

#line 4321 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement) {
#line 4322 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->kind == Parsed_Statement_Kind__ASSIGNMENT) {
#line 4322 "bootstrap/stage0/ReCode.code"
            {
#line 4323 "bootstrap/stage0/ReCode.code"
                return ((struct Checked_Statement*) Checker__check_assignment_statement(self, ((struct Parsed_Assignment_Statement*) parsed_statement)));
            } goto if__end__1; } if__else__1: ;
#line 4324 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (parsed_statement->kind == Parsed_Statement_Kind__BLOCK) {
#line 4324 "bootstrap/stage0/ReCode.code"
                {
#line 4325 "bootstrap/stage0/ReCode.code"
                    return ((struct Checked_Statement*) Checker__check_block_statement(self, ((struct Parsed_Block_Statement*) parsed_statement)));
                } goto if__end__2; } if__else__2: ;
#line 4326 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parsed_statement->kind == Parsed_Statement_Kind__BREAK) {
#line 4326 "bootstrap/stage0/ReCode.code"
                    {
#line 4327 "bootstrap/stage0/ReCode.code"
                        return ((struct Checked_Statement*) Checker__check_break_statement(self, ((struct Parsed_Break_Statement*) parsed_statement)));
                    } goto if__end__3; } if__else__3: ;
#line 4328 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (parsed_statement->kind == Parsed_Statement_Kind__EXPRESSION) {
#line 4328 "bootstrap/stage0/ReCode.code"
                        {
#line 4329 "bootstrap/stage0/ReCode.code"
                            return ((struct Checked_Statement*) Checker__check_expression_statement(self, ((struct Parsed_Expression_Statement*) parsed_statement)));
                        } goto if__end__4; } if__else__4: ;
#line 4330 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (parsed_statement->kind == Parsed_Statement_Kind__IF) {
#line 4330 "bootstrap/stage0/ReCode.code"
                            {
#line 4331 "bootstrap/stage0/ReCode.code"
                                return Checker__check_if_statement(self, ((struct Parsed_If_Statement*) parsed_statement));
                            } goto if__end__5; } if__else__5: ;
#line 4332 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (parsed_statement->kind == Parsed_Statement_Kind__RETURN) {
#line 4332 "bootstrap/stage0/ReCode.code"
                                {
#line 4333 "bootstrap/stage0/ReCode.code"
                                    return ((struct Checked_Statement*) Checker__check_return_statement(self, ((struct Parsed_Return_Statement*) parsed_statement)));
                                } goto if__end__6; } if__else__6: ;
#line 4334 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4334 "bootstrap/stage0/ReCode.code"
                                    {
#line 4335 "bootstrap/stage0/ReCode.code"
                                        return ((struct Checked_Statement*) Checker__check_variable_statement(self, ((struct Parsed_Variable_Statement*) parsed_statement)));
                                    } goto if__end__7; } if__else__7: ;
#line 4336 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (parsed_statement->kind == Parsed_Statement_Kind__WHILE) {
#line 4336 "bootstrap/stage0/ReCode.code"
                                        {
#line 4337 "bootstrap/stage0/ReCode.code"
                                            return ((struct Checked_Statement*) Checker__check_while_statement(self, ((struct Parsed_While_Statement*) parsed_statement)));
                                        } goto if__end__8; } if__end__8: ;
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }
#line 4339 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4340 "bootstrap/stage0/ReCode.code"
    abort();}

#line 4343 "bootstrap/stage0/ReCode.code"
void Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements) { struct Parsed_Statement* parsed_statement;
#line 4344 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_statements->first_statement;
#line 4345 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) { struct Checked_Statement* checked_statement;
#line 4346 "bootstrap/stage0/ReCode.code"
        checked_statement = Checker__check_statement(self, parsed_statement);
#line 4347 "bootstrap/stage0/ReCode.code"
        Checked_Statements__append(self->current_context->statements, checked_statement);
#line 4348 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }}

#line 4352 "bootstrap/stage0/ReCode.code"
void Checker__check_function_definition(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) { struct Checked_Symbol* symbol; struct Checked_Function_Symbol* function_symbol; struct Checked_Function_Type* function_type; struct Checker_Context* function_context; struct Checker_Context* context;
#line 4353 "bootstrap/stage0/ReCode.code"
    symbol = Checked_Symbols__find_sibling_symbol(self->root_context->symbols, parsed_statement->super.name->lexeme);
#line 4354 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(symbol == NULL)) { if (!(symbol->kind != Checked_Symbol_Kind__FUNCTION)) { goto if__end__1; } } if__then__1__2: {
#line 4354 "bootstrap/stage0/ReCode.code"
            {
#line 4355 "bootstrap/stage0/ReCode.code"
                TODO("Report missing function symbol");
#line 4356 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 4358 "bootstrap/stage0/ReCode.code"
    function_symbol = ((struct Checked_Function_Symbol*) symbol);
#line 4359 "bootstrap/stage0/ReCode.code"
    function_type = function_symbol->function_type;
#line 4361 "bootstrap/stage0/ReCode.code"
    function_context = Checker_Context__create(self->current_context);
#line 4362 "bootstrap/stage0/ReCode.code"
    function_context->function_return_type = function_type->return_type;
#line 4363 "bootstrap/stage0/ReCode.code"
    Counter__reset(function_context->function_counter);
#line 4365 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (function_type->first_parameter != NULL) {
#line 4365 "bootstrap/stage0/ReCode.code"
            { struct Checked_Function_Parameter* parameter;
#line 4367 "bootstrap/stage0/ReCode.code"
                parameter = function_type->first_parameter;
#line 4368 "bootstrap/stage0/ReCode.code"
                while (parameter != NULL) {
#line 4369 "bootstrap/stage0/ReCode.code"
                    Checked_Symbols__append_symbol(function_context->symbols, ((struct Checked_Symbol*) Checked_Function_Parameter_Symbol__create(parameter->location, parameter->name, parameter->type)));
#line 4370 "bootstrap/stage0/ReCode.code"
                    parameter = parameter->next_parameter;
                }
            } goto if__end__3; } if__end__3: ;
    }
#line 4374 "bootstrap/stage0/ReCode.code"
    context = Checker_Context__create(function_context);
#line 4375 "bootstrap/stage0/ReCode.code"
    self->current_context = context;
#line 4376 "bootstrap/stage0/ReCode.code"
    Checker__check_statements(self, parsed_statement->statements);
#line 4377 "bootstrap/stage0/ReCode.code"
    self->current_context = function_context->parent;
#line 4379 "bootstrap/stage0/ReCode.code"
    function_symbol->checked_statements = context->statements;}

#line 4382 "bootstrap/stage0/ReCode.code"
struct Checked_Source* Checker__check_source(struct Checker* self, struct Parsed_Source* parsed_source) { struct Parsed_Statement* parsed_statement; struct Checked_Source* checked_source;
#line 4383 "bootstrap/stage0/ReCode.code"
    ;
#line 4386 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4387 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) { struct Checked_Statement* checked_statement;
#line 4388 "bootstrap/stage0/ReCode.code"
        checked_statement = NULL;
#line 4389 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4389 "bootstrap/stage0/ReCode.code"
                {
                } goto if__end__1; } if__else__1: ;
#line 4391 "bootstrap/stage0/ReCode.code"
            if__start__2: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4391 "bootstrap/stage0/ReCode.code"
                    {
                    } goto if__end__2; } if__else__2: ;
#line 4393 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4393 "bootstrap/stage0/ReCode.code"
                        {
#line 4394 "bootstrap/stage0/ReCode.code"
                            Checker__create_struct_type(self, ((struct Parsed_Struct_Statement*) parsed_statement));
                        } goto if__end__3; } if__else__3: ;
#line 4395 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4395 "bootstrap/stage0/ReCode.code"
                            {
#line 4396 "bootstrap/stage0/ReCode.code"
                                Checker__create_opaque_type(self, ((struct Parsed_Opaque_Type_Statement*) parsed_statement));
                            } goto if__end__4; } if__else__4: ;
#line 4397 "bootstrap/stage0/ReCode.code"
                        if__start__5: { if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4397 "bootstrap/stage0/ReCode.code"
                                {
#line 4398 "bootstrap/stage0/ReCode.code"
                                    Checker__check_enum_statement(self, ((struct Parsed_Enum_Statement*) parsed_statement));
                                } goto if__end__5; } if__else__5: ;
#line 4399 "bootstrap/stage0/ReCode.code"
                            {
#line 4400 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4401 "bootstrap/stage0/ReCode.code"
                                abort();
                            } if__end__5: ;
                        } if__end__4: ;
                    } if__end__3: ;
                } if__end__2: ;
            } if__end__1: ;
        }
#line 4403 "bootstrap/stage0/ReCode.code"
        if__start__6: { if (checked_statement != NULL) {
#line 4403 "bootstrap/stage0/ReCode.code"
                {
#line 4404 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(self->current_context->statements, checked_statement);
                } goto if__end__6; } if__end__6: ;
        }
#line 4406 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4410 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4411 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4412 "bootstrap/stage0/ReCode.code"
        if__start__7: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4412 "bootstrap/stage0/ReCode.code"
                {
#line 4413 "bootstrap/stage0/ReCode.code"
                    Checker__check_struct_statement(self, ((struct Parsed_Struct_Statement*) parsed_statement));
                } goto if__end__7; } if__end__7: ;
        }
#line 4415 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4419 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4420 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) { struct Checked_Statement* checked_statement;
#line 4421 "bootstrap/stage0/ReCode.code"
        checked_statement = NULL;
#line 4422 "bootstrap/stage0/ReCode.code"
        if__start__8: { if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4422 "bootstrap/stage0/ReCode.code"
                {
#line 4423 "bootstrap/stage0/ReCode.code"
                    Checker__check_function_declaration(self, ((struct Parsed_Function_Statement*) parsed_statement));
                } goto if__end__8; } if__else__8: ;
#line 4424 "bootstrap/stage0/ReCode.code"
            if__start__9: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4424 "bootstrap/stage0/ReCode.code"
                    {
#line 4425 "bootstrap/stage0/ReCode.code"
                        checked_statement = ((struct Checked_Statement*) Checker__check_variable_statement(self, ((struct Parsed_Variable_Statement*) parsed_statement)));
                    } goto if__end__9; } if__else__9: ;
#line 4426 "bootstrap/stage0/ReCode.code"
                if__start__10: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4426 "bootstrap/stage0/ReCode.code"
                        {
                        } goto if__end__10; } if__else__10: ;
#line 4428 "bootstrap/stage0/ReCode.code"
                    if__start__11: { if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4428 "bootstrap/stage0/ReCode.code"
                            {
                            } goto if__end__11; } if__else__11: ;
#line 4430 "bootstrap/stage0/ReCode.code"
                        if__start__12: { if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4430 "bootstrap/stage0/ReCode.code"
                                {
                                } goto if__end__12; } if__else__12: ;
#line 4432 "bootstrap/stage0/ReCode.code"
                            {
#line 4433 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4434 "bootstrap/stage0/ReCode.code"
                                abort();
                            } if__end__12: ;
                        } if__end__11: ;
                    } if__end__10: ;
                } if__end__9: ;
            } if__end__8: ;
        }
#line 4436 "bootstrap/stage0/ReCode.code"
        if__start__13: { if (checked_statement != NULL) {
#line 4436 "bootstrap/stage0/ReCode.code"
                {
#line 4437 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(self->current_context->statements, checked_statement);
                } goto if__end__13; } if__end__13: ;
        }
#line 4439 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4443 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4444 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4445 "bootstrap/stage0/ReCode.code"
        if__start__14: { if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4445 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Function_Statement* function_statement;
#line 4446 "bootstrap/stage0/ReCode.code"
                    function_statement = ((struct Parsed_Function_Statement*) parsed_statement);
#line 4447 "bootstrap/stage0/ReCode.code"
                    if__start__15: { if (function_statement->statements != NULL) {
#line 4447 "bootstrap/stage0/ReCode.code"
                            {
#line 4448 "bootstrap/stage0/ReCode.code"
                                Checker__check_function_definition(self, function_statement);
                            } goto if__end__15; } if__end__15: ;
                    }
                } goto if__end__14; } if__else__14: ;
#line 4450 "bootstrap/stage0/ReCode.code"
            if__start__16: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4450 "bootstrap/stage0/ReCode.code"
                    {
                    } goto if__end__16; } if__else__16: ;
#line 4452 "bootstrap/stage0/ReCode.code"
                if__start__17: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4452 "bootstrap/stage0/ReCode.code"
                        {
                        } goto if__end__17; } if__else__17: ;
#line 4454 "bootstrap/stage0/ReCode.code"
                    if__start__18: { if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4454 "bootstrap/stage0/ReCode.code"
                            {
                            } goto if__end__18; } if__else__18: ;
#line 4456 "bootstrap/stage0/ReCode.code"
                        if__start__19: { if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4456 "bootstrap/stage0/ReCode.code"
                                {
                                } goto if__end__19; } if__else__19: ;
#line 4458 "bootstrap/stage0/ReCode.code"
                            {
#line 4459 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4460 "bootstrap/stage0/ReCode.code"
                                abort();
                            } if__end__19: ;
                        } if__end__18: ;
                    } if__end__17: ;
                } if__end__16: ;
            } if__end__14: ;
        }
#line 4462 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4465 "bootstrap/stage0/ReCode.code"
    checked_source = ((struct Checked_Source*) malloc(sizeof(struct Checked_Source)));
#line 4466 "bootstrap/stage0/ReCode.code"
    checked_source->first_symbol = self->current_context->symbols->first_symbol;
#line 4467 "bootstrap/stage0/ReCode.code"
    checked_source->statements = self->current_context->statements;
#line 4468 "bootstrap/stage0/ReCode.code"
    return checked_source;}

#line 4471 "bootstrap/stage0/ReCode.code"
struct Checked_Source* check(struct Parsed_Source* parsed_source) { struct Checker* type_checker;
#line 4472 "bootstrap/stage0/ReCode.code"
    type_checker = Checker__create();
#line 4474 "bootstrap/stage0/ReCode.code"
    return Checker__check_source(type_checker, parsed_source);}

#line 4486 "bootstrap/stage0/ReCode.code"
void Generator__write_source_location(struct Generator* self, struct Source_Location* location) {
#line 4487 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (location != NULL) {
#line 4487 "bootstrap/stage0/ReCode.code"
            {
#line 4488 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "#line ");
#line 4489 "bootstrap/stage0/ReCode.code"
                File__write_i32(self->file, ((int32_t) location->line));
#line 4490 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, " \"");
#line 4491 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, location->source->path);
#line 4492 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "\"\n");
            } goto if__end__1; } if__end__1: ;
    }}

#line 4496 "bootstrap/stage0/ReCode.code"
void Generator__generate_add_expression(struct Generator* self, struct Checked_Add_Expression* expression) {
#line 4497 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4498 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " + ");
#line 4499 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4502 "bootstrap/stage0/ReCode.code"
void Generator__generate_address_of_expression(struct Generator* self, struct Checked_Address_Of_Expression* expression) {
#line 4503 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "&");
#line 4504 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);}

#line 4507 "bootstrap/stage0/ReCode.code"
void Generator__generate_array_access_expression(struct Generator* self, struct Checked_Array_Access_Expression* expression) {
#line 4508 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->array_expression);
#line 4509 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "[");
#line 4510 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->index_expression);
#line 4511 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "]");}

#line 4514 "bootstrap/stage0/ReCode.code"
void Generator__generate_bool_expression(struct Generator* self, struct Checked_Bool_Expression* expression) {
#line 4515 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (expression->value) {
#line 4515 "bootstrap/stage0/ReCode.code"
            {
#line 4516 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "true");
            } goto if__end__1; } if__else__1: ;
#line 4517 "bootstrap/stage0/ReCode.code"
        {
#line 4518 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, "false");
        } if__end__1: ;
    }}

#line 4522 "bootstrap/stage0/ReCode.code"
void Generator__generate_call_expression(struct Generator* self, struct Checked_Call_Expression* expression) { struct Checked_Call_Argument* argument;
#line 4523 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->callee_expression);
#line 4524 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4525 "bootstrap/stage0/ReCode.code"
    argument = expression->first_argument;
#line 4526 "bootstrap/stage0/ReCode.code"
    while (argument != NULL) {
#line 4527 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, argument->expression);
#line 4528 "bootstrap/stage0/ReCode.code"
        argument = argument->next_argument;
#line 4529 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (argument != NULL) {
#line 4529 "bootstrap/stage0/ReCode.code"
                {
#line 4530 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self->file, ", ");
                } goto if__end__1; } if__end__1: ;
        }
    }
#line 4533 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");}

#line 4536 "bootstrap/stage0/ReCode.code"
void Generator__generate_cast_expression(struct Generator* self, struct Checked_Cast_Expression* expression) {
#line 4537 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "((");
#line 4538 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->super.type);
#line 4539 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4540 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
#line 4541 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ')');}

#line 4544 "bootstrap/stage0/ReCode.code"
void File__write_octal_escaped_char(struct File* stream, char value) {
#line 4545 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, '\\');
#line 4546 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (value > ((char) 64)) {
#line 4546 "bootstrap/stage0/ReCode.code"
            {
#line 4547 "bootstrap/stage0/ReCode.code"
                File__write_char(stream, value / ((char) 64) % ((char) 8) + '0');
            } goto if__end__1; } if__end__1: ;
    }
#line 4549 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (value > ((char) 8)) {
#line 4549 "bootstrap/stage0/ReCode.code"
            {
#line 4550 "bootstrap/stage0/ReCode.code"
                File__write_char(stream, value / ((char) 8) % ((char) 8) + '0');
            } goto if__end__2; } if__end__2: ;
    }
#line 4552 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, value % ((char) 8) + '0');}

#line 4555 "bootstrap/stage0/ReCode.code"
void File__write_escaped_char(struct File* stream, char ch) {
#line 4556 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (ch < ((char) 32)) {
#line 4556 "bootstrap/stage0/ReCode.code"
            {
#line 4557 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (ch == '\n') {
#line 4557 "bootstrap/stage0/ReCode.code"
                        {
#line 4558 "bootstrap/stage0/ReCode.code"
                            File__write_cstring(stream, "\\n");
                        } goto if__end__2; } if__else__2: ;
#line 4559 "bootstrap/stage0/ReCode.code"
                    if__start__3: { if (ch == '\t') {
#line 4559 "bootstrap/stage0/ReCode.code"
                            {
#line 4560 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(stream, "\\t");
                            } goto if__end__3; } if__else__3: ;
#line 4561 "bootstrap/stage0/ReCode.code"
                        {
#line 4562 "bootstrap/stage0/ReCode.code"
                            File__write_octal_escaped_char(stream, ch);
                        } if__end__3: ;
                    } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 4564 "bootstrap/stage0/ReCode.code"
        if__start__4: { if (ch < ((char) 127)) {
#line 4564 "bootstrap/stage0/ReCode.code"
                {
#line 4565 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (ch == '\"') {
#line 4565 "bootstrap/stage0/ReCode.code"
                            {
#line 4566 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(stream, "\\\"");
                            } goto if__end__5; } if__else__5: ;
#line 4567 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (ch == '\'') {
#line 4567 "bootstrap/stage0/ReCode.code"
                                {
#line 4568 "bootstrap/stage0/ReCode.code"
                                    File__write_cstring(stream, "\\\'");
                                } goto if__end__6; } if__else__6: ;
#line 4569 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (ch == '\\') {
#line 4569 "bootstrap/stage0/ReCode.code"
                                    {
#line 4570 "bootstrap/stage0/ReCode.code"
                                        File__write_cstring(stream, "\\\\");
                                    } goto if__end__7; } if__else__7: ;
#line 4571 "bootstrap/stage0/ReCode.code"
                                {
#line 4572 "bootstrap/stage0/ReCode.code"
                                    File__write_char(stream, ch);
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    }
                } goto if__end__4; } if__else__4: ;
#line 4574 "bootstrap/stage0/ReCode.code"
            {
#line 4575 "bootstrap/stage0/ReCode.code"
                File__write_octal_escaped_char(stream, ch);
            } if__end__4: ;
        } if__end__1: ;
    }}

#line 4579 "bootstrap/stage0/ReCode.code"
void Generator__generate_character_expression(struct Generator* self, struct Checked_Character_Expression* expression) {
#line 4580 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');
#line 4581 "bootstrap/stage0/ReCode.code"
    File__write_escaped_char(self->file, expression->value);
#line 4582 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');}

#line 4585 "bootstrap/stage0/ReCode.code"
void Generator__generate_dereference_expression(struct Generator* self, struct Checked_Dereference_Expression* expression) {
#line 4586 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "*(");
#line 4587 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->value_expression);
#line 4588 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ')');}

#line 4591 "bootstrap/stage0/ReCode.code"
void Generator__generate_divide_expression(struct Generator* self, struct Checked_Divide_Expression* expression) {
#line 4592 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4593 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " / ");
#line 4594 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4597 "bootstrap/stage0/ReCode.code"
void Generator__generate_equals_expression(struct Generator* self, struct Checked_Equals_Expression* expression) {
#line 4598 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4599 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " == ");
#line 4600 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4603 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_expression(struct Generator* self, struct Checked_Greater_Expression* expression) {
#line 4604 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4605 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " > ");
#line 4606 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4609 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_or_equals_expression(struct Generator* self, struct Checked_Greater_Or_Equals_Expression* expression) {
#line 4610 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4611 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " >= ");
#line 4612 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4615 "bootstrap/stage0/ReCode.code"
void Generator__generate_group_expression(struct Generator* self, struct Checked_Group_Expression* expression) {
#line 4616 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4617 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
#line 4618 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");}

#line 4621 "bootstrap/stage0/ReCode.code"
void Generator__generate_integer_expression(struct Generator* self, struct Checked_Integer_Expression* expression) {
#line 4622 "bootstrap/stage0/ReCode.code"
    File__write_u64(self->file, expression->value);}

#line 4625 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_expression(struct Generator* self, struct Checked_Less_Expression* expression) {
#line 4626 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4627 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " < ");
#line 4628 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4631 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_or_equals_expression(struct Generator* self, struct Checked_Less_Or_Equals_Expression* expression) {
#line 4632 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4633 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " <= ");
#line 4634 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4637 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_and_expression(struct Generator* self, struct Checked_Logic_And_Expression* expression) {
#line 4638 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4639 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " && ");
#line 4640 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4643 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_or_expression(struct Generator* self, struct Checked_Logic_Or_Expression* expression) {
#line 4644 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4645 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " || ");
#line 4646 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4649 "bootstrap/stage0/ReCode.code"
void Generator__generate_member_access_expression(struct Generator* self, struct Checked_Member_Access_Expression* expression) {
#line 4650 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->object_expression);
#line 4651 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (expression->object_expression->type->kind == Checked_Type_Kind__POINTER) {
#line 4651 "bootstrap/stage0/ReCode.code"
            {
#line 4652 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "->");
            } goto if__end__1; } if__else__1: ;
#line 4653 "bootstrap/stage0/ReCode.code"
        {
#line 4654 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, ".");
        } if__end__1: ;
    }
#line 4656 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->member->name);}

#line 4659 "bootstrap/stage0/ReCode.code"
void Generator__generate_minus_expression(struct Generator* self, struct Checked_Minus_Expression* expression) {
#line 4660 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "-");
#line 4661 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);}

#line 4664 "bootstrap/stage0/ReCode.code"
void Generator__generate_modulo_expression(struct Generator* self, struct Checked_Modulo_Expression* expression) {
#line 4665 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4666 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " % ");
#line 4667 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4670 "bootstrap/stage0/ReCode.code"
void Generator__generate_multiply_expression(struct Generator* self, struct Checked_Multiply_Expression* expression) {
#line 4671 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4672 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " * ");
#line 4673 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4676 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_expression(struct Generator* self, struct Checked_Not_Expression* expression) {
#line 4677 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "!(");
#line 4678 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
#line 4679 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ')');}

#line 4682 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_equals_expression(struct Generator* self, struct Checked_Not_Equals_Expression* expression) {
#line 4683 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4684 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " != ");
#line 4685 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4688 "bootstrap/stage0/ReCode.code"
void Generator__generate_null_expression(struct Generator* self, struct Checked_Null_Expression* expression) {
#line 4689 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "NULL");}

#line 4692 "bootstrap/stage0/ReCode.code"
void Generator__generate_sizeof_expression(struct Generator* self, struct Checked_Sizeof_Expression* expression) {
#line 4693 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "sizeof(");
#line 4694 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->sized_type);
#line 4695 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");}

#line 4698 "bootstrap/stage0/ReCode.code"
void Generator__generate_string_expression(struct Generator* self, struct Checked_String_Expression* expression) { size_t index;
#line 4699 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');
#line 4700 "bootstrap/stage0/ReCode.code"
    index = ((size_t) 0);
#line 4701 "bootstrap/stage0/ReCode.code"
    while (index < expression->value->length) {
#line 4702 "bootstrap/stage0/ReCode.code"
        File__write_escaped_char(self->file, expression->value->data[index]);
#line 4703 "bootstrap/stage0/ReCode.code"
        index = index + ((size_t) 1);
    }
#line 4705 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');}

#line 4708 "bootstrap/stage0/ReCode.code"
void Generator__generate_substract_expression(struct Generator* self, struct Checked_Substract_Expression* expression) {
#line 4709 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4710 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " - ");
#line 4711 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4714 "bootstrap/stage0/ReCode.code"
void Generator__generate_symbol_expression(struct Generator* self, struct Checked_Symbol_Expression* expression) {
#line 4715 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->symbol->name);}

#line 4718 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression(struct Generator* self, struct Checked_Expression* expression) {
#line 4719 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (expression->kind == Checked_Expression_Kind__ADD) {
#line 4719 "bootstrap/stage0/ReCode.code"
            {
#line 4720 "bootstrap/stage0/ReCode.code"
                Generator__generate_add_expression(self, ((struct Checked_Add_Expression*) expression));
            } goto if__end__1; } if__else__1: ;
#line 4721 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (expression->kind == Checked_Expression_Kind__ADDRESS_OF) {
#line 4721 "bootstrap/stage0/ReCode.code"
                {
#line 4722 "bootstrap/stage0/ReCode.code"
                    Generator__generate_address_of_expression(self, ((struct Checked_Address_Of_Expression*) expression));
                } goto if__end__2; } if__else__2: ;
#line 4723 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (expression->kind == Checked_Expression_Kind__ARRAY_ACCESS) {
#line 4723 "bootstrap/stage0/ReCode.code"
                    {
#line 4724 "bootstrap/stage0/ReCode.code"
                        Generator__generate_array_access_expression(self, ((struct Checked_Array_Access_Expression*) expression));
                    } goto if__end__3; } if__else__3: ;
#line 4725 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (expression->kind == Checked_Expression_Kind__BOOL) {
#line 4725 "bootstrap/stage0/ReCode.code"
                        {
#line 4726 "bootstrap/stage0/ReCode.code"
                            Generator__generate_bool_expression(self, ((struct Checked_Bool_Expression*) expression));
                        } goto if__end__4; } if__else__4: ;
#line 4727 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (expression->kind == Checked_Expression_Kind__CALL) {
#line 4727 "bootstrap/stage0/ReCode.code"
                            {
#line 4728 "bootstrap/stage0/ReCode.code"
                                Generator__generate_call_expression(self, ((struct Checked_Call_Expression*) expression));
                            } goto if__end__5; } if__else__5: ;
#line 4729 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (expression->kind == Checked_Expression_Kind__CAST) {
#line 4729 "bootstrap/stage0/ReCode.code"
                                {
#line 4730 "bootstrap/stage0/ReCode.code"
                                    Generator__generate_cast_expression(self, ((struct Checked_Cast_Expression*) expression));
                                } goto if__end__6; } if__else__6: ;
#line 4731 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (expression->kind == Checked_Expression_Kind__CHARACTER) {
#line 4731 "bootstrap/stage0/ReCode.code"
                                    {
#line 4732 "bootstrap/stage0/ReCode.code"
                                        Generator__generate_character_expression(self, ((struct Checked_Character_Expression*) expression));
                                    } goto if__end__7; } if__else__7: ;
#line 4733 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (expression->kind == Checked_Expression_Kind__DEREFERENCE) {
#line 4733 "bootstrap/stage0/ReCode.code"
                                        {
#line 4734 "bootstrap/stage0/ReCode.code"
                                            Generator__generate_dereference_expression(self, ((struct Checked_Dereference_Expression*) expression));
                                        } goto if__end__8; } if__else__8: ;
#line 4735 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (expression->kind == Checked_Expression_Kind__DIVIDE) {
#line 4735 "bootstrap/stage0/ReCode.code"
                                            {
#line 4736 "bootstrap/stage0/ReCode.code"
                                                Generator__generate_divide_expression(self, ((struct Checked_Divide_Expression*) expression));
                                            } goto if__end__9; } if__else__9: ;
#line 4737 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (expression->kind == Checked_Expression_Kind__EQUALS) {
#line 4737 "bootstrap/stage0/ReCode.code"
                                                {
#line 4738 "bootstrap/stage0/ReCode.code"
                                                    Generator__generate_equals_expression(self, ((struct Checked_Equals_Expression*) expression));
                                                } goto if__end__10; } if__else__10: ;
#line 4739 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (expression->kind == Checked_Expression_Kind__GREATER) {
#line 4739 "bootstrap/stage0/ReCode.code"
                                                    {
#line 4740 "bootstrap/stage0/ReCode.code"
                                                        Generator__generate_greater_expression(self, ((struct Checked_Greater_Expression*) expression));
                                                    } goto if__end__11; } if__else__11: ;
#line 4741 "bootstrap/stage0/ReCode.code"
                                                if__start__12: { if (expression->kind == Checked_Expression_Kind__GREATER_OR_EQUALS) {
#line 4741 "bootstrap/stage0/ReCode.code"
                                                        {
#line 4742 "bootstrap/stage0/ReCode.code"
                                                            Generator__generate_greater_or_equals_expression(self, ((struct Checked_Greater_Or_Equals_Expression*) expression));
                                                        } goto if__end__12; } if__else__12: ;
#line 4743 "bootstrap/stage0/ReCode.code"
                                                    if__start__13: { if (expression->kind == Checked_Expression_Kind__GROUP) {
#line 4743 "bootstrap/stage0/ReCode.code"
                                                            {
#line 4744 "bootstrap/stage0/ReCode.code"
                                                                Generator__generate_group_expression(self, ((struct Checked_Group_Expression*) expression));
                                                            } goto if__end__13; } if__else__13: ;
#line 4745 "bootstrap/stage0/ReCode.code"
                                                        if__start__14: { if (expression->kind == Checked_Expression_Kind__INTEGER) {
#line 4745 "bootstrap/stage0/ReCode.code"
                                                                {
#line 4746 "bootstrap/stage0/ReCode.code"
                                                                    Generator__generate_integer_expression(self, ((struct Checked_Integer_Expression*) expression));
                                                                } goto if__end__14; } if__else__14: ;
#line 4747 "bootstrap/stage0/ReCode.code"
                                                            if__start__15: { if (expression->kind == Checked_Expression_Kind__LESS) {
#line 4747 "bootstrap/stage0/ReCode.code"
                                                                    {
#line 4748 "bootstrap/stage0/ReCode.code"
                                                                        Generator__generate_less_expression(self, ((struct Checked_Less_Expression*) expression));
                                                                    } goto if__end__15; } if__else__15: ;
#line 4749 "bootstrap/stage0/ReCode.code"
                                                                if__start__16: { if (expression->kind == Checked_Expression_Kind__LESS_OR_EQUALS) {
#line 4749 "bootstrap/stage0/ReCode.code"
                                                                        {
#line 4750 "bootstrap/stage0/ReCode.code"
                                                                            Generator__generate_less_or_equals_expression(self, ((struct Checked_Less_Or_Equals_Expression*) expression));
                                                                        } goto if__end__16; } if__else__16: ;
#line 4751 "bootstrap/stage0/ReCode.code"
                                                                    if__start__17: { if (expression->kind == Checked_Expression_Kind__LOGIC_AND) {
#line 4751 "bootstrap/stage0/ReCode.code"
                                                                            {
#line 4752 "bootstrap/stage0/ReCode.code"
                                                                                Generator__generate_logic_and_expression(self, ((struct Checked_Logic_And_Expression*) expression));
                                                                            } goto if__end__17; } if__else__17: ;
#line 4753 "bootstrap/stage0/ReCode.code"
                                                                        if__start__18: { if (expression->kind == Checked_Expression_Kind__LOGIC_OR) {
#line 4753 "bootstrap/stage0/ReCode.code"
                                                                                {
#line 4754 "bootstrap/stage0/ReCode.code"
                                                                                    Generator__generate_logic_or_expression(self, ((struct Checked_Logic_Or_Expression*) expression));
                                                                                } goto if__end__18; } if__else__18: ;
#line 4755 "bootstrap/stage0/ReCode.code"
                                                                            if__start__19: { if (expression->kind == Checked_Expression_Kind__MEMBER_ACCESS) {
#line 4755 "bootstrap/stage0/ReCode.code"
                                                                                    {
#line 4756 "bootstrap/stage0/ReCode.code"
                                                                                        Generator__generate_member_access_expression(self, ((struct Checked_Member_Access_Expression*) expression));
                                                                                    } goto if__end__19; } if__else__19: ;
#line 4757 "bootstrap/stage0/ReCode.code"
                                                                                if__start__20: { if (expression->kind == Checked_Expression_Kind__MINUS) {
#line 4757 "bootstrap/stage0/ReCode.code"
                                                                                        {
#line 4758 "bootstrap/stage0/ReCode.code"
                                                                                            Generator__generate_minus_expression(self, ((struct Checked_Minus_Expression*) expression));
                                                                                        } goto if__end__20; } if__else__20: ;
#line 4759 "bootstrap/stage0/ReCode.code"
                                                                                    if__start__21: { if (expression->kind == Checked_Expression_Kind__MODULO) {
#line 4759 "bootstrap/stage0/ReCode.code"
                                                                                            {
#line 4760 "bootstrap/stage0/ReCode.code"
                                                                                                Generator__generate_modulo_expression(self, ((struct Checked_Modulo_Expression*) expression));
                                                                                            } goto if__end__21; } if__else__21: ;
#line 4761 "bootstrap/stage0/ReCode.code"
                                                                                        if__start__22: { if (expression->kind == Checked_Expression_Kind__MULTIPLY) {
#line 4761 "bootstrap/stage0/ReCode.code"
                                                                                                {
#line 4762 "bootstrap/stage0/ReCode.code"
                                                                                                    Generator__generate_multiply_expression(self, ((struct Checked_Multiply_Expression*) expression));
                                                                                                } goto if__end__22; } if__else__22: ;
#line 4763 "bootstrap/stage0/ReCode.code"
                                                                                            if__start__23: { if (expression->kind == Checked_Expression_Kind__NOT) {
#line 4763 "bootstrap/stage0/ReCode.code"
                                                                                                    {
#line 4764 "bootstrap/stage0/ReCode.code"
                                                                                                        Generator__generate_not_expression(self, ((struct Checked_Not_Expression*) expression));
                                                                                                    } goto if__end__23; } if__else__23: ;
#line 4765 "bootstrap/stage0/ReCode.code"
                                                                                                if__start__24: { if (expression->kind == Checked_Expression_Kind__NOT_EQUALS) {
#line 4765 "bootstrap/stage0/ReCode.code"
                                                                                                        {
#line 4766 "bootstrap/stage0/ReCode.code"
                                                                                                            Generator__generate_not_equals_expression(self, ((struct Checked_Not_Equals_Expression*) expression));
                                                                                                        } goto if__end__24; } if__else__24: ;
#line 4767 "bootstrap/stage0/ReCode.code"
                                                                                                    if__start__25: { if (expression->kind == Checked_Expression_Kind__NULL) {
#line 4767 "bootstrap/stage0/ReCode.code"
                                                                                                            {
#line 4768 "bootstrap/stage0/ReCode.code"
                                                                                                                Generator__generate_null_expression(self, ((struct Checked_Null_Expression*) expression));
                                                                                                            } goto if__end__25; } if__else__25: ;
#line 4769 "bootstrap/stage0/ReCode.code"
                                                                                                        if__start__26: { if (expression->kind == Checked_Expression_Kind__SIZEOF) {
#line 4769 "bootstrap/stage0/ReCode.code"
                                                                                                                {
#line 4770 "bootstrap/stage0/ReCode.code"
                                                                                                                    Generator__generate_sizeof_expression(self, ((struct Checked_Sizeof_Expression*) expression));
                                                                                                                } goto if__end__26; } if__else__26: ;
#line 4771 "bootstrap/stage0/ReCode.code"
                                                                                                            if__start__27: { if (expression->kind == Checked_Expression_Kind__STRING) {
#line 4771 "bootstrap/stage0/ReCode.code"
                                                                                                                    {
#line 4772 "bootstrap/stage0/ReCode.code"
                                                                                                                        Generator__generate_string_expression(self, ((struct Checked_String_Expression*) expression));
                                                                                                                    } goto if__end__27; } if__else__27: ;
#line 4773 "bootstrap/stage0/ReCode.code"
                                                                                                                if__start__28: { if (expression->kind == Checked_Expression_Kind__SUBSTRACT) {
#line 4773 "bootstrap/stage0/ReCode.code"
                                                                                                                        {
#line 4774 "bootstrap/stage0/ReCode.code"
                                                                                                                            Generator__generate_substract_expression(self, ((struct Checked_Substract_Expression*) expression));
                                                                                                                        } goto if__end__28; } if__else__28: ;
#line 4775 "bootstrap/stage0/ReCode.code"
                                                                                                                    if__start__29: { if (expression->kind == Checked_Expression_Kind__SYMBOL) {
#line 4775 "bootstrap/stage0/ReCode.code"
                                                                                                                            {
#line 4776 "bootstrap/stage0/ReCode.code"
                                                                                                                                Generator__generate_symbol_expression(self, ((struct Checked_Symbol_Expression*) expression));
                                                                                                                            } goto if__end__29; } if__else__29: ;
#line 4777 "bootstrap/stage0/ReCode.code"
                                                                                                                        {
#line 4778 "bootstrap/stage0/ReCode.code"
                                                                                                                            Source_Location__error(expression->location, String__create_from("Unsupported expression"));
#line 4779 "bootstrap/stage0/ReCode.code"
                                                                                                                            abort();
                                                                                                                        } if__end__29: ;
                                                                                                                    } if__end__28: ;
                                                                                                                } if__end__27: ;
                                                                                                            } if__end__26: ;
                                                                                                        } if__end__25: ;
                                                                                                    } if__end__24: ;
                                                                                                } if__end__23: ;
                                                                                            } if__end__22: ;
                                                                                        } if__end__21: ;
                                                                                    } if__end__20: ;
                                                                                } if__end__19: ;
                                                                            } if__end__18: ;
                                                                        } if__end__17: ;
                                                                    } if__end__16: ;
                                                                } if__end__15: ;
                                                            } if__end__14: ;
                                                        } if__end__13: ;
                                                    } if__end__12: ;
                                                } if__end__11: ;
                                            } if__end__10: ;
                                        } if__end__9: ;
                                    } if__end__8: ;
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }}

#line 4783 "bootstrap/stage0/ReCode.code"
void Generator__write_identation(struct Generator* self) { uint16_t identation;
#line 4784 "bootstrap/stage0/ReCode.code"
    identation = self->identation;
#line 4785 "bootstrap/stage0/ReCode.code"
    while (identation > ((uint16_t) 0)) {
#line 4786 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "    ");
#line 4787 "bootstrap/stage0/ReCode.code"
        identation = identation - ((uint16_t) 1);
    }}

#line 4791 "bootstrap/stage0/ReCode.code"
void Generator__generate_assignment_statement(struct Generator* self, struct Checked_Assignment_Statement* statement) {
#line 4792 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->object_expression);
#line 4793 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " = ");
#line 4794 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->value_expression);
#line 4795 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4798 "bootstrap/stage0/ReCode.code"
void Generator__generate_block_statement(struct Generator* self, struct Checked_Block_Statement* statement) {
#line 4799 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->label != NULL) {
#line 4799 "bootstrap/stage0/ReCode.code"
            {
#line 4800 "bootstrap/stage0/ReCode.code"
                File__write_string(self->file, statement->label);
#line 4801 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, ": ");
            } goto if__end__1; } if__end__1: ;
    }
#line 4803 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '{');
#line 4804 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, statement->context->statements);
#line 4805 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (statement->super.location != NULL) {
#line 4805 "bootstrap/stage0/ReCode.code"
            {
#line 4806 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, '\n');
#line 4807 "bootstrap/stage0/ReCode.code"
                Generator__write_identation(self);
#line 4808 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, '}');
            } goto if__end__2; } if__else__2: ;
#line 4809 "bootstrap/stage0/ReCode.code"
        {
#line 4810 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, " }");
        } if__end__2: ;
    }}

#line 4814 "bootstrap/stage0/ReCode.code"
void Generator__generate_break_statement(struct Generator* self, struct Checked_Break_Statement* statement) {
#line 4815 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "break;");}

#line 4818 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression_statement(struct Generator* self, struct Checked_Expression_Statement* statement) {
#line 4819 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->expression);
#line 4820 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4823 "bootstrap/stage0/ReCode.code"
void Generator__generate_goto_statement(struct Generator* self, struct Checked_Goto_Statement* statement) {
#line 4824 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "goto ");
#line 4825 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, statement->label);
#line 4826 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ';');}

#line 4829 "bootstrap/stage0/ReCode.code"
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement) {
#line 4830 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "if (");
#line 4831 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4832 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4833 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->true_statement);
#line 4834 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->false_statement != NULL) {
#line 4834 "bootstrap/stage0/ReCode.code"
            {
#line 4835 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, " else ");
#line 4836 "bootstrap/stage0/ReCode.code"
                Generator__generate_statement(self, statement->false_statement);
            } goto if__end__1; } if__end__1: ;
    }}

#line 4840 "bootstrap/stage0/ReCode.code"
void Generator__generate_label_statement(struct Generator* self, struct Checked_Label_Statement* statement) {
#line 4841 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, statement->label);
#line 4842 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ": ;");}

#line 4845 "bootstrap/stage0/ReCode.code"
void Generator__generate_return_statement(struct Generator* self, struct Checked_Return_Statement* statement) {
#line 4846 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "return");
#line 4847 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->expression != NULL) {
#line 4847 "bootstrap/stage0/ReCode.code"
            {
#line 4848 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, " ");
#line 4849 "bootstrap/stage0/ReCode.code"
                Generator__generate_expression(self, statement->expression);
            } goto if__end__1; } if__end__1: ;
    }
#line 4851 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4854 "bootstrap/stage0/ReCode.code"
void Generator__generate_variable_statement(struct Generator* self, struct Checked_Variable_Statement* statement) {
#line 4855 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->is_external) {
#line 4855 "bootstrap/stage0/ReCode.code"
            {
#line 4856 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "extern ");
#line 4857 "bootstrap/stage0/ReCode.code"
                File__write_checked_type(self->file, statement->variable->super.type);
#line 4858 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, ' ');
#line 4859 "bootstrap/stage0/ReCode.code"
                File__write_string(self->file, statement->variable->super.name);
            } goto if__end__1; } if__else__1: ;
#line 4860 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (statement->expression != NULL) {
#line 4860 "bootstrap/stage0/ReCode.code"
                {
#line 4861 "bootstrap/stage0/ReCode.code"
                    File__write_string(self->file, statement->variable->super.name);
#line 4862 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self->file, " = ");
#line 4863 "bootstrap/stage0/ReCode.code"
                    Generator__generate_expression(self, statement->expression);
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 4865 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4868 "bootstrap/stage0/ReCode.code"
void Generator__generate_while_statement(struct Generator* self, struct Checked_While_Statement* statement) {
#line 4869 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "while (");
#line 4870 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4871 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4872 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->body_statement);}

#line 4875 "bootstrap/stage0/ReCode.code"
void Generator__generate_statement(struct Generator* self, struct Checked_Statement* statement) {
#line 4876 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->kind == Checked_Statement_Kind__ASSIGNMENT) {
#line 4876 "bootstrap/stage0/ReCode.code"
            {
#line 4877 "bootstrap/stage0/ReCode.code"
                Generator__generate_assignment_statement(self, ((struct Checked_Assignment_Statement*) statement));
            } goto if__end__1; } if__else__1: ;
#line 4878 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (statement->kind == Checked_Statement_Kind__BLOCK) {
#line 4878 "bootstrap/stage0/ReCode.code"
                {
#line 4879 "bootstrap/stage0/ReCode.code"
                    Generator__generate_block_statement(self, ((struct Checked_Block_Statement*) statement));
                } goto if__end__2; } if__else__2: ;
#line 4880 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (statement->kind == Checked_Statement_Kind__BREAK) {
#line 4880 "bootstrap/stage0/ReCode.code"
                    {
#line 4881 "bootstrap/stage0/ReCode.code"
                        Generator__generate_break_statement(self, ((struct Checked_Break_Statement*) statement));
                    } goto if__end__3; } if__else__3: ;
#line 4882 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (statement->kind == Checked_Statement_Kind__EXPRESSION) {
#line 4882 "bootstrap/stage0/ReCode.code"
                        {
#line 4883 "bootstrap/stage0/ReCode.code"
                            Generator__generate_expression_statement(self, ((struct Checked_Expression_Statement*) statement));
                        } goto if__end__4; } if__else__4: ;
#line 4884 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (statement->kind == Checked_Statement_Kind__GOTO) {
#line 4884 "bootstrap/stage0/ReCode.code"
                            {
#line 4885 "bootstrap/stage0/ReCode.code"
                                Generator__generate_goto_statement(self, ((struct Checked_Goto_Statement*) statement));
                            } goto if__end__5; } if__else__5: ;
#line 4886 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (statement->kind == Checked_Statement_Kind__IF) {
#line 4886 "bootstrap/stage0/ReCode.code"
                                {
#line 4887 "bootstrap/stage0/ReCode.code"
                                    Generator__generate_if_statement(self, ((struct Checked_If_Statement*) statement));
                                } goto if__end__6; } if__else__6: ;
#line 4888 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (statement->kind == Checked_Statement_Kind__LABEL) {
#line 4888 "bootstrap/stage0/ReCode.code"
                                    {
#line 4889 "bootstrap/stage0/ReCode.code"
                                        Generator__generate_label_statement(self, ((struct Checked_Label_Statement*) statement));
                                    } goto if__end__7; } if__else__7: ;
#line 4890 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (statement->kind == Checked_Statement_Kind__RETURN) {
#line 4890 "bootstrap/stage0/ReCode.code"
                                        {
#line 4891 "bootstrap/stage0/ReCode.code"
                                            Generator__generate_return_statement(self, ((struct Checked_Return_Statement*) statement));
                                        } goto if__end__8; } if__else__8: ;
#line 4892 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 4892 "bootstrap/stage0/ReCode.code"
                                            {
#line 4893 "bootstrap/stage0/ReCode.code"
                                                Generator__generate_variable_statement(self, ((struct Checked_Variable_Statement*) statement));
                                            } goto if__end__9; } if__else__9: ;
#line 4894 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (statement->kind == Checked_Statement_Kind__WHILE) {
#line 4894 "bootstrap/stage0/ReCode.code"
                                                {
#line 4895 "bootstrap/stage0/ReCode.code"
                                                    Generator__generate_while_statement(self, ((struct Checked_While_Statement*) statement));
                                                } goto if__end__10; } if__else__10: ;
#line 4896 "bootstrap/stage0/ReCode.code"
                                            {
#line 4897 "bootstrap/stage0/ReCode.code"
                                                Source_Location__error(statement->location, String__create_from("Unsupported statement"));
#line 4898 "bootstrap/stage0/ReCode.code"
                                                abort();
                                            } if__end__10: ;
                                        } if__end__9: ;
                                    } if__end__8: ;
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }}

#line 4902 "bootstrap/stage0/ReCode.code"
void Generator__generate_statements(struct Generator* self, struct Checked_Statements* statements) { struct Checked_Symbol* symbol; struct Checked_Statement* statement;
#line 4903 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation + ((uint16_t) 1);
#line 4905 "bootstrap/stage0/ReCode.code"
    symbol = statements->symbols->first_symbol;
#line 4906 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 4907 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4908 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self->file, symbol->type);
#line 4909 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4910 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, symbol->name);
#line 4911 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ";");
#line 4912 "bootstrap/stage0/ReCode.code"
        symbol = symbol->next_symbol;
    }
#line 4915 "bootstrap/stage0/ReCode.code"
    statement = statements->first_statement;
#line 4916 "bootstrap/stage0/ReCode.code"
    while (statement != NULL) {
#line 4917 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (statement->location != NULL) {
#line 4917 "bootstrap/stage0/ReCode.code"
                {
#line 4918 "bootstrap/stage0/ReCode.code"
                    File__write_char(self->file, '\n');
#line 4919 "bootstrap/stage0/ReCode.code"
                    Generator__write_source_location(self, statement->location);
#line 4920 "bootstrap/stage0/ReCode.code"
                    Generator__write_identation(self);
                } goto if__end__1; } if__else__1: ;
#line 4921 "bootstrap/stage0/ReCode.code"
            {
#line 4922 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, ' ');
            } if__end__1: ;
        }
#line 4925 "bootstrap/stage0/ReCode.code"
        Generator__generate_statement(self, statement);
#line 4927 "bootstrap/stage0/ReCode.code"
        statement = statement->next_statement;
    }
#line 4930 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation - ((uint16_t) 1);}

#line 4933 "bootstrap/stage0/ReCode.code"
void Generator__generate_enum(struct Generator* self, struct Checked_Enum_Type* enum_type) { struct Checked_Enum_Member* enum_member;
#line 4934 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) enum_type));
#line 4935 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4936 "bootstrap/stage0/ReCode.code"
    enum_member = enum_type->first_member;
#line 4937 "bootstrap/stage0/ReCode.code"
    while (enum_member != NULL) {
#line 4938 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4939 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, enum_member->symbol->name);
#line 4940 "bootstrap/stage0/ReCode.code"
        enum_member = enum_member->next_member;
#line 4941 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (enum_member != NULL) {
#line 4941 "bootstrap/stage0/ReCode.code"
                {
#line 4942 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self->file, ",\n");
                } goto if__end__1; } if__else__1: ;
#line 4943 "bootstrap/stage0/ReCode.code"
            {
#line 4944 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, '\n');
            } if__end__1: ;
        }
    }
#line 4947 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n");}

#line 4950 "bootstrap/stage0/ReCode.code"
void Generator__declare_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4951 "bootstrap/stage0/ReCode.code"
    File__write_checked_function_symbol(self->file, function_symbol);
#line 4952 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");}

#line 4955 "bootstrap/stage0/ReCode.code"
void Generator__generate_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4956 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (function_symbol->checked_statements == NULL) {
#line 4956 "bootstrap/stage0/ReCode.code"
            {
#line 4957 "bootstrap/stage0/ReCode.code"
                return;
            } goto if__end__1; } if__end__1: ;
    }
#line 4959 "bootstrap/stage0/ReCode.code"
    Generator__write_source_location(self, function_symbol->super.location);
#line 4960 "bootstrap/stage0/ReCode.code"
    File__write_checked_function_symbol(self->file, function_symbol);
#line 4961 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {");
#line 4962 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, function_symbol->checked_statements);
#line 4963 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "}\n\n");}

#line 4966 "bootstrap/stage0/ReCode.code"
void Generator__declare_opaque_type(struct Generator* self, struct Checked_Opaque_Type* opaque_type) {
#line 4967 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) opaque_type));
#line 4968 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");}

#line 4971 "bootstrap/stage0/ReCode.code"
void Generator__declare_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4972 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) struct_type));
#line 4973 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");}

#line 4976 "bootstrap/stage0/ReCode.code"
void Generator__generate_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) { struct Checked_Struct_Member* struct_member;
#line 4977 "bootstrap/stage0/ReCode.code"
    struct_member = struct_type->first_member;
#line 4978 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (struct_member == NULL) {
#line 4978 "bootstrap/stage0/ReCode.code"
            {
#line 4979 "bootstrap/stage0/ReCode.code"
                return;
            } goto if__end__1; } if__end__1: ;
    }
#line 4981 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) struct_type));
#line 4982 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4983 "bootstrap/stage0/ReCode.code"
    while (struct_member != NULL) {
#line 4984 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4985 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self->file, struct_member->type);
#line 4986 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4987 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, struct_member->name);
#line 4988 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ";\n");
#line 4989 "bootstrap/stage0/ReCode.code"
        struct_member = struct_member->next_member;
    }
#line 4991 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n\n");}

#line 4994 "bootstrap/stage0/ReCode.code"
void generate(struct File* file, struct Checked_Source* checked_source) { struct Generator generator; struct Checked_Symbol* checked_symbol; struct Checked_Statement* checked_statement;
#line 4995 "bootstrap/stage0/ReCode.code"
    ;
#line 4996 "bootstrap/stage0/ReCode.code"
    generator.file = file;
#line 4997 "bootstrap/stage0/ReCode.code"
    generator.identation = ((uint16_t) 0);
#line 4999 "bootstrap/stage0/ReCode.code"
    ;
#line 5001 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "/* Copyright (C) 2023 Stefan Selariu */\n");
#line 5002 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5003 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <inttypes.h>\n");
#line 5004 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stdbool.h>\n");
#line 5005 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stddef.h>\n");
#line 5006 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5009 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5010 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5011 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 5011 "bootstrap/stage0/ReCode.code"
                { struct Checked_Named_Type* named_type;
#line 5012 "bootstrap/stage0/ReCode.code"
                    named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 5013 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 5013 "bootstrap/stage0/ReCode.code"
                            {
#line 5014 "bootstrap/stage0/ReCode.code"
                                Generator__declare_struct(&generator, ((struct Checked_Struct_Type*) named_type));
                            } goto if__end__2; } if__else__2: ;
#line 5015 "bootstrap/stage0/ReCode.code"
                        if__start__3: { if (named_type->super.kind == Checked_Type_Kind__OPAQUE) {
#line 5015 "bootstrap/stage0/ReCode.code"
                                {
#line 5016 "bootstrap/stage0/ReCode.code"
                                    Generator__declare_opaque_type(&generator, ((struct Checked_Opaque_Type*) named_type));
                                } goto if__end__3; } if__else__3: ;
#line 5017 "bootstrap/stage0/ReCode.code"
                            if__start__4: { if (named_type->super.kind == Checked_Type_Kind__ENUM) {
#line 5017 "bootstrap/stage0/ReCode.code"
                                    {
#line 5018 "bootstrap/stage0/ReCode.code"
                                        Generator__generate_enum(&generator, ((struct Checked_Enum_Type*) named_type));
                                    } goto if__end__4; } if__end__4: ;
                            } if__end__3: ;
                        } if__end__2: ;
                    }
                } goto if__end__1; } if__end__1: ;
        }
#line 5021 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 5023 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5026 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5027 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5028 "bootstrap/stage0/ReCode.code"
        if__start__5: { if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 5028 "bootstrap/stage0/ReCode.code"
                { struct Checked_Named_Type* named_type;
#line 5029 "bootstrap/stage0/ReCode.code"
                    named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 5030 "bootstrap/stage0/ReCode.code"
                    if__start__6: { if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 5030 "bootstrap/stage0/ReCode.code"
                            {
#line 5031 "bootstrap/stage0/ReCode.code"
                                Generator__generate_struct(&generator, ((struct Checked_Struct_Type*) named_type));
                            } goto if__end__6; } if__end__6: ;
                    }
                } goto if__end__5; } if__end__5: ;
        }
#line 5034 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 5038 "bootstrap/stage0/ReCode.code"
    checked_statement = checked_source->statements->first_statement;
#line 5039 "bootstrap/stage0/ReCode.code"
    while (checked_statement != NULL) {
#line 5040 "bootstrap/stage0/ReCode.code"
        if__start__7: { if (checked_statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 5040 "bootstrap/stage0/ReCode.code"
                {
#line 5041 "bootstrap/stage0/ReCode.code"
                    Generator__generate_variable_statement(&generator, ((struct Checked_Variable_Statement*) checked_statement));
#line 5042 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(generator.file, "\n");
                } goto if__end__7; } if__else__7: ;
#line 5043 "bootstrap/stage0/ReCode.code"
            {
#line 5044 "bootstrap/stage0/ReCode.code"
                Source_Location__error(checked_statement->location, String__create_from("Unsupported statement"));
#line 5045 "bootstrap/stage0/ReCode.code"
                abort();
            } if__end__7: ;
        }
#line 5047 "bootstrap/stage0/ReCode.code"
        checked_statement = checked_statement->next_statement;
    }
#line 5049 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5052 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5053 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5054 "bootstrap/stage0/ReCode.code"
        if__start__8: { if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 5054 "bootstrap/stage0/ReCode.code"
                {
#line 5055 "bootstrap/stage0/ReCode.code"
                    Generator__declare_function(&generator, ((struct Checked_Function_Symbol*) checked_symbol));
                } goto if__end__8; } if__end__8: ;
        }
#line 5057 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 5059 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5062 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5063 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5064 "bootstrap/stage0/ReCode.code"
        if__start__9: { if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 5064 "bootstrap/stage0/ReCode.code"
                {
#line 5065 "bootstrap/stage0/ReCode.code"
                    Generator__generate_function(&generator, ((struct Checked_Function_Symbol*) checked_symbol));
                } goto if__end__9; } if__end__9: ;
        }
#line 5067 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }}

#line 5079 "bootstrap/stage0/ReCode.code"
struct Counter* Counter__create() { struct Counter* counter;
#line 5080 "bootstrap/stage0/ReCode.code"
    counter = ((struct Counter*) malloc(sizeof(struct Counter)));
#line 5081 "bootstrap/stage0/ReCode.code"
    counter->value = ((int16_t) 0);
#line 5082 "bootstrap/stage0/ReCode.code"
    return counter;}

#line 5085 "bootstrap/stage0/ReCode.code"
int16_t Counter__next(struct Counter* self) {
#line 5086 "bootstrap/stage0/ReCode.code"
    self->value = self->value + ((int16_t) 1);
#line 5087 "bootstrap/stage0/ReCode.code"
    return self->value;}

#line 5090 "bootstrap/stage0/ReCode.code"
struct Counter* Counter__reset(struct Counter* self) {
#line 5091 "bootstrap/stage0/ReCode.code"
    self->value = ((int16_t) 0);
#line 5092 "bootstrap/stage0/ReCode.code"
    return self;}

#line 5099 "bootstrap/stage0/ReCode.code"
int32_t main(int32_t argc, char** argv) { char* source_file_path; struct File* source_file; char* output_file_path; struct File* output_file; struct Source* source; struct Parsed_Source* parsed_source; struct Checked_Source* checked_source;
#line 5100 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (argc < 3) {
#line 5100 "bootstrap/stage0/ReCode.code"
            {
#line 5101 "bootstrap/stage0/ReCode.code"
                error(String__append_cstring(String__append_cstring(String__create_from("Usage: "), argv[((size_t) 0)]), " SOURCE OUTPUT"));
#line 5102 "bootstrap/stage0/ReCode.code"
                return 1;
            } goto if__end__1; } if__end__1: ;
    }
#line 5105 "bootstrap/stage0/ReCode.code"
    source_file_path = argv[((size_t) 1)];
#line 5106 "bootstrap/stage0/ReCode.code"
    source_file = fopen(source_file_path, "r");
#line 5107 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (source_file == NULL) {
#line 5107 "bootstrap/stage0/ReCode.code"
            {
#line 5108 "bootstrap/stage0/ReCode.code"
                error(String__append_cstring(String__create_from("Cannot open file: "), source_file_path));
#line 5109 "bootstrap/stage0/ReCode.code"
                return 1;
            } goto if__end__2; } if__end__2: ;
    }
#line 5112 "bootstrap/stage0/ReCode.code"
    output_file_path = argv[((size_t) 2)];
#line 5113 "bootstrap/stage0/ReCode.code"
    ;
#line 5114 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (String__equals_cstring(String__create_from(output_file_path), "-")) {
#line 5114 "bootstrap/stage0/ReCode.code"
            {
#line 5115 "bootstrap/stage0/ReCode.code"
                output_file = stdout;
            } goto if__end__3; } if__else__3: ;
#line 5116 "bootstrap/stage0/ReCode.code"
        {
#line 5117 "bootstrap/stage0/ReCode.code"
            output_file = fopen(output_file_path, "w");
#line 5118 "bootstrap/stage0/ReCode.code"
            if__start__4: { if (output_file == NULL) {
#line 5118 "bootstrap/stage0/ReCode.code"
                    {
#line 5119 "bootstrap/stage0/ReCode.code"
                        error(String__append_cstring(String__create_from("Cannot open file: "), output_file_path));
#line 5120 "bootstrap/stage0/ReCode.code"
                        return 1;
                    } goto if__end__4; } if__end__4: ;
            }
        } if__end__3: ;
    }
#line 5124 "bootstrap/stage0/ReCode.code"
    source = Source__create(source_file, source_file_path);
#line 5125 "bootstrap/stage0/ReCode.code"
    parsed_source = parse(source);
#line 5126 "bootstrap/stage0/ReCode.code"
    checked_source = check(parsed_source);
#line 5127 "bootstrap/stage0/ReCode.code"
    generate(output_file, checked_source);
#line 5129 "bootstrap/stage0/ReCode.code"
    fclose(source_file);
#line 5130 "bootstrap/stage0/ReCode.code"
    return fclose(output_file);}

