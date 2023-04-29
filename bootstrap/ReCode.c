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
bool Token__is_type(struct Token* self);
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
struct Parsed_Statement* Parser__parse_external_type(struct Parser* self);
struct Parsed_Statement* Parser__parse_enum(struct Parser* self);
struct Parsed_Type* Parser__parse_type(struct Parser* self);
struct Parsed_Statement* Parser__parse_variable(struct Parser* self);
struct Parsed_Statement* Parser__parse_external_variable(struct Parser* self);
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
bool Token__is_type(struct Token* self) {
#line 501 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "type");}

#line 504 "bootstrap/stage0/ReCode.code"
bool Token__is_undefined(struct Token* self) {
#line 505 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "undefined");}

#line 508 "bootstrap/stage0/ReCode.code"
bool Token__is_while(struct Token* self) {
#line 509 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "while");}

#line 512 "bootstrap/stage0/ReCode.code"
bool Token__is_other(struct Token* self, char* lexeme) {
#line 513 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__OTHER && String__equals_cstring(self->lexeme, lexeme);}

#line 516 "bootstrap/stage0/ReCode.code"
bool Token__is_ampersand(struct Token* self) {
#line 517 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "&");}

#line 520 "bootstrap/stage0/ReCode.code"
bool Token__is_asterisk(struct Token* self) {
#line 521 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "*");}

#line 524 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_brace(struct Token* self) {
#line 525 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "}");}

#line 528 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_bracket(struct Token* self) {
#line 529 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "]");}

#line 532 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_paren(struct Token* self) {
#line 533 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ")");}

#line 536 "bootstrap/stage0/ReCode.code"
bool Token__is_colon(struct Token* self) {
#line 537 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ":");}

#line 540 "bootstrap/stage0/ReCode.code"
bool Token__is_comma(struct Token* self) {
#line 541 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ",");}

#line 544 "bootstrap/stage0/ReCode.code"
bool Token__is_dot(struct Token* self) {
#line 545 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ".");}

#line 548 "bootstrap/stage0/ReCode.code"
bool Token__is_equals(struct Token* self) {
#line 549 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "=");}

#line 552 "bootstrap/stage0/ReCode.code"
bool Token__is_exclamation_mark(struct Token* self) {
#line 553 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "!");}

#line 556 "bootstrap/stage0/ReCode.code"
bool Token__is_greater_than(struct Token* self) {
#line 557 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ">");}

#line 560 "bootstrap/stage0/ReCode.code"
bool Token__is_less_than(struct Token* self) {
#line 561 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "<");}

#line 564 "bootstrap/stage0/ReCode.code"
bool Token__is_minus(struct Token* self) {
#line 565 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "-");}

#line 568 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_brace(struct Token* self) {
#line 569 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "{");}

#line 572 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_bracket(struct Token* self) {
#line 573 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "[");}

#line 576 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_paren(struct Token* self) {
#line 577 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "(");}

#line 580 "bootstrap/stage0/ReCode.code"
bool Token__is_percent(struct Token* self) {
#line 581 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "%");}

#line 584 "bootstrap/stage0/ReCode.code"
bool Token__is_plus(struct Token* self) {
#line 585 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "+");}

#line 588 "bootstrap/stage0/ReCode.code"
bool Token__is_slash(struct Token* self) {
#line 589 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "/");}

#line 592 "bootstrap/stage0/ReCode.code"
bool Token__is_vertical_bar(struct Token* self) {
#line 593 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "|");}

#line 596 "bootstrap/stage0/ReCode.code"
bool Token__is_space(struct Token* self) {
#line 597 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__SPACE;}

#line 600 "bootstrap/stage0/ReCode.code"
bool Token__is_string(struct Token* self) {
#line 601 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__STRING;}

#line 604 "bootstrap/stage0/ReCode.code"
void File__write_token(struct File* stream, struct Token* token) { bool colored;
#line 605 "bootstrap/stage0/ReCode.code"
    colored = token->kind == Token_Kind__COMMENT || token->kind == Token_Kind__ERROR || token->kind == Token_Kind__OTHER;
#line 606 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (colored) {
#line 606 "bootstrap/stage0/ReCode.code"
            {
#line 607 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (token->kind == Token_Kind__OTHER) {
#line 607 "bootstrap/stage0/ReCode.code"
                        {
#line 608 "bootstrap/stage0/ReCode.code"
                            File__write_cstring(stream, "\33[2;33m");
                        } goto if__end__2; } if__else__2: ;
#line 609 "bootstrap/stage0/ReCode.code"
                    if__start__3: { if (token->kind == Token_Kind__COMMENT) {
#line 609 "bootstrap/stage0/ReCode.code"
                            {
#line 610 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(stream, "\33[2;37m");
                            } goto if__end__3; } if__else__3: ;
#line 611 "bootstrap/stage0/ReCode.code"
                        if__start__4: { if (token->kind == Token_Kind__ERROR) {
#line 611 "bootstrap/stage0/ReCode.code"
                                {
#line 612 "bootstrap/stage0/ReCode.code"
                                    File__write_cstring(stream, "\33[2;31m");
                                } goto if__end__4; } if__end__4: ;
                        } if__end__3: ;
                    } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 615 "bootstrap/stage0/ReCode.code"
    File__write_string(stream, token->lexeme);
#line 616 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (colored) {
#line 616 "bootstrap/stage0/ReCode.code"
            {
#line 617 "bootstrap/stage0/ReCode.code"
                File__write_cstring(stream, "\33[0m");
            } goto if__end__5; } if__end__5: ;
    }}

#line 633 "bootstrap/stage0/ReCode.code"
char Scanner__peek_char(struct Scanner* self) {
#line 634 "bootstrap/stage0/ReCode.code"
    return self->source->content->data[self->current_char_index];}

#line 637 "bootstrap/stage0/ReCode.code"
char Scanner__next_char(struct Scanner* self) { char next_char;
#line 638 "bootstrap/stage0/ReCode.code"
    next_char = Scanner__peek_char(self);
#line 639 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (next_char != '\0') {
#line 639 "bootstrap/stage0/ReCode.code"
            {
#line 640 "bootstrap/stage0/ReCode.code"
                self->current_char_index = self->current_char_index + ((size_t) 1);
#line 641 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (next_char == '\n') {
#line 641 "bootstrap/stage0/ReCode.code"
                        {
#line 642 "bootstrap/stage0/ReCode.code"
                            self->current_line = self->current_line + ((uint16_t) 1);
#line 643 "bootstrap/stage0/ReCode.code"
                            self->current_column = ((uint16_t) 1);
                        } goto if__end__2; } if__else__2: ;
#line 644 "bootstrap/stage0/ReCode.code"
                    {
#line 645 "bootstrap/stage0/ReCode.code"
                        self->current_column = self->current_column + ((uint16_t) 1);
                    } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 648 "bootstrap/stage0/ReCode.code"
    return next_char;}

#line 651 "bootstrap/stage0/ReCode.code"
char escape_char_value(char c) {
#line 652 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (c == 'n') {
#line 652 "bootstrap/stage0/ReCode.code"
            {
#line 653 "bootstrap/stage0/ReCode.code"
                return '\n';
            } goto if__end__1; } if__end__1: ;
    }
#line 655 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (c == '\"') {
#line 655 "bootstrap/stage0/ReCode.code"
            {
#line 656 "bootstrap/stage0/ReCode.code"
                return '\"';
            } goto if__end__2; } if__end__2: ;
    }
#line 658 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (c == '\'') {
#line 658 "bootstrap/stage0/ReCode.code"
            {
#line 659 "bootstrap/stage0/ReCode.code"
                return '\'';
            } goto if__end__3; } if__end__3: ;
    }
#line 661 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (c == '\\') {
#line 661 "bootstrap/stage0/ReCode.code"
            {
#line 662 "bootstrap/stage0/ReCode.code"
                return '\\';
            } goto if__end__4; } if__end__4: ;
    }
#line 664 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (c == 't') {
#line 664 "bootstrap/stage0/ReCode.code"
            {
#line 665 "bootstrap/stage0/ReCode.code"
                return '\t';
            } goto if__end__5; } if__end__5: ;
    }
#line 667 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (c == '0') {
#line 667 "bootstrap/stage0/ReCode.code"
            {
#line 668 "bootstrap/stage0/ReCode.code"
                return '\0';
            } goto if__end__6; } if__end__6: ;
    }
#line 670 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (c == 'e') {
#line 670 "bootstrap/stage0/ReCode.code"
            {
#line 671 "bootstrap/stage0/ReCode.code"
                return '\33';
            } goto if__end__7; } if__end__7: ;
    }
#line 673 "bootstrap/stage0/ReCode.code"
    return -((char) 1);}

#line 676 "bootstrap/stage0/ReCode.code"
bool char_is_end_of_line(char c) {
#line 677 "bootstrap/stage0/ReCode.code"
    return c == '\n' || c == '\0';}

#line 680 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_character_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { char next_char; char value;
#line 681 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Scanner__next_char(self) != '\'') {
#line 681 "bootstrap/stage0/ReCode.code"
            {
#line 682 "bootstrap/stage0/ReCode.code"
                Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 683 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 685 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\'');
#line 687 "bootstrap/stage0/ReCode.code"
    next_char = Scanner__peek_char(self);
#line 688 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__2; } } if__then__2__3: {
#line 688 "bootstrap/stage0/ReCode.code"
            {
#line 689 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
            } goto if__end__2; } if__end__2: ;
    }
#line 692 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 693 "bootstrap/stage0/ReCode.code"
    value = next_char;
#line 695 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (value == '\'') {
#line 695 "bootstrap/stage0/ReCode.code"
            {
#line 696 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
            } goto if__end__4; } if__end__4: ;
    }
#line 699 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (value == '\\') {
#line 699 "bootstrap/stage0/ReCode.code"
            {
#line 700 "bootstrap/stage0/ReCode.code"
                next_char = Scanner__peek_char(self);
#line 701 "bootstrap/stage0/ReCode.code"
                if__start__6: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__6; } } if__then__6__7: {
#line 701 "bootstrap/stage0/ReCode.code"
                        {
#line 702 "bootstrap/stage0/ReCode.code"
                            return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                        } goto if__end__6; } if__end__6: ;
                }
#line 705 "bootstrap/stage0/ReCode.code"
                String__append_char(token_lexeme, Scanner__next_char(self));
#line 707 "bootstrap/stage0/ReCode.code"
                value = escape_char_value(next_char);
#line 708 "bootstrap/stage0/ReCode.code"
                if__start__8: { if (value == -((char) 1)) {
#line 708 "bootstrap/stage0/ReCode.code"
                        {
#line 709 "bootstrap/stage0/ReCode.code"
                            return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                        } goto if__end__8; } if__end__8: ;
                }
            } goto if__end__5; } if__end__5: ;
    }
#line 713 "bootstrap/stage0/ReCode.code"
    if__start__9: { if (Scanner__peek_char(self) != '\'') {
#line 713 "bootstrap/stage0/ReCode.code"
            {
#line 714 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
            } goto if__end__9; } if__end__9: ;
    }
#line 717 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 718 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Character_Token__create(source_location, token_lexeme, value));}

#line 721 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_comment_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 722 "bootstrap/stage0/ReCode.code"
    while (!(char_is_end_of_line(Scanner__peek_char(self)))) {
#line 723 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 725 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Comment_Token__create(source_location, token_lexeme));}

#line 728 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_start(char c) {
#line 729 "bootstrap/stage0/ReCode.code"
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';}

#line 732 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_letter(char c) {
#line 733 "bootstrap/stage0/ReCode.code"
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');}

#line 736 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_identifier_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 737 "bootstrap/stage0/ReCode.code"
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
#line 738 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 740 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Identifier_Token__create(source_location, token_lexeme));}

#line 743 "bootstrap/stage0/ReCode.code"
bool char_is_digit(char c) {
#line 744 "bootstrap/stage0/ReCode.code"
    return c >= '0' && c <= '9';}

#line 747 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_integer_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { uint64_t value;
#line 748 "bootstrap/stage0/ReCode.code"
    value = ((uint64_t) 0);
#line 749 "bootstrap/stage0/ReCode.code"
    while (char_is_digit(Scanner__peek_char(self))) { char c;
#line 750 "bootstrap/stage0/ReCode.code"
        c = Scanner__next_char(self);
#line 751 "bootstrap/stage0/ReCode.code"
        value = value * ((uint64_t) 10) + ((uint64_t) (c - '0'));
#line 752 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, c);
    }
#line 754 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Integer_Token__create(source_location, token_lexeme, value));}

#line 757 "bootstrap/stage0/ReCode.code"
bool char_is_space(char c) {
#line 758 "bootstrap/stage0/ReCode.code"
    return c == ' ';}

#line 761 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_space_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { uint16_t count;
#line 762 "bootstrap/stage0/ReCode.code"
    count = ((uint16_t) 0);
#line 763 "bootstrap/stage0/ReCode.code"
    while (char_is_space(Scanner__peek_char(self))) {
#line 764 "bootstrap/stage0/ReCode.code"
        count = count + ((uint16_t) 1);
#line 765 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 767 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Space_Token__create(source_location, token_lexeme, count));}

#line 770 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_string_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) { struct String* value;
#line 771 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Scanner__next_char(self) != '\"') {
#line 771 "bootstrap/stage0/ReCode.code"
            {
#line 772 "bootstrap/stage0/ReCode.code"
                Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 773 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 775 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\"');
#line 777 "bootstrap/stage0/ReCode.code"
    value = String__create();
#line 779 "bootstrap/stage0/ReCode.code"
    while (true) { char next_char;
#line 780 "bootstrap/stage0/ReCode.code"
        next_char = Scanner__peek_char(self);
#line 781 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__2; } } if__then__2__3: {
#line 781 "bootstrap/stage0/ReCode.code"
                {
#line 782 "bootstrap/stage0/ReCode.code"
                    return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                } goto if__end__2; } if__end__2: ;
        }
#line 785 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 787 "bootstrap/stage0/ReCode.code"
        if__start__4: { if (next_char == '\"') {
#line 787 "bootstrap/stage0/ReCode.code"
                {
#line 788 "bootstrap/stage0/ReCode.code"
                    return ((struct Token*) String_Token__create(source_location, token_lexeme, value));
                } goto if__end__4; } if__end__4: ;
        }
#line 791 "bootstrap/stage0/ReCode.code"
        if__start__5: { if (next_char == '\\') {
#line 791 "bootstrap/stage0/ReCode.code"
                {
#line 792 "bootstrap/stage0/ReCode.code"
                    next_char = Scanner__peek_char(self);
#line 793 "bootstrap/stage0/ReCode.code"
                    if__start__6: { if (!(char_is_end_of_line(next_char))) { if (!(next_char == '\t')) { goto if__end__6; } } if__then__6__7: {
#line 793 "bootstrap/stage0/ReCode.code"
                            {
#line 794 "bootstrap/stage0/ReCode.code"
                                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                            } goto if__end__6; } if__end__6: ;
                    }
#line 797 "bootstrap/stage0/ReCode.code"
                    String__append_char(token_lexeme, Scanner__next_char(self));
#line 799 "bootstrap/stage0/ReCode.code"
                    next_char = escape_char_value(next_char);
#line 800 "bootstrap/stage0/ReCode.code"
                    if__start__8: { if (next_char == -((char) 1)) {
#line 800 "bootstrap/stage0/ReCode.code"
                            {
#line 801 "bootstrap/stage0/ReCode.code"
                                return ((struct Token*) Error_Token__create(source_location, token_lexeme));
                            } goto if__end__8; } if__end__8: ;
                    }
                } goto if__end__5; } if__end__5: ;
        }
#line 805 "bootstrap/stage0/ReCode.code"
        String__append_char(value, next_char);
    }}

#line 809 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_token(struct Scanner* self) { struct Source_Location* source_location; struct String* token_lexeme; char next_char;
#line 810 "bootstrap/stage0/ReCode.code"
    source_location = Source_Location__create(self->source, self->current_line, self->current_column);
#line 811 "bootstrap/stage0/ReCode.code"
    token_lexeme = String__create();
#line 813 "bootstrap/stage0/ReCode.code"
    next_char = Scanner__peek_char(self);
#line 815 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (char_is_identifier_start(next_char)) {
#line 815 "bootstrap/stage0/ReCode.code"
            {
#line 816 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_identifier_token(self, source_location, token_lexeme);
            } goto if__end__1; } if__end__1: ;
    }
#line 819 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (char_is_digit(next_char)) {
#line 819 "bootstrap/stage0/ReCode.code"
            {
#line 820 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_integer_token(self, source_location, token_lexeme);
            } goto if__end__2; } if__end__2: ;
    }
#line 823 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (char_is_space(next_char)) {
#line 823 "bootstrap/stage0/ReCode.code"
            {
#line 824 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_space_token(self, source_location, token_lexeme);
            } goto if__end__3; } if__end__3: ;
    }
#line 827 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (next_char == '\'') {
#line 827 "bootstrap/stage0/ReCode.code"
            {
#line 828 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_character_token(self, source_location, token_lexeme);
            } goto if__end__4; } if__end__4: ;
    }
#line 831 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (next_char == '\"') {
#line 831 "bootstrap/stage0/ReCode.code"
            {
#line 832 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_string_token(self, source_location, token_lexeme);
            } goto if__end__5; } if__end__5: ;
    }
#line 835 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (next_char == '\\') {
#line 835 "bootstrap/stage0/ReCode.code"
            {
#line 836 "bootstrap/stage0/ReCode.code"
                return Scanner__scan_comment_token(self, source_location, token_lexeme);
            } goto if__end__6; } if__end__6: ;
    }
#line 839 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (next_char == '\n') {
#line 839 "bootstrap/stage0/ReCode.code"
            {
#line 840 "bootstrap/stage0/ReCode.code"
                String__append_char(token_lexeme, Scanner__next_char(self));
#line 841 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) End_Of_Line_Token__create(source_location, token_lexeme));
            } goto if__end__7; } if__end__7: ;
    }
#line 844 "bootstrap/stage0/ReCode.code"
    if__start__8: { if (next_char == '\0') {
#line 844 "bootstrap/stage0/ReCode.code"
            {
#line 845 "bootstrap/stage0/ReCode.code"
                return ((struct Token*) End_Of_File_Token__create(source_location, token_lexeme));
            } goto if__end__8; } if__end__8: ;
    }
#line 848 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 849 "bootstrap/stage0/ReCode.code"
    return ((struct Token*) Other_Token__create(source_location, token_lexeme));}

#line 852 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__next_token(struct Scanner* self) {
#line 853 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->current_token->next_token == NULL) {
#line 853 "bootstrap/stage0/ReCode.code"
            {
#line 854 "bootstrap/stage0/ReCode.code"
                self->current_token->next_token = Scanner__scan_token(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 856 "bootstrap/stage0/ReCode.code"
    self->current_token = self->current_token->next_token;
#line 857 "bootstrap/stage0/ReCode.code"
    return self->current_token;}

#line 860 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__peek_token(struct Scanner* self, uint8_t offset) { struct Token* token;
#line 861 "bootstrap/stage0/ReCode.code"
    token = self->current_token;
#line 862 "bootstrap/stage0/ReCode.code"
    while (offset > ((uint8_t) 0)) {
#line 863 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (token->next_token == NULL) {
#line 863 "bootstrap/stage0/ReCode.code"
                {
#line 864 "bootstrap/stage0/ReCode.code"
                    token->next_token = Scanner__scan_token(self);
                } goto if__end__1; } if__end__1: ;
        }
#line 866 "bootstrap/stage0/ReCode.code"
        token = token->next_token;
#line 867 "bootstrap/stage0/ReCode.code"
        offset = offset - ((uint8_t) 1);
    }
#line 869 "bootstrap/stage0/ReCode.code"
    return token;}

#line 872 "bootstrap/stage0/ReCode.code"
struct Scanner* Scanner__create(struct Source* source) { struct Scanner* scanner;
#line 873 "bootstrap/stage0/ReCode.code"
    scanner = ((struct Scanner*) malloc(sizeof(struct Scanner)));
#line 874 "bootstrap/stage0/ReCode.code"
    scanner->source = source;
#line 875 "bootstrap/stage0/ReCode.code"
    scanner->current_char_index = ((size_t) 0);
#line 876 "bootstrap/stage0/ReCode.code"
    scanner->current_line = ((uint16_t) 1);
#line 877 "bootstrap/stage0/ReCode.code"
    scanner->current_column = ((uint16_t) 1);
#line 879 "bootstrap/stage0/ReCode.code"
    scanner->current_token = Scanner__scan_token(scanner);
#line 881 "bootstrap/stage0/ReCode.code"
    return scanner;}

#line 904 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Type__create_kind(enum Parsed_Type_Kind kind, size_t kind_size, struct Source_Location* location) { struct Parsed_Type* type;
#line 905 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Type*) malloc(kind_size));
#line 906 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 907 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 908 "bootstrap/stage0/ReCode.code"
    return type;}

#line 918 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parsed_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Parsed_Type* type) { struct Parsed_Function_Parameter* parameter;
#line 919 "bootstrap/stage0/ReCode.code"
    parameter = ((struct Parsed_Function_Parameter*) malloc(sizeof(struct Parsed_Function_Parameter)));
#line 920 "bootstrap/stage0/ReCode.code"
    parameter->location = location;
#line 921 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 922 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 923 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 924 "bootstrap/stage0/ReCode.code"
    return parameter;}

#line 933 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Type* Parsed_Function_Type__create(struct Source_Location* location, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* return_type) { struct Parsed_Function_Type* type;
#line 934 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Function_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__FUNCTION, sizeof(struct Parsed_Function_Type), location));
#line 935 "bootstrap/stage0/ReCode.code"
    type->first_parameter = first_parameter;
#line 936 "bootstrap/stage0/ReCode.code"
    type->return_type = return_type;
#line 937 "bootstrap/stage0/ReCode.code"
    return type;}

#line 945 "bootstrap/stage0/ReCode.code"
struct Parsed_Named_Type* Parsed_Named_Type__create(struct Token* name) { struct Parsed_Named_Type* type;
#line 946 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Named_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__NAMED, sizeof(struct Parsed_Named_Type), name->location));
#line 947 "bootstrap/stage0/ReCode.code"
    type->name = name->lexeme;
#line 948 "bootstrap/stage0/ReCode.code"
    return type;}

#line 956 "bootstrap/stage0/ReCode.code"
struct Parsed_Pointer_Type* Parsed_Pointer_Type__create(struct Parsed_Type* other_type) { struct Parsed_Pointer_Type* type;
#line 957 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Pointer_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__POINTER, sizeof(struct Parsed_Pointer_Type), other_type->location));
#line 958 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 959 "bootstrap/stage0/ReCode.code"
    return type;}

#line 967 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Type* Parsed_Struct_Type__create(struct Source_Location* location, struct Parsed_Type* other_type) { struct Parsed_Struct_Type* type;
#line 968 "bootstrap/stage0/ReCode.code"
    type = ((struct Parsed_Struct_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__STRUCT, sizeof(struct Parsed_Struct_Type), location));
#line 969 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 970 "bootstrap/stage0/ReCode.code"
    return type;}

#line 1010 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parsed_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location) { struct Parsed_Expression* expression;
#line 1011 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Expression*) malloc(kind_size));
#line 1012 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 1013 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 1014 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1023 "bootstrap/stage0/ReCode.code"
struct Parsed_Binary_Expression* Parsed_Binary_Expression__create_kind(enum Parsed_Expression_Kind kind, struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) { struct Parsed_Binary_Expression* expression;
#line 1024 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Binary_Expression*) Parsed_Expression__create_kind(kind, sizeof(struct Parsed_Binary_Expression), left_expression->location));
#line 1025 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 1026 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 1027 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1035 "bootstrap/stage0/ReCode.code"
struct Parsed_Unary_Expression* Parsed_Unary_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Parsed_Expression* other_expression) { struct Parsed_Unary_Expression* expression;
#line 1036 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Unary_Expression*) Parsed_Expression__create_kind(kind, kind_size, location));
#line 1037 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1038 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1046 "bootstrap/stage0/ReCode.code"
struct Parsed_Literal_Expression* Parsed_Literal_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Token* literal) { struct Parsed_Literal_Expression* expression;
#line 1047 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Literal_Expression*) Parsed_Expression__create_kind(kind, kind_size, literal->location));
#line 1048 "bootstrap/stage0/ReCode.code"
    expression->literal = literal;
#line 1049 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1056 "bootstrap/stage0/ReCode.code"
struct Parsed_Add_Expression* Parsed_Add_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1057 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Add_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__ADD, left_expression, right_expression));}

#line 1064 "bootstrap/stage0/ReCode.code"
struct Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1065 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Address_Of_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__ADDRESS_OF, sizeof(struct Parsed_Address_Of_Expression), location, other_expression));}

#line 1074 "bootstrap/stage0/ReCode.code"
struct Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(struct Parsed_Expression* array_expression, struct Parsed_Expression* index_expression) { struct Parsed_Array_Access_Expression* expression;
#line 1075 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Array_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__ARRAY_ACCESS, sizeof(struct Parsed_Array_Access_Expression), array_expression->location));
#line 1076 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 1077 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 1078 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1086 "bootstrap/stage0/ReCode.code"
struct Parsed_Bool_Expression* Parsed_Bool_Expression__create(struct Token* literal, bool value) { struct Parsed_Bool_Expression* expression;
#line 1087 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Bool_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__BOOL, sizeof(struct Parsed_Bool_Expression), literal));
#line 1088 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 1089 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1097 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Argument* Parsed_Call_Argument__create(struct Parsed_Expression* expression) { struct Parsed_Call_Argument* argument;
#line 1098 "bootstrap/stage0/ReCode.code"
    argument = ((struct Parsed_Call_Argument*) malloc(sizeof(struct Parsed_Call_Argument)));
#line 1099 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 1100 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 1101 "bootstrap/stage0/ReCode.code"
    return argument;}

#line 1110 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Expression* Parsed_Call_Expression__create(struct Parsed_Expression* callee_expression) { struct Parsed_Call_Expression* expression;
#line 1111 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Call_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__CALL, sizeof(struct Parsed_Call_Expression), callee_expression->location));
#line 1112 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 1113 "bootstrap/stage0/ReCode.code"
    expression->first_argument = NULL;
#line 1114 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1122 "bootstrap/stage0/ReCode.code"
struct Parsed_Cast_Expression* Parsed_Cast_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression, struct Parsed_Type* type) { struct Parsed_Cast_Expression* expression;
#line 1123 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Cast_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__CAST, sizeof(struct Parsed_Cast_Expression), location, other_expression));
#line 1124 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1125 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1133 "bootstrap/stage0/ReCode.code"
struct Parsed_Character_Expression* Parsed_Character_Expression__create(struct Character_Token* literal) { struct Parsed_Character_Expression* expression;
#line 1134 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Character_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__CHARACTER, sizeof(struct Parsed_Character_Expression), ((struct Token*) literal)));
#line 1135 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1136 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1144 "bootstrap/stage0/ReCode.code"
struct Parsed_Dereference_Expression* Parsed_Dereference_Expression__create(struct Parsed_Expression* value_expression) { struct Parsed_Dereference_Expression* expression;
#line 1145 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Dereference_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__DEREFERENCE, sizeof(struct Parsed_Dereference_Expression), value_expression->location));
#line 1146 "bootstrap/stage0/ReCode.code"
    expression->value_expression = value_expression;
#line 1147 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1154 "bootstrap/stage0/ReCode.code"
struct Parsed_Divide_Expression* Parsed_Divide_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1155 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Divide_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__DIVIDE, left_expression, right_expression));}

#line 1162 "bootstrap/stage0/ReCode.code"
struct Parsed_Equals_Expression* Parsed_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1163 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__EQUALS, left_expression, right_expression));}

#line 1170 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Expression* Parsed_Greater_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1171 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Greater_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER, left_expression, right_expression));}

#line 1178 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1179 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Greater_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER_OR_EQUALS, left_expression, right_expression));}

#line 1187 "bootstrap/stage0/ReCode.code"
struct Parsed_Group_Expression* Parsed_Group_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) { struct Parsed_Group_Expression* expression;
#line 1188 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Group_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__GROUP, sizeof(struct Parsed_Group_Expression), location));
#line 1189 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1190 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1198 "bootstrap/stage0/ReCode.code"
struct Parsed_Integer_Expression* Parsed_Integer_Expression__create(struct Integer_Token* literal) { struct Parsed_Integer_Expression* expression;
#line 1199 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Integer_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__INTEGER, sizeof(struct Parsed_Integer_Expression), ((struct Token*) literal)));
#line 1200 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1201 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1208 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Expression* Parsed_Less_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1209 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Less_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS, left_expression, right_expression));}

#line 1216 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1217 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Less_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS_OR_EQUALS, left_expression, right_expression));}

#line 1224 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1225 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Logic_And_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_AND, left_expression, right_expression));}

#line 1232 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1233 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Logic_Or_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_OR, left_expression, right_expression));}

#line 1242 "bootstrap/stage0/ReCode.code"
struct Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(struct Parsed_Expression* object_expression, struct Token* member_name) { struct Parsed_Member_Access_Expression* expression;
#line 1243 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Member_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__MEMBER_ACCESS, sizeof(struct Parsed_Member_Access_Expression), object_expression->location));
#line 1244 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 1245 "bootstrap/stage0/ReCode.code"
    expression->member_name = member_name;
#line 1246 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1253 "bootstrap/stage0/ReCode.code"
struct Parsed_Minus_Expression* Parsed_Minus_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1254 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Minus_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__MINUS, sizeof(struct Parsed_Minus_Expression), location, other_expression));}

#line 1261 "bootstrap/stage0/ReCode.code"
struct Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1262 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Modulo_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MODULO, left_expression, right_expression));}

#line 1269 "bootstrap/stage0/ReCode.code"
struct Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1270 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Multiply_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MULTIPLY, left_expression, right_expression));}

#line 1277 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Expression* Parsed_Not_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1278 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Not_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__NOT, sizeof(struct Parsed_Not_Expression), location, other_expression));}

#line 1285 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1286 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Not_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__NOT_EQUALS, left_expression, right_expression));}

#line 1293 "bootstrap/stage0/ReCode.code"
struct Parsed_Null_Expression* Parsed_Null_Expression__create(struct Token* literal) {
#line 1294 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Null_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__NULL, sizeof(struct Parsed_Null_Expression), literal));}

#line 1302 "bootstrap/stage0/ReCode.code"
struct Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(struct Source_Location* location, struct Parsed_Type* type) { struct Parsed_Sizeof_Expression* expression;
#line 1303 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Sizeof_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SIZEOF, sizeof(struct Parsed_Sizeof_Expression), location));
#line 1304 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1305 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1313 "bootstrap/stage0/ReCode.code"
struct Parsed_String_Expression* Parsed_String_Expression__create(struct String_Token* literal) { struct Parsed_String_Expression* expression;
#line 1314 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_String_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__STRING, sizeof(struct Parsed_String_Expression), ((struct Token*) literal)));
#line 1315 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1316 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1323 "bootstrap/stage0/ReCode.code"
struct Parsed_Substract_Expression* Parsed_Substract_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1324 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Substract_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__SUBSTRACT, left_expression, right_expression));}

#line 1332 "bootstrap/stage0/ReCode.code"
struct Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(struct Token* name) { struct Parsed_Symbol_Expression* expression;
#line 1333 "bootstrap/stage0/ReCode.code"
    expression = ((struct Parsed_Symbol_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SYMBOL, sizeof(struct Parsed_Symbol_Expression), name->location));
#line 1334 "bootstrap/stage0/ReCode.code"
    expression->name = name;
#line 1335 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1359 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location) { struct Parsed_Statement* statement;
#line 1360 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Statement*) malloc(kind_size));
#line 1361 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 1362 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 1363 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 1364 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1372 "bootstrap/stage0/ReCode.code"
struct Parsed_Named_Statement* Parsed_Named_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location, struct Token* name) { struct Parsed_Named_Statement* statement;
#line 1373 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Named_Statement*) Parsed_Statement__create_kind(kind, kind_size, location));
#line 1374 "bootstrap/stage0/ReCode.code"
    statement->name = name;
#line 1375 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1384 "bootstrap/stage0/ReCode.code"
struct Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(struct Parsed_Expression* object_expression, struct Parsed_Expression* value_expression) { struct Parsed_Assignment_Statement* statement;
#line 1385 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Assignment_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__ASSIGNMENT, sizeof(struct Parsed_Assignment_Statement), object_expression->location));
#line 1386 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 1387 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 1388 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1396 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parsed_Block_Statement__create(struct Source_Location* location, struct Parsed_Statements* statements) { struct Parsed_Block_Statement* statement;
#line 1397 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Block_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__BLOCK, sizeof(struct Parsed_Block_Statement), location));
#line 1398 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1399 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1406 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Break_Statement__create(struct Source_Location* location) {
#line 1407 "bootstrap/stage0/ReCode.code"
    return Parsed_Statement__create_kind(Parsed_Statement_Kind__BREAK, sizeof(struct Parsed_Break_Statement), location);}

#line 1415 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Member* Parsed_Enum_Member__create(struct Token* name) { struct Parsed_Enum_Member* member;
#line 1416 "bootstrap/stage0/ReCode.code"
    member = ((struct Parsed_Enum_Member*) malloc(sizeof(struct Parsed_Enum_Member)));
#line 1417 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1418 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1419 "bootstrap/stage0/ReCode.code"
    return member;}

#line 1427 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Statement* Parsed_Enum_Statement__create(struct Source_Location* location, struct Token* name) { struct Parsed_Enum_Statement* statement;
#line 1428 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Enum_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__ENUM, sizeof(struct Parsed_Enum_Statement), location, name));
#line 1429 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1430 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1438 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression_Statement* Parsed_Expression_Statement__create(struct Parsed_Expression* expression) { struct Parsed_Expression_Statement* statement;
#line 1439 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Expression_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__EXPRESSION, sizeof(struct Parsed_Expression_Statement), expression->location));
#line 1440 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1441 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1452 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Function_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* resturn_type, struct Parsed_Statements* statements, bool is_external) { struct Parsed_Function_Statement* statement;
#line 1453 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Function_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__FUNCTION, sizeof(struct Parsed_Function_Statement), location, name));
#line 1454 "bootstrap/stage0/ReCode.code"
    statement->first_parameter = first_parameter;
#line 1455 "bootstrap/stage0/ReCode.code"
    statement->return_type = resturn_type;
#line 1456 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1457 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1458 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1468 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_If_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* true_statement, struct Parsed_Statement* false_statement) { struct Parsed_If_Statement* statement;
#line 1469 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_If_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__IF, sizeof(struct Parsed_If_Statement), location));
#line 1470 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1471 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 1472 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 1473 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1480 "bootstrap/stage0/ReCode.code"
struct Parsed_Opaque_Type_Statement* Parsed_Opaque_Type_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1481 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Opaque_Type_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__OPAQUE_TYPE, sizeof(struct Parsed_Opaque_Type_Statement), location, name));}

#line 1489 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Return_Statement__create(struct Source_Location* location, struct Parsed_Expression* expression) { struct Parsed_Return_Statement* statement;
#line 1490 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Return_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__RETURN, sizeof(struct Parsed_Return_Statement), location));
#line 1491 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1492 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1501 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Member* Parsed_Struct_Member__create(struct Token* name, struct Parsed_Type* type) { struct Parsed_Struct_Member* member;
#line 1502 "bootstrap/stage0/ReCode.code"
    member = ((struct Parsed_Struct_Member*) malloc(sizeof(struct Parsed_Struct_Member)));
#line 1503 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1504 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 1505 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1506 "bootstrap/stage0/ReCode.code"
    return member;}

#line 1514 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Statement* Parsed_Struct_Statement__create(struct Source_Location* location, struct Token* name) { struct Parsed_Struct_Statement* statement;
#line 1515 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Struct_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__STRUCT, sizeof(struct Parsed_Struct_Statement), location, name));
#line 1516 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1517 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1527 "bootstrap/stage0/ReCode.code"
struct Parsed_Variable_Statement* Parsed_Variable_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Type* type, bool is_external) { struct Parsed_Variable_Statement* statement;
#line 1528 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_Variable_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__VARIABLE, sizeof(struct Parsed_Variable_Statement), location, name));
#line 1529 "bootstrap/stage0/ReCode.code"
    statement->type = type;
#line 1530 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1531 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 1540 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_While_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* body_statement) { struct Parsed_While_Statement* statement;
#line 1541 "bootstrap/stage0/ReCode.code"
    statement = ((struct Parsed_While_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__WHILE, sizeof(struct Parsed_While_Statement), location));
#line 1542 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1543 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 1544 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) statement);}

#line 1553 "bootstrap/stage0/ReCode.code"
struct Parsed_Statements* Parsed_Statements__create(bool has_globals) { struct Parsed_Statements* statements;
#line 1554 "bootstrap/stage0/ReCode.code"
    statements = ((struct Parsed_Statements*) malloc(sizeof(struct Parsed_Statements)));
#line 1555 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 1556 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 1557 "bootstrap/stage0/ReCode.code"
    statements->has_globals = has_globals;
#line 1558 "bootstrap/stage0/ReCode.code"
    return statements;}

#line 1561 "bootstrap/stage0/ReCode.code"
void Parsed_Statements__append(struct Parsed_Statements* self, struct Parsed_Statement* statement) {
#line 1562 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->first_statement == NULL) {
#line 1562 "bootstrap/stage0/ReCode.code"
            {
#line 1563 "bootstrap/stage0/ReCode.code"
                self->first_statement = statement;
            } goto if__end__1; } if__else__1: ;
#line 1564 "bootstrap/stage0/ReCode.code"
        {
#line 1565 "bootstrap/stage0/ReCode.code"
            self->last_statement->next_statement = statement;
        } if__end__1: ;
    }
#line 1567 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;}

#line 1570 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* Parsed_Compilation_Unit__create() { struct Parsed_Source* compilation_unit;
#line 1571 "bootstrap/stage0/ReCode.code"
    compilation_unit = ((struct Parsed_Source*) malloc(sizeof(struct Parsed_Source)));
#line 1572 "bootstrap/stage0/ReCode.code"
    compilation_unit->statements = Parsed_Statements__create(true);
#line 1573 "bootstrap/stage0/ReCode.code"
    return compilation_unit;}

#line 1586 "bootstrap/stage0/ReCode.code"
void Parser__error(struct Parser* self, struct String* message) {
#line 1587 "bootstrap/stage0/ReCode.code"
    Token__error(self->scanner->current_token, message);}

#line 1590 "bootstrap/stage0/ReCode.code"
void Parser__warning(struct Parser* self, struct String* message) {
#line 1591 "bootstrap/stage0/ReCode.code"
    Token__warning(self->scanner->current_token, message);}

#line 1594 "bootstrap/stage0/ReCode.code"
struct Token* Parser__peek_token(struct Parser* self, uint8_t offset) {
#line 1595 "bootstrap/stage0/ReCode.code"
    return Scanner__peek_token(self->scanner, offset);}

#line 1598 "bootstrap/stage0/ReCode.code"
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token*), bool first_required, bool (*second_is)(struct Token*), bool second_required, bool (*third_is)(struct Token*)) { uint8_t peek_offset;
#line 1599 "bootstrap/stage0/ReCode.code"
    peek_offset = ((uint8_t) 0);
#line 1600 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (first_is(Parser__peek_token(self, peek_offset))) {
#line 1600 "bootstrap/stage0/ReCode.code"
            {
#line 1601 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + ((uint8_t) 1);
            } goto if__end__1; } if__else__1: ;
#line 1602 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (first_required) {
#line 1602 "bootstrap/stage0/ReCode.code"
                {
#line 1603 "bootstrap/stage0/ReCode.code"
                    return false;
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 1605 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (second_is != NULL) {
#line 1605 "bootstrap/stage0/ReCode.code"
            {
#line 1606 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (second_is(Parser__peek_token(self, peek_offset))) {
#line 1606 "bootstrap/stage0/ReCode.code"
                        {
#line 1607 "bootstrap/stage0/ReCode.code"
                            peek_offset = peek_offset + ((uint8_t) 1);
                        } goto if__end__4; } if__else__4: ;
#line 1608 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (second_required) {
#line 1608 "bootstrap/stage0/ReCode.code"
                            {
#line 1609 "bootstrap/stage0/ReCode.code"
                                return false;
                            } goto if__end__5; } if__end__5: ;
                    } if__end__4: ;
                }
            } goto if__end__3; } if__end__3: ;
    }
#line 1612 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (third_is != NULL) {
#line 1612 "bootstrap/stage0/ReCode.code"
            {
#line 1613 "bootstrap/stage0/ReCode.code"
                return third_is(Parser__peek_token(self, peek_offset));
            } goto if__end__6; } if__end__6: ;
    }
#line 1615 "bootstrap/stage0/ReCode.code"
    return true;}

#line 1618 "bootstrap/stage0/ReCode.code"
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token*), bool first_required, bool (*second_is)(struct Token*)) {
#line 1619 "bootstrap/stage0/ReCode.code"
    return Parser__matches_three(self, first_is, first_required, second_is, true, NULL);}

#line 1622 "bootstrap/stage0/ReCode.code"
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token*)) {
#line 1623 "bootstrap/stage0/ReCode.code"
    return Parser__matches_two(self, first_is, true, NULL);}

#line 1626 "bootstrap/stage0/ReCode.code"
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token*)) {
#line 1627 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, check)) {
#line 1627 "bootstrap/stage0/ReCode.code"
            { struct Token* token;
#line 1628 "bootstrap/stage0/ReCode.code"
                token = self->scanner->current_token;
#line 1629 "bootstrap/stage0/ReCode.code"
                Scanner__next_token(self->scanner);
#line 1630 "bootstrap/stage0/ReCode.code"
                return token;
            } goto if__end__1; } if__end__1: ;
    }
#line 1632 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unexpected token"));
#line 1633 "bootstrap/stage0/ReCode.code"
    abort();}

#line 1636 "bootstrap/stage0/ReCode.code"
void Parser__consume_comment(struct Parser* self) {
#line 1637 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_comment);}

#line 1640 "bootstrap/stage0/ReCode.code"
void Parser__consume_space(struct Parser* self, uint16_t count) {
#line 1641 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_space)) {
#line 1641 "bootstrap/stage0/ReCode.code"
            { struct Space_Token* token;
#line 1642 "bootstrap/stage0/ReCode.code"
                token = ((struct Space_Token*) Parser__consume_token(self, Token__is_space));
#line 1643 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (token->count != count) {
#line 1643 "bootstrap/stage0/ReCode.code"
                        { struct String* message;
#line 1644 "bootstrap/stage0/ReCode.code"
                            message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), ((int16_t) token->count)), " spaces where "), ((int16_t) count)), " were expected");
#line 1645 "bootstrap/stage0/ReCode.code"
                            Token__warning(((struct Token*) token), message);
#line 1646 "bootstrap/stage0/ReCode.code"
                            String__delete(message);
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 1648 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (count > ((uint16_t) 0)) {
#line 1648 "bootstrap/stage0/ReCode.code"
                { struct String* message;
#line 1649 "bootstrap/stage0/ReCode.code"
                    message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), ((int16_t) 0)), " spaces where "), ((int16_t) count)), " were expected");
#line 1650 "bootstrap/stage0/ReCode.code"
                    Parser__warning(self, message);
#line 1651 "bootstrap/stage0/ReCode.code"
                    String__delete(message);
                } goto if__end__3; } if__end__3: ;
        } if__end__1: ;
    }}

#line 1655 "bootstrap/stage0/ReCode.code"
void Parser__consume_end_of_line(struct Parser* self) { struct Token* token;
#line 1656 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1656 "bootstrap/stage0/ReCode.code"
            {
#line 1657 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1658 "bootstrap/stage0/ReCode.code"
                Parser__consume_comment(self);
            } goto if__end__1; } if__else__1: ;
#line 1659 "bootstrap/stage0/ReCode.code"
        {
#line 1660 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, ((uint16_t) 0));
        } if__end__1: ;
    }
#line 1662 "bootstrap/stage0/ReCode.code"
    token = Parser__consume_token(self, Token__is_end_of_line);
#line 1663 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Token__is_end_of_file(token)) {
#line 1663 "bootstrap/stage0/ReCode.code"
            {
#line 1664 "bootstrap/stage0/ReCode.code"
                Token__warning(token, String__create_from("Unexpected end of file"));
            } goto if__end__2; } if__end__2: ;
    }}

#line 1668 "bootstrap/stage0/ReCode.code"
bool Parser__consume_empty_line(struct Parser* self) {
#line 1669 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_end_of_file)) {
#line 1669 "bootstrap/stage0/ReCode.code"
            {
#line 1670 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 1672 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 1672 "bootstrap/stage0/ReCode.code"
            {
#line 1673 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1673 "bootstrap/stage0/ReCode.code"
                        {
#line 1674 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 1675 "bootstrap/stage0/ReCode.code"
                            Parser__consume_comment(self);
                        } goto if__end__3; } if__else__3: ;
#line 1676 "bootstrap/stage0/ReCode.code"
                    {
#line 1677 "bootstrap/stage0/ReCode.code"
                        Parser__consume_space(self, ((uint16_t) 0));
                    } if__end__3: ;
                }
#line 1679 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_end_of_line);
#line 1680 "bootstrap/stage0/ReCode.code"
                return true;
            } goto if__end__2; } if__end__2: ;
    }
#line 1682 "bootstrap/stage0/ReCode.code"
    return false;}

#line 1693 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_primary_expression(struct Parser* self) {
#line 1694 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_true)) {
#line 1694 "bootstrap/stage0/ReCode.code"
            {
#line 1695 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true));
            } goto if__end__1; } if__end__1: ;
    }
#line 1697 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_null)) {
#line 1697 "bootstrap/stage0/ReCode.code"
            {
#line 1698 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null)));
            } goto if__end__2; } if__end__2: ;
    }
#line 1700 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (Parser__matches_one(self, Token__is_false)) {
#line 1700 "bootstrap/stage0/ReCode.code"
            {
#line 1701 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false));
            } goto if__end__3; } if__end__3: ;
    }
#line 1703 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (Parser__matches_one(self, Token__is_identifier)) {
#line 1703 "bootstrap/stage0/ReCode.code"
            {
#line 1704 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier)));
            } goto if__end__4; } if__end__4: ;
    }
#line 1706 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (Parser__matches_one(self, Token__is_integer)) {
#line 1706 "bootstrap/stage0/ReCode.code"
            {
#line 1707 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Integer_Expression__create(((struct Integer_Token*) Parser__consume_token(self, Token__is_integer))));
            } goto if__end__5; } if__end__5: ;
    }
#line 1709 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (Parser__matches_one(self, Token__is_character)) {
#line 1709 "bootstrap/stage0/ReCode.code"
            {
#line 1710 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Character_Expression__create(((struct Character_Token*) Parser__consume_token(self, Token__is_character))));
            } goto if__end__6; } if__end__6: ;
    }
#line 1712 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (Parser__matches_one(self, Token__is_string)) {
#line 1712 "bootstrap/stage0/ReCode.code"
            {
#line 1713 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_String_Expression__create(((struct String_Token*) Parser__consume_token(self, Token__is_string))));
            } goto if__end__7; } if__end__7: ;
    }
#line 1715 "bootstrap/stage0/ReCode.code"
    if__start__8: { if (Parser__matches_one(self, Token__is_opening_paren)) {
#line 1715 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1716 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1717 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1718 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_expression(self);
#line 1719 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1720 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 1721 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Group_Expression__create(location, expression));
            } goto if__end__8; } if__end__8: ;
    }
#line 1723 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unsupported primary expression"));
#line 1724 "bootstrap/stage0/ReCode.code"
    abort();}

#line 1729 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_access_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1730 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_primary_expression(self);
#line 1731 "bootstrap/stage0/ReCode.code"
    while (true) { struct Parsed_Expression* old_expression;
#line 1732 "bootstrap/stage0/ReCode.code"
        old_expression = expression;
#line 1733 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_dot)) {
#line 1733 "bootstrap/stage0/ReCode.code"
                {
#line 1734 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1735 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_dot);
#line 1736 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1737 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1737 "bootstrap/stage0/ReCode.code"
                            {
#line 1738 "bootstrap/stage0/ReCode.code"
                                Parser__consume_token(self, Token__is_asterisk);
#line 1739 "bootstrap/stage0/ReCode.code"
                                expression = ((struct Parsed_Expression*) Parsed_Dereference_Expression__create(expression));
                            } goto if__end__2; } if__else__2: ;
#line 1740 "bootstrap/stage0/ReCode.code"
                        { struct Token* name;
#line 1741 "bootstrap/stage0/ReCode.code"
                            name = Parser__consume_token(self, Token__is_identifier);
#line 1742 "bootstrap/stage0/ReCode.code"
                            if__start__3: { if (String__equals_cstring(name->lexeme, "as")) {
#line 1742 "bootstrap/stage0/ReCode.code"
                                    { struct Parsed_Type* type;
#line 1743 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_space(self, ((uint16_t) 0));
#line 1744 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_token(self, Token__is_opening_paren);
#line 1745 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_space(self, ((uint16_t) 0));
#line 1746 "bootstrap/stage0/ReCode.code"
                                        type = Parser__parse_type(self);
#line 1747 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_space(self, ((uint16_t) 0));
#line 1748 "bootstrap/stage0/ReCode.code"
                                        Parser__consume_token(self, Token__is_closing_paren);
#line 1749 "bootstrap/stage0/ReCode.code"
                                        expression = ((struct Parsed_Expression*) Parsed_Cast_Expression__create(name->location, expression, type));
                                    } goto if__end__3; } if__else__3: ;
#line 1750 "bootstrap/stage0/ReCode.code"
                                {
#line 1751 "bootstrap/stage0/ReCode.code"
                                    expression = ((struct Parsed_Expression*) Parsed_Member_Access_Expression__create(expression, name));
                                } if__end__3: ;
                            }
                        } if__end__2: ;
                    }
                } goto if__end__1; } if__end__1: ;
        }
#line 1755 "bootstrap/stage0/ReCode.code"
        if__start__4: { if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
#line 1755 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Call_Expression* call_expression;
#line 1756 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1757 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_opening_paren);
#line 1758 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1759 "bootstrap/stage0/ReCode.code"
                    call_expression = Parsed_Call_Expression__create(expression);
#line 1760 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (!(Parser__matches_one(self, Token__is_closing_paren))) {
#line 1760 "bootstrap/stage0/ReCode.code"
                            { struct Parsed_Call_Argument* last_argument;
#line 1761 "bootstrap/stage0/ReCode.code"
                                last_argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1762 "bootstrap/stage0/ReCode.code"
                                call_expression->first_argument = last_argument;
#line 1763 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 0));
#line 1764 "bootstrap/stage0/ReCode.code"
                                while (Parser__matches_one(self, Token__is_comma)) { struct Parsed_Call_Argument* argument;
#line 1765 "bootstrap/stage0/ReCode.code"
                                    Parser__consume_token(self, Token__is_comma);
#line 1766 "bootstrap/stage0/ReCode.code"
                                    Parser__consume_space(self, ((uint16_t) 1));
#line 1767 "bootstrap/stage0/ReCode.code"
                                    argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1768 "bootstrap/stage0/ReCode.code"
                                    last_argument->next_argument = argument;
#line 1769 "bootstrap/stage0/ReCode.code"
                                    last_argument = argument;
#line 1770 "bootstrap/stage0/ReCode.code"
                                    Parser__consume_space(self, ((uint16_t) 0));
                                }
                            } goto if__end__5; } if__end__5: ;
                    }
#line 1773 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) call_expression);
#line 1774 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_closing_paren);
                } goto if__end__4; } if__end__4: ;
        }
#line 1776 "bootstrap/stage0/ReCode.code"
        if__start__6: { if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
#line 1776 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* index_expression;
#line 1777 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1778 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_opening_bracket);
#line 1779 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1780 "bootstrap/stage0/ReCode.code"
                    index_expression = Parser__parse_expression(self);
#line 1781 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 1782 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_closing_bracket);
#line 1783 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Array_Access_Expression__create(expression, index_expression));
                } goto if__end__6; } if__end__6: ;
        }
#line 1785 "bootstrap/stage0/ReCode.code"
        if__start__7: { if (old_expression == expression) {
#line 1785 "bootstrap/stage0/ReCode.code"
                {
#line 1786 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__7; } if__end__7: ;
        }
    }
#line 1789 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1798 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_unary_expression(struct Parser* self) {
#line 1799 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_minus)) {
#line 1799 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1800 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_minus)->location;
#line 1801 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1802 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_unary_expression(self);
#line 1803 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Minus_Expression__create(location, expression));
            } goto if__end__1; } if__end__1: ;
    }
#line 1805 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_exclamation_mark)) {
#line 1805 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1806 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_exclamation_mark)->location;
#line 1807 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1808 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_unary_expression(self);
#line 1809 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Not_Expression__create(location, expression));
            } goto if__end__2; } if__end__2: ;
    }
#line 1811 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (Parser__matches_one(self, Token__is_ampersand)) {
#line 1811 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Expression* expression;
#line 1812 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_ampersand)->location;
#line 1813 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1814 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_unary_expression(self);
#line 1815 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Address_Of_Expression__create(location, expression));
            } goto if__end__3; } if__end__3: ;
    }
#line 1817 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (Parser__matches_one(self, Token__is_sizeof)) {
#line 1817 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Type* type;
#line 1818 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_sizeof)->location;
#line 1819 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1820 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_opening_paren);
#line 1821 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1822 "bootstrap/stage0/ReCode.code"
                type = Parser__parse_type(self);
#line 1823 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 1824 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 1825 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Expression*) Parsed_Sizeof_Expression__create(location, type));
            } goto if__end__4; } if__end__4: ;
    }
#line 1827 "bootstrap/stage0/ReCode.code"
    return Parser__parse_access_expression(self);}

#line 1830 "bootstrap/stage0/ReCode.code"
bool Token__is_mutliplication(struct Token* self) {
#line 1831 "bootstrap/stage0/ReCode.code"
    return Token__is_asterisk(self) || Token__is_slash(self) || Token__is_percent(self);}

#line 1836 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_multiplication_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1837 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_unary_expression(self);
#line 1838 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
#line 1839 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1840 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1840 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1841 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_asterisk);
#line 1842 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1843 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_unary_expression(self);
#line 1844 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Multiply_Expression__create(expression, right_expression));
                } goto if__end__1; } if__else__1: ;
#line 1845 "bootstrap/stage0/ReCode.code"
            if__start__2: { if (Parser__matches_one(self, Token__is_slash)) {
#line 1845 "bootstrap/stage0/ReCode.code"
                    { struct Parsed_Expression* right_expression;
#line 1846 "bootstrap/stage0/ReCode.code"
                        Parser__consume_token(self, Token__is_slash);
#line 1847 "bootstrap/stage0/ReCode.code"
                        Parser__consume_space(self, ((uint16_t) 1));
#line 1848 "bootstrap/stage0/ReCode.code"
                        right_expression = Parser__parse_unary_expression(self);
#line 1849 "bootstrap/stage0/ReCode.code"
                        expression = ((struct Parsed_Expression*) Parsed_Divide_Expression__create(expression, right_expression));
                    } goto if__end__2; } if__else__2: ;
#line 1850 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1851 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_percent);
#line 1852 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1853 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_unary_expression(self);
#line 1854 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Modulo_Expression__create(expression, right_expression));
                } if__end__2: ;
            } if__end__1: ;
        }
    }
#line 1857 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1860 "bootstrap/stage0/ReCode.code"
bool Token__is_addition(struct Token* self) {
#line 1861 "bootstrap/stage0/ReCode.code"
    return Token__is_plus(self) || Token__is_minus(self);}

#line 1866 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_addition_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1867 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_multiplication_expression(self);
#line 1868 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
#line 1869 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1870 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (Parser__matches_one(self, Token__is_plus)) {
#line 1870 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1871 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_plus);
#line 1872 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1873 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_multiplication_expression(self);
#line 1874 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Add_Expression__create(expression, right_expression));
                } goto if__end__1; } if__else__1: ;
#line 1875 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Expression* right_expression;
#line 1876 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_minus);
#line 1877 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1878 "bootstrap/stage0/ReCode.code"
                right_expression = Parser__parse_multiplication_expression(self);
#line 1879 "bootstrap/stage0/ReCode.code"
                expression = ((struct Parsed_Expression*) Parsed_Substract_Expression__create(expression, right_expression));
            } if__end__1: ;
        }
    }
#line 1882 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1887 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_comparison_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1888 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_addition_expression(self);
#line 1889 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
#line 1889 "bootstrap/stage0/ReCode.code"
            {
#line 1890 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1891 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_less_than);
#line 1892 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (Parser__matches_one(self, Token__is_equals)) {
#line 1892 "bootstrap/stage0/ReCode.code"
                        { struct Parsed_Expression* right_expression;
#line 1893 "bootstrap/stage0/ReCode.code"
                            Parser__consume_token(self, Token__is_equals);
#line 1894 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, ((uint16_t) 1));
#line 1895 "bootstrap/stage0/ReCode.code"
                            right_expression = Parser__parse_addition_expression(self);
#line 1896 "bootstrap/stage0/ReCode.code"
                            expression = ((struct Parsed_Expression*) Parsed_Less_Or_Equals_Expression__create(expression, right_expression));
                        } goto if__end__2; } if__else__2: ;
#line 1897 "bootstrap/stage0/ReCode.code"
                    { struct Parsed_Expression* right_expression;
#line 1898 "bootstrap/stage0/ReCode.code"
                        Parser__consume_space(self, ((uint16_t) 1));
#line 1899 "bootstrap/stage0/ReCode.code"
                        right_expression = Parser__parse_addition_expression(self);
#line 1900 "bootstrap/stage0/ReCode.code"
                        expression = ((struct Parsed_Expression*) Parsed_Less_Expression__create(expression, right_expression));
                    } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 1902 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
#line 1902 "bootstrap/stage0/ReCode.code"
                {
#line 1903 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1904 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_greater_than);
#line 1905 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (Parser__matches_one(self, Token__is_equals)) {
#line 1905 "bootstrap/stage0/ReCode.code"
                            { struct Parsed_Expression* right_expression;
#line 1906 "bootstrap/stage0/ReCode.code"
                                Parser__consume_token(self, Token__is_equals);
#line 1907 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 1));
#line 1908 "bootstrap/stage0/ReCode.code"
                                right_expression = Parser__parse_addition_expression(self);
#line 1909 "bootstrap/stage0/ReCode.code"
                                expression = ((struct Parsed_Expression*) Parsed_Greater_Or_Equals_Expression__create(expression, right_expression));
                            } goto if__end__4; } if__else__4: ;
#line 1910 "bootstrap/stage0/ReCode.code"
                        { struct Parsed_Expression* right_expression;
#line 1911 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, ((uint16_t) 1));
#line 1912 "bootstrap/stage0/ReCode.code"
                            right_expression = Parser__parse_addition_expression(self);
#line 1913 "bootstrap/stage0/ReCode.code"
                            expression = ((struct Parsed_Expression*) Parsed_Greater_Expression__create(expression, right_expression));
                        } if__end__4: ;
                    }
                } goto if__end__3; } if__end__3: ;
        } if__end__1: ;
    }
#line 1916 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1921 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_equality_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1922 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_comparison_expression(self);
#line 1923 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
#line 1923 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Expression* right_expression;
#line 1924 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1925 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_equals);
#line 1926 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_equals);
#line 1927 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 1928 "bootstrap/stage0/ReCode.code"
                right_expression = Parser__parse_comparison_expression(self);
#line 1929 "bootstrap/stage0/ReCode.code"
                expression = ((struct Parsed_Expression*) Parsed_Equals_Expression__create(expression, right_expression));
            } goto if__end__1; } if__else__1: ;
#line 1930 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
#line 1930 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Expression* right_expression;
#line 1931 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1932 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_exclamation_mark);
#line 1933 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_equals);
#line 1934 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 1935 "bootstrap/stage0/ReCode.code"
                    right_expression = Parser__parse_comparison_expression(self);
#line 1936 "bootstrap/stage0/ReCode.code"
                    expression = ((struct Parsed_Expression*) Parsed_Not_Equals_Expression__create(expression, right_expression));
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 1938 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1943 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_and_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1944 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_equality_expression(self);
#line 1945 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_ampersand, true, Token__is_ampersand)) { struct Parsed_Expression* right_expression;
#line 1946 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1947 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1948 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1949 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1950 "bootstrap/stage0/ReCode.code"
        right_expression = Parser__parse_equality_expression(self);
#line 1951 "bootstrap/stage0/ReCode.code"
        expression = ((struct Parsed_Expression*) Parsed_Logic_And_Expression__create(expression, right_expression));
    }
#line 1953 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1958 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_or_expression(struct Parser* self) { struct Parsed_Expression* expression;
#line 1959 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_logic_and_expression(self);
#line 1960 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_vertical_bar, true, Token__is_vertical_bar)) { struct Parsed_Expression* right_expression;
#line 1961 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1962 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1963 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1964 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1965 "bootstrap/stage0/ReCode.code"
        right_expression = Parser__parse_logic_and_expression(self);
#line 1966 "bootstrap/stage0/ReCode.code"
        expression = ((struct Parsed_Expression*) Parsed_Logic_Or_Expression__create(expression, right_expression));
    }
#line 1968 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 1973 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_expression(struct Parser* self) {
#line 1974 "bootstrap/stage0/ReCode.code"
    return Parser__parse_logic_or_expression(self);}

#line 1979 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_struct(struct Parser* self) { struct Token* name; struct Parsed_Struct_Statement* struct_statement; struct Parsed_Struct_Member* last_member;
#line 1980 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_struct);
#line 1981 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 1982 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 1983 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 1984 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 1985 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 1986 "bootstrap/stage0/ReCode.code"
    struct_statement = Parsed_Struct_Statement__create(name->location, name);
#line 1987 "bootstrap/stage0/ReCode.code"
    last_member = NULL;
#line 1988 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 1989 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 1992 "bootstrap/stage0/ReCode.code"
    while (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace))) { struct Token* name; struct Parsed_Type* type; struct Parsed_Struct_Member* member;
#line 1993 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 1994 "bootstrap/stage0/ReCode.code"
        name = Parser__consume_token(self, Token__is_identifier);
#line 1995 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 0));
#line 1996 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_colon);
#line 1997 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, ((uint16_t) 1));
#line 1998 "bootstrap/stage0/ReCode.code"
        type = Parser__parse_type(self);
#line 1999 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2000 "bootstrap/stage0/ReCode.code"
        member = Parsed_Struct_Member__create(name, type);
#line 2001 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (last_member == NULL) {
#line 2001 "bootstrap/stage0/ReCode.code"
                {
#line 2002 "bootstrap/stage0/ReCode.code"
                    struct_statement->first_member = member;
#line 2003 "bootstrap/stage0/ReCode.code"
                    last_member = member;
                } goto if__end__1; } if__else__1: ;
#line 2004 "bootstrap/stage0/ReCode.code"
            {
#line 2005 "bootstrap/stage0/ReCode.code"
                last_member->next_member = member;
#line 2006 "bootstrap/stage0/ReCode.code"
                last_member = member;
            } if__end__1: ;
        }
#line 2008 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2012 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2013 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2014 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2015 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) struct_statement);}

#line 2020 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_external_type(struct Parser* self) { struct Token* name;
#line 2021 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_type);
#line 2022 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2023 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2024 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) Parsed_Opaque_Type_Statement__create(name->location, name));}

#line 2029 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_enum(struct Parser* self) { struct Token* name; struct Parsed_Enum_Statement* enum_statement; struct Parsed_Enum_Member* last_member;
#line 2030 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_enum);
#line 2031 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2032 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2033 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2034 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2035 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2036 "bootstrap/stage0/ReCode.code"
    enum_statement = Parsed_Enum_Statement__create(name->location, name);
#line 2037 "bootstrap/stage0/ReCode.code"
    last_member = NULL;
#line 2038 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 2039 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 2042 "bootstrap/stage0/ReCode.code"
    while (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace))) { struct Token* name; struct Parsed_Enum_Member* member;
#line 2043 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2044 "bootstrap/stage0/ReCode.code"
        name = Parser__consume_token(self, Token__is_identifier);
#line 2045 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2046 "bootstrap/stage0/ReCode.code"
        member = Parsed_Enum_Member__create(name);
#line 2047 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (last_member == NULL) {
#line 2047 "bootstrap/stage0/ReCode.code"
                {
#line 2048 "bootstrap/stage0/ReCode.code"
                    enum_statement->first_member = member;
#line 2049 "bootstrap/stage0/ReCode.code"
                    last_member = member;
                } goto if__end__1; } if__else__1: ;
#line 2050 "bootstrap/stage0/ReCode.code"
            {
#line 2051 "bootstrap/stage0/ReCode.code"
                last_member->next_member = member;
#line 2052 "bootstrap/stage0/ReCode.code"
                last_member = member;
            } if__end__1: ;
        }
#line 2054 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2058 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2059 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2060 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2061 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) enum_statement);}

#line 2067 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parser__parse_type(struct Parser* self) {
#line 2068 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_three(self, Token__is_opening_paren, true, Token__is_space, false, Token__is_func)) {
#line 2068 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location; struct Parsed_Function_Parameter* first_parameter; struct Parsed_Type* return_type;
#line 2069 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 2070 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2071 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_func);
#line 2072 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2073 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_opening_paren);
#line 2074 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2075 "bootstrap/stage0/ReCode.code"
                first_parameter = NULL;
#line 2076 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (!(Parser__matches_one(self, Token__is_closing_paren))) {
#line 2076 "bootstrap/stage0/ReCode.code"
                        { struct Parsed_Type* type; struct Parsed_Function_Parameter* last_parameter;
#line 2077 "bootstrap/stage0/ReCode.code"
                            type = Parser__parse_type(self);
#line 2078 "bootstrap/stage0/ReCode.code"
                            Parser__consume_space(self, ((uint16_t) 0));
#line 2079 "bootstrap/stage0/ReCode.code"
                            first_parameter = Parsed_Function_Parameter__create(type->location, NULL, type);
#line 2080 "bootstrap/stage0/ReCode.code"
                            last_parameter = first_parameter;
#line 2081 "bootstrap/stage0/ReCode.code"
                            while (!(Parser__matches_one(self, Token__is_closing_paren))) { struct Parsed_Type* type;
#line 2082 "bootstrap/stage0/ReCode.code"
                                Parser__consume_token(self, Token__is_comma);
#line 2083 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 1));
#line 2084 "bootstrap/stage0/ReCode.code"
                                type = Parser__parse_type(self);
#line 2085 "bootstrap/stage0/ReCode.code"
                                Parser__consume_space(self, ((uint16_t) 0));
#line 2086 "bootstrap/stage0/ReCode.code"
                                last_parameter->next_parameter = Parsed_Function_Parameter__create(type->location, NULL, type);
#line 2087 "bootstrap/stage0/ReCode.code"
                                last_parameter = last_parameter->next_parameter;
                            }
                        } goto if__end__2; } if__end__2: ;
                }
#line 2090 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 2091 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2092 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_minus);
#line 2093 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2094 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_greater_than);
#line 2095 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2096 "bootstrap/stage0/ReCode.code"
                return_type = Parser__parse_type(self);
#line 2097 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2098 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 2099 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Type*) Parsed_Function_Type__create(location, first_parameter, return_type));
            } goto if__end__1; } if__else__1: ;
#line 2100 "bootstrap/stage0/ReCode.code"
        { struct Token* name; struct Parsed_Type* type;
#line 2101 "bootstrap/stage0/ReCode.code"
            name = Parser__consume_token(self, Token__is_identifier);
#line 2102 "bootstrap/stage0/ReCode.code"
            type = ((struct Parsed_Type*) Parsed_Named_Type__create(name));
#line 2103 "bootstrap/stage0/ReCode.code"
            while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
#line 2104 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2105 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_asterisk);
#line 2106 "bootstrap/stage0/ReCode.code"
                type = ((struct Parsed_Type*) Parsed_Pointer_Type__create(type));
            }
#line 2108 "bootstrap/stage0/ReCode.code"
            return type;
        } if__end__1: ;
    }}

#line 2114 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_variable(struct Parser* self) { struct Token* name; struct Parsed_Type* type; struct Parsed_Expression* value_expression; struct Parsed_Variable_Statement* variable_statement;
#line 2115 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_let);
#line 2116 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2117 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2118 "bootstrap/stage0/ReCode.code"
    type = NULL;
#line 2119 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_colon)) {
#line 2119 "bootstrap/stage0/ReCode.code"
            {
#line 2120 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2121 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_colon);
#line 2122 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2123 "bootstrap/stage0/ReCode.code"
                type = Parser__parse_type(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 2125 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2126 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_equals);
#line 2127 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2129 "bootstrap/stage0/ReCode.code"
    ;
#line 2130 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_undefined)) {
#line 2130 "bootstrap/stage0/ReCode.code"
            {
#line 2131 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_undefined);
#line 2132 "bootstrap/stage0/ReCode.code"
                value_expression = NULL;
            } goto if__end__2; } if__else__2: ;
#line 2133 "bootstrap/stage0/ReCode.code"
        {
#line 2134 "bootstrap/stage0/ReCode.code"
            value_expression = Parser__parse_expression(self);
        } if__end__2: ;
    }
#line 2136 "bootstrap/stage0/ReCode.code"
    variable_statement = Parsed_Variable_Statement__create(name->location, name, type, false);
#line 2137 "bootstrap/stage0/ReCode.code"
    variable_statement->expression = value_expression;
#line 2138 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) variable_statement);}

#line 2143 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_external_variable(struct Parser* self) { struct Token* name; struct Parsed_Type* type;
#line 2144 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2145 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2146 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_colon);
#line 2147 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2148 "bootstrap/stage0/ReCode.code"
    type = Parser__parse_type(self);
#line 2149 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) Parsed_Variable_Statement__create(name->location, name, type, true));}

#line 2154 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Statements* statements;
#line 2155 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_opening_brace)->location;
#line 2156 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2157 "bootstrap/stage0/ReCode.code"
    statements = Parsed_Statements__create(false);
#line 2158 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 2159 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2160 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2161 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2162 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2163 "bootstrap/stage0/ReCode.code"
    return Parsed_Block_Statement__create(location, statements);}

#line 2168 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self) { struct Token* name; struct Parsed_Type* type;
#line 2169 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2170 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2171 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_colon);
#line 2172 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2173 "bootstrap/stage0/ReCode.code"
    type = Parser__parse_type(self);
#line 2174 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Parameter__create(name->location, name->lexeme, type);}

#line 2179 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_function(struct Parser* self) { struct Token* name; struct Parsed_Function_Parameter* first_parameter; struct Parsed_Type* return_type; struct Parsed_Statements* statements;
#line 2180 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2181 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2182 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2183 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2184 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2185 "bootstrap/stage0/ReCode.code"
    first_parameter = NULL;
#line 2186 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren))) {
#line 2186 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Function_Parameter* last_parameter;
#line 2187 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2188 "bootstrap/stage0/ReCode.code"
                first_parameter = Parser__parse_function_parameter(self);
#line 2189 "bootstrap/stage0/ReCode.code"
                last_parameter = first_parameter;
#line 2190 "bootstrap/stage0/ReCode.code"
                while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2191 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 2192 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_comma);
#line 2193 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 2194 "bootstrap/stage0/ReCode.code"
                    last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2195 "bootstrap/stage0/ReCode.code"
                    last_parameter = last_parameter->next_parameter;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 2198 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2199 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2200 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2201 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2202 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2203 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2204 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2205 "bootstrap/stage0/ReCode.code"
    return_type = Parser__parse_type(self);
#line 2206 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2207 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2208 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2209 "bootstrap/stage0/ReCode.code"
    statements = Parsed_Statements__create(false);
#line 2210 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + ((uint16_t) 1);
#line 2211 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2212 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - ((uint16_t) 1);
#line 2213 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2214 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2215 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, statements, false);}

#line 2220 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_external_function(struct Parser* self) { struct Token* name; struct Parsed_Function_Parameter* first_parameter; struct Parsed_Type* return_type;
#line 2221 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2222 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2223 "bootstrap/stage0/ReCode.code"
    name = Parser__consume_token(self, Token__is_identifier);
#line 2224 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2225 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2226 "bootstrap/stage0/ReCode.code"
    first_parameter = NULL;
#line 2227 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren))) {
#line 2227 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Function_Parameter* last_parameter;
#line 2228 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 0));
#line 2229 "bootstrap/stage0/ReCode.code"
                first_parameter = Parser__parse_function_parameter(self);
#line 2230 "bootstrap/stage0/ReCode.code"
                last_parameter = first_parameter;
#line 2231 "bootstrap/stage0/ReCode.code"
                while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2232 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 0));
#line 2233 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_comma);
#line 2234 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, ((uint16_t) 1));
#line 2235 "bootstrap/stage0/ReCode.code"
                    last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2236 "bootstrap/stage0/ReCode.code"
                    last_parameter = last_parameter->next_parameter;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 2239 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2240 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2241 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2242 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2243 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2244 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2245 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2246 "bootstrap/stage0/ReCode.code"
    return_type = Parser__parse_type(self);
#line 2247 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, NULL, true);}

#line 2252 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_return_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Expression* expression;
#line 2253 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_return)->location;
#line 2254 "bootstrap/stage0/ReCode.code"
    expression = NULL;
#line 2255 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line))) {
#line 2255 "bootstrap/stage0/ReCode.code"
            {
#line 2256 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2257 "bootstrap/stage0/ReCode.code"
                expression = Parser__parse_expression(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 2259 "bootstrap/stage0/ReCode.code"
    return Parsed_Return_Statement__create(location, expression);}

#line 2264 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_break_statement(struct Parser* self) { struct Source_Location* location;
#line 2265 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_break)->location;
#line 2266 "bootstrap/stage0/ReCode.code"
    return Parsed_Break_Statement__create(location);}

#line 2271 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_if_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Expression* condition_expression; struct Parsed_Statement* true_statement; struct Parsed_Statement* false_statement;
#line 2272 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_if)->location;
#line 2273 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2274 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2275 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2276 "bootstrap/stage0/ReCode.code"
    condition_expression = Parser__parse_expression(self);
#line 2277 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2278 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2279 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2280 "bootstrap/stage0/ReCode.code"
    true_statement = ((struct Parsed_Statement*) Parser__parse_block_statement(self));
#line 2281 "bootstrap/stage0/ReCode.code"
    false_statement = NULL;
#line 2282 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
#line 2282 "bootstrap/stage0/ReCode.code"
            {
#line 2283 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2284 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_else);
#line 2285 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2286 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (Parser__matches_one(self, Token__is_if)) {
#line 2286 "bootstrap/stage0/ReCode.code"
                        {
#line 2287 "bootstrap/stage0/ReCode.code"
                            false_statement = Parser__parse_if_statement(self);
                        } goto if__end__2; } if__else__2: ;
#line 2288 "bootstrap/stage0/ReCode.code"
                    {
#line 2289 "bootstrap/stage0/ReCode.code"
                        false_statement = ((struct Parsed_Statement*) Parser__parse_block_statement(self));
                    } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 2292 "bootstrap/stage0/ReCode.code"
    return Parsed_If_Statement__create(location, condition_expression, true_statement, false_statement);}

#line 2297 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_while_statement(struct Parser* self) { struct Source_Location* location; struct Parsed_Expression* condition_expression; struct Parsed_Statement* body_statement;
#line 2298 "bootstrap/stage0/ReCode.code"
    location = Parser__consume_token(self, Token__is_while)->location;
#line 2299 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2300 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2301 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2302 "bootstrap/stage0/ReCode.code"
    condition_expression = Parser__parse_expression(self);
#line 2303 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 0));
#line 2304 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2305 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, ((uint16_t) 1));
#line 2306 "bootstrap/stage0/ReCode.code"
    body_statement = ((struct Parsed_Statement*) Parser__parse_block_statement(self));
#line 2307 "bootstrap/stage0/ReCode.code"
    return Parsed_While_Statement__create(location, condition_expression, body_statement);}

#line 2318 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_statement(struct Parser* self) { struct Parsed_Expression* expression;
#line 2319 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * ((uint16_t) 4));
#line 2321 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (Parser__matches_one(self, Token__is_if)) {
#line 2321 "bootstrap/stage0/ReCode.code"
            {
#line 2322 "bootstrap/stage0/ReCode.code"
                return Parser__parse_if_statement(self);
            } goto if__end__1; } if__end__1: ;
    }
#line 2325 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (Parser__matches_one(self, Token__is_while)) {
#line 2325 "bootstrap/stage0/ReCode.code"
            {
#line 2326 "bootstrap/stage0/ReCode.code"
                return Parser__parse_while_statement(self);
            } goto if__end__2; } if__end__2: ;
    }
#line 2329 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (Parser__matches_one(self, Token__is_return)) {
#line 2329 "bootstrap/stage0/ReCode.code"
            {
#line 2330 "bootstrap/stage0/ReCode.code"
                return Parser__parse_return_statement(self);
            } goto if__end__3; } if__end__3: ;
    }
#line 2333 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (Parser__matches_one(self, Token__is_break)) {
#line 2333 "bootstrap/stage0/ReCode.code"
            {
#line 2334 "bootstrap/stage0/ReCode.code"
                return Parser__parse_break_statement(self);
            } goto if__end__4; } if__end__4: ;
    }
#line 2337 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (Parser__matches_one(self, Token__is_let)) {
#line 2337 "bootstrap/stage0/ReCode.code"
            {
#line 2338 "bootstrap/stage0/ReCode.code"
                return Parser__parse_variable(self);
            } goto if__end__5; } if__end__5: ;
    }
#line 2341 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (Parser__matches_one(self, Token__is_func)) {
#line 2341 "bootstrap/stage0/ReCode.code"
            {
#line 2342 "bootstrap/stage0/ReCode.code"
                return Parser__parse_function(self);
            } goto if__end__6; } if__end__6: ;
    }
#line 2345 "bootstrap/stage0/ReCode.code"
    if__start__7: { if (Parser__matches_one(self, Token__is_struct)) {
#line 2345 "bootstrap/stage0/ReCode.code"
            {
#line 2346 "bootstrap/stage0/ReCode.code"
                return Parser__parse_struct(self);
            } goto if__end__7; } if__end__7: ;
    }
#line 2349 "bootstrap/stage0/ReCode.code"
    if__start__8: { if (Parser__matches_one(self, Token__is_enum)) {
#line 2349 "bootstrap/stage0/ReCode.code"
            {
#line 2350 "bootstrap/stage0/ReCode.code"
                return Parser__parse_enum(self);
            } goto if__end__8; } if__end__8: ;
    }
#line 2353 "bootstrap/stage0/ReCode.code"
    if__start__9: { if (Parser__matches_one(self, Token__is_external)) {
#line 2353 "bootstrap/stage0/ReCode.code"
            { struct Source_Location* location;
#line 2354 "bootstrap/stage0/ReCode.code"
                location = Parser__consume_token(self, Token__is_external)->location;
#line 2355 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2356 "bootstrap/stage0/ReCode.code"
                if__start__10: { if (Parser__matches_one(self, Token__is_func)) {
#line 2356 "bootstrap/stage0/ReCode.code"
                        {
#line 2357 "bootstrap/stage0/ReCode.code"
                            return Parser__parse_external_function(self);
                        } goto if__end__10; } if__end__10: ;
                }
#line 2359 "bootstrap/stage0/ReCode.code"
                if__start__11: { if (Parser__matches_one(self, Token__is_type)) {
#line 2359 "bootstrap/stage0/ReCode.code"
                        {
#line 2360 "bootstrap/stage0/ReCode.code"
                            return Parser__parse_external_type(self);
                        } goto if__end__11; } if__end__11: ;
                }
#line 2362 "bootstrap/stage0/ReCode.code"
                return Parser__parse_external_variable(self);
            } goto if__end__9; } if__end__9: ;
    }
#line 2365 "bootstrap/stage0/ReCode.code"
    expression = Parser__parse_access_expression(self);
#line 2366 "bootstrap/stage0/ReCode.code"
    if__start__12: { if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2366 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Expression* value_expression;
#line 2367 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2368 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_equals);
#line 2369 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, ((uint16_t) 1));
#line 2370 "bootstrap/stage0/ReCode.code"
                value_expression = Parser__parse_expression(self);
#line 2371 "bootstrap/stage0/ReCode.code"
                return ((struct Parsed_Statement*) Parsed_Assignment_Statement__create(expression, value_expression));
            } goto if__end__12; } if__end__12: ;
    }
#line 2373 "bootstrap/stage0/ReCode.code"
    return ((struct Parsed_Statement*) Parsed_Expression_Statement__create(expression));}

#line 2378 "bootstrap/stage0/ReCode.code"
void Parser__parse_statements(struct Parser* self, struct Parsed_Statements* statements) {
#line 2379 "bootstrap/stage0/ReCode.code"
    while (true) { struct Parsed_Statement* statement;
#line 2380 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
#line 2384 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (statements->has_globals) {
#line 2384 "bootstrap/stage0/ReCode.code"
                {
#line 2385 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 2385 "bootstrap/stage0/ReCode.code"
                            {
#line 2386 "bootstrap/stage0/ReCode.code"
                                return;
                            } goto if__end__2; } if__end__2: ;
                    }
                } goto if__end__1; } if__else__1: ;
#line 2388 "bootstrap/stage0/ReCode.code"
            {
#line 2389 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2389 "bootstrap/stage0/ReCode.code"
                        {
#line 2390 "bootstrap/stage0/ReCode.code"
                            return;
                        } goto if__end__3; } if__end__3: ;
                }
            } if__end__1: ;
        }
#line 2394 "bootstrap/stage0/ReCode.code"
        statement = Parser__parse_statement(self);
#line 2396 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2398 "bootstrap/stage0/ReCode.code"
        Parsed_Statements__append(statements, statement);
    }}

#line 2402 "bootstrap/stage0/ReCode.code"
void Parser__parse_source(struct Parser* self, struct Source* source) { struct Scanner* other_scanner; struct Token* last_token;
#line 2403 "bootstrap/stage0/ReCode.code"
    other_scanner = self->scanner;
#line 2405 "bootstrap/stage0/ReCode.code"
    self->scanner = Scanner__create(source);
#line 2407 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, self->compilation_unit->statements);
#line 2409 "bootstrap/stage0/ReCode.code"
    last_token = Parser__peek_token(self, ((uint8_t) 0));
#line 2410 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Token__is_end_of_file(last_token))) {
#line 2410 "bootstrap/stage0/ReCode.code"
            {
#line 2411 "bootstrap/stage0/ReCode.code"
                Parser__error(self, String__create_from("Scanner didn\'t reach end of file"));
#line 2412 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__else__1: ;
#line 2413 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (last_token->location->column != ((uint16_t) 1)) {
#line 2413 "bootstrap/stage0/ReCode.code"
                {
#line 2414 "bootstrap/stage0/ReCode.code"
                    Parser__warning(self, String__create_from("No new line at the end of file"));
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 2417 "bootstrap/stage0/ReCode.code"
    self->scanner = other_scanner;}

#line 2420 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* parse(struct Source* source) { struct Parser parser;
#line 2421 "bootstrap/stage0/ReCode.code"
    ;
#line 2422 "bootstrap/stage0/ReCode.code"
    parser.scanner = NULL;
#line 2423 "bootstrap/stage0/ReCode.code"
    parser.compilation_unit = Parsed_Compilation_Unit__create();
#line 2424 "bootstrap/stage0/ReCode.code"
    parser.current_identation = ((uint16_t) 0);
#line 2426 "bootstrap/stage0/ReCode.code"
    Parser__parse_source(&parser, source);
#line 2428 "bootstrap/stage0/ReCode.code"
    return parser.compilation_unit;}

#line 2466 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checked_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location) { struct Checked_Type* type;
#line 2467 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Type*) malloc(kind_size));
#line 2468 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 2469 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 2470 "bootstrap/stage0/ReCode.code"
    type->next_type = NULL;
#line 2471 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2474 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_same_type(struct Checked_Type* self, struct Checked_Type* other_type, struct Source_Location* location) {
#line 2475 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->kind == Checked_Type_Kind__POINTER) { if (other_type->kind == Checked_Type_Kind__NULL) {
#line 2475 "bootstrap/stage0/ReCode.code"
                {
#line 2476 "bootstrap/stage0/ReCode.code"
                    return;
                } goto if__end__1; } } if__end__1: ;
    }
#line 2478 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->kind == Checked_Type_Kind__FUNCTION) { if (other_type->kind == Checked_Type_Kind__NULL) {
#line 2478 "bootstrap/stage0/ReCode.code"
                {
#line 2479 "bootstrap/stage0/ReCode.code"
                    return;
                } goto if__end__2; } } if__end__2: ;
    }
#line 2481 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (!(Checked_Type__equals(self, other_type))) {
#line 2481 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 2482 "bootstrap/stage0/ReCode.code"
                message = String__create_from("Unexpected type. Got \"");
#line 2483 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, other_type);
#line 2484 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" instead of \"");
#line 2485 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, self);
#line 2486 "bootstrap/stage0/ReCode.code"
                String__append_char(message, '\"');
#line 2487 "bootstrap/stage0/ReCode.code"
                Source_Location__error(location, message);
#line 2488 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__3; } if__end__3: ;
    }}

#line 2492 "bootstrap/stage0/ReCode.code"
bool Checked_Type__is_scalar_type(struct Checked_Type* self) {
#line 2493 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->kind == Checked_Type_Kind__CHAR) {
#line 2493 "bootstrap/stage0/ReCode.code"
            {
#line 2494 "bootstrap/stage0/ReCode.code"
                return true;
            } goto if__end__1; } if__else__1: ;
#line 2495 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (self->kind == Checked_Type_Kind__I16) {
#line 2495 "bootstrap/stage0/ReCode.code"
                {
#line 2496 "bootstrap/stage0/ReCode.code"
                    return true;
                } goto if__end__2; } if__else__2: ;
#line 2497 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (self->kind == Checked_Type_Kind__I32) {
#line 2497 "bootstrap/stage0/ReCode.code"
                    {
#line 2498 "bootstrap/stage0/ReCode.code"
                        return true;
                    } goto if__end__3; } if__else__3: ;
#line 2499 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (self->kind == Checked_Type_Kind__I64) {
#line 2499 "bootstrap/stage0/ReCode.code"
                        {
#line 2500 "bootstrap/stage0/ReCode.code"
                            return true;
                        } goto if__end__4; } if__else__4: ;
#line 2501 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (self->kind == Checked_Type_Kind__I8) {
#line 2501 "bootstrap/stage0/ReCode.code"
                            {
#line 2502 "bootstrap/stage0/ReCode.code"
                                return true;
                            } goto if__end__5; } if__else__5: ;
#line 2503 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (self->kind == Checked_Type_Kind__U16) {
#line 2503 "bootstrap/stage0/ReCode.code"
                                {
#line 2504 "bootstrap/stage0/ReCode.code"
                                    return true;
                                } goto if__end__6; } if__else__6: ;
#line 2505 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (self->kind == Checked_Type_Kind__U32) {
#line 2505 "bootstrap/stage0/ReCode.code"
                                    {
#line 2506 "bootstrap/stage0/ReCode.code"
                                        return true;
                                    } goto if__end__7; } if__else__7: ;
#line 2507 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (self->kind == Checked_Type_Kind__U64) {
#line 2507 "bootstrap/stage0/ReCode.code"
                                        {
#line 2508 "bootstrap/stage0/ReCode.code"
                                            return true;
                                        } goto if__end__8; } if__else__8: ;
#line 2509 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (self->kind == Checked_Type_Kind__U8) {
#line 2509 "bootstrap/stage0/ReCode.code"
                                            {
#line 2510 "bootstrap/stage0/ReCode.code"
                                                return true;
                                            } goto if__end__9; } if__else__9: ;
#line 2511 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (self->kind == Checked_Type_Kind__USIZE) {
#line 2511 "bootstrap/stage0/ReCode.code"
                                                {
#line 2512 "bootstrap/stage0/ReCode.code"
                                                    return true;
                                                } goto if__end__10; } if__else__10: ;
#line 2513 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (self->kind == Checked_Type_Kind__ENUM) {
#line 2513 "bootstrap/stage0/ReCode.code"
                                                    {
#line 2514 "bootstrap/stage0/ReCode.code"
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
#line 2516 "bootstrap/stage0/ReCode.code"
    return false;}

#line 2519 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_scalar_type(struct Checked_Type* self, struct Source_Location* location) {
#line 2520 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Checked_Type__is_scalar_type(self))) {
#line 2520 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 2521 "bootstrap/stage0/ReCode.code"
                message = String__create_from("Type \"");
#line 2522 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, self);
#line 2523 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" is not a scalar type");
#line 2524 "bootstrap/stage0/ReCode.code"
                Source_Location__error(location, message);
#line 2525 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }}

#line 2534 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checked_Named_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name) { struct Checked_Named_Type* type;
#line 2535 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Named_Type*) Checked_Type__create_kind(kind, kind_size, location));
#line 2536 "bootstrap/stage0/ReCode.code"
    type->name = name;
#line 2537 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2547 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Member__create(struct Source_Location* location, struct String* name) { struct Checked_Enum_Member* member;
#line 2548 "bootstrap/stage0/ReCode.code"
    member = ((struct Checked_Enum_Member*) malloc(sizeof(struct Checked_Enum_Member)));
#line 2549 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2550 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2551 "bootstrap/stage0/ReCode.code"
    member->symbol = NULL;
#line 2552 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2553 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2561 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Type* Checked_Enum_Type__create(struct Source_Location* location, struct String* name) { struct Checked_Enum_Type* type;
#line 2562 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Enum_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__ENUM, sizeof(struct Checked_Enum_Type), location, name));
#line 2563 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2564 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2567 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Type__find_member(struct Checked_Enum_Type* self, struct String* name) { struct Checked_Enum_Member* member;
#line 2568 "bootstrap/stage0/ReCode.code"
    member = self->first_member;
#line 2569 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2570 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, member->name)) {
#line 2570 "bootstrap/stage0/ReCode.code"
                {
#line 2571 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 2573 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2575 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2585 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter* Checked_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) { struct Checked_Function_Parameter* parameter;
#line 2586 "bootstrap/stage0/ReCode.code"
    parameter = ((struct Checked_Function_Parameter*) malloc(sizeof(struct Checked_Function_Parameter)));
#line 2587 "bootstrap/stage0/ReCode.code"
    parameter->location = location;
#line 2588 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 2589 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 2590 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 2591 "bootstrap/stage0/ReCode.code"
    return parameter;}

#line 2600 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct Checked_Function_Parameter* first_parameter, struct Checked_Type* return_type) { struct Checked_Function_Type* type;
#line 2601 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Function_Type*) Checked_Type__create_kind(Checked_Type_Kind__FUNCTION, sizeof(struct Checked_Function_Type), location));
#line 2602 "bootstrap/stage0/ReCode.code"
    type->first_parameter = first_parameter;
#line 2603 "bootstrap/stage0/ReCode.code"
    type->return_type = return_type;
#line 2604 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2607 "bootstrap/stage0/ReCode.code"
bool Checked_Function_Type__equals(struct Checked_Function_Type* self, struct Checked_Type* other_type) { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* self_parameter; struct Checked_Function_Parameter* function_parameter;
#line 2608 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type->kind != self->super.kind) {
#line 2608 "bootstrap/stage0/ReCode.code"
            {
#line 2609 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 2611 "bootstrap/stage0/ReCode.code"
    function_type = ((struct Checked_Function_Type*) other_type);
#line 2612 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (!(Checked_Type__equals(self->return_type, function_type->return_type))) {
#line 2612 "bootstrap/stage0/ReCode.code"
            {
#line 2613 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__2; } if__end__2: ;
    }
#line 2615 "bootstrap/stage0/ReCode.code"
    self_parameter = self->first_parameter;
#line 2616 "bootstrap/stage0/ReCode.code"
    function_parameter = function_type->first_parameter;
#line 2617 "bootstrap/stage0/ReCode.code"
    while (self_parameter != NULL && function_parameter != NULL) {
#line 2618 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (!(Checked_Type__equals(self_parameter->type, function_parameter->type))) {
#line 2618 "bootstrap/stage0/ReCode.code"
                {
#line 2619 "bootstrap/stage0/ReCode.code"
                    return false;
                } goto if__end__3; } if__end__3: ;
        }
#line 2621 "bootstrap/stage0/ReCode.code"
        self_parameter = self_parameter->next_parameter;
#line 2622 "bootstrap/stage0/ReCode.code"
        function_parameter = function_parameter->next_parameter;
    }
#line 2624 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (!(self_parameter != NULL)) { if (!(function_parameter != NULL)) { goto if__end__4; } } if__then__4__5: {
#line 2624 "bootstrap/stage0/ReCode.code"
            {
#line 2625 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__4; } if__end__4: ;
    }
#line 2627 "bootstrap/stage0/ReCode.code"
    return true;}

#line 2634 "bootstrap/stage0/ReCode.code"
struct Checked_Opaque_Type* Checked_Opaque_Type__create(struct Source_Location* location, struct String* name) {
#line 2635 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Opaque_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__OPAQUE, sizeof(struct Checked_Opaque_Type), location, name));}

#line 2643 "bootstrap/stage0/ReCode.code"
struct Checked_Pointer_Type* Checked_Pointer_Type__create(struct Source_Location* location, struct Checked_Type* other_type) { struct Checked_Pointer_Type* type;
#line 2644 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Pointer_Type*) Checked_Type__create_kind(Checked_Type_Kind__POINTER, sizeof(struct Checked_Pointer_Type), location));
#line 2645 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 2646 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2649 "bootstrap/stage0/ReCode.code"
bool Checked_Pointer_Type__equals(struct Checked_Pointer_Type* self, struct Checked_Type* other_type) {
#line 2650 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type->kind != self->super.kind) {
#line 2650 "bootstrap/stage0/ReCode.code"
            {
#line 2651 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 2653 "bootstrap/stage0/ReCode.code"
    return Checked_Type__equals(self->other_type, ((struct Checked_Pointer_Type*) other_type)->other_type);}

#line 2661 "bootstrap/stage0/ReCode.code"
struct Checked_Defined_Type* Checked_Defined_Type__create(struct Checked_Named_Type* defined_type) { struct Checked_Defined_Type* type;
#line 2662 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Defined_Type*) Checked_Type__create_kind(Checked_Type_Kind__DEFINED, sizeof(struct Checked_Defined_Type), defined_type->super.location));
#line 2663 "bootstrap/stage0/ReCode.code"
    type->defined_type = defined_type;
#line 2664 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2674 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Member__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) { struct Checked_Struct_Member* member;
#line 2675 "bootstrap/stage0/ReCode.code"
    member = ((struct Checked_Struct_Member*) malloc(sizeof(struct Checked_Struct_Member)));
#line 2676 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2677 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2678 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 2679 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2680 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2689 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Type* Checked_Struct_Type__create(struct Source_Location* location, struct String* name) { struct Checked_Struct_Type* type;
#line 2690 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Struct_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__STRUCT, sizeof(struct Checked_Struct_Type), location, name));
#line 2691 "bootstrap/stage0/ReCode.code"
    type->super_type = NULL;
#line 2692 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2693 "bootstrap/stage0/ReCode.code"
    return type;}

#line 2696 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Type__find_member(struct Checked_Struct_Type* self, struct String* name) { struct Checked_Struct_Member* member;
#line 2697 "bootstrap/stage0/ReCode.code"
    member = self->first_member;
#line 2698 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2699 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, member->name)) {
#line 2699 "bootstrap/stage0/ReCode.code"
                {
#line 2700 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 2702 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2704 "bootstrap/stage0/ReCode.code"
    return member;}

#line 2707 "bootstrap/stage0/ReCode.code"
bool Checked_Struct_Type__equals(struct Checked_Struct_Type* self, struct Checked_Type* other_type) {
#line 2708 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->super.super.kind != other_type->kind) {
#line 2708 "bootstrap/stage0/ReCode.code"
            {
#line 2709 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__1; } if__end__1: ;
    }
#line 2711 "bootstrap/stage0/ReCode.code"
    return String__equals_string(self->super.name, ((struct Checked_Struct_Type*) other_type)->super.name);}

#line 2714 "bootstrap/stage0/ReCode.code"
bool Checked_Type__equals(struct Checked_Type* self, struct Checked_Type* other_type) {
#line 2715 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self == other_type) {
#line 2715 "bootstrap/stage0/ReCode.code"
            {
#line 2716 "bootstrap/stage0/ReCode.code"
                return true;
            } goto if__end__1; } if__end__1: ;
    }
#line 2718 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->kind != other_type->kind) {
#line 2718 "bootstrap/stage0/ReCode.code"
            {
#line 2719 "bootstrap/stage0/ReCode.code"
                return false;
            } goto if__end__2; } if__end__2: ;
    }
#line 2721 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (self->kind == Checked_Type_Kind__FUNCTION) {
#line 2721 "bootstrap/stage0/ReCode.code"
            {
#line 2722 "bootstrap/stage0/ReCode.code"
                return Checked_Function_Type__equals(((struct Checked_Function_Type*) self), other_type);
            } goto if__end__3; } if__end__3: ;
    }
#line 2724 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (self->kind == Checked_Type_Kind__POINTER) {
#line 2724 "bootstrap/stage0/ReCode.code"
            {
#line 2725 "bootstrap/stage0/ReCode.code"
                return Checked_Pointer_Type__equals(((struct Checked_Pointer_Type*) self), other_type);
            } goto if__end__4; } if__end__4: ;
    }
#line 2727 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (self->kind == Checked_Type_Kind__STRUCT) {
#line 2727 "bootstrap/stage0/ReCode.code"
            {
#line 2728 "bootstrap/stage0/ReCode.code"
                return Checked_Struct_Type__equals(((struct Checked_Struct_Type*) self), other_type);
            } goto if__end__5; } if__end__5: ;
    }
#line 2730 "bootstrap/stage0/ReCode.code"
    Source_Location__error(self->location, String__create_from("Unsupported type"));
#line 2731 "bootstrap/stage0/ReCode.code"
    abort();}

#line 2734 "bootstrap/stage0/ReCode.code"
struct String* String__append_checked_type(struct String* self, struct Checked_Type* type) {
#line 2735 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (type->kind <= Checked_Type_Kind__NULL) {
#line 2735 "bootstrap/stage0/ReCode.code"
            { struct Checked_Named_Type* named_type;
#line 2736 "bootstrap/stage0/ReCode.code"
                named_type = ((struct Checked_Named_Type*) type);
#line 2737 "bootstrap/stage0/ReCode.code"
                String__append_string(self, named_type->name);
            } goto if__end__1; } if__else__1: ;
#line 2738 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2738 "bootstrap/stage0/ReCode.code"
                { struct Checked_Struct_Type* struct_type;
#line 2739 "bootstrap/stage0/ReCode.code"
                    struct_type = ((struct Checked_Struct_Type*) type);
#line 2740 "bootstrap/stage0/ReCode.code"
                    String__append_cstring(self, "struct ");
#line 2741 "bootstrap/stage0/ReCode.code"
                    String__append_string(self, struct_type->super.name);
                } goto if__end__2; } if__else__2: ;
#line 2742 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (type->kind == Checked_Type_Kind__FUNCTION) {
#line 2742 "bootstrap/stage0/ReCode.code"
                    { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* function_parameter;
#line 2743 "bootstrap/stage0/ReCode.code"
                        function_type = ((struct Checked_Function_Type*) type);
#line 2744 "bootstrap/stage0/ReCode.code"
                        String__append_cstring(self, "(func (");
#line 2745 "bootstrap/stage0/ReCode.code"
                        function_parameter = function_type->first_parameter;
#line 2746 "bootstrap/stage0/ReCode.code"
                        while (function_parameter != NULL) {
#line 2747 "bootstrap/stage0/ReCode.code"
                            String__append_checked_type(self, function_parameter->type);
#line 2748 "bootstrap/stage0/ReCode.code"
                            function_parameter = function_parameter->next_parameter;
#line 2749 "bootstrap/stage0/ReCode.code"
                            if__start__4: { if (function_parameter != NULL) {
#line 2749 "bootstrap/stage0/ReCode.code"
                                    {
#line 2750 "bootstrap/stage0/ReCode.code"
                                        String__append_cstring(self, ", ");
                                    } goto if__end__4; } if__end__4: ;
                            }
                        }
#line 2753 "bootstrap/stage0/ReCode.code"
                        String__append_cstring(self, ") -> ");
#line 2754 "bootstrap/stage0/ReCode.code"
                        String__append_checked_type(self, function_type->return_type);
#line 2755 "bootstrap/stage0/ReCode.code"
                        String__append_char(self, ')');
                    } goto if__end__3; } if__else__3: ;
#line 2756 "bootstrap/stage0/ReCode.code"
                if__start__5: { if (type->kind == Checked_Type_Kind__ENUM) {
#line 2756 "bootstrap/stage0/ReCode.code"
                        { struct Checked_Enum_Type* enum_type;
#line 2757 "bootstrap/stage0/ReCode.code"
                            enum_type = ((struct Checked_Enum_Type*) type);
#line 2758 "bootstrap/stage0/ReCode.code"
                            String__append_cstring(self, "enum ");
#line 2759 "bootstrap/stage0/ReCode.code"
                            String__append_string(self, enum_type->super.name);
                        } goto if__end__5; } if__else__5: ;
#line 2760 "bootstrap/stage0/ReCode.code"
                    if__start__6: { if (type->kind == Checked_Type_Kind__POINTER) {
#line 2760 "bootstrap/stage0/ReCode.code"
                            { struct Checked_Pointer_Type* pointer_type;
#line 2761 "bootstrap/stage0/ReCode.code"
                                pointer_type = ((struct Checked_Pointer_Type*) type);
#line 2762 "bootstrap/stage0/ReCode.code"
                                String__append_checked_type(self, pointer_type->other_type);
#line 2763 "bootstrap/stage0/ReCode.code"
                                String__append_char(self, '*');
                            } goto if__end__6; } if__else__6: ;
#line 2764 "bootstrap/stage0/ReCode.code"
                        {
#line 2765 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2766 "bootstrap/stage0/ReCode.code"
                            abort();
                        } if__end__6: ;
                    } if__end__5: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }
#line 2768 "bootstrap/stage0/ReCode.code"
    return self;}

#line 2771 "bootstrap/stage0/ReCode.code"
void File__write_checked_function_symbol(struct File* self, struct Checked_Function_Symbol* function_symbol) { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* function_parameter;
#line 2772 "bootstrap/stage0/ReCode.code"
    function_type = function_symbol->function_type;
#line 2773 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self, function_type->return_type);
#line 2774 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ' ');
#line 2775 "bootstrap/stage0/ReCode.code"
    File__write_string(self, function_symbol->super.name);
#line 2776 "bootstrap/stage0/ReCode.code"
    File__write_char(self, '(');
#line 2777 "bootstrap/stage0/ReCode.code"
    function_parameter = function_type->first_parameter;
#line 2778 "bootstrap/stage0/ReCode.code"
    while (function_parameter != NULL) {
#line 2779 "bootstrap/stage0/ReCode.code"
        File__write_checked_function_parameter(self, function_parameter);
#line 2780 "bootstrap/stage0/ReCode.code"
        function_parameter = function_parameter->next_parameter;
#line 2781 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (function_parameter != NULL) {
#line 2781 "bootstrap/stage0/ReCode.code"
                {
#line 2782 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self, ", ");
                } goto if__end__1; } if__end__1: ;
        }
    }
#line 2785 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ')');}

#line 2788 "bootstrap/stage0/ReCode.code"
void File__write_checked_function_parameter(struct File* self, struct Checked_Function_Parameter* parameter) {
#line 2789 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parameter->type->kind == Checked_Type_Kind__FUNCTION) {
#line 2789 "bootstrap/stage0/ReCode.code"
            { struct Checked_Function_Type* function_type; struct Checked_Function_Parameter* function_parameter;
#line 2790 "bootstrap/stage0/ReCode.code"
                function_type = ((struct Checked_Function_Type*) parameter->type);
#line 2791 "bootstrap/stage0/ReCode.code"
                File__write_checked_type(self, function_type->return_type);
#line 2792 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, " (*");
#line 2793 "bootstrap/stage0/ReCode.code"
                File__write_string(self, parameter->name);
#line 2794 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, ")(");
#line 2795 "bootstrap/stage0/ReCode.code"
                function_parameter = function_type->first_parameter;
#line 2796 "bootstrap/stage0/ReCode.code"
                while (function_parameter != NULL) {
#line 2797 "bootstrap/stage0/ReCode.code"
                    File__write_checked_function_parameter(self, function_parameter);
#line 2798 "bootstrap/stage0/ReCode.code"
                    function_parameter = function_parameter->next_parameter;
#line 2799 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (function_parameter != NULL) {
#line 2799 "bootstrap/stage0/ReCode.code"
                            {
#line 2800 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(self, ", ");
                            } goto if__end__2; } if__end__2: ;
                    }
                }
#line 2803 "bootstrap/stage0/ReCode.code"
                File__write_char(self, ')');
            } goto if__end__1; } if__else__1: ;
#line 2804 "bootstrap/stage0/ReCode.code"
        {
#line 2805 "bootstrap/stage0/ReCode.code"
            File__write_checked_type(self, parameter->type);
#line 2806 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parameter->name != NULL) {
#line 2806 "bootstrap/stage0/ReCode.code"
                    {
#line 2807 "bootstrap/stage0/ReCode.code"
                        File__write_char(self, ' ');
#line 2808 "bootstrap/stage0/ReCode.code"
                        File__write_string(self, parameter->name);
                    } goto if__end__3; } if__end__3: ;
            }
        } if__end__1: ;
    }}

#line 2813 "bootstrap/stage0/ReCode.code"
void File__write_checked_type(struct File* self, struct Checked_Type* type) {
#line 2814 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (type == NULL) {
#line 2814 "bootstrap/stage0/ReCode.code"
            {
#line 2815 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, "null");
            } goto if__end__1; } if__else__1: ;
#line 2816 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (type->kind == Checked_Type_Kind__I16) {
#line 2816 "bootstrap/stage0/ReCode.code"
                {
#line 2817 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self, "int16_t");
                } goto if__end__2; } if__else__2: ;
#line 2818 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (type->kind == Checked_Type_Kind__I32) {
#line 2818 "bootstrap/stage0/ReCode.code"
                    {
#line 2819 "bootstrap/stage0/ReCode.code"
                        File__write_cstring(self, "int32_t");
                    } goto if__end__3; } if__else__3: ;
#line 2820 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (type->kind == Checked_Type_Kind__I64) {
#line 2820 "bootstrap/stage0/ReCode.code"
                        {
#line 2821 "bootstrap/stage0/ReCode.code"
                            File__write_cstring(self, "int64_t");
                        } goto if__end__4; } if__else__4: ;
#line 2822 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (type->kind == Checked_Type_Kind__I8) {
#line 2822 "bootstrap/stage0/ReCode.code"
                            {
#line 2823 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(self, "int8_t");
                            } goto if__end__5; } if__else__5: ;
#line 2824 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (type->kind == Checked_Type_Kind__U16) {
#line 2824 "bootstrap/stage0/ReCode.code"
                                {
#line 2825 "bootstrap/stage0/ReCode.code"
                                    File__write_cstring(self, "uint16_t");
                                } goto if__end__6; } if__else__6: ;
#line 2826 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (type->kind == Checked_Type_Kind__U32) {
#line 2826 "bootstrap/stage0/ReCode.code"
                                    {
#line 2827 "bootstrap/stage0/ReCode.code"
                                        File__write_cstring(self, "uint32_t");
                                    } goto if__end__7; } if__else__7: ;
#line 2828 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (type->kind == Checked_Type_Kind__U64) {
#line 2828 "bootstrap/stage0/ReCode.code"
                                        {
#line 2829 "bootstrap/stage0/ReCode.code"
                                            File__write_cstring(self, "uint64_t");
                                        } goto if__end__8; } if__else__8: ;
#line 2830 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (type->kind == Checked_Type_Kind__U8) {
#line 2830 "bootstrap/stage0/ReCode.code"
                                            {
#line 2831 "bootstrap/stage0/ReCode.code"
                                                File__write_cstring(self, "uint8_t");
                                            } goto if__end__9; } if__else__9: ;
#line 2832 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (type->kind == Checked_Type_Kind__USIZE) {
#line 2832 "bootstrap/stage0/ReCode.code"
                                                {
#line 2833 "bootstrap/stage0/ReCode.code"
                                                    File__write_cstring(self, "size_t");
                                                } goto if__end__10; } if__else__10: ;
#line 2834 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (type->kind <= Checked_Type_Kind__NULL) {
#line 2834 "bootstrap/stage0/ReCode.code"
                                                    { struct Checked_Named_Type* named_type;
#line 2835 "bootstrap/stage0/ReCode.code"
                                                        named_type = ((struct Checked_Named_Type*) type);
#line 2836 "bootstrap/stage0/ReCode.code"
                                                        File__write_string(self, named_type->name);
                                                    } goto if__end__11; } if__else__11: ;
#line 2837 "bootstrap/stage0/ReCode.code"
                                                if__start__12: { if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2837 "bootstrap/stage0/ReCode.code"
                                                        { struct Checked_Struct_Type* struct_type;
#line 2838 "bootstrap/stage0/ReCode.code"
                                                            struct_type = ((struct Checked_Struct_Type*) type);
#line 2839 "bootstrap/stage0/ReCode.code"
                                                            File__write_cstring(self, "struct ");
#line 2840 "bootstrap/stage0/ReCode.code"
                                                            File__write_string(self, struct_type->super.name);
                                                        } goto if__end__12; } if__else__12: ;
#line 2841 "bootstrap/stage0/ReCode.code"
                                                    if__start__13: { if (type->kind == Checked_Type_Kind__OPAQUE) {
#line 2841 "bootstrap/stage0/ReCode.code"
                                                            { struct Checked_Opaque_Type* opaque_type;
#line 2842 "bootstrap/stage0/ReCode.code"
                                                                opaque_type = ((struct Checked_Opaque_Type*) type);
#line 2843 "bootstrap/stage0/ReCode.code"
                                                                File__write_cstring(self, "struct ");
#line 2844 "bootstrap/stage0/ReCode.code"
                                                                File__write_string(self, opaque_type->super.name);
                                                            } goto if__end__13; } if__else__13: ;
#line 2845 "bootstrap/stage0/ReCode.code"
                                                        if__start__14: { if (type->kind == Checked_Type_Kind__ENUM) {
#line 2845 "bootstrap/stage0/ReCode.code"
                                                                { struct Checked_Enum_Type* enum_type;
#line 2846 "bootstrap/stage0/ReCode.code"
                                                                    enum_type = ((struct Checked_Enum_Type*) type);
#line 2847 "bootstrap/stage0/ReCode.code"
                                                                    File__write_cstring(self, "enum ");
#line 2848 "bootstrap/stage0/ReCode.code"
                                                                    File__write_string(self, enum_type->super.name);
                                                                } goto if__end__14; } if__else__14: ;
#line 2849 "bootstrap/stage0/ReCode.code"
                                                            if__start__15: { if (type->kind == Checked_Type_Kind__POINTER) {
#line 2849 "bootstrap/stage0/ReCode.code"
                                                                    { struct Checked_Pointer_Type* pointer_type;
#line 2850 "bootstrap/stage0/ReCode.code"
                                                                        pointer_type = ((struct Checked_Pointer_Type*) type);
#line 2851 "bootstrap/stage0/ReCode.code"
                                                                        File__write_checked_type(self, pointer_type->other_type);
#line 2852 "bootstrap/stage0/ReCode.code"
                                                                        File__write_char(self, '*');
                                                                    } goto if__end__15; } if__else__15: ;
#line 2853 "bootstrap/stage0/ReCode.code"
                                                                {
#line 2854 "bootstrap/stage0/ReCode.code"
                                                                    Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2855 "bootstrap/stage0/ReCode.code"
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

#line 2880 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbol__create_kind(enum Checked_Symbol_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name, struct Checked_Type* type) { struct Checked_Symbol* symbol;
#line 2881 "bootstrap/stage0/ReCode.code"
    symbol = ((struct Checked_Symbol*) malloc(kind_size));
#line 2882 "bootstrap/stage0/ReCode.code"
    symbol->kind = kind;
#line 2883 "bootstrap/stage0/ReCode.code"
    symbol->location = location;
#line 2884 "bootstrap/stage0/ReCode.code"
    symbol->name = name;
#line 2885 "bootstrap/stage0/ReCode.code"
    symbol->type = type;
#line 2886 "bootstrap/stage0/ReCode.code"
    symbol->prev_symbol = NULL;
#line 2887 "bootstrap/stage0/ReCode.code"
    symbol->next_symbol = NULL;
#line 2888 "bootstrap/stage0/ReCode.code"
    return symbol;}

#line 2895 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member_Symbol* Checked_Enum_Member_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2896 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Enum_Member_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__ENUM_MEMBER, sizeof(struct Checked_Enum_Member_Symbol), location, name, type));}

#line 2905 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Symbol* Checked_Function_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Function_Type* function_type) { struct Checked_Function_Symbol* symbol;
#line 2906 "bootstrap/stage0/ReCode.code"
    symbol = ((struct Checked_Function_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION, sizeof(struct Checked_Function_Symbol), location, name, ((struct Checked_Type*) function_type)));
#line 2907 "bootstrap/stage0/ReCode.code"
    symbol->function_type = function_type;
#line 2908 "bootstrap/stage0/ReCode.code"
    symbol->checked_statements = NULL;
#line 2909 "bootstrap/stage0/ReCode.code"
    return symbol;}

#line 2916 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter_Symbol* Checked_Function_Parameter_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2917 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Function_Parameter_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION_PARAMETER, sizeof(struct Checked_Function_Parameter_Symbol), location, name, type));}

#line 2925 "bootstrap/stage0/ReCode.code"
struct Checked_Type_Symbol* Checked_Type_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Named_Type* named_type) { struct Checked_Type_Symbol* symbol;
#line 2926 "bootstrap/stage0/ReCode.code"
    symbol = ((struct Checked_Type_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__TYPE, sizeof(struct Checked_Type_Symbol), location, name, ((struct Checked_Type*) Checked_Defined_Type__create(named_type))));
#line 2927 "bootstrap/stage0/ReCode.code"
    symbol->named_type = named_type;
#line 2928 "bootstrap/stage0/ReCode.code"
    return symbol;}

#line 2935 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Symbol* Checked_Variable__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2936 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Variable_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__VARIABLE, sizeof(struct Checked_Variable_Symbol), location, name, type));}

#line 2945 "bootstrap/stage0/ReCode.code"
struct Checked_Symbols* Checked_Symbols__create(struct Checked_Symbols* parent) { struct Checked_Symbols* symbols;
#line 2946 "bootstrap/stage0/ReCode.code"
    symbols = ((struct Checked_Symbols*) malloc(sizeof(struct Checked_Symbols)));
#line 2947 "bootstrap/stage0/ReCode.code"
    symbols->parent = parent;
#line 2948 "bootstrap/stage0/ReCode.code"
    symbols->first_symbol = NULL;
#line 2949 "bootstrap/stage0/ReCode.code"
    symbols->last_symbol = NULL;
#line 2950 "bootstrap/stage0/ReCode.code"
    return symbols;}

#line 2953 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_sibling_symbol(struct Checked_Symbols* self, struct String* name) { struct Checked_Symbol* symbol;
#line 2954 "bootstrap/stage0/ReCode.code"
    symbol = self->first_symbol;
#line 2955 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 2956 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, symbol->name)) {
#line 2956 "bootstrap/stage0/ReCode.code"
                {
#line 2957 "bootstrap/stage0/ReCode.code"
                    return symbol;
                } goto if__end__1; } if__end__1: ;
        }
#line 2959 "bootstrap/stage0/ReCode.code"
        symbol = symbol->next_symbol;
    }
#line 2961 "bootstrap/stage0/ReCode.code"
    return NULL;}

#line 2964 "bootstrap/stage0/ReCode.code"
void Checked_Symbols__append_symbol(struct Checked_Symbols* self, struct Checked_Symbol* symbol) { struct Checked_Symbol* other_symbol;
#line 2965 "bootstrap/stage0/ReCode.code"
    other_symbol = Checked_Symbols__find_sibling_symbol(self, symbol->name);
#line 2966 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_symbol != NULL) {
#line 2966 "bootstrap/stage0/ReCode.code"
            {
#line 2967 "bootstrap/stage0/ReCode.code"
                Source_Location__error(symbol->location, String__append_source_location(String__create_from("Symbol declared first here: "), other_symbol->location));
#line 2968 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 2971 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->last_symbol == NULL) {
#line 2971 "bootstrap/stage0/ReCode.code"
            {
#line 2972 "bootstrap/stage0/ReCode.code"
                self->first_symbol = symbol;
            } goto if__end__2; } if__else__2: ;
#line 2973 "bootstrap/stage0/ReCode.code"
        {
#line 2974 "bootstrap/stage0/ReCode.code"
            self->last_symbol->next_symbol = symbol;
#line 2975 "bootstrap/stage0/ReCode.code"
            symbol->prev_symbol = self->last_symbol;
        } if__end__2: ;
    }
#line 2977 "bootstrap/stage0/ReCode.code"
    self->last_symbol = symbol;}

#line 2980 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_symbol(struct Checked_Symbols* self, struct String* name) { struct Checked_Symbol* symbol;
#line 2981 "bootstrap/stage0/ReCode.code"
    symbol = self->last_symbol;
#line 2982 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 2983 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, symbol->name)) {
#line 2983 "bootstrap/stage0/ReCode.code"
                {
#line 2984 "bootstrap/stage0/ReCode.code"
                    return symbol;
                } goto if__end__1; } if__end__1: ;
        }
#line 2986 "bootstrap/stage0/ReCode.code"
        symbol = symbol->prev_symbol;
    }
#line 2988 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (self->parent != NULL) {
#line 2988 "bootstrap/stage0/ReCode.code"
            {
#line 2989 "bootstrap/stage0/ReCode.code"
                return Checked_Symbols__find_symbol(self->parent, name);
            } goto if__end__2; } if__end__2: ;
    }
#line 2991 "bootstrap/stage0/ReCode.code"
    return NULL;}

#line 3036 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checked_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type) { struct Checked_Expression* expression;
#line 3037 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Expression*) malloc(kind_size));
#line 3038 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 3039 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 3040 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 3041 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3050 "bootstrap/stage0/ReCode.code"
struct Checked_Binary_Expression* Checked_Binary_Expression__create_kind(enum Checked_Expression_Kind kind, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) { struct Checked_Binary_Expression* expression;
#line 3051 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Binary_Expression*) Checked_Expression__create_kind(kind, sizeof(struct Checked_Binary_Expression), location, type));
#line 3052 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 3053 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 3054 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3062 "bootstrap/stage0/ReCode.code"
struct Checked_Unary_Expression* Checked_Unary_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) { struct Checked_Unary_Expression* expression;
#line 3063 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Unary_Expression*) Checked_Expression__create_kind(kind, kind_size, location, type));
#line 3064 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3065 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3072 "bootstrap/stage0/ReCode.code"
struct Checked_Add_Expression* Checked_Add_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3073 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Add_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__ADD, location, type, left_expression, right_expression));}

#line 3080 "bootstrap/stage0/ReCode.code"
struct Checked_Address_Of_Expression* Checked_Address_Of_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3081 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Address_Of_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__ADDRESS_OF, sizeof(struct Checked_Address_Of_Expression), location, type, other_expression));}

#line 3090 "bootstrap/stage0/ReCode.code"
struct Checked_Array_Access_Expression* Checked_Array_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* array_expression, struct Checked_Expression* index_expression) { struct Checked_Array_Access_Expression* expression;
#line 3091 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Array_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__ARRAY_ACCESS, sizeof(struct Checked_Array_Access_Expression), location, type));
#line 3092 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 3093 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 3094 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3102 "bootstrap/stage0/ReCode.code"
struct Checked_Bool_Expression* Checked_Bool_Expression__create(struct Source_Location* location, struct Checked_Type* type, bool value) { struct Checked_Bool_Expression* expression;
#line 3103 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Bool_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__BOOL, sizeof(struct Checked_Bool_Expression), location, type));
#line 3104 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3105 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3113 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Argument* Checked_Call_Argument__create(struct Checked_Expression* expression) { struct Checked_Call_Argument* argument;
#line 3114 "bootstrap/stage0/ReCode.code"
    argument = ((struct Checked_Call_Argument*) malloc(sizeof(struct Checked_Call_Argument)));
#line 3115 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 3116 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 3117 "bootstrap/stage0/ReCode.code"
    return argument;}

#line 3126 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Expression* Checked_Call_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* callee_expression, struct Checked_Call_Argument* first_argument) { struct Checked_Call_Expression* expression;
#line 3127 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Call_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CALL, sizeof(struct Checked_Call_Expression), location, type));
#line 3128 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 3129 "bootstrap/stage0/ReCode.code"
    expression->first_argument = first_argument;
#line 3130 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3138 "bootstrap/stage0/ReCode.code"
struct Checked_Cast_Expression* Checked_Cast_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) { struct Checked_Cast_Expression* expression;
#line 3139 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Cast_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CAST, sizeof(struct Checked_Cast_Expression), location, type));
#line 3140 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3141 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3149 "bootstrap/stage0/ReCode.code"
struct Checked_Character_Expression* Checked_Character_Expression__create(struct Source_Location* location, struct Checked_Type* type, char value) { struct Checked_Character_Expression* expression;
#line 3150 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Character_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CHARACTER, sizeof(struct Checked_Character_Expression), location, type));
#line 3151 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3152 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3160 "bootstrap/stage0/ReCode.code"
struct Checked_Dereference_Expression* Checked_Dereference_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* value_expression) { struct Checked_Dereference_Expression* expression;
#line 3161 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Dereference_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__DEREFERENCE, sizeof(struct Checked_Dereference_Expression), location, type));
#line 3162 "bootstrap/stage0/ReCode.code"
    expression->value_expression = value_expression;
#line 3163 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3170 "bootstrap/stage0/ReCode.code"
struct Checked_Divide_Expression* Checked_Divide_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3171 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Divide_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__DIVIDE, location, type, left_expression, right_expression));}

#line 3178 "bootstrap/stage0/ReCode.code"
struct Checked_Equals_Expression* Checked_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3179 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__EQUALS, location, type, left_expression, right_expression));}

#line 3186 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Expression* Checked_Greater_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3187 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Greater_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER, location, type, left_expression, right_expression));}

#line 3194 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Or_Equals_Expression* Checked_Greater_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3195 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Greater_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER_OR_EQUALS, location, type, left_expression, right_expression));}

#line 3203 "bootstrap/stage0/ReCode.code"
struct Checked_Group_Expression* Checked_Group_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) { struct Checked_Group_Expression* expression;
#line 3204 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Group_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__GROUP, sizeof(struct Checked_Group_Expression), location, type));
#line 3205 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3206 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3214 "bootstrap/stage0/ReCode.code"
struct Checked_Integer_Expression* Checked_Integer_Expression__create(struct Source_Location* location, struct Checked_Type* type, uint64_t value) { struct Checked_Integer_Expression* expression;
#line 3215 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Integer_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__INTEGER, sizeof(struct Checked_Integer_Expression), location, type));
#line 3216 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3217 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3224 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Expression* Checked_Less_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3225 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Less_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS, location, type, left_expression, right_expression));}

#line 3232 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Or_Equals_Expression* Checked_Less_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3233 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Less_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS_OR_EQUALS, location, type, left_expression, right_expression));}

#line 3240 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_And_Expression* Checked_Logic_And_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3241 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Logic_And_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_AND, location, type, left_expression, right_expression));}

#line 3248 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_Or_Expression* Checked_Logic_Or_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3249 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Logic_Or_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_OR, location, type, left_expression, right_expression));}

#line 3258 "bootstrap/stage0/ReCode.code"
struct Checked_Member_Access_Expression* Checked_Member_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* object_expression, struct Checked_Struct_Member* member) { struct Checked_Member_Access_Expression* expression;
#line 3259 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Member_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__MEMBER_ACCESS, sizeof(struct Checked_Member_Access_Expression), location, type));
#line 3260 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 3261 "bootstrap/stage0/ReCode.code"
    expression->member = member;
#line 3262 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3269 "bootstrap/stage0/ReCode.code"
struct Checked_Minus_Expression* Checked_Minus_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3270 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Minus_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__MINUS, sizeof(struct Checked_Minus_Expression), location, type, other_expression));}

#line 3277 "bootstrap/stage0/ReCode.code"
struct Checked_Modulo_Expression* Checked_Modulo_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3278 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Modulo_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MODULO, location, type, left_expression, right_expression));}

#line 3285 "bootstrap/stage0/ReCode.code"
struct Checked_Multiply_Expression* Checked_Multiply_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3286 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Multiply_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MULTIPLY, location, type, left_expression, right_expression));}

#line 3293 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Expression* Checked_Not_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3294 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Not_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__NOT, sizeof(struct Checked_Not_Expression), location, type, other_expression));}

#line 3301 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Equals_Expression* Checked_Not_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3302 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Not_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__NOT_EQUALS, location, type, left_expression, right_expression));}

#line 3309 "bootstrap/stage0/ReCode.code"
struct Checked_Null_Expression* Checked_Null_Expression__create(struct Source_Location* location, struct Checked_Type* type) {
#line 3310 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Null_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__NULL, sizeof(struct Checked_Null_Expression), location, type));}

#line 3318 "bootstrap/stage0/ReCode.code"
struct Checked_Sizeof_Expression* Checked_Sizeof_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Type* sized_type) { struct Checked_Sizeof_Expression* expression;
#line 3319 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Sizeof_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SIZEOF, sizeof(struct Checked_Sizeof_Expression), location, type));
#line 3320 "bootstrap/stage0/ReCode.code"
    expression->sized_type = sized_type;
#line 3321 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3329 "bootstrap/stage0/ReCode.code"
struct Checked_String_Expression* Checked_String_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct String* value) { struct Checked_String_Expression* expression;
#line 3330 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_String_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__STRING, sizeof(struct Checked_String_Expression), location, type));
#line 3331 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3332 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3339 "bootstrap/stage0/ReCode.code"
struct Checked_Substract_Expression* Checked_Substract_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3340 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Substract_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__SUBSTRACT, location, type, left_expression, right_expression));}

#line 3348 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol_Expression* Checked_Symbol_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Symbol* symbol) { struct Checked_Symbol_Expression* expression;
#line 3349 "bootstrap/stage0/ReCode.code"
    expression = ((struct Checked_Symbol_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SYMBOL, sizeof(struct Checked_Symbol_Expression), location, type));
#line 3350 "bootstrap/stage0/ReCode.code"
    expression->symbol = symbol;
#line 3351 "bootstrap/stage0/ReCode.code"
    return expression;}

#line 3377 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checked_Statement__create_kind(enum Checked_Statement_Kind kind, size_t kind_size, struct Source_Location* location) { struct Checked_Statement* statement;
#line 3378 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Statement*) malloc(kind_size));
#line 3379 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 3380 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 3381 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 3382 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3391 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checked_Assignment_Statement__create(struct Source_Location* location, struct Checked_Expression* object_expression, struct Checked_Expression* value_expression) { struct Checked_Assignment_Statement* statement;
#line 3392 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Assignment_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__ASSIGNMENT, sizeof(struct Checked_Assignment_Statement), location));
#line 3393 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 3394 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 3395 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3404 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checked_Block_Statement__create(struct Source_Location* location, struct Checker_Context* context, struct String* label) { struct Checked_Block_Statement* statement;
#line 3405 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Block_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BLOCK, sizeof(struct Checked_Block_Statement), location));
#line 3406 "bootstrap/stage0/ReCode.code"
    statement->context = context;
#line 3407 "bootstrap/stage0/ReCode.code"
    statement->label = label;
#line 3408 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3415 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checked_Break_Statement__create(struct Source_Location* location) {
#line 3416 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Break_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BREAK, sizeof(struct Checked_Break_Statement), location));}

#line 3424 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checked_Expression_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) { struct Checked_Expression_Statement* statement;
#line 3425 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Expression_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__EXPRESSION, sizeof(struct Checked_Expression_Statement), location));
#line 3426 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3427 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3435 "bootstrap/stage0/ReCode.code"
struct Checked_Goto_Statement* Checked_Goto_Statement__create(struct Source_Location* location, struct String* label) { struct Checked_Goto_Statement* statement;
#line 3436 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Goto_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__GOTO, sizeof(struct Checked_Goto_Statement), location));
#line 3437 "bootstrap/stage0/ReCode.code"
    statement->label = label;
#line 3438 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3448 "bootstrap/stage0/ReCode.code"
struct Checked_If_Statement* Checked_If_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* true_statement, struct Checked_Statement* false_statement) { struct Checked_If_Statement* statement;
#line 3449 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_If_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__IF, sizeof(struct Checked_If_Statement), location));
#line 3450 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3451 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 3452 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 3453 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3461 "bootstrap/stage0/ReCode.code"
struct Checked_Label_Statement* Checked_Label_Statement__create(struct Source_Location* location, struct String* label) { struct Checked_Label_Statement* statement;
#line 3462 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Label_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__LABEL, sizeof(struct Checked_Label_Statement), location));
#line 3463 "bootstrap/stage0/ReCode.code"
    statement->label = label;
#line 3464 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3472 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checked_Return_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) { struct Checked_Return_Statement* statement;
#line 3473 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Return_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__RETURN, sizeof(struct Checked_Return_Statement), location));
#line 3474 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3475 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3485 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checked_Variable_Statement__create(struct Source_Location* location, struct Checked_Variable_Symbol* variable, struct Checked_Expression* expression, bool is_external) { struct Checked_Variable_Statement* statement;
#line 3486 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_Variable_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__VARIABLE, sizeof(struct Checked_Variable_Statement), location));
#line 3487 "bootstrap/stage0/ReCode.code"
    statement->variable = variable;
#line 3488 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3489 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 3490 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3499 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checked_While_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* body_statement) { struct Checked_While_Statement* statement;
#line 3500 "bootstrap/stage0/ReCode.code"
    statement = ((struct Checked_While_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__WHILE, sizeof(struct Checked_While_Statement), location));
#line 3501 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3502 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 3503 "bootstrap/stage0/ReCode.code"
    return statement;}

#line 3512 "bootstrap/stage0/ReCode.code"
struct Checked_Statements* Checked_Statements__create(struct Checked_Symbols* symbols) { struct Checked_Statements* statements;
#line 3513 "bootstrap/stage0/ReCode.code"
    statements = ((struct Checked_Statements*) malloc(sizeof(struct Checked_Statements)));
#line 3514 "bootstrap/stage0/ReCode.code"
    statements->symbols = symbols;
#line 3515 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 3516 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 3517 "bootstrap/stage0/ReCode.code"
    return statements;}

#line 3520 "bootstrap/stage0/ReCode.code"
void Checked_Statements__append(struct Checked_Statements* self, struct Checked_Statement* statement) {
#line 3521 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->first_statement == NULL) {
#line 3521 "bootstrap/stage0/ReCode.code"
            {
#line 3522 "bootstrap/stage0/ReCode.code"
                self->first_statement = statement;
            } goto if__end__1; } if__else__1: ;
#line 3523 "bootstrap/stage0/ReCode.code"
        {
#line 3524 "bootstrap/stage0/ReCode.code"
            self->last_statement->next_statement = statement;
        } if__end__1: ;
    }
#line 3526 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;}

#line 3551 "bootstrap/stage0/ReCode.code"
struct Checker_Context* Checker_Context__create(struct Checker_Context* parent) { struct Checker_Context* context;
#line 3552 "bootstrap/stage0/ReCode.code"
    context = ((struct Checker_Context*) malloc(sizeof(struct Checker_Context)));
#line 3553 "bootstrap/stage0/ReCode.code"
    context->parent = parent;
#line 3554 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parent == NULL) {
#line 3554 "bootstrap/stage0/ReCode.code"
            {
#line 3555 "bootstrap/stage0/ReCode.code"
                context->symbols = Checked_Symbols__create(NULL);
#line 3556 "bootstrap/stage0/ReCode.code"
                context->function_counter = Counter__create();
#line 3557 "bootstrap/stage0/ReCode.code"
                context->function_return_type = NULL;
            } goto if__end__1; } if__else__1: ;
#line 3558 "bootstrap/stage0/ReCode.code"
        {
#line 3559 "bootstrap/stage0/ReCode.code"
            context->symbols = Checked_Symbols__create(parent->symbols);
#line 3560 "bootstrap/stage0/ReCode.code"
            context->function_counter = parent->function_counter;
#line 3561 "bootstrap/stage0/ReCode.code"
            context->function_return_type = parent->function_return_type;
        } if__end__1: ;
    }
#line 3563 "bootstrap/stage0/ReCode.code"
    context->statements = Checked_Statements__create(context->symbols);
#line 3564 "bootstrap/stage0/ReCode.code"
    return context;}

#line 3576 "bootstrap/stage0/ReCode.code"
struct Checker* Checker__create() { struct Checker* checker; struct Source_Location* location;
#line 3577 "bootstrap/stage0/ReCode.code"
    checker = ((struct Checker*) malloc(sizeof(struct Checker)));
#line 3578 "bootstrap/stage0/ReCode.code"
    checker->first_type = NULL;
#line 3579 "bootstrap/stage0/ReCode.code"
    checker->last_type = NULL;
#line 3580 "bootstrap/stage0/ReCode.code"
    checker->root_context = Checker_Context__create(NULL);
#line 3581 "bootstrap/stage0/ReCode.code"
    checker->current_context = checker->root_context;
#line 3583 "bootstrap/stage0/ReCode.code"
    location = Source_Location__create(NULL, ((uint16_t) 0), ((uint16_t) 1));
#line 3584 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__BOOL, sizeof(struct Checked_Named_Type), location, String__create_from("bool")));
#line 3585 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__CHAR, sizeof(struct Checked_Named_Type), location, String__create_from("char")));
#line 3586 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I16, sizeof(struct Checked_Named_Type), location, String__create_from("i16")));
#line 3587 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I32, sizeof(struct Checked_Named_Type), location, String__create_from("i32")));
#line 3588 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I64, sizeof(struct Checked_Named_Type), location, String__create_from("i64")));
#line 3589 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I8, sizeof(struct Checked_Named_Type), location, String__create_from("i8")));
#line 3590 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U16, sizeof(struct Checked_Named_Type), location, String__create_from("u16")));
#line 3591 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U32, sizeof(struct Checked_Named_Type), location, String__create_from("u32")));
#line 3592 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U64, sizeof(struct Checked_Named_Type), location, String__create_from("u64")));
#line 3593 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U8, sizeof(struct Checked_Named_Type), location, String__create_from("u8")));
#line 3594 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__USIZE, sizeof(struct Checked_Named_Type), location, String__create_from("usize")));
#line 3595 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__VOID, sizeof(struct Checked_Named_Type), location, String__create_from("void")));
#line 3596 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__NULL, sizeof(struct Checked_Named_Type), location, String__create_from("null")));
#line 3597 "bootstrap/stage0/ReCode.code"
    checker->last_builting_type = checker->last_type;
#line 3599 "bootstrap/stage0/ReCode.code"
    return checker;}

#line 3602 "bootstrap/stage0/ReCode.code"
void Checker__append_type(struct Checker* self, struct Checked_Named_Type* type) {
#line 3603 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (self->first_type == NULL) {
#line 3603 "bootstrap/stage0/ReCode.code"
            {
#line 3604 "bootstrap/stage0/ReCode.code"
                self->first_type = type;
            } goto if__end__1; } if__else__1: ;
#line 3605 "bootstrap/stage0/ReCode.code"
        {
#line 3606 "bootstrap/stage0/ReCode.code"
            self->last_type->super.next_type = ((struct Checked_Type*) type);
        } if__end__1: ;
    }
#line 3608 "bootstrap/stage0/ReCode.code"
    self->last_type = type;
#line 3610 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->root_context->symbols, ((struct Checked_Symbol*) Checked_Type_Symbol__create(type->super.location, type->name, type)));}

#line 3613 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__find_type(struct Checker* self, struct String* name) { struct Checked_Named_Type* type;
#line 3614 "bootstrap/stage0/ReCode.code"
    type = self->first_type;
#line 3615 "bootstrap/stage0/ReCode.code"
    while (type != NULL) {
#line 3616 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (String__equals_string(name, type->name)) {
#line 3616 "bootstrap/stage0/ReCode.code"
                {
#line 3617 "bootstrap/stage0/ReCode.code"
                    break;
                } goto if__end__1; } if__end__1: ;
        }
#line 3619 "bootstrap/stage0/ReCode.code"
        type = ((struct Checked_Named_Type*) type->super.next_type);
    }
#line 3621 "bootstrap/stage0/ReCode.code"
    return type;}

#line 3624 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__get_builtin_type(struct Checker* self, enum Checked_Type_Kind kind) { struct Checked_Named_Type* type; struct Checked_Named_Type* custom_type;
#line 3625 "bootstrap/stage0/ReCode.code"
    type = self->first_type;
#line 3626 "bootstrap/stage0/ReCode.code"
    custom_type = ((struct Checked_Named_Type*) self->last_builting_type->super.next_type);
#line 3627 "bootstrap/stage0/ReCode.code"
    while (type != custom_type) {
#line 3628 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (type->super.kind == kind) {
#line 3628 "bootstrap/stage0/ReCode.code"
                {
#line 3629 "bootstrap/stage0/ReCode.code"
                    return type;
                } goto if__end__1; } if__end__1: ;
        }
#line 3631 "bootstrap/stage0/ReCode.code"
        type = ((struct Checked_Named_Type*) type->super.next_type);
    }
#line 3633 "bootstrap/stage0/ReCode.code"
    error(String__create_from("No such builtin type"));
#line 3634 "bootstrap/stage0/ReCode.code"
    abort();}

#line 3637 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checker__resolve_type(struct Checker* self, struct Parsed_Type* parsed_type) {
#line 3638 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_type->kind == Parsed_Type_Kind__NAMED) {
#line 3638 "bootstrap/stage0/ReCode.code"
            { struct Checked_Named_Type* type;
#line 3639 "bootstrap/stage0/ReCode.code"
                type = Checker__find_type(self, ((struct Parsed_Named_Type*) parsed_type)->name);
#line 3640 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (type != NULL) {
#line 3640 "bootstrap/stage0/ReCode.code"
                        {
#line 3641 "bootstrap/stage0/ReCode.code"
                            return ((struct Checked_Type*) type);
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 3644 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (parsed_type->kind == Parsed_Type_Kind__POINTER) {
#line 3644 "bootstrap/stage0/ReCode.code"
            {
#line 3645 "bootstrap/stage0/ReCode.code"
                return ((struct Checked_Type*) Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((struct Parsed_Pointer_Type*) parsed_type)->other_type)));
            } goto if__end__3; } if__end__3: ;
    }
#line 3647 "bootstrap/stage0/ReCode.code"
    if__start__4: { if (parsed_type->kind == Parsed_Type_Kind__STRUCT) {
#line 3647 "bootstrap/stage0/ReCode.code"
            { struct Checked_Type* type;
#line 3648 "bootstrap/stage0/ReCode.code"
                type = Checker__resolve_type(self, ((struct Parsed_Struct_Type*) parsed_type)->other_type);
#line 3649 "bootstrap/stage0/ReCode.code"
                if__start__5: { if (type->kind != Checked_Type_Kind__STRUCT) {
#line 3649 "bootstrap/stage0/ReCode.code"
                        {
#line 3650 "bootstrap/stage0/ReCode.code"
                            TODO("Report unexpected type");
#line 3651 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__5; } if__end__5: ;
                }
#line 3653 "bootstrap/stage0/ReCode.code"
                return type;
            } goto if__end__4; } if__end__4: ;
    }
#line 3655 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (parsed_type->kind == Parsed_Type_Kind__FUNCTION) {
#line 3655 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Function_Type* parsed_function_type; struct Checked_Function_Parameter* first_parameter; struct Parsed_Function_Parameter* parsed_parameter; struct Checked_Type* return_type;
#line 3656 "bootstrap/stage0/ReCode.code"
                parsed_function_type = ((struct Parsed_Function_Type*) parsed_type);
#line 3657 "bootstrap/stage0/ReCode.code"
                first_parameter = NULL;
#line 3658 "bootstrap/stage0/ReCode.code"
                parsed_parameter = parsed_function_type->first_parameter;
#line 3659 "bootstrap/stage0/ReCode.code"
                if__start__7: { if (parsed_parameter != NULL) {
#line 3659 "bootstrap/stage0/ReCode.code"
                        { struct Checked_Function_Parameter* last_parameter;
#line 3660 "bootstrap/stage0/ReCode.code"
                            first_parameter = Checked_Function_Parameter__create(parsed_parameter->location, NULL, Checker__resolve_type(self, parsed_parameter->type));
#line 3661 "bootstrap/stage0/ReCode.code"
                            last_parameter = first_parameter;
#line 3662 "bootstrap/stage0/ReCode.code"
                            parsed_parameter = parsed_parameter->next_parameter;
#line 3663 "bootstrap/stage0/ReCode.code"
                            while (parsed_parameter != NULL) { struct Checked_Function_Parameter* parameter;
#line 3664 "bootstrap/stage0/ReCode.code"
                                parameter = Checked_Function_Parameter__create(parsed_parameter->location, NULL, Checker__resolve_type(self, parsed_parameter->type));
#line 3665 "bootstrap/stage0/ReCode.code"
                                last_parameter->next_parameter = parameter;
#line 3666 "bootstrap/stage0/ReCode.code"
                                last_parameter = parameter;
#line 3667 "bootstrap/stage0/ReCode.code"
                                parsed_parameter = parsed_parameter->next_parameter;
                            }
                        } goto if__end__7; } if__end__7: ;
                }
#line 3670 "bootstrap/stage0/ReCode.code"
                return_type = Checker__resolve_type(self, parsed_function_type->return_type);
#line 3671 "bootstrap/stage0/ReCode.code"
                return ((struct Checked_Type*) Checked_Function_Type__create(parsed_type->location, first_parameter, return_type));
            } goto if__end__6; } if__end__6: ;
    }
#line 3673 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_type->location, String__create_from("Undefined type"));
#line 3674 "bootstrap/stage0/ReCode.code"
    abort();}

#line 3677 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_add_expression(struct Checker* self, struct Parsed_Add_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3678 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3679 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3680 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3681 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3682 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3685 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_address_of_expression(struct Checker* self, struct Parsed_Address_Of_Expression* parsed_expression) { struct Checked_Expression* other_expression;
#line 3686 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3687 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_expression->kind != Checked_Expression_Kind__SYMBOL) {
#line 3687 "bootstrap/stage0/ReCode.code"
            {
#line 3688 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.super.location, String__create_from("Not a symbol"));
#line 3689 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3691 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Address_Of_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checked_Pointer_Type__create(other_expression->location, other_expression->type)), other_expression));}

#line 3694 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_array_access_expression(struct Checker* self, struct Parsed_Array_Access_Expression* parsed_expression) { struct Checked_Expression* array_expression; struct Checked_Type* array_type; struct Checked_Type* type; struct Checked_Expression* index_expression;
#line 3695 "bootstrap/stage0/ReCode.code"
    array_expression = Checker__check_expression(self, parsed_expression->array_expression);
#line 3696 "bootstrap/stage0/ReCode.code"
    array_type = array_expression->type;
#line 3697 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (array_type->kind != Checked_Type_Kind__POINTER) {
#line 3697 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 3698 "bootstrap/stage0/ReCode.code"
                message = String__create();
#line 3699 "bootstrap/stage0/ReCode.code"
                String__append_char(message, '\"');
#line 3700 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, array_type);
#line 3701 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" is not a pointer type.");
#line 3702 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->array_expression->location, message);
#line 3703 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3705 "bootstrap/stage0/ReCode.code"
    type = ((struct Checked_Pointer_Type*) array_type)->other_type;
#line 3706 "bootstrap/stage0/ReCode.code"
    index_expression = Checker__check_expression(self, parsed_expression->index_expression);
#line 3707 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE)), index_expression->type, index_expression->location);
#line 3708 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression));}

#line 3711 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_bool_expression(struct Checker* self, struct Parsed_Bool_Expression* parsed_expression) { struct Checked_Type* expression_type; bool value;
#line 3712 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL));
#line 3713 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3714 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3717 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_call_expression(struct Checker* self, struct Parsed_Call_Expression* parsed_expression) { struct Checked_Expression* callee_expression; struct Checked_Type* callee_type; struct Checked_Function_Type* function_type; struct Checked_Call_Argument* first_argument;
#line 3718 "bootstrap/stage0/ReCode.code"
    callee_expression = Checker__check_expression(self, parsed_expression->callee_expression);
#line 3719 "bootstrap/stage0/ReCode.code"
    callee_type = callee_expression->type;
#line 3720 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (callee_type->kind != Checked_Type_Kind__FUNCTION) {
#line 3720 "bootstrap/stage0/ReCode.code"
            {
#line 3721 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.location, String__create_from("Not a function"));
#line 3722 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3724 "bootstrap/stage0/ReCode.code"
    function_type = ((struct Checked_Function_Type*) callee_type);
#line 3725 "bootstrap/stage0/ReCode.code"
    first_argument = NULL;
#line 3726 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (!(parsed_expression->first_argument != NULL)) { if (!(function_type->first_parameter != NULL)) { goto if__end__2; } } if__then__2__3: {
#line 3726 "bootstrap/stage0/ReCode.code"
            { struct Checked_Call_Argument* last_argument; struct Checked_Function_Parameter* function_parameter; struct Parsed_Call_Argument* parsed_argument;
#line 3727 "bootstrap/stage0/ReCode.code"
                last_argument = NULL;
#line 3728 "bootstrap/stage0/ReCode.code"
                function_parameter = function_type->first_parameter;
#line 3729 "bootstrap/stage0/ReCode.code"
                parsed_argument = parsed_expression->first_argument;
#line 3730 "bootstrap/stage0/ReCode.code"
                while (function_parameter != NULL && parsed_argument != NULL) { struct Checked_Expression* argument_expression; struct Checked_Call_Argument* argument;
#line 3731 "bootstrap/stage0/ReCode.code"
                    argument_expression = Checker__check_expression(self, parsed_argument->expression);
#line 3732 "bootstrap/stage0/ReCode.code"
                    Checked_Type__expect_same_type(function_parameter->type, argument_expression->type, argument_expression->location);
#line 3733 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (argument_expression->kind == Checked_Expression_Kind__SYMBOL) { if (((struct Checked_Symbol_Expression*) argument_expression)->symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 3733 "bootstrap/stage0/ReCode.code"
                                {
#line 3734 "bootstrap/stage0/ReCode.code"
                                    TODO("Create callable expression stored in a temp variable");
                                } goto if__end__4; } } if__end__4: ;
                    }
#line 3736 "bootstrap/stage0/ReCode.code"
                    argument = Checked_Call_Argument__create(argument_expression);
#line 3737 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (last_argument == NULL) {
#line 3737 "bootstrap/stage0/ReCode.code"
                            {
#line 3738 "bootstrap/stage0/ReCode.code"
                                first_argument = argument;
                            } goto if__end__5; } if__else__5: ;
#line 3739 "bootstrap/stage0/ReCode.code"
                        {
#line 3740 "bootstrap/stage0/ReCode.code"
                            last_argument->next_argument = argument;
                        } if__end__5: ;
                    }
#line 3742 "bootstrap/stage0/ReCode.code"
                    last_argument = argument;
#line 3743 "bootstrap/stage0/ReCode.code"
                    function_parameter = function_parameter->next_parameter;
#line 3744 "bootstrap/stage0/ReCode.code"
                    parsed_argument = parsed_argument->next_argument;
                }
#line 3746 "bootstrap/stage0/ReCode.code"
                if__start__6: { if (function_parameter != NULL) {
#line 3746 "bootstrap/stage0/ReCode.code"
                        {
#line 3747 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(parsed_expression->super.location, String__create_from("Report too few arguments"));
#line 3748 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__6; } if__end__6: ;
                }
#line 3750 "bootstrap/stage0/ReCode.code"
                if__start__7: { if (parsed_argument != NULL) {
#line 3750 "bootstrap/stage0/ReCode.code"
                        {
#line 3751 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(parsed_expression->super.location, String__create_from("Report too many arguments"));
#line 3752 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__7; } if__end__7: ;
                }
            } goto if__end__2; } if__end__2: ;
    }
#line 3755 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Call_Expression__create(parsed_expression->super.location, function_type->return_type, callee_expression, first_argument));}

#line 3758 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_cast_expression(struct Checker* self, struct Parsed_Cast_Expression* parsed_expression) { struct Checked_Type* type; struct Checked_Expression* other_expression; struct Checked_Type* other_type; bool can_cast;
#line 3759 "bootstrap/stage0/ReCode.code"
    type = Checker__resolve_type(self, parsed_expression->type);
#line 3760 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3761 "bootstrap/stage0/ReCode.code"
    other_type = other_expression->type;
#line 3762 "bootstrap/stage0/ReCode.code"
    can_cast = false;
#line 3763 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (type->kind == Checked_Type_Kind__POINTER) {
#line 3763 "bootstrap/stage0/ReCode.code"
            {
#line 3764 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (other_type->kind == Checked_Type_Kind__POINTER) {
#line 3764 "bootstrap/stage0/ReCode.code"
                        {
#line 3765 "bootstrap/stage0/ReCode.code"
                            can_cast = true;
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 3767 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (Checked_Type__is_scalar_type(type)) {
#line 3767 "bootstrap/stage0/ReCode.code"
                {
#line 3768 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (Checked_Type__is_scalar_type(type)) {
#line 3768 "bootstrap/stage0/ReCode.code"
                            {
#line 3769 "bootstrap/stage0/ReCode.code"
                                can_cast = true;
                            } goto if__end__4; } if__end__4: ;
                    }
                } goto if__end__3; } if__end__3: ;
        } if__end__1: ;
    }
#line 3772 "bootstrap/stage0/ReCode.code"
    if__start__5: { if (Checked_Type__equals(type, other_type)) {
#line 3772 "bootstrap/stage0/ReCode.code"
            {
#line 3773 "bootstrap/stage0/ReCode.code"
                Source_Location__warning(parsed_expression->super.super.location, String__create_from("Redundant cast"));
            } goto if__end__5; } if__end__5: ;
    }
#line 3775 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (!(can_cast)) {
#line 3775 "bootstrap/stage0/ReCode.code"
            { struct String* message;
#line 3776 "bootstrap/stage0/ReCode.code"
                message = String__create_from("Cannot cast \"");
#line 3777 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, other_expression->type);
#line 3778 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\" to \"");
#line 3779 "bootstrap/stage0/ReCode.code"
                String__append_checked_type(message, type);
#line 3780 "bootstrap/stage0/ReCode.code"
                String__append_cstring(message, "\".");
#line 3781 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.super.location, message);
#line 3782 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__6; } if__end__6: ;
    }
#line 3784 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Cast_Expression__create(parsed_expression->super.super.location, type, other_expression));}

#line 3787 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_character_expression(struct Checker* self, struct Parsed_Character_Expression* parsed_expression) { struct Checked_Type* expression_type; char value;
#line 3788 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR));
#line 3789 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3790 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3793 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_dereference_expression(struct Checker* self, struct Parsed_Dereference_Expression* parsed_expression) { struct Checked_Expression* value_expression; struct Checked_Type* value_type;
#line 3794 "bootstrap/stage0/ReCode.code"
    value_expression = Checker__check_expression(self, parsed_expression->value_expression);
#line 3795 "bootstrap/stage0/ReCode.code"
    value_type = value_expression->type;
#line 3796 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (value_type->kind != Checked_Type_Kind__POINTER) {
#line 3796 "bootstrap/stage0/ReCode.code"
            {
#line 3797 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_expression->super.location, String__create_from("Not a pointer value"));
#line 3798 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3800 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Dereference_Expression__create(parsed_expression->super.location, ((struct Checked_Pointer_Type*) value_type)->other_type, value_expression));}

#line 3803 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_divide_expression(struct Checker* self, struct Parsed_Divide_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3804 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3805 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3806 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3807 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3808 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3811 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_equals_expression(struct Checker* self, struct Parsed_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3812 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3813 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3814 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3815 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3818 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_expression(struct Checker* self, struct Parsed_Greater_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3819 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3820 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3821 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3822 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3823 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Greater_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3826 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_or_equals_expression(struct Checker* self, struct Parsed_Greater_Or_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3827 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3828 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3829 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3830 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3831 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3834 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_group_expression(struct Checker* self, struct Parsed_Group_Expression* parsed_expression) { struct Checked_Expression* other_expression;
#line 3835 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->other_expression);
#line 3836 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression));}

#line 3839 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_integer_expression(struct Checker* self, struct Parsed_Integer_Expression* parsed_expression) { struct Checked_Type* expression_type; uint64_t value;
#line 3840 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__I32));
#line 3841 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3842 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3845 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_expression(struct Checker* self, struct Parsed_Less_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3846 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3847 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3848 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3849 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3850 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Less_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3853 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_or_equals_expression(struct Checker* self, struct Parsed_Less_Or_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3854 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3855 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3856 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3857 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3858 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3861 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_and_expression(struct Checker* self, struct Parsed_Logic_And_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3862 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3863 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression->type, left_expression->location);
#line 3864 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3865 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3866 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3869 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_or_expression(struct Checker* self, struct Parsed_Logic_Or_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3870 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3871 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression->type, left_expression->location);
#line 3872 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3873 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3874 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3877 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_member_access_expression(struct Checker* self, struct Parsed_Member_Access_Expression* parsed_expression) { struct Checked_Expression* object_expression; struct Checked_Type* object_type;
#line 3878 "bootstrap/stage0/ReCode.code"
    object_expression = Checker__check_expression(self, parsed_expression->object_expression);
#line 3879 "bootstrap/stage0/ReCode.code"
    object_type = object_expression->type;
#line 3880 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (object_type->kind == Checked_Type_Kind__POINTER) {
#line 3880 "bootstrap/stage0/ReCode.code"
            {
#line 3881 "bootstrap/stage0/ReCode.code"
                object_type = ((struct Checked_Pointer_Type*) object_type)->other_type;
#line 3882 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3882 "bootstrap/stage0/ReCode.code"
                        {
#line 3883 "bootstrap/stage0/ReCode.code"
                            return Checker__check_struct_member_access_expression(self, object_expression, ((struct Checked_Struct_Type*) object_type), parsed_expression->member_name);
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 3885 "bootstrap/stage0/ReCode.code"
        if__start__3: { if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3885 "bootstrap/stage0/ReCode.code"
                {
#line 3886 "bootstrap/stage0/ReCode.code"
                    return Checker__check_struct_member_access_expression(self, object_expression, ((struct Checked_Struct_Type*) object_type), parsed_expression->member_name);
                } goto if__end__3; } if__else__3: ;
#line 3887 "bootstrap/stage0/ReCode.code"
            if__start__4: { if (object_type->kind == Checked_Type_Kind__DEFINED) {
#line 3887 "bootstrap/stage0/ReCode.code"
                    { struct Checked_Named_Type* defined_type;
#line 3888 "bootstrap/stage0/ReCode.code"
                        defined_type = ((struct Checked_Defined_Type*) object_type)->defined_type;
#line 3889 "bootstrap/stage0/ReCode.code"
                        if__start__5: { if (defined_type->super.kind == Checked_Type_Kind__ENUM) {
#line 3889 "bootstrap/stage0/ReCode.code"
                                { struct Checked_Enum_Type* enum_type; struct Checked_Enum_Member* enum_member;
#line 3890 "bootstrap/stage0/ReCode.code"
                                    enum_type = ((struct Checked_Enum_Type*) defined_type);
#line 3891 "bootstrap/stage0/ReCode.code"
                                    enum_member = Checked_Enum_Type__find_member(enum_type, parsed_expression->member_name->lexeme);
#line 3892 "bootstrap/stage0/ReCode.code"
                                    if__start__6: { if (enum_member == NULL) {
#line 3892 "bootstrap/stage0/ReCode.code"
                                            {
#line 3893 "bootstrap/stage0/ReCode.code"
                                                Source_Location__error(object_expression->location, String__create_from("No such enum members"));
#line 3894 "bootstrap/stage0/ReCode.code"
                                                abort();
                                            } goto if__end__6; } if__end__6: ;
                                    }
#line 3896 "bootstrap/stage0/ReCode.code"
                                    return ((struct Checked_Expression*) Checked_Symbol_Expression__create(object_expression->location, ((struct Checked_Type*) enum_type), enum_member->symbol));
                                } goto if__end__5; } if__end__5: ;
                        }
#line 3898 "bootstrap/stage0/ReCode.code"
                        Source_Location__error(object_expression->location, String__create_from("Type has no members"));
#line 3899 "bootstrap/stage0/ReCode.code"
                        abort();
                    } goto if__end__4; } if__end__4: ;
            } if__end__3: ;
        } if__end__1: ;
    }
#line 3901 "bootstrap/stage0/ReCode.code"
    Source_Location__error(object_expression->location, String__create_from("Unsupported type"));
#line 3902 "bootstrap/stage0/ReCode.code"
    abort();}

#line 3905 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_struct_member_access_expression(struct Checker* self, struct Checked_Expression* object_expression, struct Checked_Struct_Type* struct_type, struct Token* member_name) { struct Checked_Struct_Member* member;
#line 3906 "bootstrap/stage0/ReCode.code"
    member = Checked_Struct_Type__find_member(struct_type, member_name->lexeme);
#line 3907 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (member == NULL) {
#line 3907 "bootstrap/stage0/ReCode.code"
            {
#line 3908 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (struct_type->super_type != NULL) {
#line 3908 "bootstrap/stage0/ReCode.code"
                        {
#line 3909 "bootstrap/stage0/ReCode.code"
                            object_expression = ((struct Checked_Expression*) Checked_Member_Access_Expression__create(object_expression->location, struct_type->first_member->type, object_expression, struct_type->first_member));
#line 3910 "bootstrap/stage0/ReCode.code"
                            return Checker__check_struct_member_access_expression(self, object_expression, struct_type->super_type, member_name);
                        } goto if__end__2; } if__end__2: ;
                }
#line 3912 "bootstrap/stage0/ReCode.code"
                Source_Location__error(member_name->location, String__create_from("No such struct member"));
#line 3913 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3915 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Member_Access_Expression__create(object_expression->location, member->type, object_expression, member));}

#line 3918 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_minus_expression(struct Checker* self, struct Parsed_Minus_Expression* parsed_expression) { struct Checked_Expression* other_expression; struct Checked_Type* other_expression_type;
#line 3919 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3920 "bootstrap/stage0/ReCode.code"
    other_expression_type = other_expression->type;
#line 3921 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(other_expression_type, other_expression->location);
#line 3922 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression));}

#line 3925 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_modulo_expression(struct Checker* self, struct Parsed_Modulo_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3926 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3927 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3928 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3929 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3930 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3933 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_multiply_expression(struct Checker* self, struct Parsed_Multiply_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3934 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3935 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3936 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3937 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3938 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3941 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_expression(struct Checker* self, struct Parsed_Not_Expression* parsed_expression) { struct Checked_Expression* other_expression; struct Checked_Type* other_expression_type;
#line 3942 "bootstrap/stage0/ReCode.code"
    other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3943 "bootstrap/stage0/ReCode.code"
    other_expression_type = other_expression->type;
#line 3944 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), other_expression_type, other_expression->location);
#line 3945 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression));}

#line 3948 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_equals_expression(struct Checker* self, struct Parsed_Not_Equals_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3949 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3950 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3951 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3952 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), left_expression, right_expression));}

#line 3955 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_null_expression(struct Checker* self, struct Parsed_Null_Expression* parsed_expression) { struct Checked_Type* expression_type;
#line 3956 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__NULL));
#line 3957 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type));}

#line 3960 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_sizeof_expression(struct Checker* self, struct Parsed_Sizeof_Expression* parsed_expression) { struct Checked_Type* expression_type; struct Checked_Type* sized_type;
#line 3961 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE));
#line 3962 "bootstrap/stage0/ReCode.code"
    sized_type = Checker__resolve_type(self, parsed_expression->type);
#line 3963 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type));}

#line 3966 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_string_expression(struct Checker* self, struct Parsed_String_Expression* parsed_expression) { struct Checked_Type* char_type; struct Checked_Type* expression_type; struct String* value;
#line 3967 "bootstrap/stage0/ReCode.code"
    char_type = ((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR));
#line 3968 "bootstrap/stage0/ReCode.code"
    expression_type = ((struct Checked_Type*) Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type));
#line 3969 "bootstrap/stage0/ReCode.code"
    value = parsed_expression->value;
#line 3970 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value));}

#line 3973 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_substract_expression(struct Checker* self, struct Parsed_Substract_Expression* parsed_expression) { struct Checked_Expression* left_expression; struct Checked_Expression* right_expression;
#line 3974 "bootstrap/stage0/ReCode.code"
    left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3975 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3976 "bootstrap/stage0/ReCode.code"
    right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3977 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3978 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression));}

#line 3981 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_symbol_expression(struct Checker* self, struct Parsed_Symbol_Expression* parsed_expression) { struct Checked_Symbol* symbol;
#line 3982 "bootstrap/stage0/ReCode.code"
    symbol = Checked_Symbols__find_symbol(self->current_context->symbols, parsed_expression->name->lexeme);
#line 3983 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (symbol == NULL) {
#line 3983 "bootstrap/stage0/ReCode.code"
            {
#line 3984 "bootstrap/stage0/ReCode.code"
                Token__error(parsed_expression->name, String__create_from("Undefined symbol"));
#line 3985 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 3987 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (symbol->type == NULL) {
#line 3987 "bootstrap/stage0/ReCode.code"
            {
#line 3988 "bootstrap/stage0/ReCode.code"
                Token__error(parsed_expression->name, String__create_from("Symbol without type"));
#line 3989 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__2; } if__end__2: ;
    }
#line 3991 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Expression*) Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol));}

#line 3994 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_expression(struct Checker* self, struct Parsed_Expression* parsed_expression) {
#line 3995 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_expression->kind == Parsed_Expression_Kind__ADD) {
#line 3995 "bootstrap/stage0/ReCode.code"
            {
#line 3996 "bootstrap/stage0/ReCode.code"
                return Checker__check_add_expression(self, ((struct Parsed_Add_Expression*) parsed_expression));
            } goto if__end__1; } if__else__1: ;
#line 3997 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (parsed_expression->kind == Parsed_Expression_Kind__ADDRESS_OF) {
#line 3997 "bootstrap/stage0/ReCode.code"
                {
#line 3998 "bootstrap/stage0/ReCode.code"
                    return Checker__check_address_of_expression(self, ((struct Parsed_Address_Of_Expression*) parsed_expression));
                } goto if__end__2; } if__else__2: ;
#line 3999 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parsed_expression->kind == Parsed_Expression_Kind__ARRAY_ACCESS) {
#line 3999 "bootstrap/stage0/ReCode.code"
                    {
#line 4000 "bootstrap/stage0/ReCode.code"
                        return Checker__check_array_access_expression(self, ((struct Parsed_Array_Access_Expression*) parsed_expression));
                    } goto if__end__3; } if__else__3: ;
#line 4001 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (parsed_expression->kind == Parsed_Expression_Kind__BOOL) {
#line 4001 "bootstrap/stage0/ReCode.code"
                        {
#line 4002 "bootstrap/stage0/ReCode.code"
                            return Checker__check_bool_expression(self, ((struct Parsed_Bool_Expression*) parsed_expression));
                        } goto if__end__4; } if__else__4: ;
#line 4003 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (parsed_expression->kind == Parsed_Expression_Kind__CALL) {
#line 4003 "bootstrap/stage0/ReCode.code"
                            {
#line 4004 "bootstrap/stage0/ReCode.code"
                                return Checker__check_call_expression(self, ((struct Parsed_Call_Expression*) parsed_expression));
                            } goto if__end__5; } if__else__5: ;
#line 4005 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (parsed_expression->kind == Parsed_Expression_Kind__CAST) {
#line 4005 "bootstrap/stage0/ReCode.code"
                                {
#line 4006 "bootstrap/stage0/ReCode.code"
                                    return Checker__check_cast_expression(self, ((struct Parsed_Cast_Expression*) parsed_expression));
                                } goto if__end__6; } if__else__6: ;
#line 4007 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (parsed_expression->kind == Parsed_Expression_Kind__CHARACTER) {
#line 4007 "bootstrap/stage0/ReCode.code"
                                    {
#line 4008 "bootstrap/stage0/ReCode.code"
                                        return Checker__check_character_expression(self, ((struct Parsed_Character_Expression*) parsed_expression));
                                    } goto if__end__7; } if__else__7: ;
#line 4009 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (parsed_expression->kind == Parsed_Expression_Kind__DEREFERENCE) {
#line 4009 "bootstrap/stage0/ReCode.code"
                                        {
#line 4010 "bootstrap/stage0/ReCode.code"
                                            return Checker__check_dereference_expression(self, ((struct Parsed_Dereference_Expression*) parsed_expression));
                                        } goto if__end__8; } if__else__8: ;
#line 4011 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (parsed_expression->kind == Parsed_Expression_Kind__DIVIDE) {
#line 4011 "bootstrap/stage0/ReCode.code"
                                            {
#line 4012 "bootstrap/stage0/ReCode.code"
                                                return Checker__check_divide_expression(self, ((struct Parsed_Divide_Expression*) parsed_expression));
                                            } goto if__end__9; } if__else__9: ;
#line 4013 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (parsed_expression->kind == Parsed_Expression_Kind__EQUALS) {
#line 4013 "bootstrap/stage0/ReCode.code"
                                                {
#line 4014 "bootstrap/stage0/ReCode.code"
                                                    return Checker__check_equals_expression(self, ((struct Parsed_Equals_Expression*) parsed_expression));
                                                } goto if__end__10; } if__else__10: ;
#line 4015 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (parsed_expression->kind == Parsed_Expression_Kind__GREATER) {
#line 4015 "bootstrap/stage0/ReCode.code"
                                                    {
#line 4016 "bootstrap/stage0/ReCode.code"
                                                        return Checker__check_greater_expression(self, ((struct Parsed_Greater_Expression*) parsed_expression));
                                                    } goto if__end__11; } if__else__11: ;
#line 4017 "bootstrap/stage0/ReCode.code"
                                                if__start__12: { if (parsed_expression->kind == Parsed_Expression_Kind__GREATER_OR_EQUALS) {
#line 4017 "bootstrap/stage0/ReCode.code"
                                                        {
#line 4018 "bootstrap/stage0/ReCode.code"
                                                            return Checker__check_greater_or_equals_expression(self, ((struct Parsed_Greater_Or_Equals_Expression*) parsed_expression));
                                                        } goto if__end__12; } if__else__12: ;
#line 4019 "bootstrap/stage0/ReCode.code"
                                                    if__start__13: { if (parsed_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 4019 "bootstrap/stage0/ReCode.code"
                                                            {
#line 4020 "bootstrap/stage0/ReCode.code"
                                                                return Checker__check_group_expression(self, ((struct Parsed_Group_Expression*) parsed_expression));
                                                            } goto if__end__13; } if__else__13: ;
#line 4021 "bootstrap/stage0/ReCode.code"
                                                        if__start__14: { if (parsed_expression->kind == Parsed_Expression_Kind__INTEGER) {
#line 4021 "bootstrap/stage0/ReCode.code"
                                                                {
#line 4022 "bootstrap/stage0/ReCode.code"
                                                                    return Checker__check_integer_expression(self, ((struct Parsed_Integer_Expression*) parsed_expression));
                                                                } goto if__end__14; } if__else__14: ;
#line 4023 "bootstrap/stage0/ReCode.code"
                                                            if__start__15: { if (parsed_expression->kind == Parsed_Expression_Kind__LESS) {
#line 4023 "bootstrap/stage0/ReCode.code"
                                                                    {
#line 4024 "bootstrap/stage0/ReCode.code"
                                                                        return Checker__check_less_expression(self, ((struct Parsed_Less_Expression*) parsed_expression));
                                                                    } goto if__end__15; } if__else__15: ;
#line 4025 "bootstrap/stage0/ReCode.code"
                                                                if__start__16: { if (parsed_expression->kind == Parsed_Expression_Kind__LESS_OR_EQUALS) {
#line 4025 "bootstrap/stage0/ReCode.code"
                                                                        {
#line 4026 "bootstrap/stage0/ReCode.code"
                                                                            return Checker__check_less_or_equals_expression(self, ((struct Parsed_Less_Or_Equals_Expression*) parsed_expression));
                                                                        } goto if__end__16; } if__else__16: ;
#line 4027 "bootstrap/stage0/ReCode.code"
                                                                    if__start__17: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 4027 "bootstrap/stage0/ReCode.code"
                                                                            {
#line 4028 "bootstrap/stage0/ReCode.code"
                                                                                return Checker__check_logic_and_expression(self, ((struct Parsed_Logic_And_Expression*) parsed_expression));
                                                                            } goto if__end__17; } if__else__17: ;
#line 4029 "bootstrap/stage0/ReCode.code"
                                                                        if__start__18: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 4029 "bootstrap/stage0/ReCode.code"
                                                                                {
#line 4030 "bootstrap/stage0/ReCode.code"
                                                                                    return Checker__check_logic_or_expression(self, ((struct Parsed_Logic_Or_Expression*) parsed_expression));
                                                                                } goto if__end__18; } if__else__18: ;
#line 4031 "bootstrap/stage0/ReCode.code"
                                                                            if__start__19: { if (parsed_expression->kind == Parsed_Expression_Kind__MEMBER_ACCESS) {
#line 4031 "bootstrap/stage0/ReCode.code"
                                                                                    {
#line 4032 "bootstrap/stage0/ReCode.code"
                                                                                        return Checker__check_member_access_expression(self, ((struct Parsed_Member_Access_Expression*) parsed_expression));
                                                                                    } goto if__end__19; } if__else__19: ;
#line 4033 "bootstrap/stage0/ReCode.code"
                                                                                if__start__20: { if (parsed_expression->kind == Parsed_Expression_Kind__MINUS) {
#line 4033 "bootstrap/stage0/ReCode.code"
                                                                                        {
#line 4034 "bootstrap/stage0/ReCode.code"
                                                                                            return Checker__check_minus_expression(self, ((struct Parsed_Minus_Expression*) parsed_expression));
                                                                                        } goto if__end__20; } if__else__20: ;
#line 4035 "bootstrap/stage0/ReCode.code"
                                                                                    if__start__21: { if (parsed_expression->kind == Parsed_Expression_Kind__MODULO) {
#line 4035 "bootstrap/stage0/ReCode.code"
                                                                                            {
#line 4036 "bootstrap/stage0/ReCode.code"
                                                                                                return Checker__check_modulo_expression(self, ((struct Parsed_Modulo_Expression*) parsed_expression));
                                                                                            } goto if__end__21; } if__else__21: ;
#line 4037 "bootstrap/stage0/ReCode.code"
                                                                                        if__start__22: { if (parsed_expression->kind == Parsed_Expression_Kind__MULTIPLY) {
#line 4037 "bootstrap/stage0/ReCode.code"
                                                                                                {
#line 4038 "bootstrap/stage0/ReCode.code"
                                                                                                    return Checker__check_multiply_expression(self, ((struct Parsed_Multiply_Expression*) parsed_expression));
                                                                                                } goto if__end__22; } if__else__22: ;
#line 4039 "bootstrap/stage0/ReCode.code"
                                                                                            if__start__23: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) {
#line 4039 "bootstrap/stage0/ReCode.code"
                                                                                                    {
#line 4040 "bootstrap/stage0/ReCode.code"
                                                                                                        return Checker__check_not_expression(self, ((struct Parsed_Not_Expression*) parsed_expression));
                                                                                                    } goto if__end__23; } if__else__23: ;
#line 4041 "bootstrap/stage0/ReCode.code"
                                                                                                if__start__24: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT_EQUALS) {
#line 4041 "bootstrap/stage0/ReCode.code"
                                                                                                        {
#line 4042 "bootstrap/stage0/ReCode.code"
                                                                                                            return Checker__check_not_equals_expression(self, ((struct Parsed_Not_Equals_Expression*) parsed_expression));
                                                                                                        } goto if__end__24; } if__else__24: ;
#line 4043 "bootstrap/stage0/ReCode.code"
                                                                                                    if__start__25: { if (parsed_expression->kind == Parsed_Expression_Kind__NULL) {
#line 4043 "bootstrap/stage0/ReCode.code"
                                                                                                            {
#line 4044 "bootstrap/stage0/ReCode.code"
                                                                                                                return Checker__check_null_expression(self, ((struct Parsed_Null_Expression*) parsed_expression));
                                                                                                            } goto if__end__25; } if__else__25: ;
#line 4045 "bootstrap/stage0/ReCode.code"
                                                                                                        if__start__26: { if (parsed_expression->kind == Parsed_Expression_Kind__SIZEOF) {
#line 4045 "bootstrap/stage0/ReCode.code"
                                                                                                                {
#line 4046 "bootstrap/stage0/ReCode.code"
                                                                                                                    return Checker__check_sizeof_expression(self, ((struct Parsed_Sizeof_Expression*) parsed_expression));
                                                                                                                } goto if__end__26; } if__else__26: ;
#line 4047 "bootstrap/stage0/ReCode.code"
                                                                                                            if__start__27: { if (parsed_expression->kind == Parsed_Expression_Kind__STRING) {
#line 4047 "bootstrap/stage0/ReCode.code"
                                                                                                                    {
#line 4048 "bootstrap/stage0/ReCode.code"
                                                                                                                        return Checker__check_string_expression(self, ((struct Parsed_String_Expression*) parsed_expression));
                                                                                                                    } goto if__end__27; } if__else__27: ;
#line 4049 "bootstrap/stage0/ReCode.code"
                                                                                                                if__start__28: { if (parsed_expression->kind == Parsed_Expression_Kind__SUBSTRACT) {
#line 4049 "bootstrap/stage0/ReCode.code"
                                                                                                                        {
#line 4050 "bootstrap/stage0/ReCode.code"
                                                                                                                            return Checker__check_substract_expression(self, ((struct Parsed_Substract_Expression*) parsed_expression));
                                                                                                                        } goto if__end__28; } if__else__28: ;
#line 4051 "bootstrap/stage0/ReCode.code"
                                                                                                                    if__start__29: { if (parsed_expression->kind == Parsed_Expression_Kind__SYMBOL) {
#line 4051 "bootstrap/stage0/ReCode.code"
                                                                                                                            {
#line 4052 "bootstrap/stage0/ReCode.code"
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
#line 4054 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_expression->location, String__append_i16(String__create_from("Unsupported expression kind: "), ((int16_t) parsed_expression->kind)));
#line 4055 "bootstrap/stage0/ReCode.code"
    abort();}

#line 4058 "bootstrap/stage0/ReCode.code"
void Checker__check_enum_statement(struct Checker* self, struct Parsed_Enum_Statement* parsed_statement) { struct Checked_Enum_Type* enum_type; struct Checked_Enum_Member* last_enum_member; struct Parsed_Enum_Member* parsed_enum_member;
#line 4059 "bootstrap/stage0/ReCode.code"
    enum_type = Checked_Enum_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4060 "bootstrap/stage0/ReCode.code"
    Checker__append_type(self, ((struct Checked_Named_Type*) enum_type));
#line 4062 "bootstrap/stage0/ReCode.code"
    last_enum_member = NULL;
#line 4063 "bootstrap/stage0/ReCode.code"
    parsed_enum_member = parsed_statement->first_member;
#line 4064 "bootstrap/stage0/ReCode.code"
    while (parsed_enum_member != NULL) { struct Checked_Enum_Member* enum_member; struct String* enum_member_symbol_name;
#line 4065 "bootstrap/stage0/ReCode.code"
        enum_member = Checked_Enum_Member__create(parsed_enum_member->name->location, parsed_enum_member->name->lexeme);
#line 4066 "bootstrap/stage0/ReCode.code"
        enum_member_symbol_name = String__append_string(String__append_cstring(String__append_string(String__create(), enum_type->super.name), "__"), enum_member->name);
#line 4067 "bootstrap/stage0/ReCode.code"
        enum_member->symbol = ((struct Checked_Symbol*) Checked_Enum_Member_Symbol__create(enum_member->location, enum_member_symbol_name, ((struct Checked_Type*) enum_type)));
#line 4068 "bootstrap/stage0/ReCode.code"
        Checked_Symbols__append_symbol(self->root_context->symbols, enum_member->symbol);
#line 4069 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (last_enum_member == NULL) {
#line 4069 "bootstrap/stage0/ReCode.code"
                {
#line 4070 "bootstrap/stage0/ReCode.code"
                    enum_type->first_member = enum_member;
                } goto if__end__1; } if__else__1: ;
#line 4071 "bootstrap/stage0/ReCode.code"
            {
#line 4072 "bootstrap/stage0/ReCode.code"
                last_enum_member->next_member = enum_member;
            } if__end__1: ;
        }
#line 4074 "bootstrap/stage0/ReCode.code"
        last_enum_member = enum_member;
#line 4075 "bootstrap/stage0/ReCode.code"
        parsed_enum_member = parsed_enum_member->next_member;
    }}

#line 4079 "bootstrap/stage0/ReCode.code"
void Checker__create_opaque_type(struct Checker* self, struct Parsed_Opaque_Type_Statement* parsed_statement) { struct Checked_Named_Type* other_type;
#line 4080 "bootstrap/stage0/ReCode.code"
    other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4081 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type != NULL) {
#line 4081 "bootstrap/stage0/ReCode.code"
            {
#line 4082 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4083 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__else__1: ;
#line 4084 "bootstrap/stage0/ReCode.code"
        { struct Checked_Opaque_Type* opaque_type;
#line 4085 "bootstrap/stage0/ReCode.code"
            opaque_type = Checked_Opaque_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4086 "bootstrap/stage0/ReCode.code"
            Checker__append_type(self, ((struct Checked_Named_Type*) opaque_type));
        } if__end__1: ;
    }}

#line 4090 "bootstrap/stage0/ReCode.code"
void Checker__create_struct_type(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) { struct Checked_Named_Type* other_type;
#line 4091 "bootstrap/stage0/ReCode.code"
    other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4092 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (other_type != NULL) {
#line 4092 "bootstrap/stage0/ReCode.code"
            {
#line 4093 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4094 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__else__1: ;
#line 4095 "bootstrap/stage0/ReCode.code"
        { struct Checked_Struct_Type* struct_type;
#line 4096 "bootstrap/stage0/ReCode.code"
            struct_type = Checked_Struct_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4097 "bootstrap/stage0/ReCode.code"
            Checker__append_type(self, ((struct Checked_Named_Type*) struct_type));
        } if__end__1: ;
    }}

#line 4101 "bootstrap/stage0/ReCode.code"
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) { struct Checked_Struct_Type* struct_type;
#line 4102 "bootstrap/stage0/ReCode.code"
    struct_type = ((struct Checked_Struct_Type*) Checker__find_type(self, parsed_statement->super.name->lexeme));
#line 4103 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->first_member != NULL) {
#line 4103 "bootstrap/stage0/ReCode.code"
            { struct Checked_Struct_Member* last_struct_member; struct Parsed_Struct_Member* parsed_member;
#line 4104 "bootstrap/stage0/ReCode.code"
                last_struct_member = NULL;
#line 4105 "bootstrap/stage0/ReCode.code"
                parsed_member = parsed_statement->first_member;
#line 4106 "bootstrap/stage0/ReCode.code"
                while (parsed_member != NULL) { struct Checked_Struct_Member* struct_member; struct Checked_Type* struct_member_type;
#line 4107 "bootstrap/stage0/ReCode.code"
                    struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
#line 4108 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (struct_member != NULL) {
#line 4108 "bootstrap/stage0/ReCode.code"
                            {
#line 4109 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_member->name->location, String__append_source_location(String__create_from("Struct member declared first here: "), struct_member->location));
#line 4110 "bootstrap/stage0/ReCode.code"
                                abort();
                            } goto if__end__2; } if__end__2: ;
                    }
#line 4112 "bootstrap/stage0/ReCode.code"
                    struct_member_type = Checker__resolve_type(self, parsed_member->type);
#line 4113 "bootstrap/stage0/ReCode.code"
                    struct_member = Checked_Struct_Member__create(parsed_member->name->location, parsed_member->name->lexeme, struct_member_type);
#line 4114 "bootstrap/stage0/ReCode.code"
                    if__start__3: { if (String__equals_cstring(struct_member->name, "super")) {
#line 4114 "bootstrap/stage0/ReCode.code"
                            { struct Checked_Struct_Type* struct_super_type; struct Checked_Struct_Type* other_struct_type;
#line 4115 "bootstrap/stage0/ReCode.code"
                                if__start__4: { if (struct_type->first_member != NULL) {
#line 4115 "bootstrap/stage0/ReCode.code"
                                        {
#line 4116 "bootstrap/stage0/ReCode.code"
                                            Source_Location__error(parsed_member->name->location, String__create_from("Must be the first struct member"));
#line 4117 "bootstrap/stage0/ReCode.code"
                                            abort();
                                        } goto if__end__4; } if__end__4: ;
                                }
#line 4119 "bootstrap/stage0/ReCode.code"
                                if__start__5: { if (struct_member->type->kind != Checked_Type_Kind__STRUCT) {
#line 4119 "bootstrap/stage0/ReCode.code"
                                        {
#line 4120 "bootstrap/stage0/ReCode.code"
                                            Source_Location__error(parsed_member->type->location, String__create_from("Must be a struct"));
#line 4121 "bootstrap/stage0/ReCode.code"
                                            abort();
                                        } goto if__end__5; } if__end__5: ;
                                }
#line 4123 "bootstrap/stage0/ReCode.code"
                                struct_super_type = ((struct Checked_Struct_Type*) struct_member->type);
#line 4124 "bootstrap/stage0/ReCode.code"
                                other_struct_type = struct_super_type;
#line 4125 "bootstrap/stage0/ReCode.code"
                                while (other_struct_type != NULL) {
#line 4126 "bootstrap/stage0/ReCode.code"
                                    if__start__6: { if (other_struct_type == struct_type) {
#line 4126 "bootstrap/stage0/ReCode.code"
                                            {
#line 4127 "bootstrap/stage0/ReCode.code"
                                                Source_Location__error(parsed_member->type->location, String__create_from("Type recursivity"));
#line 4128 "bootstrap/stage0/ReCode.code"
                                                abort();
                                            } goto if__end__6; } if__end__6: ;
                                    }
#line 4130 "bootstrap/stage0/ReCode.code"
                                    other_struct_type = other_struct_type->super_type;
                                }
#line 4132 "bootstrap/stage0/ReCode.code"
                                struct_type->super_type = struct_super_type;
                            } goto if__end__3; } if__end__3: ;
                    }
#line 4134 "bootstrap/stage0/ReCode.code"
                    if__start__7: { if (last_struct_member == NULL) {
#line 4134 "bootstrap/stage0/ReCode.code"
                            {
#line 4135 "bootstrap/stage0/ReCode.code"
                                struct_type->first_member = struct_member;
                            } goto if__end__7; } if__else__7: ;
#line 4136 "bootstrap/stage0/ReCode.code"
                        {
#line 4137 "bootstrap/stage0/ReCode.code"
                            last_struct_member->next_member = struct_member;
                        } if__end__7: ;
                    }
#line 4139 "bootstrap/stage0/ReCode.code"
                    last_struct_member = struct_member;
#line 4140 "bootstrap/stage0/ReCode.code"
                    parsed_member = parsed_member->next_member;
                }
            } goto if__end__1; } if__end__1: ;
    }}

#line 4145 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement) { struct Checked_Expression* object_expression; struct Checked_Expression* value_expression;
#line 4146 "bootstrap/stage0/ReCode.code"
    object_expression = Checker__check_expression(self, parsed_statement->object_expression);
#line 4147 "bootstrap/stage0/ReCode.code"
    value_expression = Checker__check_expression(self, parsed_statement->value_expression);
#line 4148 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(object_expression->type, value_expression->type, value_expression->location);
#line 4149 "bootstrap/stage0/ReCode.code"
    return Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);}

#line 4152 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement) { struct Checker_Context* context;
#line 4153 "bootstrap/stage0/ReCode.code"
    context = Checker_Context__create(self->current_context);
#line 4154 "bootstrap/stage0/ReCode.code"
    self->current_context = context;
#line 4155 "bootstrap/stage0/ReCode.code"
    Checker__check_statements(self, parsed_statement->statements);
#line 4156 "bootstrap/stage0/ReCode.code"
    self->current_context = context->parent;
#line 4157 "bootstrap/stage0/ReCode.code"
    return Checked_Block_Statement__create(parsed_statement->super.location, context, NULL);}

#line 4160 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement) {
#line 4161 "bootstrap/stage0/ReCode.code"
    return Checked_Break_Statement__create(parsed_statement->super.location);}

#line 4164 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement) { struct Checked_Expression* expression;
#line 4165 "bootstrap/stage0/ReCode.code"
    expression = Checker__check_expression(self, parsed_statement->expression);
#line 4166 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(Checked_Type__equals(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__VOID)), expression->type))) {
#line 4166 "bootstrap/stage0/ReCode.code"
            {
            } goto if__end__1; } if__end__1: ;
    }
#line 4169 "bootstrap/stage0/ReCode.code"
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);}

#line 4172 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement) { int16_t labels_count; struct String* wrapper_label; struct String* wrapper_end_label; struct String* then_label; struct String* else_label; struct Checker_Context* wrapper_context; struct Checked_Block_Statement* wrapper_block; struct Checked_Block_Statement* then_block; struct Checker_Context* current_context;
#line 4173 "bootstrap/stage0/ReCode.code"
    labels_count = Counter__next(self->current_context->function_counter);
#line 4174 "bootstrap/stage0/ReCode.code"
    wrapper_label = String__append_i16(String__create_from("if__start__"), labels_count);
#line 4175 "bootstrap/stage0/ReCode.code"
    wrapper_end_label = String__append_i16(String__create_from("if__end__"), labels_count);
#line 4176 "bootstrap/stage0/ReCode.code"
    then_label = String__append_i16(String__create_from("if__then__"), labels_count);
#line 4177 "bootstrap/stage0/ReCode.code"
    else_label = wrapper_end_label;
#line 4178 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->false_statement != NULL) {
#line 4178 "bootstrap/stage0/ReCode.code"
            {
#line 4179 "bootstrap/stage0/ReCode.code"
                else_label = String__append_i16(String__create_from("if__else__"), labels_count);
            } goto if__end__1; } if__end__1: ;
    }
#line 4182 "bootstrap/stage0/ReCode.code"
    wrapper_context = Checker_Context__create(self->current_context);
#line 4183 "bootstrap/stage0/ReCode.code"
    self->current_context = wrapper_context;
#line 4185 "bootstrap/stage0/ReCode.code"
    wrapper_block = Checked_Block_Statement__create(parsed_statement->super.location, wrapper_context, wrapper_label);
#line 4187 "bootstrap/stage0/ReCode.code"
    then_block = Checker__check_if_condition(self, parsed_statement->condition_expression, then_label, else_label);
#line 4189 "bootstrap/stage0/ReCode.code"
    current_context = self->current_context;
#line 4190 "bootstrap/stage0/ReCode.code"
    self->current_context = then_block->context;
#line 4191 "bootstrap/stage0/ReCode.code"
    Checked_Statements__append(then_block->context->statements, Checker__check_statement(self, parsed_statement->true_statement));
#line 4192 "bootstrap/stage0/ReCode.code"
    Checked_Statements__append(then_block->context->statements, ((struct Checked_Statement*) Checked_Goto_Statement__create(NULL, wrapper_end_label)));
#line 4193 "bootstrap/stage0/ReCode.code"
    self->current_context = current_context;
#line 4195 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (parsed_statement->false_statement != NULL) {
#line 4195 "bootstrap/stage0/ReCode.code"
            {
#line 4196 "bootstrap/stage0/ReCode.code"
                Checked_Statements__append(wrapper_block->context->statements, ((struct Checked_Statement*) Checked_Label_Statement__create(NULL, else_label)));
#line 4197 "bootstrap/stage0/ReCode.code"
                Checked_Statements__append(wrapper_block->context->statements, Checker__check_statement(self, parsed_statement->false_statement));
            } goto if__end__2; } if__end__2: ;
    }
#line 4200 "bootstrap/stage0/ReCode.code"
    Checked_Statements__append(wrapper_block->context->statements, ((struct Checked_Statement*) Checked_Label_Statement__create(NULL, wrapper_end_label)));
#line 4202 "bootstrap/stage0/ReCode.code"
    self->current_context = wrapper_context->parent;
#line 4204 "bootstrap/stage0/ReCode.code"
    return ((struct Checked_Statement*) wrapper_block);}

#line 4208 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checker__check_if_condition(struct Checker* self, struct Parsed_Expression* parsed_expression, struct String* then_label, struct String* else_label) { struct Checker_Context* initial_context; struct Checked_Block_Statement* then_block;
#line 4209 "bootstrap/stage0/ReCode.code"
    initial_context = self->current_context;
#line 4210 "bootstrap/stage0/ReCode.code"
    ;
#line 4211 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 4211 "bootstrap/stage0/ReCode.code"
            { struct Parsed_Logic_And_Expression* parsed_binary_expression; struct Checked_Block_Statement* first_expression_block;
#line 4212 "bootstrap/stage0/ReCode.code"
                parsed_binary_expression = ((struct Parsed_Logic_And_Expression*) parsed_expression);
#line 4213 "bootstrap/stage0/ReCode.code"
                first_expression_block = Checker__check_if_condition(self, parsed_binary_expression->super.left_expression, then_label, else_label);
#line 4214 "bootstrap/stage0/ReCode.code"
                self->current_context = first_expression_block->context;
#line 4215 "bootstrap/stage0/ReCode.code"
                then_block = Checker__check_if_condition(self, parsed_binary_expression->super.right_expression, then_label, else_label);
            } goto if__end__1; } if__else__1: ;
#line 4216 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 4216 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Logic_Or_Expression* parsed_binary_expression; struct String* new_then_label; struct Checked_Block_Statement* first_expression_block; struct Checked_Block_Statement* second_expression_block;
#line 4217 "bootstrap/stage0/ReCode.code"
                    parsed_binary_expression = ((struct Parsed_Logic_Or_Expression*) parsed_expression);
#line 4218 "bootstrap/stage0/ReCode.code"
                    new_then_label = String__append_i16(String__append_cstring(String__append_string(String__create(), then_label), "__"), Counter__next(self->current_context->function_counter));
#line 4219 "bootstrap/stage0/ReCode.code"
                    first_expression_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.left_expression)), else_label, new_then_label);
#line 4220 "bootstrap/stage0/ReCode.code"
                    self->current_context = first_expression_block->context;
#line 4221 "bootstrap/stage0/ReCode.code"
                    second_expression_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.right_expression)), else_label, new_then_label);
#line 4222 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(second_expression_block->context->statements, ((struct Checked_Statement*) Checked_Goto_Statement__create(NULL, else_label)));
#line 4223 "bootstrap/stage0/ReCode.code"
                    then_block = Checked_Block_Statement__create(NULL, Checker_Context__create(initial_context), new_then_label);
#line 4224 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(initial_context->statements, ((struct Checked_Statement*) then_block));
                } goto if__end__2; } if__else__2: ;
#line 4225 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parsed_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 4225 "bootstrap/stage0/ReCode.code"
                    {
#line 4226 "bootstrap/stage0/ReCode.code"
                        then_block = Checker__check_if_condition(self, ((struct Parsed_Group_Expression*) parsed_expression)->other_expression, then_label, else_label);
                    } goto if__end__3; } if__else__3: ;
#line 4227 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 4227 "bootstrap/stage0/ReCode.code"
                            {
#line 4228 "bootstrap/stage0/ReCode.code"
                                then_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, ((struct Parsed_Group_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression)->other_expression)), then_label, else_label);
                            } goto if__end__4; } } if__else__4: ;
#line 4229 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__NOT) {
#line 4229 "bootstrap/stage0/ReCode.code"
                                {
#line 4230 "bootstrap/stage0/ReCode.code"
                                    then_block = Checker__check_if_condition(self, ((struct Parsed_Not_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression)->super.other_expression, then_label, else_label);
                                } goto if__end__5; } } if__else__5: ;
#line 4231 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 4231 "bootstrap/stage0/ReCode.code"
                                    { struct Parsed_Logic_Or_Expression* parsed_binary_expression;
#line 4232 "bootstrap/stage0/ReCode.code"
                                        parsed_binary_expression = ((struct Parsed_Logic_Or_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression);
#line 4233 "bootstrap/stage0/ReCode.code"
                                        then_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Logic_And_Expression__create(((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.left_expression)), ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.right_expression)))), then_label, else_label);
                                    } goto if__end__6; } } if__else__6: ;
#line 4234 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (parsed_expression->kind == Parsed_Expression_Kind__NOT) { if (((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 4234 "bootstrap/stage0/ReCode.code"
                                        { struct Parsed_Logic_And_Expression* parsed_binary_expression;
#line 4235 "bootstrap/stage0/ReCode.code"
                                            parsed_binary_expression = ((struct Parsed_Logic_And_Expression*) ((struct Parsed_Not_Expression*) parsed_expression)->super.other_expression);
#line 4236 "bootstrap/stage0/ReCode.code"
                                            then_block = Checker__check_if_condition(self, ((struct Parsed_Expression*) Parsed_Logic_Or_Expression__create(((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.left_expression)), ((struct Parsed_Expression*) Parsed_Not_Expression__create(NULL, parsed_binary_expression->super.right_expression)))), then_label, else_label);
                                        } goto if__end__7; } } if__else__7: ;
#line 4237 "bootstrap/stage0/ReCode.code"
                                { struct Checked_Expression* checked_expression;
#line 4238 "bootstrap/stage0/ReCode.code"
                                    checked_expression = Checker__check_expression(self, parsed_expression);
#line 4239 "bootstrap/stage0/ReCode.code"
                                    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), checked_expression->type, checked_expression->location);
#line 4240 "bootstrap/stage0/ReCode.code"
                                    then_block = Checked_Block_Statement__create(NULL, Checker_Context__create(self->current_context), NULL);
#line 4241 "bootstrap/stage0/ReCode.code"
                                    Checked_Statements__append(self->current_context->statements, ((struct Checked_Statement*) Checked_If_Statement__create(NULL, checked_expression, ((struct Checked_Statement*) then_block), NULL)));
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    } if__end__4: ;
                } if__end__3: ;
            } if__end__2: ;
        } if__end__1: ;
    }
#line 4243 "bootstrap/stage0/ReCode.code"
    self->current_context = initial_context;
#line 4244 "bootstrap/stage0/ReCode.code"
    return then_block;}

#line 4247 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement) { struct Checked_Expression* expression;
#line 4248 "bootstrap/stage0/ReCode.code"
    expression = NULL;
#line 4249 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->expression != NULL) {
#line 4249 "bootstrap/stage0/ReCode.code"
            {
#line 4250 "bootstrap/stage0/ReCode.code"
                expression = Checker__check_expression(self, parsed_statement->expression);
#line 4251 "bootstrap/stage0/ReCode.code"
                Checked_Type__expect_same_type(self->current_context->function_return_type, expression->type, expression->location);
            } goto if__end__1; } if__else__1: ;
#line 4252 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (self->current_context->function_return_type->kind != Checked_Type_Kind__VOID) {
#line 4252 "bootstrap/stage0/ReCode.code"
                {
#line 4253 "bootstrap/stage0/ReCode.code"
                    Source_Location__error(parsed_statement->super.location, String__create_from("Missing expression"));
#line 4254 "bootstrap/stage0/ReCode.code"
                    abort();
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 4256 "bootstrap/stage0/ReCode.code"
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);}

#line 4259 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement) { struct Checked_Type* type; struct Checked_Expression* expression; struct Checked_Variable_Symbol* variable;
#line 4260 "bootstrap/stage0/ReCode.code"
    type = NULL;
#line 4261 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->type != NULL) {
#line 4261 "bootstrap/stage0/ReCode.code"
            {
#line 4262 "bootstrap/stage0/ReCode.code"
                type = Checker__resolve_type(self, parsed_statement->type);
#line 4263 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (type->kind == Checked_Type_Kind__OPAQUE) {
#line 4263 "bootstrap/stage0/ReCode.code"
                        {
#line 4264 "bootstrap/stage0/ReCode.code"
                            Source_Location__error(parsed_statement->super.super.location, String__create_from("Variable cannot have an opaque type"));
#line 4265 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__2; } if__end__2: ;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 4268 "bootstrap/stage0/ReCode.code"
    expression = NULL;
#line 4269 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (parsed_statement->expression != NULL) {
#line 4269 "bootstrap/stage0/ReCode.code"
            {
#line 4270 "bootstrap/stage0/ReCode.code"
                expression = Checker__check_expression(self, parsed_statement->expression);
#line 4271 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (type != NULL) {
#line 4271 "bootstrap/stage0/ReCode.code"
                        {
#line 4272 "bootstrap/stage0/ReCode.code"
                            Checked_Type__expect_same_type(type, expression->type, expression->location);
#line 4273 "bootstrap/stage0/ReCode.code"
                            if__start__5: { if (expression->type->kind != Checked_Type_Kind__NULL) {
#line 4273 "bootstrap/stage0/ReCode.code"
                                    {
#line 4274 "bootstrap/stage0/ReCode.code"
                                        Source_Location__warning(parsed_statement->type->location, String__create_from("Redundant type declaration"));
                                    } goto if__end__5; } if__end__5: ;
                            }
                        } goto if__end__4; } if__else__4: ;
#line 4276 "bootstrap/stage0/ReCode.code"
                    {
#line 4277 "bootstrap/stage0/ReCode.code"
                        type = expression->type;
                    } if__end__4: ;
                }
            } goto if__end__3; } if__end__3: ;
    }
#line 4280 "bootstrap/stage0/ReCode.code"
    if__start__6: { if (!(type == NULL)) { if (!(type->kind == Checked_Type_Kind__NULL)) { goto if__end__6; } } if__then__6__7: {
#line 4280 "bootstrap/stage0/ReCode.code"
            {
#line 4281 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_statement->super.super.location, String__create_from("Unknown variable type"));
#line 4282 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__6; } if__end__6: ;
    }
#line 4284 "bootstrap/stage0/ReCode.code"
    variable = Checked_Variable__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
#line 4285 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->current_context->symbols, ((struct Checked_Symbol*) variable));
#line 4286 "bootstrap/stage0/ReCode.code"
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);}

#line 4289 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement) { struct Checked_Expression* condition_expression; struct Checked_Statement* body_statement;
#line 4290 "bootstrap/stage0/ReCode.code"
    condition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4291 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL)), condition_expression->type, condition_expression->location);
#line 4292 "bootstrap/stage0/ReCode.code"
    body_statement = Checker__check_statement(self, parsed_statement->body_statement);
#line 4293 "bootstrap/stage0/ReCode.code"
    return Checked_While_Statement__create(parsed_statement->super.location, condition_expression, body_statement);}

#line 4296 "bootstrap/stage0/ReCode.code"
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) { struct String* function_name; struct Checked_Type* function_return_type; struct Checked_Function_Parameter* function_first_parameter; struct Parsed_Function_Parameter* parsed_parameter; struct Checked_Function_Type* function_type; struct Checked_Symbol* other_symbol;
#line 4297 "bootstrap/stage0/ReCode.code"
    function_name = parsed_statement->super.name->lexeme;
#line 4298 "bootstrap/stage0/ReCode.code"
    function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 4299 "bootstrap/stage0/ReCode.code"
    function_first_parameter = NULL;
#line 4300 "bootstrap/stage0/ReCode.code"
    parsed_parameter = parsed_statement->first_parameter;
#line 4301 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_parameter != NULL) {
#line 4301 "bootstrap/stage0/ReCode.code"
            { struct Checked_Function_Parameter* function_last_parameter;
#line 4302 "bootstrap/stage0/ReCode.code"
                function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->location, parsed_parameter->name, Checker__resolve_type(self, parsed_parameter->type));
#line 4303 "bootstrap/stage0/ReCode.code"
                function_last_parameter = function_first_parameter;
#line 4304 "bootstrap/stage0/ReCode.code"
                parsed_parameter = parsed_parameter->next_parameter;
#line 4305 "bootstrap/stage0/ReCode.code"
                while (parsed_parameter != NULL) { struct Checked_Function_Parameter* function_parameter;
#line 4306 "bootstrap/stage0/ReCode.code"
                    function_parameter = Checked_Function_Parameter__create(parsed_parameter->location, parsed_parameter->name, Checker__resolve_type(self, parsed_parameter->type));
#line 4307 "bootstrap/stage0/ReCode.code"
                    function_last_parameter->next_parameter = function_parameter;
#line 4308 "bootstrap/stage0/ReCode.code"
                    function_last_parameter = function_parameter;
#line 4309 "bootstrap/stage0/ReCode.code"
                    parsed_parameter = parsed_parameter->next_parameter;
                }
            } goto if__end__1; } if__end__1: ;
    }
#line 4312 "bootstrap/stage0/ReCode.code"
    function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_first_parameter, function_return_type);
#line 4314 "bootstrap/stage0/ReCode.code"
    other_symbol = Checked_Symbols__find_sibling_symbol(self->root_context->symbols, function_name);
#line 4315 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (other_symbol != NULL) {
#line 4315 "bootstrap/stage0/ReCode.code"
            {
#line 4316 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (!(other_symbol->kind != Checked_Symbol_Kind__FUNCTION)) { if (Checked_Type__equals(((struct Checked_Type*) function_type), ((struct Checked_Type*) ((struct Checked_Function_Symbol*) other_symbol)->function_type))) { goto if__else__3; } } if__then__3__4: {
#line 4316 "bootstrap/stage0/ReCode.code"
                        {
#line 4317 "bootstrap/stage0/ReCode.code"
                            TODO("Report overloaded function");
#line 4318 "bootstrap/stage0/ReCode.code"
                            abort();
                        } goto if__end__3; } if__else__3: ;
#line 4319 "bootstrap/stage0/ReCode.code"
                    {
#line 4320 "bootstrap/stage0/ReCode.code"
                        Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Function declared first here: "), other_symbol->location));
#line 4321 "bootstrap/stage0/ReCode.code"
                        abort();
                    } if__end__3: ;
                }
            } goto if__end__2; } if__else__2: ;
#line 4323 "bootstrap/stage0/ReCode.code"
        {
#line 4324 "bootstrap/stage0/ReCode.code"
            Checked_Symbols__append_symbol(self->root_context->symbols, ((struct Checked_Symbol*) Checked_Function_Symbol__create(parsed_statement->super.name->location, function_name, function_type)));
        } if__end__2: ;
    }}

#line 4328 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement) {
#line 4329 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (parsed_statement->kind == Parsed_Statement_Kind__ASSIGNMENT) {
#line 4329 "bootstrap/stage0/ReCode.code"
            {
#line 4330 "bootstrap/stage0/ReCode.code"
                return ((struct Checked_Statement*) Checker__check_assignment_statement(self, ((struct Parsed_Assignment_Statement*) parsed_statement)));
            } goto if__end__1; } if__else__1: ;
#line 4331 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (parsed_statement->kind == Parsed_Statement_Kind__BLOCK) {
#line 4331 "bootstrap/stage0/ReCode.code"
                {
#line 4332 "bootstrap/stage0/ReCode.code"
                    return ((struct Checked_Statement*) Checker__check_block_statement(self, ((struct Parsed_Block_Statement*) parsed_statement)));
                } goto if__end__2; } if__else__2: ;
#line 4333 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (parsed_statement->kind == Parsed_Statement_Kind__BREAK) {
#line 4333 "bootstrap/stage0/ReCode.code"
                    {
#line 4334 "bootstrap/stage0/ReCode.code"
                        return ((struct Checked_Statement*) Checker__check_break_statement(self, ((struct Parsed_Break_Statement*) parsed_statement)));
                    } goto if__end__3; } if__else__3: ;
#line 4335 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (parsed_statement->kind == Parsed_Statement_Kind__EXPRESSION) {
#line 4335 "bootstrap/stage0/ReCode.code"
                        {
#line 4336 "bootstrap/stage0/ReCode.code"
                            return ((struct Checked_Statement*) Checker__check_expression_statement(self, ((struct Parsed_Expression_Statement*) parsed_statement)));
                        } goto if__end__4; } if__else__4: ;
#line 4337 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (parsed_statement->kind == Parsed_Statement_Kind__IF) {
#line 4337 "bootstrap/stage0/ReCode.code"
                            {
#line 4338 "bootstrap/stage0/ReCode.code"
                                return Checker__check_if_statement(self, ((struct Parsed_If_Statement*) parsed_statement));
                            } goto if__end__5; } if__else__5: ;
#line 4339 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (parsed_statement->kind == Parsed_Statement_Kind__RETURN) {
#line 4339 "bootstrap/stage0/ReCode.code"
                                {
#line 4340 "bootstrap/stage0/ReCode.code"
                                    return ((struct Checked_Statement*) Checker__check_return_statement(self, ((struct Parsed_Return_Statement*) parsed_statement)));
                                } goto if__end__6; } if__else__6: ;
#line 4341 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4341 "bootstrap/stage0/ReCode.code"
                                    {
#line 4342 "bootstrap/stage0/ReCode.code"
                                        return ((struct Checked_Statement*) Checker__check_variable_statement(self, ((struct Parsed_Variable_Statement*) parsed_statement)));
                                    } goto if__end__7; } if__else__7: ;
#line 4343 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (parsed_statement->kind == Parsed_Statement_Kind__WHILE) {
#line 4343 "bootstrap/stage0/ReCode.code"
                                        {
#line 4344 "bootstrap/stage0/ReCode.code"
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
#line 4346 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4347 "bootstrap/stage0/ReCode.code"
    abort();}

#line 4350 "bootstrap/stage0/ReCode.code"
void Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements) { struct Parsed_Statement* parsed_statement;
#line 4351 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_statements->first_statement;
#line 4352 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) { struct Checked_Statement* checked_statement;
#line 4353 "bootstrap/stage0/ReCode.code"
        checked_statement = Checker__check_statement(self, parsed_statement);
#line 4354 "bootstrap/stage0/ReCode.code"
        Checked_Statements__append(self->current_context->statements, checked_statement);
#line 4355 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }}

#line 4359 "bootstrap/stage0/ReCode.code"
void Checker__check_function_definition(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) { struct Checked_Symbol* symbol; struct Checked_Function_Symbol* function_symbol; struct Checked_Function_Type* function_type; struct Checker_Context* function_context; struct Checker_Context* context;
#line 4360 "bootstrap/stage0/ReCode.code"
    symbol = Checked_Symbols__find_sibling_symbol(self->root_context->symbols, parsed_statement->super.name->lexeme);
#line 4361 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (!(symbol == NULL)) { if (!(symbol->kind != Checked_Symbol_Kind__FUNCTION)) { goto if__end__1; } } if__then__1__2: {
#line 4361 "bootstrap/stage0/ReCode.code"
            {
#line 4362 "bootstrap/stage0/ReCode.code"
                TODO("Report missing function symbol");
#line 4363 "bootstrap/stage0/ReCode.code"
                abort();
            } goto if__end__1; } if__end__1: ;
    }
#line 4365 "bootstrap/stage0/ReCode.code"
    function_symbol = ((struct Checked_Function_Symbol*) symbol);
#line 4366 "bootstrap/stage0/ReCode.code"
    function_type = function_symbol->function_type;
#line 4368 "bootstrap/stage0/ReCode.code"
    function_context = Checker_Context__create(self->current_context);
#line 4369 "bootstrap/stage0/ReCode.code"
    function_context->function_return_type = function_type->return_type;
#line 4370 "bootstrap/stage0/ReCode.code"
    Counter__reset(function_context->function_counter);
#line 4372 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (function_type->first_parameter != NULL) {
#line 4372 "bootstrap/stage0/ReCode.code"
            { struct Checked_Function_Parameter* parameter;
#line 4374 "bootstrap/stage0/ReCode.code"
                parameter = function_type->first_parameter;
#line 4375 "bootstrap/stage0/ReCode.code"
                while (parameter != NULL) {
#line 4376 "bootstrap/stage0/ReCode.code"
                    Checked_Symbols__append_symbol(function_context->symbols, ((struct Checked_Symbol*) Checked_Function_Parameter_Symbol__create(parameter->location, parameter->name, parameter->type)));
#line 4377 "bootstrap/stage0/ReCode.code"
                    parameter = parameter->next_parameter;
                }
            } goto if__end__3; } if__end__3: ;
    }
#line 4381 "bootstrap/stage0/ReCode.code"
    context = Checker_Context__create(function_context);
#line 4382 "bootstrap/stage0/ReCode.code"
    self->current_context = context;
#line 4383 "bootstrap/stage0/ReCode.code"
    Checker__check_statements(self, parsed_statement->statements);
#line 4384 "bootstrap/stage0/ReCode.code"
    self->current_context = function_context->parent;
#line 4386 "bootstrap/stage0/ReCode.code"
    function_symbol->checked_statements = context->statements;}

#line 4389 "bootstrap/stage0/ReCode.code"
struct Checked_Source* Checker__check_source(struct Checker* self, struct Parsed_Source* parsed_source) { struct Parsed_Statement* parsed_statement; struct Checked_Source* checked_source;
#line 4390 "bootstrap/stage0/ReCode.code"
    ;
#line 4393 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4394 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) { struct Checked_Statement* checked_statement;
#line 4395 "bootstrap/stage0/ReCode.code"
        checked_statement = NULL;
#line 4396 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4396 "bootstrap/stage0/ReCode.code"
                {
                } goto if__end__1; } if__else__1: ;
#line 4398 "bootstrap/stage0/ReCode.code"
            if__start__2: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4398 "bootstrap/stage0/ReCode.code"
                    {
                    } goto if__end__2; } if__else__2: ;
#line 4400 "bootstrap/stage0/ReCode.code"
                if__start__3: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4400 "bootstrap/stage0/ReCode.code"
                        {
#line 4401 "bootstrap/stage0/ReCode.code"
                            Checker__create_struct_type(self, ((struct Parsed_Struct_Statement*) parsed_statement));
                        } goto if__end__3; } if__else__3: ;
#line 4402 "bootstrap/stage0/ReCode.code"
                    if__start__4: { if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4402 "bootstrap/stage0/ReCode.code"
                            {
#line 4403 "bootstrap/stage0/ReCode.code"
                                Checker__create_opaque_type(self, ((struct Parsed_Opaque_Type_Statement*) parsed_statement));
                            } goto if__end__4; } if__else__4: ;
#line 4404 "bootstrap/stage0/ReCode.code"
                        if__start__5: { if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4404 "bootstrap/stage0/ReCode.code"
                                {
#line 4405 "bootstrap/stage0/ReCode.code"
                                    Checker__check_enum_statement(self, ((struct Parsed_Enum_Statement*) parsed_statement));
                                } goto if__end__5; } if__else__5: ;
#line 4406 "bootstrap/stage0/ReCode.code"
                            {
#line 4407 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4408 "bootstrap/stage0/ReCode.code"
                                abort();
                            } if__end__5: ;
                        } if__end__4: ;
                    } if__end__3: ;
                } if__end__2: ;
            } if__end__1: ;
        }
#line 4410 "bootstrap/stage0/ReCode.code"
        if__start__6: { if (checked_statement != NULL) {
#line 4410 "bootstrap/stage0/ReCode.code"
                {
#line 4411 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(self->current_context->statements, checked_statement);
                } goto if__end__6; } if__end__6: ;
        }
#line 4413 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4417 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4418 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4419 "bootstrap/stage0/ReCode.code"
        if__start__7: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4419 "bootstrap/stage0/ReCode.code"
                {
#line 4420 "bootstrap/stage0/ReCode.code"
                    Checker__check_struct_statement(self, ((struct Parsed_Struct_Statement*) parsed_statement));
                } goto if__end__7; } if__end__7: ;
        }
#line 4422 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4426 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4427 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) { struct Checked_Statement* checked_statement;
#line 4428 "bootstrap/stage0/ReCode.code"
        checked_statement = NULL;
#line 4429 "bootstrap/stage0/ReCode.code"
        if__start__8: { if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4429 "bootstrap/stage0/ReCode.code"
                {
#line 4430 "bootstrap/stage0/ReCode.code"
                    Checker__check_function_declaration(self, ((struct Parsed_Function_Statement*) parsed_statement));
                } goto if__end__8; } if__else__8: ;
#line 4431 "bootstrap/stage0/ReCode.code"
            if__start__9: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4431 "bootstrap/stage0/ReCode.code"
                    {
#line 4432 "bootstrap/stage0/ReCode.code"
                        checked_statement = ((struct Checked_Statement*) Checker__check_variable_statement(self, ((struct Parsed_Variable_Statement*) parsed_statement)));
                    } goto if__end__9; } if__else__9: ;
#line 4433 "bootstrap/stage0/ReCode.code"
                if__start__10: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4433 "bootstrap/stage0/ReCode.code"
                        {
                        } goto if__end__10; } if__else__10: ;
#line 4435 "bootstrap/stage0/ReCode.code"
                    if__start__11: { if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4435 "bootstrap/stage0/ReCode.code"
                            {
                            } goto if__end__11; } if__else__11: ;
#line 4437 "bootstrap/stage0/ReCode.code"
                        if__start__12: { if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4437 "bootstrap/stage0/ReCode.code"
                                {
                                } goto if__end__12; } if__else__12: ;
#line 4439 "bootstrap/stage0/ReCode.code"
                            {
#line 4440 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4441 "bootstrap/stage0/ReCode.code"
                                abort();
                            } if__end__12: ;
                        } if__end__11: ;
                    } if__end__10: ;
                } if__end__9: ;
            } if__end__8: ;
        }
#line 4443 "bootstrap/stage0/ReCode.code"
        if__start__13: { if (checked_statement != NULL) {
#line 4443 "bootstrap/stage0/ReCode.code"
                {
#line 4444 "bootstrap/stage0/ReCode.code"
                    Checked_Statements__append(self->current_context->statements, checked_statement);
                } goto if__end__13; } if__end__13: ;
        }
#line 4446 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4450 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4451 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4452 "bootstrap/stage0/ReCode.code"
        if__start__14: { if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4452 "bootstrap/stage0/ReCode.code"
                { struct Parsed_Function_Statement* function_statement;
#line 4453 "bootstrap/stage0/ReCode.code"
                    function_statement = ((struct Parsed_Function_Statement*) parsed_statement);
#line 4454 "bootstrap/stage0/ReCode.code"
                    if__start__15: { if (function_statement->statements != NULL) {
#line 4454 "bootstrap/stage0/ReCode.code"
                            {
#line 4455 "bootstrap/stage0/ReCode.code"
                                Checker__check_function_definition(self, function_statement);
                            } goto if__end__15; } if__end__15: ;
                    }
                } goto if__end__14; } if__else__14: ;
#line 4457 "bootstrap/stage0/ReCode.code"
            if__start__16: { if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4457 "bootstrap/stage0/ReCode.code"
                    {
                    } goto if__end__16; } if__else__16: ;
#line 4459 "bootstrap/stage0/ReCode.code"
                if__start__17: { if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4459 "bootstrap/stage0/ReCode.code"
                        {
                        } goto if__end__17; } if__else__17: ;
#line 4461 "bootstrap/stage0/ReCode.code"
                    if__start__18: { if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4461 "bootstrap/stage0/ReCode.code"
                            {
                            } goto if__end__18; } if__else__18: ;
#line 4463 "bootstrap/stage0/ReCode.code"
                        if__start__19: { if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4463 "bootstrap/stage0/ReCode.code"
                                {
                                } goto if__end__19; } if__else__19: ;
#line 4465 "bootstrap/stage0/ReCode.code"
                            {
#line 4466 "bootstrap/stage0/ReCode.code"
                                Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4467 "bootstrap/stage0/ReCode.code"
                                abort();
                            } if__end__19: ;
                        } if__end__18: ;
                    } if__end__17: ;
                } if__end__16: ;
            } if__end__14: ;
        }
#line 4469 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4472 "bootstrap/stage0/ReCode.code"
    checked_source = ((struct Checked_Source*) malloc(sizeof(struct Checked_Source)));
#line 4473 "bootstrap/stage0/ReCode.code"
    checked_source->first_symbol = self->current_context->symbols->first_symbol;
#line 4474 "bootstrap/stage0/ReCode.code"
    checked_source->statements = self->current_context->statements;
#line 4475 "bootstrap/stage0/ReCode.code"
    return checked_source;}

#line 4478 "bootstrap/stage0/ReCode.code"
struct Checked_Source* check(struct Parsed_Source* parsed_source) { struct Checker* type_checker;
#line 4479 "bootstrap/stage0/ReCode.code"
    type_checker = Checker__create();
#line 4481 "bootstrap/stage0/ReCode.code"
    return Checker__check_source(type_checker, parsed_source);}

#line 4493 "bootstrap/stage0/ReCode.code"
void Generator__write_source_location(struct Generator* self, struct Source_Location* location) {
#line 4494 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (location != NULL) {
#line 4494 "bootstrap/stage0/ReCode.code"
            {
#line 4495 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "#line ");
#line 4496 "bootstrap/stage0/ReCode.code"
                File__write_i32(self->file, ((int32_t) location->line));
#line 4497 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, " \"");
#line 4498 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, location->source->path);
#line 4499 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "\"\n");
            } goto if__end__1; } if__end__1: ;
    }}

#line 4503 "bootstrap/stage0/ReCode.code"
void Generator__generate_add_expression(struct Generator* self, struct Checked_Add_Expression* expression) {
#line 4504 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4505 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " + ");
#line 4506 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4509 "bootstrap/stage0/ReCode.code"
void Generator__generate_address_of_expression(struct Generator* self, struct Checked_Address_Of_Expression* expression) {
#line 4510 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "&");
#line 4511 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);}

#line 4514 "bootstrap/stage0/ReCode.code"
void Generator__generate_array_access_expression(struct Generator* self, struct Checked_Array_Access_Expression* expression) {
#line 4515 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->array_expression);
#line 4516 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "[");
#line 4517 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->index_expression);
#line 4518 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "]");}

#line 4521 "bootstrap/stage0/ReCode.code"
void Generator__generate_bool_expression(struct Generator* self, struct Checked_Bool_Expression* expression) {
#line 4522 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (expression->value) {
#line 4522 "bootstrap/stage0/ReCode.code"
            {
#line 4523 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "true");
            } goto if__end__1; } if__else__1: ;
#line 4524 "bootstrap/stage0/ReCode.code"
        {
#line 4525 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, "false");
        } if__end__1: ;
    }}

#line 4529 "bootstrap/stage0/ReCode.code"
void Generator__generate_call_expression(struct Generator* self, struct Checked_Call_Expression* expression) { struct Checked_Call_Argument* argument;
#line 4530 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->callee_expression);
#line 4531 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4532 "bootstrap/stage0/ReCode.code"
    argument = expression->first_argument;
#line 4533 "bootstrap/stage0/ReCode.code"
    while (argument != NULL) {
#line 4534 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, argument->expression);
#line 4535 "bootstrap/stage0/ReCode.code"
        argument = argument->next_argument;
#line 4536 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (argument != NULL) {
#line 4536 "bootstrap/stage0/ReCode.code"
                {
#line 4537 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self->file, ", ");
                } goto if__end__1; } if__end__1: ;
        }
    }
#line 4540 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");}

#line 4543 "bootstrap/stage0/ReCode.code"
void Generator__generate_cast_expression(struct Generator* self, struct Checked_Cast_Expression* expression) {
#line 4544 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "((");
#line 4545 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->super.type);
#line 4546 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4547 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
#line 4548 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ')');}

#line 4551 "bootstrap/stage0/ReCode.code"
void File__write_octal_escaped_char(struct File* stream, char value) {
#line 4552 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, '\\');
#line 4553 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (value > ((char) 64)) {
#line 4553 "bootstrap/stage0/ReCode.code"
            {
#line 4554 "bootstrap/stage0/ReCode.code"
                File__write_char(stream, value / ((char) 64) % ((char) 8) + '0');
            } goto if__end__1; } if__end__1: ;
    }
#line 4556 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (value > ((char) 8)) {
#line 4556 "bootstrap/stage0/ReCode.code"
            {
#line 4557 "bootstrap/stage0/ReCode.code"
                File__write_char(stream, value / ((char) 8) % ((char) 8) + '0');
            } goto if__end__2; } if__end__2: ;
    }
#line 4559 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, value % ((char) 8) + '0');}

#line 4562 "bootstrap/stage0/ReCode.code"
void File__write_escaped_char(struct File* stream, char ch) {
#line 4563 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (ch < ((char) 32)) {
#line 4563 "bootstrap/stage0/ReCode.code"
            {
#line 4564 "bootstrap/stage0/ReCode.code"
                if__start__2: { if (ch == '\n') {
#line 4564 "bootstrap/stage0/ReCode.code"
                        {
#line 4565 "bootstrap/stage0/ReCode.code"
                            File__write_cstring(stream, "\\n");
                        } goto if__end__2; } if__else__2: ;
#line 4566 "bootstrap/stage0/ReCode.code"
                    if__start__3: { if (ch == '\t') {
#line 4566 "bootstrap/stage0/ReCode.code"
                            {
#line 4567 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(stream, "\\t");
                            } goto if__end__3; } if__else__3: ;
#line 4568 "bootstrap/stage0/ReCode.code"
                        {
#line 4569 "bootstrap/stage0/ReCode.code"
                            File__write_octal_escaped_char(stream, ch);
                        } if__end__3: ;
                    } if__end__2: ;
                }
            } goto if__end__1; } if__else__1: ;
#line 4571 "bootstrap/stage0/ReCode.code"
        if__start__4: { if (ch < ((char) 127)) {
#line 4571 "bootstrap/stage0/ReCode.code"
                {
#line 4572 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (ch == '\"') {
#line 4572 "bootstrap/stage0/ReCode.code"
                            {
#line 4573 "bootstrap/stage0/ReCode.code"
                                File__write_cstring(stream, "\\\"");
                            } goto if__end__5; } if__else__5: ;
#line 4574 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (ch == '\'') {
#line 4574 "bootstrap/stage0/ReCode.code"
                                {
#line 4575 "bootstrap/stage0/ReCode.code"
                                    File__write_cstring(stream, "\\\'");
                                } goto if__end__6; } if__else__6: ;
#line 4576 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (ch == '\\') {
#line 4576 "bootstrap/stage0/ReCode.code"
                                    {
#line 4577 "bootstrap/stage0/ReCode.code"
                                        File__write_cstring(stream, "\\\\");
                                    } goto if__end__7; } if__else__7: ;
#line 4578 "bootstrap/stage0/ReCode.code"
                                {
#line 4579 "bootstrap/stage0/ReCode.code"
                                    File__write_char(stream, ch);
                                } if__end__7: ;
                            } if__end__6: ;
                        } if__end__5: ;
                    }
                } goto if__end__4; } if__else__4: ;
#line 4581 "bootstrap/stage0/ReCode.code"
            {
#line 4582 "bootstrap/stage0/ReCode.code"
                File__write_octal_escaped_char(stream, ch);
            } if__end__4: ;
        } if__end__1: ;
    }}

#line 4586 "bootstrap/stage0/ReCode.code"
void Generator__generate_character_expression(struct Generator* self, struct Checked_Character_Expression* expression) {
#line 4587 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');
#line 4588 "bootstrap/stage0/ReCode.code"
    File__write_escaped_char(self->file, expression->value);
#line 4589 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');}

#line 4592 "bootstrap/stage0/ReCode.code"
void Generator__generate_dereference_expression(struct Generator* self, struct Checked_Dereference_Expression* expression) {
#line 4593 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "*(");
#line 4594 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->value_expression);
#line 4595 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ')');}

#line 4598 "bootstrap/stage0/ReCode.code"
void Generator__generate_divide_expression(struct Generator* self, struct Checked_Divide_Expression* expression) {
#line 4599 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4600 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " / ");
#line 4601 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4604 "bootstrap/stage0/ReCode.code"
void Generator__generate_equals_expression(struct Generator* self, struct Checked_Equals_Expression* expression) {
#line 4605 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4606 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " == ");
#line 4607 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4610 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_expression(struct Generator* self, struct Checked_Greater_Expression* expression) {
#line 4611 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4612 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " > ");
#line 4613 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4616 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_or_equals_expression(struct Generator* self, struct Checked_Greater_Or_Equals_Expression* expression) {
#line 4617 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4618 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " >= ");
#line 4619 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4622 "bootstrap/stage0/ReCode.code"
void Generator__generate_group_expression(struct Generator* self, struct Checked_Group_Expression* expression) {
#line 4623 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4624 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
#line 4625 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");}

#line 4628 "bootstrap/stage0/ReCode.code"
void Generator__generate_integer_expression(struct Generator* self, struct Checked_Integer_Expression* expression) {
#line 4629 "bootstrap/stage0/ReCode.code"
    File__write_u64(self->file, expression->value);}

#line 4632 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_expression(struct Generator* self, struct Checked_Less_Expression* expression) {
#line 4633 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4634 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " < ");
#line 4635 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4638 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_or_equals_expression(struct Generator* self, struct Checked_Less_Or_Equals_Expression* expression) {
#line 4639 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4640 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " <= ");
#line 4641 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4644 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_and_expression(struct Generator* self, struct Checked_Logic_And_Expression* expression) {
#line 4645 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4646 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " && ");
#line 4647 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4650 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_or_expression(struct Generator* self, struct Checked_Logic_Or_Expression* expression) {
#line 4651 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4652 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " || ");
#line 4653 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4656 "bootstrap/stage0/ReCode.code"
void Generator__generate_member_access_expression(struct Generator* self, struct Checked_Member_Access_Expression* expression) {
#line 4657 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->object_expression);
#line 4658 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (expression->object_expression->type->kind == Checked_Type_Kind__POINTER) {
#line 4658 "bootstrap/stage0/ReCode.code"
            {
#line 4659 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "->");
            } goto if__end__1; } if__else__1: ;
#line 4660 "bootstrap/stage0/ReCode.code"
        {
#line 4661 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, ".");
        } if__end__1: ;
    }
#line 4663 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->member->name);}

#line 4666 "bootstrap/stage0/ReCode.code"
void Generator__generate_minus_expression(struct Generator* self, struct Checked_Minus_Expression* expression) {
#line 4667 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "-");
#line 4668 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);}

#line 4671 "bootstrap/stage0/ReCode.code"
void Generator__generate_modulo_expression(struct Generator* self, struct Checked_Modulo_Expression* expression) {
#line 4672 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4673 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " % ");
#line 4674 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4677 "bootstrap/stage0/ReCode.code"
void Generator__generate_multiply_expression(struct Generator* self, struct Checked_Multiply_Expression* expression) {
#line 4678 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4679 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " * ");
#line 4680 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4683 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_expression(struct Generator* self, struct Checked_Not_Expression* expression) {
#line 4684 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "!(");
#line 4685 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
#line 4686 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ')');}

#line 4689 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_equals_expression(struct Generator* self, struct Checked_Not_Equals_Expression* expression) {
#line 4690 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4691 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " != ");
#line 4692 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4695 "bootstrap/stage0/ReCode.code"
void Generator__generate_null_expression(struct Generator* self, struct Checked_Null_Expression* expression) {
#line 4696 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "NULL");}

#line 4699 "bootstrap/stage0/ReCode.code"
void Generator__generate_sizeof_expression(struct Generator* self, struct Checked_Sizeof_Expression* expression) {
#line 4700 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "sizeof(");
#line 4701 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->sized_type);
#line 4702 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");}

#line 4705 "bootstrap/stage0/ReCode.code"
void Generator__generate_string_expression(struct Generator* self, struct Checked_String_Expression* expression) { size_t index;
#line 4706 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');
#line 4707 "bootstrap/stage0/ReCode.code"
    index = ((size_t) 0);
#line 4708 "bootstrap/stage0/ReCode.code"
    while (index < expression->value->length) {
#line 4709 "bootstrap/stage0/ReCode.code"
        File__write_escaped_char(self->file, expression->value->data[index]);
#line 4710 "bootstrap/stage0/ReCode.code"
        index = index + ((size_t) 1);
    }
#line 4712 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');}

#line 4715 "bootstrap/stage0/ReCode.code"
void Generator__generate_substract_expression(struct Generator* self, struct Checked_Substract_Expression* expression) {
#line 4716 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4717 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " - ");
#line 4718 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);}

#line 4721 "bootstrap/stage0/ReCode.code"
void Generator__generate_symbol_expression(struct Generator* self, struct Checked_Symbol_Expression* expression) {
#line 4722 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->symbol->name);}

#line 4725 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression(struct Generator* self, struct Checked_Expression* expression) {
#line 4726 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (expression->kind == Checked_Expression_Kind__ADD) {
#line 4726 "bootstrap/stage0/ReCode.code"
            {
#line 4727 "bootstrap/stage0/ReCode.code"
                Generator__generate_add_expression(self, ((struct Checked_Add_Expression*) expression));
            } goto if__end__1; } if__else__1: ;
#line 4728 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (expression->kind == Checked_Expression_Kind__ADDRESS_OF) {
#line 4728 "bootstrap/stage0/ReCode.code"
                {
#line 4729 "bootstrap/stage0/ReCode.code"
                    Generator__generate_address_of_expression(self, ((struct Checked_Address_Of_Expression*) expression));
                } goto if__end__2; } if__else__2: ;
#line 4730 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (expression->kind == Checked_Expression_Kind__ARRAY_ACCESS) {
#line 4730 "bootstrap/stage0/ReCode.code"
                    {
#line 4731 "bootstrap/stage0/ReCode.code"
                        Generator__generate_array_access_expression(self, ((struct Checked_Array_Access_Expression*) expression));
                    } goto if__end__3; } if__else__3: ;
#line 4732 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (expression->kind == Checked_Expression_Kind__BOOL) {
#line 4732 "bootstrap/stage0/ReCode.code"
                        {
#line 4733 "bootstrap/stage0/ReCode.code"
                            Generator__generate_bool_expression(self, ((struct Checked_Bool_Expression*) expression));
                        } goto if__end__4; } if__else__4: ;
#line 4734 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (expression->kind == Checked_Expression_Kind__CALL) {
#line 4734 "bootstrap/stage0/ReCode.code"
                            {
#line 4735 "bootstrap/stage0/ReCode.code"
                                Generator__generate_call_expression(self, ((struct Checked_Call_Expression*) expression));
                            } goto if__end__5; } if__else__5: ;
#line 4736 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (expression->kind == Checked_Expression_Kind__CAST) {
#line 4736 "bootstrap/stage0/ReCode.code"
                                {
#line 4737 "bootstrap/stage0/ReCode.code"
                                    Generator__generate_cast_expression(self, ((struct Checked_Cast_Expression*) expression));
                                } goto if__end__6; } if__else__6: ;
#line 4738 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (expression->kind == Checked_Expression_Kind__CHARACTER) {
#line 4738 "bootstrap/stage0/ReCode.code"
                                    {
#line 4739 "bootstrap/stage0/ReCode.code"
                                        Generator__generate_character_expression(self, ((struct Checked_Character_Expression*) expression));
                                    } goto if__end__7; } if__else__7: ;
#line 4740 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (expression->kind == Checked_Expression_Kind__DEREFERENCE) {
#line 4740 "bootstrap/stage0/ReCode.code"
                                        {
#line 4741 "bootstrap/stage0/ReCode.code"
                                            Generator__generate_dereference_expression(self, ((struct Checked_Dereference_Expression*) expression));
                                        } goto if__end__8; } if__else__8: ;
#line 4742 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (expression->kind == Checked_Expression_Kind__DIVIDE) {
#line 4742 "bootstrap/stage0/ReCode.code"
                                            {
#line 4743 "bootstrap/stage0/ReCode.code"
                                                Generator__generate_divide_expression(self, ((struct Checked_Divide_Expression*) expression));
                                            } goto if__end__9; } if__else__9: ;
#line 4744 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (expression->kind == Checked_Expression_Kind__EQUALS) {
#line 4744 "bootstrap/stage0/ReCode.code"
                                                {
#line 4745 "bootstrap/stage0/ReCode.code"
                                                    Generator__generate_equals_expression(self, ((struct Checked_Equals_Expression*) expression));
                                                } goto if__end__10; } if__else__10: ;
#line 4746 "bootstrap/stage0/ReCode.code"
                                            if__start__11: { if (expression->kind == Checked_Expression_Kind__GREATER) {
#line 4746 "bootstrap/stage0/ReCode.code"
                                                    {
#line 4747 "bootstrap/stage0/ReCode.code"
                                                        Generator__generate_greater_expression(self, ((struct Checked_Greater_Expression*) expression));
                                                    } goto if__end__11; } if__else__11: ;
#line 4748 "bootstrap/stage0/ReCode.code"
                                                if__start__12: { if (expression->kind == Checked_Expression_Kind__GREATER_OR_EQUALS) {
#line 4748 "bootstrap/stage0/ReCode.code"
                                                        {
#line 4749 "bootstrap/stage0/ReCode.code"
                                                            Generator__generate_greater_or_equals_expression(self, ((struct Checked_Greater_Or_Equals_Expression*) expression));
                                                        } goto if__end__12; } if__else__12: ;
#line 4750 "bootstrap/stage0/ReCode.code"
                                                    if__start__13: { if (expression->kind == Checked_Expression_Kind__GROUP) {
#line 4750 "bootstrap/stage0/ReCode.code"
                                                            {
#line 4751 "bootstrap/stage0/ReCode.code"
                                                                Generator__generate_group_expression(self, ((struct Checked_Group_Expression*) expression));
                                                            } goto if__end__13; } if__else__13: ;
#line 4752 "bootstrap/stage0/ReCode.code"
                                                        if__start__14: { if (expression->kind == Checked_Expression_Kind__INTEGER) {
#line 4752 "bootstrap/stage0/ReCode.code"
                                                                {
#line 4753 "bootstrap/stage0/ReCode.code"
                                                                    Generator__generate_integer_expression(self, ((struct Checked_Integer_Expression*) expression));
                                                                } goto if__end__14; } if__else__14: ;
#line 4754 "bootstrap/stage0/ReCode.code"
                                                            if__start__15: { if (expression->kind == Checked_Expression_Kind__LESS) {
#line 4754 "bootstrap/stage0/ReCode.code"
                                                                    {
#line 4755 "bootstrap/stage0/ReCode.code"
                                                                        Generator__generate_less_expression(self, ((struct Checked_Less_Expression*) expression));
                                                                    } goto if__end__15; } if__else__15: ;
#line 4756 "bootstrap/stage0/ReCode.code"
                                                                if__start__16: { if (expression->kind == Checked_Expression_Kind__LESS_OR_EQUALS) {
#line 4756 "bootstrap/stage0/ReCode.code"
                                                                        {
#line 4757 "bootstrap/stage0/ReCode.code"
                                                                            Generator__generate_less_or_equals_expression(self, ((struct Checked_Less_Or_Equals_Expression*) expression));
                                                                        } goto if__end__16; } if__else__16: ;
#line 4758 "bootstrap/stage0/ReCode.code"
                                                                    if__start__17: { if (expression->kind == Checked_Expression_Kind__LOGIC_AND) {
#line 4758 "bootstrap/stage0/ReCode.code"
                                                                            {
#line 4759 "bootstrap/stage0/ReCode.code"
                                                                                Generator__generate_logic_and_expression(self, ((struct Checked_Logic_And_Expression*) expression));
                                                                            } goto if__end__17; } if__else__17: ;
#line 4760 "bootstrap/stage0/ReCode.code"
                                                                        if__start__18: { if (expression->kind == Checked_Expression_Kind__LOGIC_OR) {
#line 4760 "bootstrap/stage0/ReCode.code"
                                                                                {
#line 4761 "bootstrap/stage0/ReCode.code"
                                                                                    Generator__generate_logic_or_expression(self, ((struct Checked_Logic_Or_Expression*) expression));
                                                                                } goto if__end__18; } if__else__18: ;
#line 4762 "bootstrap/stage0/ReCode.code"
                                                                            if__start__19: { if (expression->kind == Checked_Expression_Kind__MEMBER_ACCESS) {
#line 4762 "bootstrap/stage0/ReCode.code"
                                                                                    {
#line 4763 "bootstrap/stage0/ReCode.code"
                                                                                        Generator__generate_member_access_expression(self, ((struct Checked_Member_Access_Expression*) expression));
                                                                                    } goto if__end__19; } if__else__19: ;
#line 4764 "bootstrap/stage0/ReCode.code"
                                                                                if__start__20: { if (expression->kind == Checked_Expression_Kind__MINUS) {
#line 4764 "bootstrap/stage0/ReCode.code"
                                                                                        {
#line 4765 "bootstrap/stage0/ReCode.code"
                                                                                            Generator__generate_minus_expression(self, ((struct Checked_Minus_Expression*) expression));
                                                                                        } goto if__end__20; } if__else__20: ;
#line 4766 "bootstrap/stage0/ReCode.code"
                                                                                    if__start__21: { if (expression->kind == Checked_Expression_Kind__MODULO) {
#line 4766 "bootstrap/stage0/ReCode.code"
                                                                                            {
#line 4767 "bootstrap/stage0/ReCode.code"
                                                                                                Generator__generate_modulo_expression(self, ((struct Checked_Modulo_Expression*) expression));
                                                                                            } goto if__end__21; } if__else__21: ;
#line 4768 "bootstrap/stage0/ReCode.code"
                                                                                        if__start__22: { if (expression->kind == Checked_Expression_Kind__MULTIPLY) {
#line 4768 "bootstrap/stage0/ReCode.code"
                                                                                                {
#line 4769 "bootstrap/stage0/ReCode.code"
                                                                                                    Generator__generate_multiply_expression(self, ((struct Checked_Multiply_Expression*) expression));
                                                                                                } goto if__end__22; } if__else__22: ;
#line 4770 "bootstrap/stage0/ReCode.code"
                                                                                            if__start__23: { if (expression->kind == Checked_Expression_Kind__NOT) {
#line 4770 "bootstrap/stage0/ReCode.code"
                                                                                                    {
#line 4771 "bootstrap/stage0/ReCode.code"
                                                                                                        Generator__generate_not_expression(self, ((struct Checked_Not_Expression*) expression));
                                                                                                    } goto if__end__23; } if__else__23: ;
#line 4772 "bootstrap/stage0/ReCode.code"
                                                                                                if__start__24: { if (expression->kind == Checked_Expression_Kind__NOT_EQUALS) {
#line 4772 "bootstrap/stage0/ReCode.code"
                                                                                                        {
#line 4773 "bootstrap/stage0/ReCode.code"
                                                                                                            Generator__generate_not_equals_expression(self, ((struct Checked_Not_Equals_Expression*) expression));
                                                                                                        } goto if__end__24; } if__else__24: ;
#line 4774 "bootstrap/stage0/ReCode.code"
                                                                                                    if__start__25: { if (expression->kind == Checked_Expression_Kind__NULL) {
#line 4774 "bootstrap/stage0/ReCode.code"
                                                                                                            {
#line 4775 "bootstrap/stage0/ReCode.code"
                                                                                                                Generator__generate_null_expression(self, ((struct Checked_Null_Expression*) expression));
                                                                                                            } goto if__end__25; } if__else__25: ;
#line 4776 "bootstrap/stage0/ReCode.code"
                                                                                                        if__start__26: { if (expression->kind == Checked_Expression_Kind__SIZEOF) {
#line 4776 "bootstrap/stage0/ReCode.code"
                                                                                                                {
#line 4777 "bootstrap/stage0/ReCode.code"
                                                                                                                    Generator__generate_sizeof_expression(self, ((struct Checked_Sizeof_Expression*) expression));
                                                                                                                } goto if__end__26; } if__else__26: ;
#line 4778 "bootstrap/stage0/ReCode.code"
                                                                                                            if__start__27: { if (expression->kind == Checked_Expression_Kind__STRING) {
#line 4778 "bootstrap/stage0/ReCode.code"
                                                                                                                    {
#line 4779 "bootstrap/stage0/ReCode.code"
                                                                                                                        Generator__generate_string_expression(self, ((struct Checked_String_Expression*) expression));
                                                                                                                    } goto if__end__27; } if__else__27: ;
#line 4780 "bootstrap/stage0/ReCode.code"
                                                                                                                if__start__28: { if (expression->kind == Checked_Expression_Kind__SUBSTRACT) {
#line 4780 "bootstrap/stage0/ReCode.code"
                                                                                                                        {
#line 4781 "bootstrap/stage0/ReCode.code"
                                                                                                                            Generator__generate_substract_expression(self, ((struct Checked_Substract_Expression*) expression));
                                                                                                                        } goto if__end__28; } if__else__28: ;
#line 4782 "bootstrap/stage0/ReCode.code"
                                                                                                                    if__start__29: { if (expression->kind == Checked_Expression_Kind__SYMBOL) {
#line 4782 "bootstrap/stage0/ReCode.code"
                                                                                                                            {
#line 4783 "bootstrap/stage0/ReCode.code"
                                                                                                                                Generator__generate_symbol_expression(self, ((struct Checked_Symbol_Expression*) expression));
                                                                                                                            } goto if__end__29; } if__else__29: ;
#line 4784 "bootstrap/stage0/ReCode.code"
                                                                                                                        {
#line 4785 "bootstrap/stage0/ReCode.code"
                                                                                                                            Source_Location__error(expression->location, String__create_from("Unsupported expression"));
#line 4786 "bootstrap/stage0/ReCode.code"
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

#line 4790 "bootstrap/stage0/ReCode.code"
void Generator__write_identation(struct Generator* self) { uint16_t identation;
#line 4791 "bootstrap/stage0/ReCode.code"
    identation = self->identation;
#line 4792 "bootstrap/stage0/ReCode.code"
    while (identation > ((uint16_t) 0)) {
#line 4793 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "    ");
#line 4794 "bootstrap/stage0/ReCode.code"
        identation = identation - ((uint16_t) 1);
    }}

#line 4798 "bootstrap/stage0/ReCode.code"
void Generator__generate_assignment_statement(struct Generator* self, struct Checked_Assignment_Statement* statement) {
#line 4799 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->object_expression);
#line 4800 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " = ");
#line 4801 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->value_expression);
#line 4802 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4805 "bootstrap/stage0/ReCode.code"
void Generator__generate_block_statement(struct Generator* self, struct Checked_Block_Statement* statement) {
#line 4806 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->label != NULL) {
#line 4806 "bootstrap/stage0/ReCode.code"
            {
#line 4807 "bootstrap/stage0/ReCode.code"
                File__write_string(self->file, statement->label);
#line 4808 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, ": ");
            } goto if__end__1; } if__end__1: ;
    }
#line 4810 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '{');
#line 4811 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, statement->context->statements);
#line 4812 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (statement->super.location != NULL) {
#line 4812 "bootstrap/stage0/ReCode.code"
            {
#line 4813 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, '\n');
#line 4814 "bootstrap/stage0/ReCode.code"
                Generator__write_identation(self);
#line 4815 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, '}');
            } goto if__end__2; } if__else__2: ;
#line 4816 "bootstrap/stage0/ReCode.code"
        {
#line 4817 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, " }");
        } if__end__2: ;
    }}

#line 4821 "bootstrap/stage0/ReCode.code"
void Generator__generate_break_statement(struct Generator* self, struct Checked_Break_Statement* statement) {
#line 4822 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "break;");}

#line 4825 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression_statement(struct Generator* self, struct Checked_Expression_Statement* statement) {
#line 4826 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->expression);
#line 4827 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4830 "bootstrap/stage0/ReCode.code"
void Generator__generate_goto_statement(struct Generator* self, struct Checked_Goto_Statement* statement) {
#line 4831 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "goto ");
#line 4832 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, statement->label);
#line 4833 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ';');}

#line 4836 "bootstrap/stage0/ReCode.code"
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement) {
#line 4837 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "if (");
#line 4838 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4839 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4840 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->true_statement);
#line 4841 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->false_statement != NULL) {
#line 4841 "bootstrap/stage0/ReCode.code"
            {
#line 4842 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, " else ");
#line 4843 "bootstrap/stage0/ReCode.code"
                Generator__generate_statement(self, statement->false_statement);
            } goto if__end__1; } if__end__1: ;
    }}

#line 4847 "bootstrap/stage0/ReCode.code"
void Generator__generate_label_statement(struct Generator* self, struct Checked_Label_Statement* statement) {
#line 4848 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, statement->label);
#line 4849 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ": ;");}

#line 4852 "bootstrap/stage0/ReCode.code"
void Generator__generate_return_statement(struct Generator* self, struct Checked_Return_Statement* statement) {
#line 4853 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "return");
#line 4854 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->expression != NULL) {
#line 4854 "bootstrap/stage0/ReCode.code"
            {
#line 4855 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, " ");
#line 4856 "bootstrap/stage0/ReCode.code"
                Generator__generate_expression(self, statement->expression);
            } goto if__end__1; } if__end__1: ;
    }
#line 4858 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4861 "bootstrap/stage0/ReCode.code"
void Generator__generate_variable_statement(struct Generator* self, struct Checked_Variable_Statement* statement) {
#line 4862 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->is_external) {
#line 4862 "bootstrap/stage0/ReCode.code"
            {
#line 4863 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self->file, "extern ");
#line 4864 "bootstrap/stage0/ReCode.code"
                File__write_checked_type(self->file, statement->variable->super.type);
#line 4865 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, ' ');
#line 4866 "bootstrap/stage0/ReCode.code"
                File__write_string(self->file, statement->variable->super.name);
            } goto if__end__1; } if__else__1: ;
#line 4867 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (statement->expression != NULL) {
#line 4867 "bootstrap/stage0/ReCode.code"
                {
#line 4868 "bootstrap/stage0/ReCode.code"
                    File__write_string(self->file, statement->variable->super.name);
#line 4869 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self->file, " = ");
#line 4870 "bootstrap/stage0/ReCode.code"
                    Generator__generate_expression(self, statement->expression);
                } goto if__end__2; } if__end__2: ;
        } if__end__1: ;
    }
#line 4872 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");}

#line 4875 "bootstrap/stage0/ReCode.code"
void Generator__generate_while_statement(struct Generator* self, struct Checked_While_Statement* statement) {
#line 4876 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "while (");
#line 4877 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4878 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4879 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->body_statement);}

#line 4882 "bootstrap/stage0/ReCode.code"
void Generator__generate_statement(struct Generator* self, struct Checked_Statement* statement) {
#line 4883 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (statement->kind == Checked_Statement_Kind__ASSIGNMENT) {
#line 4883 "bootstrap/stage0/ReCode.code"
            {
#line 4884 "bootstrap/stage0/ReCode.code"
                Generator__generate_assignment_statement(self, ((struct Checked_Assignment_Statement*) statement));
            } goto if__end__1; } if__else__1: ;
#line 4885 "bootstrap/stage0/ReCode.code"
        if__start__2: { if (statement->kind == Checked_Statement_Kind__BLOCK) {
#line 4885 "bootstrap/stage0/ReCode.code"
                {
#line 4886 "bootstrap/stage0/ReCode.code"
                    Generator__generate_block_statement(self, ((struct Checked_Block_Statement*) statement));
                } goto if__end__2; } if__else__2: ;
#line 4887 "bootstrap/stage0/ReCode.code"
            if__start__3: { if (statement->kind == Checked_Statement_Kind__BREAK) {
#line 4887 "bootstrap/stage0/ReCode.code"
                    {
#line 4888 "bootstrap/stage0/ReCode.code"
                        Generator__generate_break_statement(self, ((struct Checked_Break_Statement*) statement));
                    } goto if__end__3; } if__else__3: ;
#line 4889 "bootstrap/stage0/ReCode.code"
                if__start__4: { if (statement->kind == Checked_Statement_Kind__EXPRESSION) {
#line 4889 "bootstrap/stage0/ReCode.code"
                        {
#line 4890 "bootstrap/stage0/ReCode.code"
                            Generator__generate_expression_statement(self, ((struct Checked_Expression_Statement*) statement));
                        } goto if__end__4; } if__else__4: ;
#line 4891 "bootstrap/stage0/ReCode.code"
                    if__start__5: { if (statement->kind == Checked_Statement_Kind__GOTO) {
#line 4891 "bootstrap/stage0/ReCode.code"
                            {
#line 4892 "bootstrap/stage0/ReCode.code"
                                Generator__generate_goto_statement(self, ((struct Checked_Goto_Statement*) statement));
                            } goto if__end__5; } if__else__5: ;
#line 4893 "bootstrap/stage0/ReCode.code"
                        if__start__6: { if (statement->kind == Checked_Statement_Kind__IF) {
#line 4893 "bootstrap/stage0/ReCode.code"
                                {
#line 4894 "bootstrap/stage0/ReCode.code"
                                    Generator__generate_if_statement(self, ((struct Checked_If_Statement*) statement));
                                } goto if__end__6; } if__else__6: ;
#line 4895 "bootstrap/stage0/ReCode.code"
                            if__start__7: { if (statement->kind == Checked_Statement_Kind__LABEL) {
#line 4895 "bootstrap/stage0/ReCode.code"
                                    {
#line 4896 "bootstrap/stage0/ReCode.code"
                                        Generator__generate_label_statement(self, ((struct Checked_Label_Statement*) statement));
                                    } goto if__end__7; } if__else__7: ;
#line 4897 "bootstrap/stage0/ReCode.code"
                                if__start__8: { if (statement->kind == Checked_Statement_Kind__RETURN) {
#line 4897 "bootstrap/stage0/ReCode.code"
                                        {
#line 4898 "bootstrap/stage0/ReCode.code"
                                            Generator__generate_return_statement(self, ((struct Checked_Return_Statement*) statement));
                                        } goto if__end__8; } if__else__8: ;
#line 4899 "bootstrap/stage0/ReCode.code"
                                    if__start__9: { if (statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 4899 "bootstrap/stage0/ReCode.code"
                                            {
#line 4900 "bootstrap/stage0/ReCode.code"
                                                Generator__generate_variable_statement(self, ((struct Checked_Variable_Statement*) statement));
                                            } goto if__end__9; } if__else__9: ;
#line 4901 "bootstrap/stage0/ReCode.code"
                                        if__start__10: { if (statement->kind == Checked_Statement_Kind__WHILE) {
#line 4901 "bootstrap/stage0/ReCode.code"
                                                {
#line 4902 "bootstrap/stage0/ReCode.code"
                                                    Generator__generate_while_statement(self, ((struct Checked_While_Statement*) statement));
                                                } goto if__end__10; } if__else__10: ;
#line 4903 "bootstrap/stage0/ReCode.code"
                                            {
#line 4904 "bootstrap/stage0/ReCode.code"
                                                Source_Location__error(statement->location, String__create_from("Unsupported statement"));
#line 4905 "bootstrap/stage0/ReCode.code"
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

#line 4909 "bootstrap/stage0/ReCode.code"
void Generator__generate_statements(struct Generator* self, struct Checked_Statements* statements) { struct Checked_Symbol* symbol; struct Checked_Statement* statement;
#line 4910 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation + ((uint16_t) 1);
#line 4912 "bootstrap/stage0/ReCode.code"
    symbol = statements->symbols->first_symbol;
#line 4913 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 4914 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4915 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self->file, symbol->type);
#line 4916 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4917 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, symbol->name);
#line 4918 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ";");
#line 4919 "bootstrap/stage0/ReCode.code"
        symbol = symbol->next_symbol;
    }
#line 4922 "bootstrap/stage0/ReCode.code"
    statement = statements->first_statement;
#line 4923 "bootstrap/stage0/ReCode.code"
    while (statement != NULL) {
#line 4924 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (statement->location != NULL) {
#line 4924 "bootstrap/stage0/ReCode.code"
                {
#line 4925 "bootstrap/stage0/ReCode.code"
                    File__write_char(self->file, '\n');
#line 4926 "bootstrap/stage0/ReCode.code"
                    Generator__write_source_location(self, statement->location);
#line 4927 "bootstrap/stage0/ReCode.code"
                    Generator__write_identation(self);
                } goto if__end__1; } if__else__1: ;
#line 4928 "bootstrap/stage0/ReCode.code"
            {
#line 4929 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, ' ');
            } if__end__1: ;
        }
#line 4932 "bootstrap/stage0/ReCode.code"
        Generator__generate_statement(self, statement);
#line 4934 "bootstrap/stage0/ReCode.code"
        statement = statement->next_statement;
    }
#line 4937 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation - ((uint16_t) 1);}

#line 4940 "bootstrap/stage0/ReCode.code"
void Generator__generate_enum(struct Generator* self, struct Checked_Enum_Type* enum_type) { struct Checked_Enum_Member* enum_member;
#line 4941 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) enum_type));
#line 4942 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4943 "bootstrap/stage0/ReCode.code"
    enum_member = enum_type->first_member;
#line 4944 "bootstrap/stage0/ReCode.code"
    while (enum_member != NULL) {
#line 4945 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4946 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, enum_member->symbol->name);
#line 4947 "bootstrap/stage0/ReCode.code"
        enum_member = enum_member->next_member;
#line 4948 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (enum_member != NULL) {
#line 4948 "bootstrap/stage0/ReCode.code"
                {
#line 4949 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(self->file, ",\n");
                } goto if__end__1; } if__else__1: ;
#line 4950 "bootstrap/stage0/ReCode.code"
            {
#line 4951 "bootstrap/stage0/ReCode.code"
                File__write_char(self->file, '\n');
            } if__end__1: ;
        }
    }
#line 4954 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n");}

#line 4957 "bootstrap/stage0/ReCode.code"
void Generator__declare_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4958 "bootstrap/stage0/ReCode.code"
    File__write_checked_function_symbol(self->file, function_symbol);
#line 4959 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");}

#line 4962 "bootstrap/stage0/ReCode.code"
void Generator__generate_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4963 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (function_symbol->checked_statements == NULL) {
#line 4963 "bootstrap/stage0/ReCode.code"
            {
#line 4964 "bootstrap/stage0/ReCode.code"
                return;
            } goto if__end__1; } if__end__1: ;
    }
#line 4966 "bootstrap/stage0/ReCode.code"
    Generator__write_source_location(self, function_symbol->super.location);
#line 4967 "bootstrap/stage0/ReCode.code"
    File__write_checked_function_symbol(self->file, function_symbol);
#line 4968 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {");
#line 4969 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, function_symbol->checked_statements);
#line 4970 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "}\n\n");}

#line 4973 "bootstrap/stage0/ReCode.code"
void Generator__declare_opaque_type(struct Generator* self, struct Checked_Opaque_Type* opaque_type) {
#line 4974 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) opaque_type));
#line 4975 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");}

#line 4978 "bootstrap/stage0/ReCode.code"
void Generator__declare_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4979 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) struct_type));
#line 4980 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");}

#line 4983 "bootstrap/stage0/ReCode.code"
void Generator__generate_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) { struct Checked_Struct_Member* struct_member;
#line 4984 "bootstrap/stage0/ReCode.code"
    struct_member = struct_type->first_member;
#line 4985 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (struct_member == NULL) {
#line 4985 "bootstrap/stage0/ReCode.code"
            {
#line 4986 "bootstrap/stage0/ReCode.code"
                return;
            } goto if__end__1; } if__end__1: ;
    }
#line 4988 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, ((struct Checked_Type*) struct_type));
#line 4989 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4990 "bootstrap/stage0/ReCode.code"
    while (struct_member != NULL) {
#line 4991 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4992 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self->file, struct_member->type);
#line 4993 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4994 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, struct_member->name);
#line 4995 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ";\n");
#line 4996 "bootstrap/stage0/ReCode.code"
        struct_member = struct_member->next_member;
    }
#line 4998 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n\n");}

#line 5001 "bootstrap/stage0/ReCode.code"
void generate(struct File* file, struct Checked_Source* checked_source) { struct Generator generator; struct Checked_Symbol* checked_symbol; struct Checked_Statement* checked_statement;
#line 5002 "bootstrap/stage0/ReCode.code"
    ;
#line 5003 "bootstrap/stage0/ReCode.code"
    generator.file = file;
#line 5004 "bootstrap/stage0/ReCode.code"
    generator.identation = ((uint16_t) 0);
#line 5006 "bootstrap/stage0/ReCode.code"
    ;
#line 5008 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "/* Copyright (C) 2023 Stefan Selariu */\n");
#line 5009 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5010 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <inttypes.h>\n");
#line 5011 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stdbool.h>\n");
#line 5012 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stddef.h>\n");
#line 5013 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5016 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5017 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5018 "bootstrap/stage0/ReCode.code"
        if__start__1: { if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 5018 "bootstrap/stage0/ReCode.code"
                { struct Checked_Named_Type* named_type;
#line 5019 "bootstrap/stage0/ReCode.code"
                    named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 5020 "bootstrap/stage0/ReCode.code"
                    if__start__2: { if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 5020 "bootstrap/stage0/ReCode.code"
                            {
#line 5021 "bootstrap/stage0/ReCode.code"
                                Generator__declare_struct(&generator, ((struct Checked_Struct_Type*) named_type));
                            } goto if__end__2; } if__else__2: ;
#line 5022 "bootstrap/stage0/ReCode.code"
                        if__start__3: { if (named_type->super.kind == Checked_Type_Kind__OPAQUE) {
#line 5022 "bootstrap/stage0/ReCode.code"
                                {
#line 5023 "bootstrap/stage0/ReCode.code"
                                    Generator__declare_opaque_type(&generator, ((struct Checked_Opaque_Type*) named_type));
                                } goto if__end__3; } if__else__3: ;
#line 5024 "bootstrap/stage0/ReCode.code"
                            if__start__4: { if (named_type->super.kind == Checked_Type_Kind__ENUM) {
#line 5024 "bootstrap/stage0/ReCode.code"
                                    {
#line 5025 "bootstrap/stage0/ReCode.code"
                                        Generator__generate_enum(&generator, ((struct Checked_Enum_Type*) named_type));
                                    } goto if__end__4; } if__end__4: ;
                            } if__end__3: ;
                        } if__end__2: ;
                    }
                } goto if__end__1; } if__end__1: ;
        }
#line 5028 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 5030 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5033 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5034 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5035 "bootstrap/stage0/ReCode.code"
        if__start__5: { if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 5035 "bootstrap/stage0/ReCode.code"
                { struct Checked_Named_Type* named_type;
#line 5036 "bootstrap/stage0/ReCode.code"
                    named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 5037 "bootstrap/stage0/ReCode.code"
                    if__start__6: { if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 5037 "bootstrap/stage0/ReCode.code"
                            {
#line 5038 "bootstrap/stage0/ReCode.code"
                                Generator__generate_struct(&generator, ((struct Checked_Struct_Type*) named_type));
                            } goto if__end__6; } if__end__6: ;
                    }
                } goto if__end__5; } if__end__5: ;
        }
#line 5041 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 5045 "bootstrap/stage0/ReCode.code"
    checked_statement = checked_source->statements->first_statement;
#line 5046 "bootstrap/stage0/ReCode.code"
    while (checked_statement != NULL) {
#line 5047 "bootstrap/stage0/ReCode.code"
        if__start__7: { if (checked_statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 5047 "bootstrap/stage0/ReCode.code"
                {
#line 5048 "bootstrap/stage0/ReCode.code"
                    Generator__generate_variable_statement(&generator, ((struct Checked_Variable_Statement*) checked_statement));
#line 5049 "bootstrap/stage0/ReCode.code"
                    File__write_cstring(generator.file, "\n");
                } goto if__end__7; } if__else__7: ;
#line 5050 "bootstrap/stage0/ReCode.code"
            {
#line 5051 "bootstrap/stage0/ReCode.code"
                Source_Location__error(checked_statement->location, String__create_from("Unsupported statement"));
#line 5052 "bootstrap/stage0/ReCode.code"
                abort();
            } if__end__7: ;
        }
#line 5054 "bootstrap/stage0/ReCode.code"
        checked_statement = checked_statement->next_statement;
    }
#line 5056 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5059 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5060 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5061 "bootstrap/stage0/ReCode.code"
        if__start__8: { if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 5061 "bootstrap/stage0/ReCode.code"
                {
#line 5062 "bootstrap/stage0/ReCode.code"
                    Generator__declare_function(&generator, ((struct Checked_Function_Symbol*) checked_symbol));
                } goto if__end__8; } if__end__8: ;
        }
#line 5064 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 5066 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 5069 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 5070 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 5071 "bootstrap/stage0/ReCode.code"
        if__start__9: { if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 5071 "bootstrap/stage0/ReCode.code"
                {
#line 5072 "bootstrap/stage0/ReCode.code"
                    Generator__generate_function(&generator, ((struct Checked_Function_Symbol*) checked_symbol));
                } goto if__end__9; } if__end__9: ;
        }
#line 5074 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }}

#line 5086 "bootstrap/stage0/ReCode.code"
struct Counter* Counter__create() { struct Counter* counter;
#line 5087 "bootstrap/stage0/ReCode.code"
    counter = ((struct Counter*) malloc(sizeof(struct Counter)));
#line 5088 "bootstrap/stage0/ReCode.code"
    counter->value = ((int16_t) 0);
#line 5089 "bootstrap/stage0/ReCode.code"
    return counter;}

#line 5092 "bootstrap/stage0/ReCode.code"
int16_t Counter__next(struct Counter* self) {
#line 5093 "bootstrap/stage0/ReCode.code"
    self->value = self->value + ((int16_t) 1);
#line 5094 "bootstrap/stage0/ReCode.code"
    return self->value;}

#line 5097 "bootstrap/stage0/ReCode.code"
struct Counter* Counter__reset(struct Counter* self) {
#line 5098 "bootstrap/stage0/ReCode.code"
    self->value = ((int16_t) 0);
#line 5099 "bootstrap/stage0/ReCode.code"
    return self;}

#line 5106 "bootstrap/stage0/ReCode.code"
int32_t main(int32_t argc, char** argv) { char* source_file_path; struct File* source_file; char* output_file_path; struct File* output_file; struct Source* source; struct Parsed_Source* parsed_source; struct Checked_Source* checked_source;
#line 5107 "bootstrap/stage0/ReCode.code"
    if__start__1: { if (argc < 3) {
#line 5107 "bootstrap/stage0/ReCode.code"
            {
#line 5108 "bootstrap/stage0/ReCode.code"
                error(String__append_cstring(String__append_cstring(String__create_from("Usage: "), argv[((size_t) 0)]), " SOURCE OUTPUT"));
#line 5109 "bootstrap/stage0/ReCode.code"
                return 1;
            } goto if__end__1; } if__end__1: ;
    }
#line 5112 "bootstrap/stage0/ReCode.code"
    source_file_path = argv[((size_t) 1)];
#line 5113 "bootstrap/stage0/ReCode.code"
    source_file = fopen(source_file_path, "r");
#line 5114 "bootstrap/stage0/ReCode.code"
    if__start__2: { if (source_file == NULL) {
#line 5114 "bootstrap/stage0/ReCode.code"
            {
#line 5115 "bootstrap/stage0/ReCode.code"
                error(String__append_cstring(String__create_from("Cannot open file: "), source_file_path));
#line 5116 "bootstrap/stage0/ReCode.code"
                return 1;
            } goto if__end__2; } if__end__2: ;
    }
#line 5119 "bootstrap/stage0/ReCode.code"
    output_file_path = argv[((size_t) 2)];
#line 5120 "bootstrap/stage0/ReCode.code"
    ;
#line 5121 "bootstrap/stage0/ReCode.code"
    if__start__3: { if (String__equals_cstring(String__create_from(output_file_path), "-")) {
#line 5121 "bootstrap/stage0/ReCode.code"
            {
#line 5122 "bootstrap/stage0/ReCode.code"
                output_file = stdout;
            } goto if__end__3; } if__else__3: ;
#line 5123 "bootstrap/stage0/ReCode.code"
        {
#line 5124 "bootstrap/stage0/ReCode.code"
            output_file = fopen(output_file_path, "w");
#line 5125 "bootstrap/stage0/ReCode.code"
            if__start__4: { if (output_file == NULL) {
#line 5125 "bootstrap/stage0/ReCode.code"
                    {
#line 5126 "bootstrap/stage0/ReCode.code"
                        error(String__append_cstring(String__create_from("Cannot open file: "), output_file_path));
#line 5127 "bootstrap/stage0/ReCode.code"
                        return 1;
                    } goto if__end__4; } if__end__4: ;
            }
        } if__end__3: ;
    }
#line 5131 "bootstrap/stage0/ReCode.code"
    source = Source__create(source_file, source_file_path);
#line 5132 "bootstrap/stage0/ReCode.code"
    parsed_source = parse(source);
#line 5133 "bootstrap/stage0/ReCode.code"
    checked_source = check(parsed_source);
#line 5134 "bootstrap/stage0/ReCode.code"
    generate(output_file, checked_source);
#line 5136 "bootstrap/stage0/ReCode.code"
    fclose(source_file);
#line 5137 "bootstrap/stage0/ReCode.code"
    return fclose(output_file);}

