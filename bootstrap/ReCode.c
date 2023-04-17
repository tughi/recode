/* Copyright (C) 2023 Stefan Selariu */

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct File;
struct String;
struct Source;
struct Source_Location;
enum Token_Kind {
	TOKEN_KIND__CHARACTER,
	TOKEN_KIND__COMMENT,
	TOKEN_KIND__END_OF_FILE,
	TOKEN_KIND__END_OF_LINE,
	TOKEN_KIND__ERROR,
	TOKEN_KIND__IDENTIFIER,
	TOKEN_KIND__INTEGER,
	TOKEN_KIND__KEYWORD,
	TOKEN_KIND__OTHER,
	TOKEN_KIND__SPACE,
	TOKEN_KIND__STRING
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
struct Parsed_Statements;
struct Parsed_Source;
enum Parsed_Type_Kind {
	PARSED_TYPE_KIND__NAMED,
	PARSED_TYPE_KIND__POINTER,
	PARSED_TYPE_KIND__STRUCT
};
struct Parsed_Statement;
struct Parsed_Type;
struct Parsed_Named_Type;
struct Parsed_Pointer_Type;
struct Parsed_Struct_Type;
enum Parsed_Expression_Kind {
	PARSED_EXPRESSION_KIND__ADD,
	PARSED_EXPRESSION_KIND__ADDRESS_OF,
	PARSED_EXPRESSION_KIND__ARRAY_ACCESS,
	PARSED_EXPRESSION_KIND__BOOL,
	PARSED_EXPRESSION_KIND__CALL,
	PARSED_EXPRESSION_KIND__CAST,
	PARSED_EXPRESSION_KIND__CHARACTER,
	PARSED_EXPRESSION_KIND__DIVIDE,
	PARSED_EXPRESSION_KIND__EQUALS,
	PARSED_EXPRESSION_KIND__GREATER,
	PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS,
	PARSED_EXPRESSION_KIND__GROUP,
	PARSED_EXPRESSION_KIND__INTEGER,
	PARSED_EXPRESSION_KIND__LESS,
	PARSED_EXPRESSION_KIND__LESS_OR_EQUALS,
	PARSED_EXPRESSION_KIND__LOGIC_AND,
	PARSED_EXPRESSION_KIND__LOGIC_OR,
	PARSED_EXPRESSION_KIND__MEMBER_ACCESS,
	PARSED_EXPRESSION_KIND__MINUS,
	PARSED_EXPRESSION_KIND__MODULO,
	PARSED_EXPRESSION_KIND__MULTIPLY,
	PARSED_EXPRESSION_KIND__NOT,
	PARSED_EXPRESSION_KIND__NOT_EQUALS,
	PARSED_EXPRESSION_KIND__NULL,
	PARSED_EXPRESSION_KIND__SIZEOF,
	PARSED_EXPRESSION_KIND__STRING,
	PARSED_EXPRESSION_KIND__SUBSTRACT,
	PARSED_EXPRESSION_KIND__SYMBOL
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
	PARSED_STATEMENT_KIND__ASSIGNMENT,
	PARSED_STATEMENT_KIND__BLOCK,
	PARSED_STATEMENT_KIND__BREAK,
	PARSED_STATEMENT_KIND__ENUM,
	PARSED_STATEMENT_KIND__EXPRESSION,
	PARSED_STATEMENT_KIND__FUNCTION,
	PARSED_STATEMENT_KIND__FUNCTION_TYPE,
	PARSED_STATEMENT_KIND__IF,
	PARSED_STATEMENT_KIND__RETURN,
	PARSED_STATEMENT_KIND__STRUCT,
	PARSED_STATEMENT_KIND__VARIABLE,
	PARSED_STATEMENT_KIND__WHILE
};
struct Parsed_Named_Statement;
struct Parsed_Assignment_Statement;
struct Parsed_Block_Statement;
struct Parsed_Break_Statement;
struct Parsed_Enum_Member;
struct Parsed_Enum_Statement;
struct Parsed_Expression_Statement;
struct Parsed_Function_Parameter;
struct Parsed_Function_Statement;
struct Parsed_Function_Type_Parameter;
struct Parsed_Function_Type_Statement;
struct Parsed_If_Statement;
struct Parsed_Return_Statement;
struct Parsed_Struct_Member;
struct Parsed_Struct_Statement;
struct Parsed_Variable_Statement;
struct Parsed_While_Statement;
struct Parser;
enum Checked_Type_Kind {
	CHECKED_TYPE_KIND__BOOL,
	CHECKED_TYPE_KIND__CHAR,
	CHECKED_TYPE_KIND__INT16_T,
	CHECKED_TYPE_KIND__INT32_T,
	CHECKED_TYPE_KIND__INT64_T,
	CHECKED_TYPE_KIND__INT8_T,
	CHECKED_TYPE_KIND__SIZE_T,
	CHECKED_TYPE_KIND__UINT16_T,
	CHECKED_TYPE_KIND__UINT32_T,
	CHECKED_TYPE_KIND__UINT64_T,
	CHECKED_TYPE_KIND__UINT8_T,
	CHECKED_TYPE_KIND__VOID,
	CHECKED_TYPE_KIND__NULL,
	CHECKED_TYPE_KIND__ENUM,
	CHECKED_TYPE_KIND__FUNCTION,
	CHECKED_TYPE_KIND__STRUCT,
	CHECKED_TYPE_KIND__POINTER
};
struct Checked_Type;
struct Checked_Named_Type;
struct Checked_Enum_Member;
struct Checked_Enum_Type;
struct Checked_Function_Parameter;
struct Checked_Function_Type;
struct Checked_Pointer_Type;
struct Checked_Struct_Member;
struct Checked_Struct_Type;
enum Checked_Symbol_Kind {
	CHECKED_SYMBOL_KIND__ENUM_MEMBER,
	CHECKED_SYMBOL_KIND__FUNCTION,
	CHECKED_SYMBOL_KIND__FUNCTION_PARAMETER,
	CHECKED_SYMBOL_KIND__TYPE,
	CHECKED_SYMBOL_KIND__VARIABLE
};
struct Checked_Symbol;
struct Checked_Enum_Member_Symbol;
struct Checked_Statements;
struct Checked_Function_Symbol;
struct Checked_Function_Parameter_Symbol;
struct Checked_Type_Symbol;
struct Checked_Variable_Symbol;
struct Checked_Symbols;
enum Checked_Expression_Kind {
	CHECKED_EXPRESSION_KIND__ADD,
	CHECKED_EXPRESSION_KIND__ADDRESS_OF,
	CHECKED_EXPRESSION_KIND__ARRAY_ACCESS,
	CHECKED_EXPRESSION_KIND__BOOL,
	CHECKED_EXPRESSION_KIND__CALL,
	CHECKED_EXPRESSION_KIND__CAST,
	CHECKED_EXPRESSION_KIND__CHARACTER,
	CHECKED_EXPRESSION_KIND__DIVIDE,
	CHECKED_EXPRESSION_KIND__EQUALS,
	CHECKED_EXPRESSION_KIND__GREATER,
	CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS,
	CHECKED_EXPRESSION_KIND__GROUP,
	CHECKED_EXPRESSION_KIND__INTEGER,
	CHECKED_EXPRESSION_KIND__LESS,
	CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS,
	CHECKED_EXPRESSION_KIND__LOGIC_AND,
	CHECKED_EXPRESSION_KIND__LOGIC_OR,
	CHECKED_EXPRESSION_KIND__MEMBER_ACCESS,
	CHECKED_EXPRESSION_KIND__MINUS,
	CHECKED_EXPRESSION_KIND__MODULO,
	CHECKED_EXPRESSION_KIND__MULTIPLY,
	CHECKED_EXPRESSION_KIND__NOT,
	CHECKED_EXPRESSION_KIND__NOT_EQUALS,
	CHECKED_EXPRESSION_KIND__NULL,
	CHECKED_EXPRESSION_KIND__SIZEOF,
	CHECKED_EXPRESSION_KIND__STRING,
	CHECKED_EXPRESSION_KIND__SUBSTRACT,
	CHECKED_EXPRESSION_KIND__SYMBOL
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
	CHECKED_STATEMENT_KIND__ASSIGNMENT,
	CHECKED_STATEMENT_KIND__BLOCK,
	CHECKED_STATEMENT_KIND__BREAK,
	CHECKED_STATEMENT_KIND__EXPRESSION,
	CHECKED_STATEMENT_KIND__IF,
	CHECKED_STATEMENT_KIND__RETURN,
	CHECKED_STATEMENT_KIND__VARIABLE,
	CHECKED_STATEMENT_KIND__WHILE
};
struct Checked_Statement;
struct Checked_Assignment_Statement;
struct Checked_Block_Statement;
struct Checked_Break_Statement;
struct Checked_Expression_Statement;
struct Checked_If_Statement;
struct Checked_Return_Statement;
struct Checked_Variable_Statement;
struct Checked_While_Statement;
struct Checked_Source;
struct Checker;
struct Generator;

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

struct Parsed_Statements {
	struct Parsed_Statement* first_statement;
	struct Parsed_Statement* last_statement;
	bool has_globals;
};

struct Parsed_Source {
	struct Parsed_Statements* statements;
};

struct Parsed_Statement {
	enum Parsed_Statement_Kind kind;
	struct Source_Location* location;
	struct Parsed_Statement* next_statement;
};

struct Parsed_Type {
	enum Parsed_Type_Kind kind;
	struct Source_Location* location;
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

struct Parsed_Function_Parameter {
	struct Token* name;
	struct Parsed_Type* type;
	struct Parsed_Function_Parameter* next_parameter;
};

struct Parsed_Function_Statement {
	struct Parsed_Named_Statement super;
	struct Parsed_Function_Parameter* first_parameter;
	struct Parsed_Type* return_type;
	struct Parsed_Statements* statements;
	bool is_external;
};

struct Parsed_Function_Type_Parameter {
	struct Token* name;
	struct Parsed_Type* type;
	struct Parsed_Function_Type_Parameter* next_parameter;
};

struct Parsed_Function_Type_Statement {
	struct Parsed_Named_Statement super;
	struct Parsed_Function_Type_Parameter* first_parameter;
	struct Parsed_Type* return_type;
};

struct Parsed_If_Statement {
	struct Parsed_Statement super;
	struct Parsed_Expression* condition_expression;
	struct Parsed_Statement* true_statement;
	struct Parsed_Statement* false_statement;
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
	struct Checked_Named_Type super;
	struct Checked_Type* return_type;
	struct Checked_Function_Parameter* first_parameter;
};

struct Checked_Pointer_Type {
	struct Checked_Type super;
	struct Checked_Type* other_type;
};

struct Checked_Struct_Member {
	struct Source_Location* location;
	struct String* name;
	struct Checked_Type* type;
	struct Checked_Struct_Member* next_member;
};

struct Checked_Struct_Type {
	struct Checked_Named_Type super;
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

struct Checked_Statements {
	struct Checked_Statement* first_statement;
	struct Checked_Statement* last_statement;
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
	struct Checked_Statements* statements;
};

struct Checked_Break_Statement {
	struct Checked_Statement super;
};

struct Checked_Expression_Statement {
	struct Checked_Statement super;
	struct Checked_Expression* expression;
};

struct Checked_If_Statement {
	struct Checked_Statement super;
	struct Checked_Expression* condition_expression;
	struct Checked_Statement* true_statement;
	struct Checked_Statement* false_statement;
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

struct Checked_Source {
	struct Checked_Symbol* first_symbol;
	struct Checked_Statements* statements;
};

struct Checker {
	struct Checked_Named_Type* first_type;
	struct Checked_Named_Type* last_type;
	struct Checked_Named_Type* last_builting_type;
	struct Checked_Symbols* symbols;
	struct Checked_Type* return_type;
};

struct Generator {
	struct File* file;
	uint16_t identation;
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
struct String* String__append_int16_t(struct String* self, int16_t value);
struct String* String__append_string(struct String* self, struct String* other);
bool String__equals_cstring(struct String* self, char* s);
bool String__equals_string(struct String* self, struct String* other);
void pass();
void File__write_char(struct File* self, char c);
void File__write_cstring(struct File* self, char* s);
void File__write_int32_t(struct File* self, int32_t value);
void File__write_uint64_t(struct File* self, uint64_t value);
void File__write_string(struct File* self, struct String* string);
void error(struct String* message);
void warning(struct String* message);
void TODO(char* message);
struct Source* Source__create(struct File* file, char* file_path);
struct Source_Location* Source_Location__create(struct Source* source, uint16_t line, uint16_t column);
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
bool Token__is_extern(struct Token* self);
bool Token__is_false(struct Token* self);
bool Token__is_if(struct Token* self);
bool Token__is_null(struct Token* self);
bool Token__is_return(struct Token* self);
bool Token__is_sizeof(struct Token* self);
bool Token__is_struct(struct Token* self);
bool Token__is_true(struct Token* self);
bool Token__is_typedef(struct Token* self);
bool Token__is_while(struct Token* self);
bool Token__is_other(struct Token* self, char* lexeme);
bool Token__is_ampersand(struct Token* self);
bool Token__is_asterisk(struct Token* self);
bool Token__is_closing_brace(struct Token* self);
bool Token__is_closing_bracket(struct Token* self);
bool Token__is_closing_paren(struct Token* self);
bool Token__is_comma(struct Token* self);
bool Token__is_dot(struct Token* self);
bool Token__is_equals(struct Token* self);
bool Token__is_exclamation_mark(struct Token* self);
bool Token__is_greater_than(struct Token* self);
bool Token__is_hash(struct Token* self);
bool Token__is_less_than(struct Token* self);
bool Token__is_minus(struct Token* self);
bool Token__is_opening_brace(struct Token* self);
bool Token__is_opening_bracket(struct Token* self);
bool Token__is_opening_paren(struct Token* self);
bool Token__is_percent(struct Token* self);
bool Token__is_plus(struct Token* self);
bool Token__is_semicolon(struct Token* self);
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
struct Parsed_Type* Parsed_Named_Type__create(struct Token* name);
struct Parsed_Type* Parsed_Pointer_Type__create(struct Parsed_Type* other_type);
struct Parsed_Type* Parsed_Struct_Type__create(struct Source_Location* location, struct Parsed_Type* other_type);
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
struct Parsed_Function_Parameter* Parsed_Function_Parameter__create(struct Token* name, struct Parsed_Type* type);
struct Parsed_Statement* Parsed_Function_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* resturn_type, struct Parsed_Statements* statements, bool is_external);
struct Parsed_Function_Type_Parameter* Parsed_Function_Type_Parameter__create(struct Token* name, struct Parsed_Type* type);
struct Parsed_Statement* Parsed_Function_Type_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Type_Parameter* first_parameter, struct Parsed_Type* resturn_type);
struct Parsed_Statement* Parsed_If_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* true_statement, struct Parsed_Statement* false_statement);
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
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self), bool second_required, bool (*third_is)(struct Token* self));
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self));
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token* self));
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token* self));
void Parser__consume_comment(struct Parser* self);
void Parser__consume_space(struct Parser* self, uint16_t count);
void Parser__consume_end_of_line(struct Parser* self);
bool Parser__consume_empty_line(struct Parser* self);
struct Parsed_Expression* Parser__parse_expression(struct Parser* self);
struct Parsed_Type* Parser__parse_type(struct Parser* self);
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
struct Parsed_Statement* Parser__parse_struct(struct Parser* self);
struct Parsed_Statement* Parser__parse_enum(struct Parser* self);
struct Parsed_Statement* Parser__parse_type_alias(struct Parser* self);
struct Parsed_Statement* Parser__parse_variable(struct Parser* self);
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self);
struct Parsed_Function_Parameter* Parser__parse_function_parameters(struct Parser* self);
void Parser__parse_statements(struct Parser* self, struct Parsed_Statements* statements);
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_function(struct Parser* self);
struct Parsed_Statement* Parser__parse_return_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_break_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_if_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_while_statement(struct Parser* self);
struct Parsed_Statement* Parser__parse_statement(struct Parser* self);
void Parser__parse_source(struct Parser* self, struct Source* source);
struct Parsed_Source* parse(struct Source* source);
struct Checked_Type* Checked_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location);
bool Checked_Type__equals(struct Checked_Type* self, struct Checked_Type* other_type);
struct String* String__append_checked_type(struct String* self, struct Checked_Type* type);
void Checked_Type__expect_same_type(struct Checked_Type* self, struct Checked_Type* other_type, struct Source_Location* location);
bool Checked_Type__is_scalar_type(struct Checked_Type* self);
void Checked_Type__expect_scalar_type(struct Checked_Type* self, struct Source_Location* location);
struct Checked_Named_Type* Checked_Named_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name);
struct Checked_Enum_Member* Checked_Enum_Member__create(struct Source_Location* location, struct String* name);
struct Checked_Enum_Type* Checked_Enum_Type__create(struct Source_Location* location, struct String* name);
struct Checked_Enum_Member* Checked_Enum_Type__find_member(struct Checked_Enum_Type* self, struct String* name);
struct Checked_Function_Parameter* Checked_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct String* name, struct Checked_Type* return_type);
bool Checked_Function_Type__equals(struct Checked_Function_Type* self, struct Checked_Type* other_type);
struct Checked_Pointer_Type* Checked_Pointer_Type__create(struct Source_Location* location, struct Checked_Type* other_type);
bool Checked_Pointer_Type__equals(struct Checked_Pointer_Type* self, struct Checked_Type* other_type);
struct Checked_Struct_Member* Checked_Struct_Member__create(struct Source_Location* location, struct String* name, struct Checked_Type* type);
struct Checked_Struct_Type* Checked_Struct_Type__create(struct Source_Location* location, struct String* name);
struct Checked_Struct_Member* Checked_Struct_Type__find_member(struct Checked_Struct_Type* self, struct String* name);
bool Checked_Struct_Type__equals(struct Checked_Struct_Type* self, struct Checked_Type* other_type);
void File__write_checked_type(struct File* self, struct Checked_Type* type);
void File__write_checked_function_parameter(struct File* self, struct Checked_Function_Parameter* parameter);
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
struct Checked_Block_Statement* Checked_Block_Statement__create(struct Source_Location* location, struct Checked_Statements* statements);
struct Checked_Break_Statement* Checked_Break_Statement__create(struct Source_Location* location);
struct Checked_Expression_Statement* Checked_Expression_Statement__create(struct Source_Location* location, struct Checked_Expression* expression);
struct Checked_If_Statement* Checked_If_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* true_statement, struct Checked_Statement* false_statement);
struct Checked_Return_Statement* Checked_Return_Statement__create(struct Source_Location* location, struct Checked_Expression* expression);
struct Checked_Variable_Statement* Checked_Variable_Statement__create(struct Source_Location* location, struct Checked_Variable_Symbol* variable, struct Checked_Expression* expression, bool is_external);
struct Checked_While_Statement* Checked_While_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* body_statement);
struct Checked_Statements* Checked_Statements__create();
void Checked_Statements__append(struct Checked_Statements* self, struct Checked_Statement* statement);
void Checker__append_type(struct Checker* self, struct Checked_Named_Type* type);
struct Checker* Checker__create();
struct Checked_Named_Type* Checker__find_type(struct Checker* self, struct String* name);
struct Checked_Named_Type* Checker__get_builtin_type(struct Checker* self, enum Checked_Type_Kind kind);
struct Checked_Type* Checker__resolve_type(struct Checker* self, struct Parsed_Type* parsed_type);
struct Checked_Expression* Checker__check_expression(struct Checker* self, struct Parsed_Expression* parsed_expression);
struct Checked_Expression* Checker__check_add_expression(struct Checker* self, struct Parsed_Add_Expression* parsed_expression);
struct Checked_Expression* Checker__check_address_of_expression(struct Checker* self, struct Parsed_Address_Of_Expression* parsed_expression);
struct Checked_Expression* Checker__check_array_access_expression(struct Checker* self, struct Parsed_Array_Access_Expression* parsed_expression);
struct Checked_Expression* Checker__check_bool_expression(struct Checker* self, struct Parsed_Bool_Expression* parsed_expression);
struct Checked_Expression* Checker__check_call_expression(struct Checker* self, struct Parsed_Call_Expression* parsed_expression);
struct Checked_Expression* Checker__check_cast_expression(struct Checker* self, struct Parsed_Cast_Expression* parsed_expression);
struct Checked_Expression* Checker__check_character_expression(struct Checker* self, struct Parsed_Character_Expression* parsed_expression);
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
void Checker__check_enum_statement(struct Checker* self, struct Parsed_Enum_Statement* parsed_statement);
void Checker__check_function_type_statement(struct Checker* self, struct Parsed_Function_Type_Statement* parsed_statement);
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement);
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement);
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement);
struct Checked_Statements* Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements);
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement);
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement);
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement);
struct Checked_If_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement);
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement);
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement);
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement);
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement);
void Checker__check_function_definition(struct Checker* self, struct Parsed_Function_Statement* parsed_statement);
struct Checked_Source* Checker__check_source(struct Checker* self, struct Parsed_Source* parsed_source);
struct Checked_Source* check(struct Parsed_Source* parsed_source);
void Generator__write_source_location(struct Generator* self, struct Source_Location* location);
void Generator__generate_expression(struct Generator* self, struct Checked_Expression* expression);
void Generator__generate_add_expression(struct Generator* self, struct Checked_Add_Expression* expression);
void Generator__generate_address_of_expression(struct Generator* self, struct Checked_Address_Of_Expression* expression);
void Generator__generate_array_access_expression(struct Generator* self, struct Checked_Array_Access_Expression* expression);
void Generator__generate_bool_expression(struct Generator* self, struct Checked_Bool_Expression* expression);
void Generator__generate_call_expression(struct Generator* self, struct Checked_Call_Expression* expression);
void Generator__generate_cast_expression(struct Generator* self, struct Checked_Cast_Expression* expression);
void File__write_octal_escaped_char(struct File* stream, char value);
void File__write_escaped_char(struct File* stream, char ch);
void Generator__generate_character_expression(struct Generator* self, struct Checked_Character_Expression* expression);
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
void Generator__write_identation(struct Generator* self);
void Generator__generate_statement(struct Generator* self, struct Checked_Statement* statement);
void Generator__generate_statements(struct Generator* self, struct Checked_Statements* statements);
void Generator__generate_assignment_statement(struct Generator* self, struct Checked_Assignment_Statement* statement);
void Generator__generate_block_statement(struct Generator* self, struct Checked_Block_Statement* statement);
void Generator__generate_break_statement(struct Generator* self, struct Checked_Break_Statement* statement);
void Generator__generate_expression_statement(struct Generator* self, struct Checked_Expression_Statement* statement);
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement);
void Generator__generate_return_statement(struct Generator* self, struct Checked_Return_Statement* statement);
void Generator__generate_variable_statement(struct Generator* self, struct Checked_Variable_Statement* statement);
void Generator__generate_while_statement(struct Generator* self, struct Checked_While_Statement* statement);
void Generator__generate_enum(struct Generator* self, struct Checked_Enum_Type* enum_type);
void Generator__declare_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol);
void Generator__generate_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol);
void Generator__declare_struct(struct Generator* self, struct Checked_Struct_Type* struct_type);
void Generator__generate_struct(struct Generator* self, struct Checked_Struct_Type* struct_type);
void generate(struct File* file, struct Checked_Source* checked_source);
int32_t main(int32_t argc, char** argv);

#line 41 "boostrap/stage0/ReCode.c"
struct String* String__create_empty(size_t data_size) {
#line 42 "boostrap/stage0/ReCode.c"
    struct String* string = (struct String*) malloc(sizeof(struct String));
#line 43 "boostrap/stage0/ReCode.c"
    string->data = (char*) malloc(data_size);
#line 44 "boostrap/stage0/ReCode.c"
    string->data_size = data_size;
#line 45 "boostrap/stage0/ReCode.c"
    string->length = (size_t) 0;
#line 46 "boostrap/stage0/ReCode.c"
    return string;
}

#line 49 "boostrap/stage0/ReCode.c"
struct String* String__create() {
#line 50 "boostrap/stage0/ReCode.c"
    return String__create_empty((size_t) 16);
}

#line 53 "boostrap/stage0/ReCode.c"
void String__delete(struct String* self) {
#line 54 "boostrap/stage0/ReCode.c"
    free((void*) self->data);
#line 55 "boostrap/stage0/ReCode.c"
    free((void*) self);
}

#line 58 "boostrap/stage0/ReCode.c"
struct String* String__append_char(struct String* self, char ch) {
#line 59 "boostrap/stage0/ReCode.c"
    if (self->length >= self->data_size) {
#line 60 "boostrap/stage0/ReCode.c"
        self->data_size = self->data_size + (size_t) 16;
#line 61 "boostrap/stage0/ReCode.c"
        self->data = (char*) realloc((void*) self->data, self->data_size);
    }
#line 63 "boostrap/stage0/ReCode.c"
    self->data[self->length] = ch;
#line 64 "boostrap/stage0/ReCode.c"
    self->length = self->length + (size_t) 1;
#line 65 "boostrap/stage0/ReCode.c"
    return self;
}

#line 68 "boostrap/stage0/ReCode.c"
struct String* String__append_cstring(struct String* self, char* s) {
#line 69 "boostrap/stage0/ReCode.c"
    size_t index = (size_t) 0;
#line 70 "boostrap/stage0/ReCode.c"
    while (true) {
#line 71 "boostrap/stage0/ReCode.c"
        char c = s[index];
#line 72 "boostrap/stage0/ReCode.c"
        if (c == '\0') {
#line 73 "boostrap/stage0/ReCode.c"
            return self;
        }
#line 75 "boostrap/stage0/ReCode.c"
        String__append_char(self, c);
#line 76 "boostrap/stage0/ReCode.c"
        index = index + (size_t) 1;
    }
}

#line 80 "boostrap/stage0/ReCode.c"
size_t cstring_length(char* s) {
#line 81 "boostrap/stage0/ReCode.c"
    size_t length = (size_t) 0;
#line 82 "boostrap/stage0/ReCode.c"
    while (true) {
#line 83 "boostrap/stage0/ReCode.c"
        uint8_t c = (uint8_t) s[length];
#line 84 "boostrap/stage0/ReCode.c"
        if (c == (uint8_t) 0) {
#line 85 "boostrap/stage0/ReCode.c"
            break;
        }
#line 87 "boostrap/stage0/ReCode.c"
        length = length + (size_t) 1;
    }
#line 89 "boostrap/stage0/ReCode.c"
    return length;
}

#line 92 "boostrap/stage0/ReCode.c"
struct String* String__create_from(char* data) {
#line 93 "boostrap/stage0/ReCode.c"
    size_t string_length = cstring_length(data);
#line 94 "boostrap/stage0/ReCode.c"
    struct String* string = String__create_empty(string_length);
#line 95 "boostrap/stage0/ReCode.c"
    String__append_cstring(string, data);
#line 96 "boostrap/stage0/ReCode.c"
    return string;
}

#line 99 "boostrap/stage0/ReCode.c"
struct String* String__append_int16_t(struct String* self, int16_t value) {
#line 100 "boostrap/stage0/ReCode.c"
    if (value < (int16_t) 0) {
#line 101 "boostrap/stage0/ReCode.c"
        String__append_char(self, '-');
#line 102 "boostrap/stage0/ReCode.c"
        String__append_int16_t(self, -value);
    } else {
#line 104 "boostrap/stage0/ReCode.c"
        if (value >= (int16_t) 10) {
#line 105 "boostrap/stage0/ReCode.c"
            String__append_int16_t(self, value / (int16_t) 10);
        }
#line 107 "boostrap/stage0/ReCode.c"
        String__append_char(self, (char) (value % (int16_t) 10) + '0');
    }
#line 109 "boostrap/stage0/ReCode.c"
    return self;
}

#line 112 "boostrap/stage0/ReCode.c"
struct String* String__append_string(struct String* self, struct String* other) {
#line 113 "boostrap/stage0/ReCode.c"
    size_t index = (size_t) 0;
#line 114 "boostrap/stage0/ReCode.c"
    while (index < other->length) {
#line 115 "boostrap/stage0/ReCode.c"
        String__append_char(self, other->data[index]);
#line 116 "boostrap/stage0/ReCode.c"
        index = index + (size_t) 1;
    }
#line 118 "boostrap/stage0/ReCode.c"
    return self;
}

#line 121 "boostrap/stage0/ReCode.c"
bool String__equals_cstring(struct String* self, char* s) {
#line 122 "boostrap/stage0/ReCode.c"
    size_t length = cstring_length(s);
#line 123 "boostrap/stage0/ReCode.c"
    if (self->length != length) {
#line 124 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 127 "boostrap/stage0/ReCode.c"
    size_t index = (size_t) 0;
#line 128 "boostrap/stage0/ReCode.c"
    while (index < length) {
#line 129 "boostrap/stage0/ReCode.c"
        if (self->data[index] != s[index]) {
#line 130 "boostrap/stage0/ReCode.c"
            return false;
        }
#line 132 "boostrap/stage0/ReCode.c"
        index = index + (size_t) 1;
    }
#line 135 "boostrap/stage0/ReCode.c"
    return true;
}

#line 138 "boostrap/stage0/ReCode.c"
bool String__equals_string(struct String* self, struct String* other) {
#line 139 "boostrap/stage0/ReCode.c"
    if (self->length != other->length) {
#line 140 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 143 "boostrap/stage0/ReCode.c"
    size_t index = (size_t) 0;
#line 144 "boostrap/stage0/ReCode.c"
    while (index < self->length) {
#line 145 "boostrap/stage0/ReCode.c"
        if (self->data[index] != other->data[index]) {
#line 146 "boostrap/stage0/ReCode.c"
            return false;
        }
#line 148 "boostrap/stage0/ReCode.c"
        index = index + (size_t) 1;
    }
#line 151 "boostrap/stage0/ReCode.c"
    return true;
}

#line 157 "boostrap/stage0/ReCode.c"
void pass() {
}

#line 160 "boostrap/stage0/ReCode.c"
void File__write_char(struct File* self, char c) {
#line 161 "boostrap/stage0/ReCode.c"
    fputc((int32_t) c, self);
}

#line 164 "boostrap/stage0/ReCode.c"
void File__write_cstring(struct File* self, char* s) {
#line 165 "boostrap/stage0/ReCode.c"
    fputs(s, self);
}

#line 168 "boostrap/stage0/ReCode.c"
void File__write_int32_t(struct File* self, int32_t value) {
#line 169 "boostrap/stage0/ReCode.c"
    if (value < 0) {
#line 170 "boostrap/stage0/ReCode.c"
        File__write_char(self, '-');
#line 171 "boostrap/stage0/ReCode.c"
        File__write_int32_t(self, -value);
    } else {
#line 173 "boostrap/stage0/ReCode.c"
        if (value >= 10) {
#line 174 "boostrap/stage0/ReCode.c"
            File__write_int32_t(self, value / 10);
        }
#line 176 "boostrap/stage0/ReCode.c"
        File__write_char(self, (char) (value % 10) + '0');
    }
}

#line 180 "boostrap/stage0/ReCode.c"
void File__write_uint64_t(struct File* self, uint64_t value) {
#line 181 "boostrap/stage0/ReCode.c"
    if (value >= (uint64_t) 10) {
#line 182 "boostrap/stage0/ReCode.c"
        File__write_uint64_t(self, value / (uint64_t) 10);
    }
#line 184 "boostrap/stage0/ReCode.c"
    File__write_char(self, (char) (value % (uint64_t) 10) + '0');
}

#line 187 "boostrap/stage0/ReCode.c"
void File__write_string(struct File* self, struct String* string) {
#line 188 "boostrap/stage0/ReCode.c"
    size_t index = (size_t) 0;
#line 189 "boostrap/stage0/ReCode.c"
    while (index < string->length) {
#line 190 "boostrap/stage0/ReCode.c"
        File__write_char(self, string->data[index]);
#line 191 "boostrap/stage0/ReCode.c"
        index = index + (size_t) 1;
    }
}

#line 195 "boostrap/stage0/ReCode.c"
void error(struct String* message) {
#line 196 "boostrap/stage0/ReCode.c"
    File__write_cstring(stderr, "\33[0;91m");
#line 197 "boostrap/stage0/ReCode.c"
    File__write_string(stderr, message);
#line 198 "boostrap/stage0/ReCode.c"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 201 "boostrap/stage0/ReCode.c"
void warning(struct String* message) {
#line 202 "boostrap/stage0/ReCode.c"
    File__write_cstring(stderr, "\33[0;93m");
#line 203 "boostrap/stage0/ReCode.c"
    File__write_string(stderr, message);
#line 204 "boostrap/stage0/ReCode.c"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 207 "boostrap/stage0/ReCode.c"
void TODO(char* message) {
#line 208 "boostrap/stage0/ReCode.c"
    File__write_cstring(stderr, "\33[0;95mTODO: ");
#line 209 "boostrap/stage0/ReCode.c"
    File__write_cstring(stderr, message);
#line 210 "boostrap/stage0/ReCode.c"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 221 "boostrap/stage0/ReCode.c"
struct Source* Source__create(struct File* file, char* file_path) {
#line 222 "boostrap/stage0/ReCode.c"
    struct String* file_content = String__create();
#line 224 "boostrap/stage0/ReCode.c"
    while (true) {
#line 225 "boostrap/stage0/ReCode.c"
        int32_t ch = fgetc(file);
#line 226 "boostrap/stage0/ReCode.c"
        if (ch == -1) {
#line 227 "boostrap/stage0/ReCode.c"
            break;
        }
#line 229 "boostrap/stage0/ReCode.c"
        String__append_char(file_content, (char) ch);
    }
#line 232 "boostrap/stage0/ReCode.c"
    String__append_char(file_content, '\0');
#line 234 "boostrap/stage0/ReCode.c"
    struct Source* source = (struct Source*) malloc(sizeof(struct Source));
#line 235 "boostrap/stage0/ReCode.c"
    source->content = file_content;
#line 236 "boostrap/stage0/ReCode.c"
    source->path = file_path;
#line 238 "boostrap/stage0/ReCode.c"
    return source;
}

#line 250 "boostrap/stage0/ReCode.c"
struct Source_Location* Source_Location__create(struct Source* source, uint16_t line, uint16_t column) {
#line 251 "boostrap/stage0/ReCode.c"
    struct Source_Location* source_location = (struct Source_Location*) malloc(sizeof(struct Source_Location));
#line 252 "boostrap/stage0/ReCode.c"
    source_location->source = source;
#line 253 "boostrap/stage0/ReCode.c"
    source_location->line = line;
#line 254 "boostrap/stage0/ReCode.c"
    source_location->column = column;
#line 255 "boostrap/stage0/ReCode.c"
    return source_location;
}

#line 258 "boostrap/stage0/ReCode.c"
void File__write_source_location(struct File* self, struct Source_Location* location) {
#line 259 "boostrap/stage0/ReCode.c"
    File__write_cstring(self, location->source->path);
#line 260 "boostrap/stage0/ReCode.c"
    File__write_char(self, ':');
#line 261 "boostrap/stage0/ReCode.c"
    File__write_int32_t(self, (int32_t) location->line);
#line 262 "boostrap/stage0/ReCode.c"
    File__write_char(self, ':');
#line 263 "boostrap/stage0/ReCode.c"
    File__write_int32_t(self, (int32_t) location->column);
#line 264 "boostrap/stage0/ReCode.c"
    File__write_cstring(self, ": ");
}

#line 267 "boostrap/stage0/ReCode.c"
void Source_Location__error(struct Source_Location* self, struct String* message) {
#line 268 "boostrap/stage0/ReCode.c"
    File__write_source_location(stderr, self);
#line 269 "boostrap/stage0/ReCode.c"
    error(message);
}

#line 272 "boostrap/stage0/ReCode.c"
void Source_Location__warning(struct Source_Location* self, struct String* message) {
#line 273 "boostrap/stage0/ReCode.c"
    File__write_source_location(stderr, self);
#line 274 "boostrap/stage0/ReCode.c"
    warning(message);
}

#line 301 "boostrap/stage0/ReCode.c"
struct Token* Token__create_kind(enum Token_Kind kind, size_t kind_size, struct Source_Location* location, struct String* lexeme) {
#line 302 "boostrap/stage0/ReCode.c"
    struct Token* token = (struct Token*) malloc(kind_size);
#line 303 "boostrap/stage0/ReCode.c"
    token->kind = kind;
#line 304 "boostrap/stage0/ReCode.c"
    token->location = location;
#line 305 "boostrap/stage0/ReCode.c"
    token->lexeme = lexeme;
#line 306 "boostrap/stage0/ReCode.c"
    token->next_token = NULL;
#line 307 "boostrap/stage0/ReCode.c"
    return token;
}

#line 310 "boostrap/stage0/ReCode.c"
void Token__error(struct Token* self, struct String* message) {
#line 311 "boostrap/stage0/ReCode.c"
    Source_Location__error(self->location, message);
}

#line 314 "boostrap/stage0/ReCode.c"
void Token__warning(struct Token* self, struct String* message) {
#line 315 "boostrap/stage0/ReCode.c"
    Source_Location__warning(self->location, message);
}

#line 323 "boostrap/stage0/ReCode.c"
struct Character_Token* Character_Token__create(struct Source_Location* location, struct String* lexeme, char value) {
#line 324 "boostrap/stage0/ReCode.c"
    struct Character_Token* token = (struct Character_Token*) Token__create_kind(TOKEN_KIND__CHARACTER, sizeof(struct Character_Token), location, lexeme);
#line 325 "boostrap/stage0/ReCode.c"
    token->value = value;
#line 326 "boostrap/stage0/ReCode.c"
    return token;
}

#line 333 "boostrap/stage0/ReCode.c"
struct Comment_Token* Comment_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 334 "boostrap/stage0/ReCode.c"
    return (struct Comment_Token*) Token__create_kind(TOKEN_KIND__COMMENT, sizeof(struct Comment_Token), location, lexeme);
}

#line 341 "boostrap/stage0/ReCode.c"
struct End_Of_File_Token* End_Of_File_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 342 "boostrap/stage0/ReCode.c"
    return (struct End_Of_File_Token*) Token__create_kind(TOKEN_KIND__END_OF_FILE, sizeof(struct End_Of_File_Token), location, lexeme);
}

#line 349 "boostrap/stage0/ReCode.c"
struct End_Of_Line_Token* End_Of_Line_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 350 "boostrap/stage0/ReCode.c"
    return (struct End_Of_Line_Token*) Token__create_kind(TOKEN_KIND__END_OF_LINE, sizeof(struct End_Of_Line_Token), location, lexeme);
}

#line 357 "boostrap/stage0/ReCode.c"
struct Error_Token* Error_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 358 "boostrap/stage0/ReCode.c"
    return (struct Error_Token*) Token__create_kind(TOKEN_KIND__ERROR, sizeof(struct Error_Token), location, lexeme);
}

#line 365 "boostrap/stage0/ReCode.c"
struct Identifier_Token* Identifier_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 366 "boostrap/stage0/ReCode.c"
    return (struct Identifier_Token*) Token__create_kind(TOKEN_KIND__IDENTIFIER, sizeof(struct Identifier_Token), location, lexeme);
}

#line 374 "boostrap/stage0/ReCode.c"
struct Integer_Token* Integer_Token__create(struct Source_Location* location, struct String* lexeme, uint64_t value) {
#line 375 "boostrap/stage0/ReCode.c"
    struct Integer_Token* token = (struct Integer_Token*) Token__create_kind(TOKEN_KIND__INTEGER, sizeof(struct Integer_Token), location, lexeme);
#line 376 "boostrap/stage0/ReCode.c"
    token->value = value;
#line 377 "boostrap/stage0/ReCode.c"
    return token;
}

#line 384 "boostrap/stage0/ReCode.c"
struct Other_Token* Other_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 385 "boostrap/stage0/ReCode.c"
    return (struct Other_Token*) Token__create_kind(TOKEN_KIND__OTHER, sizeof(struct Other_Token), location, lexeme);
}

#line 393 "boostrap/stage0/ReCode.c"
struct Space_Token* Space_Token__create(struct Source_Location* location, struct String* lexeme, uint16_t count) {
#line 394 "boostrap/stage0/ReCode.c"
    struct Space_Token* token = (struct Space_Token*) Token__create_kind(TOKEN_KIND__SPACE, sizeof(struct Space_Token), location, lexeme);
#line 395 "boostrap/stage0/ReCode.c"
    token->count = count;
#line 396 "boostrap/stage0/ReCode.c"
    return token;
}

#line 404 "boostrap/stage0/ReCode.c"
struct String_Token* String_Token__create(struct Source_Location* location, struct String* lexeme, struct String* value) {
#line 405 "boostrap/stage0/ReCode.c"
    struct String_Token* token = (struct String_Token*) Token__create_kind(TOKEN_KIND__STRING, sizeof(struct String_Token), location, lexeme);
#line 406 "boostrap/stage0/ReCode.c"
    token->value = value;
#line 407 "boostrap/stage0/ReCode.c"
    return token;
}

#line 410 "boostrap/stage0/ReCode.c"
bool Token__is_anything(struct Token* self) {
#line 411 "boostrap/stage0/ReCode.c"
    return self != NULL;
}

#line 414 "boostrap/stage0/ReCode.c"
bool Token__is_character(struct Token* self) {
#line 415 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__CHARACTER;
}

#line 418 "boostrap/stage0/ReCode.c"
bool Token__is_comment(struct Token* self) {
#line 419 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__COMMENT;
}

#line 422 "boostrap/stage0/ReCode.c"
bool Token__is_end_of_file(struct Token* self) {
#line 423 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__END_OF_FILE;
}

#line 426 "boostrap/stage0/ReCode.c"
bool Token__is_end_of_line(struct Token* self) {
#line 427 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__END_OF_LINE || self->kind == TOKEN_KIND__END_OF_FILE;
}

#line 430 "boostrap/stage0/ReCode.c"
bool Token__is_identifier(struct Token* self) {
#line 431 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__IDENTIFIER;
}

#line 434 "boostrap/stage0/ReCode.c"
bool Token__is_integer(struct Token* self) {
#line 435 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__INTEGER;
}

#line 438 "boostrap/stage0/ReCode.c"
bool Token__is_keyword(struct Token* self, char* lexeme) {
#line 439 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

#line 442 "boostrap/stage0/ReCode.c"
bool Token__is_break(struct Token* self) {
#line 443 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "break");
}

#line 446 "boostrap/stage0/ReCode.c"
bool Token__is_else(struct Token* self) {
#line 447 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "else");
}

#line 450 "boostrap/stage0/ReCode.c"
bool Token__is_enum(struct Token* self) {
#line 451 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "enum");
}

#line 454 "boostrap/stage0/ReCode.c"
bool Token__is_extern(struct Token* self) {
#line 455 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "extern");
}

#line 458 "boostrap/stage0/ReCode.c"
bool Token__is_false(struct Token* self) {
#line 459 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "false");
}

#line 462 "boostrap/stage0/ReCode.c"
bool Token__is_if(struct Token* self) {
#line 463 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "if");
}

#line 466 "boostrap/stage0/ReCode.c"
bool Token__is_null(struct Token* self) {
#line 467 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "null");
}

#line 470 "boostrap/stage0/ReCode.c"
bool Token__is_return(struct Token* self) {
#line 471 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "return");
}

#line 474 "boostrap/stage0/ReCode.c"
bool Token__is_sizeof(struct Token* self) {
#line 475 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "sizeof");
}

#line 478 "boostrap/stage0/ReCode.c"
bool Token__is_struct(struct Token* self) {
#line 479 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "struct");
}

#line 482 "boostrap/stage0/ReCode.c"
bool Token__is_true(struct Token* self) {
#line 483 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "true");
}

#line 486 "boostrap/stage0/ReCode.c"
bool Token__is_typedef(struct Token* self) {
#line 487 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "typedef");
}

#line 490 "boostrap/stage0/ReCode.c"
bool Token__is_while(struct Token* self) {
#line 491 "boostrap/stage0/ReCode.c"
    return Token__is_keyword(self, "while");
}

#line 494 "boostrap/stage0/ReCode.c"
bool Token__is_other(struct Token* self, char* lexeme) {
#line 495 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__OTHER && String__equals_cstring(self->lexeme, lexeme);
}

#line 498 "boostrap/stage0/ReCode.c"
bool Token__is_ampersand(struct Token* self) {
#line 499 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "&");
}

#line 502 "boostrap/stage0/ReCode.c"
bool Token__is_asterisk(struct Token* self) {
#line 503 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "*");
}

#line 506 "boostrap/stage0/ReCode.c"
bool Token__is_closing_brace(struct Token* self) {
#line 507 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "}");
}

#line 510 "boostrap/stage0/ReCode.c"
bool Token__is_closing_bracket(struct Token* self) {
#line 511 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "]");
}

#line 514 "boostrap/stage0/ReCode.c"
bool Token__is_closing_paren(struct Token* self) {
#line 515 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, ")");
}

#line 518 "boostrap/stage0/ReCode.c"
bool Token__is_comma(struct Token* self) {
#line 519 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, ",");
}

#line 522 "boostrap/stage0/ReCode.c"
bool Token__is_dot(struct Token* self) {
#line 523 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, ".");
}

#line 526 "boostrap/stage0/ReCode.c"
bool Token__is_equals(struct Token* self) {
#line 527 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "=");
}

#line 530 "boostrap/stage0/ReCode.c"
bool Token__is_exclamation_mark(struct Token* self) {
#line 531 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "!");
}

#line 534 "boostrap/stage0/ReCode.c"
bool Token__is_greater_than(struct Token* self) {
#line 535 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, ">");
}

#line 538 "boostrap/stage0/ReCode.c"
bool Token__is_hash(struct Token* self) {
#line 539 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "#");
}

#line 542 "boostrap/stage0/ReCode.c"
bool Token__is_less_than(struct Token* self) {
#line 543 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "<");
}

#line 546 "boostrap/stage0/ReCode.c"
bool Token__is_minus(struct Token* self) {
#line 547 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "-");
}

#line 550 "boostrap/stage0/ReCode.c"
bool Token__is_opening_brace(struct Token* self) {
#line 551 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "{");
}

#line 554 "boostrap/stage0/ReCode.c"
bool Token__is_opening_bracket(struct Token* self) {
#line 555 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "[");
}

#line 558 "boostrap/stage0/ReCode.c"
bool Token__is_opening_paren(struct Token* self) {
#line 559 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "(");
}

#line 562 "boostrap/stage0/ReCode.c"
bool Token__is_percent(struct Token* self) {
#line 563 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "%");
}

#line 566 "boostrap/stage0/ReCode.c"
bool Token__is_plus(struct Token* self) {
#line 567 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "+");
}

#line 570 "boostrap/stage0/ReCode.c"
bool Token__is_semicolon(struct Token* self) {
#line 571 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, ";");
}

#line 574 "boostrap/stage0/ReCode.c"
bool Token__is_slash(struct Token* self) {
#line 575 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "/");
}

#line 578 "boostrap/stage0/ReCode.c"
bool Token__is_vertical_bar(struct Token* self) {
#line 579 "boostrap/stage0/ReCode.c"
    return Token__is_other(self, "|");
}

#line 582 "boostrap/stage0/ReCode.c"
bool Token__is_space(struct Token* self) {
#line 583 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__SPACE;
}

#line 586 "boostrap/stage0/ReCode.c"
bool Token__is_string(struct Token* self) {
#line 587 "boostrap/stage0/ReCode.c"
    return self->kind == TOKEN_KIND__STRING;
}

#line 590 "boostrap/stage0/ReCode.c"
void File__write_token(struct File* stream, struct Token* token) {
#line 591 "boostrap/stage0/ReCode.c"
    bool colored = token->kind == TOKEN_KIND__COMMENT || token->kind == TOKEN_KIND__ERROR || token->kind == TOKEN_KIND__OTHER;
#line 592 "boostrap/stage0/ReCode.c"
    if (colored) {
#line 593 "boostrap/stage0/ReCode.c"
        if (token->kind == TOKEN_KIND__OTHER) {
#line 594 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\33[2;33m");
        } else if (token->kind == TOKEN_KIND__COMMENT) {
#line 596 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\33[2;37m");
        } else if (token->kind == TOKEN_KIND__ERROR) {
#line 598 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\33[2;31m");
        }
    }
#line 601 "boostrap/stage0/ReCode.c"
    File__write_string(stream, token->lexeme);
#line 602 "boostrap/stage0/ReCode.c"
    if (colored) {
#line 603 "boostrap/stage0/ReCode.c"
        File__write_cstring(stream, "\33[0m");
    }
}

#line 618 "boostrap/stage0/ReCode.c"
char Scanner__peek_char(struct Scanner* self) {
#line 619 "boostrap/stage0/ReCode.c"
    return self->source->content->data[self->current_char_index];
}

#line 622 "boostrap/stage0/ReCode.c"
char Scanner__next_char(struct Scanner* self) {
#line 623 "boostrap/stage0/ReCode.c"
    char next_char = Scanner__peek_char(self);
#line 624 "boostrap/stage0/ReCode.c"
    if (next_char != '\0') {
#line 625 "boostrap/stage0/ReCode.c"
        self->current_char_index = self->current_char_index + (size_t) 1;
#line 626 "boostrap/stage0/ReCode.c"
        if (next_char == '\n') {
#line 627 "boostrap/stage0/ReCode.c"
            self->current_line = self->current_line + (uint16_t) 1;
#line 628 "boostrap/stage0/ReCode.c"
            self->current_column = (uint16_t) 1;
        } else {
#line 630 "boostrap/stage0/ReCode.c"
            self->current_column = self->current_column + (uint16_t) 1;
        }
    }
#line 633 "boostrap/stage0/ReCode.c"
    return next_char;
}

#line 636 "boostrap/stage0/ReCode.c"
char escape_char_value(char c) {
#line 637 "boostrap/stage0/ReCode.c"
    if (c == 'n') {
#line 638 "boostrap/stage0/ReCode.c"
        return '\n';
    }
#line 640 "boostrap/stage0/ReCode.c"
    if (c == '\"') {
#line 641 "boostrap/stage0/ReCode.c"
        return '\"';
    }
#line 643 "boostrap/stage0/ReCode.c"
    if (c == '\'') {
#line 644 "boostrap/stage0/ReCode.c"
        return '\'';
    }
#line 646 "boostrap/stage0/ReCode.c"
    if (c == '\\') {
#line 647 "boostrap/stage0/ReCode.c"
        return '\\';
    }
#line 649 "boostrap/stage0/ReCode.c"
    if (c == 't') {
#line 650 "boostrap/stage0/ReCode.c"
        return '\t';
    }
#line 652 "boostrap/stage0/ReCode.c"
    if (c == '0') {
#line 653 "boostrap/stage0/ReCode.c"
        return '\0';
    }
#line 655 "boostrap/stage0/ReCode.c"
    if (c == 'e') {
#line 656 "boostrap/stage0/ReCode.c"
        return '\33';
    }
#line 658 "boostrap/stage0/ReCode.c"
    return (char) -1;
}

#line 661 "boostrap/stage0/ReCode.c"
bool char_is_end_of_line(char c) {
#line 662 "boostrap/stage0/ReCode.c"
    return c == '\n' || c == '\0';
}

#line 665 "boostrap/stage0/ReCode.c"
struct Token* Scanner__scan_character_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 666 "boostrap/stage0/ReCode.c"
    if (Scanner__next_char(self) != '\'') {
#line 667 "boostrap/stage0/ReCode.c"
        Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 668 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 670 "boostrap/stage0/ReCode.c"
    String__append_char(token_lexeme, '\'');
#line 672 "boostrap/stage0/ReCode.c"
    char next_char = Scanner__peek_char(self);
#line 673 "boostrap/stage0/ReCode.c"
    if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 674 "boostrap/stage0/ReCode.c"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 677 "boostrap/stage0/ReCode.c"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 678 "boostrap/stage0/ReCode.c"
    char value = next_char;
#line 680 "boostrap/stage0/ReCode.c"
    if (value == '\'') {
#line 681 "boostrap/stage0/ReCode.c"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 684 "boostrap/stage0/ReCode.c"
    if (value == '\\') {
#line 685 "boostrap/stage0/ReCode.c"
        next_char = Scanner__peek_char(self);
#line 686 "boostrap/stage0/ReCode.c"
        if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 687 "boostrap/stage0/ReCode.c"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
#line 690 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 692 "boostrap/stage0/ReCode.c"
        value = escape_char_value(next_char);
#line 693 "boostrap/stage0/ReCode.c"
        if (value == (char) -1) {
#line 694 "boostrap/stage0/ReCode.c"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
    }
#line 698 "boostrap/stage0/ReCode.c"
    if (Scanner__peek_char(self) != '\'') {
#line 699 "boostrap/stage0/ReCode.c"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 702 "boostrap/stage0/ReCode.c"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 703 "boostrap/stage0/ReCode.c"
    return (struct Token*) Character_Token__create(source_location, token_lexeme, value);
}

#line 706 "boostrap/stage0/ReCode.c"
struct Token* Scanner__scan_comment_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 707 "boostrap/stage0/ReCode.c"
    while (!char_is_end_of_line(Scanner__peek_char(self))) {
#line 708 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 710 "boostrap/stage0/ReCode.c"
    return (struct Token*) Comment_Token__create(source_location, token_lexeme);
}

#line 713 "boostrap/stage0/ReCode.c"
bool char_is_identifier_start(char c) {
#line 714 "boostrap/stage0/ReCode.c"
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

#line 717 "boostrap/stage0/ReCode.c"
bool char_is_identifier_letter(char c) {
#line 718 "boostrap/stage0/ReCode.c"
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

#line 721 "boostrap/stage0/ReCode.c"
struct Token* Scanner__scan_identifier_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 722 "boostrap/stage0/ReCode.c"
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
#line 723 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 725 "boostrap/stage0/ReCode.c"
    return (struct Token*) Identifier_Token__create(source_location, token_lexeme);
}

#line 728 "boostrap/stage0/ReCode.c"
bool char_is_digit(char c) {
#line 729 "boostrap/stage0/ReCode.c"
    return c >= '0' && c <= '9';
}

#line 732 "boostrap/stage0/ReCode.c"
struct Token* Scanner__scan_integer_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 733 "boostrap/stage0/ReCode.c"
    uint64_t value = (uint64_t) 0;
#line 734 "boostrap/stage0/ReCode.c"
    while (char_is_digit(Scanner__peek_char(self))) {
#line 735 "boostrap/stage0/ReCode.c"
        char c = Scanner__next_char(self);
#line 736 "boostrap/stage0/ReCode.c"
        value = value * (uint64_t) 10 + (uint64_t) (c - '0');
#line 737 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, c);
    }
#line 739 "boostrap/stage0/ReCode.c"
    return (struct Token*) Integer_Token__create(source_location, token_lexeme, value);
}

#line 742 "boostrap/stage0/ReCode.c"
bool char_is_space(char c) {
#line 743 "boostrap/stage0/ReCode.c"
    return c == ' ';
}

#line 746 "boostrap/stage0/ReCode.c"
struct Token* Scanner__scan_space_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 747 "boostrap/stage0/ReCode.c"
    uint16_t count = (uint16_t) 0;
#line 748 "boostrap/stage0/ReCode.c"
    while (char_is_space(Scanner__peek_char(self))) {
#line 749 "boostrap/stage0/ReCode.c"
        count = count + (uint16_t) 1;
#line 750 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 752 "boostrap/stage0/ReCode.c"
    return (struct Token*) Space_Token__create(source_location, token_lexeme, count);
}

#line 755 "boostrap/stage0/ReCode.c"
struct Token* Scanner__scan_string_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 756 "boostrap/stage0/ReCode.c"
    if (Scanner__next_char(self) != '\"') {
#line 757 "boostrap/stage0/ReCode.c"
        Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 758 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 760 "boostrap/stage0/ReCode.c"
    String__append_char(token_lexeme, '\"');
#line 762 "boostrap/stage0/ReCode.c"
    struct String* value = String__create();
#line 764 "boostrap/stage0/ReCode.c"
    while (true) {
#line 765 "boostrap/stage0/ReCode.c"
        char next_char = Scanner__peek_char(self);
#line 766 "boostrap/stage0/ReCode.c"
        if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 767 "boostrap/stage0/ReCode.c"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
#line 770 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 772 "boostrap/stage0/ReCode.c"
        if (next_char == '\"') {
#line 773 "boostrap/stage0/ReCode.c"
            return (struct Token*) String_Token__create(source_location, token_lexeme, value);
        }
#line 776 "boostrap/stage0/ReCode.c"
        if (next_char == '\\') {
#line 777 "boostrap/stage0/ReCode.c"
            next_char = Scanner__peek_char(self);
#line 778 "boostrap/stage0/ReCode.c"
            if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 779 "boostrap/stage0/ReCode.c"
                return (struct Token*) Error_Token__create(source_location, token_lexeme);
            }
#line 782 "boostrap/stage0/ReCode.c"
            String__append_char(token_lexeme, Scanner__next_char(self));
#line 784 "boostrap/stage0/ReCode.c"
            next_char = escape_char_value(next_char);
#line 785 "boostrap/stage0/ReCode.c"
            if (next_char == ((char) -1)) {
#line 786 "boostrap/stage0/ReCode.c"
                return (struct Token*) Error_Token__create(source_location, token_lexeme);
            }
        }
#line 790 "boostrap/stage0/ReCode.c"
        String__append_char(value, next_char);
    }
}

#line 794 "boostrap/stage0/ReCode.c"
struct Token* Scanner__scan_token(struct Scanner* self) {
#line 795 "boostrap/stage0/ReCode.c"
    struct Source_Location* source_location = Source_Location__create(self->source, self->current_line, self->current_column);
#line 796 "boostrap/stage0/ReCode.c"
    struct String* token_lexeme = String__create();
#line 798 "boostrap/stage0/ReCode.c"
    char next_char = Scanner__peek_char(self);
#line 800 "boostrap/stage0/ReCode.c"
    if (char_is_identifier_start(next_char)) {
#line 801 "boostrap/stage0/ReCode.c"
        return Scanner__scan_identifier_token(self, source_location, token_lexeme);
    }
#line 804 "boostrap/stage0/ReCode.c"
    if (char_is_digit(next_char)) {
#line 805 "boostrap/stage0/ReCode.c"
        return Scanner__scan_integer_token(self, source_location, token_lexeme);
    }
#line 808 "boostrap/stage0/ReCode.c"
    if (char_is_space(next_char)) {
#line 809 "boostrap/stage0/ReCode.c"
        return Scanner__scan_space_token(self, source_location, token_lexeme);
    }
#line 812 "boostrap/stage0/ReCode.c"
    if (next_char == '\'') {
#line 813 "boostrap/stage0/ReCode.c"
        return Scanner__scan_character_token(self, source_location, token_lexeme);
    }
#line 816 "boostrap/stage0/ReCode.c"
    if (next_char == '\"') {
#line 817 "boostrap/stage0/ReCode.c"
        return Scanner__scan_string_token(self, source_location, token_lexeme);
    }
#line 820 "boostrap/stage0/ReCode.c"
    if (next_char == '/') {
#line 821 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 822 "boostrap/stage0/ReCode.c"
        if (Scanner__peek_char(self) == '/') {
#line 823 "boostrap/stage0/ReCode.c"
            return Scanner__scan_comment_token(self, source_location, token_lexeme);
        }
#line 826 "boostrap/stage0/ReCode.c"
        return (struct Token*) Other_Token__create(source_location, token_lexeme);
    }
#line 829 "boostrap/stage0/ReCode.c"
    if (next_char == '\n') {
#line 830 "boostrap/stage0/ReCode.c"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 831 "boostrap/stage0/ReCode.c"
        return (struct Token*) End_Of_Line_Token__create(source_location, token_lexeme);
    }
#line 834 "boostrap/stage0/ReCode.c"
    if (next_char == '\0') {
#line 835 "boostrap/stage0/ReCode.c"
        return (struct Token*) End_Of_File_Token__create(source_location, token_lexeme);
    }
#line 838 "boostrap/stage0/ReCode.c"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 839 "boostrap/stage0/ReCode.c"
    return (struct Token*) Other_Token__create(source_location, token_lexeme);
}

#line 842 "boostrap/stage0/ReCode.c"
struct Token* Scanner__next_token(struct Scanner* self) {
#line 843 "boostrap/stage0/ReCode.c"
    if (self->current_token->next_token == NULL) {
#line 844 "boostrap/stage0/ReCode.c"
        self->current_token->next_token = Scanner__scan_token(self);
    }
#line 846 "boostrap/stage0/ReCode.c"
    self->current_token = self->current_token->next_token;
#line 847 "boostrap/stage0/ReCode.c"
    return self->current_token;
}

#line 850 "boostrap/stage0/ReCode.c"
struct Token* Scanner__peek_token(struct Scanner* self, uint8_t offset) {
#line 851 "boostrap/stage0/ReCode.c"
    struct Token* token = self->current_token;
#line 852 "boostrap/stage0/ReCode.c"
    while (offset > (uint8_t) 0) {
#line 853 "boostrap/stage0/ReCode.c"
        if (token->next_token == NULL) {
#line 854 "boostrap/stage0/ReCode.c"
            token->next_token = Scanner__scan_token(self);
        }
#line 856 "boostrap/stage0/ReCode.c"
        token = token->next_token;
#line 857 "boostrap/stage0/ReCode.c"
        offset = offset - (uint8_t) 1;
    }
#line 859 "boostrap/stage0/ReCode.c"
    return token;
}

#line 862 "boostrap/stage0/ReCode.c"
struct Scanner* Scanner__create(struct Source* source) {
#line 863 "boostrap/stage0/ReCode.c"
    struct Scanner* scanner = (struct Scanner*) malloc(sizeof(struct Scanner));
#line 864 "boostrap/stage0/ReCode.c"
    scanner->source = source;
#line 865 "boostrap/stage0/ReCode.c"
    scanner->current_char_index = (size_t) 0;
#line 866 "boostrap/stage0/ReCode.c"
    scanner->current_line = (uint16_t) 1;
#line 867 "boostrap/stage0/ReCode.c"
    scanner->current_column = (uint16_t) 1;
#line 869 "boostrap/stage0/ReCode.c"
    scanner->current_token = Scanner__scan_token(scanner);
#line 871 "boostrap/stage0/ReCode.c"
    return scanner;
}

#line 896 "boostrap/stage0/ReCode.c"
struct Parsed_Type* Parsed_Type__create_kind(enum Parsed_Type_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 897 "boostrap/stage0/ReCode.c"
    struct Parsed_Type* type = (struct Parsed_Type*) malloc(kind_size);
#line 898 "boostrap/stage0/ReCode.c"
    type->kind = kind;
#line 899 "boostrap/stage0/ReCode.c"
    type->location = location;
#line 900 "boostrap/stage0/ReCode.c"
    return type;
}

#line 908 "boostrap/stage0/ReCode.c"
struct Parsed_Type* Parsed_Named_Type__create(struct Token* name) {
#line 909 "boostrap/stage0/ReCode.c"
    struct Parsed_Named_Type* type = (struct Parsed_Named_Type*) Parsed_Type__create_kind(PARSED_TYPE_KIND__NAMED, sizeof(struct Parsed_Named_Type), name->location);
#line 910 "boostrap/stage0/ReCode.c"
    type->name = name->lexeme;
#line 911 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Type*) type;
}

#line 919 "boostrap/stage0/ReCode.c"
struct Parsed_Type* Parsed_Pointer_Type__create(struct Parsed_Type* other_type) {
#line 920 "boostrap/stage0/ReCode.c"
    struct Parsed_Pointer_Type* type = (struct Parsed_Pointer_Type*) Parsed_Type__create_kind(PARSED_TYPE_KIND__POINTER, sizeof(struct Parsed_Pointer_Type), other_type->location);
#line 921 "boostrap/stage0/ReCode.c"
    type->other_type = other_type;
#line 922 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Type*) type;
}

#line 930 "boostrap/stage0/ReCode.c"
struct Parsed_Type* Parsed_Struct_Type__create(struct Source_Location* location, struct Parsed_Type* other_type) {
#line 931 "boostrap/stage0/ReCode.c"
    struct Parsed_Struct_Type* type = (struct Parsed_Struct_Type*) Parsed_Type__create_kind(PARSED_TYPE_KIND__STRUCT, sizeof(struct Parsed_Struct_Type), location);
#line 932 "boostrap/stage0/ReCode.c"
    type->other_type = other_type;
#line 933 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Type*) type;
}

#line 972 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parsed_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 973 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = (struct Parsed_Expression*) malloc(kind_size);
#line 974 "boostrap/stage0/ReCode.c"
    expression->kind = kind;
#line 975 "boostrap/stage0/ReCode.c"
    expression->location = location;
#line 976 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 985 "boostrap/stage0/ReCode.c"
struct Parsed_Binary_Expression* Parsed_Binary_Expression__create_kind(enum Parsed_Expression_Kind kind, struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 986 "boostrap/stage0/ReCode.c"
    struct Parsed_Binary_Expression* expression = (struct Parsed_Binary_Expression*) Parsed_Expression__create_kind(kind, sizeof(struct Parsed_Binary_Expression), left_expression->location);
#line 987 "boostrap/stage0/ReCode.c"
    expression->left_expression = left_expression;
#line 988 "boostrap/stage0/ReCode.c"
    expression->right_expression = right_expression;
#line 989 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 997 "boostrap/stage0/ReCode.c"
struct Parsed_Unary_Expression* Parsed_Unary_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 998 "boostrap/stage0/ReCode.c"
    struct Parsed_Unary_Expression* expression = (struct Parsed_Unary_Expression*) Parsed_Expression__create_kind(kind, kind_size, location);
#line 999 "boostrap/stage0/ReCode.c"
    expression->other_expression = other_expression;
#line 1000 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1008 "boostrap/stage0/ReCode.c"
struct Parsed_Literal_Expression* Parsed_Literal_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Token* literal) {
#line 1009 "boostrap/stage0/ReCode.c"
    struct Parsed_Literal_Expression* expression = (struct Parsed_Literal_Expression*) Parsed_Expression__create_kind(kind, kind_size, literal->location);
#line 1010 "boostrap/stage0/ReCode.c"
    expression->literal = literal;
#line 1011 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1018 "boostrap/stage0/ReCode.c"
struct Parsed_Add_Expression* Parsed_Add_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1019 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Add_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__ADD, left_expression, right_expression);
}

#line 1026 "boostrap/stage0/ReCode.c"
struct Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1027 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Address_Of_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__ADDRESS_OF, sizeof(struct Parsed_Address_Of_Expression), location, other_expression);
}

#line 1036 "boostrap/stage0/ReCode.c"
struct Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(struct Parsed_Expression* array_expression, struct Parsed_Expression* index_expression) {
#line 1037 "boostrap/stage0/ReCode.c"
    struct Parsed_Array_Access_Expression* expression = (struct Parsed_Array_Access_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__ARRAY_ACCESS, sizeof(struct Parsed_Array_Access_Expression), array_expression->location);
#line 1038 "boostrap/stage0/ReCode.c"
    expression->array_expression = array_expression;
#line 1039 "boostrap/stage0/ReCode.c"
    expression->index_expression = index_expression;
#line 1040 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1048 "boostrap/stage0/ReCode.c"
struct Parsed_Bool_Expression* Parsed_Bool_Expression__create(struct Token* literal, bool value) {
#line 1049 "boostrap/stage0/ReCode.c"
    struct Parsed_Bool_Expression* expression = (struct Parsed_Bool_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__BOOL, sizeof(struct Parsed_Bool_Expression), literal);
#line 1050 "boostrap/stage0/ReCode.c"
    expression->value = value;
#line 1051 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1059 "boostrap/stage0/ReCode.c"
struct Parsed_Call_Argument* Parsed_Call_Argument__create(struct Parsed_Expression* expression) {
#line 1060 "boostrap/stage0/ReCode.c"
    struct Parsed_Call_Argument* argument = (struct Parsed_Call_Argument*) malloc(sizeof(struct Parsed_Call_Argument));
#line 1061 "boostrap/stage0/ReCode.c"
    argument->expression = expression;
#line 1062 "boostrap/stage0/ReCode.c"
    argument->next_argument = NULL;
#line 1063 "boostrap/stage0/ReCode.c"
    return argument;
}

#line 1072 "boostrap/stage0/ReCode.c"
struct Parsed_Call_Expression* Parsed_Call_Expression__create(struct Parsed_Expression* callee_expression) {
#line 1073 "boostrap/stage0/ReCode.c"
    struct Parsed_Call_Expression* expression = (struct Parsed_Call_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__CALL, sizeof(struct Parsed_Call_Expression), callee_expression->location);
#line 1074 "boostrap/stage0/ReCode.c"
    expression->callee_expression = callee_expression;
#line 1075 "boostrap/stage0/ReCode.c"
    expression->first_argument = NULL;
#line 1076 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1084 "boostrap/stage0/ReCode.c"
struct Parsed_Cast_Expression* Parsed_Cast_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression, struct Parsed_Type* type) {
#line 1085 "boostrap/stage0/ReCode.c"
    struct Parsed_Cast_Expression* expression = (struct Parsed_Cast_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__CAST, sizeof(struct Parsed_Cast_Expression), location, other_expression);
#line 1086 "boostrap/stage0/ReCode.c"
    expression->type = type;
#line 1087 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1095 "boostrap/stage0/ReCode.c"
struct Parsed_Character_Expression* Parsed_Character_Expression__create(struct Character_Token* literal) {
#line 1096 "boostrap/stage0/ReCode.c"
    struct Parsed_Character_Expression* expression = (struct Parsed_Character_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__CHARACTER, sizeof(struct Parsed_Character_Expression), (struct Token*) literal);
#line 1097 "boostrap/stage0/ReCode.c"
    expression->value = literal->value;
#line 1098 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1105 "boostrap/stage0/ReCode.c"
struct Parsed_Divide_Expression* Parsed_Divide_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1106 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Divide_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__DIVIDE, left_expression, right_expression);
}

#line 1113 "boostrap/stage0/ReCode.c"
struct Parsed_Equals_Expression* Parsed_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1114 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__EQUALS, left_expression, right_expression);
}

#line 1121 "boostrap/stage0/ReCode.c"
struct Parsed_Greater_Expression* Parsed_Greater_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1122 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Greater_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__GREATER, left_expression, right_expression);
}

#line 1129 "boostrap/stage0/ReCode.c"
struct Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1130 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Greater_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS, left_expression, right_expression);
}

#line 1138 "boostrap/stage0/ReCode.c"
struct Parsed_Group_Expression* Parsed_Group_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1139 "boostrap/stage0/ReCode.c"
    struct Parsed_Group_Expression* expression = (struct Parsed_Group_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__GROUP, sizeof(struct Parsed_Group_Expression), location);
#line 1140 "boostrap/stage0/ReCode.c"
    expression->other_expression = other_expression;
#line 1141 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1149 "boostrap/stage0/ReCode.c"
struct Parsed_Integer_Expression* Parsed_Integer_Expression__create(struct Integer_Token* literal) {
#line 1150 "boostrap/stage0/ReCode.c"
    struct Parsed_Integer_Expression* expression = (struct Parsed_Integer_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__INTEGER, sizeof(struct Parsed_Integer_Expression), (struct Token*) literal);
#line 1151 "boostrap/stage0/ReCode.c"
    expression->value = literal->value;
#line 1152 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1159 "boostrap/stage0/ReCode.c"
struct Parsed_Less_Expression* Parsed_Less_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1160 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Less_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LESS, left_expression, right_expression);
}

#line 1167 "boostrap/stage0/ReCode.c"
struct Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1168 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Less_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LESS_OR_EQUALS, left_expression, right_expression);
}

#line 1175 "boostrap/stage0/ReCode.c"
struct Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1176 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Logic_And_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LOGIC_AND, left_expression, right_expression);
}

#line 1183 "boostrap/stage0/ReCode.c"
struct Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1184 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Logic_Or_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LOGIC_OR, left_expression, right_expression);
}

#line 1193 "boostrap/stage0/ReCode.c"
struct Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(struct Parsed_Expression* object_expression, struct Token* member_name) {
#line 1194 "boostrap/stage0/ReCode.c"
    struct Parsed_Member_Access_Expression* expression = (struct Parsed_Member_Access_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__MEMBER_ACCESS, sizeof(struct Parsed_Member_Access_Expression), object_expression->location);
#line 1195 "boostrap/stage0/ReCode.c"
    expression->object_expression = object_expression;
#line 1196 "boostrap/stage0/ReCode.c"
    expression->member_name = member_name;
#line 1197 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1204 "boostrap/stage0/ReCode.c"
struct Parsed_Minus_Expression* Parsed_Minus_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1205 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Minus_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__MINUS, sizeof(struct Parsed_Minus_Expression), location, other_expression);
}

#line 1212 "boostrap/stage0/ReCode.c"
struct Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1213 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Modulo_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__MODULO, left_expression, right_expression);
}

#line 1220 "boostrap/stage0/ReCode.c"
struct Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1221 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Multiply_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__MULTIPLY, left_expression, right_expression);
}

#line 1228 "boostrap/stage0/ReCode.c"
struct Parsed_Not_Expression* Parsed_Not_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1229 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Not_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__NOT, sizeof(struct Parsed_Not_Expression), location, other_expression);
}

#line 1236 "boostrap/stage0/ReCode.c"
struct Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1237 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Not_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__NOT_EQUALS, left_expression, right_expression);
}

#line 1244 "boostrap/stage0/ReCode.c"
struct Parsed_Null_Expression* Parsed_Null_Expression__create(struct Token* literal) {
#line 1245 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Null_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__NULL, sizeof(struct Parsed_Null_Expression), literal);
}

#line 1253 "boostrap/stage0/ReCode.c"
struct Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(struct Source_Location* location, struct Parsed_Type* type) {
#line 1254 "boostrap/stage0/ReCode.c"
    struct Parsed_Sizeof_Expression* expression = (struct Parsed_Sizeof_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__SIZEOF, sizeof(struct Parsed_Sizeof_Expression), location);
#line 1255 "boostrap/stage0/ReCode.c"
    expression->type = type;
#line 1256 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1264 "boostrap/stage0/ReCode.c"
struct Parsed_String_Expression* Parsed_String_Expression__create(struct String_Token* literal) {
#line 1265 "boostrap/stage0/ReCode.c"
    struct Parsed_String_Expression* expression = (struct Parsed_String_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__STRING, sizeof(struct Parsed_String_Expression), (struct Token*) literal);
#line 1266 "boostrap/stage0/ReCode.c"
    expression->value = literal->value;
#line 1267 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1274 "boostrap/stage0/ReCode.c"
struct Parsed_Substract_Expression* Parsed_Substract_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1275 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Substract_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__SUBSTRACT, left_expression, right_expression);
}

#line 1283 "boostrap/stage0/ReCode.c"
struct Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(struct Token* name) {
#line 1284 "boostrap/stage0/ReCode.c"
    struct Parsed_Symbol_Expression* expression = (struct Parsed_Symbol_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__SYMBOL, sizeof(struct Parsed_Symbol_Expression), name->location);
#line 1285 "boostrap/stage0/ReCode.c"
    expression->name = name;
#line 1286 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1310 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parsed_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 1311 "boostrap/stage0/ReCode.c"
    struct Parsed_Statement* statement = (struct Parsed_Statement*) malloc(kind_size);
#line 1312 "boostrap/stage0/ReCode.c"
    statement->kind = kind;
#line 1313 "boostrap/stage0/ReCode.c"
    statement->location = location;
#line 1314 "boostrap/stage0/ReCode.c"
    statement->next_statement = NULL;
#line 1315 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1323 "boostrap/stage0/ReCode.c"
struct Parsed_Named_Statement* Parsed_Named_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location, struct Token* name) {
#line 1324 "boostrap/stage0/ReCode.c"
    struct Parsed_Named_Statement* statement = (struct Parsed_Named_Statement*) Parsed_Statement__create_kind(kind, kind_size, location);
#line 1325 "boostrap/stage0/ReCode.c"
    statement->name = name;
#line 1326 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1335 "boostrap/stage0/ReCode.c"
struct Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(struct Parsed_Expression* object_expression, struct Parsed_Expression* value_expression) {
#line 1336 "boostrap/stage0/ReCode.c"
    struct Parsed_Assignment_Statement* statement = (struct Parsed_Assignment_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__ASSIGNMENT, sizeof(struct Parsed_Assignment_Statement), object_expression->location);
#line 1337 "boostrap/stage0/ReCode.c"
    statement->object_expression = object_expression;
#line 1338 "boostrap/stage0/ReCode.c"
    statement->value_expression = value_expression;
#line 1339 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1347 "boostrap/stage0/ReCode.c"
struct Parsed_Block_Statement* Parsed_Block_Statement__create(struct Source_Location* location, struct Parsed_Statements* statements) {
#line 1348 "boostrap/stage0/ReCode.c"
    struct Parsed_Block_Statement* statement = (struct Parsed_Block_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__BLOCK, sizeof(struct Parsed_Block_Statement), location);
#line 1349 "boostrap/stage0/ReCode.c"
    statement->statements = statements;
#line 1350 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1357 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parsed_Break_Statement__create(struct Source_Location* location) {
#line 1358 "boostrap/stage0/ReCode.c"
    return Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__BREAK, sizeof(struct Parsed_Break_Statement), location);
}

#line 1366 "boostrap/stage0/ReCode.c"
struct Parsed_Enum_Member* Parsed_Enum_Member__create(struct Token* name) {
#line 1367 "boostrap/stage0/ReCode.c"
    struct Parsed_Enum_Member* member = (struct Parsed_Enum_Member*) malloc(sizeof(struct Parsed_Enum_Member));
#line 1368 "boostrap/stage0/ReCode.c"
    member->name = name;
#line 1369 "boostrap/stage0/ReCode.c"
    member->next_member = NULL;
#line 1370 "boostrap/stage0/ReCode.c"
    return member;
}

#line 1378 "boostrap/stage0/ReCode.c"
struct Parsed_Enum_Statement* Parsed_Enum_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1379 "boostrap/stage0/ReCode.c"
    struct Parsed_Enum_Statement* statement = (struct Parsed_Enum_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__ENUM, sizeof(struct Parsed_Enum_Statement), location, name);
#line 1380 "boostrap/stage0/ReCode.c"
    statement->first_member = NULL;
#line 1381 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1389 "boostrap/stage0/ReCode.c"
struct Parsed_Expression_Statement* Parsed_Expression_Statement__create(struct Parsed_Expression* expression) {
#line 1390 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression_Statement* statement = (struct Parsed_Expression_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__EXPRESSION, sizeof(struct Parsed_Expression_Statement), expression->location);
#line 1391 "boostrap/stage0/ReCode.c"
    statement->expression = expression;
#line 1392 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1401 "boostrap/stage0/ReCode.c"
struct Parsed_Function_Parameter* Parsed_Function_Parameter__create(struct Token* name, struct Parsed_Type* type) {
#line 1402 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Parameter* parameter = (struct Parsed_Function_Parameter*) malloc(sizeof(struct Parsed_Function_Parameter));
#line 1403 "boostrap/stage0/ReCode.c"
    parameter->name = name;
#line 1404 "boostrap/stage0/ReCode.c"
    parameter->type = type;
#line 1405 "boostrap/stage0/ReCode.c"
    parameter->next_parameter = NULL;
#line 1406 "boostrap/stage0/ReCode.c"
    return parameter;
}

#line 1417 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parsed_Function_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* resturn_type, struct Parsed_Statements* statements, bool is_external) {
#line 1418 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Statement* statement = (struct Parsed_Function_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__FUNCTION, sizeof(struct Parsed_Function_Statement), location, name);
#line 1419 "boostrap/stage0/ReCode.c"
    statement->first_parameter = first_parameter;
#line 1420 "boostrap/stage0/ReCode.c"
    statement->return_type = resturn_type;
#line 1421 "boostrap/stage0/ReCode.c"
    statement->statements = statements;
#line 1422 "boostrap/stage0/ReCode.c"
    statement->is_external = is_external;
#line 1423 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) statement;
}

#line 1432 "boostrap/stage0/ReCode.c"
struct Parsed_Function_Type_Parameter* Parsed_Function_Type_Parameter__create(struct Token* name, struct Parsed_Type* type) {
#line 1433 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Type_Parameter* parameter = (struct Parsed_Function_Type_Parameter*) malloc(sizeof(struct Parsed_Function_Type_Parameter));
#line 1434 "boostrap/stage0/ReCode.c"
    parameter->name = name;
#line 1435 "boostrap/stage0/ReCode.c"
    parameter->type = type;
#line 1436 "boostrap/stage0/ReCode.c"
    parameter->next_parameter = NULL;
#line 1437 "boostrap/stage0/ReCode.c"
    return parameter;
}

#line 1446 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parsed_Function_Type_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Type_Parameter* first_parameter, struct Parsed_Type* resturn_type) {
#line 1447 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Type_Statement* statement = (struct Parsed_Function_Type_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__FUNCTION_TYPE, sizeof(struct Parsed_Function_Type_Statement), location, name);
#line 1448 "boostrap/stage0/ReCode.c"
    statement->first_parameter = first_parameter;
#line 1449 "boostrap/stage0/ReCode.c"
    statement->return_type = resturn_type;
#line 1450 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) statement;
}

#line 1460 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parsed_If_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* true_statement, struct Parsed_Statement* false_statement) {
#line 1461 "boostrap/stage0/ReCode.c"
    struct Parsed_If_Statement* statement = (struct Parsed_If_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__IF, sizeof(struct Parsed_If_Statement), location);
#line 1462 "boostrap/stage0/ReCode.c"
    statement->condition_expression = condition_expression;
#line 1463 "boostrap/stage0/ReCode.c"
    statement->true_statement = true_statement;
#line 1464 "boostrap/stage0/ReCode.c"
    statement->false_statement = false_statement;
#line 1465 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) statement;
}

#line 1473 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parsed_Return_Statement__create(struct Source_Location* location, struct Parsed_Expression* expression) {
#line 1474 "boostrap/stage0/ReCode.c"
    struct Parsed_Return_Statement* statement = (struct Parsed_Return_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__RETURN, sizeof(struct Parsed_Return_Statement), location);
#line 1475 "boostrap/stage0/ReCode.c"
    statement->expression = expression;
#line 1476 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) statement;
}

#line 1485 "boostrap/stage0/ReCode.c"
struct Parsed_Struct_Member* Parsed_Struct_Member__create(struct Token* name, struct Parsed_Type* type) {
#line 1486 "boostrap/stage0/ReCode.c"
    struct Parsed_Struct_Member* member = (struct Parsed_Struct_Member*) malloc(sizeof(struct Parsed_Struct_Member));
#line 1487 "boostrap/stage0/ReCode.c"
    member->name = name;
#line 1488 "boostrap/stage0/ReCode.c"
    member->type = type;
#line 1489 "boostrap/stage0/ReCode.c"
    member->next_member = NULL;
#line 1490 "boostrap/stage0/ReCode.c"
    return member;
}

#line 1498 "boostrap/stage0/ReCode.c"
struct Parsed_Struct_Statement* Parsed_Struct_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1499 "boostrap/stage0/ReCode.c"
    struct Parsed_Struct_Statement* statement = (struct Parsed_Struct_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__STRUCT, sizeof(struct Parsed_Struct_Statement), location, name);
#line 1500 "boostrap/stage0/ReCode.c"
    statement->first_member = NULL;
#line 1501 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1511 "boostrap/stage0/ReCode.c"
struct Parsed_Variable_Statement* Parsed_Variable_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Type* type, bool is_external) {
#line 1512 "boostrap/stage0/ReCode.c"
    struct Parsed_Variable_Statement* statement = (struct Parsed_Variable_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__VARIABLE, sizeof(struct Parsed_Variable_Statement), location, name);
#line 1513 "boostrap/stage0/ReCode.c"
    statement->type = type;
#line 1514 "boostrap/stage0/ReCode.c"
    statement->is_external = is_external;
#line 1515 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 1524 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parsed_While_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* body_statement) {
#line 1525 "boostrap/stage0/ReCode.c"
    struct Parsed_While_Statement* statement = (struct Parsed_While_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__WHILE, sizeof(struct Parsed_While_Statement), location);
#line 1526 "boostrap/stage0/ReCode.c"
    statement->condition_expression = condition_expression;
#line 1527 "boostrap/stage0/ReCode.c"
    statement->body_statement = body_statement;
#line 1528 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) statement;
}

#line 1537 "boostrap/stage0/ReCode.c"
struct Parsed_Statements* Parsed_Statements__create(bool has_globals) {
#line 1538 "boostrap/stage0/ReCode.c"
    struct Parsed_Statements* statements = (struct Parsed_Statements*) malloc(sizeof(struct Parsed_Statements));
#line 1539 "boostrap/stage0/ReCode.c"
    statements->first_statement = NULL;
#line 1540 "boostrap/stage0/ReCode.c"
    statements->last_statement = NULL;
#line 1541 "boostrap/stage0/ReCode.c"
    statements->has_globals = has_globals;
#line 1542 "boostrap/stage0/ReCode.c"
    return statements;
}

#line 1545 "boostrap/stage0/ReCode.c"
void Parsed_Statements__append(struct Parsed_Statements* self, struct Parsed_Statement* statement) {
#line 1546 "boostrap/stage0/ReCode.c"
    if (self->first_statement == NULL) {
#line 1547 "boostrap/stage0/ReCode.c"
        self->first_statement = statement;
    } else {
#line 1549 "boostrap/stage0/ReCode.c"
        self->last_statement->next_statement = statement;
    }
#line 1551 "boostrap/stage0/ReCode.c"
    self->last_statement = statement;
}

#line 1554 "boostrap/stage0/ReCode.c"
struct Parsed_Source* Parsed_Compilation_Unit__create() {
#line 1555 "boostrap/stage0/ReCode.c"
    struct Parsed_Source* compilation_unit = (struct Parsed_Source*) malloc(sizeof(struct Parsed_Source));
#line 1556 "boostrap/stage0/ReCode.c"
    compilation_unit->statements = Parsed_Statements__create(true);
#line 1557 "boostrap/stage0/ReCode.c"
    return compilation_unit;
}

#line 1569 "boostrap/stage0/ReCode.c"
void Parser__error(struct Parser* self, struct String* message) {
#line 1570 "boostrap/stage0/ReCode.c"
    Token__error(self->scanner->current_token, message);
}

#line 1573 "boostrap/stage0/ReCode.c"
void Parser__warning(struct Parser* self, struct String* message) {
#line 1574 "boostrap/stage0/ReCode.c"
    Token__warning(self->scanner->current_token, message);
}

#line 1577 "boostrap/stage0/ReCode.c"
struct Token* Parser__peek_token(struct Parser* self, uint8_t offset) {
#line 1578 "boostrap/stage0/ReCode.c"
    return Scanner__peek_token(self->scanner, offset);
}

#line 1583 "boostrap/stage0/ReCode.c"
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self), bool second_required, bool (*third_is)(struct Token* self)) {
#line 1584 "boostrap/stage0/ReCode.c"
    uint8_t peek_offset = (uint8_t) 0;
#line 1585 "boostrap/stage0/ReCode.c"
    if (first_is(Parser__peek_token(self, peek_offset))) {
#line 1586 "boostrap/stage0/ReCode.c"
        peek_offset = peek_offset + (uint8_t) 1;
    } else if (first_required) {
#line 1588 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 1590 "boostrap/stage0/ReCode.c"
    if (second_is != NULL) {
#line 1591 "boostrap/stage0/ReCode.c"
        if (second_is(Parser__peek_token(self, peek_offset))) {
#line 1592 "boostrap/stage0/ReCode.c"
            peek_offset = peek_offset + (uint8_t) 1;
        } else if (second_required) {
#line 1594 "boostrap/stage0/ReCode.c"
            return false;
        }
    }
#line 1597 "boostrap/stage0/ReCode.c"
    if (third_is != NULL) {
#line 1598 "boostrap/stage0/ReCode.c"
        return third_is(Parser__peek_token(self, peek_offset));
    }
#line 1600 "boostrap/stage0/ReCode.c"
    return true;
}

#line 1603 "boostrap/stage0/ReCode.c"
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self)) {
#line 1604 "boostrap/stage0/ReCode.c"
    return Parser__matches_three(self, first_is, first_required, second_is, true, NULL);
}

#line 1607 "boostrap/stage0/ReCode.c"
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token* self)) {
#line 1608 "boostrap/stage0/ReCode.c"
    return Parser__matches_two(self, first_is, true, NULL);
}

#line 1611 "boostrap/stage0/ReCode.c"
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token* self)) {
#line 1612 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, check)) {
#line 1613 "boostrap/stage0/ReCode.c"
        struct Token* token = self->scanner->current_token;
#line 1614 "boostrap/stage0/ReCode.c"
        Scanner__next_token(self->scanner);
#line 1615 "boostrap/stage0/ReCode.c"
        return token;
    }
#line 1617 "boostrap/stage0/ReCode.c"
    Parser__error(self, String__create_from("Unexpected token"));
#line 1618 "boostrap/stage0/ReCode.c"
    abort();
}

#line 1621 "boostrap/stage0/ReCode.c"
void Parser__consume_comment(struct Parser* self) {
#line 1622 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_comment);
}

#line 1625 "boostrap/stage0/ReCode.c"
void Parser__consume_space(struct Parser* self, uint16_t count) {
#line 1626 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_space)) {
#line 1627 "boostrap/stage0/ReCode.c"
        struct Space_Token* token = (struct Space_Token*) Parser__consume_token(self, Token__is_space);
#line 1628 "boostrap/stage0/ReCode.c"
        if (token->count != count) {
#line 1629 "boostrap/stage0/ReCode.c"
            struct String* message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), (int16_t) token->count), " spaces where "), (int16_t) count), " were expected");
#line 1630 "boostrap/stage0/ReCode.c"
            Token__warning((struct Token*) token, message);
#line 1631 "boostrap/stage0/ReCode.c"
            String__delete(message);
        }
    } else if (count > (uint16_t) 0) {
#line 1634 "boostrap/stage0/ReCode.c"
        struct String* message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), (int16_t) 0), " spaces where "), (int16_t) count), " were expected");
#line 1635 "boostrap/stage0/ReCode.c"
        Parser__warning(self, message);
#line 1636 "boostrap/stage0/ReCode.c"
        String__delete(message);
    }
}

#line 1640 "boostrap/stage0/ReCode.c"
void Parser__consume_end_of_line(struct Parser* self) {
#line 1641 "boostrap/stage0/ReCode.c"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1642 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1643 "boostrap/stage0/ReCode.c"
        Parser__consume_comment(self);
    } else {
#line 1645 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
    }
#line 1647 "boostrap/stage0/ReCode.c"
    struct Token* token = Parser__consume_token(self, Token__is_end_of_line);
#line 1648 "boostrap/stage0/ReCode.c"
    if (Token__is_end_of_file(token)) {
#line 1649 "boostrap/stage0/ReCode.c"
        Token__warning(token, String__create_from("Unexpected end of file"));
    }
}

#line 1653 "boostrap/stage0/ReCode.c"
bool Parser__consume_empty_line(struct Parser* self) {
#line 1654 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_end_of_file)) {
#line 1655 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 1657 "boostrap/stage0/ReCode.c"
    if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 1658 "boostrap/stage0/ReCode.c"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1659 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 1660 "boostrap/stage0/ReCode.c"
            Parser__consume_comment(self);
        } else {
#line 1662 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
        }
#line 1664 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_end_of_line);
#line 1665 "boostrap/stage0/ReCode.c"
        return true;
    }
#line 1667 "boostrap/stage0/ReCode.c"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_hash)) {
#line 1669 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1670 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_hash);
#line 1671 "boostrap/stage0/ReCode.c"
        while (!Parser__matches_one(self, Token__is_end_of_line)) {
#line 1672 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_anything);
        }
#line 1674 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_end_of_line);
#line 1675 "boostrap/stage0/ReCode.c"
        return true;
    }
#line 1677 "boostrap/stage0/ReCode.c"
    return false;
}

#line 1680 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_expression(struct Parser* self) {
#line 1995 "boostrap/stage0/ReCode.c"
    return Parser__parse_logic_or_expression(self);
}

#line 1681 "boostrap/stage0/ReCode.c"
struct Parsed_Type* Parser__parse_type(struct Parser* self) {
#line 2092 "boostrap/stage0/ReCode.c"
    struct Token* struct_token = NULL;
#line 2093 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_struct)) {
#line 2094 "boostrap/stage0/ReCode.c"
        struct_token = Parser__consume_token(self, Token__is_struct);
#line 2095 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
    }
#line 2097 "boostrap/stage0/ReCode.c"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2098 "boostrap/stage0/ReCode.c"
    struct Parsed_Type* type = Parsed_Named_Type__create(name);
#line 2099 "boostrap/stage0/ReCode.c"
    if (struct_token != NULL) {
#line 2100 "boostrap/stage0/ReCode.c"
        type = Parsed_Struct_Type__create(struct_token->location, type);
    }
#line 2102 "boostrap/stage0/ReCode.c"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
#line 2103 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 2104 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_asterisk);
#line 2105 "boostrap/stage0/ReCode.c"
        type = Parsed_Pointer_Type__create(type);
    }
#line 2107 "boostrap/stage0/ReCode.c"
    return type;
}

#line 1691 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_primary_expression(struct Parser* self) {
#line 1692 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_true)) {
#line 1693 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true);
    }
#line 1695 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_null)) {
#line 1696 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null));
    }
#line 1698 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_false)) {
#line 1699 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false);
    }
#line 1701 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_identifier)) {
#line 1702 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier));
    }
#line 1704 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_integer)) {
#line 1705 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Integer_Expression__create((struct Integer_Token*) Parser__consume_token(self, Token__is_integer));
    }
#line 1707 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_character)) {
#line 1708 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Character_Expression__create((struct Character_Token*) Parser__consume_token(self, Token__is_character));
    }
#line 1710 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_string)) {
#line 1711 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_String_Expression__create((struct String_Token*) Parser__consume_token(self, Token__is_string));
    }
#line 1713 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_opening_paren)) {
#line 1714 "boostrap/stage0/ReCode.c"
        struct Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1715 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1716 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* expression = Parser__parse_expression(self);
#line 1717 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1718 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_closing_paren);
#line 1719 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Group_Expression__create(location, expression);
    }
#line 1721 "boostrap/stage0/ReCode.c"
    Parser__error(self, String__create_from("Unsupported primary expression"));
#line 1722 "boostrap/stage0/ReCode.c"
    abort();
}

#line 1727 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_access_expression(struct Parser* self) {
#line 1728 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = Parser__parse_primary_expression(self);
#line 1729 "boostrap/stage0/ReCode.c"
    while (true) {
#line 1730 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* old_expression = expression;
#line 1731 "boostrap/stage0/ReCode.c"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_dot) || Parser__matches_three(self, Token__is_space, false, Token__is_minus, true, Token__is_greater_than)) {
#line 1732 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 1733 "boostrap/stage0/ReCode.c"
            if (Parser__matches_one(self, Token__is_dot)) {
#line 1734 "boostrap/stage0/ReCode.c"
                Parser__consume_token(self, Token__is_dot);
            } else {
#line 1736 "boostrap/stage0/ReCode.c"
                Parser__consume_token(self, Token__is_minus);
#line 1737 "boostrap/stage0/ReCode.c"
                Parser__consume_token(self, Token__is_greater_than);
            }
#line 1739 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 1740 "boostrap/stage0/ReCode.c"
            struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 1741 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Member_Access_Expression__create(expression, name);
        }
#line 1743 "boostrap/stage0/ReCode.c"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
#line 1744 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 1745 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_opening_paren);
#line 1746 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 1747 "boostrap/stage0/ReCode.c"
            struct Parsed_Call_Expression* call_expression = Parsed_Call_Expression__create(expression);
#line 1748 "boostrap/stage0/ReCode.c"
            if (!Parser__matches_one(self, Token__is_closing_paren)) {
#line 1749 "boostrap/stage0/ReCode.c"
                struct Parsed_Call_Argument* last_argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1750 "boostrap/stage0/ReCode.c"
                call_expression->first_argument = last_argument;
#line 1751 "boostrap/stage0/ReCode.c"
                Parser__consume_space(self, (uint16_t) 0);
#line 1752 "boostrap/stage0/ReCode.c"
                while (Parser__matches_one(self, Token__is_comma)) {
#line 1753 "boostrap/stage0/ReCode.c"
                    Parser__consume_token(self, Token__is_comma);
#line 1754 "boostrap/stage0/ReCode.c"
                    Parser__consume_space(self, (uint16_t) 1);
#line 1755 "boostrap/stage0/ReCode.c"
                    struct Parsed_Call_Argument* argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1756 "boostrap/stage0/ReCode.c"
                    last_argument->next_argument = argument;
#line 1757 "boostrap/stage0/ReCode.c"
                    last_argument = argument;
#line 1758 "boostrap/stage0/ReCode.c"
                    Parser__consume_space(self, (uint16_t) 0);
                }
            }
#line 1761 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) call_expression;
#line 1762 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_closing_paren);
        }
#line 1764 "boostrap/stage0/ReCode.c"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
#line 1765 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 1766 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_opening_bracket);
#line 1767 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 1768 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* index_expression = Parser__parse_expression(self);
#line 1769 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 1770 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_closing_bracket);
#line 1771 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Array_Access_Expression__create(expression, index_expression);
        }
#line 1773 "boostrap/stage0/ReCode.c"
        if (old_expression == expression) {
#line 1774 "boostrap/stage0/ReCode.c"
            break;
        }
    }
#line 1777 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1787 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_unary_expression(struct Parser* self) {
#line 1788 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_minus)) {
#line 1789 "boostrap/stage0/ReCode.c"
        struct Source_Location* location = Parser__consume_token(self, Token__is_minus)->location;
#line 1790 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1791 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1792 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Minus_Expression__create(location, expression);
    }
#line 1794 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_exclamation_mark)) {
#line 1795 "boostrap/stage0/ReCode.c"
        struct Source_Location* location = Parser__consume_token(self, Token__is_exclamation_mark)->location;
#line 1796 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1797 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1798 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Not_Expression__create(location, expression);
    }
#line 1800 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_ampersand)) {
#line 1801 "boostrap/stage0/ReCode.c"
        struct Source_Location* location = Parser__consume_token(self, Token__is_ampersand)->location;
#line 1802 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1803 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1804 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Address_Of_Expression__create(location, expression);
    }
#line 1806 "boostrap/stage0/ReCode.c"
    if (Parser__matches_three(self, Token__is_opening_paren, true, Token__is_space, false, Token__is_identifier)) {
#line 1807 "boostrap/stage0/ReCode.c"
        uint8_t peek_offset = (uint8_t) 1;
#line 1808 "boostrap/stage0/ReCode.c"
        if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1809 "boostrap/stage0/ReCode.c"
            peek_offset = peek_offset + (uint8_t) 1;
        }
#line 1811 "boostrap/stage0/ReCode.c"
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
#line 1812 "boostrap/stage0/ReCode.c"
            peek_offset = peek_offset + (uint8_t) 1;
#line 1813 "boostrap/stage0/ReCode.c"
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1814 "boostrap/stage0/ReCode.c"
                peek_offset = peek_offset + (uint8_t) 1;
            }
#line 1816 "boostrap/stage0/ReCode.c"
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
#line 1817 "boostrap/stage0/ReCode.c"
                peek_offset = peek_offset + (uint8_t) 1;
#line 1818 "boostrap/stage0/ReCode.c"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1819 "boostrap/stage0/ReCode.c"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
            }
#line 1822 "boostrap/stage0/ReCode.c"
            if (Token__is_closing_paren(Parser__peek_token(self, peek_offset))) {
#line 1823 "boostrap/stage0/ReCode.c"
                peek_offset = peek_offset + (uint8_t) 1;
#line 1824 "boostrap/stage0/ReCode.c"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1825 "boostrap/stage0/ReCode.c"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
#line 1827 "boostrap/stage0/ReCode.c"
                struct Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1828 "boostrap/stage0/ReCode.c"
                Parser__consume_space(self, (uint16_t) 0);
#line 1829 "boostrap/stage0/ReCode.c"
                struct Parsed_Type* type = Parser__parse_type(self);
#line 1830 "boostrap/stage0/ReCode.c"
                Parser__consume_space(self, (uint16_t) 0);
#line 1831 "boostrap/stage0/ReCode.c"
                Parser__consume_token(self, Token__is_closing_paren);
#line 1832 "boostrap/stage0/ReCode.c"
                Parser__consume_space(self, (uint16_t) 1);
#line 1833 "boostrap/stage0/ReCode.c"
                struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1834 "boostrap/stage0/ReCode.c"
                return (struct Parsed_Expression*) Parsed_Cast_Expression__create(location, expression, type);
            }
        }
    }
#line 1838 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_sizeof)) {
#line 1839 "boostrap/stage0/ReCode.c"
        struct Source_Location* location = Parser__consume_token(self, Token__is_sizeof)->location;
#line 1840 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1841 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_opening_paren);
#line 1842 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1843 "boostrap/stage0/ReCode.c"
        struct Parsed_Type* type = Parser__parse_type(self);
#line 1844 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 1845 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_closing_paren);
#line 1846 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Expression*) Parsed_Sizeof_Expression__create(location, type);
    }
#line 1848 "boostrap/stage0/ReCode.c"
    return Parser__parse_access_expression(self);
}

#line 1851 "boostrap/stage0/ReCode.c"
bool Token__is_mutliplication(struct Token* self) {
#line 1852 "boostrap/stage0/ReCode.c"
    return Token__is_asterisk(self) || Token__is_slash(self) || Token__is_percent(self);
}

#line 1857 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_multiplication_expression(struct Parser* self) {
#line 1858 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1859 "boostrap/stage0/ReCode.c"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
#line 1860 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1861 "boostrap/stage0/ReCode.c"
        if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1862 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_asterisk);
#line 1863 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1864 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1865 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Multiply_Expression__create(expression, right_expression);
        } else if (Parser__matches_one(self, Token__is_slash)) {
#line 1867 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_slash);
#line 1868 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1869 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1870 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Divide_Expression__create(expression, right_expression);
        } else {
#line 1872 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_percent);
#line 1873 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1874 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1875 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Modulo_Expression__create(expression, right_expression);
        }
    }
#line 1878 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1881 "boostrap/stage0/ReCode.c"
bool Token__is_addition(struct Token* self) {
#line 1882 "boostrap/stage0/ReCode.c"
    return Token__is_plus(self) || Token__is_minus(self);
}

#line 1887 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_addition_expression(struct Parser* self) {
#line 1888 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = Parser__parse_multiplication_expression(self);
#line 1889 "boostrap/stage0/ReCode.c"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
#line 1890 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1891 "boostrap/stage0/ReCode.c"
        if (Parser__matches_one(self, Token__is_plus)) {
#line 1892 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_plus);
#line 1893 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1894 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
#line 1895 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Add_Expression__create(expression, right_expression);
        } else {
#line 1897 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_minus);
#line 1898 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1899 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
#line 1900 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Substract_Expression__create(expression, right_expression);
        }
    }
#line 1903 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1908 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_comparison_expression(struct Parser* self) {
#line 1909 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = Parser__parse_addition_expression(self);
#line 1910 "boostrap/stage0/ReCode.c"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
#line 1911 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1912 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_less_than);
#line 1913 "boostrap/stage0/ReCode.c"
        if (Parser__matches_one(self, Token__is_equals)) {
#line 1914 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_equals);
#line 1915 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1916 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1917 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
#line 1919 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1920 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1921 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
#line 1924 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1925 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_greater_than);
#line 1926 "boostrap/stage0/ReCode.c"
        if (Parser__matches_one(self, Token__is_equals)) {
#line 1927 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_equals);
#line 1928 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1929 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1930 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
#line 1932 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 1933 "boostrap/stage0/ReCode.c"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1934 "boostrap/stage0/ReCode.c"
            expression = (struct Parsed_Expression*) Parsed_Greater_Expression__create(expression, right_expression);
        }
    }
#line 1937 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1942 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_equality_expression(struct Parser* self) {
#line 1943 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = Parser__parse_comparison_expression(self);
#line 1944 "boostrap/stage0/ReCode.c"
    if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
#line 1945 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1946 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_equals);
#line 1947 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_equals);
#line 1948 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1949 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
#line 1950 "boostrap/stage0/ReCode.c"
        expression = (struct Parsed_Expression*) Parsed_Equals_Expression__create(expression, right_expression);
    } else if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
#line 1952 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1953 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_exclamation_mark);
#line 1954 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_equals);
#line 1955 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1956 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
#line 1957 "boostrap/stage0/ReCode.c"
        expression = (struct Parsed_Expression*) Parsed_Not_Equals_Expression__create(expression, right_expression);
    }
#line 1959 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1964 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_logic_and_expression(struct Parser* self) {
#line 1965 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = Parser__parse_equality_expression(self);
#line 1966 "boostrap/stage0/ReCode.c"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_ampersand, true, Token__is_ampersand)) {
#line 1967 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1968 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_ampersand);
#line 1969 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_ampersand);
#line 1970 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1971 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* right_expression = Parser__parse_equality_expression(self);
#line 1972 "boostrap/stage0/ReCode.c"
        expression = (struct Parsed_Expression*) Parsed_Logic_And_Expression__create(expression, right_expression);
    }
#line 1974 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 1979 "boostrap/stage0/ReCode.c"
struct Parsed_Expression* Parser__parse_logic_or_expression(struct Parser* self) {
#line 1980 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = Parser__parse_logic_and_expression(self);
#line 1981 "boostrap/stage0/ReCode.c"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_vertical_bar, true, Token__is_vertical_bar)) {
#line 1982 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1983 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1984 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1985 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 1986 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* right_expression = Parser__parse_logic_and_expression(self);
#line 1987 "boostrap/stage0/ReCode.c"
        expression = (struct Parsed_Expression*) Parsed_Logic_Or_Expression__create(expression, right_expression);
    }
#line 1989 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 2000 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_struct(struct Parser* self) {
#line 2001 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
#line 2002 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2003 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_struct);
#line 2004 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2005 "boostrap/stage0/ReCode.c"
    struct Token* local_name = Parser__consume_token(self, Token__is_identifier);
#line 2006 "boostrap/stage0/ReCode.c"
    struct Parsed_Struct_Statement* struct_statement = Parsed_Struct_Statement__create(location, local_name);
#line 2007 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2008 "boostrap/stage0/ReCode.c"
    if (!Parser__matches_one(self, Token__is_identifier)) {
#line 2009 "boostrap/stage0/ReCode.c"
        struct Parsed_Struct_Member* last_member = NULL;
#line 2010 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_opening_brace);
#line 2011 "boostrap/stage0/ReCode.c"
        Parser__consume_end_of_line(self);
#line 2012 "boostrap/stage0/ReCode.c"
        while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2013 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (self->current_identation + (uint16_t) 1) * (uint16_t) 4);
#line 2014 "boostrap/stage0/ReCode.c"
            struct Parsed_Type* type = Parser__parse_type(self);
#line 2015 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 2016 "boostrap/stage0/ReCode.c"
            struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2017 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 2018 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_semicolon);
#line 2019 "boostrap/stage0/ReCode.c"
            Parser__consume_end_of_line(self);
#line 2020 "boostrap/stage0/ReCode.c"
            struct Parsed_Struct_Member* member = Parsed_Struct_Member__create(name, type);
#line 2021 "boostrap/stage0/ReCode.c"
            if (last_member == NULL) {
#line 2022 "boostrap/stage0/ReCode.c"
                struct_statement->first_member = member;
#line 2023 "boostrap/stage0/ReCode.c"
                last_member = member;
            } else {
#line 2025 "boostrap/stage0/ReCode.c"
                last_member->next_member = member;
#line 2026 "boostrap/stage0/ReCode.c"
                last_member = member;
            }
        }
#line 2029 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 2030 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_closing_brace);
#line 2031 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
    }
#line 2033 "boostrap/stage0/ReCode.c"
    struct Token* final_name = Parser__consume_token(self, Token__is_identifier);
#line 2034 "boostrap/stage0/ReCode.c"
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
#line 2035 "boostrap/stage0/ReCode.c"
        Token__error(final_name, String__append_string(String__create_from("Final struct name doesn\'t match the local name: "), local_name->lexeme));
#line 2036 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 2038 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2039 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_semicolon);
#line 2040 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) struct_statement;
}

#line 2045 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_enum(struct Parser* self) {
#line 2046 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
#line 2047 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2048 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_enum);
#line 2049 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2050 "boostrap/stage0/ReCode.c"
    struct Token* local_name = Parser__consume_token(self, Token__is_identifier);
#line 2051 "boostrap/stage0/ReCode.c"
    struct Parsed_Enum_Statement* enum_statement = Parsed_Enum_Statement__create(location, local_name);
#line 2052 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2053 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2054 "boostrap/stage0/ReCode.c"
    Parser__consume_end_of_line(self);
#line 2055 "boostrap/stage0/ReCode.c"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2056 "boostrap/stage0/ReCode.c"
    struct Parsed_Enum_Member* last_member = NULL;
#line 2057 "boostrap/stage0/ReCode.c"
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2058 "boostrap/stage0/ReCode.c"
        while (Parser__consume_empty_line(self)) {
        }
#line 2061 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2062 "boostrap/stage0/ReCode.c"
        struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2063 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 2064 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_comma);
#line 2065 "boostrap/stage0/ReCode.c"
        Parser__consume_end_of_line(self);
#line 2066 "boostrap/stage0/ReCode.c"
        struct Parsed_Enum_Member* member = Parsed_Enum_Member__create(name);
#line 2067 "boostrap/stage0/ReCode.c"
        if (last_member == NULL) {
#line 2068 "boostrap/stage0/ReCode.c"
            enum_statement->first_member = member;
#line 2069 "boostrap/stage0/ReCode.c"
            last_member = member;
        } else {
#line 2071 "boostrap/stage0/ReCode.c"
            last_member->next_member = member;
#line 2072 "boostrap/stage0/ReCode.c"
            last_member = member;
        }
    }
#line 2075 "boostrap/stage0/ReCode.c"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2076 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2077 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2078 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2079 "boostrap/stage0/ReCode.c"
    struct Token* final_name = Parser__consume_token(self, Token__is_identifier);
#line 2080 "boostrap/stage0/ReCode.c"
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
#line 2081 "boostrap/stage0/ReCode.c"
        Token__error(final_name, String__append_string(String__create_from("Final enum name doesn\'t match the local name: "), local_name->lexeme));
#line 2082 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 2084 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2085 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_semicolon);
#line 2086 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) enum_statement;
}

#line 2112 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_type_alias(struct Parser* self) {
#line 2113 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
#line 2114 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2115 "boostrap/stage0/ReCode.c"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2116 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2117 "boostrap/stage0/ReCode.c"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2118 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2119 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2120 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Type_Parameter* first_parameter = NULL;
#line 2121 "boostrap/stage0/ReCode.c"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2122 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 2123 "boostrap/stage0/ReCode.c"
        struct Parsed_Type* parameter_type = Parser__parse_type(self);
#line 2124 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2125 "boostrap/stage0/ReCode.c"
        struct Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
#line 2126 "boostrap/stage0/ReCode.c"
        first_parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
#line 2127 "boostrap/stage0/ReCode.c"
        struct Parsed_Function_Type_Parameter* last_parameter = first_parameter;
#line 2128 "boostrap/stage0/ReCode.c"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2129 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 2130 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_comma);
#line 2131 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 2132 "boostrap/stage0/ReCode.c"
            struct Parsed_Type* parameter_type = Parser__parse_type(self);
#line 2133 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 2134 "boostrap/stage0/ReCode.c"
            struct Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
#line 2135 "boostrap/stage0/ReCode.c"
            struct Parsed_Function_Type_Parameter* parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
#line 2136 "boostrap/stage0/ReCode.c"
            last_parameter->next_parameter = parameter;
#line 2137 "boostrap/stage0/ReCode.c"
            last_parameter = parameter;
        }
    }
#line 2140 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2141 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2142 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2143 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_semicolon);
#line 2144 "boostrap/stage0/ReCode.c"
    return Parsed_Function_Type_Statement__create(location, name, first_parameter, return_type);
}

#line 2149 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_variable(struct Parser* self) {
#line 2150 "boostrap/stage0/ReCode.c"
    bool is_external;
#line 2151 "boostrap/stage0/ReCode.c"
    struct Source_Location* location;
#line 2152 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_extern)) {
#line 2153 "boostrap/stage0/ReCode.c"
        is_external = true;
#line 2154 "boostrap/stage0/ReCode.c"
        location = Parser__consume_token(self, Token__is_extern)->location;
#line 2155 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
    } else {
#line 2157 "boostrap/stage0/ReCode.c"
        is_external = false;
#line 2158 "boostrap/stage0/ReCode.c"
        location = Parser__peek_token(self, (uint8_t) 0)->location;
    }
#line 2160 "boostrap/stage0/ReCode.c"
    struct Parsed_Type* type = Parser__parse_type(self);
#line 2161 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2162 "boostrap/stage0/ReCode.c"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2163 "boostrap/stage0/ReCode.c"
    struct Parsed_Variable_Statement* variable_statement = Parsed_Variable_Statement__create(location, name, type, is_external);
#line 2164 "boostrap/stage0/ReCode.c"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2165 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2166 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_equals);
#line 2167 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2168 "boostrap/stage0/ReCode.c"
        variable_statement->expression = Parser__parse_expression(self);
    }
#line 2170 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2171 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_semicolon);
#line 2172 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) variable_statement;
}

#line 2175 "boostrap/stage0/ReCode.c"
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self) {
#line 2176 "boostrap/stage0/ReCode.c"
    struct Parsed_Type* type = Parser__parse_type(self);
#line 2177 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2178 "boostrap/stage0/ReCode.c"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2179 "boostrap/stage0/ReCode.c"
    return Parsed_Function_Parameter__create(name, type);
}

#line 2182 "boostrap/stage0/ReCode.c"
struct Parsed_Function_Parameter* Parser__parse_function_parameters(struct Parser* self) {
#line 2183 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Parameter* first_parameter = NULL;
#line 2184 "boostrap/stage0/ReCode.c"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2185 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 2186 "boostrap/stage0/ReCode.c"
        first_parameter = Parser__parse_function_parameter(self);
#line 2187 "boostrap/stage0/ReCode.c"
        struct Parsed_Function_Parameter* last_parameter = first_parameter;
#line 2188 "boostrap/stage0/ReCode.c"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2189 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 0);
#line 2190 "boostrap/stage0/ReCode.c"
            Parser__consume_token(self, Token__is_comma);
#line 2191 "boostrap/stage0/ReCode.c"
            Parser__consume_space(self, (uint16_t) 1);
#line 2192 "boostrap/stage0/ReCode.c"
            last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2193 "boostrap/stage0/ReCode.c"
            last_parameter = last_parameter->next_parameter;
        }
    }
#line 2196 "boostrap/stage0/ReCode.c"
    return first_parameter;
}

#line 2199 "boostrap/stage0/ReCode.c"
void Parser__parse_statements(struct Parser* self, struct Parsed_Statements* statements) {
#line 2404 "boostrap/stage0/ReCode.c"
    while (true) {
#line 2405 "boostrap/stage0/ReCode.c"
        while (Parser__consume_empty_line(self)) {
        }
#line 2409 "boostrap/stage0/ReCode.c"
        if (statements->has_globals) {
#line 2410 "boostrap/stage0/ReCode.c"
            if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 2411 "boostrap/stage0/ReCode.c"
                return;
            }
        } else {
#line 2414 "boostrap/stage0/ReCode.c"
            if (Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2415 "boostrap/stage0/ReCode.c"
                return;
            }
        }
#line 2419 "boostrap/stage0/ReCode.c"
        struct Parsed_Statement* statement = Parser__parse_statement(self);
#line 2421 "boostrap/stage0/ReCode.c"
        Parser__consume_end_of_line(self);
#line 2423 "boostrap/stage0/ReCode.c"
        Parsed_Statements__append(statements, statement);
    }
}

#line 2203 "boostrap/stage0/ReCode.c"
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self) {
#line 2204 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_opening_brace)->location;
#line 2205 "boostrap/stage0/ReCode.c"
    Parser__consume_end_of_line(self);
#line 2206 "boostrap/stage0/ReCode.c"
    struct Parsed_Statements* statements = Parsed_Statements__create(false);
#line 2207 "boostrap/stage0/ReCode.c"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2208 "boostrap/stage0/ReCode.c"
    Parser__parse_statements(self, statements);
#line 2209 "boostrap/stage0/ReCode.c"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2210 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2211 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2212 "boostrap/stage0/ReCode.c"
    return Parsed_Block_Statement__create(location, statements);
}

#line 2217 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_function(struct Parser* self) {
#line 2218 "boostrap/stage0/ReCode.c"
    bool is_external;
#line 2219 "boostrap/stage0/ReCode.c"
    struct Source_Location* location;
#line 2220 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_extern)) {
#line 2221 "boostrap/stage0/ReCode.c"
        is_external = true;
#line 2222 "boostrap/stage0/ReCode.c"
        location = Parser__consume_token(self, Token__is_extern)->location;
#line 2223 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
    } else {
#line 2225 "boostrap/stage0/ReCode.c"
        is_external = false;
#line 2226 "boostrap/stage0/ReCode.c"
        location = Parser__peek_token(self, (uint8_t) 0)->location;
    }
#line 2228 "boostrap/stage0/ReCode.c"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2229 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2230 "boostrap/stage0/ReCode.c"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2231 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2232 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2233 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Parameter* first_parameter = Parser__parse_function_parameters(self);
#line 2234 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2235 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2236 "boostrap/stage0/ReCode.c"
    struct Parsed_Statements* statements = NULL;
#line 2237 "boostrap/stage0/ReCode.c"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_brace)) {
#line 2238 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2239 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_opening_brace);
#line 2240 "boostrap/stage0/ReCode.c"
        Parser__consume_end_of_line(self);
#line 2241 "boostrap/stage0/ReCode.c"
        statements = Parsed_Statements__create(false);
#line 2242 "boostrap/stage0/ReCode.c"
        self->current_identation = self->current_identation + (uint16_t) 1;
#line 2243 "boostrap/stage0/ReCode.c"
        Parser__parse_statements(self, statements);
#line 2244 "boostrap/stage0/ReCode.c"
        self->current_identation = self->current_identation - (uint16_t) 1;
#line 2245 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2246 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_closing_brace);
    } else {
#line 2248 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 2249 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_semicolon);
    }
#line 2251 "boostrap/stage0/ReCode.c"
    return Parsed_Function_Statement__create(location, name, first_parameter, return_type, statements, is_external);
}

#line 2256 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_return_statement(struct Parser* self) {
#line 2257 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_return)->location;
#line 2258 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expression = NULL;
#line 2259 "boostrap/stage0/ReCode.c"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_semicolon)) {
#line 2260 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2261 "boostrap/stage0/ReCode.c"
        expression = Parser__parse_expression(self);
    }
#line 2263 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2264 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_semicolon);
#line 2265 "boostrap/stage0/ReCode.c"
    return Parsed_Return_Statement__create(location, expression);
}

#line 2270 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_break_statement(struct Parser* self) {
#line 2271 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_break)->location;
#line 2272 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2273 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_semicolon);
#line 2274 "boostrap/stage0/ReCode.c"
    return Parsed_Break_Statement__create(location);
}

#line 2279 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_if_statement(struct Parser* self) {
#line 2280 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_if)->location;
#line 2281 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2282 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2283 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2284 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* condition_expression = Parser__parse_expression(self);
#line 2285 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2286 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2287 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2288 "boostrap/stage0/ReCode.c"
    struct Parsed_Statement* true_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
#line 2289 "boostrap/stage0/ReCode.c"
    struct Parsed_Statement* false_statement = NULL;
#line 2290 "boostrap/stage0/ReCode.c"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
#line 2291 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2292 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_else);
#line 2293 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2294 "boostrap/stage0/ReCode.c"
        if (Parser__matches_one(self, Token__is_if)) {
#line 2295 "boostrap/stage0/ReCode.c"
            false_statement = Parser__parse_if_statement(self);
        } else {
#line 2297 "boostrap/stage0/ReCode.c"
            false_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
        }
    }
#line 2300 "boostrap/stage0/ReCode.c"
    return Parsed_If_Statement__create(location, condition_expression, true_statement, false_statement);
}

#line 2305 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_while_statement(struct Parser* self) {
#line 2306 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Parser__consume_token(self, Token__is_while)->location;
#line 2307 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2308 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2309 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2310 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* condition_expression = Parser__parse_expression(self);
#line 2311 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2312 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2313 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 1);
#line 2314 "boostrap/stage0/ReCode.c"
    struct Parsed_Statement* body_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
#line 2315 "boostrap/stage0/ReCode.c"
    return Parsed_While_Statement__create(location, condition_expression, body_statement);
}

#line 2326 "boostrap/stage0/ReCode.c"
struct Parsed_Statement* Parser__parse_statement(struct Parser* self) {
#line 2327 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2329 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_if)) {
#line 2330 "boostrap/stage0/ReCode.c"
        return Parser__parse_if_statement(self);
    }
#line 2332 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_while)) {
#line 2333 "boostrap/stage0/ReCode.c"
        return Parser__parse_while_statement(self);
    }
#line 2335 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_return)) {
#line 2336 "boostrap/stage0/ReCode.c"
        return Parser__parse_return_statement(self);
    }
#line 2338 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_break)) {
#line 2339 "boostrap/stage0/ReCode.c"
        return Parser__parse_break_statement(self);
    }
#line 2342 "boostrap/stage0/ReCode.c"
    if (Parser__matches_three(self, Token__is_typedef, true, Token__is_space, true, Token__is_struct)) {
#line 2343 "boostrap/stage0/ReCode.c"
        return Parser__parse_struct(self);
    }
#line 2346 "boostrap/stage0/ReCode.c"
    if (Parser__matches_three(self, Token__is_typedef, true, Token__is_space, true, Token__is_enum)) {
#line 2347 "boostrap/stage0/ReCode.c"
        return Parser__parse_enum(self);
    }
#line 2350 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_typedef)) {
#line 2351 "boostrap/stage0/ReCode.c"
        return Parser__parse_type_alias(self);
    }
#line 2354 "boostrap/stage0/ReCode.c"
    if (Parser__matches_one(self, Token__is_extern) || Parser__matches_one(self, Token__is_identifier)) {
#line 2355 "boostrap/stage0/ReCode.c"
        uint8_t peek_offset = (uint8_t) 0;
#line 2356 "boostrap/stage0/ReCode.c"
        if (Token__is_extern(Parser__peek_token(self, peek_offset))) {
#line 2357 "boostrap/stage0/ReCode.c"
            peek_offset = peek_offset + (uint8_t) 1;
#line 2358 "boostrap/stage0/ReCode.c"
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2359 "boostrap/stage0/ReCode.c"
                peek_offset = peek_offset + (uint8_t) 1;
            }
        }
#line 2362 "boostrap/stage0/ReCode.c"
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
#line 2363 "boostrap/stage0/ReCode.c"
            peek_offset = peek_offset + (uint8_t) 1;
#line 2364 "boostrap/stage0/ReCode.c"
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2365 "boostrap/stage0/ReCode.c"
                peek_offset = peek_offset + (uint8_t) 1;
            }
#line 2367 "boostrap/stage0/ReCode.c"
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
#line 2368 "boostrap/stage0/ReCode.c"
                peek_offset = peek_offset + (uint8_t) 1;
#line 2369 "boostrap/stage0/ReCode.c"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2370 "boostrap/stage0/ReCode.c"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
            }
#line 2373 "boostrap/stage0/ReCode.c"
            if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
#line 2374 "boostrap/stage0/ReCode.c"
                peek_offset = peek_offset + (uint8_t) 1;
#line 2375 "boostrap/stage0/ReCode.c"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2376 "boostrap/stage0/ReCode.c"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
#line 2378 "boostrap/stage0/ReCode.c"
                if (Token__is_opening_paren(Parser__peek_token(self, peek_offset))) {
#line 2379 "boostrap/stage0/ReCode.c"
                    return Parser__parse_function(self);
                }
#line 2381 "boostrap/stage0/ReCode.c"
                return Parser__parse_variable(self);
            }
        }
    }
#line 2386 "boostrap/stage0/ReCode.c"
    struct Parsed_Expression* expresion = Parser__parse_access_expression(self);
#line 2387 "boostrap/stage0/ReCode.c"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2388 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2389 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_equals);
#line 2390 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 1);
#line 2391 "boostrap/stage0/ReCode.c"
        struct Parsed_Expression* value_expression = Parser__parse_expression(self);
#line 2392 "boostrap/stage0/ReCode.c"
        Parser__consume_space(self, (uint16_t) 0);
#line 2393 "boostrap/stage0/ReCode.c"
        Parser__consume_token(self, Token__is_semicolon);
#line 2394 "boostrap/stage0/ReCode.c"
        return (struct Parsed_Statement*) Parsed_Assignment_Statement__create(expresion, value_expression);
    }
#line 2396 "boostrap/stage0/ReCode.c"
    Parser__consume_space(self, (uint16_t) 0);
#line 2397 "boostrap/stage0/ReCode.c"
    Parser__consume_token(self, Token__is_semicolon);
#line 2398 "boostrap/stage0/ReCode.c"
    return (struct Parsed_Statement*) Parsed_Expression_Statement__create(expresion);
}

#line 2427 "boostrap/stage0/ReCode.c"
void Parser__parse_source(struct Parser* self, struct Source* source) {
#line 2428 "boostrap/stage0/ReCode.c"
    struct Scanner* other_scanner = self->scanner;
#line 2430 "boostrap/stage0/ReCode.c"
    self->scanner = Scanner__create(source);
#line 2432 "boostrap/stage0/ReCode.c"
    Parser__parse_statements(self, self->compilation_unit->statements);
#line 2434 "boostrap/stage0/ReCode.c"
    struct Token* last_token = Parser__peek_token(self, (uint8_t) 0);
#line 2435 "boostrap/stage0/ReCode.c"
    if (!Token__is_end_of_file(last_token)) {
#line 2436 "boostrap/stage0/ReCode.c"
        Parser__error(self, String__create_from("Scanner didn\'t reach end of file"));
#line 2437 "boostrap/stage0/ReCode.c"
        abort();
    } else if (last_token->location->column != (uint16_t) 1) {
#line 2439 "boostrap/stage0/ReCode.c"
        Parser__warning(self, String__create_from("No new line at the end of file"));
    }
#line 2442 "boostrap/stage0/ReCode.c"
    self->scanner = other_scanner;
}

#line 2445 "boostrap/stage0/ReCode.c"
struct Parsed_Source* parse(struct Source* source) {
#line 2446 "boostrap/stage0/ReCode.c"
    struct Parser parser;
#line 2447 "boostrap/stage0/ReCode.c"
    parser.scanner = NULL;
#line 2448 "boostrap/stage0/ReCode.c"
    parser.compilation_unit = Parsed_Compilation_Unit__create();
#line 2449 "boostrap/stage0/ReCode.c"
    parser.current_identation = (uint16_t) 0;
#line 2451 "boostrap/stage0/ReCode.c"
    Parser__parse_source(&parser, source);
#line 2453 "boostrap/stage0/ReCode.c"
    return parser.compilation_unit;
}

#line 2488 "boostrap/stage0/ReCode.c"
struct Checked_Type* Checked_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 2489 "boostrap/stage0/ReCode.c"
    struct Checked_Type* type = (struct Checked_Type*) malloc(kind_size);
#line 2490 "boostrap/stage0/ReCode.c"
    type->kind = kind;
#line 2491 "boostrap/stage0/ReCode.c"
    type->location = location;
#line 2492 "boostrap/stage0/ReCode.c"
    type->next_type = NULL;
#line 2493 "boostrap/stage0/ReCode.c"
    return type;
}

#line 2496 "boostrap/stage0/ReCode.c"
bool Checked_Type__equals(struct Checked_Type* self, struct Checked_Type* other_type) {
#line 2715 "boostrap/stage0/ReCode.c"
    if (self == other_type) {
#line 2716 "boostrap/stage0/ReCode.c"
        return true;
    }
#line 2718 "boostrap/stage0/ReCode.c"
    if (self->kind != other_type->kind) {
#line 2719 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 2721 "boostrap/stage0/ReCode.c"
    if (self->kind == CHECKED_TYPE_KIND__FUNCTION) {
#line 2722 "boostrap/stage0/ReCode.c"
        return Checked_Function_Type__equals((struct Checked_Function_Type*) self, other_type);
    }
#line 2724 "boostrap/stage0/ReCode.c"
    if (self->kind == CHECKED_TYPE_KIND__POINTER) {
#line 2725 "boostrap/stage0/ReCode.c"
        return Checked_Pointer_Type__equals((struct Checked_Pointer_Type*) self, other_type);
    }
#line 2727 "boostrap/stage0/ReCode.c"
    if (self->kind == CHECKED_TYPE_KIND__STRUCT) {
#line 2728 "boostrap/stage0/ReCode.c"
        return Checked_Struct_Type__equals((struct Checked_Struct_Type*) self, other_type);
    }
#line 2730 "boostrap/stage0/ReCode.c"
    error(String__create_from("TODO: Compare unsupported type"));
#line 2731 "boostrap/stage0/ReCode.c"
    abort();
}

#line 2498 "boostrap/stage0/ReCode.c"
struct String* String__append_checked_type(struct String* self, struct Checked_Type* type) {
#line 2735 "boostrap/stage0/ReCode.c"
    if (type->kind <= CHECKED_TYPE_KIND__NULL) {
#line 2736 "boostrap/stage0/ReCode.c"
        struct Checked_Named_Type* named_type = (struct Checked_Named_Type*) type;
#line 2737 "boostrap/stage0/ReCode.c"
        String__append_string(self, named_type->name);
    } else if (type->kind == CHECKED_TYPE_KIND__STRUCT) {
#line 2739 "boostrap/stage0/ReCode.c"
        struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) type;
#line 2740 "boostrap/stage0/ReCode.c"
        String__append_cstring(self, "struct ");
#line 2741 "boostrap/stage0/ReCode.c"
        String__append_string(self, struct_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__FUNCTION) {
#line 2743 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) type;
#line 2744 "boostrap/stage0/ReCode.c"
        String__append_checked_type(self, function_type->return_type);
#line 2745 "boostrap/stage0/ReCode.c"
        String__append_char(self, ' ');
#line 2746 "boostrap/stage0/ReCode.c"
        String__append_string(self, function_type->super.name);
#line 2747 "boostrap/stage0/ReCode.c"
        String__append_char(self, '(');
#line 2748 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2749 "boostrap/stage0/ReCode.c"
        while (function_parameter != NULL) {
#line 2750 "boostrap/stage0/ReCode.c"
            String__append_checked_type(self, function_parameter->type);
#line 2751 "boostrap/stage0/ReCode.c"
            String__append_char(self, ' ');
#line 2752 "boostrap/stage0/ReCode.c"
            String__append_string(self, function_parameter->name);
#line 2753 "boostrap/stage0/ReCode.c"
            function_parameter = function_parameter->next_parameter;
#line 2754 "boostrap/stage0/ReCode.c"
            if (function_parameter != NULL) {
#line 2755 "boostrap/stage0/ReCode.c"
                String__append_cstring(self, ", ");
            }
        }
#line 2758 "boostrap/stage0/ReCode.c"
        String__append_char(self, ')');
    } else if (type->kind == CHECKED_TYPE_KIND__ENUM) {
#line 2760 "boostrap/stage0/ReCode.c"
        struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) type;
#line 2761 "boostrap/stage0/ReCode.c"
        String__append_cstring(self, "enum ");
#line 2762 "boostrap/stage0/ReCode.c"
        String__append_string(self, enum_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__POINTER) {
#line 2764 "boostrap/stage0/ReCode.c"
        struct Checked_Pointer_Type* pointer_type = (struct Checked_Pointer_Type*) type;
#line 2765 "boostrap/stage0/ReCode.c"
        String__append_checked_type(self, pointer_type->other_type);
#line 2766 "boostrap/stage0/ReCode.c"
        String__append_char(self, '*');
    } else {
#line 2768 "boostrap/stage0/ReCode.c"
        Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2769 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 2771 "boostrap/stage0/ReCode.c"
    return self;
}

#line 2500 "boostrap/stage0/ReCode.c"
void Checked_Type__expect_same_type(struct Checked_Type* self, struct Checked_Type* other_type, struct Source_Location* location) {
#line 2501 "boostrap/stage0/ReCode.c"
    if (self->kind == CHECKED_TYPE_KIND__POINTER && other_type->kind == CHECKED_TYPE_KIND__NULL) {
#line 2502 "boostrap/stage0/ReCode.c"
        return;
    }
#line 2504 "boostrap/stage0/ReCode.c"
    if (!Checked_Type__equals(self, other_type)) {
#line 2505 "boostrap/stage0/ReCode.c"
        struct String* message = String__create_from("Unexpected type. Got \"");
#line 2506 "boostrap/stage0/ReCode.c"
        String__append_checked_type(message, other_type);
#line 2507 "boostrap/stage0/ReCode.c"
        String__append_cstring(message, "\" instead of \"");
#line 2508 "boostrap/stage0/ReCode.c"
        String__append_checked_type(message, self);
#line 2509 "boostrap/stage0/ReCode.c"
        String__append_char(message, '\"');
#line 2510 "boostrap/stage0/ReCode.c"
        Source_Location__error(location, message);
#line 2511 "boostrap/stage0/ReCode.c"
        abort();
    }
}

#line 2515 "boostrap/stage0/ReCode.c"
bool Checked_Type__is_scalar_type(struct Checked_Type* self) {
#line 2516 "boostrap/stage0/ReCode.c"
    if (self->kind == CHECKED_TYPE_KIND__CHAR) {
#line 2517 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT16_T) {
#line 2519 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT32_T) {
#line 2521 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT64_T) {
#line 2523 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT8_T) {
#line 2525 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__SIZE_T) {
#line 2527 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT16_T) {
#line 2529 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT32_T) {
#line 2531 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT64_T) {
#line 2533 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT8_T) {
#line 2535 "boostrap/stage0/ReCode.c"
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__ENUM) {
#line 2537 "boostrap/stage0/ReCode.c"
        return true;
    }
#line 2539 "boostrap/stage0/ReCode.c"
    return false;
}

#line 2542 "boostrap/stage0/ReCode.c"
void Checked_Type__expect_scalar_type(struct Checked_Type* self, struct Source_Location* location) {
#line 2543 "boostrap/stage0/ReCode.c"
    if (!Checked_Type__is_scalar_type(self)) {
#line 2544 "boostrap/stage0/ReCode.c"
        struct String* message = String__create_from("Type \"");
#line 2545 "boostrap/stage0/ReCode.c"
        String__append_checked_type(message, self);
#line 2546 "boostrap/stage0/ReCode.c"
        String__append_cstring(message, "\" is not a scalar type");
#line 2547 "boostrap/stage0/ReCode.c"
        Source_Location__error(location, message);
#line 2548 "boostrap/stage0/ReCode.c"
        abort();
    }
}

#line 2557 "boostrap/stage0/ReCode.c"
struct Checked_Named_Type* Checked_Named_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name) {
#line 2558 "boostrap/stage0/ReCode.c"
    struct Checked_Named_Type* type = (struct Checked_Named_Type*) Checked_Type__create_kind(kind, kind_size, location);
#line 2559 "boostrap/stage0/ReCode.c"
    type->name = name;
#line 2560 "boostrap/stage0/ReCode.c"
    return type;
}

#line 2569 "boostrap/stage0/ReCode.c"
struct Checked_Enum_Member* Checked_Enum_Member__create(struct Source_Location* location, struct String* name) {
#line 2570 "boostrap/stage0/ReCode.c"
    struct Checked_Enum_Member* member = (struct Checked_Enum_Member*) malloc(sizeof(struct Checked_Enum_Member));
#line 2571 "boostrap/stage0/ReCode.c"
    member->location = location;
#line 2572 "boostrap/stage0/ReCode.c"
    member->name = name;
#line 2573 "boostrap/stage0/ReCode.c"
    member->next_member = NULL;
#line 2574 "boostrap/stage0/ReCode.c"
    return member;
}

#line 2582 "boostrap/stage0/ReCode.c"
struct Checked_Enum_Type* Checked_Enum_Type__create(struct Source_Location* location, struct String* name) {
#line 2583 "boostrap/stage0/ReCode.c"
    struct Checked_Enum_Type* type = (struct Checked_Enum_Type*) Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__ENUM, sizeof(struct Checked_Enum_Type), location, name);
#line 2584 "boostrap/stage0/ReCode.c"
    type->first_member = NULL;
#line 2585 "boostrap/stage0/ReCode.c"
    return type;
}

#line 2588 "boostrap/stage0/ReCode.c"
struct Checked_Enum_Member* Checked_Enum_Type__find_member(struct Checked_Enum_Type* self, struct String* name) {
#line 2589 "boostrap/stage0/ReCode.c"
    struct Checked_Enum_Member* member = self->first_member;
#line 2590 "boostrap/stage0/ReCode.c"
    while (member != NULL) {
#line 2591 "boostrap/stage0/ReCode.c"
        if (String__equals_string(name, member->name)) {
#line 2592 "boostrap/stage0/ReCode.c"
            break;
        }
#line 2594 "boostrap/stage0/ReCode.c"
        member = member->next_member;
    }
#line 2596 "boostrap/stage0/ReCode.c"
    return member;
}

#line 2606 "boostrap/stage0/ReCode.c"
struct Checked_Function_Parameter* Checked_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2607 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Parameter* parameter = (struct Checked_Function_Parameter*) malloc(sizeof(struct Checked_Function_Parameter));
#line 2608 "boostrap/stage0/ReCode.c"
    parameter->location = location;
#line 2609 "boostrap/stage0/ReCode.c"
    parameter->name = name;
#line 2610 "boostrap/stage0/ReCode.c"
    parameter->type = type;
#line 2611 "boostrap/stage0/ReCode.c"
    parameter->next_parameter = NULL;
#line 2612 "boostrap/stage0/ReCode.c"
    return parameter;
}

#line 2621 "boostrap/stage0/ReCode.c"
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct String* name, struct Checked_Type* return_type) {
#line 2622 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Type* type = (struct Checked_Function_Type*) Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__FUNCTION, sizeof(struct Checked_Function_Type), location, name);
#line 2623 "boostrap/stage0/ReCode.c"
    type->return_type = return_type;
#line 2624 "boostrap/stage0/ReCode.c"
    type->first_parameter = NULL;
#line 2625 "boostrap/stage0/ReCode.c"
    return type;
}

#line 2628 "boostrap/stage0/ReCode.c"
bool Checked_Function_Type__equals(struct Checked_Function_Type* self, struct Checked_Type* other_type) {
#line 2629 "boostrap/stage0/ReCode.c"
    if (other_type->kind != self->super.super.kind) {
#line 2630 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 2632 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) other_type;
#line 2633 "boostrap/stage0/ReCode.c"
    if (!Checked_Type__equals(self->return_type, function_type->return_type)) {
#line 2634 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 2636 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Parameter* self_parameter = self->first_parameter;
#line 2637 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2638 "boostrap/stage0/ReCode.c"
    while (self_parameter != NULL && function_parameter != NULL) {
#line 2639 "boostrap/stage0/ReCode.c"
        if (!Checked_Type__equals(self_parameter->type, function_parameter->type)) {
#line 2640 "boostrap/stage0/ReCode.c"
            return false;
        }
#line 2642 "boostrap/stage0/ReCode.c"
        self_parameter = self_parameter->next_parameter;
#line 2643 "boostrap/stage0/ReCode.c"
        function_parameter = function_parameter->next_parameter;
    }
#line 2645 "boostrap/stage0/ReCode.c"
    if (self_parameter != NULL || function_parameter != NULL) {
#line 2646 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 2648 "boostrap/stage0/ReCode.c"
    return true;
}

#line 2656 "boostrap/stage0/ReCode.c"
struct Checked_Pointer_Type* Checked_Pointer_Type__create(struct Source_Location* location, struct Checked_Type* other_type) {
#line 2657 "boostrap/stage0/ReCode.c"
    struct Checked_Pointer_Type* type = (struct Checked_Pointer_Type*) Checked_Type__create_kind(CHECKED_TYPE_KIND__POINTER, sizeof(struct Checked_Pointer_Type), location);
#line 2658 "boostrap/stage0/ReCode.c"
    type->other_type = other_type;
#line 2659 "boostrap/stage0/ReCode.c"
    return type;
}

#line 2662 "boostrap/stage0/ReCode.c"
bool Checked_Pointer_Type__equals(struct Checked_Pointer_Type* self, struct Checked_Type* other_type) {
#line 2663 "boostrap/stage0/ReCode.c"
    if (other_type->kind != self->super.kind) {
#line 2664 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 2666 "boostrap/stage0/ReCode.c"
    return Checked_Type__equals(self->other_type, ((struct Checked_Pointer_Type*) other_type)->other_type);
}

#line 2676 "boostrap/stage0/ReCode.c"
struct Checked_Struct_Member* Checked_Struct_Member__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2677 "boostrap/stage0/ReCode.c"
    struct Checked_Struct_Member* member = (struct Checked_Struct_Member*) malloc(sizeof(struct Checked_Struct_Member));
#line 2678 "boostrap/stage0/ReCode.c"
    member->location = location;
#line 2679 "boostrap/stage0/ReCode.c"
    member->name = name;
#line 2680 "boostrap/stage0/ReCode.c"
    member->type = type;
#line 2681 "boostrap/stage0/ReCode.c"
    member->next_member = NULL;
#line 2682 "boostrap/stage0/ReCode.c"
    return member;
}

#line 2690 "boostrap/stage0/ReCode.c"
struct Checked_Struct_Type* Checked_Struct_Type__create(struct Source_Location* location, struct String* name) {
#line 2691 "boostrap/stage0/ReCode.c"
    struct Checked_Struct_Type* type = (struct Checked_Struct_Type*) Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__STRUCT, sizeof(struct Checked_Struct_Type), location, name);
#line 2692 "boostrap/stage0/ReCode.c"
    type->first_member = NULL;
#line 2693 "boostrap/stage0/ReCode.c"
    return type;
}

#line 2696 "boostrap/stage0/ReCode.c"
struct Checked_Struct_Member* Checked_Struct_Type__find_member(struct Checked_Struct_Type* self, struct String* name) {
#line 2697 "boostrap/stage0/ReCode.c"
    struct Checked_Struct_Member* member = self->first_member;
#line 2698 "boostrap/stage0/ReCode.c"
    while (member != NULL) {
#line 2699 "boostrap/stage0/ReCode.c"
        if (String__equals_string(name, member->name)) {
#line 2700 "boostrap/stage0/ReCode.c"
            break;
        }
#line 2702 "boostrap/stage0/ReCode.c"
        member = member->next_member;
    }
#line 2704 "boostrap/stage0/ReCode.c"
    return member;
}

#line 2707 "boostrap/stage0/ReCode.c"
bool Checked_Struct_Type__equals(struct Checked_Struct_Type* self, struct Checked_Type* other_type) {
#line 2708 "boostrap/stage0/ReCode.c"
    if (self->super.super.kind != other_type->kind) {
#line 2709 "boostrap/stage0/ReCode.c"
        return false;
    }
#line 2711 "boostrap/stage0/ReCode.c"
    return String__equals_string(self->super.name, ((struct Checked_Struct_Type*) other_type)->super.name);
}

#line 2774 "boostrap/stage0/ReCode.c"
void File__write_checked_type(struct File* self, struct Checked_Type* type) {
#line 2800 "boostrap/stage0/ReCode.c"
    if (type == NULL) {
#line 2801 "boostrap/stage0/ReCode.c"
        File__write_cstring(self, "null");
    } else if (type->kind <= CHECKED_TYPE_KIND__NULL) {
#line 2803 "boostrap/stage0/ReCode.c"
        struct Checked_Named_Type* named_type = (struct Checked_Named_Type*) type;
#line 2804 "boostrap/stage0/ReCode.c"
        File__write_string(self, named_type->name);
    } else if (type->kind == CHECKED_TYPE_KIND__STRUCT) {
#line 2806 "boostrap/stage0/ReCode.c"
        struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) type;
#line 2807 "boostrap/stage0/ReCode.c"
        File__write_cstring(self, "struct ");
#line 2808 "boostrap/stage0/ReCode.c"
        File__write_string(self, struct_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__FUNCTION) {
#line 2810 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) type;
#line 2811 "boostrap/stage0/ReCode.c"
        File__write_checked_type(self, function_type->return_type);
#line 2812 "boostrap/stage0/ReCode.c"
        File__write_char(self, ' ');
#line 2813 "boostrap/stage0/ReCode.c"
        File__write_string(self, function_type->super.name);
#line 2814 "boostrap/stage0/ReCode.c"
        File__write_char(self, '(');
#line 2815 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2816 "boostrap/stage0/ReCode.c"
        while (function_parameter != NULL) {
#line 2817 "boostrap/stage0/ReCode.c"
            File__write_checked_function_parameter(self, function_parameter);
#line 2818 "boostrap/stage0/ReCode.c"
            function_parameter = function_parameter->next_parameter;
#line 2819 "boostrap/stage0/ReCode.c"
            if (function_parameter != NULL) {
#line 2820 "boostrap/stage0/ReCode.c"
                File__write_cstring(self, ", ");
            }
        }
#line 2823 "boostrap/stage0/ReCode.c"
        File__write_char(self, ')');
    } else if (type->kind == CHECKED_TYPE_KIND__ENUM) {
#line 2825 "boostrap/stage0/ReCode.c"
        struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) type;
#line 2826 "boostrap/stage0/ReCode.c"
        File__write_cstring(self, "enum ");
#line 2827 "boostrap/stage0/ReCode.c"
        File__write_string(self, enum_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__POINTER) {
#line 2829 "boostrap/stage0/ReCode.c"
        struct Checked_Pointer_Type* pointer_type = (struct Checked_Pointer_Type*) type;
#line 2830 "boostrap/stage0/ReCode.c"
        File__write_checked_type(self, pointer_type->other_type);
#line 2831 "boostrap/stage0/ReCode.c"
        File__write_char(self, '*');
    } else {
#line 2833 "boostrap/stage0/ReCode.c"
        Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2834 "boostrap/stage0/ReCode.c"
        abort();
    }
}

#line 2776 "boostrap/stage0/ReCode.c"
void File__write_checked_function_parameter(struct File* self, struct Checked_Function_Parameter* parameter) {
#line 2777 "boostrap/stage0/ReCode.c"
    if (parameter->type->kind == CHECKED_TYPE_KIND__POINTER && ((struct Checked_Pointer_Type*) parameter->type)->other_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
#line 2778 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) ((struct Checked_Pointer_Type*) parameter->type)->other_type;
#line 2779 "boostrap/stage0/ReCode.c"
        File__write_checked_type(self, function_type->return_type);
#line 2780 "boostrap/stage0/ReCode.c"
        File__write_cstring(self, " (*");
#line 2781 "boostrap/stage0/ReCode.c"
        File__write_string(self, parameter->name);
#line 2782 "boostrap/stage0/ReCode.c"
        File__write_cstring(self, ")(");
#line 2783 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2784 "boostrap/stage0/ReCode.c"
        while (function_parameter != NULL) {
#line 2785 "boostrap/stage0/ReCode.c"
            File__write_checked_function_parameter(self, function_parameter);
#line 2786 "boostrap/stage0/ReCode.c"
            function_parameter = function_parameter->next_parameter;
#line 2787 "boostrap/stage0/ReCode.c"
            if (function_parameter != NULL) {
#line 2788 "boostrap/stage0/ReCode.c"
                File__write_cstring(self, ", ");
            }
        }
#line 2791 "boostrap/stage0/ReCode.c"
        File__write_char(self, ')');
    } else {
#line 2793 "boostrap/stage0/ReCode.c"
        File__write_checked_type(self, parameter->type);
#line 2794 "boostrap/stage0/ReCode.c"
        File__write_char(self, ' ');
#line 2795 "boostrap/stage0/ReCode.c"
        File__write_string(self, parameter->name);
    }
}

#line 2858 "boostrap/stage0/ReCode.c"
struct Checked_Symbol* Checked_Symbol__create_kind(enum Checked_Symbol_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2859 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol* symbol = (struct Checked_Symbol*) malloc(kind_size);
#line 2860 "boostrap/stage0/ReCode.c"
    symbol->kind = kind;
#line 2861 "boostrap/stage0/ReCode.c"
    symbol->location = location;
#line 2862 "boostrap/stage0/ReCode.c"
    symbol->name = name;
#line 2863 "boostrap/stage0/ReCode.c"
    symbol->type = type;
#line 2864 "boostrap/stage0/ReCode.c"
    symbol->prev_symbol = NULL;
#line 2865 "boostrap/stage0/ReCode.c"
    symbol->next_symbol = NULL;
#line 2866 "boostrap/stage0/ReCode.c"
    return symbol;
}

#line 2873 "boostrap/stage0/ReCode.c"
struct Checked_Enum_Member_Symbol* Checked_Enum_Member_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2874 "boostrap/stage0/ReCode.c"
    return (struct Checked_Enum_Member_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__ENUM_MEMBER, sizeof(struct Checked_Enum_Member_Symbol), location, name, type);
}

#line 2885 "boostrap/stage0/ReCode.c"
struct Checked_Function_Symbol* Checked_Function_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Function_Type* function_type) {
#line 2886 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Symbol* symbol = (struct Checked_Function_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__FUNCTION, sizeof(struct Checked_Function_Symbol), location, name, (struct Checked_Type*) Checked_Pointer_Type__create(function_type->super.super.location, (struct Checked_Type*) function_type));
#line 2887 "boostrap/stage0/ReCode.c"
    symbol->function_type = function_type;
#line 2888 "boostrap/stage0/ReCode.c"
    symbol->checked_statements = NULL;
#line 2889 "boostrap/stage0/ReCode.c"
    return symbol;
}

#line 2896 "boostrap/stage0/ReCode.c"
struct Checked_Function_Parameter_Symbol* Checked_Function_Parameter_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2897 "boostrap/stage0/ReCode.c"
    return (struct Checked_Function_Parameter_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__FUNCTION_PARAMETER, sizeof(struct Checked_Function_Parameter_Symbol), location, name, type);
}

#line 2905 "boostrap/stage0/ReCode.c"
struct Checked_Type_Symbol* Checked_Type_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Named_Type* named_type) {
#line 2906 "boostrap/stage0/ReCode.c"
    struct Checked_Type_Symbol* symbol = (struct Checked_Type_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__TYPE, sizeof(struct Checked_Type_Symbol), location, name, NULL);
#line 2907 "boostrap/stage0/ReCode.c"
    symbol->named_type = named_type;
#line 2908 "boostrap/stage0/ReCode.c"
    return symbol;
}

#line 2915 "boostrap/stage0/ReCode.c"
struct Checked_Variable_Symbol* Checked_Variable__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2916 "boostrap/stage0/ReCode.c"
    return (struct Checked_Variable_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__VARIABLE, sizeof(struct Checked_Variable_Symbol), location, name, type);
}

#line 2925 "boostrap/stage0/ReCode.c"
struct Checked_Symbols* Checked_Symbols__create(struct Checked_Symbols* parent) {
#line 2926 "boostrap/stage0/ReCode.c"
    struct Checked_Symbols* symbols = (struct Checked_Symbols*) malloc(sizeof(struct Checked_Symbols));
#line 2927 "boostrap/stage0/ReCode.c"
    symbols->parent = parent;
#line 2928 "boostrap/stage0/ReCode.c"
    symbols->first_symbol = NULL;
#line 2929 "boostrap/stage0/ReCode.c"
    symbols->last_symbol = NULL;
#line 2930 "boostrap/stage0/ReCode.c"
    return symbols;
}

#line 2933 "boostrap/stage0/ReCode.c"
struct Checked_Symbol* Checked_Symbols__find_sibling_symbol(struct Checked_Symbols* self, struct String* name) {
#line 2934 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol* symbol = self->first_symbol;
#line 2935 "boostrap/stage0/ReCode.c"
    while (symbol != NULL) {
#line 2936 "boostrap/stage0/ReCode.c"
        if (String__equals_string(name, symbol->name)) {
#line 2937 "boostrap/stage0/ReCode.c"
            return symbol;
        }
#line 2939 "boostrap/stage0/ReCode.c"
        symbol = symbol->next_symbol;
    }
#line 2941 "boostrap/stage0/ReCode.c"
    return NULL;
}

#line 2944 "boostrap/stage0/ReCode.c"
void Checked_Symbols__append_symbol(struct Checked_Symbols* self, struct Checked_Symbol* symbol) {
#line 2945 "boostrap/stage0/ReCode.c"
    if (Checked_Symbols__find_sibling_symbol(self, symbol->name) != NULL) {
#line 2946 "boostrap/stage0/ReCode.c"
        error(String__create_from("TODO: Report symbol redeclaration"));
#line 2947 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 2950 "boostrap/stage0/ReCode.c"
    if (self->last_symbol == NULL) {
#line 2951 "boostrap/stage0/ReCode.c"
        self->first_symbol = symbol;
    } else {
#line 2953 "boostrap/stage0/ReCode.c"
        self->last_symbol->next_symbol = symbol;
#line 2954 "boostrap/stage0/ReCode.c"
        symbol->prev_symbol = self->last_symbol;
    }
#line 2956 "boostrap/stage0/ReCode.c"
    self->last_symbol = symbol;
}

#line 2959 "boostrap/stage0/ReCode.c"
struct Checked_Symbol* Checked_Symbols__find_symbol(struct Checked_Symbols* self, struct String* name) {
#line 2960 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol* symbol = self->last_symbol;
#line 2961 "boostrap/stage0/ReCode.c"
    while (symbol != NULL) {
#line 2962 "boostrap/stage0/ReCode.c"
        if (String__equals_string(name, symbol->name)) {
#line 2963 "boostrap/stage0/ReCode.c"
            return symbol;
        }
#line 2965 "boostrap/stage0/ReCode.c"
        symbol = symbol->prev_symbol;
    }
#line 2967 "boostrap/stage0/ReCode.c"
    if (self->parent != NULL) {
#line 2968 "boostrap/stage0/ReCode.c"
        return Checked_Symbols__find_symbol(self->parent, name);
    }
#line 2970 "boostrap/stage0/ReCode.c"
    return NULL;
}

#line 3013 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checked_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type) {
#line 3014 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* expression = (struct Checked_Expression*) malloc(kind_size);
#line 3015 "boostrap/stage0/ReCode.c"
    expression->kind = kind;
#line 3016 "boostrap/stage0/ReCode.c"
    expression->location = location;
#line 3017 "boostrap/stage0/ReCode.c"
    expression->type = type;
#line 3018 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3027 "boostrap/stage0/ReCode.c"
struct Checked_Binary_Expression* Checked_Binary_Expression__create_kind(enum Checked_Expression_Kind kind, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3028 "boostrap/stage0/ReCode.c"
    struct Checked_Binary_Expression* expression = (struct Checked_Binary_Expression*) Checked_Expression__create_kind(kind, sizeof(struct Checked_Binary_Expression), location, type);
#line 3029 "boostrap/stage0/ReCode.c"
    expression->left_expression = left_expression;
#line 3030 "boostrap/stage0/ReCode.c"
    expression->right_expression = right_expression;
#line 3031 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3039 "boostrap/stage0/ReCode.c"
struct Checked_Unary_Expression* Checked_Unary_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3040 "boostrap/stage0/ReCode.c"
    struct Checked_Unary_Expression* expression = (struct Checked_Unary_Expression*) Checked_Expression__create_kind(kind, kind_size, location, type);
#line 3041 "boostrap/stage0/ReCode.c"
    expression->other_expression = other_expression;
#line 3042 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3049 "boostrap/stage0/ReCode.c"
struct Checked_Add_Expression* Checked_Add_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3050 "boostrap/stage0/ReCode.c"
    return (struct Checked_Add_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADD, location, type, left_expression, right_expression);
}

#line 3057 "boostrap/stage0/ReCode.c"
struct Checked_Address_Of_Expression* Checked_Address_Of_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3058 "boostrap/stage0/ReCode.c"
    return (struct Checked_Address_Of_Expression*) Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADDRESS_OF, sizeof(struct Checked_Address_Of_Expression), location, type, other_expression);
}

#line 3067 "boostrap/stage0/ReCode.c"
struct Checked_Array_Access_Expression* Checked_Array_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* array_expression, struct Checked_Expression* index_expression) {
#line 3068 "boostrap/stage0/ReCode.c"
    struct Checked_Array_Access_Expression* expression = (struct Checked_Array_Access_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__ARRAY_ACCESS, sizeof(struct Checked_Array_Access_Expression), location, type);
#line 3069 "boostrap/stage0/ReCode.c"
    expression->array_expression = array_expression;
#line 3070 "boostrap/stage0/ReCode.c"
    expression->index_expression = index_expression;
#line 3071 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3079 "boostrap/stage0/ReCode.c"
struct Checked_Bool_Expression* Checked_Bool_Expression__create(struct Source_Location* location, struct Checked_Type* type, bool value) {
#line 3080 "boostrap/stage0/ReCode.c"
    struct Checked_Bool_Expression* expression = (struct Checked_Bool_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__BOOL, sizeof(struct Checked_Bool_Expression), location, type);
#line 3081 "boostrap/stage0/ReCode.c"
    expression->value = value;
#line 3082 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3090 "boostrap/stage0/ReCode.c"
struct Checked_Call_Argument* Checked_Call_Argument__create(struct Checked_Expression* expression) {
#line 3091 "boostrap/stage0/ReCode.c"
    struct Checked_Call_Argument* argument = (struct Checked_Call_Argument*) malloc(sizeof(struct Checked_Call_Argument));
#line 3092 "boostrap/stage0/ReCode.c"
    argument->expression = expression;
#line 3093 "boostrap/stage0/ReCode.c"
    argument->next_argument = NULL;
#line 3094 "boostrap/stage0/ReCode.c"
    return argument;
}

#line 3103 "boostrap/stage0/ReCode.c"
struct Checked_Call_Expression* Checked_Call_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* callee_expression, struct Checked_Call_Argument* first_argument) {
#line 3104 "boostrap/stage0/ReCode.c"
    struct Checked_Call_Expression* expression = (struct Checked_Call_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CALL, sizeof(struct Checked_Call_Expression), location, type);
#line 3105 "boostrap/stage0/ReCode.c"
    expression->callee_expression = callee_expression;
#line 3106 "boostrap/stage0/ReCode.c"
    expression->first_argument = first_argument;
#line 3107 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3115 "boostrap/stage0/ReCode.c"
struct Checked_Cast_Expression* Checked_Cast_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3116 "boostrap/stage0/ReCode.c"
    struct Checked_Cast_Expression* expression = (struct Checked_Cast_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CAST, sizeof(struct Checked_Cast_Expression), location, type);
#line 3117 "boostrap/stage0/ReCode.c"
    expression->other_expression = other_expression;
#line 3118 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3126 "boostrap/stage0/ReCode.c"
struct Checked_Character_Expression* Checked_Character_Expression__create(struct Source_Location* location, struct Checked_Type* type, char value) {
#line 3127 "boostrap/stage0/ReCode.c"
    struct Checked_Character_Expression* expression = (struct Checked_Character_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CHARACTER, sizeof(struct Checked_Character_Expression), location, type);
#line 3128 "boostrap/stage0/ReCode.c"
    expression->value = value;
#line 3129 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3136 "boostrap/stage0/ReCode.c"
struct Checked_Divide_Expression* Checked_Divide_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3137 "boostrap/stage0/ReCode.c"
    return (struct Checked_Divide_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__DIVIDE, location, type, left_expression, right_expression);
}

#line 3144 "boostrap/stage0/ReCode.c"
struct Checked_Equals_Expression* Checked_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3145 "boostrap/stage0/ReCode.c"
    return (struct Checked_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__EQUALS, location, type, left_expression, right_expression);
}

#line 3152 "boostrap/stage0/ReCode.c"
struct Checked_Greater_Expression* Checked_Greater_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3153 "boostrap/stage0/ReCode.c"
    return (struct Checked_Greater_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER, location, type, left_expression, right_expression);
}

#line 3160 "boostrap/stage0/ReCode.c"
struct Checked_Greater_Or_Equals_Expression* Checked_Greater_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3161 "boostrap/stage0/ReCode.c"
    return (struct Checked_Greater_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS, location, type, left_expression, right_expression);
}

#line 3169 "boostrap/stage0/ReCode.c"
struct Checked_Group_Expression* Checked_Group_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3170 "boostrap/stage0/ReCode.c"
    struct Checked_Group_Expression* expression = (struct Checked_Group_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__GROUP, sizeof(struct Checked_Group_Expression), location, type);
#line 3171 "boostrap/stage0/ReCode.c"
    expression->other_expression = other_expression;
#line 3172 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3180 "boostrap/stage0/ReCode.c"
struct Checked_Integer_Expression* Checked_Integer_Expression__create(struct Source_Location* location, struct Checked_Type* type, uint64_t value) {
#line 3181 "boostrap/stage0/ReCode.c"
    struct Checked_Integer_Expression* expression = (struct Checked_Integer_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__INTEGER, sizeof(struct Checked_Integer_Expression), location, type);
#line 3182 "boostrap/stage0/ReCode.c"
    expression->value = value;
#line 3183 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3190 "boostrap/stage0/ReCode.c"
struct Checked_Less_Expression* Checked_Less_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3191 "boostrap/stage0/ReCode.c"
    return (struct Checked_Less_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS, location, type, left_expression, right_expression);
}

#line 3198 "boostrap/stage0/ReCode.c"
struct Checked_Less_Or_Equals_Expression* Checked_Less_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3199 "boostrap/stage0/ReCode.c"
    return (struct Checked_Less_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS, location, type, left_expression, right_expression);
}

#line 3206 "boostrap/stage0/ReCode.c"
struct Checked_Logic_And_Expression* Checked_Logic_And_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3207 "boostrap/stage0/ReCode.c"
    return (struct Checked_Logic_And_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_AND, location, type, left_expression, right_expression);
}

#line 3214 "boostrap/stage0/ReCode.c"
struct Checked_Logic_Or_Expression* Checked_Logic_Or_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3215 "boostrap/stage0/ReCode.c"
    return (struct Checked_Logic_Or_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_OR, location, type, left_expression, right_expression);
}

#line 3224 "boostrap/stage0/ReCode.c"
struct Checked_Member_Access_Expression* Checked_Member_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* object_expression, struct Checked_Struct_Member* member) {
#line 3225 "boostrap/stage0/ReCode.c"
    struct Checked_Member_Access_Expression* expression = (struct Checked_Member_Access_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__MEMBER_ACCESS, sizeof(struct Checked_Member_Access_Expression), location, type);
#line 3226 "boostrap/stage0/ReCode.c"
    expression->object_expression = object_expression;
#line 3227 "boostrap/stage0/ReCode.c"
    expression->member = member;
#line 3228 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3235 "boostrap/stage0/ReCode.c"
struct Checked_Minus_Expression* Checked_Minus_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3236 "boostrap/stage0/ReCode.c"
    return (struct Checked_Minus_Expression*) Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MINUS, sizeof(struct Checked_Minus_Expression), location, type, other_expression);
}

#line 3243 "boostrap/stage0/ReCode.c"
struct Checked_Modulo_Expression* Checked_Modulo_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3244 "boostrap/stage0/ReCode.c"
    return (struct Checked_Modulo_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MODULO, location, type, left_expression, right_expression);
}

#line 3251 "boostrap/stage0/ReCode.c"
struct Checked_Multiply_Expression* Checked_Multiply_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3252 "boostrap/stage0/ReCode.c"
    return (struct Checked_Multiply_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MULTIPLY, location, type, left_expression, right_expression);
}

#line 3259 "boostrap/stage0/ReCode.c"
struct Checked_Not_Expression* Checked_Not_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3260 "boostrap/stage0/ReCode.c"
    return (struct Checked_Not_Expression*) Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT, sizeof(struct Checked_Not_Expression), location, type, other_expression);
}

#line 3267 "boostrap/stage0/ReCode.c"
struct Checked_Not_Equals_Expression* Checked_Not_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3268 "boostrap/stage0/ReCode.c"
    return (struct Checked_Not_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT_EQUALS, location, type, left_expression, right_expression);
}

#line 3275 "boostrap/stage0/ReCode.c"
struct Checked_Null_Expression* Checked_Null_Expression__create(struct Source_Location* location, struct Checked_Type* type) {
#line 3276 "boostrap/stage0/ReCode.c"
    return (struct Checked_Null_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__NULL, sizeof(struct Checked_Null_Expression), location, type);
}

#line 3284 "boostrap/stage0/ReCode.c"
struct Checked_Sizeof_Expression* Checked_Sizeof_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Type* sized_type) {
#line 3285 "boostrap/stage0/ReCode.c"
    struct Checked_Sizeof_Expression* expression = (struct Checked_Sizeof_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SIZEOF, sizeof(struct Checked_Sizeof_Expression), location, type);
#line 3286 "boostrap/stage0/ReCode.c"
    expression->sized_type = sized_type;
#line 3287 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3295 "boostrap/stage0/ReCode.c"
struct Checked_String_Expression* Checked_String_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct String* value) {
#line 3296 "boostrap/stage0/ReCode.c"
    struct Checked_String_Expression* expression = (struct Checked_String_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__STRING, sizeof(struct Checked_String_Expression), location, type);
#line 3297 "boostrap/stage0/ReCode.c"
    expression->value = value;
#line 3298 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3305 "boostrap/stage0/ReCode.c"
struct Checked_Substract_Expression* Checked_Substract_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3306 "boostrap/stage0/ReCode.c"
    return (struct Checked_Substract_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__SUBSTRACT, location, type, left_expression, right_expression);
}

#line 3314 "boostrap/stage0/ReCode.c"
struct Checked_Symbol_Expression* Checked_Symbol_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Symbol* symbol) {
#line 3315 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol_Expression* expression = (struct Checked_Symbol_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SYMBOL, sizeof(struct Checked_Symbol_Expression), location, type);
#line 3316 "boostrap/stage0/ReCode.c"
    expression->symbol = symbol;
#line 3317 "boostrap/stage0/ReCode.c"
    return expression;
}

#line 3340 "boostrap/stage0/ReCode.c"
struct Checked_Statement* Checked_Statement__create_kind(enum Checked_Statement_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 3341 "boostrap/stage0/ReCode.c"
    struct Checked_Statement* statement = (struct Checked_Statement*) malloc(kind_size);
#line 3342 "boostrap/stage0/ReCode.c"
    statement->kind = kind;
#line 3343 "boostrap/stage0/ReCode.c"
    statement->location = location;
#line 3344 "boostrap/stage0/ReCode.c"
    statement->next_statement = NULL;
#line 3345 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3354 "boostrap/stage0/ReCode.c"
struct Checked_Assignment_Statement* Checked_Assignment_Statement__create(struct Source_Location* location, struct Checked_Expression* object_expression, struct Checked_Expression* value_expression) {
#line 3355 "boostrap/stage0/ReCode.c"
    struct Checked_Assignment_Statement* statement = (struct Checked_Assignment_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__ASSIGNMENT, sizeof(struct Checked_Assignment_Statement), location);
#line 3356 "boostrap/stage0/ReCode.c"
    statement->object_expression = object_expression;
#line 3357 "boostrap/stage0/ReCode.c"
    statement->value_expression = value_expression;
#line 3358 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3366 "boostrap/stage0/ReCode.c"
struct Checked_Block_Statement* Checked_Block_Statement__create(struct Source_Location* location, struct Checked_Statements* statements) {
#line 3367 "boostrap/stage0/ReCode.c"
    struct Checked_Block_Statement* statement = (struct Checked_Block_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BLOCK, sizeof(struct Checked_Block_Statement), location);
#line 3368 "boostrap/stage0/ReCode.c"
    statement->statements = statements;
#line 3369 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3376 "boostrap/stage0/ReCode.c"
struct Checked_Break_Statement* Checked_Break_Statement__create(struct Source_Location* location) {
#line 3377 "boostrap/stage0/ReCode.c"
    return (struct Checked_Break_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BREAK, sizeof(struct Checked_Break_Statement), location);
}

#line 3385 "boostrap/stage0/ReCode.c"
struct Checked_Expression_Statement* Checked_Expression_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) {
#line 3386 "boostrap/stage0/ReCode.c"
    struct Checked_Expression_Statement* statement = (struct Checked_Expression_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__EXPRESSION, sizeof(struct Checked_Expression_Statement), location);
#line 3387 "boostrap/stage0/ReCode.c"
    statement->expression = expression;
#line 3388 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3398 "boostrap/stage0/ReCode.c"
struct Checked_If_Statement* Checked_If_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* true_statement, struct Checked_Statement* false_statement) {
#line 3399 "boostrap/stage0/ReCode.c"
    struct Checked_If_Statement* statement = (struct Checked_If_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__IF, sizeof(struct Checked_If_Statement), location);
#line 3400 "boostrap/stage0/ReCode.c"
    statement->condition_expression = condition_expression;
#line 3401 "boostrap/stage0/ReCode.c"
    statement->true_statement = true_statement;
#line 3402 "boostrap/stage0/ReCode.c"
    statement->false_statement = false_statement;
#line 3403 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3411 "boostrap/stage0/ReCode.c"
struct Checked_Return_Statement* Checked_Return_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) {
#line 3412 "boostrap/stage0/ReCode.c"
    struct Checked_Return_Statement* statement = (struct Checked_Return_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__RETURN, sizeof(struct Checked_Return_Statement), location);
#line 3413 "boostrap/stage0/ReCode.c"
    statement->expression = expression;
#line 3414 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3424 "boostrap/stage0/ReCode.c"
struct Checked_Variable_Statement* Checked_Variable_Statement__create(struct Source_Location* location, struct Checked_Variable_Symbol* variable, struct Checked_Expression* expression, bool is_external) {
#line 3425 "boostrap/stage0/ReCode.c"
    struct Checked_Variable_Statement* statement = (struct Checked_Variable_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__VARIABLE, sizeof(struct Checked_Variable_Statement), location);
#line 3426 "boostrap/stage0/ReCode.c"
    statement->variable = variable;
#line 3427 "boostrap/stage0/ReCode.c"
    statement->expression = expression;
#line 3428 "boostrap/stage0/ReCode.c"
    statement->is_external = is_external;
#line 3429 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3438 "boostrap/stage0/ReCode.c"
struct Checked_While_Statement* Checked_While_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* body_statement) {
#line 3439 "boostrap/stage0/ReCode.c"
    struct Checked_While_Statement* statement = (struct Checked_While_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__WHILE, sizeof(struct Checked_While_Statement), location);
#line 3440 "boostrap/stage0/ReCode.c"
    statement->condition_expression = condition_expression;
#line 3441 "boostrap/stage0/ReCode.c"
    statement->body_statement = body_statement;
#line 3442 "boostrap/stage0/ReCode.c"
    return statement;
}

#line 3450 "boostrap/stage0/ReCode.c"
struct Checked_Statements* Checked_Statements__create() {
#line 3451 "boostrap/stage0/ReCode.c"
    struct Checked_Statements* statements = (struct Checked_Statements*) malloc(sizeof(struct Checked_Statements));
#line 3452 "boostrap/stage0/ReCode.c"
    statements->first_statement = NULL;
#line 3453 "boostrap/stage0/ReCode.c"
    statements->last_statement = NULL;
#line 3454 "boostrap/stage0/ReCode.c"
    return statements;
}

#line 3457 "boostrap/stage0/ReCode.c"
void Checked_Statements__append(struct Checked_Statements* self, struct Checked_Statement* statement) {
#line 3458 "boostrap/stage0/ReCode.c"
    if (self->first_statement == NULL) {
#line 3459 "boostrap/stage0/ReCode.c"
        self->first_statement = statement;
    } else {
#line 3461 "boostrap/stage0/ReCode.c"
        self->last_statement->next_statement = statement;
    }
#line 3463 "boostrap/stage0/ReCode.c"
    self->last_statement = statement;
}

#line 3485 "boostrap/stage0/ReCode.c"
void Checker__append_type(struct Checker* self, struct Checked_Named_Type* type) {
#line 3513 "boostrap/stage0/ReCode.c"
    if (self->first_type == NULL) {
#line 3514 "boostrap/stage0/ReCode.c"
        self->first_type = type;
    } else {
#line 3516 "boostrap/stage0/ReCode.c"
        self->last_type->super.next_type = (struct Checked_Type*) type;
    }
#line 3518 "boostrap/stage0/ReCode.c"
    self->last_type = type;
#line 3520 "boostrap/stage0/ReCode.c"
    Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Type_Symbol__create(type->super.location, type->name, type));
}

#line 3487 "boostrap/stage0/ReCode.c"
struct Checker* Checker__create() {
#line 3488 "boostrap/stage0/ReCode.c"
    struct Checker* checker = (struct Checker*) malloc(sizeof(struct Checker));
#line 3489 "boostrap/stage0/ReCode.c"
    checker->first_type = NULL;
#line 3490 "boostrap/stage0/ReCode.c"
    checker->last_type = NULL;
#line 3491 "boostrap/stage0/ReCode.c"
    checker->symbols = Checked_Symbols__create(NULL);
#line 3493 "boostrap/stage0/ReCode.c"
    struct Source_Location* location = Source_Location__create(NULL, (uint16_t) 0, (uint16_t) 1);
#line 3494 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__BOOL, sizeof(struct Checked_Named_Type), location, String__create_from("bool")));
#line 3495 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__CHAR, sizeof(struct Checked_Named_Type), location, String__create_from("char")));
#line 3496 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT16_T, sizeof(struct Checked_Named_Type), location, String__create_from("int16_t")));
#line 3497 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT32_T, sizeof(struct Checked_Named_Type), location, String__create_from("int32_t")));
#line 3498 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT64_T, sizeof(struct Checked_Named_Type), location, String__create_from("int64_t")));
#line 3499 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT8_T, sizeof(struct Checked_Named_Type), location, String__create_from("int8_t")));
#line 3500 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__SIZE_T, sizeof(struct Checked_Named_Type), location, String__create_from("size_t")));
#line 3501 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT16_T, sizeof(struct Checked_Named_Type), location, String__create_from("uint16_t")));
#line 3502 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT32_T, sizeof(struct Checked_Named_Type), location, String__create_from("uint32_t")));
#line 3503 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT64_T, sizeof(struct Checked_Named_Type), location, String__create_from("uint64_t")));
#line 3504 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT8_T, sizeof(struct Checked_Named_Type), location, String__create_from("uint8_t")));
#line 3505 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__VOID, sizeof(struct Checked_Named_Type), location, String__create_from("void")));
#line 3506 "boostrap/stage0/ReCode.c"
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__NULL, sizeof(struct Checked_Named_Type), location, String__create_from("null")));
#line 3507 "boostrap/stage0/ReCode.c"
    checker->last_builting_type = checker->last_type;
#line 3509 "boostrap/stage0/ReCode.c"
    return checker;
}

#line 3523 "boostrap/stage0/ReCode.c"
struct Checked_Named_Type* Checker__find_type(struct Checker* self, struct String* name) {
#line 3524 "boostrap/stage0/ReCode.c"
    struct Checked_Named_Type* type = self->first_type;
#line 3525 "boostrap/stage0/ReCode.c"
    while (type != NULL) {
#line 3526 "boostrap/stage0/ReCode.c"
        if (String__equals_string(name, type->name)) {
#line 3527 "boostrap/stage0/ReCode.c"
            break;
        }
#line 3529 "boostrap/stage0/ReCode.c"
        type = (struct Checked_Named_Type*) type->super.next_type;
    }
#line 3531 "boostrap/stage0/ReCode.c"
    return type;
}

#line 3534 "boostrap/stage0/ReCode.c"
struct Checked_Named_Type* Checker__get_builtin_type(struct Checker* self, enum Checked_Type_Kind kind) {
#line 3535 "boostrap/stage0/ReCode.c"
    struct Checked_Named_Type* type = self->first_type;
#line 3536 "boostrap/stage0/ReCode.c"
    struct Checked_Named_Type* custom_type = (struct Checked_Named_Type*) self->last_builting_type->super.next_type;
#line 3537 "boostrap/stage0/ReCode.c"
    while (type != custom_type) {
#line 3538 "boostrap/stage0/ReCode.c"
        if (type->super.kind == kind) {
#line 3539 "boostrap/stage0/ReCode.c"
            return type;
        }
#line 3541 "boostrap/stage0/ReCode.c"
        type = (struct Checked_Named_Type*) type->super.next_type;
    }
#line 3543 "boostrap/stage0/ReCode.c"
    error(String__create_from("No such builtin type"));
#line 3544 "boostrap/stage0/ReCode.c"
    abort();
}

#line 3547 "boostrap/stage0/ReCode.c"
struct Checked_Type* Checker__resolve_type(struct Checker* self, struct Parsed_Type* parsed_type) {
#line 3548 "boostrap/stage0/ReCode.c"
    if (parsed_type->kind == PARSED_TYPE_KIND__NAMED) {
#line 3549 "boostrap/stage0/ReCode.c"
        struct Checked_Named_Type* type = Checker__find_type(self, ((struct Parsed_Named_Type*) parsed_type)->name);
#line 3550 "boostrap/stage0/ReCode.c"
        if (type != NULL) {
#line 3551 "boostrap/stage0/ReCode.c"
            return (struct Checked_Type*) type;
        }
    }
#line 3554 "boostrap/stage0/ReCode.c"
    if (parsed_type->kind == PARSED_TYPE_KIND__POINTER) {
#line 3555 "boostrap/stage0/ReCode.c"
        return (struct Checked_Type*) Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((struct Parsed_Pointer_Type*) parsed_type)->other_type));
    }
#line 3557 "boostrap/stage0/ReCode.c"
    if (parsed_type->kind == PARSED_TYPE_KIND__STRUCT) {
#line 3558 "boostrap/stage0/ReCode.c"
        struct Checked_Type* type = Checker__resolve_type(self, ((struct Parsed_Struct_Type*) parsed_type)->other_type);
#line 3559 "boostrap/stage0/ReCode.c"
        if (type->kind != CHECKED_TYPE_KIND__STRUCT) {
#line 3560 "boostrap/stage0/ReCode.c"
            TODO("Report unexpected type");
#line 3561 "boostrap/stage0/ReCode.c"
            abort();
        }
#line 3563 "boostrap/stage0/ReCode.c"
        return type;
    }
#line 3565 "boostrap/stage0/ReCode.c"
    TODO("Report undefined type");
#line 3566 "boostrap/stage0/ReCode.c"
    abort();
}

#line 3569 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_expression(struct Checker* self, struct Parsed_Expression* parsed_expression) {
#line 3854 "boostrap/stage0/ReCode.c"
    if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ADD) {
#line 3855 "boostrap/stage0/ReCode.c"
        return Checker__check_add_expression(self, (struct Parsed_Add_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ADDRESS_OF) {
#line 3857 "boostrap/stage0/ReCode.c"
        return Checker__check_address_of_expression(self, (struct Parsed_Address_Of_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ARRAY_ACCESS) {
#line 3859 "boostrap/stage0/ReCode.c"
        return Checker__check_array_access_expression(self, (struct Parsed_Array_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__BOOL) {
#line 3861 "boostrap/stage0/ReCode.c"
        return Checker__check_bool_expression(self, (struct Parsed_Bool_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CALL) {
#line 3863 "boostrap/stage0/ReCode.c"
        return Checker__check_call_expression(self, (struct Parsed_Call_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CAST) {
#line 3865 "boostrap/stage0/ReCode.c"
        return Checker__check_cast_expression(self, (struct Parsed_Cast_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CHARACTER) {
#line 3867 "boostrap/stage0/ReCode.c"
        return Checker__check_character_expression(self, (struct Parsed_Character_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__DIVIDE) {
#line 3869 "boostrap/stage0/ReCode.c"
        return Checker__check_divide_expression(self, (struct Parsed_Divide_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__EQUALS) {
#line 3871 "boostrap/stage0/ReCode.c"
        return Checker__check_equals_expression(self, (struct Parsed_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GREATER) {
#line 3873 "boostrap/stage0/ReCode.c"
        return Checker__check_greater_expression(self, (struct Parsed_Greater_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS) {
#line 3875 "boostrap/stage0/ReCode.c"
        return Checker__check_greater_or_equals_expression(self, (struct Parsed_Greater_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GROUP) {
#line 3877 "boostrap/stage0/ReCode.c"
        return Checker__check_group_expression(self, (struct Parsed_Group_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__INTEGER) {
#line 3879 "boostrap/stage0/ReCode.c"
        return Checker__check_integer_expression(self, (struct Parsed_Integer_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LESS) {
#line 3881 "boostrap/stage0/ReCode.c"
        return Checker__check_less_expression(self, (struct Parsed_Less_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LESS_OR_EQUALS) {
#line 3883 "boostrap/stage0/ReCode.c"
        return Checker__check_less_or_equals_expression(self, (struct Parsed_Less_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LOGIC_AND) {
#line 3885 "boostrap/stage0/ReCode.c"
        return Checker__check_logic_and_expression(self, (struct Parsed_Logic_And_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LOGIC_OR) {
#line 3887 "boostrap/stage0/ReCode.c"
        return Checker__check_logic_or_expression(self, (struct Parsed_Logic_Or_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MEMBER_ACCESS) {
#line 3889 "boostrap/stage0/ReCode.c"
        return Checker__check_member_access_expression(self, (struct Parsed_Member_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MINUS) {
#line 3891 "boostrap/stage0/ReCode.c"
        return Checker__check_minus_expression(self, (struct Parsed_Minus_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MODULO) {
#line 3893 "boostrap/stage0/ReCode.c"
        return Checker__check_modulo_expression(self, (struct Parsed_Modulo_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MULTIPLY) {
#line 3895 "boostrap/stage0/ReCode.c"
        return Checker__check_multiply_expression(self, (struct Parsed_Multiply_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NOT) {
#line 3897 "boostrap/stage0/ReCode.c"
        return Checker__check_not_expression(self, (struct Parsed_Not_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NOT_EQUALS) {
#line 3899 "boostrap/stage0/ReCode.c"
        return Checker__check_not_equals_expression(self, (struct Parsed_Not_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NULL) {
#line 3901 "boostrap/stage0/ReCode.c"
        return Checker__check_null_expression(self, (struct Parsed_Null_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SIZEOF) {
#line 3903 "boostrap/stage0/ReCode.c"
        return Checker__check_sizeof_expression(self, (struct Parsed_Sizeof_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__STRING) {
#line 3905 "boostrap/stage0/ReCode.c"
        return Checker__check_string_expression(self, (struct Parsed_String_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SUBSTRACT) {
#line 3907 "boostrap/stage0/ReCode.c"
        return Checker__check_substract_expression(self, (struct Parsed_Substract_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SYMBOL) {
#line 3909 "boostrap/stage0/ReCode.c"
        return Checker__check_symbol_expression(self, (struct Parsed_Symbol_Expression*) parsed_expression);
    }
#line 3911 "boostrap/stage0/ReCode.c"
    Source_Location__error(parsed_expression->location, String__create_from("Unsupported expression kind"));
#line 3912 "boostrap/stage0/ReCode.c"
    abort();
}

#line 3571 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_add_expression(struct Checker* self, struct Parsed_Add_Expression* parsed_expression) {
#line 3572 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3573 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3574 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3575 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3576 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3579 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_address_of_expression(struct Checker* self, struct Parsed_Address_Of_Expression* parsed_expression) {
#line 3580 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3581 "boostrap/stage0/ReCode.c"
    if (other_expression->kind != CHECKED_EXPRESSION_KIND__SYMBOL) {
#line 3582 "boostrap/stage0/ReCode.c"
        Source_Location__error(parsed_expression->super.super.location, String__create_from("Not a symbol"));
#line 3583 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3585 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
}

#line 3588 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_array_access_expression(struct Checker* self, struct Parsed_Array_Access_Expression* parsed_expression) {
#line 3589 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* array_expression = Checker__check_expression(self, parsed_expression->array_expression);
#line 3590 "boostrap/stage0/ReCode.c"
    struct Checked_Type* array_type = array_expression->type;
#line 3591 "boostrap/stage0/ReCode.c"
    if (array_type->kind != CHECKED_TYPE_KIND__POINTER) {
#line 3592 "boostrap/stage0/ReCode.c"
        struct String* message = String__create();
#line 3593 "boostrap/stage0/ReCode.c"
        String__append_char(message, '\"');
#line 3594 "boostrap/stage0/ReCode.c"
        String__append_checked_type(message, array_type);
#line 3595 "boostrap/stage0/ReCode.c"
        String__append_cstring(message, "\" is not a pointer type.");
#line 3596 "boostrap/stage0/ReCode.c"
        Source_Location__error(parsed_expression->array_expression->location, message);
#line 3597 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3599 "boostrap/stage0/ReCode.c"
    struct Checked_Type* type = ((struct Checked_Pointer_Type*) array_type)->other_type;
#line 3600 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* index_expression = Checker__check_expression(self, parsed_expression->index_expression);
#line 3601 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__SIZE_T), index_expression->type, index_expression->location);
#line 3602 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

#line 3605 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_bool_expression(struct Checker* self, struct Parsed_Bool_Expression* parsed_expression) {
#line 3606 "boostrap/stage0/ReCode.c"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL);
#line 3607 "boostrap/stage0/ReCode.c"
    bool value = parsed_expression->value;
#line 3608 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3611 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_call_expression(struct Checker* self, struct Parsed_Call_Expression* parsed_expression) {
#line 3612 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* callee_expression = Checker__check_expression(self, parsed_expression->callee_expression);
#line 3613 "boostrap/stage0/ReCode.c"
    struct Checked_Type* callee_type = callee_expression->type;
#line 3614 "boostrap/stage0/ReCode.c"
    if (callee_type->kind != CHECKED_TYPE_KIND__POINTER || ((struct Checked_Pointer_Type*) callee_type)->other_type->kind != CHECKED_TYPE_KIND__FUNCTION) {
#line 3615 "boostrap/stage0/ReCode.c"
        Source_Location__error(parsed_expression->super.location, String__create_from("Not a function"));
#line 3616 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3618 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) ((struct Checked_Pointer_Type*) callee_type)->other_type;
#line 3619 "boostrap/stage0/ReCode.c"
    struct Checked_Call_Argument* first_argument = NULL;
#line 3620 "boostrap/stage0/ReCode.c"
    if (parsed_expression->first_argument != NULL) {
#line 3621 "boostrap/stage0/ReCode.c"
        struct Checked_Call_Argument* last_argument = NULL;
#line 3622 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 3623 "boostrap/stage0/ReCode.c"
        struct Parsed_Call_Argument* parsed_argument = parsed_expression->first_argument;
#line 3624 "boostrap/stage0/ReCode.c"
        while (function_parameter != NULL && parsed_argument != NULL) {
#line 3625 "boostrap/stage0/ReCode.c"
            struct Checked_Expression* argument_expression = Checker__check_expression(self, parsed_argument->expression);
#line 3626 "boostrap/stage0/ReCode.c"
            Checked_Type__expect_same_type(function_parameter->type, argument_expression->type, argument_expression->location);
#line 3627 "boostrap/stage0/ReCode.c"
            struct Checked_Call_Argument* argument = Checked_Call_Argument__create(argument_expression);
#line 3628 "boostrap/stage0/ReCode.c"
            if (last_argument == NULL) {
#line 3629 "boostrap/stage0/ReCode.c"
                first_argument = argument;
            } else {
#line 3631 "boostrap/stage0/ReCode.c"
                last_argument->next_argument = argument;
            }
#line 3633 "boostrap/stage0/ReCode.c"
            last_argument = argument;
#line 3634 "boostrap/stage0/ReCode.c"
            function_parameter = function_parameter->next_parameter;
#line 3635 "boostrap/stage0/ReCode.c"
            parsed_argument = parsed_argument->next_argument;
        }
#line 3637 "boostrap/stage0/ReCode.c"
        if (function_parameter != NULL) {
#line 3638 "boostrap/stage0/ReCode.c"
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too few arguments"));
#line 3639 "boostrap/stage0/ReCode.c"
            abort();
        }
#line 3641 "boostrap/stage0/ReCode.c"
        if (parsed_argument != NULL) {
#line 3642 "boostrap/stage0/ReCode.c"
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too many arguments"));
#line 3643 "boostrap/stage0/ReCode.c"
            abort();
        }
    }
#line 3646 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Call_Expression__create(parsed_expression->super.location, function_type->return_type, callee_expression, first_argument);
}

#line 3649 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_cast_expression(struct Checker* self, struct Parsed_Cast_Expression* parsed_expression) {
#line 3650 "boostrap/stage0/ReCode.c"
    struct Checked_Type* type = Checker__resolve_type(self, parsed_expression->type);
#line 3651 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3652 "boostrap/stage0/ReCode.c"
    struct Checked_Type* other_type = other_expression->type;
#line 3653 "boostrap/stage0/ReCode.c"
    bool can_cast = false;
#line 3654 "boostrap/stage0/ReCode.c"
    if (type->kind == CHECKED_TYPE_KIND__POINTER) {
#line 3655 "boostrap/stage0/ReCode.c"
        if (other_type->kind == CHECKED_TYPE_KIND__POINTER) {
#line 3656 "boostrap/stage0/ReCode.c"
            can_cast = true;
        }
    } else if (Checked_Type__is_scalar_type(type)) {
#line 3659 "boostrap/stage0/ReCode.c"
        if (Checked_Type__is_scalar_type(type)) {
#line 3660 "boostrap/stage0/ReCode.c"
            can_cast = true;
        }
    }
#line 3663 "boostrap/stage0/ReCode.c"
    if (Checked_Type__equals(type, other_type)) {
#line 3664 "boostrap/stage0/ReCode.c"
        Source_Location__warning(parsed_expression->super.super.location, String__create_from("Redundant cast"));
    }
#line 3666 "boostrap/stage0/ReCode.c"
    if (!can_cast) {
#line 3667 "boostrap/stage0/ReCode.c"
        struct String* message = String__create_from("Cannot cast \"");
#line 3668 "boostrap/stage0/ReCode.c"
        String__append_checked_type(message, other_expression->type);
#line 3669 "boostrap/stage0/ReCode.c"
        String__append_cstring(message, "\" to \"");
#line 3670 "boostrap/stage0/ReCode.c"
        String__append_checked_type(message, type);
#line 3671 "boostrap/stage0/ReCode.c"
        String__append_cstring(message, "\".");
#line 3672 "boostrap/stage0/ReCode.c"
        Source_Location__error(parsed_expression->super.super.location, message);
#line 3673 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3675 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Cast_Expression__create(parsed_expression->super.super.location, type, other_expression);
}

#line 3678 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_character_expression(struct Checker* self, struct Parsed_Character_Expression* parsed_expression) {
#line 3679 "boostrap/stage0/ReCode.c"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__CHAR);
#line 3680 "boostrap/stage0/ReCode.c"
    char value = parsed_expression->value;
#line 3681 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3684 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_divide_expression(struct Checker* self, struct Parsed_Divide_Expression* parsed_expression) {
#line 3685 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3686 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3687 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3688 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3689 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3692 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_equals_expression(struct Checker* self, struct Parsed_Equals_Expression* parsed_expression) {
#line 3693 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3694 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3695 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3696 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

#line 3699 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_greater_expression(struct Checker* self, struct Parsed_Greater_Expression* parsed_expression) {
#line 3700 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3701 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3702 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3703 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3704 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Greater_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

#line 3707 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_greater_or_equals_expression(struct Checker* self, struct Parsed_Greater_Or_Equals_Expression* parsed_expression) {
#line 3708 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3709 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3710 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3711 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3712 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

#line 3715 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_group_expression(struct Checker* self, struct Parsed_Group_Expression* parsed_expression) {
#line 3716 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->other_expression);
#line 3717 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

#line 3720 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_integer_expression(struct Checker* self, struct Parsed_Integer_Expression* parsed_expression) {
#line 3721 "boostrap/stage0/ReCode.c"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__INT32_T);
#line 3722 "boostrap/stage0/ReCode.c"
    uint64_t value = parsed_expression->value;
#line 3723 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3726 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_less_expression(struct Checker* self, struct Parsed_Less_Expression* parsed_expression) {
#line 3727 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3728 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3729 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3730 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3731 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Less_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

#line 3734 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_less_or_equals_expression(struct Checker* self, struct Parsed_Less_Or_Equals_Expression* parsed_expression) {
#line 3735 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3736 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3737 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3738 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3739 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

#line 3742 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_logic_and_expression(struct Checker* self, struct Parsed_Logic_And_Expression* parsed_expression) {
#line 3743 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3744 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
#line 3745 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3746 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3747 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3750 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_logic_or_expression(struct Checker* self, struct Parsed_Logic_Or_Expression* parsed_expression) {
#line 3751 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3752 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
#line 3753 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3754 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3755 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3758 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_member_access_expression(struct Checker* self, struct Parsed_Member_Access_Expression* parsed_expression) {
#line 3759 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* object_expression = Checker__check_expression(self, parsed_expression->object_expression);
#line 3760 "boostrap/stage0/ReCode.c"
    struct Checked_Type* object_type = object_expression->type;
#line 3761 "boostrap/stage0/ReCode.c"
    if (object_type->kind == CHECKED_TYPE_KIND__POINTER) {
#line 3762 "boostrap/stage0/ReCode.c"
        object_type = ((struct Checked_Pointer_Type*) object_type)->other_type;
    }
#line 3764 "boostrap/stage0/ReCode.c"
    if (object_type->kind != CHECKED_TYPE_KIND__STRUCT) {
#line 3765 "boostrap/stage0/ReCode.c"
        Source_Location__error(object_expression->location, String__create_from("Not a struct type"));
#line 3766 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3768 "boostrap/stage0/ReCode.c"
    struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) object_type;
#line 3769 "boostrap/stage0/ReCode.c"
    struct Checked_Struct_Member* member = Checked_Struct_Type__find_member(struct_type, parsed_expression->member_name->lexeme);
#line 3770 "boostrap/stage0/ReCode.c"
    if (member == NULL) {
#line 3771 "boostrap/stage0/ReCode.c"
        Source_Location__error(object_expression->location, String__create_from("No such struct member"));
#line 3772 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3774 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Member_Access_Expression__create(parsed_expression->super.location, member->type, object_expression, member);
}

#line 3777 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_minus_expression(struct Checker* self, struct Parsed_Minus_Expression* parsed_expression) {
#line 3778 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3779 "boostrap/stage0/ReCode.c"
    struct Checked_Type* other_expression_type = other_expression->type;
#line 3780 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(other_expression_type, other_expression->location);
#line 3781 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

#line 3784 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_modulo_expression(struct Checker* self, struct Parsed_Modulo_Expression* parsed_expression) {
#line 3785 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3786 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3787 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3788 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3789 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3792 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_multiply_expression(struct Checker* self, struct Parsed_Multiply_Expression* parsed_expression) {
#line 3793 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3794 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3795 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3796 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3797 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3800 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_not_expression(struct Checker* self, struct Parsed_Not_Expression* parsed_expression) {
#line 3801 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3802 "boostrap/stage0/ReCode.c"
    struct Checked_Type* other_expression_type = other_expression->type;
#line 3803 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), other_expression_type, other_expression->location);
#line 3804 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

#line 3807 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_not_equals_expression(struct Checker* self, struct Parsed_Not_Equals_Expression* parsed_expression) {
#line 3808 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3809 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3810 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3811 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

#line 3814 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_null_expression(struct Checker* self, struct Parsed_Null_Expression* parsed_expression) {
#line 3815 "boostrap/stage0/ReCode.c"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__NULL);
#line 3816 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

#line 3819 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_sizeof_expression(struct Checker* self, struct Parsed_Sizeof_Expression* parsed_expression) {
#line 3820 "boostrap/stage0/ReCode.c"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__SIZE_T);
#line 3821 "boostrap/stage0/ReCode.c"
    struct Checked_Type* sized_type = Checker__resolve_type(self, parsed_expression->type);
#line 3822 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

#line 3825 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_string_expression(struct Checker* self, struct Parsed_String_Expression* parsed_expression) {
#line 3826 "boostrap/stage0/ReCode.c"
    struct Checked_Type* char_type = (struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__CHAR);
#line 3827 "boostrap/stage0/ReCode.c"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type);
#line 3828 "boostrap/stage0/ReCode.c"
    struct String* value = parsed_expression->value;
#line 3829 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3832 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_substract_expression(struct Checker* self, struct Parsed_Substract_Expression* parsed_expression) {
#line 3833 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3834 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3835 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3836 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3837 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3840 "boostrap/stage0/ReCode.c"
struct Checked_Expression* Checker__check_symbol_expression(struct Checker* self, struct Parsed_Symbol_Expression* parsed_expression) {
#line 3841 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol* symbol = Checked_Symbols__find_symbol(self->symbols, parsed_expression->name->lexeme);
#line 3842 "boostrap/stage0/ReCode.c"
    if (symbol == NULL) {
#line 3843 "boostrap/stage0/ReCode.c"
        Token__error(parsed_expression->name, String__create_from("Undefined symbol"));
#line 3844 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3846 "boostrap/stage0/ReCode.c"
    if (symbol->type == NULL) {
#line 3847 "boostrap/stage0/ReCode.c"
        Token__error(parsed_expression->name, String__create_from("Symbol without type"));
#line 3848 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 3850 "boostrap/stage0/ReCode.c"
    return (struct Checked_Expression*) Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol);
}

#line 3915 "boostrap/stage0/ReCode.c"
void Checker__check_enum_statement(struct Checker* self, struct Parsed_Enum_Statement* parsed_statement) {
#line 3916 "boostrap/stage0/ReCode.c"
    struct Checked_Enum_Type* enum_type = Checked_Enum_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 3917 "boostrap/stage0/ReCode.c"
    Checker__append_type(self, (struct Checked_Named_Type*) enum_type);
#line 3919 "boostrap/stage0/ReCode.c"
    struct Checked_Enum_Member* last_enum_member = NULL;
#line 3920 "boostrap/stage0/ReCode.c"
    struct Parsed_Enum_Member* parsed_enum_member = parsed_statement->first_member;
#line 3921 "boostrap/stage0/ReCode.c"
    while (parsed_enum_member != NULL) {
#line 3922 "boostrap/stage0/ReCode.c"
        struct Checked_Enum_Member* enum_member = Checked_Enum_Type__find_member(enum_type, parsed_enum_member->name->lexeme);
#line 3923 "boostrap/stage0/ReCode.c"
        if (enum_member != NULL) {
#line 3924 "boostrap/stage0/ReCode.c"
            TODO("Handle enum member duplicate");
#line 3925 "boostrap/stage0/ReCode.c"
            abort();
        }
#line 3927 "boostrap/stage0/ReCode.c"
        enum_member = Checked_Enum_Member__create(parsed_enum_member->name->location, parsed_enum_member->name->lexeme);
#line 3928 "boostrap/stage0/ReCode.c"
        if (last_enum_member == NULL) {
#line 3929 "boostrap/stage0/ReCode.c"
            enum_type->first_member = enum_member;
        } else {
#line 3931 "boostrap/stage0/ReCode.c"
            last_enum_member->next_member = enum_member;
        }
#line 3933 "boostrap/stage0/ReCode.c"
        last_enum_member = enum_member;
#line 3934 "boostrap/stage0/ReCode.c"
        Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Enum_Member_Symbol__create(enum_member->location, enum_member->name, (struct Checked_Type*) enum_type));
#line 3935 "boostrap/stage0/ReCode.c"
        parsed_enum_member = parsed_enum_member->next_member;
    }
}

#line 3939 "boostrap/stage0/ReCode.c"
void Checker__check_function_type_statement(struct Checker* self, struct Parsed_Function_Type_Statement* parsed_statement) {
#line 3940 "boostrap/stage0/ReCode.c"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 3941 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Type* function_type;
#line 3942 "boostrap/stage0/ReCode.c"
    if (other_type != NULL) {
#line 3943 "boostrap/stage0/ReCode.c"
        TODO("Handle type redeclaration");
#line 3944 "boostrap/stage0/ReCode.c"
        abort();
    } else {
#line 3946 "boostrap/stage0/ReCode.c"
        struct Checked_Type* return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 3947 "boostrap/stage0/ReCode.c"
        function_type = Checked_Function_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, return_type);
#line 3948 "boostrap/stage0/ReCode.c"
        Checker__append_type(self, (struct Checked_Named_Type*) function_type);
    }
#line 3951 "boostrap/stage0/ReCode.c"
    if (parsed_statement->first_parameter != NULL) {
#line 3952 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Parameter* last_function_parameter = NULL;
#line 3953 "boostrap/stage0/ReCode.c"
        struct Parsed_Function_Type_Parameter* parsed_parameter = parsed_statement->first_parameter;
#line 3954 "boostrap/stage0/ReCode.c"
        while (parsed_parameter != NULL) {
#line 3955 "boostrap/stage0/ReCode.c"
            struct Checked_Type* function_parameter_type = Checker__resolve_type(self, parsed_parameter->type);
#line 3956 "boostrap/stage0/ReCode.c"
            struct Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, function_parameter_type);
#line 3957 "boostrap/stage0/ReCode.c"
            if (last_function_parameter == NULL) {
#line 3958 "boostrap/stage0/ReCode.c"
                function_type->first_parameter = function_parameter;
            } else {
#line 3960 "boostrap/stage0/ReCode.c"
                last_function_parameter->next_parameter = function_parameter;
            }
#line 3962 "boostrap/stage0/ReCode.c"
            last_function_parameter = function_parameter;
#line 3963 "boostrap/stage0/ReCode.c"
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
}

#line 3968 "boostrap/stage0/ReCode.c"
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) {
#line 3969 "boostrap/stage0/ReCode.c"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 3970 "boostrap/stage0/ReCode.c"
    struct Checked_Struct_Type* struct_type;
#line 3971 "boostrap/stage0/ReCode.c"
    if (other_type != NULL) {
#line 3972 "boostrap/stage0/ReCode.c"
        if (other_type->super.kind != CHECKED_TYPE_KIND__STRUCT || (((struct Checked_Struct_Type*) other_type)->first_member != NULL)) {
#line 3973 "boostrap/stage0/ReCode.c"
            TODO("Report type redeclaration");
#line 3974 "boostrap/stage0/ReCode.c"
            abort();
        }
#line 3976 "boostrap/stage0/ReCode.c"
        struct_type = (struct Checked_Struct_Type*) other_type;
    } else {
#line 3978 "boostrap/stage0/ReCode.c"
        struct_type = Checked_Struct_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 3979 "boostrap/stage0/ReCode.c"
        Checker__append_type(self, (struct Checked_Named_Type*) struct_type);
    }
#line 3982 "boostrap/stage0/ReCode.c"
    if (parsed_statement->first_member != NULL) {
#line 3983 "boostrap/stage0/ReCode.c"
        struct Checked_Struct_Member* last_struct_member = NULL;
#line 3984 "boostrap/stage0/ReCode.c"
        struct Parsed_Struct_Member* parsed_member = parsed_statement->first_member;
#line 3985 "boostrap/stage0/ReCode.c"
        while (parsed_member != NULL) {
#line 3986 "boostrap/stage0/ReCode.c"
            struct Checked_Struct_Member* struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
#line 3987 "boostrap/stage0/ReCode.c"
            if (struct_member != NULL) {
#line 3988 "boostrap/stage0/ReCode.c"
                TODO("Handle struct member duplicate");
#line 3989 "boostrap/stage0/ReCode.c"
                abort();
            }
#line 3991 "boostrap/stage0/ReCode.c"
            struct Checked_Type* struct_member_type = Checker__resolve_type(self, parsed_member->type);
#line 3992 "boostrap/stage0/ReCode.c"
            struct_member = Checked_Struct_Member__create(parsed_member->name->location, parsed_member->name->lexeme, struct_member_type);
#line 3993 "boostrap/stage0/ReCode.c"
            if (last_struct_member == NULL) {
#line 3994 "boostrap/stage0/ReCode.c"
                struct_type->first_member = struct_member;
            } else {
#line 3996 "boostrap/stage0/ReCode.c"
                last_struct_member->next_member = struct_member;
            }
#line 3998 "boostrap/stage0/ReCode.c"
            last_struct_member = struct_member;
#line 3999 "boostrap/stage0/ReCode.c"
            parsed_member = parsed_member->next_member;
        }
    }
}

#line 4004 "boostrap/stage0/ReCode.c"
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement) {
#line 4105 "boostrap/stage0/ReCode.c"
    if (parsed_statement->kind == PARSED_STATEMENT_KIND__ASSIGNMENT) {
#line 4106 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_assignment_statement(self, (struct Parsed_Assignment_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__BLOCK) {
#line 4108 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_block_statement(self, (struct Parsed_Block_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__BREAK) {
#line 4110 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_break_statement(self, (struct Parsed_Break_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__EXPRESSION) {
#line 4112 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_expression_statement(self, (struct Parsed_Expression_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__IF) {
#line 4114 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_if_statement(self, (struct Parsed_If_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__RETURN) {
#line 4116 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_return_statement(self, (struct Parsed_Return_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
#line 4118 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_variable_statement(self, (struct Parsed_Variable_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__WHILE) {
#line 4120 "boostrap/stage0/ReCode.c"
        return (struct Checked_Statement*) Checker__check_while_statement(self, (struct Parsed_While_Statement*) parsed_statement);
    }
#line 4122 "boostrap/stage0/ReCode.c"
    Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4123 "boostrap/stage0/ReCode.c"
    abort();
}

#line 4006 "boostrap/stage0/ReCode.c"
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement) {
#line 4007 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* object_expression = Checker__check_expression(self, parsed_statement->object_expression);
#line 4008 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* value_expression = Checker__check_expression(self, parsed_statement->value_expression);
#line 4009 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type(object_expression->type, value_expression->type, value_expression->location);
#line 4010 "boostrap/stage0/ReCode.c"
    return Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);
}

#line 4013 "boostrap/stage0/ReCode.c"
struct Checked_Statements* Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements) {
#line 4128 "boostrap/stage0/ReCode.c"
    self->symbols = Checked_Symbols__create(self->symbols);
#line 4130 "boostrap/stage0/ReCode.c"
    struct Checked_Statements* checked_statements = Checked_Statements__create();
#line 4131 "boostrap/stage0/ReCode.c"
    struct Parsed_Statement* parsed_statement = parsed_statements->first_statement;
#line 4132 "boostrap/stage0/ReCode.c"
    while (parsed_statement != NULL) {
#line 4133 "boostrap/stage0/ReCode.c"
        struct Checked_Statement* checked_statement = Checker__check_statement(self, parsed_statement);
#line 4134 "boostrap/stage0/ReCode.c"
        Checked_Statements__append(checked_statements, checked_statement);
#line 4135 "boostrap/stage0/ReCode.c"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4139 "boostrap/stage0/ReCode.c"
    self->symbols = self->symbols->parent;
#line 4141 "boostrap/stage0/ReCode.c"
    return checked_statements;
}

#line 4015 "boostrap/stage0/ReCode.c"
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement) {
#line 4016 "boostrap/stage0/ReCode.c"
    struct Checked_Statements* statements = Checker__check_statements(self, parsed_statement->statements);
#line 4017 "boostrap/stage0/ReCode.c"
    return Checked_Block_Statement__create(parsed_statement->super.location, statements);
}

#line 4020 "boostrap/stage0/ReCode.c"
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement) {
#line 4021 "boostrap/stage0/ReCode.c"
    return Checked_Break_Statement__create(parsed_statement->super.location);
}

#line 4024 "boostrap/stage0/ReCode.c"
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement) {
#line 4025 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* expression = Checker__check_expression(self, parsed_statement->expression);
#line 4026 "boostrap/stage0/ReCode.c"
    if (!Checked_Type__equals((struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__VOID), expression->type)) {
    }
#line 4029 "boostrap/stage0/ReCode.c"
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

#line 4032 "boostrap/stage0/ReCode.c"
struct Checked_If_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement) {
#line 4033 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4034 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
#line 4035 "boostrap/stage0/ReCode.c"
    struct Checked_Statement* true_statement = Checker__check_statement(self, parsed_statement->true_statement);
#line 4036 "boostrap/stage0/ReCode.c"
    struct Checked_Statement* false_statement = NULL;
#line 4037 "boostrap/stage0/ReCode.c"
    if (parsed_statement->false_statement != NULL) {
#line 4038 "boostrap/stage0/ReCode.c"
        false_statement = Checker__check_statement(self, parsed_statement->false_statement);
    }
#line 4040 "boostrap/stage0/ReCode.c"
    return Checked_If_Statement__create(parsed_statement->super.location, considition_expression, true_statement, false_statement);
}

#line 4043 "boostrap/stage0/ReCode.c"
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement) {
#line 4044 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* expression = NULL;
#line 4045 "boostrap/stage0/ReCode.c"
    if (parsed_statement->expression != NULL) {
#line 4046 "boostrap/stage0/ReCode.c"
        expression = Checker__check_expression(self, parsed_statement->expression);
#line 4047 "boostrap/stage0/ReCode.c"
        Checked_Type__expect_same_type(self->return_type, expression->type, expression->location);
    } else if (self->return_type->kind != CHECKED_TYPE_KIND__VOID) {
#line 4049 "boostrap/stage0/ReCode.c"
        Source_Location__error(parsed_statement->super.location, String__create_from("Missing expression"));
#line 4050 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 4052 "boostrap/stage0/ReCode.c"
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);
}

#line 4055 "boostrap/stage0/ReCode.c"
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement) {
#line 4056 "boostrap/stage0/ReCode.c"
    struct Checked_Type* type = Checker__resolve_type(self, parsed_statement->type);
#line 4057 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* expression = NULL;
#line 4058 "boostrap/stage0/ReCode.c"
    if (parsed_statement->expression != NULL) {
#line 4059 "boostrap/stage0/ReCode.c"
        expression = Checker__check_expression(self, parsed_statement->expression);
#line 4060 "boostrap/stage0/ReCode.c"
        Checked_Type__expect_same_type(type, expression->type, expression->location);
    }
#line 4062 "boostrap/stage0/ReCode.c"
    struct Checked_Variable_Symbol* variable = Checked_Variable__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
#line 4063 "boostrap/stage0/ReCode.c"
    Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) variable);
#line 4064 "boostrap/stage0/ReCode.c"
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);
}

#line 4067 "boostrap/stage0/ReCode.c"
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement) {
#line 4068 "boostrap/stage0/ReCode.c"
    struct Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4069 "boostrap/stage0/ReCode.c"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
#line 4070 "boostrap/stage0/ReCode.c"
    struct Checked_Statement* body_statement = Checker__check_statement(self, parsed_statement->body_statement);
#line 4071 "boostrap/stage0/ReCode.c"
    return Checked_While_Statement__create(parsed_statement->super.location, considition_expression, body_statement);
}

#line 4074 "boostrap/stage0/ReCode.c"
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) {
#line 4075 "boostrap/stage0/ReCode.c"
    struct String* function_name = parsed_statement->super.name->lexeme;
#line 4076 "boostrap/stage0/ReCode.c"
    struct Checked_Type* function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 4077 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Parameter* function_first_parameter = NULL;
#line 4078 "boostrap/stage0/ReCode.c"
    struct Parsed_Function_Parameter* parsed_parameter = parsed_statement->first_parameter;
#line 4079 "boostrap/stage0/ReCode.c"
    if (parsed_parameter != NULL) {
#line 4080 "boostrap/stage0/ReCode.c"
        function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
#line 4081 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Parameter* function_last_parameter = function_first_parameter;
#line 4082 "boostrap/stage0/ReCode.c"
        parsed_parameter = parsed_parameter->next_parameter;
#line 4083 "boostrap/stage0/ReCode.c"
        while (parsed_parameter != NULL) {
#line 4084 "boostrap/stage0/ReCode.c"
            struct Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
#line 4085 "boostrap/stage0/ReCode.c"
            function_last_parameter->next_parameter = function_parameter;
#line 4086 "boostrap/stage0/ReCode.c"
            function_last_parameter = function_parameter;
#line 4087 "boostrap/stage0/ReCode.c"
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
#line 4090 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Type* function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_name, function_return_type);
#line 4091 "boostrap/stage0/ReCode.c"
    function_type->first_parameter = function_first_parameter;
#line 4093 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol* other_symbol = Checked_Symbols__find_sibling_symbol(self->symbols, function_name);
#line 4094 "boostrap/stage0/ReCode.c"
    if (other_symbol != NULL) {
#line 4095 "boostrap/stage0/ReCode.c"
        if (other_symbol->kind != CHECKED_SYMBOL_KIND__FUNCTION || !Checked_Type__equals((struct Checked_Type*) function_type, (struct Checked_Type*) ((struct Checked_Function_Symbol*) other_symbol)->function_type)) {
#line 4096 "boostrap/stage0/ReCode.c"
            TODO("Report function redeclaration");
#line 4097 "boostrap/stage0/ReCode.c"
            abort();
        }
    } else {
#line 4100 "boostrap/stage0/ReCode.c"
        Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Function_Symbol__create(parsed_statement->super.name->location, function_name, function_type));
    }
}

#line 4144 "boostrap/stage0/ReCode.c"
void Checker__check_function_definition(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) {
#line 4145 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol* symbol = Checked_Symbols__find_sibling_symbol(self->symbols, parsed_statement->super.name->lexeme);
#line 4146 "boostrap/stage0/ReCode.c"
    if (symbol == NULL || symbol->kind != CHECKED_SYMBOL_KIND__FUNCTION) {
#line 4147 "boostrap/stage0/ReCode.c"
        TODO("Report missing function symbol");
#line 4148 "boostrap/stage0/ReCode.c"
        abort();
    }
#line 4150 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Symbol* function_symbol = (struct Checked_Function_Symbol*) symbol;
#line 4151 "boostrap/stage0/ReCode.c"
    struct Checked_Function_Type* function_type = function_symbol->function_type;
#line 4152 "boostrap/stage0/ReCode.c"
    self->return_type = function_type->return_type;
#line 4155 "boostrap/stage0/ReCode.c"
    self->symbols = Checked_Symbols__create(self->symbols);
#line 4157 "boostrap/stage0/ReCode.c"
    if (function_type->first_parameter != NULL) {
#line 4159 "boostrap/stage0/ReCode.c"
        struct Checked_Function_Parameter* parameter = function_type->first_parameter;
#line 4160 "boostrap/stage0/ReCode.c"
        while (parameter != NULL) {
#line 4161 "boostrap/stage0/ReCode.c"
            Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Function_Parameter_Symbol__create(parameter->location, parameter->name, parameter->type));
#line 4162 "boostrap/stage0/ReCode.c"
            parameter = parameter->next_parameter;
        }
    }
#line 4167 "boostrap/stage0/ReCode.c"
    function_symbol->checked_statements = Checker__check_statements(self, parsed_statement->statements);
#line 4170 "boostrap/stage0/ReCode.c"
    self->symbols = self->symbols->parent;
}

#line 4173 "boostrap/stage0/ReCode.c"
struct Checked_Source* Checker__check_source(struct Checker* self, struct Parsed_Source* parsed_source) {
#line 4174 "boostrap/stage0/ReCode.c"
    struct Checked_Statements* checked_statements = Checked_Statements__create();
#line 4176 "boostrap/stage0/ReCode.c"
    struct Parsed_Statement* parsed_statement;
#line 4179 "boostrap/stage0/ReCode.c"
    parsed_statement = parsed_source->statements->first_statement;
#line 4180 "boostrap/stage0/ReCode.c"
    while (parsed_statement != NULL) {
#line 4181 "boostrap/stage0/ReCode.c"
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
#line 4182 "boostrap/stage0/ReCode.c"
            Checker__check_struct_statement(self, (struct Parsed_Struct_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
#line 4184 "boostrap/stage0/ReCode.c"
            Checker__check_enum_statement(self, (struct Parsed_Enum_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION_TYPE) {
#line 4186 "boostrap/stage0/ReCode.c"
            Checker__check_function_type_statement(self, (struct Parsed_Function_Type_Statement*) parsed_statement);
        }
#line 4188 "boostrap/stage0/ReCode.c"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4192 "boostrap/stage0/ReCode.c"
    parsed_statement = parsed_source->statements->first_statement;
#line 4193 "boostrap/stage0/ReCode.c"
    while (parsed_statement != NULL) {
#line 4194 "boostrap/stage0/ReCode.c"
        struct Checked_Statement* checked_statement = NULL;
#line 4195 "boostrap/stage0/ReCode.c"
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION) {
#line 4196 "boostrap/stage0/ReCode.c"
            Checker__check_function_declaration(self, (struct Parsed_Function_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
#line 4198 "boostrap/stage0/ReCode.c"
            checked_statement = (struct Checked_Statement*) Checker__check_variable_statement(self, (struct Parsed_Variable_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION_TYPE) {
        } else {
#line 4206 "boostrap/stage0/ReCode.c"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4207 "boostrap/stage0/ReCode.c"
            abort();
        }
#line 4209 "boostrap/stage0/ReCode.c"
        if (checked_statement != NULL) {
#line 4210 "boostrap/stage0/ReCode.c"
            Checked_Statements__append(checked_statements, checked_statement);
        }
#line 4212 "boostrap/stage0/ReCode.c"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4216 "boostrap/stage0/ReCode.c"
    parsed_statement = parsed_source->statements->first_statement;
#line 4217 "boostrap/stage0/ReCode.c"
    while (parsed_statement != NULL) {
#line 4218 "boostrap/stage0/ReCode.c"
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION) {
#line 4219 "boostrap/stage0/ReCode.c"
            struct Parsed_Function_Statement* function_statement = (struct Parsed_Function_Statement*) parsed_statement;
#line 4220 "boostrap/stage0/ReCode.c"
            if (function_statement->statements != NULL) {
#line 4221 "boostrap/stage0/ReCode.c"
                Checker__check_function_definition(self, function_statement);
            }
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION_TYPE) {
        } else {
#line 4232 "boostrap/stage0/ReCode.c"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4233 "boostrap/stage0/ReCode.c"
            abort();
        }
#line 4235 "boostrap/stage0/ReCode.c"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4238 "boostrap/stage0/ReCode.c"
    struct Checked_Source* checked_source = (struct Checked_Source*) malloc(sizeof(struct Checked_Source));
#line 4239 "boostrap/stage0/ReCode.c"
    checked_source->first_symbol = self->symbols->first_symbol;
#line 4240 "boostrap/stage0/ReCode.c"
    checked_source->statements = checked_statements;
#line 4241 "boostrap/stage0/ReCode.c"
    return checked_source;
}

#line 4244 "boostrap/stage0/ReCode.c"
struct Checked_Source* check(struct Parsed_Source* parsed_source) {
#line 4245 "boostrap/stage0/ReCode.c"
    struct Checker* type_checker = Checker__create();
#line 4247 "boostrap/stage0/ReCode.c"
    return Checker__check_source(type_checker, parsed_source);
}

#line 4258 "boostrap/stage0/ReCode.c"
void Generator__write_source_location(struct Generator* self, struct Source_Location* location) {
#line 4259 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "#line ");
#line 4260 "boostrap/stage0/ReCode.c"
    File__write_int32_t(self->file, (int32_t) location->line);
#line 4261 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " \"");
#line 4262 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, location->source->path);
#line 4263 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "\"\n");
}

#line 4266 "boostrap/stage0/ReCode.c"
void Generator__generate_expression(struct Generator* self, struct Checked_Expression* expression) {
#line 4483 "boostrap/stage0/ReCode.c"
    if (expression->kind == CHECKED_EXPRESSION_KIND__ADD) {
#line 4484 "boostrap/stage0/ReCode.c"
        Generator__generate_add_expression(self, (struct Checked_Add_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__ADDRESS_OF) {
#line 4486 "boostrap/stage0/ReCode.c"
        Generator__generate_address_of_expression(self, (struct Checked_Address_Of_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__ARRAY_ACCESS) {
#line 4488 "boostrap/stage0/ReCode.c"
        Generator__generate_array_access_expression(self, (struct Checked_Array_Access_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__BOOL) {
#line 4490 "boostrap/stage0/ReCode.c"
        Generator__generate_bool_expression(self, (struct Checked_Bool_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CALL) {
#line 4492 "boostrap/stage0/ReCode.c"
        Generator__generate_call_expression(self, (struct Checked_Call_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CAST) {
#line 4494 "boostrap/stage0/ReCode.c"
        Generator__generate_cast_expression(self, (struct Checked_Cast_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CHARACTER) {
#line 4496 "boostrap/stage0/ReCode.c"
        Generator__generate_character_expression(self, (struct Checked_Character_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__DIVIDE) {
#line 4498 "boostrap/stage0/ReCode.c"
        Generator__generate_divide_expression(self, (struct Checked_Divide_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__EQUALS) {
#line 4500 "boostrap/stage0/ReCode.c"
        Generator__generate_equals_expression(self, (struct Checked_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GREATER) {
#line 4502 "boostrap/stage0/ReCode.c"
        Generator__generate_greater_expression(self, (struct Checked_Greater_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS) {
#line 4504 "boostrap/stage0/ReCode.c"
        Generator__generate_greater_or_equals_expression(self, (struct Checked_Greater_Or_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GROUP) {
#line 4506 "boostrap/stage0/ReCode.c"
        Generator__generate_group_expression(self, (struct Checked_Group_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__INTEGER) {
#line 4508 "boostrap/stage0/ReCode.c"
        Generator__generate_integer_expression(self, (struct Checked_Integer_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LESS) {
#line 4510 "boostrap/stage0/ReCode.c"
        Generator__generate_less_expression(self, (struct Checked_Less_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS) {
#line 4512 "boostrap/stage0/ReCode.c"
        Generator__generate_less_or_equals_expression(self, (struct Checked_Less_Or_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LOGIC_AND) {
#line 4514 "boostrap/stage0/ReCode.c"
        Generator__generate_logic_and_expression(self, (struct Checked_Logic_And_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LOGIC_OR) {
#line 4516 "boostrap/stage0/ReCode.c"
        Generator__generate_logic_or_expression(self, (struct Checked_Logic_Or_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MEMBER_ACCESS) {
#line 4518 "boostrap/stage0/ReCode.c"
        Generator__generate_member_access_expression(self, (struct Checked_Member_Access_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MINUS) {
#line 4520 "boostrap/stage0/ReCode.c"
        Generator__generate_minus_expression(self, (struct Checked_Minus_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MODULO) {
#line 4522 "boostrap/stage0/ReCode.c"
        Generator__generate_modulo_expression(self, (struct Checked_Modulo_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MULTIPLY) {
#line 4524 "boostrap/stage0/ReCode.c"
        Generator__generate_multiply_expression(self, (struct Checked_Multiply_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NOT) {
#line 4526 "boostrap/stage0/ReCode.c"
        Generator__generate_not_expression(self, (struct Checked_Not_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NOT_EQUALS) {
#line 4528 "boostrap/stage0/ReCode.c"
        Generator__generate_not_equals_expression(self, (struct Checked_Not_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NULL) {
#line 4530 "boostrap/stage0/ReCode.c"
        Generator__generate_null_expression(self, (struct Checked_Null_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SIZEOF) {
#line 4532 "boostrap/stage0/ReCode.c"
        Generator__generate_sizeof_expression(self, (struct Checked_Sizeof_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__STRING) {
#line 4534 "boostrap/stage0/ReCode.c"
        Generator__generate_string_expression(self, (struct Checked_String_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SUBSTRACT) {
#line 4536 "boostrap/stage0/ReCode.c"
        Generator__generate_substract_expression(self, (struct Checked_Substract_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
#line 4538 "boostrap/stage0/ReCode.c"
        Generator__generate_symbol_expression(self, (struct Checked_Symbol_Expression*) expression);
    } else {
#line 4540 "boostrap/stage0/ReCode.c"
        Source_Location__error(expression->location, String__create_from("Unsupported expression"));
#line 4541 "boostrap/stage0/ReCode.c"
        abort();
    }
}

#line 4268 "boostrap/stage0/ReCode.c"
void Generator__generate_add_expression(struct Generator* self, struct Checked_Add_Expression* expression) {
#line 4269 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4270 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " + ");
#line 4271 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4274 "boostrap/stage0/ReCode.c"
void Generator__generate_address_of_expression(struct Generator* self, struct Checked_Address_Of_Expression* expression) {
#line 4275 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "&");
#line 4276 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4279 "boostrap/stage0/ReCode.c"
void Generator__generate_array_access_expression(struct Generator* self, struct Checked_Array_Access_Expression* expression) {
#line 4280 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->array_expression);
#line 4281 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "[");
#line 4282 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->index_expression);
#line 4283 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "]");
}

#line 4286 "boostrap/stage0/ReCode.c"
void Generator__generate_bool_expression(struct Generator* self, struct Checked_Bool_Expression* expression) {
#line 4287 "boostrap/stage0/ReCode.c"
    if (expression->value) {
#line 4288 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, "true");
    } else {
#line 4290 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, "false");
    }
}

#line 4294 "boostrap/stage0/ReCode.c"
void Generator__generate_call_expression(struct Generator* self, struct Checked_Call_Expression* expression) {
#line 4295 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->callee_expression);
#line 4296 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "(");
#line 4297 "boostrap/stage0/ReCode.c"
    struct Checked_Call_Argument* argument = expression->first_argument;
#line 4298 "boostrap/stage0/ReCode.c"
    while (argument != NULL) {
#line 4299 "boostrap/stage0/ReCode.c"
        Generator__generate_expression(self, argument->expression);
#line 4300 "boostrap/stage0/ReCode.c"
        argument = argument->next_argument;
#line 4301 "boostrap/stage0/ReCode.c"
        if (argument != NULL) {
#line 4302 "boostrap/stage0/ReCode.c"
            File__write_cstring(self->file, ", ");
        }
    }
#line 4305 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ")");
}

#line 4308 "boostrap/stage0/ReCode.c"
void Generator__generate_cast_expression(struct Generator* self, struct Checked_Cast_Expression* expression) {
#line 4309 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "(");
#line 4310 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, expression->super.type);
#line 4311 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ") ");
#line 4312 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->other_expression);
}

#line 4315 "boostrap/stage0/ReCode.c"
void File__write_octal_escaped_char(struct File* stream, char value) {
#line 4316 "boostrap/stage0/ReCode.c"
    File__write_char(stream, '\\');
#line 4317 "boostrap/stage0/ReCode.c"
    if (value > (char) 64) {
#line 4318 "boostrap/stage0/ReCode.c"
        File__write_char(stream, value / (char) 64 % (char) 8 + '0');
    }
#line 4320 "boostrap/stage0/ReCode.c"
    if (value > (char) 8) {
#line 4321 "boostrap/stage0/ReCode.c"
        File__write_char(stream, value / (char) 8 % (char) 8 + '0');
    }
#line 4323 "boostrap/stage0/ReCode.c"
    File__write_char(stream, value % (char) 8 + '0');
}

#line 4326 "boostrap/stage0/ReCode.c"
void File__write_escaped_char(struct File* stream, char ch) {
#line 4327 "boostrap/stage0/ReCode.c"
    if (ch < (char) 32) {
#line 4328 "boostrap/stage0/ReCode.c"
        if (ch == '\n') {
#line 4329 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\\n");
        } else if (ch == '\t') {
#line 4331 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\\t");
        } else {
#line 4333 "boostrap/stage0/ReCode.c"
            File__write_octal_escaped_char(stream, ch);
        }
    } else if (ch < (char) 127) {
#line 4336 "boostrap/stage0/ReCode.c"
        if (ch == '\"') {
#line 4337 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\\\"");
        } else if (ch == '\'') {
#line 4339 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\\\'");
        } else if (ch == '\\') {
#line 4341 "boostrap/stage0/ReCode.c"
            File__write_cstring(stream, "\\\\");
        } else {
#line 4343 "boostrap/stage0/ReCode.c"
            File__write_char(stream, ch);
        }
    } else {
#line 4346 "boostrap/stage0/ReCode.c"
        File__write_octal_escaped_char(stream, ch);
    }
}

#line 4350 "boostrap/stage0/ReCode.c"
void Generator__generate_character_expression(struct Generator* self, struct Checked_Character_Expression* expression) {
#line 4351 "boostrap/stage0/ReCode.c"
    File__write_char(self->file, '\'');
#line 4352 "boostrap/stage0/ReCode.c"
    File__write_escaped_char(self->file, expression->value);
#line 4353 "boostrap/stage0/ReCode.c"
    File__write_char(self->file, '\'');
}

#line 4356 "boostrap/stage0/ReCode.c"
void Generator__generate_divide_expression(struct Generator* self, struct Checked_Divide_Expression* expression) {
#line 4357 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4358 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " / ");
#line 4359 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4362 "boostrap/stage0/ReCode.c"
void Generator__generate_equals_expression(struct Generator* self, struct Checked_Equals_Expression* expression) {
#line 4363 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4364 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " == ");
#line 4365 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4368 "boostrap/stage0/ReCode.c"
void Generator__generate_greater_expression(struct Generator* self, struct Checked_Greater_Expression* expression) {
#line 4369 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4370 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " > ");
#line 4371 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4374 "boostrap/stage0/ReCode.c"
void Generator__generate_greater_or_equals_expression(struct Generator* self, struct Checked_Greater_Or_Equals_Expression* expression) {
#line 4375 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4376 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " >= ");
#line 4377 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4380 "boostrap/stage0/ReCode.c"
void Generator__generate_group_expression(struct Generator* self, struct Checked_Group_Expression* expression) {
#line 4381 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "(");
#line 4382 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->other_expression);
#line 4383 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ")");
}

#line 4386 "boostrap/stage0/ReCode.c"
void Generator__generate_integer_expression(struct Generator* self, struct Checked_Integer_Expression* expression) {
#line 4387 "boostrap/stage0/ReCode.c"
    File__write_uint64_t(self->file, expression->value);
}

#line 4390 "boostrap/stage0/ReCode.c"
void Generator__generate_less_expression(struct Generator* self, struct Checked_Less_Expression* expression) {
#line 4391 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4392 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " < ");
#line 4393 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4396 "boostrap/stage0/ReCode.c"
void Generator__generate_less_or_equals_expression(struct Generator* self, struct Checked_Less_Or_Equals_Expression* expression) {
#line 4397 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4398 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " <= ");
#line 4399 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4402 "boostrap/stage0/ReCode.c"
void Generator__generate_logic_and_expression(struct Generator* self, struct Checked_Logic_And_Expression* expression) {
#line 4403 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4404 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " && ");
#line 4405 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4408 "boostrap/stage0/ReCode.c"
void Generator__generate_logic_or_expression(struct Generator* self, struct Checked_Logic_Or_Expression* expression) {
#line 4409 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4410 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " || ");
#line 4411 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4414 "boostrap/stage0/ReCode.c"
void Generator__generate_member_access_expression(struct Generator* self, struct Checked_Member_Access_Expression* expression) {
#line 4415 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->object_expression);
#line 4416 "boostrap/stage0/ReCode.c"
    if (expression->object_expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
#line 4417 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, "->");
    } else {
#line 4419 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, ".");
    }
#line 4421 "boostrap/stage0/ReCode.c"
    File__write_string(self->file, expression->member->name);
}

#line 4424 "boostrap/stage0/ReCode.c"
void Generator__generate_minus_expression(struct Generator* self, struct Checked_Minus_Expression* expression) {
#line 4425 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "-");
#line 4426 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4429 "boostrap/stage0/ReCode.c"
void Generator__generate_modulo_expression(struct Generator* self, struct Checked_Modulo_Expression* expression) {
#line 4430 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4431 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " % ");
#line 4432 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4435 "boostrap/stage0/ReCode.c"
void Generator__generate_multiply_expression(struct Generator* self, struct Checked_Multiply_Expression* expression) {
#line 4436 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4437 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " * ");
#line 4438 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4441 "boostrap/stage0/ReCode.c"
void Generator__generate_not_expression(struct Generator* self, struct Checked_Not_Expression* expression) {
#line 4442 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "!");
#line 4443 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4446 "boostrap/stage0/ReCode.c"
void Generator__generate_not_equals_expression(struct Generator* self, struct Checked_Not_Equals_Expression* expression) {
#line 4447 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4448 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " != ");
#line 4449 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4452 "boostrap/stage0/ReCode.c"
void Generator__generate_null_expression(struct Generator* self, struct Checked_Null_Expression* expression) {
#line 4453 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "NULL");
}

#line 4456 "boostrap/stage0/ReCode.c"
void Generator__generate_sizeof_expression(struct Generator* self, struct Checked_Sizeof_Expression* expression) {
#line 4457 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "sizeof(");
#line 4458 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, expression->sized_type);
#line 4459 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ")");
}

#line 4462 "boostrap/stage0/ReCode.c"
void Generator__generate_string_expression(struct Generator* self, struct Checked_String_Expression* expression) {
#line 4463 "boostrap/stage0/ReCode.c"
    File__write_char(self->file, '\"');
#line 4464 "boostrap/stage0/ReCode.c"
    size_t index = (size_t) 0;
#line 4465 "boostrap/stage0/ReCode.c"
    while (index < expression->value->length) {
#line 4466 "boostrap/stage0/ReCode.c"
        File__write_escaped_char(self->file, expression->value->data[index]);
#line 4467 "boostrap/stage0/ReCode.c"
        index = index + (size_t) 1;
    }
#line 4469 "boostrap/stage0/ReCode.c"
    File__write_char(self->file, '\"');
}

#line 4472 "boostrap/stage0/ReCode.c"
void Generator__generate_substract_expression(struct Generator* self, struct Checked_Substract_Expression* expression) {
#line 4473 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4474 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " - ");
#line 4475 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4478 "boostrap/stage0/ReCode.c"
void Generator__generate_symbol_expression(struct Generator* self, struct Checked_Symbol_Expression* expression) {
#line 4479 "boostrap/stage0/ReCode.c"
    File__write_string(self->file, expression->symbol->name);
}

#line 4545 "boostrap/stage0/ReCode.c"
void Generator__write_identation(struct Generator* self) {
#line 4546 "boostrap/stage0/ReCode.c"
    uint16_t identation = self->identation;
#line 4547 "boostrap/stage0/ReCode.c"
    while (identation > (uint16_t) 0) {
#line 4548 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, "    ");
#line 4549 "boostrap/stage0/ReCode.c"
        identation = identation - (uint16_t) 1;
    }
}

#line 4553 "boostrap/stage0/ReCode.c"
void Generator__generate_statement(struct Generator* self, struct Checked_Statement* statement) {
#line 4621 "boostrap/stage0/ReCode.c"
    if (statement->kind == CHECKED_STATEMENT_KIND__ASSIGNMENT) {
#line 4622 "boostrap/stage0/ReCode.c"
        Generator__generate_assignment_statement(self, (struct Checked_Assignment_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__BLOCK) {
#line 4624 "boostrap/stage0/ReCode.c"
        Generator__generate_block_statement(self, (struct Checked_Block_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__BREAK) {
#line 4626 "boostrap/stage0/ReCode.c"
        Generator__generate_break_statement(self, (struct Checked_Break_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__EXPRESSION) {
#line 4628 "boostrap/stage0/ReCode.c"
        Generator__generate_expression_statement(self, (struct Checked_Expression_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__IF) {
#line 4630 "boostrap/stage0/ReCode.c"
        Generator__generate_if_statement(self, (struct Checked_If_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__RETURN) {
#line 4632 "boostrap/stage0/ReCode.c"
        Generator__generate_return_statement(self, (struct Checked_Return_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__VARIABLE) {
#line 4634 "boostrap/stage0/ReCode.c"
        Generator__generate_variable_statement(self, (struct Checked_Variable_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__WHILE) {
#line 4636 "boostrap/stage0/ReCode.c"
        Generator__generate_while_statement(self, (struct Checked_While_Statement*) statement);
    } else {
#line 4638 "boostrap/stage0/ReCode.c"
        Source_Location__error(statement->location, String__create_from("Unsupported statement"));
#line 4639 "boostrap/stage0/ReCode.c"
        abort();
    }
}

#line 4554 "boostrap/stage0/ReCode.c"
void Generator__generate_statements(struct Generator* self, struct Checked_Statements* statements) {
#line 4644 "boostrap/stage0/ReCode.c"
    self->identation = self->identation + (uint16_t) 1;
#line 4646 "boostrap/stage0/ReCode.c"
    struct Checked_Statement* statement = statements->first_statement;
#line 4647 "boostrap/stage0/ReCode.c"
    while (statement != NULL) {
#line 4648 "boostrap/stage0/ReCode.c"
        Generator__write_source_location(self, statement->location);
#line 4650 "boostrap/stage0/ReCode.c"
        Generator__write_identation(self);
#line 4652 "boostrap/stage0/ReCode.c"
        Generator__generate_statement(self, statement);
#line 4654 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, "\n");
#line 4656 "boostrap/stage0/ReCode.c"
        statement = statement->next_statement;
    }
#line 4659 "boostrap/stage0/ReCode.c"
    self->identation = self->identation - (uint16_t) 1;
}

#line 4556 "boostrap/stage0/ReCode.c"
void Generator__generate_assignment_statement(struct Generator* self, struct Checked_Assignment_Statement* statement) {
#line 4557 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, statement->object_expression);
#line 4558 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " = ");
#line 4559 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, statement->value_expression);
#line 4560 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ";");
}

#line 4563 "boostrap/stage0/ReCode.c"
void Generator__generate_block_statement(struct Generator* self, struct Checked_Block_Statement* statement) {
#line 4564 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "{\n");
#line 4565 "boostrap/stage0/ReCode.c"
    Generator__generate_statements(self, statement->statements);
#line 4566 "boostrap/stage0/ReCode.c"
    Generator__write_identation(self);
#line 4567 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "}");
}

#line 4570 "boostrap/stage0/ReCode.c"
void Generator__generate_break_statement(struct Generator* self, struct Checked_Break_Statement* statement) {
#line 4571 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "break;");
}

#line 4574 "boostrap/stage0/ReCode.c"
void Generator__generate_expression_statement(struct Generator* self, struct Checked_Expression_Statement* statement) {
#line 4575 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, statement->expression);
#line 4576 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ";");
}

#line 4579 "boostrap/stage0/ReCode.c"
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement) {
#line 4580 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "if (");
#line 4581 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, statement->condition_expression);
#line 4582 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ") ");
#line 4583 "boostrap/stage0/ReCode.c"
    Generator__generate_statement(self, statement->true_statement);
#line 4584 "boostrap/stage0/ReCode.c"
    if (statement->false_statement != NULL) {
#line 4585 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, " else ");
#line 4586 "boostrap/stage0/ReCode.c"
        Generator__generate_statement(self, statement->false_statement);
    }
}

#line 4590 "boostrap/stage0/ReCode.c"
void Generator__generate_return_statement(struct Generator* self, struct Checked_Return_Statement* statement) {
#line 4591 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "return");
#line 4592 "boostrap/stage0/ReCode.c"
    if (statement->expression != NULL) {
#line 4593 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, " ");
#line 4594 "boostrap/stage0/ReCode.c"
        Generator__generate_expression(self, statement->expression);
    }
#line 4596 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ";");
}

#line 4599 "boostrap/stage0/ReCode.c"
void Generator__generate_variable_statement(struct Generator* self, struct Checked_Variable_Statement* statement) {
#line 4600 "boostrap/stage0/ReCode.c"
    if (statement->is_external) {
#line 4601 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, "extern ");
    }
#line 4603 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, statement->variable->super.type);
#line 4604 "boostrap/stage0/ReCode.c"
    File__write_char(self->file, ' ');
#line 4605 "boostrap/stage0/ReCode.c"
    File__write_string(self->file, statement->variable->super.name);
#line 4606 "boostrap/stage0/ReCode.c"
    if (statement->expression != NULL) {
#line 4607 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, " = ");
#line 4608 "boostrap/stage0/ReCode.c"
        Generator__generate_expression(self, statement->expression);
    }
#line 4610 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ";");
}

#line 4613 "boostrap/stage0/ReCode.c"
void Generator__generate_while_statement(struct Generator* self, struct Checked_While_Statement* statement) {
#line 4614 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "while (");
#line 4615 "boostrap/stage0/ReCode.c"
    Generator__generate_expression(self, statement->condition_expression);
#line 4616 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ") ");
#line 4617 "boostrap/stage0/ReCode.c"
    Generator__generate_statement(self, statement->body_statement);
}

#line 4662 "boostrap/stage0/ReCode.c"
void Generator__generate_enum(struct Generator* self, struct Checked_Enum_Type* enum_type) {
#line 4663 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, (struct Checked_Type*) enum_type);
#line 4664 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " {\n");
#line 4665 "boostrap/stage0/ReCode.c"
    struct Checked_Enum_Member* enum_member = enum_type->first_member;
#line 4666 "boostrap/stage0/ReCode.c"
    while (enum_member != NULL) {
#line 4667 "boostrap/stage0/ReCode.c"
        File__write_char(self->file, '\t');
#line 4668 "boostrap/stage0/ReCode.c"
        File__write_string(self->file, enum_member->name);
#line 4669 "boostrap/stage0/ReCode.c"
        enum_member = enum_member->next_member;
#line 4670 "boostrap/stage0/ReCode.c"
        if (enum_member != NULL) {
#line 4671 "boostrap/stage0/ReCode.c"
            File__write_cstring(self->file, ",\n");
        } else {
#line 4673 "boostrap/stage0/ReCode.c"
            File__write_char(self->file, '\n');
        }
    }
#line 4676 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "};\n");
}

#line 4679 "boostrap/stage0/ReCode.c"
void Generator__declare_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4680 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, (struct Checked_Type*) function_symbol->function_type);
#line 4681 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ";\n");
}

#line 4684 "boostrap/stage0/ReCode.c"
void Generator__generate_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4685 "boostrap/stage0/ReCode.c"
    if (function_symbol->checked_statements == NULL) {
#line 4686 "boostrap/stage0/ReCode.c"
        return;
    }
#line 4688 "boostrap/stage0/ReCode.c"
    Generator__write_source_location(self, function_symbol->super.location);
#line 4689 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, (struct Checked_Type*) function_symbol->function_type);
#line 4690 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " {\n");
#line 4691 "boostrap/stage0/ReCode.c"
    Generator__generate_statements(self, function_symbol->checked_statements);
#line 4692 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "}\n\n");
}

#line 4695 "boostrap/stage0/ReCode.c"
void Generator__declare_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4696 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, (struct Checked_Type*) struct_type);
#line 4697 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, ";\n");
}

#line 4700 "boostrap/stage0/ReCode.c"
void Generator__generate_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4701 "boostrap/stage0/ReCode.c"
    struct Checked_Struct_Member* struct_member = struct_type->first_member;
#line 4702 "boostrap/stage0/ReCode.c"
    if (struct_member == NULL) {
#line 4703 "boostrap/stage0/ReCode.c"
        return;
    }
#line 4705 "boostrap/stage0/ReCode.c"
    File__write_checked_type(self->file, (struct Checked_Type*) struct_type);
#line 4706 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, " {\n");
#line 4707 "boostrap/stage0/ReCode.c"
    while (struct_member != NULL) {
#line 4708 "boostrap/stage0/ReCode.c"
        File__write_char(self->file, '\t');
#line 4709 "boostrap/stage0/ReCode.c"
        File__write_checked_type(self->file, struct_member->type);
#line 4710 "boostrap/stage0/ReCode.c"
        File__write_char(self->file, ' ');
#line 4711 "boostrap/stage0/ReCode.c"
        File__write_string(self->file, struct_member->name);
#line 4712 "boostrap/stage0/ReCode.c"
        File__write_cstring(self->file, ";\n");
#line 4713 "boostrap/stage0/ReCode.c"
        struct_member = struct_member->next_member;
    }
#line 4715 "boostrap/stage0/ReCode.c"
    File__write_cstring(self->file, "};\n\n");
}

#line 4718 "boostrap/stage0/ReCode.c"
void generate(struct File* file, struct Checked_Source* checked_source) {
#line 4719 "boostrap/stage0/ReCode.c"
    struct Generator generator;
#line 4720 "boostrap/stage0/ReCode.c"
    generator.file = file;
#line 4721 "boostrap/stage0/ReCode.c"
    generator.identation = (uint16_t) 0;
#line 4723 "boostrap/stage0/ReCode.c"
    struct Checked_Symbol* checked_symbol;
#line 4725 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "/* Copyright (C) 2023 Stefan Selariu */\n");
#line 4726 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "\n");
#line 4727 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "#include <inttypes.h>\n");
#line 4728 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "#include <stdbool.h>\n");
#line 4729 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "#include <stddef.h>\n");
#line 4730 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "\n");
#line 4733 "boostrap/stage0/ReCode.c"
    checked_symbol = checked_source->first_symbol;
#line 4734 "boostrap/stage0/ReCode.c"
    while (checked_symbol != NULL) {
#line 4735 "boostrap/stage0/ReCode.c"
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
#line 4736 "boostrap/stage0/ReCode.c"
            struct Checked_Named_Type* named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 4737 "boostrap/stage0/ReCode.c"
            if (named_type->super.kind == CHECKED_TYPE_KIND__STRUCT) {
#line 4738 "boostrap/stage0/ReCode.c"
                Generator__declare_struct(&generator, (struct Checked_Struct_Type*) named_type);
            } else if (named_type->super.kind == CHECKED_TYPE_KIND__ENUM) {
#line 4740 "boostrap/stage0/ReCode.c"
                Generator__generate_enum(&generator, (struct Checked_Enum_Type*) named_type);
            }
        }
#line 4743 "boostrap/stage0/ReCode.c"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4745 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "\n");
#line 4748 "boostrap/stage0/ReCode.c"
    checked_symbol = checked_source->first_symbol;
#line 4749 "boostrap/stage0/ReCode.c"
    while (checked_symbol != NULL) {
#line 4750 "boostrap/stage0/ReCode.c"
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
#line 4751 "boostrap/stage0/ReCode.c"
            struct Checked_Named_Type* named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 4752 "boostrap/stage0/ReCode.c"
            if (named_type->super.kind == CHECKED_TYPE_KIND__STRUCT) {
#line 4753 "boostrap/stage0/ReCode.c"
                Generator__generate_struct(&generator, (struct Checked_Struct_Type*) named_type);
            }
        }
#line 4756 "boostrap/stage0/ReCode.c"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4760 "boostrap/stage0/ReCode.c"
    struct Checked_Statement* checked_statement = checked_source->statements->first_statement;
#line 4761 "boostrap/stage0/ReCode.c"
    while (checked_statement != NULL) {
#line 4762 "boostrap/stage0/ReCode.c"
        if (checked_statement->kind == CHECKED_STATEMENT_KIND__VARIABLE) {
#line 4763 "boostrap/stage0/ReCode.c"
            Generator__generate_variable_statement(&generator, (struct Checked_Variable_Statement*) checked_statement);
#line 4764 "boostrap/stage0/ReCode.c"
            File__write_cstring(generator.file, "\n");
        } else {
#line 4766 "boostrap/stage0/ReCode.c"
            Source_Location__error(checked_statement->location, String__create_from("Unsupported statement"));
#line 4767 "boostrap/stage0/ReCode.c"
            abort();
        }
#line 4769 "boostrap/stage0/ReCode.c"
        checked_statement = checked_statement->next_statement;
    }
#line 4771 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "\n");
#line 4774 "boostrap/stage0/ReCode.c"
    checked_symbol = checked_source->first_symbol;
#line 4775 "boostrap/stage0/ReCode.c"
    while (checked_symbol != NULL) {
#line 4776 "boostrap/stage0/ReCode.c"
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION) {
#line 4777 "boostrap/stage0/ReCode.c"
            Generator__declare_function(&generator, (struct Checked_Function_Symbol*) checked_symbol);
        }
#line 4779 "boostrap/stage0/ReCode.c"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4781 "boostrap/stage0/ReCode.c"
    File__write_cstring(generator.file, "\n");
#line 4784 "boostrap/stage0/ReCode.c"
    checked_symbol = checked_source->first_symbol;
#line 4785 "boostrap/stage0/ReCode.c"
    while (checked_symbol != NULL) {
#line 4786 "boostrap/stage0/ReCode.c"
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION) {
#line 4787 "boostrap/stage0/ReCode.c"
            Generator__generate_function(&generator, (struct Checked_Function_Symbol*) checked_symbol);
        }
#line 4789 "boostrap/stage0/ReCode.c"
        checked_symbol = checked_symbol->next_symbol;
    }
}

#line 4795 "boostrap/stage0/ReCode.c"
int32_t main(int32_t argc, char** argv) {
#line 4796 "boostrap/stage0/ReCode.c"
    if (argc < 3) {
#line 4797 "boostrap/stage0/ReCode.c"
        error(String__append_cstring(String__append_cstring(String__create_from("Usage: "), argv[(size_t) 0]), " SOURCE OUTPUT"));
#line 4798 "boostrap/stage0/ReCode.c"
        return 1;
    }
#line 4801 "boostrap/stage0/ReCode.c"
    char* source_file_path = argv[(size_t) 1];
#line 4802 "boostrap/stage0/ReCode.c"
    struct File* source_file = fopen(source_file_path, "r");
#line 4803 "boostrap/stage0/ReCode.c"
    if (source_file == NULL) {
#line 4804 "boostrap/stage0/ReCode.c"
        error(String__append_cstring(String__create_from("Cannot open file: "), source_file_path));
#line 4805 "boostrap/stage0/ReCode.c"
        return 1;
    }
#line 4808 "boostrap/stage0/ReCode.c"
    char* output_file_path = argv[(size_t) 2];
#line 4809 "boostrap/stage0/ReCode.c"
    struct File* output_file;
#line 4810 "boostrap/stage0/ReCode.c"
    if (String__equals_cstring(String__create_from(output_file_path), "-")) {
#line 4811 "boostrap/stage0/ReCode.c"
        output_file = stdout;
    } else {
#line 4813 "boostrap/stage0/ReCode.c"
        output_file = fopen(output_file_path, "w");
#line 4814 "boostrap/stage0/ReCode.c"
        if (output_file == NULL) {
#line 4815 "boostrap/stage0/ReCode.c"
            error(String__append_cstring(String__create_from("Cannot open file: "), output_file_path));
#line 4816 "boostrap/stage0/ReCode.c"
            return 1;
        }
    }
#line 4820 "boostrap/stage0/ReCode.c"
    struct Source* source = Source__create(source_file, source_file_path);
#line 4821 "boostrap/stage0/ReCode.c"
    struct Parsed_Source* parsed_source = parse(source);
#line 4822 "boostrap/stage0/ReCode.c"
    struct Checked_Source* checked_source = check(parsed_source);
#line 4823 "boostrap/stage0/ReCode.c"
    generate(output_file, checked_source);
#line 4825 "boostrap/stage0/ReCode.c"
    fclose(source_file);
#line 4826 "boostrap/stage0/ReCode.c"
    return fclose(output_file);
}

