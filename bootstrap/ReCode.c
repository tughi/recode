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
	Parsed_Type_Kind__NAMED,
	Parsed_Type_Kind__POINTER,
	Parsed_Type_Kind__STRUCT
};
struct Parsed_Type;
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
	Parsed_Statement_Kind__FUNCTION_TYPE,
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
struct Parsed_Function_Parameter;
struct Parsed_Function_Statement;
struct Parsed_Function_Type_Parameter;
struct Parsed_Function_Type_Statement;
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
	Checked_Type_Kind__FUNCTION,
	Checked_Type_Kind__OPAQUE,
	Checked_Type_Kind__STRUCT,
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
	Checked_Statement_Kind__IF,
	Checked_Statement_Kind__RETURN,
	Checked_Statement_Kind__VARIABLE,
	Checked_Statement_Kind__WHILE
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
struct Checked_Statements;
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

struct Parsed_Source {
	struct Parsed_Statements* statements;
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
	struct Checked_Named_Type super;
	struct Checked_Type* return_type;
	struct Checked_Function_Parameter* first_parameter;
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

struct Checked_Statements {
	struct Checked_Statement* first_statement;
	struct Checked_Statement* last_statement;
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
struct String* String__append_i16(struct String* self, int16_t value);
struct String* String__append_string(struct String* self, struct String* other);
bool String__equals_cstring(struct String* self, char* s);
bool String__equals_string(struct String* self, struct String* other);
void pass();
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
bool Token__is_define(struct Token* self);
bool Token__is_else(struct Token* self);
bool Token__is_enum(struct Token* self);
bool Token__is_extern(struct Token* self);
bool Token__is_external(struct Token* self);
bool Token__is_false(struct Token* self);
bool Token__is_func(struct Token* self);
bool Token__is_if(struct Token* self);
bool Token__is_null(struct Token* self);
bool Token__is_opaque(struct Token* self);
bool Token__is_return(struct Token* self);
bool Token__is_sizeof(struct Token* self);
bool Token__is_struct(struct Token* self);
bool Token__is_true(struct Token* self);
bool Token__is_type(struct Token* self);
bool Token__is_typedef(struct Token* self);
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
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self), bool second_required, bool (*third_is)(struct Token* self));
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self));
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token* self));
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token* self));
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
struct Parsed_Statement* Parser__parse_opaque_type(struct Parser* self, struct Token* name);
struct Parsed_Statement* Parser__parse_struct(struct Parser* self, struct Token* name);
struct Parsed_Statement* Parser__parse_enum(struct Parser* self, struct Token* name);
struct Parsed_Type* Parser__parse_type(struct Parser* self);
struct Parsed_Statement* Parser__parse_type_alias(struct Parser* self);
struct Parsed_Statement* Parser__parse_variable(struct Parser* self);
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self);
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self);
struct Parsed_Statement* Parser__parse_function(struct Parser* self, struct Token* name);
struct Parsed_Statement* Parser__parse_external_function(struct Parser* self, struct Token* name);
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
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct String* name, struct Checked_Type* return_type);
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
void Checker__check_function_type_statement(struct Checker* self, struct Parsed_Function_Type_Statement* parsed_statement);
void Checker__create_opaque_type(struct Checker* self, struct Parsed_Opaque_Type_Statement* parsed_statement);
void Checker__create_struct_type(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement);
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement);
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement);
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement);
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement);
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement);
struct Checked_If_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement);
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement);
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement);
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement);
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement);
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement);
struct Checked_Statements* Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements);
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
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement);
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
int32_t main(int32_t argc, char** argv);

#line 35 "bootstrap/stage0/ReCode.code"
struct String* String__create_empty(size_t data_size) {
#line 36 "bootstrap/stage0/ReCode.code"
    struct String* string = (struct String*) malloc(sizeof(struct String));
#line 37 "bootstrap/stage0/ReCode.code"
    string->data = (char*) malloc(data_size);
#line 38 "bootstrap/stage0/ReCode.code"
    string->data_size = data_size;
#line 39 "bootstrap/stage0/ReCode.code"
    string->length = (size_t) 0;
#line 40 "bootstrap/stage0/ReCode.code"
    return string;
}

#line 43 "bootstrap/stage0/ReCode.code"
struct String* String__create() {
#line 44 "bootstrap/stage0/ReCode.code"
    return String__create_empty((size_t) 16);
}

#line 47 "bootstrap/stage0/ReCode.code"
void String__delete(struct String* self) {
#line 48 "bootstrap/stage0/ReCode.code"
    free((void*) self->data);
#line 49 "bootstrap/stage0/ReCode.code"
    free((void*) self);
}

#line 52 "bootstrap/stage0/ReCode.code"
struct String* String__append_char(struct String* self, char ch) {
#line 53 "bootstrap/stage0/ReCode.code"
    if (self->length >= self->data_size) {
#line 54 "bootstrap/stage0/ReCode.code"
        self->data_size = self->data_size + (size_t) 16;
#line 55 "bootstrap/stage0/ReCode.code"
        self->data = (char*) realloc((void*) self->data, self->data_size);
    }
#line 57 "bootstrap/stage0/ReCode.code"
    self->data[self->length] = ch;
#line 58 "bootstrap/stage0/ReCode.code"
    self->length = self->length + (size_t) 1;
#line 59 "bootstrap/stage0/ReCode.code"
    return self;
}

#line 62 "bootstrap/stage0/ReCode.code"
struct String* String__append_cstring(struct String* self, char* s) {
#line 63 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 64 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 65 "bootstrap/stage0/ReCode.code"
        char c = s[index];
#line 66 "bootstrap/stage0/ReCode.code"
        if (c == '\0') {
#line 67 "bootstrap/stage0/ReCode.code"
            return self;
        }
#line 69 "bootstrap/stage0/ReCode.code"
        String__append_char(self, c);
#line 70 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
}

#line 74 "bootstrap/stage0/ReCode.code"
size_t cstring_length(char* s) {
#line 75 "bootstrap/stage0/ReCode.code"
    size_t length = (size_t) 0;
#line 76 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 77 "bootstrap/stage0/ReCode.code"
        uint8_t c = (uint8_t) s[length];
#line 78 "bootstrap/stage0/ReCode.code"
        if (c == (uint8_t) 0) {
#line 79 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 81 "bootstrap/stage0/ReCode.code"
        length = length + (size_t) 1;
    }
#line 83 "bootstrap/stage0/ReCode.code"
    return length;
}

#line 86 "bootstrap/stage0/ReCode.code"
struct String* String__create_from(char* data) {
#line 87 "bootstrap/stage0/ReCode.code"
    size_t string_length = cstring_length(data);
#line 88 "bootstrap/stage0/ReCode.code"
    struct String* string = String__create_empty(string_length);
#line 89 "bootstrap/stage0/ReCode.code"
    String__append_cstring(string, data);
#line 90 "bootstrap/stage0/ReCode.code"
    return string;
}

#line 93 "bootstrap/stage0/ReCode.code"
struct String* String__append_i16(struct String* self, int16_t value) {
#line 94 "bootstrap/stage0/ReCode.code"
    if (value < (int16_t) 0) {
#line 95 "bootstrap/stage0/ReCode.code"
        String__append_char(self, '-');
#line 96 "bootstrap/stage0/ReCode.code"
        String__append_i16(self, -value);
    } else {
#line 98 "bootstrap/stage0/ReCode.code"
        if (value >= (int16_t) 10) {
#line 99 "bootstrap/stage0/ReCode.code"
            String__append_i16(self, value / (int16_t) 10);
        }
#line 101 "bootstrap/stage0/ReCode.code"
        String__append_char(self, (char) (value % (int16_t) 10) + '0');
    }
#line 103 "bootstrap/stage0/ReCode.code"
    return self;
}

#line 106 "bootstrap/stage0/ReCode.code"
struct String* String__append_string(struct String* self, struct String* other) {
#line 107 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 108 "bootstrap/stage0/ReCode.code"
    while (index < other->length) {
#line 109 "bootstrap/stage0/ReCode.code"
        String__append_char(self, other->data[index]);
#line 110 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
#line 112 "bootstrap/stage0/ReCode.code"
    return self;
}

#line 115 "bootstrap/stage0/ReCode.code"
bool String__equals_cstring(struct String* self, char* s) {
#line 116 "bootstrap/stage0/ReCode.code"
    size_t length = cstring_length(s);
#line 117 "bootstrap/stage0/ReCode.code"
    if (self->length != length) {
#line 118 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 121 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 122 "bootstrap/stage0/ReCode.code"
    while (index < length) {
#line 123 "bootstrap/stage0/ReCode.code"
        if (self->data[index] != s[index]) {
#line 124 "bootstrap/stage0/ReCode.code"
            return false;
        }
#line 126 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
#line 129 "bootstrap/stage0/ReCode.code"
    return true;
}

#line 132 "bootstrap/stage0/ReCode.code"
bool String__equals_string(struct String* self, struct String* other) {
#line 133 "bootstrap/stage0/ReCode.code"
    if (self->length != other->length) {
#line 134 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 137 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 138 "bootstrap/stage0/ReCode.code"
    while (index < self->length) {
#line 139 "bootstrap/stage0/ReCode.code"
        if (self->data[index] != other->data[index]) {
#line 140 "bootstrap/stage0/ReCode.code"
            return false;
        }
#line 142 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
#line 145 "bootstrap/stage0/ReCode.code"
    return true;
}

#line 152 "bootstrap/stage0/ReCode.code"
void pass() {
}

#line 155 "bootstrap/stage0/ReCode.code"
void File__write_char(struct File* self, char c) {
#line 156 "bootstrap/stage0/ReCode.code"
    fputc((int32_t) c, self);
}

#line 159 "bootstrap/stage0/ReCode.code"
void File__write_cstring(struct File* self, char* s) {
#line 160 "bootstrap/stage0/ReCode.code"
    fputs(s, self);
}

#line 163 "bootstrap/stage0/ReCode.code"
void File__write_i32(struct File* self, int32_t value) {
#line 164 "bootstrap/stage0/ReCode.code"
    if (value < 0) {
#line 165 "bootstrap/stage0/ReCode.code"
        File__write_char(self, '-');
#line 166 "bootstrap/stage0/ReCode.code"
        File__write_i32(self, -value);
    } else {
#line 168 "bootstrap/stage0/ReCode.code"
        if (value >= 10) {
#line 169 "bootstrap/stage0/ReCode.code"
            File__write_i32(self, value / 10);
        }
#line 171 "bootstrap/stage0/ReCode.code"
        File__write_char(self, (char) (value % 10) + '0');
    }
}

#line 175 "bootstrap/stage0/ReCode.code"
void File__write_u64(struct File* self, uint64_t value) {
#line 176 "bootstrap/stage0/ReCode.code"
    if (value >= (uint64_t) 10) {
#line 177 "bootstrap/stage0/ReCode.code"
        File__write_u64(self, value / (uint64_t) 10);
    }
#line 179 "bootstrap/stage0/ReCode.code"
    File__write_char(self, (char) (value % (uint64_t) 10) + '0');
}

#line 182 "bootstrap/stage0/ReCode.code"
void File__write_string(struct File* self, struct String* string) {
#line 183 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 184 "bootstrap/stage0/ReCode.code"
    while (index < string->length) {
#line 185 "bootstrap/stage0/ReCode.code"
        File__write_char(self, string->data[index]);
#line 186 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
}

#line 190 "bootstrap/stage0/ReCode.code"
void error(struct String* message) {
#line 191 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;91m");
#line 192 "bootstrap/stage0/ReCode.code"
    File__write_string(stderr, message);
#line 193 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 196 "bootstrap/stage0/ReCode.code"
void warning(struct String* message) {
#line 197 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;93m");
#line 198 "bootstrap/stage0/ReCode.code"
    File__write_string(stderr, message);
#line 199 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 202 "bootstrap/stage0/ReCode.code"
void TODO(char* message) {
#line 203 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;95mTODO: ");
#line 204 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, message);
#line 205 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 217 "bootstrap/stage0/ReCode.code"
struct Source* Source__create(struct File* file, char* file_path) {
#line 218 "bootstrap/stage0/ReCode.code"
    struct String* file_content = String__create();
#line 220 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 221 "bootstrap/stage0/ReCode.code"
        int32_t ch = fgetc(file);
#line 222 "bootstrap/stage0/ReCode.code"
        if (ch == -1) {
#line 223 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 225 "bootstrap/stage0/ReCode.code"
        String__append_char(file_content, (char) ch);
    }
#line 228 "bootstrap/stage0/ReCode.code"
    String__append_char(file_content, '\0');
#line 230 "bootstrap/stage0/ReCode.code"
    struct Source* source = (struct Source*) malloc(sizeof(struct Source));
#line 231 "bootstrap/stage0/ReCode.code"
    source->content = file_content;
#line 232 "bootstrap/stage0/ReCode.code"
    source->path = file_path;
#line 234 "bootstrap/stage0/ReCode.code"
    return source;
}

#line 247 "bootstrap/stage0/ReCode.code"
struct Source_Location* Source_Location__create(struct Source* source, uint16_t line, uint16_t column) {
#line 248 "bootstrap/stage0/ReCode.code"
    struct Source_Location* source_location = (struct Source_Location*) malloc(sizeof(struct Source_Location));
#line 249 "bootstrap/stage0/ReCode.code"
    source_location->source = source;
#line 250 "bootstrap/stage0/ReCode.code"
    source_location->line = line;
#line 251 "bootstrap/stage0/ReCode.code"
    source_location->column = column;
#line 252 "bootstrap/stage0/ReCode.code"
    return source_location;
}

#line 255 "bootstrap/stage0/ReCode.code"
struct String* String__append_source_location(struct String* self, struct Source_Location* location) {
#line 256 "bootstrap/stage0/ReCode.code"
    String__append_cstring(self, location->source->path);
#line 257 "bootstrap/stage0/ReCode.code"
    String__append_char(self, ':');
#line 258 "bootstrap/stage0/ReCode.code"
    String__append_i16(self, (int16_t) location->line);
#line 259 "bootstrap/stage0/ReCode.code"
    String__append_char(self, ':');
#line 260 "bootstrap/stage0/ReCode.code"
    String__append_i16(self, (int16_t) location->column);
#line 261 "bootstrap/stage0/ReCode.code"
    return self;
}

#line 264 "bootstrap/stage0/ReCode.code"
void File__write_source_location(struct File* self, struct Source_Location* location) {
#line 265 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self, location->source->path);
#line 266 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ':');
#line 267 "bootstrap/stage0/ReCode.code"
    File__write_i32(self, (int32_t) location->line);
#line 268 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ':');
#line 269 "bootstrap/stage0/ReCode.code"
    File__write_i32(self, (int32_t) location->column);
#line 270 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self, ": ");
}

#line 273 "bootstrap/stage0/ReCode.code"
void Source_Location__error(struct Source_Location* self, struct String* message) {
#line 274 "bootstrap/stage0/ReCode.code"
    File__write_source_location(stderr, self);
#line 275 "bootstrap/stage0/ReCode.code"
    error(message);
}

#line 278 "bootstrap/stage0/ReCode.code"
void Source_Location__warning(struct Source_Location* self, struct String* message) {
#line 279 "bootstrap/stage0/ReCode.code"
    File__write_source_location(stderr, self);
#line 280 "bootstrap/stage0/ReCode.code"
    warning(message);
}

#line 308 "bootstrap/stage0/ReCode.code"
struct Token* Token__create_kind(enum Token_Kind kind, size_t kind_size, struct Source_Location* location, struct String* lexeme) {
#line 309 "bootstrap/stage0/ReCode.code"
    struct Token* token = (struct Token*) malloc(kind_size);
#line 310 "bootstrap/stage0/ReCode.code"
    token->kind = kind;
#line 311 "bootstrap/stage0/ReCode.code"
    token->location = location;
#line 312 "bootstrap/stage0/ReCode.code"
    token->lexeme = lexeme;
#line 313 "bootstrap/stage0/ReCode.code"
    token->next_token = NULL;
#line 314 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 317 "bootstrap/stage0/ReCode.code"
void Token__error(struct Token* self, struct String* message) {
#line 318 "bootstrap/stage0/ReCode.code"
    Source_Location__error(self->location, message);
}

#line 321 "bootstrap/stage0/ReCode.code"
void Token__warning(struct Token* self, struct String* message) {
#line 322 "bootstrap/stage0/ReCode.code"
    Source_Location__warning(self->location, message);
}

#line 330 "bootstrap/stage0/ReCode.code"
struct Character_Token* Character_Token__create(struct Source_Location* location, struct String* lexeme, char value) {
#line 331 "bootstrap/stage0/ReCode.code"
    struct Character_Token* token = (struct Character_Token*) Token__create_kind(Token_Kind__CHARACTER, sizeof(struct Character_Token), location, lexeme);
#line 332 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 333 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 340 "bootstrap/stage0/ReCode.code"
struct Comment_Token* Comment_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 341 "bootstrap/stage0/ReCode.code"
    return (struct Comment_Token*) Token__create_kind(Token_Kind__COMMENT, sizeof(struct Comment_Token), location, lexeme);
}

#line 348 "bootstrap/stage0/ReCode.code"
struct End_Of_File_Token* End_Of_File_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 349 "bootstrap/stage0/ReCode.code"
    return (struct End_Of_File_Token*) Token__create_kind(Token_Kind__END_OF_FILE, sizeof(struct End_Of_File_Token), location, lexeme);
}

#line 356 "bootstrap/stage0/ReCode.code"
struct End_Of_Line_Token* End_Of_Line_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 357 "bootstrap/stage0/ReCode.code"
    return (struct End_Of_Line_Token*) Token__create_kind(Token_Kind__END_OF_LINE, sizeof(struct End_Of_Line_Token), location, lexeme);
}

#line 364 "bootstrap/stage0/ReCode.code"
struct Error_Token* Error_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 365 "bootstrap/stage0/ReCode.code"
    return (struct Error_Token*) Token__create_kind(Token_Kind__ERROR, sizeof(struct Error_Token), location, lexeme);
}

#line 372 "bootstrap/stage0/ReCode.code"
struct Identifier_Token* Identifier_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 373 "bootstrap/stage0/ReCode.code"
    return (struct Identifier_Token*) Token__create_kind(Token_Kind__IDENTIFIER, sizeof(struct Identifier_Token), location, lexeme);
}

#line 381 "bootstrap/stage0/ReCode.code"
struct Integer_Token* Integer_Token__create(struct Source_Location* location, struct String* lexeme, uint64_t value) {
#line 382 "bootstrap/stage0/ReCode.code"
    struct Integer_Token* token = (struct Integer_Token*) Token__create_kind(Token_Kind__INTEGER, sizeof(struct Integer_Token), location, lexeme);
#line 383 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 384 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 391 "bootstrap/stage0/ReCode.code"
struct Other_Token* Other_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 392 "bootstrap/stage0/ReCode.code"
    return (struct Other_Token*) Token__create_kind(Token_Kind__OTHER, sizeof(struct Other_Token), location, lexeme);
}

#line 400 "bootstrap/stage0/ReCode.code"
struct Space_Token* Space_Token__create(struct Source_Location* location, struct String* lexeme, uint16_t count) {
#line 401 "bootstrap/stage0/ReCode.code"
    struct Space_Token* token = (struct Space_Token*) Token__create_kind(Token_Kind__SPACE, sizeof(struct Space_Token), location, lexeme);
#line 402 "bootstrap/stage0/ReCode.code"
    token->count = count;
#line 403 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 411 "bootstrap/stage0/ReCode.code"
struct String_Token* String_Token__create(struct Source_Location* location, struct String* lexeme, struct String* value) {
#line 412 "bootstrap/stage0/ReCode.code"
    struct String_Token* token = (struct String_Token*) Token__create_kind(Token_Kind__STRING, sizeof(struct String_Token), location, lexeme);
#line 413 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 414 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 417 "bootstrap/stage0/ReCode.code"
bool Token__is_anything(struct Token* self) {
#line 418 "bootstrap/stage0/ReCode.code"
    return self != NULL;
}

#line 421 "bootstrap/stage0/ReCode.code"
bool Token__is_character(struct Token* self) {
#line 422 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__CHARACTER;
}

#line 425 "bootstrap/stage0/ReCode.code"
bool Token__is_comment(struct Token* self) {
#line 426 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__COMMENT;
}

#line 429 "bootstrap/stage0/ReCode.code"
bool Token__is_end_of_file(struct Token* self) {
#line 430 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__END_OF_FILE;
}

#line 433 "bootstrap/stage0/ReCode.code"
bool Token__is_end_of_line(struct Token* self) {
#line 434 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__END_OF_LINE || self->kind == Token_Kind__END_OF_FILE;
}

#line 437 "bootstrap/stage0/ReCode.code"
bool Token__is_identifier(struct Token* self) {
#line 438 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__IDENTIFIER;
}

#line 441 "bootstrap/stage0/ReCode.code"
bool Token__is_integer(struct Token* self) {
#line 442 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__INTEGER;
}

#line 445 "bootstrap/stage0/ReCode.code"
bool Token__is_keyword(struct Token* self, char* lexeme) {
#line 446 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

#line 449 "bootstrap/stage0/ReCode.code"
bool Token__is_break(struct Token* self) {
#line 450 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "break");
}

#line 453 "bootstrap/stage0/ReCode.code"
bool Token__is_define(struct Token* self) {
#line 454 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "define");
}

#line 457 "bootstrap/stage0/ReCode.code"
bool Token__is_else(struct Token* self) {
#line 458 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "else");
}

#line 461 "bootstrap/stage0/ReCode.code"
bool Token__is_enum(struct Token* self) {
#line 462 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "enum");
}

#line 465 "bootstrap/stage0/ReCode.code"
bool Token__is_extern(struct Token* self) {
#line 466 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "extern");
}

#line 469 "bootstrap/stage0/ReCode.code"
bool Token__is_external(struct Token* self) {
#line 470 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "external");
}

#line 473 "bootstrap/stage0/ReCode.code"
bool Token__is_false(struct Token* self) {
#line 474 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "false");
}

#line 477 "bootstrap/stage0/ReCode.code"
bool Token__is_func(struct Token* self) {
#line 478 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "func");
}

#line 481 "bootstrap/stage0/ReCode.code"
bool Token__is_if(struct Token* self) {
#line 482 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "if");
}

#line 485 "bootstrap/stage0/ReCode.code"
bool Token__is_null(struct Token* self) {
#line 486 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "null");
}

#line 489 "bootstrap/stage0/ReCode.code"
bool Token__is_opaque(struct Token* self) {
#line 490 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "opaque");
}

#line 493 "bootstrap/stage0/ReCode.code"
bool Token__is_return(struct Token* self) {
#line 494 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "return");
}

#line 497 "bootstrap/stage0/ReCode.code"
bool Token__is_sizeof(struct Token* self) {
#line 498 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "sizeof");
}

#line 501 "bootstrap/stage0/ReCode.code"
bool Token__is_struct(struct Token* self) {
#line 502 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "struct");
}

#line 505 "bootstrap/stage0/ReCode.code"
bool Token__is_true(struct Token* self) {
#line 506 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "true");
}

#line 509 "bootstrap/stage0/ReCode.code"
bool Token__is_type(struct Token* self) {
#line 510 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "type");
}

#line 513 "bootstrap/stage0/ReCode.code"
bool Token__is_typedef(struct Token* self) {
#line 514 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "typedef");
}

#line 517 "bootstrap/stage0/ReCode.code"
bool Token__is_while(struct Token* self) {
#line 518 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "while");
}

#line 521 "bootstrap/stage0/ReCode.code"
bool Token__is_other(struct Token* self, char* lexeme) {
#line 522 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__OTHER && String__equals_cstring(self->lexeme, lexeme);
}

#line 525 "bootstrap/stage0/ReCode.code"
bool Token__is_ampersand(struct Token* self) {
#line 526 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "&");
}

#line 529 "bootstrap/stage0/ReCode.code"
bool Token__is_asterisk(struct Token* self) {
#line 530 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "*");
}

#line 533 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_brace(struct Token* self) {
#line 534 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "}");
}

#line 537 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_bracket(struct Token* self) {
#line 538 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "]");
}

#line 541 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_paren(struct Token* self) {
#line 542 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ")");
}

#line 545 "bootstrap/stage0/ReCode.code"
bool Token__is_colon(struct Token* self) {
#line 546 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ":");
}

#line 549 "bootstrap/stage0/ReCode.code"
bool Token__is_comma(struct Token* self) {
#line 550 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ",");
}

#line 553 "bootstrap/stage0/ReCode.code"
bool Token__is_dot(struct Token* self) {
#line 554 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ".");
}

#line 557 "bootstrap/stage0/ReCode.code"
bool Token__is_equals(struct Token* self) {
#line 558 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "=");
}

#line 561 "bootstrap/stage0/ReCode.code"
bool Token__is_exclamation_mark(struct Token* self) {
#line 562 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "!");
}

#line 565 "bootstrap/stage0/ReCode.code"
bool Token__is_greater_than(struct Token* self) {
#line 566 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ">");
}

#line 569 "bootstrap/stage0/ReCode.code"
bool Token__is_less_than(struct Token* self) {
#line 570 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "<");
}

#line 573 "bootstrap/stage0/ReCode.code"
bool Token__is_minus(struct Token* self) {
#line 574 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "-");
}

#line 577 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_brace(struct Token* self) {
#line 578 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "{");
}

#line 581 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_bracket(struct Token* self) {
#line 582 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "[");
}

#line 585 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_paren(struct Token* self) {
#line 586 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "(");
}

#line 589 "bootstrap/stage0/ReCode.code"
bool Token__is_percent(struct Token* self) {
#line 590 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "%");
}

#line 593 "bootstrap/stage0/ReCode.code"
bool Token__is_plus(struct Token* self) {
#line 594 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "+");
}

#line 597 "bootstrap/stage0/ReCode.code"
bool Token__is_slash(struct Token* self) {
#line 598 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "/");
}

#line 601 "bootstrap/stage0/ReCode.code"
bool Token__is_vertical_bar(struct Token* self) {
#line 602 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "|");
}

#line 605 "bootstrap/stage0/ReCode.code"
bool Token__is_space(struct Token* self) {
#line 606 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__SPACE;
}

#line 609 "bootstrap/stage0/ReCode.code"
bool Token__is_string(struct Token* self) {
#line 610 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__STRING;
}

#line 613 "bootstrap/stage0/ReCode.code"
void File__write_token(struct File* stream, struct Token* token) {
#line 614 "bootstrap/stage0/ReCode.code"
    bool colored = token->kind == Token_Kind__COMMENT || token->kind == Token_Kind__ERROR || token->kind == Token_Kind__OTHER;
#line 615 "bootstrap/stage0/ReCode.code"
    if (colored) {
#line 616 "bootstrap/stage0/ReCode.code"
        if (token->kind == Token_Kind__OTHER) {
#line 617 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\33[2;33m");
        } else if (token->kind == Token_Kind__COMMENT) {
#line 619 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\33[2;37m");
        } else if (token->kind == Token_Kind__ERROR) {
#line 621 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\33[2;31m");
        }
    }
#line 624 "bootstrap/stage0/ReCode.code"
    File__write_string(stream, token->lexeme);
#line 625 "bootstrap/stage0/ReCode.code"
    if (colored) {
#line 626 "bootstrap/stage0/ReCode.code"
        File__write_cstring(stream, "\33[0m");
    }
}

#line 642 "bootstrap/stage0/ReCode.code"
char Scanner__peek_char(struct Scanner* self) {
#line 643 "bootstrap/stage0/ReCode.code"
    return self->source->content->data[self->current_char_index];
}

#line 646 "bootstrap/stage0/ReCode.code"
char Scanner__next_char(struct Scanner* self) {
#line 647 "bootstrap/stage0/ReCode.code"
    char next_char = Scanner__peek_char(self);
#line 648 "bootstrap/stage0/ReCode.code"
    if (next_char != '\0') {
#line 649 "bootstrap/stage0/ReCode.code"
        self->current_char_index = self->current_char_index + (size_t) 1;
#line 650 "bootstrap/stage0/ReCode.code"
        if (next_char == '\n') {
#line 651 "bootstrap/stage0/ReCode.code"
            self->current_line = self->current_line + (uint16_t) 1;
#line 652 "bootstrap/stage0/ReCode.code"
            self->current_column = (uint16_t) 1;
        } else {
#line 654 "bootstrap/stage0/ReCode.code"
            self->current_column = self->current_column + (uint16_t) 1;
        }
    }
#line 657 "bootstrap/stage0/ReCode.code"
    return next_char;
}

#line 660 "bootstrap/stage0/ReCode.code"
char escape_char_value(char c) {
#line 661 "bootstrap/stage0/ReCode.code"
    if (c == 'n') {
#line 662 "bootstrap/stage0/ReCode.code"
        return '\n';
    }
#line 664 "bootstrap/stage0/ReCode.code"
    if (c == '\"') {
#line 665 "bootstrap/stage0/ReCode.code"
        return '\"';
    }
#line 667 "bootstrap/stage0/ReCode.code"
    if (c == '\'') {
#line 668 "bootstrap/stage0/ReCode.code"
        return '\'';
    }
#line 670 "bootstrap/stage0/ReCode.code"
    if (c == '\\') {
#line 671 "bootstrap/stage0/ReCode.code"
        return '\\';
    }
#line 673 "bootstrap/stage0/ReCode.code"
    if (c == 't') {
#line 674 "bootstrap/stage0/ReCode.code"
        return '\t';
    }
#line 676 "bootstrap/stage0/ReCode.code"
    if (c == '0') {
#line 677 "bootstrap/stage0/ReCode.code"
        return '\0';
    }
#line 679 "bootstrap/stage0/ReCode.code"
    if (c == 'e') {
#line 680 "bootstrap/stage0/ReCode.code"
        return '\33';
    }
#line 682 "bootstrap/stage0/ReCode.code"
    return (char) -1;
}

#line 685 "bootstrap/stage0/ReCode.code"
bool char_is_end_of_line(char c) {
#line 686 "bootstrap/stage0/ReCode.code"
    return c == '\n' || c == '\0';
}

#line 689 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_character_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 690 "bootstrap/stage0/ReCode.code"
    if (Scanner__next_char(self) != '\'') {
#line 691 "bootstrap/stage0/ReCode.code"
        Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 692 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 694 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\'');
#line 696 "bootstrap/stage0/ReCode.code"
    char next_char = Scanner__peek_char(self);
#line 697 "bootstrap/stage0/ReCode.code"
    if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 698 "bootstrap/stage0/ReCode.code"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 701 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 702 "bootstrap/stage0/ReCode.code"
    char value = next_char;
#line 704 "bootstrap/stage0/ReCode.code"
    if (value == '\'') {
#line 705 "bootstrap/stage0/ReCode.code"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 708 "bootstrap/stage0/ReCode.code"
    if (value == '\\') {
#line 709 "bootstrap/stage0/ReCode.code"
        next_char = Scanner__peek_char(self);
#line 710 "bootstrap/stage0/ReCode.code"
        if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 711 "bootstrap/stage0/ReCode.code"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
#line 714 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 716 "bootstrap/stage0/ReCode.code"
        value = escape_char_value(next_char);
#line 717 "bootstrap/stage0/ReCode.code"
        if (value == (char) -1) {
#line 718 "bootstrap/stage0/ReCode.code"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
    }
#line 722 "bootstrap/stage0/ReCode.code"
    if (Scanner__peek_char(self) != '\'') {
#line 723 "bootstrap/stage0/ReCode.code"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 726 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 727 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Character_Token__create(source_location, token_lexeme, value);
}

#line 730 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_comment_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 731 "bootstrap/stage0/ReCode.code"
    while (!char_is_end_of_line(Scanner__peek_char(self))) {
#line 732 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 734 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Comment_Token__create(source_location, token_lexeme);
}

#line 737 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_start(char c) {
#line 738 "bootstrap/stage0/ReCode.code"
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

#line 741 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_letter(char c) {
#line 742 "bootstrap/stage0/ReCode.code"
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

#line 745 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_identifier_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 746 "bootstrap/stage0/ReCode.code"
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
#line 747 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 749 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Identifier_Token__create(source_location, token_lexeme);
}

#line 752 "bootstrap/stage0/ReCode.code"
bool char_is_digit(char c) {
#line 753 "bootstrap/stage0/ReCode.code"
    return c >= '0' && c <= '9';
}

#line 756 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_integer_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 757 "bootstrap/stage0/ReCode.code"
    uint64_t value = (uint64_t) 0;
#line 758 "bootstrap/stage0/ReCode.code"
    while (char_is_digit(Scanner__peek_char(self))) {
#line 759 "bootstrap/stage0/ReCode.code"
        char c = Scanner__next_char(self);
#line 760 "bootstrap/stage0/ReCode.code"
        value = value * (uint64_t) 10 + (uint64_t) (c - '0');
#line 761 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, c);
    }
#line 763 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Integer_Token__create(source_location, token_lexeme, value);
}

#line 766 "bootstrap/stage0/ReCode.code"
bool char_is_space(char c) {
#line 767 "bootstrap/stage0/ReCode.code"
    return c == ' ';
}

#line 770 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_space_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 771 "bootstrap/stage0/ReCode.code"
    uint16_t count = (uint16_t) 0;
#line 772 "bootstrap/stage0/ReCode.code"
    while (char_is_space(Scanner__peek_char(self))) {
#line 773 "bootstrap/stage0/ReCode.code"
        count = count + (uint16_t) 1;
#line 774 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 776 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Space_Token__create(source_location, token_lexeme, count);
}

#line 779 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_string_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 780 "bootstrap/stage0/ReCode.code"
    if (Scanner__next_char(self) != '\"') {
#line 781 "bootstrap/stage0/ReCode.code"
        Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 782 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 784 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\"');
#line 786 "bootstrap/stage0/ReCode.code"
    struct String* value = String__create();
#line 788 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 789 "bootstrap/stage0/ReCode.code"
        char next_char = Scanner__peek_char(self);
#line 790 "bootstrap/stage0/ReCode.code"
        if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 791 "bootstrap/stage0/ReCode.code"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
#line 794 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 796 "bootstrap/stage0/ReCode.code"
        if (next_char == '\"') {
#line 797 "bootstrap/stage0/ReCode.code"
            return (struct Token*) String_Token__create(source_location, token_lexeme, value);
        }
#line 800 "bootstrap/stage0/ReCode.code"
        if (next_char == '\\') {
#line 801 "bootstrap/stage0/ReCode.code"
            next_char = Scanner__peek_char(self);
#line 802 "bootstrap/stage0/ReCode.code"
            if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 803 "bootstrap/stage0/ReCode.code"
                return (struct Token*) Error_Token__create(source_location, token_lexeme);
            }
#line 806 "bootstrap/stage0/ReCode.code"
            String__append_char(token_lexeme, Scanner__next_char(self));
#line 808 "bootstrap/stage0/ReCode.code"
            next_char = escape_char_value(next_char);
#line 809 "bootstrap/stage0/ReCode.code"
            if (next_char == ((char) -1)) {
#line 810 "bootstrap/stage0/ReCode.code"
                return (struct Token*) Error_Token__create(source_location, token_lexeme);
            }
        }
#line 814 "bootstrap/stage0/ReCode.code"
        String__append_char(value, next_char);
    }
}

#line 818 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_token(struct Scanner* self) {
#line 819 "bootstrap/stage0/ReCode.code"
    struct Source_Location* source_location = Source_Location__create(self->source, self->current_line, self->current_column);
#line 820 "bootstrap/stage0/ReCode.code"
    struct String* token_lexeme = String__create();
#line 822 "bootstrap/stage0/ReCode.code"
    char next_char = Scanner__peek_char(self);
#line 824 "bootstrap/stage0/ReCode.code"
    if (char_is_identifier_start(next_char)) {
#line 825 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_identifier_token(self, source_location, token_lexeme);
    }
#line 828 "bootstrap/stage0/ReCode.code"
    if (char_is_digit(next_char)) {
#line 829 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_integer_token(self, source_location, token_lexeme);
    }
#line 832 "bootstrap/stage0/ReCode.code"
    if (char_is_space(next_char)) {
#line 833 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_space_token(self, source_location, token_lexeme);
    }
#line 836 "bootstrap/stage0/ReCode.code"
    if (next_char == '\'') {
#line 837 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_character_token(self, source_location, token_lexeme);
    }
#line 840 "bootstrap/stage0/ReCode.code"
    if (next_char == '\"') {
#line 841 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_string_token(self, source_location, token_lexeme);
    }
#line 844 "bootstrap/stage0/ReCode.code"
    if (next_char == '\\') {
#line 845 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_comment_token(self, source_location, token_lexeme);
    }
#line 848 "bootstrap/stage0/ReCode.code"
    if (next_char == '\n') {
#line 849 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 850 "bootstrap/stage0/ReCode.code"
        return (struct Token*) End_Of_Line_Token__create(source_location, token_lexeme);
    }
#line 853 "bootstrap/stage0/ReCode.code"
    if (next_char == '\0') {
#line 854 "bootstrap/stage0/ReCode.code"
        return (struct Token*) End_Of_File_Token__create(source_location, token_lexeme);
    }
#line 857 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 858 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Other_Token__create(source_location, token_lexeme);
}

#line 861 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__next_token(struct Scanner* self) {
#line 862 "bootstrap/stage0/ReCode.code"
    if (self->current_token->next_token == NULL) {
#line 863 "bootstrap/stage0/ReCode.code"
        self->current_token->next_token = Scanner__scan_token(self);
    }
#line 865 "bootstrap/stage0/ReCode.code"
    self->current_token = self->current_token->next_token;
#line 866 "bootstrap/stage0/ReCode.code"
    return self->current_token;
}

#line 869 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__peek_token(struct Scanner* self, uint8_t offset) {
#line 870 "bootstrap/stage0/ReCode.code"
    struct Token* token = self->current_token;
#line 871 "bootstrap/stage0/ReCode.code"
    while (offset > (uint8_t) 0) {
#line 872 "bootstrap/stage0/ReCode.code"
        if (token->next_token == NULL) {
#line 873 "bootstrap/stage0/ReCode.code"
            token->next_token = Scanner__scan_token(self);
        }
#line 875 "bootstrap/stage0/ReCode.code"
        token = token->next_token;
#line 876 "bootstrap/stage0/ReCode.code"
        offset = offset - (uint8_t) 1;
    }
#line 878 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 881 "bootstrap/stage0/ReCode.code"
struct Scanner* Scanner__create(struct Source* source) {
#line 882 "bootstrap/stage0/ReCode.code"
    struct Scanner* scanner = (struct Scanner*) malloc(sizeof(struct Scanner));
#line 883 "bootstrap/stage0/ReCode.code"
    scanner->source = source;
#line 884 "bootstrap/stage0/ReCode.code"
    scanner->current_char_index = (size_t) 0;
#line 885 "bootstrap/stage0/ReCode.code"
    scanner->current_line = (uint16_t) 1;
#line 886 "bootstrap/stage0/ReCode.code"
    scanner->current_column = (uint16_t) 1;
#line 888 "bootstrap/stage0/ReCode.code"
    scanner->current_token = Scanner__scan_token(scanner);
#line 890 "bootstrap/stage0/ReCode.code"
    return scanner;
}

#line 912 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Type__create_kind(enum Parsed_Type_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 913 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = (struct Parsed_Type*) malloc(kind_size);
#line 914 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 915 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 916 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 924 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Named_Type__create(struct Token* name) {
#line 925 "bootstrap/stage0/ReCode.code"
    struct Parsed_Named_Type* type = (struct Parsed_Named_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__NAMED, sizeof(struct Parsed_Named_Type), name->location);
#line 926 "bootstrap/stage0/ReCode.code"
    type->name = name->lexeme;
#line 927 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Type*) type;
}

#line 935 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Pointer_Type__create(struct Parsed_Type* other_type) {
#line 936 "bootstrap/stage0/ReCode.code"
    struct Parsed_Pointer_Type* type = (struct Parsed_Pointer_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__POINTER, sizeof(struct Parsed_Pointer_Type), other_type->location);
#line 937 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 938 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Type*) type;
}

#line 946 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Struct_Type__create(struct Source_Location* location, struct Parsed_Type* other_type) {
#line 947 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Type* type = (struct Parsed_Struct_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__STRUCT, sizeof(struct Parsed_Struct_Type), location);
#line 948 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 949 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Type*) type;
}

#line 988 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parsed_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 989 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = (struct Parsed_Expression*) malloc(kind_size);
#line 990 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 991 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 992 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1001 "bootstrap/stage0/ReCode.code"
struct Parsed_Binary_Expression* Parsed_Binary_Expression__create_kind(enum Parsed_Expression_Kind kind, struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1002 "bootstrap/stage0/ReCode.code"
    struct Parsed_Binary_Expression* expression = (struct Parsed_Binary_Expression*) Parsed_Expression__create_kind(kind, sizeof(struct Parsed_Binary_Expression), left_expression->location);
#line 1003 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 1004 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 1005 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1013 "bootstrap/stage0/ReCode.code"
struct Parsed_Unary_Expression* Parsed_Unary_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1014 "bootstrap/stage0/ReCode.code"
    struct Parsed_Unary_Expression* expression = (struct Parsed_Unary_Expression*) Parsed_Expression__create_kind(kind, kind_size, location);
#line 1015 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1016 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1024 "bootstrap/stage0/ReCode.code"
struct Parsed_Literal_Expression* Parsed_Literal_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Token* literal) {
#line 1025 "bootstrap/stage0/ReCode.code"
    struct Parsed_Literal_Expression* expression = (struct Parsed_Literal_Expression*) Parsed_Expression__create_kind(kind, kind_size, literal->location);
#line 1026 "bootstrap/stage0/ReCode.code"
    expression->literal = literal;
#line 1027 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1034 "bootstrap/stage0/ReCode.code"
struct Parsed_Add_Expression* Parsed_Add_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1035 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Add_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__ADD, left_expression, right_expression);
}

#line 1042 "bootstrap/stage0/ReCode.code"
struct Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1043 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Address_Of_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__ADDRESS_OF, sizeof(struct Parsed_Address_Of_Expression), location, other_expression);
}

#line 1052 "bootstrap/stage0/ReCode.code"
struct Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(struct Parsed_Expression* array_expression, struct Parsed_Expression* index_expression) {
#line 1053 "bootstrap/stage0/ReCode.code"
    struct Parsed_Array_Access_Expression* expression = (struct Parsed_Array_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__ARRAY_ACCESS, sizeof(struct Parsed_Array_Access_Expression), array_expression->location);
#line 1054 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 1055 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 1056 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1064 "bootstrap/stage0/ReCode.code"
struct Parsed_Bool_Expression* Parsed_Bool_Expression__create(struct Token* literal, bool value) {
#line 1065 "bootstrap/stage0/ReCode.code"
    struct Parsed_Bool_Expression* expression = (struct Parsed_Bool_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__BOOL, sizeof(struct Parsed_Bool_Expression), literal);
#line 1066 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 1067 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1075 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Argument* Parsed_Call_Argument__create(struct Parsed_Expression* expression) {
#line 1076 "bootstrap/stage0/ReCode.code"
    struct Parsed_Call_Argument* argument = (struct Parsed_Call_Argument*) malloc(sizeof(struct Parsed_Call_Argument));
#line 1077 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 1078 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 1079 "bootstrap/stage0/ReCode.code"
    return argument;
}

#line 1088 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Expression* Parsed_Call_Expression__create(struct Parsed_Expression* callee_expression) {
#line 1089 "bootstrap/stage0/ReCode.code"
    struct Parsed_Call_Expression* expression = (struct Parsed_Call_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__CALL, sizeof(struct Parsed_Call_Expression), callee_expression->location);
#line 1090 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 1091 "bootstrap/stage0/ReCode.code"
    expression->first_argument = NULL;
#line 1092 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1100 "bootstrap/stage0/ReCode.code"
struct Parsed_Cast_Expression* Parsed_Cast_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression, struct Parsed_Type* type) {
#line 1101 "bootstrap/stage0/ReCode.code"
    struct Parsed_Cast_Expression* expression = (struct Parsed_Cast_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__CAST, sizeof(struct Parsed_Cast_Expression), location, other_expression);
#line 1102 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1103 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1111 "bootstrap/stage0/ReCode.code"
struct Parsed_Character_Expression* Parsed_Character_Expression__create(struct Character_Token* literal) {
#line 1112 "bootstrap/stage0/ReCode.code"
    struct Parsed_Character_Expression* expression = (struct Parsed_Character_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__CHARACTER, sizeof(struct Parsed_Character_Expression), (struct Token*) literal);
#line 1113 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1114 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1121 "bootstrap/stage0/ReCode.code"
struct Parsed_Divide_Expression* Parsed_Divide_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1122 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Divide_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__DIVIDE, left_expression, right_expression);
}

#line 1129 "bootstrap/stage0/ReCode.code"
struct Parsed_Equals_Expression* Parsed_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1130 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__EQUALS, left_expression, right_expression);
}

#line 1137 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Expression* Parsed_Greater_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1138 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Greater_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER, left_expression, right_expression);
}

#line 1145 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1146 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Greater_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER_OR_EQUALS, left_expression, right_expression);
}

#line 1154 "bootstrap/stage0/ReCode.code"
struct Parsed_Group_Expression* Parsed_Group_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1155 "bootstrap/stage0/ReCode.code"
    struct Parsed_Group_Expression* expression = (struct Parsed_Group_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__GROUP, sizeof(struct Parsed_Group_Expression), location);
#line 1156 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1157 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1165 "bootstrap/stage0/ReCode.code"
struct Parsed_Integer_Expression* Parsed_Integer_Expression__create(struct Integer_Token* literal) {
#line 1166 "bootstrap/stage0/ReCode.code"
    struct Parsed_Integer_Expression* expression = (struct Parsed_Integer_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__INTEGER, sizeof(struct Parsed_Integer_Expression), (struct Token*) literal);
#line 1167 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1168 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1175 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Expression* Parsed_Less_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1176 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Less_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS, left_expression, right_expression);
}

#line 1183 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1184 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Less_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS_OR_EQUALS, left_expression, right_expression);
}

#line 1191 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1192 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Logic_And_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_AND, left_expression, right_expression);
}

#line 1199 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1200 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Logic_Or_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_OR, left_expression, right_expression);
}

#line 1209 "bootstrap/stage0/ReCode.code"
struct Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(struct Parsed_Expression* object_expression, struct Token* member_name) {
#line 1210 "bootstrap/stage0/ReCode.code"
    struct Parsed_Member_Access_Expression* expression = (struct Parsed_Member_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__MEMBER_ACCESS, sizeof(struct Parsed_Member_Access_Expression), object_expression->location);
#line 1211 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 1212 "bootstrap/stage0/ReCode.code"
    expression->member_name = member_name;
#line 1213 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1220 "bootstrap/stage0/ReCode.code"
struct Parsed_Minus_Expression* Parsed_Minus_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1221 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Minus_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__MINUS, sizeof(struct Parsed_Minus_Expression), location, other_expression);
}

#line 1228 "bootstrap/stage0/ReCode.code"
struct Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1229 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Modulo_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MODULO, left_expression, right_expression);
}

#line 1236 "bootstrap/stage0/ReCode.code"
struct Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1237 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Multiply_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MULTIPLY, left_expression, right_expression);
}

#line 1244 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Expression* Parsed_Not_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1245 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Not_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__NOT, sizeof(struct Parsed_Not_Expression), location, other_expression);
}

#line 1252 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1253 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Not_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__NOT_EQUALS, left_expression, right_expression);
}

#line 1260 "bootstrap/stage0/ReCode.code"
struct Parsed_Null_Expression* Parsed_Null_Expression__create(struct Token* literal) {
#line 1261 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Null_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__NULL, sizeof(struct Parsed_Null_Expression), literal);
}

#line 1269 "bootstrap/stage0/ReCode.code"
struct Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(struct Source_Location* location, struct Parsed_Type* type) {
#line 1270 "bootstrap/stage0/ReCode.code"
    struct Parsed_Sizeof_Expression* expression = (struct Parsed_Sizeof_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SIZEOF, sizeof(struct Parsed_Sizeof_Expression), location);
#line 1271 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1272 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1280 "bootstrap/stage0/ReCode.code"
struct Parsed_String_Expression* Parsed_String_Expression__create(struct String_Token* literal) {
#line 1281 "bootstrap/stage0/ReCode.code"
    struct Parsed_String_Expression* expression = (struct Parsed_String_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__STRING, sizeof(struct Parsed_String_Expression), (struct Token*) literal);
#line 1282 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1283 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1290 "bootstrap/stage0/ReCode.code"
struct Parsed_Substract_Expression* Parsed_Substract_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1291 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Substract_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__SUBSTRACT, left_expression, right_expression);
}

#line 1299 "bootstrap/stage0/ReCode.code"
struct Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(struct Token* name) {
#line 1300 "bootstrap/stage0/ReCode.code"
    struct Parsed_Symbol_Expression* expression = (struct Parsed_Symbol_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SYMBOL, sizeof(struct Parsed_Symbol_Expression), name->location);
#line 1301 "bootstrap/stage0/ReCode.code"
    expression->name = name;
#line 1302 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1327 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 1328 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* statement = (struct Parsed_Statement*) malloc(kind_size);
#line 1329 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 1330 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 1331 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 1332 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1340 "bootstrap/stage0/ReCode.code"
struct Parsed_Named_Statement* Parsed_Named_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location, struct Token* name) {
#line 1341 "bootstrap/stage0/ReCode.code"
    struct Parsed_Named_Statement* statement = (struct Parsed_Named_Statement*) Parsed_Statement__create_kind(kind, kind_size, location);
#line 1342 "bootstrap/stage0/ReCode.code"
    statement->name = name;
#line 1343 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1352 "bootstrap/stage0/ReCode.code"
struct Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(struct Parsed_Expression* object_expression, struct Parsed_Expression* value_expression) {
#line 1353 "bootstrap/stage0/ReCode.code"
    struct Parsed_Assignment_Statement* statement = (struct Parsed_Assignment_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__ASSIGNMENT, sizeof(struct Parsed_Assignment_Statement), object_expression->location);
#line 1354 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 1355 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 1356 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1364 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parsed_Block_Statement__create(struct Source_Location* location, struct Parsed_Statements* statements) {
#line 1365 "bootstrap/stage0/ReCode.code"
    struct Parsed_Block_Statement* statement = (struct Parsed_Block_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__BLOCK, sizeof(struct Parsed_Block_Statement), location);
#line 1366 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1367 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1374 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Break_Statement__create(struct Source_Location* location) {
#line 1375 "bootstrap/stage0/ReCode.code"
    return Parsed_Statement__create_kind(Parsed_Statement_Kind__BREAK, sizeof(struct Parsed_Break_Statement), location);
}

#line 1383 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Member* Parsed_Enum_Member__create(struct Token* name) {
#line 1384 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Member* member = (struct Parsed_Enum_Member*) malloc(sizeof(struct Parsed_Enum_Member));
#line 1385 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1386 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1387 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 1395 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Statement* Parsed_Enum_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1396 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Statement* statement = (struct Parsed_Enum_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__ENUM, sizeof(struct Parsed_Enum_Statement), location, name);
#line 1397 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1398 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1406 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression_Statement* Parsed_Expression_Statement__create(struct Parsed_Expression* expression) {
#line 1407 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression_Statement* statement = (struct Parsed_Expression_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__EXPRESSION, sizeof(struct Parsed_Expression_Statement), expression->location);
#line 1408 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1409 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1418 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parsed_Function_Parameter__create(struct Token* name, struct Parsed_Type* type) {
#line 1419 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* parameter = (struct Parsed_Function_Parameter*) malloc(sizeof(struct Parsed_Function_Parameter));
#line 1420 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 1421 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 1422 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 1423 "bootstrap/stage0/ReCode.code"
    return parameter;
}

#line 1434 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Function_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* resturn_type, struct Parsed_Statements* statements, bool is_external) {
#line 1435 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Statement* statement = (struct Parsed_Function_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__FUNCTION, sizeof(struct Parsed_Function_Statement), location, name);
#line 1436 "bootstrap/stage0/ReCode.code"
    statement->first_parameter = first_parameter;
#line 1437 "bootstrap/stage0/ReCode.code"
    statement->return_type = resturn_type;
#line 1438 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1439 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1440 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1449 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Type_Parameter* Parsed_Function_Type_Parameter__create(struct Token* name, struct Parsed_Type* type) {
#line 1450 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Type_Parameter* parameter = (struct Parsed_Function_Type_Parameter*) malloc(sizeof(struct Parsed_Function_Type_Parameter));
#line 1451 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 1452 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 1453 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 1454 "bootstrap/stage0/ReCode.code"
    return parameter;
}

#line 1463 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Function_Type_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Type_Parameter* first_parameter, struct Parsed_Type* resturn_type) {
#line 1464 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Type_Statement* statement = (struct Parsed_Function_Type_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__FUNCTION_TYPE, sizeof(struct Parsed_Function_Type_Statement), location, name);
#line 1465 "bootstrap/stage0/ReCode.code"
    statement->first_parameter = first_parameter;
#line 1466 "bootstrap/stage0/ReCode.code"
    statement->return_type = resturn_type;
#line 1467 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1477 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_If_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* true_statement, struct Parsed_Statement* false_statement) {
#line 1478 "bootstrap/stage0/ReCode.code"
    struct Parsed_If_Statement* statement = (struct Parsed_If_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__IF, sizeof(struct Parsed_If_Statement), location);
#line 1479 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1480 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 1481 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 1482 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1489 "bootstrap/stage0/ReCode.code"
struct Parsed_Opaque_Type_Statement* Parsed_Opaque_Type_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1490 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Opaque_Type_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__OPAQUE_TYPE, sizeof(struct Parsed_Opaque_Type_Statement), location, name);
}

#line 1498 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Return_Statement__create(struct Source_Location* location, struct Parsed_Expression* expression) {
#line 1499 "bootstrap/stage0/ReCode.code"
    struct Parsed_Return_Statement* statement = (struct Parsed_Return_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__RETURN, sizeof(struct Parsed_Return_Statement), location);
#line 1500 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1501 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1510 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Member* Parsed_Struct_Member__create(struct Token* name, struct Parsed_Type* type) {
#line 1511 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Member* member = (struct Parsed_Struct_Member*) malloc(sizeof(struct Parsed_Struct_Member));
#line 1512 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1513 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 1514 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1515 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 1523 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Statement* Parsed_Struct_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1524 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Statement* statement = (struct Parsed_Struct_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__STRUCT, sizeof(struct Parsed_Struct_Statement), location, name);
#line 1525 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1526 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1536 "bootstrap/stage0/ReCode.code"
struct Parsed_Variable_Statement* Parsed_Variable_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Type* type, bool is_external) {
#line 1537 "bootstrap/stage0/ReCode.code"
    struct Parsed_Variable_Statement* statement = (struct Parsed_Variable_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__VARIABLE, sizeof(struct Parsed_Variable_Statement), location, name);
#line 1538 "bootstrap/stage0/ReCode.code"
    statement->type = type;
#line 1539 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1540 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1549 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_While_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* body_statement) {
#line 1550 "bootstrap/stage0/ReCode.code"
    struct Parsed_While_Statement* statement = (struct Parsed_While_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__WHILE, sizeof(struct Parsed_While_Statement), location);
#line 1551 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1552 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 1553 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1562 "bootstrap/stage0/ReCode.code"
struct Parsed_Statements* Parsed_Statements__create(bool has_globals) {
#line 1563 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statements* statements = (struct Parsed_Statements*) malloc(sizeof(struct Parsed_Statements));
#line 1564 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 1565 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 1566 "bootstrap/stage0/ReCode.code"
    statements->has_globals = has_globals;
#line 1567 "bootstrap/stage0/ReCode.code"
    return statements;
}

#line 1570 "bootstrap/stage0/ReCode.code"
void Parsed_Statements__append(struct Parsed_Statements* self, struct Parsed_Statement* statement) {
#line 1571 "bootstrap/stage0/ReCode.code"
    if (self->first_statement == NULL) {
#line 1572 "bootstrap/stage0/ReCode.code"
        self->first_statement = statement;
    } else {
#line 1574 "bootstrap/stage0/ReCode.code"
        self->last_statement->next_statement = statement;
    }
#line 1576 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;
}

#line 1579 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* Parsed_Compilation_Unit__create() {
#line 1580 "bootstrap/stage0/ReCode.code"
    struct Parsed_Source* compilation_unit = (struct Parsed_Source*) malloc(sizeof(struct Parsed_Source));
#line 1581 "bootstrap/stage0/ReCode.code"
    compilation_unit->statements = Parsed_Statements__create(true);
#line 1582 "bootstrap/stage0/ReCode.code"
    return compilation_unit;
}

#line 1595 "bootstrap/stage0/ReCode.code"
void Parser__error(struct Parser* self, struct String* message) {
#line 1596 "bootstrap/stage0/ReCode.code"
    Token__error(self->scanner->current_token, message);
}

#line 1599 "bootstrap/stage0/ReCode.code"
void Parser__warning(struct Parser* self, struct String* message) {
#line 1600 "bootstrap/stage0/ReCode.code"
    Token__warning(self->scanner->current_token, message);
}

#line 1603 "bootstrap/stage0/ReCode.code"
struct Token* Parser__peek_token(struct Parser* self, uint8_t offset) {
#line 1604 "bootstrap/stage0/ReCode.code"
    return Scanner__peek_token(self->scanner, offset);
}

#line 1609 "bootstrap/stage0/ReCode.code"
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self), bool second_required, bool (*third_is)(struct Token* self)) {
#line 1610 "bootstrap/stage0/ReCode.code"
    uint8_t peek_offset = (uint8_t) 0;
#line 1611 "bootstrap/stage0/ReCode.code"
    if (first_is(Parser__peek_token(self, peek_offset))) {
#line 1612 "bootstrap/stage0/ReCode.code"
        peek_offset = peek_offset + (uint8_t) 1;
    } else if (first_required) {
#line 1614 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 1616 "bootstrap/stage0/ReCode.code"
    if (second_is != NULL) {
#line 1617 "bootstrap/stage0/ReCode.code"
        if (second_is(Parser__peek_token(self, peek_offset))) {
#line 1618 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
        } else if (second_required) {
#line 1620 "bootstrap/stage0/ReCode.code"
            return false;
        }
    }
#line 1623 "bootstrap/stage0/ReCode.code"
    if (third_is != NULL) {
#line 1624 "bootstrap/stage0/ReCode.code"
        return third_is(Parser__peek_token(self, peek_offset));
    }
#line 1626 "bootstrap/stage0/ReCode.code"
    return true;
}

#line 1629 "bootstrap/stage0/ReCode.code"
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self)) {
#line 1630 "bootstrap/stage0/ReCode.code"
    return Parser__matches_three(self, first_is, first_required, second_is, true, NULL);
}

#line 1633 "bootstrap/stage0/ReCode.code"
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token* self)) {
#line 1634 "bootstrap/stage0/ReCode.code"
    return Parser__matches_two(self, first_is, true, NULL);
}

#line 1637 "bootstrap/stage0/ReCode.code"
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token* self)) {
#line 1638 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, check)) {
#line 1639 "bootstrap/stage0/ReCode.code"
        struct Token* token = self->scanner->current_token;
#line 1640 "bootstrap/stage0/ReCode.code"
        Scanner__next_token(self->scanner);
#line 1641 "bootstrap/stage0/ReCode.code"
        return token;
    }
#line 1643 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unexpected token"));
#line 1644 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 1647 "bootstrap/stage0/ReCode.code"
void Parser__consume_comment(struct Parser* self) {
#line 1648 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_comment);
}

#line 1651 "bootstrap/stage0/ReCode.code"
void Parser__consume_space(struct Parser* self, uint16_t count) {
#line 1652 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_space)) {
#line 1653 "bootstrap/stage0/ReCode.code"
        struct Space_Token* token = (struct Space_Token*) Parser__consume_token(self, Token__is_space);
#line 1654 "bootstrap/stage0/ReCode.code"
        if (token->count != count) {
#line 1655 "bootstrap/stage0/ReCode.code"
            struct String* message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), (int16_t) token->count), " spaces where "), (int16_t) count), " were expected");
#line 1656 "bootstrap/stage0/ReCode.code"
            Token__warning((struct Token*) token, message);
#line 1657 "bootstrap/stage0/ReCode.code"
            String__delete(message);
        }
    } else if (count > (uint16_t) 0) {
#line 1660 "bootstrap/stage0/ReCode.code"
        struct String* message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), (int16_t) 0), " spaces where "), (int16_t) count), " were expected");
#line 1661 "bootstrap/stage0/ReCode.code"
        Parser__warning(self, message);
#line 1662 "bootstrap/stage0/ReCode.code"
        String__delete(message);
    }
}

#line 1666 "bootstrap/stage0/ReCode.code"
void Parser__consume_end_of_line(struct Parser* self) {
#line 1667 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1668 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1669 "bootstrap/stage0/ReCode.code"
        Parser__consume_comment(self);
    } else {
#line 1671 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
    }
#line 1673 "bootstrap/stage0/ReCode.code"
    struct Token* token = Parser__consume_token(self, Token__is_end_of_line);
#line 1674 "bootstrap/stage0/ReCode.code"
    if (Token__is_end_of_file(token)) {
#line 1675 "bootstrap/stage0/ReCode.code"
        Token__warning(token, String__create_from("Unexpected end of file"));
    }
}

#line 1679 "bootstrap/stage0/ReCode.code"
bool Parser__consume_empty_line(struct Parser* self) {
#line 1680 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_end_of_file)) {
#line 1681 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 1683 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 1684 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1685 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 1686 "bootstrap/stage0/ReCode.code"
            Parser__consume_comment(self);
        } else {
#line 1688 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
        }
#line 1690 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_end_of_line);
#line 1691 "bootstrap/stage0/ReCode.code"
        return true;
    }
#line 1693 "bootstrap/stage0/ReCode.code"
    return false;
}

#line 1704 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_primary_expression(struct Parser* self) {
#line 1705 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_true)) {
#line 1706 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true);
    }
#line 1708 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_null)) {
#line 1709 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null));
    }
#line 1711 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_false)) {
#line 1712 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false);
    }
#line 1714 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_identifier)) {
#line 1715 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier));
    }
#line 1717 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_integer)) {
#line 1718 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Integer_Expression__create((struct Integer_Token*) Parser__consume_token(self, Token__is_integer));
    }
#line 1720 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_character)) {
#line 1721 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Character_Expression__create((struct Character_Token*) Parser__consume_token(self, Token__is_character));
    }
#line 1723 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_string)) {
#line 1724 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_String_Expression__create((struct String_Token*) Parser__consume_token(self, Token__is_string));
    }
#line 1726 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_opening_paren)) {
#line 1727 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1728 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1729 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_expression(self);
#line 1730 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1731 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_closing_paren);
#line 1732 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Group_Expression__create(location, expression);
    }
#line 1734 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unsupported primary expression"));
#line 1735 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 1740 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_access_expression(struct Parser* self) {
#line 1741 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_primary_expression(self);
#line 1742 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 1743 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* old_expression = expression;
#line 1744 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_dot) || Parser__matches_three(self, Token__is_space, false, Token__is_minus, true, Token__is_greater_than)) {
#line 1745 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1746 "bootstrap/stage0/ReCode.code"
            if (Parser__matches_one(self, Token__is_dot)) {
#line 1747 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_dot);
            } else {
#line 1749 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_minus);
#line 1750 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_greater_than);
            }
#line 1752 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1753 "bootstrap/stage0/ReCode.code"
            struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 1754 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Member_Access_Expression__create(expression, name);
        }
#line 1756 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
#line 1757 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1758 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_opening_paren);
#line 1759 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1760 "bootstrap/stage0/ReCode.code"
            struct Parsed_Call_Expression* call_expression = Parsed_Call_Expression__create(expression);
#line 1761 "bootstrap/stage0/ReCode.code"
            if (!Parser__matches_one(self, Token__is_closing_paren)) {
#line 1762 "bootstrap/stage0/ReCode.code"
                struct Parsed_Call_Argument* last_argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1763 "bootstrap/stage0/ReCode.code"
                call_expression->first_argument = last_argument;
#line 1764 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 0);
#line 1765 "bootstrap/stage0/ReCode.code"
                while (Parser__matches_one(self, Token__is_comma)) {
#line 1766 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_comma);
#line 1767 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, (uint16_t) 1);
#line 1768 "bootstrap/stage0/ReCode.code"
                    struct Parsed_Call_Argument* argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1769 "bootstrap/stage0/ReCode.code"
                    last_argument->next_argument = argument;
#line 1770 "bootstrap/stage0/ReCode.code"
                    last_argument = argument;
#line 1771 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, (uint16_t) 0);
                }
            }
#line 1774 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) call_expression;
#line 1775 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_closing_paren);
        }
#line 1777 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
#line 1778 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1779 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_opening_bracket);
#line 1780 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1781 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* index_expression = Parser__parse_expression(self);
#line 1782 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1783 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_closing_bracket);
#line 1784 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Array_Access_Expression__create(expression, index_expression);
        }
#line 1786 "bootstrap/stage0/ReCode.code"
        if (old_expression == expression) {
#line 1787 "bootstrap/stage0/ReCode.code"
            break;
        }
    }
#line 1790 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1800 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_unary_expression(struct Parser* self) {
#line 1801 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_minus)) {
#line 1802 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_minus)->location;
#line 1803 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1804 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1805 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Minus_Expression__create(location, expression);
    }
#line 1807 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_exclamation_mark)) {
#line 1808 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_exclamation_mark)->location;
#line 1809 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1810 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1811 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Not_Expression__create(location, expression);
    }
#line 1813 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_ampersand)) {
#line 1814 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_ampersand)->location;
#line 1815 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1816 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1817 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Address_Of_Expression__create(location, expression);
    }
#line 1819 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_three(self, Token__is_opening_paren, true, Token__is_space, false, Token__is_identifier)) {
#line 1820 "bootstrap/stage0/ReCode.code"
        uint8_t peek_offset = (uint8_t) 1;
#line 1821 "bootstrap/stage0/ReCode.code"
        if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1822 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
        }
#line 1824 "bootstrap/stage0/ReCode.code"
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
#line 1825 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
#line 1826 "bootstrap/stage0/ReCode.code"
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1827 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
            }
#line 1829 "bootstrap/stage0/ReCode.code"
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
#line 1830 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
#line 1831 "bootstrap/stage0/ReCode.code"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1832 "bootstrap/stage0/ReCode.code"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
            }
#line 1835 "bootstrap/stage0/ReCode.code"
            if (Token__is_closing_paren(Parser__peek_token(self, peek_offset))) {
#line 1836 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
#line 1837 "bootstrap/stage0/ReCode.code"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1838 "bootstrap/stage0/ReCode.code"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
#line 1840 "bootstrap/stage0/ReCode.code"
                struct Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1841 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 0);
#line 1842 "bootstrap/stage0/ReCode.code"
                struct Parsed_Type* type = Parser__parse_type(self);
#line 1843 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 0);
#line 1844 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 1845 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 1);
#line 1846 "bootstrap/stage0/ReCode.code"
                struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1847 "bootstrap/stage0/ReCode.code"
                return (struct Parsed_Expression*) Parsed_Cast_Expression__create(location, expression, type);
            }
        }
    }
#line 1851 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_sizeof)) {
#line 1852 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_sizeof)->location;
#line 1853 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1854 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_opening_paren);
#line 1855 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1856 "bootstrap/stage0/ReCode.code"
        struct Parsed_Type* type = Parser__parse_type(self);
#line 1857 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1858 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_closing_paren);
#line 1859 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Sizeof_Expression__create(location, type);
    }
#line 1861 "bootstrap/stage0/ReCode.code"
    return Parser__parse_access_expression(self);
}

#line 1864 "bootstrap/stage0/ReCode.code"
bool Token__is_mutliplication(struct Token* self) {
#line 1865 "bootstrap/stage0/ReCode.code"
    return Token__is_asterisk(self) || Token__is_slash(self) || Token__is_percent(self);
}

#line 1870 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_multiplication_expression(struct Parser* self) {
#line 1871 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1872 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
#line 1873 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1874 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1875 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_asterisk);
#line 1876 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1877 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1878 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Multiply_Expression__create(expression, right_expression);
        } else if (Parser__matches_one(self, Token__is_slash)) {
#line 1880 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_slash);
#line 1881 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1882 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1883 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Divide_Expression__create(expression, right_expression);
        } else {
#line 1885 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_percent);
#line 1886 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1887 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1888 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Modulo_Expression__create(expression, right_expression);
        }
    }
#line 1891 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1894 "bootstrap/stage0/ReCode.code"
bool Token__is_addition(struct Token* self) {
#line 1895 "bootstrap/stage0/ReCode.code"
    return Token__is_plus(self) || Token__is_minus(self);
}

#line 1900 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_addition_expression(struct Parser* self) {
#line 1901 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_multiplication_expression(self);
#line 1902 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
#line 1903 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1904 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_plus)) {
#line 1905 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_plus);
#line 1906 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1907 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
#line 1908 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Add_Expression__create(expression, right_expression);
        } else {
#line 1910 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_minus);
#line 1911 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1912 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
#line 1913 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Substract_Expression__create(expression, right_expression);
        }
    }
#line 1916 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1921 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_comparison_expression(struct Parser* self) {
#line 1922 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_addition_expression(self);
#line 1923 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
#line 1924 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1925 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_less_than);
#line 1926 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_equals)) {
#line 1927 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_equals);
#line 1928 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1929 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1930 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
#line 1932 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1933 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1934 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
#line 1937 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1938 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_greater_than);
#line 1939 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_equals)) {
#line 1940 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_equals);
#line 1941 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1942 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1943 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
#line 1945 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1946 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1947 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Greater_Expression__create(expression, right_expression);
        }
    }
#line 1950 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1955 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_equality_expression(struct Parser* self) {
#line 1956 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_comparison_expression(self);
#line 1957 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
#line 1958 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1959 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 1960 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 1961 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1962 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
#line 1963 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Equals_Expression__create(expression, right_expression);
    } else if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
#line 1965 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1966 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_exclamation_mark);
#line 1967 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 1968 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1969 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
#line 1970 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Not_Equals_Expression__create(expression, right_expression);
    }
#line 1972 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1977 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_and_expression(struct Parser* self) {
#line 1978 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_equality_expression(self);
#line 1979 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_ampersand, true, Token__is_ampersand)) {
#line 1980 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1981 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1982 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1983 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1984 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_equality_expression(self);
#line 1985 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Logic_And_Expression__create(expression, right_expression);
    }
#line 1987 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1992 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_or_expression(struct Parser* self) {
#line 1993 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_logic_and_expression(self);
#line 1994 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_vertical_bar, true, Token__is_vertical_bar)) {
#line 1995 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1996 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1997 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 1998 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1999 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_logic_and_expression(self);
#line 2000 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Logic_Or_Expression__create(expression, right_expression);
    }
#line 2002 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 2007 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_expression(struct Parser* self) {
#line 2008 "bootstrap/stage0/ReCode.code"
    return Parser__parse_logic_or_expression(self);
}

#line 2013 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_opaque_type(struct Parser* self, struct Token* name) {
#line 2014 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opaque);
#line 2015 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2016 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_type);
#line 2017 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) Parsed_Opaque_Type_Statement__create(name->location, name);
}

#line 2022 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_struct(struct Parser* self, struct Token* name) {
#line 2023 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_struct);
#line 2024 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2025 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2026 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2027 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Statement* struct_statement = Parsed_Struct_Statement__create(name->location, name);
#line 2028 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Member* last_member = NULL;
#line 2029 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2030 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 2033 "bootstrap/stage0/ReCode.code"
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2034 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2035 "bootstrap/stage0/ReCode.code"
        struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2036 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2037 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_colon);
#line 2038 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2039 "bootstrap/stage0/ReCode.code"
        struct Parsed_Type* type = Parser__parse_type(self);
#line 2040 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2041 "bootstrap/stage0/ReCode.code"
        struct Parsed_Struct_Member* member = Parsed_Struct_Member__create(name, type);
#line 2042 "bootstrap/stage0/ReCode.code"
        if (last_member == NULL) {
#line 2043 "bootstrap/stage0/ReCode.code"
            struct_statement->first_member = member;
#line 2044 "bootstrap/stage0/ReCode.code"
            last_member = member;
        } else {
#line 2046 "bootstrap/stage0/ReCode.code"
            last_member->next_member = member;
#line 2047 "bootstrap/stage0/ReCode.code"
            last_member = member;
        }
#line 2049 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2053 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2054 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2055 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2056 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) struct_statement;
}

#line 2061 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_enum(struct Parser* self, struct Token* name) {
#line 2062 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_enum);
#line 2063 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2064 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2065 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2066 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Statement* enum_statement = Parsed_Enum_Statement__create(name->location, name);
#line 2067 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Member* last_member = NULL;
#line 2068 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2069 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 2072 "bootstrap/stage0/ReCode.code"
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2073 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2074 "bootstrap/stage0/ReCode.code"
        struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2075 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2076 "bootstrap/stage0/ReCode.code"
        struct Parsed_Enum_Member* member = Parsed_Enum_Member__create(name);
#line 2077 "bootstrap/stage0/ReCode.code"
        if (last_member == NULL) {
#line 2078 "bootstrap/stage0/ReCode.code"
            enum_statement->first_member = member;
#line 2079 "bootstrap/stage0/ReCode.code"
            last_member = member;
        } else {
#line 2081 "bootstrap/stage0/ReCode.code"
            last_member->next_member = member;
#line 2082 "bootstrap/stage0/ReCode.code"
            last_member = member;
        }
#line 2084 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2088 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2089 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2090 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2091 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) enum_statement;
}

#line 2096 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parser__parse_type(struct Parser* self) {
#line 2097 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2098 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = Parsed_Named_Type__create(name);
#line 2099 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
#line 2100 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2101 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_asterisk);
#line 2102 "bootstrap/stage0/ReCode.code"
        type = Parsed_Pointer_Type__create(type);
    }
#line 2104 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2109 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_type_alias(struct Parser* self) {
#line 2110 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
#line 2111 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2112 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2113 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2114 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2115 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2116 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2117 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Type_Parameter* first_parameter = NULL;
#line 2118 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2119 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2120 "bootstrap/stage0/ReCode.code"
        struct Parsed_Type* parameter_type = Parser__parse_type(self);
#line 2121 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2122 "bootstrap/stage0/ReCode.code"
        struct Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
#line 2123 "bootstrap/stage0/ReCode.code"
        first_parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
#line 2124 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Type_Parameter* last_parameter = first_parameter;
#line 2125 "bootstrap/stage0/ReCode.code"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2126 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 2127 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_comma);
#line 2128 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2129 "bootstrap/stage0/ReCode.code"
            struct Parsed_Type* parameter_type = Parser__parse_type(self);
#line 2130 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2131 "bootstrap/stage0/ReCode.code"
            struct Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
#line 2132 "bootstrap/stage0/ReCode.code"
            struct Parsed_Function_Type_Parameter* parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
#line 2133 "bootstrap/stage0/ReCode.code"
            last_parameter->next_parameter = parameter;
#line 2134 "bootstrap/stage0/ReCode.code"
            last_parameter = parameter;
        }
    }
#line 2137 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2138 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2139 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Type_Statement__create(location, name, first_parameter, return_type);
}

#line 2144 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_variable(struct Parser* self) {
#line 2145 "bootstrap/stage0/ReCode.code"
    bool is_external;
#line 2146 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location;
#line 2147 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_external)) {
#line 2148 "bootstrap/stage0/ReCode.code"
        is_external = true;
#line 2149 "bootstrap/stage0/ReCode.code"
        location = Parser__consume_token(self, Token__is_external)->location;
#line 2150 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
    } else if (Parser__matches_one(self, Token__is_extern)) {
#line 2152 "bootstrap/stage0/ReCode.code"
        is_external = true;
#line 2153 "bootstrap/stage0/ReCode.code"
        location = Parser__consume_token(self, Token__is_extern)->location;
#line 2154 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
    } else {
#line 2156 "bootstrap/stage0/ReCode.code"
        is_external = false;
#line 2157 "bootstrap/stage0/ReCode.code"
        location = Parser__peek_token(self, (uint8_t) 0)->location;
    }
#line 2159 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = Parser__parse_type(self);
#line 2160 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2161 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2162 "bootstrap/stage0/ReCode.code"
    struct Parsed_Variable_Statement* variable_statement = Parsed_Variable_Statement__create(location, name, type, is_external);
#line 2163 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2164 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2165 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 2166 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2167 "bootstrap/stage0/ReCode.code"
        variable_statement->expression = Parser__parse_expression(self);
    }
#line 2169 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) variable_statement;
}

#line 2174 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self) {
#line 2175 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_opening_brace)->location;
#line 2176 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2177 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statements* statements = Parsed_Statements__create(false);
#line 2178 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2179 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2180 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2181 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2182 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2183 "bootstrap/stage0/ReCode.code"
    return Parsed_Block_Statement__create(location, statements);
}

#line 2188 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self) {
#line 2189 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2190 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2191 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_colon);
#line 2192 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2193 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = Parser__parse_type(self);
#line 2194 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Parameter__create(name, type);
}

#line 2199 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_function(struct Parser* self, struct Token* name) {
#line 2200 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2201 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2202 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2203 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* first_parameter = NULL;
#line 2204 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2205 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2206 "bootstrap/stage0/ReCode.code"
        first_parameter = Parser__parse_function_parameter(self);
#line 2207 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Parameter* last_parameter = first_parameter;
#line 2208 "bootstrap/stage0/ReCode.code"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2209 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 2210 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_comma);
#line 2211 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2212 "bootstrap/stage0/ReCode.code"
            last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2213 "bootstrap/stage0/ReCode.code"
            last_parameter = last_parameter->next_parameter;
        }
    }
#line 2216 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2217 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2218 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2219 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2220 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2221 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2222 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2223 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2224 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2225 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2226 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2227 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statements* statements = Parsed_Statements__create(false);
#line 2228 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2229 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2230 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2231 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2232 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2233 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, statements, false);
}

#line 2238 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_external_function(struct Parser* self, struct Token* name) {
#line 2239 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_external);
#line 2240 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2241 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2242 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2243 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2244 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* first_parameter = NULL;
#line 2245 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2246 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2247 "bootstrap/stage0/ReCode.code"
        first_parameter = Parser__parse_function_parameter(self);
#line 2248 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Parameter* last_parameter = first_parameter;
#line 2249 "bootstrap/stage0/ReCode.code"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2250 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 2251 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_comma);
#line 2252 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2253 "bootstrap/stage0/ReCode.code"
            last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2254 "bootstrap/stage0/ReCode.code"
            last_parameter = last_parameter->next_parameter;
        }
    }
#line 2257 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2258 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2259 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2260 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2261 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2262 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2263 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2264 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2265 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, NULL, true);
}

#line 2270 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_return_statement(struct Parser* self) {
#line 2271 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_return)->location;
#line 2272 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = NULL;
#line 2273 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 2274 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2275 "bootstrap/stage0/ReCode.code"
        expression = Parser__parse_expression(self);
    }
#line 2277 "bootstrap/stage0/ReCode.code"
    return Parsed_Return_Statement__create(location, expression);
}

#line 2282 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_break_statement(struct Parser* self) {
#line 2283 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_break)->location;
#line 2284 "bootstrap/stage0/ReCode.code"
    return Parsed_Break_Statement__create(location);
}

#line 2289 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_if_statement(struct Parser* self) {
#line 2290 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_if)->location;
#line 2291 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2292 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2293 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2294 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* condition_expression = Parser__parse_expression(self);
#line 2295 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2296 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2297 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2298 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* true_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
#line 2299 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* false_statement = NULL;
#line 2300 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
#line 2301 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2302 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_else);
#line 2303 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2304 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_if)) {
#line 2305 "bootstrap/stage0/ReCode.code"
            false_statement = Parser__parse_if_statement(self);
        } else {
#line 2307 "bootstrap/stage0/ReCode.code"
            false_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
        }
    }
#line 2310 "bootstrap/stage0/ReCode.code"
    return Parsed_If_Statement__create(location, condition_expression, true_statement, false_statement);
}

#line 2315 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_while_statement(struct Parser* self) {
#line 2316 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_while)->location;
#line 2317 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2318 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2319 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2320 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* condition_expression = Parser__parse_expression(self);
#line 2321 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2322 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2323 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2324 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* body_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
#line 2325 "bootstrap/stage0/ReCode.code"
    return Parsed_While_Statement__create(location, condition_expression, body_statement);
}

#line 2335 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_statement(struct Parser* self) {
#line 2336 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2338 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_if)) {
#line 2339 "bootstrap/stage0/ReCode.code"
        return Parser__parse_if_statement(self);
    }
#line 2341 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_while)) {
#line 2342 "bootstrap/stage0/ReCode.code"
        return Parser__parse_while_statement(self);
    }
#line 2344 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_return)) {
#line 2345 "bootstrap/stage0/ReCode.code"
        return Parser__parse_return_statement(self);
    }
#line 2347 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_break)) {
#line 2348 "bootstrap/stage0/ReCode.code"
        return Parser__parse_break_statement(self);
    }
#line 2351 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_define)) {
#line 2352 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_define);
#line 2353 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2354 "bootstrap/stage0/ReCode.code"
        struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2355 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2356 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 2357 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2358 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_func)) {
#line 2359 "bootstrap/stage0/ReCode.code"
            return Parser__parse_function(self, name);
        } else if (Parser__matches_one(self, Token__is_struct)) {
#line 2361 "bootstrap/stage0/ReCode.code"
            return Parser__parse_struct(self, name);
        } else if (Parser__matches_three(self, Token__is_opaque, true, Token__is_space, true, Token__is_type)) {
#line 2363 "bootstrap/stage0/ReCode.code"
            return Parser__parse_opaque_type(self, name);
        } else if (Parser__matches_one(self, Token__is_enum)) {
#line 2365 "bootstrap/stage0/ReCode.code"
            return Parser__parse_enum(self, name);
        } else if (Parser__matches_three(self, Token__is_external, true, Token__is_space, true, Token__is_func)) {
#line 2367 "bootstrap/stage0/ReCode.code"
            return Parser__parse_external_function(self, name);
        } else if (Parser__matches_three(self, Token__is_extern, true, Token__is_space, true, Token__is_func)) {
#line 2369 "bootstrap/stage0/ReCode.code"
            return Parser__parse_external_function(self, name);
        }
#line 2371 "bootstrap/stage0/ReCode.code"
        Parser__error(self, String__create_from("Unsupported define"));
#line 2372 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 2375 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_typedef)) {
#line 2376 "bootstrap/stage0/ReCode.code"
        return Parser__parse_type_alias(self);
    }
#line 2379 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_extern) || Parser__matches_one(self, Token__is_identifier)) {
#line 2380 "bootstrap/stage0/ReCode.code"
        uint8_t peek_offset = (uint8_t) 0;
#line 2381 "bootstrap/stage0/ReCode.code"
        if (Token__is_extern(Parser__peek_token(self, peek_offset))) {
#line 2382 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
#line 2383 "bootstrap/stage0/ReCode.code"
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2384 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
            }
        }
#line 2387 "bootstrap/stage0/ReCode.code"
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
#line 2388 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
#line 2389 "bootstrap/stage0/ReCode.code"
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2390 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
            }
#line 2392 "bootstrap/stage0/ReCode.code"
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
#line 2393 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
#line 2394 "bootstrap/stage0/ReCode.code"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2395 "bootstrap/stage0/ReCode.code"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
            }
#line 2398 "bootstrap/stage0/ReCode.code"
            if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
#line 2399 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
#line 2400 "bootstrap/stage0/ReCode.code"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 2401 "bootstrap/stage0/ReCode.code"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
#line 2403 "bootstrap/stage0/ReCode.code"
                return Parser__parse_variable(self);
            }
        }
    }
#line 2408 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expresion = Parser__parse_access_expression(self);
#line 2409 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2410 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2411 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 2412 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2413 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* value_expression = Parser__parse_expression(self);
#line 2414 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Statement*) Parsed_Assignment_Statement__create(expresion, value_expression);
    }
#line 2416 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) Parsed_Expression_Statement__create(expresion);
}

#line 2421 "bootstrap/stage0/ReCode.code"
void Parser__parse_statements(struct Parser* self, struct Parsed_Statements* statements) {
#line 2422 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 2423 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
#line 2427 "bootstrap/stage0/ReCode.code"
        if (statements->has_globals) {
#line 2428 "bootstrap/stage0/ReCode.code"
            if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 2429 "bootstrap/stage0/ReCode.code"
                return;
            }
        } else {
#line 2432 "bootstrap/stage0/ReCode.code"
            if (Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2433 "bootstrap/stage0/ReCode.code"
                return;
            }
        }
#line 2437 "bootstrap/stage0/ReCode.code"
        struct Parsed_Statement* statement = Parser__parse_statement(self);
#line 2439 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2441 "bootstrap/stage0/ReCode.code"
        Parsed_Statements__append(statements, statement);
    }
}

#line 2445 "bootstrap/stage0/ReCode.code"
void Parser__parse_source(struct Parser* self, struct Source* source) {
#line 2446 "bootstrap/stage0/ReCode.code"
    struct Scanner* other_scanner = self->scanner;
#line 2448 "bootstrap/stage0/ReCode.code"
    self->scanner = Scanner__create(source);
#line 2450 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, self->compilation_unit->statements);
#line 2452 "bootstrap/stage0/ReCode.code"
    struct Token* last_token = Parser__peek_token(self, (uint8_t) 0);
#line 2453 "bootstrap/stage0/ReCode.code"
    if (!Token__is_end_of_file(last_token)) {
#line 2454 "bootstrap/stage0/ReCode.code"
        Parser__error(self, String__create_from("Scanner didn\'t reach end of file"));
#line 2455 "bootstrap/stage0/ReCode.code"
        abort();
    } else if (last_token->location->column != (uint16_t) 1) {
#line 2457 "bootstrap/stage0/ReCode.code"
        Parser__warning(self, String__create_from("No new line at the end of file"));
    }
#line 2460 "bootstrap/stage0/ReCode.code"
    self->scanner = other_scanner;
}

#line 2463 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* parse(struct Source* source) {
#line 2464 "bootstrap/stage0/ReCode.code"
    struct Parser parser;
#line 2465 "bootstrap/stage0/ReCode.code"
    parser.scanner = NULL;
#line 2466 "bootstrap/stage0/ReCode.code"
    parser.compilation_unit = Parsed_Compilation_Unit__create();
#line 2467 "bootstrap/stage0/ReCode.code"
    parser.current_identation = (uint16_t) 0;
#line 2469 "bootstrap/stage0/ReCode.code"
    Parser__parse_source(&parser, source);
#line 2471 "bootstrap/stage0/ReCode.code"
    return parser.compilation_unit;
}

#line 2509 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checked_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 2510 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = (struct Checked_Type*) malloc(kind_size);
#line 2511 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 2512 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 2513 "bootstrap/stage0/ReCode.code"
    type->next_type = NULL;
#line 2514 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2517 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_same_type(struct Checked_Type* self, struct Checked_Type* other_type, struct Source_Location* location) {
#line 2518 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__POINTER && other_type->kind == Checked_Type_Kind__NULL) {
#line 2519 "bootstrap/stage0/ReCode.code"
        return;
    }
#line 2521 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__equals(self, other_type)) {
#line 2522 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create_from("Unexpected type. Got \"");
#line 2523 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, other_type);
#line 2524 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" instead of \"");
#line 2525 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, self);
#line 2526 "bootstrap/stage0/ReCode.code"
        String__append_char(message, '\"');
#line 2527 "bootstrap/stage0/ReCode.code"
        Source_Location__error(location, message);
#line 2528 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 2532 "bootstrap/stage0/ReCode.code"
bool Checked_Type__is_scalar_type(struct Checked_Type* self) {
#line 2533 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__CHAR) {
#line 2534 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I16) {
#line 2536 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I32) {
#line 2538 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I64) {
#line 2540 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I8) {
#line 2542 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U16) {
#line 2544 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U32) {
#line 2546 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U64) {
#line 2548 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U8) {
#line 2550 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__USIZE) {
#line 2552 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__ENUM) {
#line 2554 "bootstrap/stage0/ReCode.code"
        return true;
    }
#line 2556 "bootstrap/stage0/ReCode.code"
    return false;
}

#line 2559 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_scalar_type(struct Checked_Type* self, struct Source_Location* location) {
#line 2560 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__is_scalar_type(self)) {
#line 2561 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create_from("Type \"");
#line 2562 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, self);
#line 2563 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" is not a scalar type");
#line 2564 "bootstrap/stage0/ReCode.code"
        Source_Location__error(location, message);
#line 2565 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 2574 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checked_Named_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name) {
#line 2575 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* type = (struct Checked_Named_Type*) Checked_Type__create_kind(kind, kind_size, location);
#line 2576 "bootstrap/stage0/ReCode.code"
    type->name = name;
#line 2577 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2587 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Member__create(struct Source_Location* location, struct String* name) {
#line 2588 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* member = (struct Checked_Enum_Member*) malloc(sizeof(struct Checked_Enum_Member));
#line 2589 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2590 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2591 "bootstrap/stage0/ReCode.code"
    member->symbol = NULL;
#line 2592 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2593 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2601 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Type* Checked_Enum_Type__create(struct Source_Location* location, struct String* name) {
#line 2602 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Type* type = (struct Checked_Enum_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__ENUM, sizeof(struct Checked_Enum_Type), location, name);
#line 2603 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2604 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2607 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Type__find_member(struct Checked_Enum_Type* self, struct String* name) {
#line 2608 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* member = self->first_member;
#line 2609 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2610 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, member->name)) {
#line 2611 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 2613 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2615 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2625 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter* Checked_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2626 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* parameter = (struct Checked_Function_Parameter*) malloc(sizeof(struct Checked_Function_Parameter));
#line 2627 "bootstrap/stage0/ReCode.code"
    parameter->location = location;
#line 2628 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 2629 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 2630 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 2631 "bootstrap/stage0/ReCode.code"
    return parameter;
}

#line 2640 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct String* name, struct Checked_Type* return_type) {
#line 2641 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* type = (struct Checked_Function_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__FUNCTION, sizeof(struct Checked_Function_Type), location, name);
#line 2642 "bootstrap/stage0/ReCode.code"
    type->return_type = return_type;
#line 2643 "bootstrap/stage0/ReCode.code"
    type->first_parameter = NULL;
#line 2644 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2647 "bootstrap/stage0/ReCode.code"
bool Checked_Function_Type__equals(struct Checked_Function_Type* self, struct Checked_Type* other_type) {
#line 2648 "bootstrap/stage0/ReCode.code"
    if (other_type->kind != self->super.super.kind) {
#line 2649 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2651 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) other_type;
#line 2652 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__equals(self->return_type, function_type->return_type)) {
#line 2653 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2655 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* self_parameter = self->first_parameter;
#line 2656 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2657 "bootstrap/stage0/ReCode.code"
    while (self_parameter != NULL && function_parameter != NULL) {
#line 2658 "bootstrap/stage0/ReCode.code"
        if (!Checked_Type__equals(self_parameter->type, function_parameter->type)) {
#line 2659 "bootstrap/stage0/ReCode.code"
            return false;
        }
#line 2661 "bootstrap/stage0/ReCode.code"
        self_parameter = self_parameter->next_parameter;
#line 2662 "bootstrap/stage0/ReCode.code"
        function_parameter = function_parameter->next_parameter;
    }
#line 2664 "bootstrap/stage0/ReCode.code"
    if (self_parameter != NULL || function_parameter != NULL) {
#line 2665 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2667 "bootstrap/stage0/ReCode.code"
    return true;
}

#line 2674 "bootstrap/stage0/ReCode.code"
struct Checked_Opaque_Type* Checked_Opaque_Type__create(struct Source_Location* location, struct String* name) {
#line 2675 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Opaque_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__OPAQUE, sizeof(struct Checked_Opaque_Type), location, name);
}

#line 2683 "bootstrap/stage0/ReCode.code"
struct Checked_Pointer_Type* Checked_Pointer_Type__create(struct Source_Location* location, struct Checked_Type* other_type) {
#line 2684 "bootstrap/stage0/ReCode.code"
    struct Checked_Pointer_Type* type = (struct Checked_Pointer_Type*) Checked_Type__create_kind(Checked_Type_Kind__POINTER, sizeof(struct Checked_Pointer_Type), location);
#line 2685 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 2686 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2689 "bootstrap/stage0/ReCode.code"
bool Checked_Pointer_Type__equals(struct Checked_Pointer_Type* self, struct Checked_Type* other_type) {
#line 2690 "bootstrap/stage0/ReCode.code"
    if (other_type->kind != self->super.kind) {
#line 2691 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2693 "bootstrap/stage0/ReCode.code"
    return Checked_Type__equals(self->other_type, ((struct Checked_Pointer_Type*) other_type)->other_type);
}

#line 2701 "bootstrap/stage0/ReCode.code"
struct Checked_Defined_Type* Checked_Defined_Type__create(struct Checked_Named_Type* defined_type) {
#line 2702 "bootstrap/stage0/ReCode.code"
    struct Checked_Defined_Type* type = (struct Checked_Defined_Type*) Checked_Type__create_kind(Checked_Type_Kind__DEFINED, sizeof(struct Checked_Defined_Type), defined_type->super.location);
#line 2703 "bootstrap/stage0/ReCode.code"
    type->defined_type = defined_type;
#line 2704 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2714 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Member__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2715 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* member = (struct Checked_Struct_Member*) malloc(sizeof(struct Checked_Struct_Member));
#line 2716 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2717 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2718 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 2719 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2720 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2728 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Type* Checked_Struct_Type__create(struct Source_Location* location, struct String* name) {
#line 2729 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Type* type = (struct Checked_Struct_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__STRUCT, sizeof(struct Checked_Struct_Type), location, name);
#line 2730 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2731 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2734 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Type__find_member(struct Checked_Struct_Type* self, struct String* name) {
#line 2735 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* member = self->first_member;
#line 2736 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2737 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, member->name)) {
#line 2738 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 2740 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2742 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2745 "bootstrap/stage0/ReCode.code"
bool Checked_Struct_Type__equals(struct Checked_Struct_Type* self, struct Checked_Type* other_type) {
#line 2746 "bootstrap/stage0/ReCode.code"
    if (self->super.super.kind != other_type->kind) {
#line 2747 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2749 "bootstrap/stage0/ReCode.code"
    return String__equals_string(self->super.name, ((struct Checked_Struct_Type*) other_type)->super.name);
}

#line 2752 "bootstrap/stage0/ReCode.code"
bool Checked_Type__equals(struct Checked_Type* self, struct Checked_Type* other_type) {
#line 2753 "bootstrap/stage0/ReCode.code"
    if (self == other_type) {
#line 2754 "bootstrap/stage0/ReCode.code"
        return true;
    }
#line 2756 "bootstrap/stage0/ReCode.code"
    if (self->kind != other_type->kind) {
#line 2757 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2759 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__FUNCTION) {
#line 2760 "bootstrap/stage0/ReCode.code"
        return Checked_Function_Type__equals((struct Checked_Function_Type*) self, other_type);
    }
#line 2762 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__POINTER) {
#line 2763 "bootstrap/stage0/ReCode.code"
        return Checked_Pointer_Type__equals((struct Checked_Pointer_Type*) self, other_type);
    }
#line 2765 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__STRUCT) {
#line 2766 "bootstrap/stage0/ReCode.code"
        return Checked_Struct_Type__equals((struct Checked_Struct_Type*) self, other_type);
    }
#line 2768 "bootstrap/stage0/ReCode.code"
    Source_Location__error(self->location, String__create_from("Unsupported type"));
#line 2769 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 2772 "bootstrap/stage0/ReCode.code"
struct String* String__append_checked_type(struct String* self, struct Checked_Type* type) {
#line 2773 "bootstrap/stage0/ReCode.code"
    if (type->kind <= Checked_Type_Kind__NULL) {
#line 2774 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* named_type = (struct Checked_Named_Type*) type;
#line 2775 "bootstrap/stage0/ReCode.code"
        String__append_string(self, named_type->name);
    } else if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2777 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) type;
#line 2778 "bootstrap/stage0/ReCode.code"
        String__append_cstring(self, "struct ");
#line 2779 "bootstrap/stage0/ReCode.code"
        String__append_string(self, struct_type->super.name);
    } else if (type->kind == Checked_Type_Kind__FUNCTION) {
#line 2781 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) type;
#line 2782 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(self, function_type->return_type);
#line 2783 "bootstrap/stage0/ReCode.code"
        String__append_char(self, ' ');
#line 2784 "bootstrap/stage0/ReCode.code"
        String__append_string(self, function_type->super.name);
#line 2785 "bootstrap/stage0/ReCode.code"
        String__append_char(self, '(');
#line 2786 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2787 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL) {
#line 2788 "bootstrap/stage0/ReCode.code"
            String__append_checked_type(self, function_parameter->type);
#line 2789 "bootstrap/stage0/ReCode.code"
            String__append_char(self, ' ');
#line 2790 "bootstrap/stage0/ReCode.code"
            String__append_string(self, function_parameter->name);
#line 2791 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 2792 "bootstrap/stage0/ReCode.code"
            if (function_parameter != NULL) {
#line 2793 "bootstrap/stage0/ReCode.code"
                String__append_cstring(self, ", ");
            }
        }
#line 2796 "bootstrap/stage0/ReCode.code"
        String__append_char(self, ')');
    } else if (type->kind == Checked_Type_Kind__ENUM) {
#line 2798 "bootstrap/stage0/ReCode.code"
        struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) type;
#line 2799 "bootstrap/stage0/ReCode.code"
        String__append_cstring(self, "enum ");
#line 2800 "bootstrap/stage0/ReCode.code"
        String__append_string(self, enum_type->super.name);
    } else if (type->kind == Checked_Type_Kind__POINTER) {
#line 2802 "bootstrap/stage0/ReCode.code"
        struct Checked_Pointer_Type* pointer_type = (struct Checked_Pointer_Type*) type;
#line 2803 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(self, pointer_type->other_type);
#line 2804 "bootstrap/stage0/ReCode.code"
        String__append_char(self, '*');
    } else {
#line 2806 "bootstrap/stage0/ReCode.code"
        Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2807 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 2809 "bootstrap/stage0/ReCode.code"
    return self;
}

#line 2812 "bootstrap/stage0/ReCode.code"
void File__write_checked_function_parameter(struct File* self, struct Checked_Function_Parameter* parameter) {
#line 2813 "bootstrap/stage0/ReCode.code"
    if (parameter->type->kind == Checked_Type_Kind__POINTER && ((struct Checked_Pointer_Type*) parameter->type)->other_type->kind == Checked_Type_Kind__FUNCTION) {
#line 2814 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) ((struct Checked_Pointer_Type*) parameter->type)->other_type;
#line 2815 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, function_type->return_type);
#line 2816 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, " (*");
#line 2817 "bootstrap/stage0/ReCode.code"
        File__write_string(self, parameter->name);
#line 2818 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, ")(");
#line 2819 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2820 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL) {
#line 2821 "bootstrap/stage0/ReCode.code"
            File__write_checked_function_parameter(self, function_parameter);
#line 2822 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 2823 "bootstrap/stage0/ReCode.code"
            if (function_parameter != NULL) {
#line 2824 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, ", ");
            }
        }
#line 2827 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ')');
    } else {
#line 2829 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, parameter->type);
#line 2830 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ' ');
#line 2831 "bootstrap/stage0/ReCode.code"
        File__write_string(self, parameter->name);
    }
}

#line 2835 "bootstrap/stage0/ReCode.code"
void File__write_checked_type(struct File* self, struct Checked_Type* type) {
#line 2836 "bootstrap/stage0/ReCode.code"
    if (type == NULL) {
#line 2837 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "null");
    } else if (type->kind == Checked_Type_Kind__I16) {
#line 2839 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int16_t");
    } else if (type->kind == Checked_Type_Kind__I32) {
#line 2841 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int32_t");
    } else if (type->kind == Checked_Type_Kind__I64) {
#line 2843 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int64_t");
    } else if (type->kind == Checked_Type_Kind__I8) {
#line 2845 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int8_t");
    } else if (type->kind == Checked_Type_Kind__U16) {
#line 2847 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint16_t");
    } else if (type->kind == Checked_Type_Kind__U32) {
#line 2849 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint32_t");
    } else if (type->kind == Checked_Type_Kind__U64) {
#line 2851 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint64_t");
    } else if (type->kind == Checked_Type_Kind__U8) {
#line 2853 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint8_t");
    } else if (type->kind == Checked_Type_Kind__USIZE) {
#line 2855 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "size_t");
    } else if (type->kind <= Checked_Type_Kind__NULL) {
#line 2857 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* named_type = (struct Checked_Named_Type*) type;
#line 2858 "bootstrap/stage0/ReCode.code"
        File__write_string(self, named_type->name);
    } else if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2860 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) type;
#line 2861 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "struct ");
#line 2862 "bootstrap/stage0/ReCode.code"
        File__write_string(self, struct_type->super.name);
    } else if (type->kind == Checked_Type_Kind__OPAQUE) {
#line 2864 "bootstrap/stage0/ReCode.code"
        struct Checked_Opaque_Type* opaque_type = (struct Checked_Opaque_Type*) type;
#line 2865 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "struct ");
#line 2866 "bootstrap/stage0/ReCode.code"
        File__write_string(self, opaque_type->super.name);
    } else if (type->kind == Checked_Type_Kind__FUNCTION) {
#line 2868 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) type;
#line 2869 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, function_type->return_type);
#line 2870 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ' ');
#line 2871 "bootstrap/stage0/ReCode.code"
        File__write_string(self, function_type->super.name);
#line 2872 "bootstrap/stage0/ReCode.code"
        File__write_char(self, '(');
#line 2873 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2874 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL) {
#line 2875 "bootstrap/stage0/ReCode.code"
            File__write_checked_function_parameter(self, function_parameter);
#line 2876 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 2877 "bootstrap/stage0/ReCode.code"
            if (function_parameter != NULL) {
#line 2878 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, ", ");
            }
        }
#line 2881 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ')');
    } else if (type->kind == Checked_Type_Kind__ENUM) {
#line 2883 "bootstrap/stage0/ReCode.code"
        struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) type;
#line 2884 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "enum ");
#line 2885 "bootstrap/stage0/ReCode.code"
        File__write_string(self, enum_type->super.name);
    } else if (type->kind == Checked_Type_Kind__POINTER) {
#line 2887 "bootstrap/stage0/ReCode.code"
        struct Checked_Pointer_Type* pointer_type = (struct Checked_Pointer_Type*) type;
#line 2888 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, pointer_type->other_type);
#line 2889 "bootstrap/stage0/ReCode.code"
        File__write_char(self, '*');
    } else {
#line 2891 "bootstrap/stage0/ReCode.code"
        Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2892 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 2917 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbol__create_kind(enum Checked_Symbol_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2918 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = (struct Checked_Symbol*) malloc(kind_size);
#line 2919 "bootstrap/stage0/ReCode.code"
    symbol->kind = kind;
#line 2920 "bootstrap/stage0/ReCode.code"
    symbol->location = location;
#line 2921 "bootstrap/stage0/ReCode.code"
    symbol->name = name;
#line 2922 "bootstrap/stage0/ReCode.code"
    symbol->type = type;
#line 2923 "bootstrap/stage0/ReCode.code"
    symbol->prev_symbol = NULL;
#line 2924 "bootstrap/stage0/ReCode.code"
    symbol->next_symbol = NULL;
#line 2925 "bootstrap/stage0/ReCode.code"
    return symbol;
}

#line 2932 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member_Symbol* Checked_Enum_Member_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2933 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Enum_Member_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__ENUM_MEMBER, sizeof(struct Checked_Enum_Member_Symbol), location, name, type);
}

#line 2942 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Symbol* Checked_Function_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Function_Type* function_type) {
#line 2943 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Symbol* symbol = (struct Checked_Function_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION, sizeof(struct Checked_Function_Symbol), location, name, (struct Checked_Type*) Checked_Pointer_Type__create(function_type->super.super.location, (struct Checked_Type*) function_type));
#line 2944 "bootstrap/stage0/ReCode.code"
    symbol->function_type = function_type;
#line 2945 "bootstrap/stage0/ReCode.code"
    symbol->checked_statements = NULL;
#line 2946 "bootstrap/stage0/ReCode.code"
    return symbol;
}

#line 2953 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter_Symbol* Checked_Function_Parameter_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2954 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Function_Parameter_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION_PARAMETER, sizeof(struct Checked_Function_Parameter_Symbol), location, name, type);
}

#line 2962 "bootstrap/stage0/ReCode.code"
struct Checked_Type_Symbol* Checked_Type_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Named_Type* named_type) {
#line 2963 "bootstrap/stage0/ReCode.code"
    struct Checked_Type_Symbol* symbol = (struct Checked_Type_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__TYPE, sizeof(struct Checked_Type_Symbol), location, name, (struct Checked_Type*) Checked_Defined_Type__create(named_type));
#line 2964 "bootstrap/stage0/ReCode.code"
    symbol->named_type = named_type;
#line 2965 "bootstrap/stage0/ReCode.code"
    return symbol;
}

#line 2972 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Symbol* Checked_Variable__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2973 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Variable_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__VARIABLE, sizeof(struct Checked_Variable_Symbol), location, name, type);
}

#line 2982 "bootstrap/stage0/ReCode.code"
struct Checked_Symbols* Checked_Symbols__create(struct Checked_Symbols* parent) {
#line 2983 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbols* symbols = (struct Checked_Symbols*) malloc(sizeof(struct Checked_Symbols));
#line 2984 "bootstrap/stage0/ReCode.code"
    symbols->parent = parent;
#line 2985 "bootstrap/stage0/ReCode.code"
    symbols->first_symbol = NULL;
#line 2986 "bootstrap/stage0/ReCode.code"
    symbols->last_symbol = NULL;
#line 2987 "bootstrap/stage0/ReCode.code"
    return symbols;
}

#line 2990 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_sibling_symbol(struct Checked_Symbols* self, struct String* name) {
#line 2991 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = self->first_symbol;
#line 2992 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 2993 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, symbol->name)) {
#line 2994 "bootstrap/stage0/ReCode.code"
            return symbol;
        }
#line 2996 "bootstrap/stage0/ReCode.code"
        symbol = symbol->next_symbol;
    }
#line 2998 "bootstrap/stage0/ReCode.code"
    return NULL;
}

#line 3001 "bootstrap/stage0/ReCode.code"
void Checked_Symbols__append_symbol(struct Checked_Symbols* self, struct Checked_Symbol* symbol) {
#line 3002 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* other_symbol = Checked_Symbols__find_sibling_symbol(self, symbol->name);
#line 3003 "bootstrap/stage0/ReCode.code"
    if (other_symbol != NULL) {
#line 3004 "bootstrap/stage0/ReCode.code"
        Source_Location__error(symbol->location, String__append_source_location(String__create_from("Symbol declared first here: "), other_symbol->location));
#line 3005 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3008 "bootstrap/stage0/ReCode.code"
    if (self->last_symbol == NULL) {
#line 3009 "bootstrap/stage0/ReCode.code"
        self->first_symbol = symbol;
    } else {
#line 3011 "bootstrap/stage0/ReCode.code"
        self->last_symbol->next_symbol = symbol;
#line 3012 "bootstrap/stage0/ReCode.code"
        symbol->prev_symbol = self->last_symbol;
    }
#line 3014 "bootstrap/stage0/ReCode.code"
    self->last_symbol = symbol;
}

#line 3017 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_symbol(struct Checked_Symbols* self, struct String* name) {
#line 3018 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = self->last_symbol;
#line 3019 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 3020 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, symbol->name)) {
#line 3021 "bootstrap/stage0/ReCode.code"
            return symbol;
        }
#line 3023 "bootstrap/stage0/ReCode.code"
        symbol = symbol->prev_symbol;
    }
#line 3025 "bootstrap/stage0/ReCode.code"
    if (self->parent != NULL) {
#line 3026 "bootstrap/stage0/ReCode.code"
        return Checked_Symbols__find_symbol(self->parent, name);
    }
#line 3028 "bootstrap/stage0/ReCode.code"
    return NULL;
}

#line 3072 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checked_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type) {
#line 3073 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = (struct Checked_Expression*) malloc(kind_size);
#line 3074 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 3075 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 3076 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 3077 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3086 "bootstrap/stage0/ReCode.code"
struct Checked_Binary_Expression* Checked_Binary_Expression__create_kind(enum Checked_Expression_Kind kind, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3087 "bootstrap/stage0/ReCode.code"
    struct Checked_Binary_Expression* expression = (struct Checked_Binary_Expression*) Checked_Expression__create_kind(kind, sizeof(struct Checked_Binary_Expression), location, type);
#line 3088 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 3089 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 3090 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3098 "bootstrap/stage0/ReCode.code"
struct Checked_Unary_Expression* Checked_Unary_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3099 "bootstrap/stage0/ReCode.code"
    struct Checked_Unary_Expression* expression = (struct Checked_Unary_Expression*) Checked_Expression__create_kind(kind, kind_size, location, type);
#line 3100 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3101 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3108 "bootstrap/stage0/ReCode.code"
struct Checked_Add_Expression* Checked_Add_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3109 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Add_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__ADD, location, type, left_expression, right_expression);
}

#line 3116 "bootstrap/stage0/ReCode.code"
struct Checked_Address_Of_Expression* Checked_Address_Of_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3117 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Address_Of_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__ADDRESS_OF, sizeof(struct Checked_Address_Of_Expression), location, type, other_expression);
}

#line 3126 "bootstrap/stage0/ReCode.code"
struct Checked_Array_Access_Expression* Checked_Array_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* array_expression, struct Checked_Expression* index_expression) {
#line 3127 "bootstrap/stage0/ReCode.code"
    struct Checked_Array_Access_Expression* expression = (struct Checked_Array_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__ARRAY_ACCESS, sizeof(struct Checked_Array_Access_Expression), location, type);
#line 3128 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 3129 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 3130 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3138 "bootstrap/stage0/ReCode.code"
struct Checked_Bool_Expression* Checked_Bool_Expression__create(struct Source_Location* location, struct Checked_Type* type, bool value) {
#line 3139 "bootstrap/stage0/ReCode.code"
    struct Checked_Bool_Expression* expression = (struct Checked_Bool_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__BOOL, sizeof(struct Checked_Bool_Expression), location, type);
#line 3140 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3141 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3149 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Argument* Checked_Call_Argument__create(struct Checked_Expression* expression) {
#line 3150 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Argument* argument = (struct Checked_Call_Argument*) malloc(sizeof(struct Checked_Call_Argument));
#line 3151 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 3152 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 3153 "bootstrap/stage0/ReCode.code"
    return argument;
}

#line 3162 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Expression* Checked_Call_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* callee_expression, struct Checked_Call_Argument* first_argument) {
#line 3163 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Expression* expression = (struct Checked_Call_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CALL, sizeof(struct Checked_Call_Expression), location, type);
#line 3164 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 3165 "bootstrap/stage0/ReCode.code"
    expression->first_argument = first_argument;
#line 3166 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3174 "bootstrap/stage0/ReCode.code"
struct Checked_Cast_Expression* Checked_Cast_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3175 "bootstrap/stage0/ReCode.code"
    struct Checked_Cast_Expression* expression = (struct Checked_Cast_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CAST, sizeof(struct Checked_Cast_Expression), location, type);
#line 3176 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3177 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3185 "bootstrap/stage0/ReCode.code"
struct Checked_Character_Expression* Checked_Character_Expression__create(struct Source_Location* location, struct Checked_Type* type, char value) {
#line 3186 "bootstrap/stage0/ReCode.code"
    struct Checked_Character_Expression* expression = (struct Checked_Character_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CHARACTER, sizeof(struct Checked_Character_Expression), location, type);
#line 3187 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3188 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3195 "bootstrap/stage0/ReCode.code"
struct Checked_Divide_Expression* Checked_Divide_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3196 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Divide_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__DIVIDE, location, type, left_expression, right_expression);
}

#line 3203 "bootstrap/stage0/ReCode.code"
struct Checked_Equals_Expression* Checked_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3204 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__EQUALS, location, type, left_expression, right_expression);
}

#line 3211 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Expression* Checked_Greater_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3212 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Greater_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER, location, type, left_expression, right_expression);
}

#line 3219 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Or_Equals_Expression* Checked_Greater_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3220 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Greater_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER_OR_EQUALS, location, type, left_expression, right_expression);
}

#line 3228 "bootstrap/stage0/ReCode.code"
struct Checked_Group_Expression* Checked_Group_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3229 "bootstrap/stage0/ReCode.code"
    struct Checked_Group_Expression* expression = (struct Checked_Group_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__GROUP, sizeof(struct Checked_Group_Expression), location, type);
#line 3230 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3231 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3239 "bootstrap/stage0/ReCode.code"
struct Checked_Integer_Expression* Checked_Integer_Expression__create(struct Source_Location* location, struct Checked_Type* type, uint64_t value) {
#line 3240 "bootstrap/stage0/ReCode.code"
    struct Checked_Integer_Expression* expression = (struct Checked_Integer_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__INTEGER, sizeof(struct Checked_Integer_Expression), location, type);
#line 3241 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3242 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3249 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Expression* Checked_Less_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3250 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Less_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS, location, type, left_expression, right_expression);
}

#line 3257 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Or_Equals_Expression* Checked_Less_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3258 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Less_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS_OR_EQUALS, location, type, left_expression, right_expression);
}

#line 3265 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_And_Expression* Checked_Logic_And_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3266 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Logic_And_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_AND, location, type, left_expression, right_expression);
}

#line 3273 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_Or_Expression* Checked_Logic_Or_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3274 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Logic_Or_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_OR, location, type, left_expression, right_expression);
}

#line 3283 "bootstrap/stage0/ReCode.code"
struct Checked_Member_Access_Expression* Checked_Member_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* object_expression, struct Checked_Struct_Member* member) {
#line 3284 "bootstrap/stage0/ReCode.code"
    struct Checked_Member_Access_Expression* expression = (struct Checked_Member_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__MEMBER_ACCESS, sizeof(struct Checked_Member_Access_Expression), location, type);
#line 3285 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 3286 "bootstrap/stage0/ReCode.code"
    expression->member = member;
#line 3287 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3294 "bootstrap/stage0/ReCode.code"
struct Checked_Minus_Expression* Checked_Minus_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3295 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Minus_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__MINUS, sizeof(struct Checked_Minus_Expression), location, type, other_expression);
}

#line 3302 "bootstrap/stage0/ReCode.code"
struct Checked_Modulo_Expression* Checked_Modulo_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3303 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Modulo_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MODULO, location, type, left_expression, right_expression);
}

#line 3310 "bootstrap/stage0/ReCode.code"
struct Checked_Multiply_Expression* Checked_Multiply_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3311 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Multiply_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MULTIPLY, location, type, left_expression, right_expression);
}

#line 3318 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Expression* Checked_Not_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3319 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Not_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__NOT, sizeof(struct Checked_Not_Expression), location, type, other_expression);
}

#line 3326 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Equals_Expression* Checked_Not_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3327 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Not_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__NOT_EQUALS, location, type, left_expression, right_expression);
}

#line 3334 "bootstrap/stage0/ReCode.code"
struct Checked_Null_Expression* Checked_Null_Expression__create(struct Source_Location* location, struct Checked_Type* type) {
#line 3335 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Null_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__NULL, sizeof(struct Checked_Null_Expression), location, type);
}

#line 3343 "bootstrap/stage0/ReCode.code"
struct Checked_Sizeof_Expression* Checked_Sizeof_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Type* sized_type) {
#line 3344 "bootstrap/stage0/ReCode.code"
    struct Checked_Sizeof_Expression* expression = (struct Checked_Sizeof_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SIZEOF, sizeof(struct Checked_Sizeof_Expression), location, type);
#line 3345 "bootstrap/stage0/ReCode.code"
    expression->sized_type = sized_type;
#line 3346 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3354 "bootstrap/stage0/ReCode.code"
struct Checked_String_Expression* Checked_String_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct String* value) {
#line 3355 "bootstrap/stage0/ReCode.code"
    struct Checked_String_Expression* expression = (struct Checked_String_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__STRING, sizeof(struct Checked_String_Expression), location, type);
#line 3356 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3357 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3364 "bootstrap/stage0/ReCode.code"
struct Checked_Substract_Expression* Checked_Substract_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3365 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Substract_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__SUBSTRACT, location, type, left_expression, right_expression);
}

#line 3373 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol_Expression* Checked_Symbol_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Symbol* symbol) {
#line 3374 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol_Expression* expression = (struct Checked_Symbol_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SYMBOL, sizeof(struct Checked_Symbol_Expression), location, type);
#line 3375 "bootstrap/stage0/ReCode.code"
    expression->symbol = symbol;
#line 3376 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3400 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checked_Statement__create_kind(enum Checked_Statement_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 3401 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* statement = (struct Checked_Statement*) malloc(kind_size);
#line 3402 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 3403 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 3404 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 3405 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3414 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checked_Assignment_Statement__create(struct Source_Location* location, struct Checked_Expression* object_expression, struct Checked_Expression* value_expression) {
#line 3415 "bootstrap/stage0/ReCode.code"
    struct Checked_Assignment_Statement* statement = (struct Checked_Assignment_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__ASSIGNMENT, sizeof(struct Checked_Assignment_Statement), location);
#line 3416 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 3417 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 3418 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3426 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checked_Block_Statement__create(struct Source_Location* location, struct Checked_Statements* statements) {
#line 3427 "bootstrap/stage0/ReCode.code"
    struct Checked_Block_Statement* statement = (struct Checked_Block_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BLOCK, sizeof(struct Checked_Block_Statement), location);
#line 3428 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 3429 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3436 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checked_Break_Statement__create(struct Source_Location* location) {
#line 3437 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Break_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BREAK, sizeof(struct Checked_Break_Statement), location);
}

#line 3445 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checked_Expression_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) {
#line 3446 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression_Statement* statement = (struct Checked_Expression_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__EXPRESSION, sizeof(struct Checked_Expression_Statement), location);
#line 3447 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3448 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3458 "bootstrap/stage0/ReCode.code"
struct Checked_If_Statement* Checked_If_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* true_statement, struct Checked_Statement* false_statement) {
#line 3459 "bootstrap/stage0/ReCode.code"
    struct Checked_If_Statement* statement = (struct Checked_If_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__IF, sizeof(struct Checked_If_Statement), location);
#line 3460 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3461 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 3462 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 3463 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3471 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checked_Return_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) {
#line 3472 "bootstrap/stage0/ReCode.code"
    struct Checked_Return_Statement* statement = (struct Checked_Return_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__RETURN, sizeof(struct Checked_Return_Statement), location);
#line 3473 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3474 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3484 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checked_Variable_Statement__create(struct Source_Location* location, struct Checked_Variable_Symbol* variable, struct Checked_Expression* expression, bool is_external) {
#line 3485 "bootstrap/stage0/ReCode.code"
    struct Checked_Variable_Statement* statement = (struct Checked_Variable_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__VARIABLE, sizeof(struct Checked_Variable_Statement), location);
#line 3486 "bootstrap/stage0/ReCode.code"
    statement->variable = variable;
#line 3487 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3488 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 3489 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3498 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checked_While_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* body_statement) {
#line 3499 "bootstrap/stage0/ReCode.code"
    struct Checked_While_Statement* statement = (struct Checked_While_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__WHILE, sizeof(struct Checked_While_Statement), location);
#line 3500 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3501 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 3502 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3510 "bootstrap/stage0/ReCode.code"
struct Checked_Statements* Checked_Statements__create() {
#line 3511 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* statements = (struct Checked_Statements*) malloc(sizeof(struct Checked_Statements));
#line 3512 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 3513 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 3514 "bootstrap/stage0/ReCode.code"
    return statements;
}

#line 3517 "bootstrap/stage0/ReCode.code"
void Checked_Statements__append(struct Checked_Statements* self, struct Checked_Statement* statement) {
#line 3518 "bootstrap/stage0/ReCode.code"
    if (self->first_statement == NULL) {
#line 3519 "bootstrap/stage0/ReCode.code"
        self->first_statement = statement;
    } else {
#line 3521 "bootstrap/stage0/ReCode.code"
        self->last_statement->next_statement = statement;
    }
#line 3523 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;
}

#line 3547 "bootstrap/stage0/ReCode.code"
struct Checker* Checker__create() {
#line 3548 "bootstrap/stage0/ReCode.code"
    struct Checker* checker = (struct Checker*) malloc(sizeof(struct Checker));
#line 3549 "bootstrap/stage0/ReCode.code"
    checker->first_type = NULL;
#line 3550 "bootstrap/stage0/ReCode.code"
    checker->last_type = NULL;
#line 3551 "bootstrap/stage0/ReCode.code"
    checker->symbols = Checked_Symbols__create(NULL);
#line 3553 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Source_Location__create(NULL, (uint16_t) 0, (uint16_t) 1);
#line 3554 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__BOOL, sizeof(struct Checked_Named_Type), location, String__create_from("bool")));
#line 3555 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__CHAR, sizeof(struct Checked_Named_Type), location, String__create_from("char")));
#line 3556 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I16, sizeof(struct Checked_Named_Type), location, String__create_from("i16")));
#line 3557 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I32, sizeof(struct Checked_Named_Type), location, String__create_from("i32")));
#line 3558 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I64, sizeof(struct Checked_Named_Type), location, String__create_from("i64")));
#line 3559 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I8, sizeof(struct Checked_Named_Type), location, String__create_from("i8")));
#line 3560 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U16, sizeof(struct Checked_Named_Type), location, String__create_from("u16")));
#line 3561 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U32, sizeof(struct Checked_Named_Type), location, String__create_from("u32")));
#line 3562 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U64, sizeof(struct Checked_Named_Type), location, String__create_from("u64")));
#line 3563 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U8, sizeof(struct Checked_Named_Type), location, String__create_from("u8")));
#line 3564 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__USIZE, sizeof(struct Checked_Named_Type), location, String__create_from("usize")));
#line 3565 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__VOID, sizeof(struct Checked_Named_Type), location, String__create_from("void")));
#line 3566 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__NULL, sizeof(struct Checked_Named_Type), location, String__create_from("null")));
#line 3567 "bootstrap/stage0/ReCode.code"
    checker->last_builting_type = checker->last_type;
#line 3569 "bootstrap/stage0/ReCode.code"
    return checker;
}

#line 3572 "bootstrap/stage0/ReCode.code"
void Checker__append_type(struct Checker* self, struct Checked_Named_Type* type) {
#line 3573 "bootstrap/stage0/ReCode.code"
    if (self->first_type == NULL) {
#line 3574 "bootstrap/stage0/ReCode.code"
        self->first_type = type;
    } else {
#line 3576 "bootstrap/stage0/ReCode.code"
        self->last_type->super.next_type = (struct Checked_Type*) type;
    }
#line 3578 "bootstrap/stage0/ReCode.code"
    self->last_type = type;
#line 3580 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Type_Symbol__create(type->super.location, type->name, type));
}

#line 3583 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__find_type(struct Checker* self, struct String* name) {
#line 3584 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* type = self->first_type;
#line 3585 "bootstrap/stage0/ReCode.code"
    while (type != NULL) {
#line 3586 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, type->name)) {
#line 3587 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 3589 "bootstrap/stage0/ReCode.code"
        type = (struct Checked_Named_Type*) type->super.next_type;
    }
#line 3591 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 3594 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__get_builtin_type(struct Checker* self, enum Checked_Type_Kind kind) {
#line 3595 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* type = self->first_type;
#line 3596 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* custom_type = (struct Checked_Named_Type*) self->last_builting_type->super.next_type;
#line 3597 "bootstrap/stage0/ReCode.code"
    while (type != custom_type) {
#line 3598 "bootstrap/stage0/ReCode.code"
        if (type->super.kind == kind) {
#line 3599 "bootstrap/stage0/ReCode.code"
            return type;
        }
#line 3601 "bootstrap/stage0/ReCode.code"
        type = (struct Checked_Named_Type*) type->super.next_type;
    }
#line 3603 "bootstrap/stage0/ReCode.code"
    error(String__create_from("No such builtin type"));
#line 3604 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 3607 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checker__resolve_type(struct Checker* self, struct Parsed_Type* parsed_type) {
#line 3608 "bootstrap/stage0/ReCode.code"
    if (parsed_type->kind == Parsed_Type_Kind__NAMED) {
#line 3609 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* type = Checker__find_type(self, ((struct Parsed_Named_Type*) parsed_type)->name);
#line 3610 "bootstrap/stage0/ReCode.code"
        if (type != NULL) {
#line 3611 "bootstrap/stage0/ReCode.code"
            return (struct Checked_Type*) type;
        }
    }
#line 3614 "bootstrap/stage0/ReCode.code"
    if (parsed_type->kind == Parsed_Type_Kind__POINTER) {
#line 3615 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Type*) Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((struct Parsed_Pointer_Type*) parsed_type)->other_type));
    }
#line 3617 "bootstrap/stage0/ReCode.code"
    if (parsed_type->kind == Parsed_Type_Kind__STRUCT) {
#line 3618 "bootstrap/stage0/ReCode.code"
        struct Checked_Type* type = Checker__resolve_type(self, ((struct Parsed_Struct_Type*) parsed_type)->other_type);
#line 3619 "bootstrap/stage0/ReCode.code"
        if (type->kind != Checked_Type_Kind__STRUCT) {
#line 3620 "bootstrap/stage0/ReCode.code"
            TODO("Report unexpected type");
#line 3621 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 3623 "bootstrap/stage0/ReCode.code"
        return type;
    }
#line 3625 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_type->location, String__create_from("Undefined type"));
#line 3626 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 3629 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_add_expression(struct Checker* self, struct Parsed_Add_Expression* parsed_expression) {
#line 3630 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3631 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3632 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3633 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3634 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3637 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_address_of_expression(struct Checker* self, struct Parsed_Address_Of_Expression* parsed_expression) {
#line 3638 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3639 "bootstrap/stage0/ReCode.code"
    if (other_expression->kind != Checked_Expression_Kind__SYMBOL) {
#line 3640 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->super.super.location, String__create_from("Not a symbol"));
#line 3641 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3643 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
}

#line 3646 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_array_access_expression(struct Checker* self, struct Parsed_Array_Access_Expression* parsed_expression) {
#line 3647 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* array_expression = Checker__check_expression(self, parsed_expression->array_expression);
#line 3648 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* array_type = array_expression->type;
#line 3649 "bootstrap/stage0/ReCode.code"
    if (array_type->kind != Checked_Type_Kind__POINTER) {
#line 3650 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create();
#line 3651 "bootstrap/stage0/ReCode.code"
        String__append_char(message, '\"');
#line 3652 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, array_type);
#line 3653 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" is not a pointer type.");
#line 3654 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->array_expression->location, message);
#line 3655 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3657 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = ((struct Checked_Pointer_Type*) array_type)->other_type;
#line 3658 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* index_expression = Checker__check_expression(self, parsed_expression->index_expression);
#line 3659 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE), index_expression->type, index_expression->location);
#line 3660 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

#line 3663 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_bool_expression(struct Checker* self, struct Parsed_Bool_Expression* parsed_expression) {
#line 3664 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL);
#line 3665 "bootstrap/stage0/ReCode.code"
    bool value = parsed_expression->value;
#line 3666 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3669 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_call_expression(struct Checker* self, struct Parsed_Call_Expression* parsed_expression) {
#line 3670 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* callee_expression = Checker__check_expression(self, parsed_expression->callee_expression);
#line 3671 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* callee_type = callee_expression->type;
#line 3672 "bootstrap/stage0/ReCode.code"
    if (callee_type->kind != Checked_Type_Kind__POINTER || ((struct Checked_Pointer_Type*) callee_type)->other_type->kind != Checked_Type_Kind__FUNCTION) {
#line 3673 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->super.location, String__create_from("Not a function"));
#line 3674 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3676 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) ((struct Checked_Pointer_Type*) callee_type)->other_type;
#line 3677 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Argument* first_argument = NULL;
#line 3678 "bootstrap/stage0/ReCode.code"
    if (parsed_expression->first_argument != NULL) {
#line 3679 "bootstrap/stage0/ReCode.code"
        struct Checked_Call_Argument* last_argument = NULL;
#line 3680 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 3681 "bootstrap/stage0/ReCode.code"
        struct Parsed_Call_Argument* parsed_argument = parsed_expression->first_argument;
#line 3682 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL && parsed_argument != NULL) {
#line 3683 "bootstrap/stage0/ReCode.code"
            struct Checked_Expression* argument_expression = Checker__check_expression(self, parsed_argument->expression);
#line 3684 "bootstrap/stage0/ReCode.code"
            Checked_Type__expect_same_type(function_parameter->type, argument_expression->type, argument_expression->location);
#line 3685 "bootstrap/stage0/ReCode.code"
            struct Checked_Call_Argument* argument = Checked_Call_Argument__create(argument_expression);
#line 3686 "bootstrap/stage0/ReCode.code"
            if (last_argument == NULL) {
#line 3687 "bootstrap/stage0/ReCode.code"
                first_argument = argument;
            } else {
#line 3689 "bootstrap/stage0/ReCode.code"
                last_argument->next_argument = argument;
            }
#line 3691 "bootstrap/stage0/ReCode.code"
            last_argument = argument;
#line 3692 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 3693 "bootstrap/stage0/ReCode.code"
            parsed_argument = parsed_argument->next_argument;
        }
#line 3695 "bootstrap/stage0/ReCode.code"
        if (function_parameter != NULL) {
#line 3696 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too few arguments"));
#line 3697 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 3699 "bootstrap/stage0/ReCode.code"
        if (parsed_argument != NULL) {
#line 3700 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too many arguments"));
#line 3701 "bootstrap/stage0/ReCode.code"
            abort();
        }
    }
#line 3704 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Call_Expression__create(parsed_expression->super.location, function_type->return_type, callee_expression, first_argument);
}

#line 3707 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_cast_expression(struct Checker* self, struct Parsed_Cast_Expression* parsed_expression) {
#line 3708 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = Checker__resolve_type(self, parsed_expression->type);
#line 3709 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3710 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* other_type = other_expression->type;
#line 3711 "bootstrap/stage0/ReCode.code"
    bool can_cast = false;
#line 3712 "bootstrap/stage0/ReCode.code"
    if (type->kind == Checked_Type_Kind__POINTER) {
#line 3713 "bootstrap/stage0/ReCode.code"
        if (other_type->kind == Checked_Type_Kind__POINTER) {
#line 3714 "bootstrap/stage0/ReCode.code"
            can_cast = true;
        }
    } else if (Checked_Type__is_scalar_type(type)) {
#line 3717 "bootstrap/stage0/ReCode.code"
        if (Checked_Type__is_scalar_type(type)) {
#line 3718 "bootstrap/stage0/ReCode.code"
            can_cast = true;
        }
    }
#line 3721 "bootstrap/stage0/ReCode.code"
    if (Checked_Type__equals(type, other_type)) {
#line 3722 "bootstrap/stage0/ReCode.code"
        Source_Location__warning(parsed_expression->super.super.location, String__create_from("Redundant cast"));
    }
#line 3724 "bootstrap/stage0/ReCode.code"
    if (!can_cast) {
#line 3725 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create_from("Cannot cast \"");
#line 3726 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, other_expression->type);
#line 3727 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" to \"");
#line 3728 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, type);
#line 3729 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\".");
#line 3730 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->super.super.location, message);
#line 3731 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3733 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Cast_Expression__create(parsed_expression->super.super.location, type, other_expression);
}

#line 3736 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_character_expression(struct Checker* self, struct Parsed_Character_Expression* parsed_expression) {
#line 3737 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR);
#line 3738 "bootstrap/stage0/ReCode.code"
    char value = parsed_expression->value;
#line 3739 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3742 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_divide_expression(struct Checker* self, struct Parsed_Divide_Expression* parsed_expression) {
#line 3743 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3744 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3745 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3746 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3747 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3750 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_equals_expression(struct Checker* self, struct Parsed_Equals_Expression* parsed_expression) {
#line 3751 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3752 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3753 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3754 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3757 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_expression(struct Checker* self, struct Parsed_Greater_Expression* parsed_expression) {
#line 3758 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3759 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3760 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3761 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3762 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Greater_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3765 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_or_equals_expression(struct Checker* self, struct Parsed_Greater_Or_Equals_Expression* parsed_expression) {
#line 3766 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3767 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3768 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3769 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3770 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3773 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_group_expression(struct Checker* self, struct Parsed_Group_Expression* parsed_expression) {
#line 3774 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->other_expression);
#line 3775 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

#line 3778 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_integer_expression(struct Checker* self, struct Parsed_Integer_Expression* parsed_expression) {
#line 3779 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__I32);
#line 3780 "bootstrap/stage0/ReCode.code"
    uint64_t value = parsed_expression->value;
#line 3781 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3784 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_expression(struct Checker* self, struct Parsed_Less_Expression* parsed_expression) {
#line 3785 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3786 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3787 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3788 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3789 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Less_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3792 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_or_equals_expression(struct Checker* self, struct Parsed_Less_Or_Equals_Expression* parsed_expression) {
#line 3793 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3794 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3795 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3796 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3797 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3800 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_and_expression(struct Checker* self, struct Parsed_Logic_And_Expression* parsed_expression) {
#line 3801 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3802 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression->type, left_expression->location);
#line 3803 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3804 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3805 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3808 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_or_expression(struct Checker* self, struct Parsed_Logic_Or_Expression* parsed_expression) {
#line 3809 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3810 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression->type, left_expression->location);
#line 3811 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3812 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3813 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3816 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_member_access_expression(struct Checker* self, struct Parsed_Member_Access_Expression* parsed_expression) {
#line 3817 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* object_expression = Checker__check_expression(self, parsed_expression->object_expression);
#line 3818 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* object_type = object_expression->type;
#line 3819 "bootstrap/stage0/ReCode.code"
    if (object_type->kind == Checked_Type_Kind__POINTER) {
#line 3820 "bootstrap/stage0/ReCode.code"
        object_type = ((struct Checked_Pointer_Type*) object_type)->other_type;
#line 3821 "bootstrap/stage0/ReCode.code"
        if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3822 "bootstrap/stage0/ReCode.code"
            return Checker__check_struct_member_access_expression(self, object_expression, (struct Checked_Struct_Type*) object_type, parsed_expression->member_name);
        }
    } else if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3825 "bootstrap/stage0/ReCode.code"
        return Checker__check_struct_member_access_expression(self, object_expression, (struct Checked_Struct_Type*) object_type, parsed_expression->member_name);
    } else if (object_type->kind == Checked_Type_Kind__DEFINED) {
#line 3827 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* defined_type = ((struct Checked_Defined_Type*) object_type)->defined_type;
#line 3828 "bootstrap/stage0/ReCode.code"
        if (defined_type->super.kind == Checked_Type_Kind__ENUM) {
#line 3829 "bootstrap/stage0/ReCode.code"
            struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) defined_type;
#line 3830 "bootstrap/stage0/ReCode.code"
            struct Checked_Enum_Member* enum_member = Checked_Enum_Type__find_member(enum_type, parsed_expression->member_name->lexeme);
#line 3831 "bootstrap/stage0/ReCode.code"
            if (enum_member == NULL) {
#line 3832 "bootstrap/stage0/ReCode.code"
                Source_Location__error(object_expression->location, String__create_from("No such enum members"));
#line 3833 "bootstrap/stage0/ReCode.code"
                abort();
            }
#line 3835 "bootstrap/stage0/ReCode.code"
            return (struct Checked_Expression*) Checked_Symbol_Expression__create(object_expression->location, (struct Checked_Type*) enum_type, enum_member->symbol);
        }
#line 3837 "bootstrap/stage0/ReCode.code"
        Source_Location__error(object_expression->location, String__create_from("Type has no members"));
#line 3838 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3840 "bootstrap/stage0/ReCode.code"
    Source_Location__error(object_expression->location, String__create_from("Unsupported type"));
#line 3841 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 3844 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_struct_member_access_expression(struct Checker* self, struct Checked_Expression* object_expression, struct Checked_Struct_Type* struct_type, struct Token* member_name) {
#line 3845 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* member = Checked_Struct_Type__find_member(struct_type, member_name->lexeme);
#line 3846 "bootstrap/stage0/ReCode.code"
    if (member == NULL) {
#line 3847 "bootstrap/stage0/ReCode.code"
        Source_Location__error(object_expression->location, String__create_from("No such struct member"));
#line 3848 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3850 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Member_Access_Expression__create(object_expression->location, member->type, object_expression, member);
}

#line 3853 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_minus_expression(struct Checker* self, struct Parsed_Minus_Expression* parsed_expression) {
#line 3854 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3855 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* other_expression_type = other_expression->type;
#line 3856 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(other_expression_type, other_expression->location);
#line 3857 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

#line 3860 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_modulo_expression(struct Checker* self, struct Parsed_Modulo_Expression* parsed_expression) {
#line 3861 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3862 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3863 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3864 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3865 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3868 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_multiply_expression(struct Checker* self, struct Parsed_Multiply_Expression* parsed_expression) {
#line 3869 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3870 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3871 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3872 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3873 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3876 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_expression(struct Checker* self, struct Parsed_Not_Expression* parsed_expression) {
#line 3877 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3878 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* other_expression_type = other_expression->type;
#line 3879 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), other_expression_type, other_expression->location);
#line 3880 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

#line 3883 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_equals_expression(struct Checker* self, struct Parsed_Not_Equals_Expression* parsed_expression) {
#line 3884 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3885 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3886 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3887 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3890 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_null_expression(struct Checker* self, struct Parsed_Null_Expression* parsed_expression) {
#line 3891 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__NULL);
#line 3892 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

#line 3895 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_sizeof_expression(struct Checker* self, struct Parsed_Sizeof_Expression* parsed_expression) {
#line 3896 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE);
#line 3897 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* sized_type = Checker__resolve_type(self, parsed_expression->type);
#line 3898 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

#line 3901 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_string_expression(struct Checker* self, struct Parsed_String_Expression* parsed_expression) {
#line 3902 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* char_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR);
#line 3903 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type);
#line 3904 "bootstrap/stage0/ReCode.code"
    struct String* value = parsed_expression->value;
#line 3905 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3908 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_substract_expression(struct Checker* self, struct Parsed_Substract_Expression* parsed_expression) {
#line 3909 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3910 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3911 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3912 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3913 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3916 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_symbol_expression(struct Checker* self, struct Parsed_Symbol_Expression* parsed_expression) {
#line 3917 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = Checked_Symbols__find_symbol(self->symbols, parsed_expression->name->lexeme);
#line 3918 "bootstrap/stage0/ReCode.code"
    if (symbol == NULL) {
#line 3919 "bootstrap/stage0/ReCode.code"
        Token__error(parsed_expression->name, String__create_from("Undefined symbol"));
#line 3920 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3922 "bootstrap/stage0/ReCode.code"
    if (symbol->type == NULL) {
#line 3923 "bootstrap/stage0/ReCode.code"
        Token__error(parsed_expression->name, String__create_from("Symbol without type"));
#line 3924 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3926 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol);
}

#line 3929 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_expression(struct Checker* self, struct Parsed_Expression* parsed_expression) {
#line 3930 "bootstrap/stage0/ReCode.code"
    if (parsed_expression->kind == Parsed_Expression_Kind__ADD) {
#line 3931 "bootstrap/stage0/ReCode.code"
        return Checker__check_add_expression(self, (struct Parsed_Add_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__ADDRESS_OF) {
#line 3933 "bootstrap/stage0/ReCode.code"
        return Checker__check_address_of_expression(self, (struct Parsed_Address_Of_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__ARRAY_ACCESS) {
#line 3935 "bootstrap/stage0/ReCode.code"
        return Checker__check_array_access_expression(self, (struct Parsed_Array_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__BOOL) {
#line 3937 "bootstrap/stage0/ReCode.code"
        return Checker__check_bool_expression(self, (struct Parsed_Bool_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__CALL) {
#line 3939 "bootstrap/stage0/ReCode.code"
        return Checker__check_call_expression(self, (struct Parsed_Call_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__CAST) {
#line 3941 "bootstrap/stage0/ReCode.code"
        return Checker__check_cast_expression(self, (struct Parsed_Cast_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__CHARACTER) {
#line 3943 "bootstrap/stage0/ReCode.code"
        return Checker__check_character_expression(self, (struct Parsed_Character_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__DIVIDE) {
#line 3945 "bootstrap/stage0/ReCode.code"
        return Checker__check_divide_expression(self, (struct Parsed_Divide_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__EQUALS) {
#line 3947 "bootstrap/stage0/ReCode.code"
        return Checker__check_equals_expression(self, (struct Parsed_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__GREATER) {
#line 3949 "bootstrap/stage0/ReCode.code"
        return Checker__check_greater_expression(self, (struct Parsed_Greater_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__GREATER_OR_EQUALS) {
#line 3951 "bootstrap/stage0/ReCode.code"
        return Checker__check_greater_or_equals_expression(self, (struct Parsed_Greater_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 3953 "bootstrap/stage0/ReCode.code"
        return Checker__check_group_expression(self, (struct Parsed_Group_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__INTEGER) {
#line 3955 "bootstrap/stage0/ReCode.code"
        return Checker__check_integer_expression(self, (struct Parsed_Integer_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LESS) {
#line 3957 "bootstrap/stage0/ReCode.code"
        return Checker__check_less_expression(self, (struct Parsed_Less_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LESS_OR_EQUALS) {
#line 3959 "bootstrap/stage0/ReCode.code"
        return Checker__check_less_or_equals_expression(self, (struct Parsed_Less_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 3961 "bootstrap/stage0/ReCode.code"
        return Checker__check_logic_and_expression(self, (struct Parsed_Logic_And_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 3963 "bootstrap/stage0/ReCode.code"
        return Checker__check_logic_or_expression(self, (struct Parsed_Logic_Or_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MEMBER_ACCESS) {
#line 3965 "bootstrap/stage0/ReCode.code"
        return Checker__check_member_access_expression(self, (struct Parsed_Member_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MINUS) {
#line 3967 "bootstrap/stage0/ReCode.code"
        return Checker__check_minus_expression(self, (struct Parsed_Minus_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MODULO) {
#line 3969 "bootstrap/stage0/ReCode.code"
        return Checker__check_modulo_expression(self, (struct Parsed_Modulo_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MULTIPLY) {
#line 3971 "bootstrap/stage0/ReCode.code"
        return Checker__check_multiply_expression(self, (struct Parsed_Multiply_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__NOT) {
#line 3973 "bootstrap/stage0/ReCode.code"
        return Checker__check_not_expression(self, (struct Parsed_Not_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__NOT_EQUALS) {
#line 3975 "bootstrap/stage0/ReCode.code"
        return Checker__check_not_equals_expression(self, (struct Parsed_Not_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__NULL) {
#line 3977 "bootstrap/stage0/ReCode.code"
        return Checker__check_null_expression(self, (struct Parsed_Null_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__SIZEOF) {
#line 3979 "bootstrap/stage0/ReCode.code"
        return Checker__check_sizeof_expression(self, (struct Parsed_Sizeof_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__STRING) {
#line 3981 "bootstrap/stage0/ReCode.code"
        return Checker__check_string_expression(self, (struct Parsed_String_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__SUBSTRACT) {
#line 3983 "bootstrap/stage0/ReCode.code"
        return Checker__check_substract_expression(self, (struct Parsed_Substract_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__SYMBOL) {
#line 3985 "bootstrap/stage0/ReCode.code"
        return Checker__check_symbol_expression(self, (struct Parsed_Symbol_Expression*) parsed_expression);
    }
#line 3987 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_expression->location, String__create_from("Unsupported expression kind"));
#line 3988 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 3991 "bootstrap/stage0/ReCode.code"
void Checker__check_enum_statement(struct Checker* self, struct Parsed_Enum_Statement* parsed_statement) {
#line 3992 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Type* enum_type = Checked_Enum_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 3993 "bootstrap/stage0/ReCode.code"
    Checker__append_type(self, (struct Checked_Named_Type*) enum_type);
#line 3995 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* last_enum_member = NULL;
#line 3996 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Member* parsed_enum_member = parsed_statement->first_member;
#line 3997 "bootstrap/stage0/ReCode.code"
    while (parsed_enum_member != NULL) {
#line 3998 "bootstrap/stage0/ReCode.code"
        struct Checked_Enum_Member* enum_member = Checked_Enum_Member__create(parsed_enum_member->name->location, parsed_enum_member->name->lexeme);
#line 3999 "bootstrap/stage0/ReCode.code"
        struct String* enum_member_symbol_name = String__append_string(String__append_cstring(String__append_string(String__create(), enum_type->super.name), "__"), enum_member->name);
#line 4000 "bootstrap/stage0/ReCode.code"
        enum_member->symbol = (struct Checked_Symbol*) Checked_Enum_Member_Symbol__create(enum_member->location, enum_member_symbol_name, (struct Checked_Type*) enum_type);
#line 4001 "bootstrap/stage0/ReCode.code"
        Checked_Symbols__append_symbol(self->symbols, enum_member->symbol);
#line 4002 "bootstrap/stage0/ReCode.code"
        if (last_enum_member == NULL) {
#line 4003 "bootstrap/stage0/ReCode.code"
            enum_type->first_member = enum_member;
        } else {
#line 4005 "bootstrap/stage0/ReCode.code"
            last_enum_member->next_member = enum_member;
        }
#line 4007 "bootstrap/stage0/ReCode.code"
        last_enum_member = enum_member;
#line 4008 "bootstrap/stage0/ReCode.code"
        parsed_enum_member = parsed_enum_member->next_member;
    }
}

#line 4012 "bootstrap/stage0/ReCode.code"
void Checker__check_function_type_statement(struct Checker* self, struct Parsed_Function_Type_Statement* parsed_statement) {
#line 4013 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4014 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type;
#line 4015 "bootstrap/stage0/ReCode.code"
    if (other_type != NULL) {
#line 4016 "bootstrap/stage0/ReCode.code"
        TODO("Handle type redeclaration");
#line 4017 "bootstrap/stage0/ReCode.code"
        abort();
    } else {
#line 4019 "bootstrap/stage0/ReCode.code"
        struct Checked_Type* return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 4020 "bootstrap/stage0/ReCode.code"
        function_type = Checked_Function_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, return_type);
#line 4021 "bootstrap/stage0/ReCode.code"
        Checker__append_type(self, (struct Checked_Named_Type*) function_type);
    }
#line 4024 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->first_parameter != NULL) {
#line 4025 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* last_function_parameter = NULL;
#line 4026 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Type_Parameter* parsed_parameter = parsed_statement->first_parameter;
#line 4027 "bootstrap/stage0/ReCode.code"
        while (parsed_parameter != NULL) {
#line 4028 "bootstrap/stage0/ReCode.code"
            struct Checked_Type* function_parameter_type = Checker__resolve_type(self, parsed_parameter->type);
#line 4029 "bootstrap/stage0/ReCode.code"
            struct Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, function_parameter_type);
#line 4030 "bootstrap/stage0/ReCode.code"
            if (last_function_parameter == NULL) {
#line 4031 "bootstrap/stage0/ReCode.code"
                function_type->first_parameter = function_parameter;
            } else {
#line 4033 "bootstrap/stage0/ReCode.code"
                last_function_parameter->next_parameter = function_parameter;
            }
#line 4035 "bootstrap/stage0/ReCode.code"
            last_function_parameter = function_parameter;
#line 4036 "bootstrap/stage0/ReCode.code"
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
}

#line 4041 "bootstrap/stage0/ReCode.code"
void Checker__create_opaque_type(struct Checker* self, struct Parsed_Opaque_Type_Statement* parsed_statement) {
#line 4042 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4043 "bootstrap/stage0/ReCode.code"
    if (other_type != NULL) {
#line 4044 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4045 "bootstrap/stage0/ReCode.code"
        abort();
    } else {
#line 4047 "bootstrap/stage0/ReCode.code"
        struct Checked_Opaque_Type* opaque_type = Checked_Opaque_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4048 "bootstrap/stage0/ReCode.code"
        Checker__append_type(self, (struct Checked_Named_Type*) opaque_type);
    }
}

#line 4052 "bootstrap/stage0/ReCode.code"
void Checker__create_struct_type(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) {
#line 4053 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4054 "bootstrap/stage0/ReCode.code"
    if (other_type != NULL) {
#line 4055 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4056 "bootstrap/stage0/ReCode.code"
        abort();
    } else {
#line 4058 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Type* struct_type = Checked_Struct_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4059 "bootstrap/stage0/ReCode.code"
        Checker__append_type(self, (struct Checked_Named_Type*) struct_type);
    }
}

#line 4063 "bootstrap/stage0/ReCode.code"
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) {
#line 4064 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4065 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->first_member != NULL) {
#line 4066 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Member* last_struct_member = NULL;
#line 4067 "bootstrap/stage0/ReCode.code"
        struct Parsed_Struct_Member* parsed_member = parsed_statement->first_member;
#line 4068 "bootstrap/stage0/ReCode.code"
        while (parsed_member != NULL) {
#line 4069 "bootstrap/stage0/ReCode.code"
            struct Checked_Struct_Member* struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
#line 4070 "bootstrap/stage0/ReCode.code"
            if (struct_member != NULL) {
#line 4071 "bootstrap/stage0/ReCode.code"
                TODO("Handle struct member duplicate");
#line 4072 "bootstrap/stage0/ReCode.code"
                abort();
            }
#line 4074 "bootstrap/stage0/ReCode.code"
            struct Checked_Type* struct_member_type = Checker__resolve_type(self, parsed_member->type);
#line 4075 "bootstrap/stage0/ReCode.code"
            struct_member = Checked_Struct_Member__create(parsed_member->name->location, parsed_member->name->lexeme, struct_member_type);
#line 4076 "bootstrap/stage0/ReCode.code"
            if (last_struct_member == NULL) {
#line 4077 "bootstrap/stage0/ReCode.code"
                struct_type->first_member = struct_member;
            } else {
#line 4079 "bootstrap/stage0/ReCode.code"
                last_struct_member->next_member = struct_member;
            }
#line 4081 "bootstrap/stage0/ReCode.code"
            last_struct_member = struct_member;
#line 4082 "bootstrap/stage0/ReCode.code"
            parsed_member = parsed_member->next_member;
        }
    }
}

#line 4087 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement) {
#line 4088 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* object_expression = Checker__check_expression(self, parsed_statement->object_expression);
#line 4089 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* value_expression = Checker__check_expression(self, parsed_statement->value_expression);
#line 4090 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(object_expression->type, value_expression->type, value_expression->location);
#line 4091 "bootstrap/stage0/ReCode.code"
    return Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);
}

#line 4094 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement) {
#line 4095 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* statements = Checker__check_statements(self, parsed_statement->statements);
#line 4096 "bootstrap/stage0/ReCode.code"
    return Checked_Block_Statement__create(parsed_statement->super.location, statements);
}

#line 4099 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement) {
#line 4100 "bootstrap/stage0/ReCode.code"
    return Checked_Break_Statement__create(parsed_statement->super.location);
}

#line 4103 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement) {
#line 4104 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = Checker__check_expression(self, parsed_statement->expression);
#line 4105 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__equals((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__VOID), expression->type)) {
    }
#line 4108 "bootstrap/stage0/ReCode.code"
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

#line 4111 "bootstrap/stage0/ReCode.code"
struct Checked_If_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement) {
#line 4112 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4113 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), considition_expression->type, considition_expression->location);
#line 4114 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* true_statement = Checker__check_statement(self, parsed_statement->true_statement);
#line 4115 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* false_statement = NULL;
#line 4116 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->false_statement != NULL) {
#line 4117 "bootstrap/stage0/ReCode.code"
        false_statement = Checker__check_statement(self, parsed_statement->false_statement);
    }
#line 4119 "bootstrap/stage0/ReCode.code"
    return Checked_If_Statement__create(parsed_statement->super.location, considition_expression, true_statement, false_statement);
}

#line 4122 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement) {
#line 4123 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = NULL;
#line 4124 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->expression != NULL) {
#line 4125 "bootstrap/stage0/ReCode.code"
        expression = Checker__check_expression(self, parsed_statement->expression);
#line 4126 "bootstrap/stage0/ReCode.code"
        Checked_Type__expect_same_type(self->return_type, expression->type, expression->location);
    } else if (self->return_type->kind != Checked_Type_Kind__VOID) {
#line 4128 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_statement->super.location, String__create_from("Missing expression"));
#line 4129 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 4131 "bootstrap/stage0/ReCode.code"
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);
}

#line 4134 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement) {
#line 4135 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = Checker__resolve_type(self, parsed_statement->type);
#line 4136 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = NULL;
#line 4137 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->expression != NULL) {
#line 4138 "bootstrap/stage0/ReCode.code"
        expression = Checker__check_expression(self, parsed_statement->expression);
#line 4139 "bootstrap/stage0/ReCode.code"
        Checked_Type__expect_same_type(type, expression->type, expression->location);
    }
#line 4141 "bootstrap/stage0/ReCode.code"
    struct Checked_Variable_Symbol* variable = Checked_Variable__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
#line 4142 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) variable);
#line 4143 "bootstrap/stage0/ReCode.code"
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);
}

#line 4146 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement) {
#line 4147 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4148 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), considition_expression->type, considition_expression->location);
#line 4149 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* body_statement = Checker__check_statement(self, parsed_statement->body_statement);
#line 4150 "bootstrap/stage0/ReCode.code"
    return Checked_While_Statement__create(parsed_statement->super.location, considition_expression, body_statement);
}

#line 4153 "bootstrap/stage0/ReCode.code"
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) {
#line 4154 "bootstrap/stage0/ReCode.code"
    struct String* function_name = parsed_statement->super.name->lexeme;
#line 4155 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 4156 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* function_first_parameter = NULL;
#line 4157 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* parsed_parameter = parsed_statement->first_parameter;
#line 4158 "bootstrap/stage0/ReCode.code"
    if (parsed_parameter != NULL) {
#line 4159 "bootstrap/stage0/ReCode.code"
        function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
#line 4160 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_last_parameter = function_first_parameter;
#line 4161 "bootstrap/stage0/ReCode.code"
        parsed_parameter = parsed_parameter->next_parameter;
#line 4162 "bootstrap/stage0/ReCode.code"
        while (parsed_parameter != NULL) {
#line 4163 "bootstrap/stage0/ReCode.code"
            struct Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
#line 4164 "bootstrap/stage0/ReCode.code"
            function_last_parameter->next_parameter = function_parameter;
#line 4165 "bootstrap/stage0/ReCode.code"
            function_last_parameter = function_parameter;
#line 4166 "bootstrap/stage0/ReCode.code"
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
#line 4169 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_name, function_return_type);
#line 4170 "bootstrap/stage0/ReCode.code"
    function_type->first_parameter = function_first_parameter;
#line 4172 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* other_symbol = Checked_Symbols__find_sibling_symbol(self->symbols, function_name);
#line 4173 "bootstrap/stage0/ReCode.code"
    if (other_symbol != NULL) {
#line 4174 "bootstrap/stage0/ReCode.code"
        if (other_symbol->kind != Checked_Symbol_Kind__FUNCTION || !Checked_Type__equals((struct Checked_Type*) function_type, (struct Checked_Type*) ((struct Checked_Function_Symbol*) other_symbol)->function_type)) {
#line 4175 "bootstrap/stage0/ReCode.code"
            TODO("Report overloaded function");
#line 4176 "bootstrap/stage0/ReCode.code"
            abort();
        } else {
#line 4178 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Function declared first here: "), other_symbol->location));
#line 4179 "bootstrap/stage0/ReCode.code"
            abort();
        }
    } else {
#line 4182 "bootstrap/stage0/ReCode.code"
        Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Function_Symbol__create(parsed_statement->super.name->location, function_name, function_type));
    }
}

#line 4186 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement) {
#line 4187 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->kind == Parsed_Statement_Kind__ASSIGNMENT) {
#line 4188 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_assignment_statement(self, (struct Parsed_Assignment_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__BLOCK) {
#line 4190 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_block_statement(self, (struct Parsed_Block_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__BREAK) {
#line 4192 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_break_statement(self, (struct Parsed_Break_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__EXPRESSION) {
#line 4194 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_expression_statement(self, (struct Parsed_Expression_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__IF) {
#line 4196 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_if_statement(self, (struct Parsed_If_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__RETURN) {
#line 4198 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_return_statement(self, (struct Parsed_Return_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4200 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_variable_statement(self, (struct Parsed_Variable_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__WHILE) {
#line 4202 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_while_statement(self, (struct Parsed_While_Statement*) parsed_statement);
    }
#line 4204 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4205 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 4208 "bootstrap/stage0/ReCode.code"
struct Checked_Statements* Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements) {
#line 4210 "bootstrap/stage0/ReCode.code"
    self->symbols = Checked_Symbols__create(self->symbols);
#line 4212 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* checked_statements = Checked_Statements__create();
#line 4213 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* parsed_statement = parsed_statements->first_statement;
#line 4214 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4215 "bootstrap/stage0/ReCode.code"
        struct Checked_Statement* checked_statement = Checker__check_statement(self, parsed_statement);
#line 4216 "bootstrap/stage0/ReCode.code"
        Checked_Statements__append(checked_statements, checked_statement);
#line 4217 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4221 "bootstrap/stage0/ReCode.code"
    self->symbols = self->symbols->parent;
#line 4223 "bootstrap/stage0/ReCode.code"
    return checked_statements;
}

#line 4226 "bootstrap/stage0/ReCode.code"
void Checker__check_function_definition(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) {
#line 4227 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = Checked_Symbols__find_sibling_symbol(self->symbols, parsed_statement->super.name->lexeme);
#line 4228 "bootstrap/stage0/ReCode.code"
    if (symbol == NULL || symbol->kind != Checked_Symbol_Kind__FUNCTION) {
#line 4229 "bootstrap/stage0/ReCode.code"
        TODO("Report missing function symbol");
#line 4230 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 4232 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Symbol* function_symbol = (struct Checked_Function_Symbol*) symbol;
#line 4233 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = function_symbol->function_type;
#line 4234 "bootstrap/stage0/ReCode.code"
    self->return_type = function_type->return_type;
#line 4237 "bootstrap/stage0/ReCode.code"
    self->symbols = Checked_Symbols__create(self->symbols);
#line 4239 "bootstrap/stage0/ReCode.code"
    if (function_type->first_parameter != NULL) {
#line 4241 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* parameter = function_type->first_parameter;
#line 4242 "bootstrap/stage0/ReCode.code"
        while (parameter != NULL) {
#line 4243 "bootstrap/stage0/ReCode.code"
            Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Function_Parameter_Symbol__create(parameter->location, parameter->name, parameter->type));
#line 4244 "bootstrap/stage0/ReCode.code"
            parameter = parameter->next_parameter;
        }
    }
#line 4249 "bootstrap/stage0/ReCode.code"
    function_symbol->checked_statements = Checker__check_statements(self, parsed_statement->statements);
#line 4252 "bootstrap/stage0/ReCode.code"
    self->symbols = self->symbols->parent;
}

#line 4255 "bootstrap/stage0/ReCode.code"
struct Checked_Source* Checker__check_source(struct Checker* self, struct Parsed_Source* parsed_source) {
#line 4256 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* checked_statements = Checked_Statements__create();
#line 4258 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* parsed_statement;
#line 4261 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4262 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4263 "bootstrap/stage0/ReCode.code"
        struct Checked_Statement* checked_statement = NULL;
#line 4264 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4269 "bootstrap/stage0/ReCode.code"
            Checker__create_struct_type(self, (struct Parsed_Struct_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4271 "bootstrap/stage0/ReCode.code"
            Checker__create_opaque_type(self, (struct Parsed_Opaque_Type_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4273 "bootstrap/stage0/ReCode.code"
            Checker__check_enum_statement(self, (struct Parsed_Enum_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
        } else {
#line 4277 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4278 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4280 "bootstrap/stage0/ReCode.code"
        if (checked_statement != NULL) {
#line 4281 "bootstrap/stage0/ReCode.code"
            Checked_Statements__append(checked_statements, checked_statement);
        }
#line 4283 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4287 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4288 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4289 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4290 "bootstrap/stage0/ReCode.code"
            Checker__check_struct_statement(self, (struct Parsed_Struct_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
#line 4292 "bootstrap/stage0/ReCode.code"
            Checker__check_function_type_statement(self, (struct Parsed_Function_Type_Statement*) parsed_statement);
        }
#line 4294 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4298 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4299 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4300 "bootstrap/stage0/ReCode.code"
        struct Checked_Statement* checked_statement = NULL;
#line 4301 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4302 "bootstrap/stage0/ReCode.code"
            Checker__check_function_declaration(self, (struct Parsed_Function_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4304 "bootstrap/stage0/ReCode.code"
            checked_statement = (struct Checked_Statement*) Checker__check_variable_statement(self, (struct Parsed_Variable_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
        } else {
#line 4314 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4315 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4317 "bootstrap/stage0/ReCode.code"
        if (checked_statement != NULL) {
#line 4318 "bootstrap/stage0/ReCode.code"
            Checked_Statements__append(checked_statements, checked_statement);
        }
#line 4320 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4324 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4325 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4326 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4327 "bootstrap/stage0/ReCode.code"
            struct Parsed_Function_Statement* function_statement = (struct Parsed_Function_Statement*) parsed_statement;
#line 4328 "bootstrap/stage0/ReCode.code"
            if (function_statement->statements != NULL) {
#line 4329 "bootstrap/stage0/ReCode.code"
                Checker__check_function_definition(self, function_statement);
            }
        } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
        } else {
#line 4342 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4343 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4345 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4348 "bootstrap/stage0/ReCode.code"
    struct Checked_Source* checked_source = (struct Checked_Source*) malloc(sizeof(struct Checked_Source));
#line 4349 "bootstrap/stage0/ReCode.code"
    checked_source->first_symbol = self->symbols->first_symbol;
#line 4350 "bootstrap/stage0/ReCode.code"
    checked_source->statements = checked_statements;
#line 4351 "bootstrap/stage0/ReCode.code"
    return checked_source;
}

#line 4354 "bootstrap/stage0/ReCode.code"
struct Checked_Source* check(struct Parsed_Source* parsed_source) {
#line 4355 "bootstrap/stage0/ReCode.code"
    struct Checker* type_checker = Checker__create();
#line 4357 "bootstrap/stage0/ReCode.code"
    return Checker__check_source(type_checker, parsed_source);
}

#line 4369 "bootstrap/stage0/ReCode.code"
void Generator__write_source_location(struct Generator* self, struct Source_Location* location) {
#line 4370 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "#line ");
#line 4371 "bootstrap/stage0/ReCode.code"
    File__write_i32(self->file, (int32_t) location->line);
#line 4372 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " \"");
#line 4373 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, location->source->path);
#line 4374 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "\"\n");
}

#line 4377 "bootstrap/stage0/ReCode.code"
void Generator__generate_add_expression(struct Generator* self, struct Checked_Add_Expression* expression) {
#line 4378 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4379 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " + ");
#line 4380 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4383 "bootstrap/stage0/ReCode.code"
void Generator__generate_address_of_expression(struct Generator* self, struct Checked_Address_Of_Expression* expression) {
#line 4384 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "&");
#line 4385 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4388 "bootstrap/stage0/ReCode.code"
void Generator__generate_array_access_expression(struct Generator* self, struct Checked_Array_Access_Expression* expression) {
#line 4389 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->array_expression);
#line 4390 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "[");
#line 4391 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->index_expression);
#line 4392 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "]");
}

#line 4395 "bootstrap/stage0/ReCode.code"
void Generator__generate_bool_expression(struct Generator* self, struct Checked_Bool_Expression* expression) {
#line 4396 "bootstrap/stage0/ReCode.code"
    if (expression->value) {
#line 4397 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "true");
    } else {
#line 4399 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "false");
    }
}

#line 4403 "bootstrap/stage0/ReCode.code"
void Generator__generate_call_expression(struct Generator* self, struct Checked_Call_Expression* expression) {
#line 4404 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->callee_expression);
#line 4405 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4406 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Argument* argument = expression->first_argument;
#line 4407 "bootstrap/stage0/ReCode.code"
    while (argument != NULL) {
#line 4408 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, argument->expression);
#line 4409 "bootstrap/stage0/ReCode.code"
        argument = argument->next_argument;
#line 4410 "bootstrap/stage0/ReCode.code"
        if (argument != NULL) {
#line 4411 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, ", ");
        }
    }
#line 4414 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");
}

#line 4417 "bootstrap/stage0/ReCode.code"
void Generator__generate_cast_expression(struct Generator* self, struct Checked_Cast_Expression* expression) {
#line 4418 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4419 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->super.type);
#line 4420 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4421 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
}

#line 4424 "bootstrap/stage0/ReCode.code"
void File__write_octal_escaped_char(struct File* stream, char value) {
#line 4425 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, '\\');
#line 4426 "bootstrap/stage0/ReCode.code"
    if (value > (char) 64) {
#line 4427 "bootstrap/stage0/ReCode.code"
        File__write_char(stream, value / (char) 64 % (char) 8 + '0');
    }
#line 4429 "bootstrap/stage0/ReCode.code"
    if (value > (char) 8) {
#line 4430 "bootstrap/stage0/ReCode.code"
        File__write_char(stream, value / (char) 8 % (char) 8 + '0');
    }
#line 4432 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, value % (char) 8 + '0');
}

#line 4435 "bootstrap/stage0/ReCode.code"
void File__write_escaped_char(struct File* stream, char ch) {
#line 4436 "bootstrap/stage0/ReCode.code"
    if (ch < (char) 32) {
#line 4437 "bootstrap/stage0/ReCode.code"
        if (ch == '\n') {
#line 4438 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\n");
        } else if (ch == '\t') {
#line 4440 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\t");
        } else {
#line 4442 "bootstrap/stage0/ReCode.code"
            File__write_octal_escaped_char(stream, ch);
        }
    } else if (ch < (char) 127) {
#line 4445 "bootstrap/stage0/ReCode.code"
        if (ch == '\"') {
#line 4446 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\\"");
        } else if (ch == '\'') {
#line 4448 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\\'");
        } else if (ch == '\\') {
#line 4450 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\\\");
        } else {
#line 4452 "bootstrap/stage0/ReCode.code"
            File__write_char(stream, ch);
        }
    } else {
#line 4455 "bootstrap/stage0/ReCode.code"
        File__write_octal_escaped_char(stream, ch);
    }
}

#line 4459 "bootstrap/stage0/ReCode.code"
void Generator__generate_character_expression(struct Generator* self, struct Checked_Character_Expression* expression) {
#line 4460 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');
#line 4461 "bootstrap/stage0/ReCode.code"
    File__write_escaped_char(self->file, expression->value);
#line 4462 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');
}

#line 4465 "bootstrap/stage0/ReCode.code"
void Generator__generate_divide_expression(struct Generator* self, struct Checked_Divide_Expression* expression) {
#line 4466 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4467 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " / ");
#line 4468 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4471 "bootstrap/stage0/ReCode.code"
void Generator__generate_equals_expression(struct Generator* self, struct Checked_Equals_Expression* expression) {
#line 4472 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4473 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " == ");
#line 4474 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4477 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_expression(struct Generator* self, struct Checked_Greater_Expression* expression) {
#line 4478 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4479 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " > ");
#line 4480 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4483 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_or_equals_expression(struct Generator* self, struct Checked_Greater_Or_Equals_Expression* expression) {
#line 4484 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4485 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " >= ");
#line 4486 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4489 "bootstrap/stage0/ReCode.code"
void Generator__generate_group_expression(struct Generator* self, struct Checked_Group_Expression* expression) {
#line 4490 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4491 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
#line 4492 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");
}

#line 4495 "bootstrap/stage0/ReCode.code"
void Generator__generate_integer_expression(struct Generator* self, struct Checked_Integer_Expression* expression) {
#line 4496 "bootstrap/stage0/ReCode.code"
    File__write_u64(self->file, expression->value);
}

#line 4499 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_expression(struct Generator* self, struct Checked_Less_Expression* expression) {
#line 4500 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4501 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " < ");
#line 4502 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4505 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_or_equals_expression(struct Generator* self, struct Checked_Less_Or_Equals_Expression* expression) {
#line 4506 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4507 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " <= ");
#line 4508 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4511 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_and_expression(struct Generator* self, struct Checked_Logic_And_Expression* expression) {
#line 4512 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4513 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " && ");
#line 4514 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4517 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_or_expression(struct Generator* self, struct Checked_Logic_Or_Expression* expression) {
#line 4518 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4519 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " || ");
#line 4520 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4523 "bootstrap/stage0/ReCode.code"
void Generator__generate_member_access_expression(struct Generator* self, struct Checked_Member_Access_Expression* expression) {
#line 4524 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->object_expression);
#line 4525 "bootstrap/stage0/ReCode.code"
    if (expression->object_expression->type->kind == Checked_Type_Kind__POINTER) {
#line 4526 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "->");
    } else {
#line 4528 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ".");
    }
#line 4530 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->member->name);
}

#line 4533 "bootstrap/stage0/ReCode.code"
void Generator__generate_minus_expression(struct Generator* self, struct Checked_Minus_Expression* expression) {
#line 4534 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "-");
#line 4535 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4538 "bootstrap/stage0/ReCode.code"
void Generator__generate_modulo_expression(struct Generator* self, struct Checked_Modulo_Expression* expression) {
#line 4539 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4540 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " % ");
#line 4541 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4544 "bootstrap/stage0/ReCode.code"
void Generator__generate_multiply_expression(struct Generator* self, struct Checked_Multiply_Expression* expression) {
#line 4545 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4546 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " * ");
#line 4547 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4550 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_expression(struct Generator* self, struct Checked_Not_Expression* expression) {
#line 4551 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "!");
#line 4552 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4555 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_equals_expression(struct Generator* self, struct Checked_Not_Equals_Expression* expression) {
#line 4556 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4557 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " != ");
#line 4558 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4561 "bootstrap/stage0/ReCode.code"
void Generator__generate_null_expression(struct Generator* self, struct Checked_Null_Expression* expression) {
#line 4562 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "NULL");
}

#line 4565 "bootstrap/stage0/ReCode.code"
void Generator__generate_sizeof_expression(struct Generator* self, struct Checked_Sizeof_Expression* expression) {
#line 4566 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "sizeof(");
#line 4567 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->sized_type);
#line 4568 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");
}

#line 4571 "bootstrap/stage0/ReCode.code"
void Generator__generate_string_expression(struct Generator* self, struct Checked_String_Expression* expression) {
#line 4572 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');
#line 4573 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 4574 "bootstrap/stage0/ReCode.code"
    while (index < expression->value->length) {
#line 4575 "bootstrap/stage0/ReCode.code"
        File__write_escaped_char(self->file, expression->value->data[index]);
#line 4576 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
#line 4578 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');
}

#line 4581 "bootstrap/stage0/ReCode.code"
void Generator__generate_substract_expression(struct Generator* self, struct Checked_Substract_Expression* expression) {
#line 4582 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4583 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " - ");
#line 4584 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4587 "bootstrap/stage0/ReCode.code"
void Generator__generate_symbol_expression(struct Generator* self, struct Checked_Symbol_Expression* expression) {
#line 4588 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->symbol->name);
}

#line 4591 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression(struct Generator* self, struct Checked_Expression* expression) {
#line 4592 "bootstrap/stage0/ReCode.code"
    if (expression->kind == Checked_Expression_Kind__ADD) {
#line 4593 "bootstrap/stage0/ReCode.code"
        Generator__generate_add_expression(self, (struct Checked_Add_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__ADDRESS_OF) {
#line 4595 "bootstrap/stage0/ReCode.code"
        Generator__generate_address_of_expression(self, (struct Checked_Address_Of_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__ARRAY_ACCESS) {
#line 4597 "bootstrap/stage0/ReCode.code"
        Generator__generate_array_access_expression(self, (struct Checked_Array_Access_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__BOOL) {
#line 4599 "bootstrap/stage0/ReCode.code"
        Generator__generate_bool_expression(self, (struct Checked_Bool_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__CALL) {
#line 4601 "bootstrap/stage0/ReCode.code"
        Generator__generate_call_expression(self, (struct Checked_Call_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__CAST) {
#line 4603 "bootstrap/stage0/ReCode.code"
        Generator__generate_cast_expression(self, (struct Checked_Cast_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__CHARACTER) {
#line 4605 "bootstrap/stage0/ReCode.code"
        Generator__generate_character_expression(self, (struct Checked_Character_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__DIVIDE) {
#line 4607 "bootstrap/stage0/ReCode.code"
        Generator__generate_divide_expression(self, (struct Checked_Divide_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__EQUALS) {
#line 4609 "bootstrap/stage0/ReCode.code"
        Generator__generate_equals_expression(self, (struct Checked_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__GREATER) {
#line 4611 "bootstrap/stage0/ReCode.code"
        Generator__generate_greater_expression(self, (struct Checked_Greater_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__GREATER_OR_EQUALS) {
#line 4613 "bootstrap/stage0/ReCode.code"
        Generator__generate_greater_or_equals_expression(self, (struct Checked_Greater_Or_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__GROUP) {
#line 4615 "bootstrap/stage0/ReCode.code"
        Generator__generate_group_expression(self, (struct Checked_Group_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__INTEGER) {
#line 4617 "bootstrap/stage0/ReCode.code"
        Generator__generate_integer_expression(self, (struct Checked_Integer_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LESS) {
#line 4619 "bootstrap/stage0/ReCode.code"
        Generator__generate_less_expression(self, (struct Checked_Less_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LESS_OR_EQUALS) {
#line 4621 "bootstrap/stage0/ReCode.code"
        Generator__generate_less_or_equals_expression(self, (struct Checked_Less_Or_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LOGIC_AND) {
#line 4623 "bootstrap/stage0/ReCode.code"
        Generator__generate_logic_and_expression(self, (struct Checked_Logic_And_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LOGIC_OR) {
#line 4625 "bootstrap/stage0/ReCode.code"
        Generator__generate_logic_or_expression(self, (struct Checked_Logic_Or_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MEMBER_ACCESS) {
#line 4627 "bootstrap/stage0/ReCode.code"
        Generator__generate_member_access_expression(self, (struct Checked_Member_Access_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MINUS) {
#line 4629 "bootstrap/stage0/ReCode.code"
        Generator__generate_minus_expression(self, (struct Checked_Minus_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MODULO) {
#line 4631 "bootstrap/stage0/ReCode.code"
        Generator__generate_modulo_expression(self, (struct Checked_Modulo_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MULTIPLY) {
#line 4633 "bootstrap/stage0/ReCode.code"
        Generator__generate_multiply_expression(self, (struct Checked_Multiply_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__NOT) {
#line 4635 "bootstrap/stage0/ReCode.code"
        Generator__generate_not_expression(self, (struct Checked_Not_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__NOT_EQUALS) {
#line 4637 "bootstrap/stage0/ReCode.code"
        Generator__generate_not_equals_expression(self, (struct Checked_Not_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__NULL) {
#line 4639 "bootstrap/stage0/ReCode.code"
        Generator__generate_null_expression(self, (struct Checked_Null_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__SIZEOF) {
#line 4641 "bootstrap/stage0/ReCode.code"
        Generator__generate_sizeof_expression(self, (struct Checked_Sizeof_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__STRING) {
#line 4643 "bootstrap/stage0/ReCode.code"
        Generator__generate_string_expression(self, (struct Checked_String_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__SUBSTRACT) {
#line 4645 "bootstrap/stage0/ReCode.code"
        Generator__generate_substract_expression(self, (struct Checked_Substract_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__SYMBOL) {
#line 4647 "bootstrap/stage0/ReCode.code"
        Generator__generate_symbol_expression(self, (struct Checked_Symbol_Expression*) expression);
    } else {
#line 4649 "bootstrap/stage0/ReCode.code"
        Source_Location__error(expression->location, String__create_from("Unsupported expression"));
#line 4650 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 4654 "bootstrap/stage0/ReCode.code"
void Generator__write_identation(struct Generator* self) {
#line 4655 "bootstrap/stage0/ReCode.code"
    uint16_t identation = self->identation;
#line 4656 "bootstrap/stage0/ReCode.code"
    while (identation > (uint16_t) 0) {
#line 4657 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "    ");
#line 4658 "bootstrap/stage0/ReCode.code"
        identation = identation - (uint16_t) 1;
    }
}

#line 4662 "bootstrap/stage0/ReCode.code"
void Generator__generate_assignment_statement(struct Generator* self, struct Checked_Assignment_Statement* statement) {
#line 4663 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->object_expression);
#line 4664 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " = ");
#line 4665 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->value_expression);
#line 4666 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4669 "bootstrap/stage0/ReCode.code"
void Generator__generate_block_statement(struct Generator* self, struct Checked_Block_Statement* statement) {
#line 4670 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "{\n");
#line 4671 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, statement->statements);
#line 4672 "bootstrap/stage0/ReCode.code"
    Generator__write_identation(self);
#line 4673 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "}");
}

#line 4676 "bootstrap/stage0/ReCode.code"
void Generator__generate_break_statement(struct Generator* self, struct Checked_Break_Statement* statement) {
#line 4677 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "break;");
}

#line 4680 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression_statement(struct Generator* self, struct Checked_Expression_Statement* statement) {
#line 4681 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->expression);
#line 4682 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4685 "bootstrap/stage0/ReCode.code"
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement) {
#line 4686 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "if (");
#line 4687 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4688 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4689 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->true_statement);
#line 4690 "bootstrap/stage0/ReCode.code"
    if (statement->false_statement != NULL) {
#line 4691 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, " else ");
#line 4692 "bootstrap/stage0/ReCode.code"
        Generator__generate_statement(self, statement->false_statement);
    }
}

#line 4696 "bootstrap/stage0/ReCode.code"
void Generator__generate_return_statement(struct Generator* self, struct Checked_Return_Statement* statement) {
#line 4697 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "return");
#line 4698 "bootstrap/stage0/ReCode.code"
    if (statement->expression != NULL) {
#line 4699 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, " ");
#line 4700 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, statement->expression);
    }
#line 4702 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4705 "bootstrap/stage0/ReCode.code"
void Generator__generate_variable_statement(struct Generator* self, struct Checked_Variable_Statement* statement) {
#line 4706 "bootstrap/stage0/ReCode.code"
    if (statement->is_external) {
#line 4707 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "extern ");
    }
#line 4709 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, statement->variable->super.type);
#line 4710 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ' ');
#line 4711 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, statement->variable->super.name);
#line 4712 "bootstrap/stage0/ReCode.code"
    if (statement->expression != NULL) {
#line 4713 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, " = ");
#line 4714 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, statement->expression);
    }
#line 4716 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4719 "bootstrap/stage0/ReCode.code"
void Generator__generate_while_statement(struct Generator* self, struct Checked_While_Statement* statement) {
#line 4720 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "while (");
#line 4721 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4722 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4723 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->body_statement);
}

#line 4726 "bootstrap/stage0/ReCode.code"
void Generator__generate_statement(struct Generator* self, struct Checked_Statement* statement) {
#line 4727 "bootstrap/stage0/ReCode.code"
    if (statement->kind == Checked_Statement_Kind__ASSIGNMENT) {
#line 4728 "bootstrap/stage0/ReCode.code"
        Generator__generate_assignment_statement(self, (struct Checked_Assignment_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__BLOCK) {
#line 4730 "bootstrap/stage0/ReCode.code"
        Generator__generate_block_statement(self, (struct Checked_Block_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__BREAK) {
#line 4732 "bootstrap/stage0/ReCode.code"
        Generator__generate_break_statement(self, (struct Checked_Break_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__EXPRESSION) {
#line 4734 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression_statement(self, (struct Checked_Expression_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__IF) {
#line 4736 "bootstrap/stage0/ReCode.code"
        Generator__generate_if_statement(self, (struct Checked_If_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__RETURN) {
#line 4738 "bootstrap/stage0/ReCode.code"
        Generator__generate_return_statement(self, (struct Checked_Return_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 4740 "bootstrap/stage0/ReCode.code"
        Generator__generate_variable_statement(self, (struct Checked_Variable_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__WHILE) {
#line 4742 "bootstrap/stage0/ReCode.code"
        Generator__generate_while_statement(self, (struct Checked_While_Statement*) statement);
    } else {
#line 4744 "bootstrap/stage0/ReCode.code"
        Source_Location__error(statement->location, String__create_from("Unsupported statement"));
#line 4745 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 4749 "bootstrap/stage0/ReCode.code"
void Generator__generate_statements(struct Generator* self, struct Checked_Statements* statements) {
#line 4750 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation + (uint16_t) 1;
#line 4752 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* statement = statements->first_statement;
#line 4753 "bootstrap/stage0/ReCode.code"
    while (statement != NULL) {
#line 4754 "bootstrap/stage0/ReCode.code"
        Generator__write_source_location(self, statement->location);
#line 4756 "bootstrap/stage0/ReCode.code"
        Generator__write_identation(self);
#line 4758 "bootstrap/stage0/ReCode.code"
        Generator__generate_statement(self, statement);
#line 4760 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "\n");
#line 4762 "bootstrap/stage0/ReCode.code"
        statement = statement->next_statement;
    }
#line 4765 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation - (uint16_t) 1;
}

#line 4768 "bootstrap/stage0/ReCode.code"
void Generator__generate_enum(struct Generator* self, struct Checked_Enum_Type* enum_type) {
#line 4769 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) enum_type);
#line 4770 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4771 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* enum_member = enum_type->first_member;
#line 4772 "bootstrap/stage0/ReCode.code"
    while (enum_member != NULL) {
#line 4773 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4774 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, enum_member->symbol->name);
#line 4775 "bootstrap/stage0/ReCode.code"
        enum_member = enum_member->next_member;
#line 4776 "bootstrap/stage0/ReCode.code"
        if (enum_member != NULL) {
#line 4777 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, ",\n");
        } else {
#line 4779 "bootstrap/stage0/ReCode.code"
            File__write_char(self->file, '\n');
        }
    }
#line 4782 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n");
}

#line 4785 "bootstrap/stage0/ReCode.code"
void Generator__declare_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4786 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) function_symbol->function_type);
#line 4787 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");
}

#line 4790 "bootstrap/stage0/ReCode.code"
void Generator__generate_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4791 "bootstrap/stage0/ReCode.code"
    if (function_symbol->checked_statements == NULL) {
#line 4792 "bootstrap/stage0/ReCode.code"
        return;
    }
#line 4794 "bootstrap/stage0/ReCode.code"
    Generator__write_source_location(self, function_symbol->super.location);
#line 4795 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) function_symbol->function_type);
#line 4796 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4797 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, function_symbol->checked_statements);
#line 4798 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "}\n\n");
}

#line 4801 "bootstrap/stage0/ReCode.code"
void Generator__declare_opaque_type(struct Generator* self, struct Checked_Opaque_Type* opaque_type) {
#line 4802 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) opaque_type);
#line 4803 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");
}

#line 4806 "bootstrap/stage0/ReCode.code"
void Generator__declare_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4807 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) struct_type);
#line 4808 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");
}

#line 4811 "bootstrap/stage0/ReCode.code"
void Generator__generate_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4812 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* struct_member = struct_type->first_member;
#line 4813 "bootstrap/stage0/ReCode.code"
    if (struct_member == NULL) {
#line 4814 "bootstrap/stage0/ReCode.code"
        return;
    }
#line 4816 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) struct_type);
#line 4817 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4818 "bootstrap/stage0/ReCode.code"
    while (struct_member != NULL) {
#line 4819 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4820 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self->file, struct_member->type);
#line 4821 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4822 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, struct_member->name);
#line 4823 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ";\n");
#line 4824 "bootstrap/stage0/ReCode.code"
        struct_member = struct_member->next_member;
    }
#line 4826 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n\n");
}

#line 4829 "bootstrap/stage0/ReCode.code"
void generate(struct File* file, struct Checked_Source* checked_source) {
#line 4830 "bootstrap/stage0/ReCode.code"
    struct Generator generator;
#line 4831 "bootstrap/stage0/ReCode.code"
    generator.file = file;
#line 4832 "bootstrap/stage0/ReCode.code"
    generator.identation = (uint16_t) 0;
#line 4834 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* checked_symbol;
#line 4836 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "/* Copyright (C) 2023 Stefan Selariu */\n");
#line 4837 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4838 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <inttypes.h>\n");
#line 4839 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stdbool.h>\n");
#line 4840 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stddef.h>\n");
#line 4841 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4844 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4845 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4846 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 4847 "bootstrap/stage0/ReCode.code"
            struct Checked_Named_Type* named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 4848 "bootstrap/stage0/ReCode.code"
            if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 4849 "bootstrap/stage0/ReCode.code"
                Generator__declare_struct(&generator, (struct Checked_Struct_Type*) named_type);
            } else if (named_type->super.kind == Checked_Type_Kind__OPAQUE) {
#line 4851 "bootstrap/stage0/ReCode.code"
                Generator__declare_opaque_type(&generator, (struct Checked_Opaque_Type*) named_type);
            } else if (named_type->super.kind == Checked_Type_Kind__ENUM) {
#line 4853 "bootstrap/stage0/ReCode.code"
                Generator__generate_enum(&generator, (struct Checked_Enum_Type*) named_type);
            }
        }
#line 4856 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4858 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4861 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4862 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4863 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 4864 "bootstrap/stage0/ReCode.code"
            struct Checked_Named_Type* named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 4865 "bootstrap/stage0/ReCode.code"
            if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 4866 "bootstrap/stage0/ReCode.code"
                Generator__generate_struct(&generator, (struct Checked_Struct_Type*) named_type);
            }
        }
#line 4869 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4873 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* checked_statement = checked_source->statements->first_statement;
#line 4874 "bootstrap/stage0/ReCode.code"
    while (checked_statement != NULL) {
#line 4875 "bootstrap/stage0/ReCode.code"
        if (checked_statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 4876 "bootstrap/stage0/ReCode.code"
            Generator__generate_variable_statement(&generator, (struct Checked_Variable_Statement*) checked_statement);
#line 4877 "bootstrap/stage0/ReCode.code"
            File__write_cstring(generator.file, "\n");
        } else {
#line 4879 "bootstrap/stage0/ReCode.code"
            Source_Location__error(checked_statement->location, String__create_from("Unsupported statement"));
#line 4880 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4882 "bootstrap/stage0/ReCode.code"
        checked_statement = checked_statement->next_statement;
    }
#line 4884 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4887 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4888 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4889 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 4890 "bootstrap/stage0/ReCode.code"
            Generator__declare_function(&generator, (struct Checked_Function_Symbol*) checked_symbol);
        }
#line 4892 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4894 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4897 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4898 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4899 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 4900 "bootstrap/stage0/ReCode.code"
            Generator__generate_function(&generator, (struct Checked_Function_Symbol*) checked_symbol);
        }
#line 4902 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
}

#line 4910 "bootstrap/stage0/ReCode.code"
int32_t main(int32_t argc, char** argv) {
#line 4911 "bootstrap/stage0/ReCode.code"
    if (argc < 3) {
#line 4912 "bootstrap/stage0/ReCode.code"
        error(String__append_cstring(String__append_cstring(String__create_from("Usage: "), argv[(size_t) 0]), " SOURCE OUTPUT"));
#line 4913 "bootstrap/stage0/ReCode.code"
        return 1;
    }
#line 4916 "bootstrap/stage0/ReCode.code"
    char* source_file_path = argv[(size_t) 1];
#line 4917 "bootstrap/stage0/ReCode.code"
    struct File* source_file = fopen(source_file_path, "r");
#line 4918 "bootstrap/stage0/ReCode.code"
    if (source_file == NULL) {
#line 4919 "bootstrap/stage0/ReCode.code"
        error(String__append_cstring(String__create_from("Cannot open file: "), source_file_path));
#line 4920 "bootstrap/stage0/ReCode.code"
        return 1;
    }
#line 4923 "bootstrap/stage0/ReCode.code"
    char* output_file_path = argv[(size_t) 2];
#line 4924 "bootstrap/stage0/ReCode.code"
    struct File* output_file;
#line 4925 "bootstrap/stage0/ReCode.code"
    if (String__equals_cstring(String__create_from(output_file_path), "-")) {
#line 4926 "bootstrap/stage0/ReCode.code"
        output_file = stdout;
    } else {
#line 4928 "bootstrap/stage0/ReCode.code"
        output_file = fopen(output_file_path, "w");
#line 4929 "bootstrap/stage0/ReCode.code"
        if (output_file == NULL) {
#line 4930 "bootstrap/stage0/ReCode.code"
            error(String__append_cstring(String__create_from("Cannot open file: "), output_file_path));
#line 4931 "bootstrap/stage0/ReCode.code"
            return 1;
        }
    }
#line 4935 "bootstrap/stage0/ReCode.code"
    struct Source* source = Source__create(source_file, source_file_path);
#line 4936 "bootstrap/stage0/ReCode.code"
    struct Parsed_Source* parsed_source = parse(source);
#line 4937 "bootstrap/stage0/ReCode.code"
    struct Checked_Source* checked_source = check(parsed_source);
#line 4938 "bootstrap/stage0/ReCode.code"
    generate(output_file, checked_source);
#line 4940 "bootstrap/stage0/ReCode.code"
    fclose(source_file);
#line 4941 "bootstrap/stage0/ReCode.code"
    return fclose(output_file);
}

