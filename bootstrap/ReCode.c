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
bool Token__is_external(struct Token* self);
bool Token__is_false(struct Token* self);
bool Token__is_func(struct Token* self);
bool Token__is_if(struct Token* self);
bool Token__is_let(struct Token* self);
bool Token__is_null(struct Token* self);
bool Token__is_opaque(struct Token* self);
bool Token__is_return(struct Token* self);
bool Token__is_sizeof(struct Token* self);
bool Token__is_struct(struct Token* self);
bool Token__is_true(struct Token* self);
bool Token__is_type(struct Token* self);
bool Token__is_typedef(struct Token* self);
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
struct Parsed_Statement* Parser__parse_old_variable(struct Parser* self);
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
void File__write_char(struct File* self, char c) {
#line 153 "bootstrap/stage0/ReCode.code"
    fputc((int32_t) c, self);
}

#line 156 "bootstrap/stage0/ReCode.code"
void File__write_cstring(struct File* self, char* s) {
#line 157 "bootstrap/stage0/ReCode.code"
    fputs(s, self);
}

#line 160 "bootstrap/stage0/ReCode.code"
void File__write_i32(struct File* self, int32_t value) {
#line 161 "bootstrap/stage0/ReCode.code"
    if (value < 0) {
#line 162 "bootstrap/stage0/ReCode.code"
        File__write_char(self, '-');
#line 163 "bootstrap/stage0/ReCode.code"
        File__write_i32(self, -value);
    } else {
#line 165 "bootstrap/stage0/ReCode.code"
        if (value >= 10) {
#line 166 "bootstrap/stage0/ReCode.code"
            File__write_i32(self, value / 10);
        }
#line 168 "bootstrap/stage0/ReCode.code"
        File__write_char(self, (char) (value % 10) + '0');
    }
}

#line 172 "bootstrap/stage0/ReCode.code"
void File__write_u64(struct File* self, uint64_t value) {
#line 173 "bootstrap/stage0/ReCode.code"
    if (value >= (uint64_t) 10) {
#line 174 "bootstrap/stage0/ReCode.code"
        File__write_u64(self, value / (uint64_t) 10);
    }
#line 176 "bootstrap/stage0/ReCode.code"
    File__write_char(self, (char) (value % (uint64_t) 10) + '0');
}

#line 179 "bootstrap/stage0/ReCode.code"
void File__write_string(struct File* self, struct String* string) {
#line 180 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 181 "bootstrap/stage0/ReCode.code"
    while (index < string->length) {
#line 182 "bootstrap/stage0/ReCode.code"
        File__write_char(self, string->data[index]);
#line 183 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
}

#line 187 "bootstrap/stage0/ReCode.code"
void error(struct String* message) {
#line 188 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;91m");
#line 189 "bootstrap/stage0/ReCode.code"
    File__write_string(stderr, message);
#line 190 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 193 "bootstrap/stage0/ReCode.code"
void warning(struct String* message) {
#line 194 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;93m");
#line 195 "bootstrap/stage0/ReCode.code"
    File__write_string(stderr, message);
#line 196 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 199 "bootstrap/stage0/ReCode.code"
void TODO(char* message) {
#line 200 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0;95mTODO: ");
#line 201 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, message);
#line 202 "bootstrap/stage0/ReCode.code"
    File__write_cstring(stderr, "\33[0m\n");
}

#line 214 "bootstrap/stage0/ReCode.code"
struct Source* Source__create(struct File* file, char* file_path) {
#line 215 "bootstrap/stage0/ReCode.code"
    struct String* file_content = String__create();
#line 217 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 218 "bootstrap/stage0/ReCode.code"
        int32_t ch = fgetc(file);
#line 219 "bootstrap/stage0/ReCode.code"
        if (ch == -1) {
#line 220 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 222 "bootstrap/stage0/ReCode.code"
        String__append_char(file_content, (char) ch);
    }
#line 225 "bootstrap/stage0/ReCode.code"
    String__append_char(file_content, '\0');
#line 227 "bootstrap/stage0/ReCode.code"
    struct Source* source = (struct Source*) malloc(sizeof(struct Source));
#line 228 "bootstrap/stage0/ReCode.code"
    source->content = file_content;
#line 229 "bootstrap/stage0/ReCode.code"
    source->path = file_path;
#line 231 "bootstrap/stage0/ReCode.code"
    return source;
}

#line 244 "bootstrap/stage0/ReCode.code"
struct Source_Location* Source_Location__create(struct Source* source, uint16_t line, uint16_t column) {
#line 245 "bootstrap/stage0/ReCode.code"
    struct Source_Location* source_location = (struct Source_Location*) malloc(sizeof(struct Source_Location));
#line 246 "bootstrap/stage0/ReCode.code"
    source_location->source = source;
#line 247 "bootstrap/stage0/ReCode.code"
    source_location->line = line;
#line 248 "bootstrap/stage0/ReCode.code"
    source_location->column = column;
#line 249 "bootstrap/stage0/ReCode.code"
    return source_location;
}

#line 252 "bootstrap/stage0/ReCode.code"
struct String* String__append_source_location(struct String* self, struct Source_Location* location) {
#line 253 "bootstrap/stage0/ReCode.code"
    String__append_cstring(self, location->source->path);
#line 254 "bootstrap/stage0/ReCode.code"
    String__append_char(self, ':');
#line 255 "bootstrap/stage0/ReCode.code"
    String__append_i16(self, (int16_t) location->line);
#line 256 "bootstrap/stage0/ReCode.code"
    String__append_char(self, ':');
#line 257 "bootstrap/stage0/ReCode.code"
    String__append_i16(self, (int16_t) location->column);
#line 258 "bootstrap/stage0/ReCode.code"
    return self;
}

#line 261 "bootstrap/stage0/ReCode.code"
void File__write_source_location(struct File* self, struct Source_Location* location) {
#line 262 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self, location->source->path);
#line 263 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ':');
#line 264 "bootstrap/stage0/ReCode.code"
    File__write_i32(self, (int32_t) location->line);
#line 265 "bootstrap/stage0/ReCode.code"
    File__write_char(self, ':');
#line 266 "bootstrap/stage0/ReCode.code"
    File__write_i32(self, (int32_t) location->column);
#line 267 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self, ": ");
}

#line 270 "bootstrap/stage0/ReCode.code"
void Source_Location__error(struct Source_Location* self, struct String* message) {
#line 271 "bootstrap/stage0/ReCode.code"
    File__write_source_location(stderr, self);
#line 272 "bootstrap/stage0/ReCode.code"
    error(message);
}

#line 275 "bootstrap/stage0/ReCode.code"
void Source_Location__warning(struct Source_Location* self, struct String* message) {
#line 276 "bootstrap/stage0/ReCode.code"
    File__write_source_location(stderr, self);
#line 277 "bootstrap/stage0/ReCode.code"
    warning(message);
}

#line 305 "bootstrap/stage0/ReCode.code"
struct Token* Token__create_kind(enum Token_Kind kind, size_t kind_size, struct Source_Location* location, struct String* lexeme) {
#line 306 "bootstrap/stage0/ReCode.code"
    struct Token* token = (struct Token*) malloc(kind_size);
#line 307 "bootstrap/stage0/ReCode.code"
    token->kind = kind;
#line 308 "bootstrap/stage0/ReCode.code"
    token->location = location;
#line 309 "bootstrap/stage0/ReCode.code"
    token->lexeme = lexeme;
#line 310 "bootstrap/stage0/ReCode.code"
    token->next_token = NULL;
#line 311 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 314 "bootstrap/stage0/ReCode.code"
void Token__error(struct Token* self, struct String* message) {
#line 315 "bootstrap/stage0/ReCode.code"
    Source_Location__error(self->location, message);
}

#line 318 "bootstrap/stage0/ReCode.code"
void Token__warning(struct Token* self, struct String* message) {
#line 319 "bootstrap/stage0/ReCode.code"
    Source_Location__warning(self->location, message);
}

#line 327 "bootstrap/stage0/ReCode.code"
struct Character_Token* Character_Token__create(struct Source_Location* location, struct String* lexeme, char value) {
#line 328 "bootstrap/stage0/ReCode.code"
    struct Character_Token* token = (struct Character_Token*) Token__create_kind(Token_Kind__CHARACTER, sizeof(struct Character_Token), location, lexeme);
#line 329 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 330 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 337 "bootstrap/stage0/ReCode.code"
struct Comment_Token* Comment_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 338 "bootstrap/stage0/ReCode.code"
    return (struct Comment_Token*) Token__create_kind(Token_Kind__COMMENT, sizeof(struct Comment_Token), location, lexeme);
}

#line 345 "bootstrap/stage0/ReCode.code"
struct End_Of_File_Token* End_Of_File_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 346 "bootstrap/stage0/ReCode.code"
    return (struct End_Of_File_Token*) Token__create_kind(Token_Kind__END_OF_FILE, sizeof(struct End_Of_File_Token), location, lexeme);
}

#line 353 "bootstrap/stage0/ReCode.code"
struct End_Of_Line_Token* End_Of_Line_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 354 "bootstrap/stage0/ReCode.code"
    return (struct End_Of_Line_Token*) Token__create_kind(Token_Kind__END_OF_LINE, sizeof(struct End_Of_Line_Token), location, lexeme);
}

#line 361 "bootstrap/stage0/ReCode.code"
struct Error_Token* Error_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 362 "bootstrap/stage0/ReCode.code"
    return (struct Error_Token*) Token__create_kind(Token_Kind__ERROR, sizeof(struct Error_Token), location, lexeme);
}

#line 369 "bootstrap/stage0/ReCode.code"
struct Identifier_Token* Identifier_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 370 "bootstrap/stage0/ReCode.code"
    return (struct Identifier_Token*) Token__create_kind(Token_Kind__IDENTIFIER, sizeof(struct Identifier_Token), location, lexeme);
}

#line 378 "bootstrap/stage0/ReCode.code"
struct Integer_Token* Integer_Token__create(struct Source_Location* location, struct String* lexeme, uint64_t value) {
#line 379 "bootstrap/stage0/ReCode.code"
    struct Integer_Token* token = (struct Integer_Token*) Token__create_kind(Token_Kind__INTEGER, sizeof(struct Integer_Token), location, lexeme);
#line 380 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 381 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 388 "bootstrap/stage0/ReCode.code"
struct Other_Token* Other_Token__create(struct Source_Location* location, struct String* lexeme) {
#line 389 "bootstrap/stage0/ReCode.code"
    return (struct Other_Token*) Token__create_kind(Token_Kind__OTHER, sizeof(struct Other_Token), location, lexeme);
}

#line 397 "bootstrap/stage0/ReCode.code"
struct Space_Token* Space_Token__create(struct Source_Location* location, struct String* lexeme, uint16_t count) {
#line 398 "bootstrap/stage0/ReCode.code"
    struct Space_Token* token = (struct Space_Token*) Token__create_kind(Token_Kind__SPACE, sizeof(struct Space_Token), location, lexeme);
#line 399 "bootstrap/stage0/ReCode.code"
    token->count = count;
#line 400 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 408 "bootstrap/stage0/ReCode.code"
struct String_Token* String_Token__create(struct Source_Location* location, struct String* lexeme, struct String* value) {
#line 409 "bootstrap/stage0/ReCode.code"
    struct String_Token* token = (struct String_Token*) Token__create_kind(Token_Kind__STRING, sizeof(struct String_Token), location, lexeme);
#line 410 "bootstrap/stage0/ReCode.code"
    token->value = value;
#line 411 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 414 "bootstrap/stage0/ReCode.code"
bool Token__is_anything(struct Token* self) {
#line 415 "bootstrap/stage0/ReCode.code"
    return self != NULL;
}

#line 418 "bootstrap/stage0/ReCode.code"
bool Token__is_character(struct Token* self) {
#line 419 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__CHARACTER;
}

#line 422 "bootstrap/stage0/ReCode.code"
bool Token__is_comment(struct Token* self) {
#line 423 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__COMMENT;
}

#line 426 "bootstrap/stage0/ReCode.code"
bool Token__is_end_of_file(struct Token* self) {
#line 427 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__END_OF_FILE;
}

#line 430 "bootstrap/stage0/ReCode.code"
bool Token__is_end_of_line(struct Token* self) {
#line 431 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__END_OF_LINE || self->kind == Token_Kind__END_OF_FILE;
}

#line 434 "bootstrap/stage0/ReCode.code"
bool Token__is_identifier(struct Token* self) {
#line 435 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__IDENTIFIER;
}

#line 438 "bootstrap/stage0/ReCode.code"
bool Token__is_integer(struct Token* self) {
#line 439 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__INTEGER;
}

#line 442 "bootstrap/stage0/ReCode.code"
bool Token__is_keyword(struct Token* self, char* lexeme) {
#line 443 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

#line 446 "bootstrap/stage0/ReCode.code"
bool Token__is_break(struct Token* self) {
#line 447 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "break");
}

#line 450 "bootstrap/stage0/ReCode.code"
bool Token__is_define(struct Token* self) {
#line 451 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "define");
}

#line 454 "bootstrap/stage0/ReCode.code"
bool Token__is_else(struct Token* self) {
#line 455 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "else");
}

#line 458 "bootstrap/stage0/ReCode.code"
bool Token__is_enum(struct Token* self) {
#line 459 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "enum");
}

#line 462 "bootstrap/stage0/ReCode.code"
bool Token__is_external(struct Token* self) {
#line 463 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "external");
}

#line 466 "bootstrap/stage0/ReCode.code"
bool Token__is_false(struct Token* self) {
#line 467 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "false");
}

#line 470 "bootstrap/stage0/ReCode.code"
bool Token__is_func(struct Token* self) {
#line 471 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "func");
}

#line 474 "bootstrap/stage0/ReCode.code"
bool Token__is_if(struct Token* self) {
#line 475 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "if");
}

#line 478 "bootstrap/stage0/ReCode.code"
bool Token__is_let(struct Token* self) {
#line 479 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "let");
}

#line 482 "bootstrap/stage0/ReCode.code"
bool Token__is_null(struct Token* self) {
#line 483 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "null");
}

#line 486 "bootstrap/stage0/ReCode.code"
bool Token__is_opaque(struct Token* self) {
#line 487 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "opaque");
}

#line 490 "bootstrap/stage0/ReCode.code"
bool Token__is_return(struct Token* self) {
#line 491 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "return");
}

#line 494 "bootstrap/stage0/ReCode.code"
bool Token__is_sizeof(struct Token* self) {
#line 495 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "sizeof");
}

#line 498 "bootstrap/stage0/ReCode.code"
bool Token__is_struct(struct Token* self) {
#line 499 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "struct");
}

#line 502 "bootstrap/stage0/ReCode.code"
bool Token__is_true(struct Token* self) {
#line 503 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "true");
}

#line 506 "bootstrap/stage0/ReCode.code"
bool Token__is_type(struct Token* self) {
#line 507 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "type");
}

#line 510 "bootstrap/stage0/ReCode.code"
bool Token__is_typedef(struct Token* self) {
#line 511 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "typedef");
}

#line 514 "bootstrap/stage0/ReCode.code"
bool Token__is_undefined(struct Token* self) {
#line 515 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "undefined");
}

#line 518 "bootstrap/stage0/ReCode.code"
bool Token__is_while(struct Token* self) {
#line 519 "bootstrap/stage0/ReCode.code"
    return Token__is_keyword(self, "while");
}

#line 522 "bootstrap/stage0/ReCode.code"
bool Token__is_other(struct Token* self, char* lexeme) {
#line 523 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__OTHER && String__equals_cstring(self->lexeme, lexeme);
}

#line 526 "bootstrap/stage0/ReCode.code"
bool Token__is_ampersand(struct Token* self) {
#line 527 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "&");
}

#line 530 "bootstrap/stage0/ReCode.code"
bool Token__is_asterisk(struct Token* self) {
#line 531 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "*");
}

#line 534 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_brace(struct Token* self) {
#line 535 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "}");
}

#line 538 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_bracket(struct Token* self) {
#line 539 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "]");
}

#line 542 "bootstrap/stage0/ReCode.code"
bool Token__is_closing_paren(struct Token* self) {
#line 543 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ")");
}

#line 546 "bootstrap/stage0/ReCode.code"
bool Token__is_colon(struct Token* self) {
#line 547 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ":");
}

#line 550 "bootstrap/stage0/ReCode.code"
bool Token__is_comma(struct Token* self) {
#line 551 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ",");
}

#line 554 "bootstrap/stage0/ReCode.code"
bool Token__is_dot(struct Token* self) {
#line 555 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ".");
}

#line 558 "bootstrap/stage0/ReCode.code"
bool Token__is_equals(struct Token* self) {
#line 559 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "=");
}

#line 562 "bootstrap/stage0/ReCode.code"
bool Token__is_exclamation_mark(struct Token* self) {
#line 563 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "!");
}

#line 566 "bootstrap/stage0/ReCode.code"
bool Token__is_greater_than(struct Token* self) {
#line 567 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, ">");
}

#line 570 "bootstrap/stage0/ReCode.code"
bool Token__is_less_than(struct Token* self) {
#line 571 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "<");
}

#line 574 "bootstrap/stage0/ReCode.code"
bool Token__is_minus(struct Token* self) {
#line 575 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "-");
}

#line 578 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_brace(struct Token* self) {
#line 579 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "{");
}

#line 582 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_bracket(struct Token* self) {
#line 583 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "[");
}

#line 586 "bootstrap/stage0/ReCode.code"
bool Token__is_opening_paren(struct Token* self) {
#line 587 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "(");
}

#line 590 "bootstrap/stage0/ReCode.code"
bool Token__is_percent(struct Token* self) {
#line 591 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "%");
}

#line 594 "bootstrap/stage0/ReCode.code"
bool Token__is_plus(struct Token* self) {
#line 595 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "+");
}

#line 598 "bootstrap/stage0/ReCode.code"
bool Token__is_slash(struct Token* self) {
#line 599 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "/");
}

#line 602 "bootstrap/stage0/ReCode.code"
bool Token__is_vertical_bar(struct Token* self) {
#line 603 "bootstrap/stage0/ReCode.code"
    return Token__is_other(self, "|");
}

#line 606 "bootstrap/stage0/ReCode.code"
bool Token__is_space(struct Token* self) {
#line 607 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__SPACE;
}

#line 610 "bootstrap/stage0/ReCode.code"
bool Token__is_string(struct Token* self) {
#line 611 "bootstrap/stage0/ReCode.code"
    return self->kind == Token_Kind__STRING;
}

#line 614 "bootstrap/stage0/ReCode.code"
void File__write_token(struct File* stream, struct Token* token) {
#line 615 "bootstrap/stage0/ReCode.code"
    bool colored = token->kind == Token_Kind__COMMENT || token->kind == Token_Kind__ERROR || token->kind == Token_Kind__OTHER;
#line 616 "bootstrap/stage0/ReCode.code"
    if (colored) {
#line 617 "bootstrap/stage0/ReCode.code"
        if (token->kind == Token_Kind__OTHER) {
#line 618 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\33[2;33m");
        } else if (token->kind == Token_Kind__COMMENT) {
#line 620 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\33[2;37m");
        } else if (token->kind == Token_Kind__ERROR) {
#line 622 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\33[2;31m");
        }
    }
#line 625 "bootstrap/stage0/ReCode.code"
    File__write_string(stream, token->lexeme);
#line 626 "bootstrap/stage0/ReCode.code"
    if (colored) {
#line 627 "bootstrap/stage0/ReCode.code"
        File__write_cstring(stream, "\33[0m");
    }
}

#line 643 "bootstrap/stage0/ReCode.code"
char Scanner__peek_char(struct Scanner* self) {
#line 644 "bootstrap/stage0/ReCode.code"
    return self->source->content->data[self->current_char_index];
}

#line 647 "bootstrap/stage0/ReCode.code"
char Scanner__next_char(struct Scanner* self) {
#line 648 "bootstrap/stage0/ReCode.code"
    char next_char = Scanner__peek_char(self);
#line 649 "bootstrap/stage0/ReCode.code"
    if (next_char != '\0') {
#line 650 "bootstrap/stage0/ReCode.code"
        self->current_char_index = self->current_char_index + (size_t) 1;
#line 651 "bootstrap/stage0/ReCode.code"
        if (next_char == '\n') {
#line 652 "bootstrap/stage0/ReCode.code"
            self->current_line = self->current_line + (uint16_t) 1;
#line 653 "bootstrap/stage0/ReCode.code"
            self->current_column = (uint16_t) 1;
        } else {
#line 655 "bootstrap/stage0/ReCode.code"
            self->current_column = self->current_column + (uint16_t) 1;
        }
    }
#line 658 "bootstrap/stage0/ReCode.code"
    return next_char;
}

#line 661 "bootstrap/stage0/ReCode.code"
char escape_char_value(char c) {
#line 662 "bootstrap/stage0/ReCode.code"
    if (c == 'n') {
#line 663 "bootstrap/stage0/ReCode.code"
        return '\n';
    }
#line 665 "bootstrap/stage0/ReCode.code"
    if (c == '\"') {
#line 666 "bootstrap/stage0/ReCode.code"
        return '\"';
    }
#line 668 "bootstrap/stage0/ReCode.code"
    if (c == '\'') {
#line 669 "bootstrap/stage0/ReCode.code"
        return '\'';
    }
#line 671 "bootstrap/stage0/ReCode.code"
    if (c == '\\') {
#line 672 "bootstrap/stage0/ReCode.code"
        return '\\';
    }
#line 674 "bootstrap/stage0/ReCode.code"
    if (c == 't') {
#line 675 "bootstrap/stage0/ReCode.code"
        return '\t';
    }
#line 677 "bootstrap/stage0/ReCode.code"
    if (c == '0') {
#line 678 "bootstrap/stage0/ReCode.code"
        return '\0';
    }
#line 680 "bootstrap/stage0/ReCode.code"
    if (c == 'e') {
#line 681 "bootstrap/stage0/ReCode.code"
        return '\33';
    }
#line 683 "bootstrap/stage0/ReCode.code"
    return (char) -1;
}

#line 686 "bootstrap/stage0/ReCode.code"
bool char_is_end_of_line(char c) {
#line 687 "bootstrap/stage0/ReCode.code"
    return c == '\n' || c == '\0';
}

#line 690 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_character_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 691 "bootstrap/stage0/ReCode.code"
    if (Scanner__next_char(self) != '\'') {
#line 692 "bootstrap/stage0/ReCode.code"
        Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 693 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 695 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\'');
#line 697 "bootstrap/stage0/ReCode.code"
    char next_char = Scanner__peek_char(self);
#line 698 "bootstrap/stage0/ReCode.code"
    if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 699 "bootstrap/stage0/ReCode.code"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 702 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 703 "bootstrap/stage0/ReCode.code"
    char value = next_char;
#line 705 "bootstrap/stage0/ReCode.code"
    if (value == '\'') {
#line 706 "bootstrap/stage0/ReCode.code"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 709 "bootstrap/stage0/ReCode.code"
    if (value == '\\') {
#line 710 "bootstrap/stage0/ReCode.code"
        next_char = Scanner__peek_char(self);
#line 711 "bootstrap/stage0/ReCode.code"
        if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 712 "bootstrap/stage0/ReCode.code"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
#line 715 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 717 "bootstrap/stage0/ReCode.code"
        value = escape_char_value(next_char);
#line 718 "bootstrap/stage0/ReCode.code"
        if (value == (char) -1) {
#line 719 "bootstrap/stage0/ReCode.code"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
    }
#line 723 "bootstrap/stage0/ReCode.code"
    if (Scanner__peek_char(self) != '\'') {
#line 724 "bootstrap/stage0/ReCode.code"
        return (struct Token*) Error_Token__create(source_location, token_lexeme);
    }
#line 727 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 728 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Character_Token__create(source_location, token_lexeme, value);
}

#line 731 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_comment_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 732 "bootstrap/stage0/ReCode.code"
    while (!char_is_end_of_line(Scanner__peek_char(self))) {
#line 733 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 735 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Comment_Token__create(source_location, token_lexeme);
}

#line 738 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_start(char c) {
#line 739 "bootstrap/stage0/ReCode.code"
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

#line 742 "bootstrap/stage0/ReCode.code"
bool char_is_identifier_letter(char c) {
#line 743 "bootstrap/stage0/ReCode.code"
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

#line 746 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_identifier_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 747 "bootstrap/stage0/ReCode.code"
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
#line 748 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 750 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Identifier_Token__create(source_location, token_lexeme);
}

#line 753 "bootstrap/stage0/ReCode.code"
bool char_is_digit(char c) {
#line 754 "bootstrap/stage0/ReCode.code"
    return c >= '0' && c <= '9';
}

#line 757 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_integer_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 758 "bootstrap/stage0/ReCode.code"
    uint64_t value = (uint64_t) 0;
#line 759 "bootstrap/stage0/ReCode.code"
    while (char_is_digit(Scanner__peek_char(self))) {
#line 760 "bootstrap/stage0/ReCode.code"
        char c = Scanner__next_char(self);
#line 761 "bootstrap/stage0/ReCode.code"
        value = value * (uint64_t) 10 + (uint64_t) (c - '0');
#line 762 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, c);
    }
#line 764 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Integer_Token__create(source_location, token_lexeme, value);
}

#line 767 "bootstrap/stage0/ReCode.code"
bool char_is_space(char c) {
#line 768 "bootstrap/stage0/ReCode.code"
    return c == ' ';
}

#line 771 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_space_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 772 "bootstrap/stage0/ReCode.code"
    uint16_t count = (uint16_t) 0;
#line 773 "bootstrap/stage0/ReCode.code"
    while (char_is_space(Scanner__peek_char(self))) {
#line 774 "bootstrap/stage0/ReCode.code"
        count = count + (uint16_t) 1;
#line 775 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
#line 777 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Space_Token__create(source_location, token_lexeme, count);
}

#line 780 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_string_token(struct Scanner* self, struct Source_Location* source_location, struct String* token_lexeme) {
#line 781 "bootstrap/stage0/ReCode.code"
    if (Scanner__next_char(self) != '\"') {
#line 782 "bootstrap/stage0/ReCode.code"
        Source_Location__error(source_location, String__create_from("Unexpected char"));
#line 783 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 785 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, '\"');
#line 787 "bootstrap/stage0/ReCode.code"
    struct String* value = String__create();
#line 789 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 790 "bootstrap/stage0/ReCode.code"
        char next_char = Scanner__peek_char(self);
#line 791 "bootstrap/stage0/ReCode.code"
        if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 792 "bootstrap/stage0/ReCode.code"
            return (struct Token*) Error_Token__create(source_location, token_lexeme);
        }
#line 795 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 797 "bootstrap/stage0/ReCode.code"
        if (next_char == '\"') {
#line 798 "bootstrap/stage0/ReCode.code"
            return (struct Token*) String_Token__create(source_location, token_lexeme, value);
        }
#line 801 "bootstrap/stage0/ReCode.code"
        if (next_char == '\\') {
#line 802 "bootstrap/stage0/ReCode.code"
            next_char = Scanner__peek_char(self);
#line 803 "bootstrap/stage0/ReCode.code"
            if (char_is_end_of_line(next_char) || next_char == '\t') {
#line 804 "bootstrap/stage0/ReCode.code"
                return (struct Token*) Error_Token__create(source_location, token_lexeme);
            }
#line 807 "bootstrap/stage0/ReCode.code"
            String__append_char(token_lexeme, Scanner__next_char(self));
#line 809 "bootstrap/stage0/ReCode.code"
            next_char = escape_char_value(next_char);
#line 810 "bootstrap/stage0/ReCode.code"
            if (next_char == ((char) -1)) {
#line 811 "bootstrap/stage0/ReCode.code"
                return (struct Token*) Error_Token__create(source_location, token_lexeme);
            }
        }
#line 815 "bootstrap/stage0/ReCode.code"
        String__append_char(value, next_char);
    }
}

#line 819 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__scan_token(struct Scanner* self) {
#line 820 "bootstrap/stage0/ReCode.code"
    struct Source_Location* source_location = Source_Location__create(self->source, self->current_line, self->current_column);
#line 821 "bootstrap/stage0/ReCode.code"
    struct String* token_lexeme = String__create();
#line 823 "bootstrap/stage0/ReCode.code"
    char next_char = Scanner__peek_char(self);
#line 825 "bootstrap/stage0/ReCode.code"
    if (char_is_identifier_start(next_char)) {
#line 826 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_identifier_token(self, source_location, token_lexeme);
    }
#line 829 "bootstrap/stage0/ReCode.code"
    if (char_is_digit(next_char)) {
#line 830 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_integer_token(self, source_location, token_lexeme);
    }
#line 833 "bootstrap/stage0/ReCode.code"
    if (char_is_space(next_char)) {
#line 834 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_space_token(self, source_location, token_lexeme);
    }
#line 837 "bootstrap/stage0/ReCode.code"
    if (next_char == '\'') {
#line 838 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_character_token(self, source_location, token_lexeme);
    }
#line 841 "bootstrap/stage0/ReCode.code"
    if (next_char == '\"') {
#line 842 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_string_token(self, source_location, token_lexeme);
    }
#line 845 "bootstrap/stage0/ReCode.code"
    if (next_char == '\\') {
#line 846 "bootstrap/stage0/ReCode.code"
        return Scanner__scan_comment_token(self, source_location, token_lexeme);
    }
#line 849 "bootstrap/stage0/ReCode.code"
    if (next_char == '\n') {
#line 850 "bootstrap/stage0/ReCode.code"
        String__append_char(token_lexeme, Scanner__next_char(self));
#line 851 "bootstrap/stage0/ReCode.code"
        return (struct Token*) End_Of_Line_Token__create(source_location, token_lexeme);
    }
#line 854 "bootstrap/stage0/ReCode.code"
    if (next_char == '\0') {
#line 855 "bootstrap/stage0/ReCode.code"
        return (struct Token*) End_Of_File_Token__create(source_location, token_lexeme);
    }
#line 858 "bootstrap/stage0/ReCode.code"
    String__append_char(token_lexeme, Scanner__next_char(self));
#line 859 "bootstrap/stage0/ReCode.code"
    return (struct Token*) Other_Token__create(source_location, token_lexeme);
}

#line 862 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__next_token(struct Scanner* self) {
#line 863 "bootstrap/stage0/ReCode.code"
    if (self->current_token->next_token == NULL) {
#line 864 "bootstrap/stage0/ReCode.code"
        self->current_token->next_token = Scanner__scan_token(self);
    }
#line 866 "bootstrap/stage0/ReCode.code"
    self->current_token = self->current_token->next_token;
#line 867 "bootstrap/stage0/ReCode.code"
    return self->current_token;
}

#line 870 "bootstrap/stage0/ReCode.code"
struct Token* Scanner__peek_token(struct Scanner* self, uint8_t offset) {
#line 871 "bootstrap/stage0/ReCode.code"
    struct Token* token = self->current_token;
#line 872 "bootstrap/stage0/ReCode.code"
    while (offset > (uint8_t) 0) {
#line 873 "bootstrap/stage0/ReCode.code"
        if (token->next_token == NULL) {
#line 874 "bootstrap/stage0/ReCode.code"
            token->next_token = Scanner__scan_token(self);
        }
#line 876 "bootstrap/stage0/ReCode.code"
        token = token->next_token;
#line 877 "bootstrap/stage0/ReCode.code"
        offset = offset - (uint8_t) 1;
    }
#line 879 "bootstrap/stage0/ReCode.code"
    return token;
}

#line 882 "bootstrap/stage0/ReCode.code"
struct Scanner* Scanner__create(struct Source* source) {
#line 883 "bootstrap/stage0/ReCode.code"
    struct Scanner* scanner = (struct Scanner*) malloc(sizeof(struct Scanner));
#line 884 "bootstrap/stage0/ReCode.code"
    scanner->source = source;
#line 885 "bootstrap/stage0/ReCode.code"
    scanner->current_char_index = (size_t) 0;
#line 886 "bootstrap/stage0/ReCode.code"
    scanner->current_line = (uint16_t) 1;
#line 887 "bootstrap/stage0/ReCode.code"
    scanner->current_column = (uint16_t) 1;
#line 889 "bootstrap/stage0/ReCode.code"
    scanner->current_token = Scanner__scan_token(scanner);
#line 891 "bootstrap/stage0/ReCode.code"
    return scanner;
}

#line 913 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Type__create_kind(enum Parsed_Type_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 914 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = (struct Parsed_Type*) malloc(kind_size);
#line 915 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 916 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 917 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 925 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Named_Type__create(struct Token* name) {
#line 926 "bootstrap/stage0/ReCode.code"
    struct Parsed_Named_Type* type = (struct Parsed_Named_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__NAMED, sizeof(struct Parsed_Named_Type), name->location);
#line 927 "bootstrap/stage0/ReCode.code"
    type->name = name->lexeme;
#line 928 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Type*) type;
}

#line 936 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Pointer_Type__create(struct Parsed_Type* other_type) {
#line 937 "bootstrap/stage0/ReCode.code"
    struct Parsed_Pointer_Type* type = (struct Parsed_Pointer_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__POINTER, sizeof(struct Parsed_Pointer_Type), other_type->location);
#line 938 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 939 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Type*) type;
}

#line 947 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parsed_Struct_Type__create(struct Source_Location* location, struct Parsed_Type* other_type) {
#line 948 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Type* type = (struct Parsed_Struct_Type*) Parsed_Type__create_kind(Parsed_Type_Kind__STRUCT, sizeof(struct Parsed_Struct_Type), location);
#line 949 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 950 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Type*) type;
}

#line 990 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parsed_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 991 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = (struct Parsed_Expression*) malloc(kind_size);
#line 992 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 993 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 994 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1003 "bootstrap/stage0/ReCode.code"
struct Parsed_Binary_Expression* Parsed_Binary_Expression__create_kind(enum Parsed_Expression_Kind kind, struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1004 "bootstrap/stage0/ReCode.code"
    struct Parsed_Binary_Expression* expression = (struct Parsed_Binary_Expression*) Parsed_Expression__create_kind(kind, sizeof(struct Parsed_Binary_Expression), left_expression->location);
#line 1005 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 1006 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 1007 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1015 "bootstrap/stage0/ReCode.code"
struct Parsed_Unary_Expression* Parsed_Unary_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1016 "bootstrap/stage0/ReCode.code"
    struct Parsed_Unary_Expression* expression = (struct Parsed_Unary_Expression*) Parsed_Expression__create_kind(kind, kind_size, location);
#line 1017 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1018 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1026 "bootstrap/stage0/ReCode.code"
struct Parsed_Literal_Expression* Parsed_Literal_Expression__create_kind(enum Parsed_Expression_Kind kind, size_t kind_size, struct Token* literal) {
#line 1027 "bootstrap/stage0/ReCode.code"
    struct Parsed_Literal_Expression* expression = (struct Parsed_Literal_Expression*) Parsed_Expression__create_kind(kind, kind_size, literal->location);
#line 1028 "bootstrap/stage0/ReCode.code"
    expression->literal = literal;
#line 1029 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1036 "bootstrap/stage0/ReCode.code"
struct Parsed_Add_Expression* Parsed_Add_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1037 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Add_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__ADD, left_expression, right_expression);
}

#line 1044 "bootstrap/stage0/ReCode.code"
struct Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1045 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Address_Of_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__ADDRESS_OF, sizeof(struct Parsed_Address_Of_Expression), location, other_expression);
}

#line 1054 "bootstrap/stage0/ReCode.code"
struct Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(struct Parsed_Expression* array_expression, struct Parsed_Expression* index_expression) {
#line 1055 "bootstrap/stage0/ReCode.code"
    struct Parsed_Array_Access_Expression* expression = (struct Parsed_Array_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__ARRAY_ACCESS, sizeof(struct Parsed_Array_Access_Expression), array_expression->location);
#line 1056 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 1057 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 1058 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1066 "bootstrap/stage0/ReCode.code"
struct Parsed_Bool_Expression* Parsed_Bool_Expression__create(struct Token* literal, bool value) {
#line 1067 "bootstrap/stage0/ReCode.code"
    struct Parsed_Bool_Expression* expression = (struct Parsed_Bool_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__BOOL, sizeof(struct Parsed_Bool_Expression), literal);
#line 1068 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 1069 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1077 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Argument* Parsed_Call_Argument__create(struct Parsed_Expression* expression) {
#line 1078 "bootstrap/stage0/ReCode.code"
    struct Parsed_Call_Argument* argument = (struct Parsed_Call_Argument*) malloc(sizeof(struct Parsed_Call_Argument));
#line 1079 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 1080 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 1081 "bootstrap/stage0/ReCode.code"
    return argument;
}

#line 1090 "bootstrap/stage0/ReCode.code"
struct Parsed_Call_Expression* Parsed_Call_Expression__create(struct Parsed_Expression* callee_expression) {
#line 1091 "bootstrap/stage0/ReCode.code"
    struct Parsed_Call_Expression* expression = (struct Parsed_Call_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__CALL, sizeof(struct Parsed_Call_Expression), callee_expression->location);
#line 1092 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 1093 "bootstrap/stage0/ReCode.code"
    expression->first_argument = NULL;
#line 1094 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1102 "bootstrap/stage0/ReCode.code"
struct Parsed_Cast_Expression* Parsed_Cast_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression, struct Parsed_Type* type) {
#line 1103 "bootstrap/stage0/ReCode.code"
    struct Parsed_Cast_Expression* expression = (struct Parsed_Cast_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__CAST, sizeof(struct Parsed_Cast_Expression), location, other_expression);
#line 1104 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1105 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1113 "bootstrap/stage0/ReCode.code"
struct Parsed_Character_Expression* Parsed_Character_Expression__create(struct Character_Token* literal) {
#line 1114 "bootstrap/stage0/ReCode.code"
    struct Parsed_Character_Expression* expression = (struct Parsed_Character_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__CHARACTER, sizeof(struct Parsed_Character_Expression), (struct Token*) literal);
#line 1115 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1116 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1124 "bootstrap/stage0/ReCode.code"
struct Parsed_Dereference_Expression* Parsed_Dereference_Expression__create(struct Parsed_Expression* value_expression) {
#line 1125 "bootstrap/stage0/ReCode.code"
    struct Parsed_Dereference_Expression* expression = (struct Parsed_Dereference_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__DEREFERENCE, sizeof(struct Parsed_Dereference_Expression), value_expression->location);
#line 1126 "bootstrap/stage0/ReCode.code"
    expression->value_expression = value_expression;
#line 1127 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1134 "bootstrap/stage0/ReCode.code"
struct Parsed_Divide_Expression* Parsed_Divide_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1135 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Divide_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__DIVIDE, left_expression, right_expression);
}

#line 1142 "bootstrap/stage0/ReCode.code"
struct Parsed_Equals_Expression* Parsed_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1143 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__EQUALS, left_expression, right_expression);
}

#line 1150 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Expression* Parsed_Greater_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1151 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Greater_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER, left_expression, right_expression);
}

#line 1158 "bootstrap/stage0/ReCode.code"
struct Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1159 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Greater_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__GREATER_OR_EQUALS, left_expression, right_expression);
}

#line 1167 "bootstrap/stage0/ReCode.code"
struct Parsed_Group_Expression* Parsed_Group_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1168 "bootstrap/stage0/ReCode.code"
    struct Parsed_Group_Expression* expression = (struct Parsed_Group_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__GROUP, sizeof(struct Parsed_Group_Expression), location);
#line 1169 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 1170 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1178 "bootstrap/stage0/ReCode.code"
struct Parsed_Integer_Expression* Parsed_Integer_Expression__create(struct Integer_Token* literal) {
#line 1179 "bootstrap/stage0/ReCode.code"
    struct Parsed_Integer_Expression* expression = (struct Parsed_Integer_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__INTEGER, sizeof(struct Parsed_Integer_Expression), (struct Token*) literal);
#line 1180 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1181 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1188 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Expression* Parsed_Less_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1189 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Less_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS, left_expression, right_expression);
}

#line 1196 "bootstrap/stage0/ReCode.code"
struct Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1197 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Less_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LESS_OR_EQUALS, left_expression, right_expression);
}

#line 1204 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1205 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Logic_And_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_AND, left_expression, right_expression);
}

#line 1212 "bootstrap/stage0/ReCode.code"
struct Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1213 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Logic_Or_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__LOGIC_OR, left_expression, right_expression);
}

#line 1222 "bootstrap/stage0/ReCode.code"
struct Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(struct Parsed_Expression* object_expression, struct Token* member_name) {
#line 1223 "bootstrap/stage0/ReCode.code"
    struct Parsed_Member_Access_Expression* expression = (struct Parsed_Member_Access_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__MEMBER_ACCESS, sizeof(struct Parsed_Member_Access_Expression), object_expression->location);
#line 1224 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 1225 "bootstrap/stage0/ReCode.code"
    expression->member_name = member_name;
#line 1226 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1233 "bootstrap/stage0/ReCode.code"
struct Parsed_Minus_Expression* Parsed_Minus_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1234 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Minus_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__MINUS, sizeof(struct Parsed_Minus_Expression), location, other_expression);
}

#line 1241 "bootstrap/stage0/ReCode.code"
struct Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1242 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Modulo_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MODULO, left_expression, right_expression);
}

#line 1249 "bootstrap/stage0/ReCode.code"
struct Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1250 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Multiply_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__MULTIPLY, left_expression, right_expression);
}

#line 1257 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Expression* Parsed_Not_Expression__create(struct Source_Location* location, struct Parsed_Expression* other_expression) {
#line 1258 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Not_Expression*) Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind__NOT, sizeof(struct Parsed_Not_Expression), location, other_expression);
}

#line 1265 "bootstrap/stage0/ReCode.code"
struct Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1266 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Not_Equals_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__NOT_EQUALS, left_expression, right_expression);
}

#line 1273 "bootstrap/stage0/ReCode.code"
struct Parsed_Null_Expression* Parsed_Null_Expression__create(struct Token* literal) {
#line 1274 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Null_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__NULL, sizeof(struct Parsed_Null_Expression), literal);
}

#line 1282 "bootstrap/stage0/ReCode.code"
struct Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(struct Source_Location* location, struct Parsed_Type* type) {
#line 1283 "bootstrap/stage0/ReCode.code"
    struct Parsed_Sizeof_Expression* expression = (struct Parsed_Sizeof_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SIZEOF, sizeof(struct Parsed_Sizeof_Expression), location);
#line 1284 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 1285 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1293 "bootstrap/stage0/ReCode.code"
struct Parsed_String_Expression* Parsed_String_Expression__create(struct String_Token* literal) {
#line 1294 "bootstrap/stage0/ReCode.code"
    struct Parsed_String_Expression* expression = (struct Parsed_String_Expression*) Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind__STRING, sizeof(struct Parsed_String_Expression), (struct Token*) literal);
#line 1295 "bootstrap/stage0/ReCode.code"
    expression->value = literal->value;
#line 1296 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1303 "bootstrap/stage0/ReCode.code"
struct Parsed_Substract_Expression* Parsed_Substract_Expression__create(struct Parsed_Expression* left_expression, struct Parsed_Expression* right_expression) {
#line 1304 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Substract_Expression*) Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind__SUBSTRACT, left_expression, right_expression);
}

#line 1312 "bootstrap/stage0/ReCode.code"
struct Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(struct Token* name) {
#line 1313 "bootstrap/stage0/ReCode.code"
    struct Parsed_Symbol_Expression* expression = (struct Parsed_Symbol_Expression*) Parsed_Expression__create_kind(Parsed_Expression_Kind__SYMBOL, sizeof(struct Parsed_Symbol_Expression), name->location);
#line 1314 "bootstrap/stage0/ReCode.code"
    expression->name = name;
#line 1315 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1340 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 1341 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* statement = (struct Parsed_Statement*) malloc(kind_size);
#line 1342 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 1343 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 1344 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 1345 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1353 "bootstrap/stage0/ReCode.code"
struct Parsed_Named_Statement* Parsed_Named_Statement__create_kind(enum Parsed_Statement_Kind kind, size_t kind_size, struct Source_Location* location, struct Token* name) {
#line 1354 "bootstrap/stage0/ReCode.code"
    struct Parsed_Named_Statement* statement = (struct Parsed_Named_Statement*) Parsed_Statement__create_kind(kind, kind_size, location);
#line 1355 "bootstrap/stage0/ReCode.code"
    statement->name = name;
#line 1356 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1365 "bootstrap/stage0/ReCode.code"
struct Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(struct Parsed_Expression* object_expression, struct Parsed_Expression* value_expression) {
#line 1366 "bootstrap/stage0/ReCode.code"
    struct Parsed_Assignment_Statement* statement = (struct Parsed_Assignment_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__ASSIGNMENT, sizeof(struct Parsed_Assignment_Statement), object_expression->location);
#line 1367 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 1368 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 1369 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1377 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parsed_Block_Statement__create(struct Source_Location* location, struct Parsed_Statements* statements) {
#line 1378 "bootstrap/stage0/ReCode.code"
    struct Parsed_Block_Statement* statement = (struct Parsed_Block_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__BLOCK, sizeof(struct Parsed_Block_Statement), location);
#line 1379 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1380 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1387 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Break_Statement__create(struct Source_Location* location) {
#line 1388 "bootstrap/stage0/ReCode.code"
    return Parsed_Statement__create_kind(Parsed_Statement_Kind__BREAK, sizeof(struct Parsed_Break_Statement), location);
}

#line 1396 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Member* Parsed_Enum_Member__create(struct Token* name) {
#line 1397 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Member* member = (struct Parsed_Enum_Member*) malloc(sizeof(struct Parsed_Enum_Member));
#line 1398 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1399 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1400 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 1408 "bootstrap/stage0/ReCode.code"
struct Parsed_Enum_Statement* Parsed_Enum_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1409 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Statement* statement = (struct Parsed_Enum_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__ENUM, sizeof(struct Parsed_Enum_Statement), location, name);
#line 1410 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1411 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1419 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression_Statement* Parsed_Expression_Statement__create(struct Parsed_Expression* expression) {
#line 1420 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression_Statement* statement = (struct Parsed_Expression_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__EXPRESSION, sizeof(struct Parsed_Expression_Statement), expression->location);
#line 1421 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1422 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1431 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parsed_Function_Parameter__create(struct Token* name, struct Parsed_Type* type) {
#line 1432 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* parameter = (struct Parsed_Function_Parameter*) malloc(sizeof(struct Parsed_Function_Parameter));
#line 1433 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 1434 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 1435 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 1436 "bootstrap/stage0/ReCode.code"
    return parameter;
}

#line 1447 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Function_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Parameter* first_parameter, struct Parsed_Type* resturn_type, struct Parsed_Statements* statements, bool is_external) {
#line 1448 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Statement* statement = (struct Parsed_Function_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__FUNCTION, sizeof(struct Parsed_Function_Statement), location, name);
#line 1449 "bootstrap/stage0/ReCode.code"
    statement->first_parameter = first_parameter;
#line 1450 "bootstrap/stage0/ReCode.code"
    statement->return_type = resturn_type;
#line 1451 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 1452 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1453 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1462 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Type_Parameter* Parsed_Function_Type_Parameter__create(struct Token* name, struct Parsed_Type* type) {
#line 1463 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Type_Parameter* parameter = (struct Parsed_Function_Type_Parameter*) malloc(sizeof(struct Parsed_Function_Type_Parameter));
#line 1464 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 1465 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 1466 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 1467 "bootstrap/stage0/ReCode.code"
    return parameter;
}

#line 1476 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Function_Type_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Function_Type_Parameter* first_parameter, struct Parsed_Type* resturn_type) {
#line 1477 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Type_Statement* statement = (struct Parsed_Function_Type_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__FUNCTION_TYPE, sizeof(struct Parsed_Function_Type_Statement), location, name);
#line 1478 "bootstrap/stage0/ReCode.code"
    statement->first_parameter = first_parameter;
#line 1479 "bootstrap/stage0/ReCode.code"
    statement->return_type = resturn_type;
#line 1480 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1490 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_If_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* true_statement, struct Parsed_Statement* false_statement) {
#line 1491 "bootstrap/stage0/ReCode.code"
    struct Parsed_If_Statement* statement = (struct Parsed_If_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__IF, sizeof(struct Parsed_If_Statement), location);
#line 1492 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1493 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 1494 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 1495 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1502 "bootstrap/stage0/ReCode.code"
struct Parsed_Opaque_Type_Statement* Parsed_Opaque_Type_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1503 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Opaque_Type_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__OPAQUE_TYPE, sizeof(struct Parsed_Opaque_Type_Statement), location, name);
}

#line 1511 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_Return_Statement__create(struct Source_Location* location, struct Parsed_Expression* expression) {
#line 1512 "bootstrap/stage0/ReCode.code"
    struct Parsed_Return_Statement* statement = (struct Parsed_Return_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__RETURN, sizeof(struct Parsed_Return_Statement), location);
#line 1513 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 1514 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1523 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Member* Parsed_Struct_Member__create(struct Token* name, struct Parsed_Type* type) {
#line 1524 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Member* member = (struct Parsed_Struct_Member*) malloc(sizeof(struct Parsed_Struct_Member));
#line 1525 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 1526 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 1527 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 1528 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 1536 "bootstrap/stage0/ReCode.code"
struct Parsed_Struct_Statement* Parsed_Struct_Statement__create(struct Source_Location* location, struct Token* name) {
#line 1537 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Statement* statement = (struct Parsed_Struct_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__STRUCT, sizeof(struct Parsed_Struct_Statement), location, name);
#line 1538 "bootstrap/stage0/ReCode.code"
    statement->first_member = NULL;
#line 1539 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1549 "bootstrap/stage0/ReCode.code"
struct Parsed_Variable_Statement* Parsed_Variable_Statement__create(struct Source_Location* location, struct Token* name, struct Parsed_Type* type, bool is_external) {
#line 1550 "bootstrap/stage0/ReCode.code"
    struct Parsed_Variable_Statement* statement = (struct Parsed_Variable_Statement*) Parsed_Named_Statement__create_kind(Parsed_Statement_Kind__VARIABLE, sizeof(struct Parsed_Variable_Statement), location, name);
#line 1551 "bootstrap/stage0/ReCode.code"
    statement->type = type;
#line 1552 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 1553 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 1562 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parsed_While_Statement__create(struct Source_Location* location, struct Parsed_Expression* condition_expression, struct Parsed_Statement* body_statement) {
#line 1563 "bootstrap/stage0/ReCode.code"
    struct Parsed_While_Statement* statement = (struct Parsed_While_Statement*) Parsed_Statement__create_kind(Parsed_Statement_Kind__WHILE, sizeof(struct Parsed_While_Statement), location);
#line 1564 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 1565 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 1566 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) statement;
}

#line 1575 "bootstrap/stage0/ReCode.code"
struct Parsed_Statements* Parsed_Statements__create(bool has_globals) {
#line 1576 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statements* statements = (struct Parsed_Statements*) malloc(sizeof(struct Parsed_Statements));
#line 1577 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 1578 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 1579 "bootstrap/stage0/ReCode.code"
    statements->has_globals = has_globals;
#line 1580 "bootstrap/stage0/ReCode.code"
    return statements;
}

#line 1583 "bootstrap/stage0/ReCode.code"
void Parsed_Statements__append(struct Parsed_Statements* self, struct Parsed_Statement* statement) {
#line 1584 "bootstrap/stage0/ReCode.code"
    if (self->first_statement == NULL) {
#line 1585 "bootstrap/stage0/ReCode.code"
        self->first_statement = statement;
    } else {
#line 1587 "bootstrap/stage0/ReCode.code"
        self->last_statement->next_statement = statement;
    }
#line 1589 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;
}

#line 1592 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* Parsed_Compilation_Unit__create() {
#line 1593 "bootstrap/stage0/ReCode.code"
    struct Parsed_Source* compilation_unit = (struct Parsed_Source*) malloc(sizeof(struct Parsed_Source));
#line 1594 "bootstrap/stage0/ReCode.code"
    compilation_unit->statements = Parsed_Statements__create(true);
#line 1595 "bootstrap/stage0/ReCode.code"
    return compilation_unit;
}

#line 1608 "bootstrap/stage0/ReCode.code"
void Parser__error(struct Parser* self, struct String* message) {
#line 1609 "bootstrap/stage0/ReCode.code"
    Token__error(self->scanner->current_token, message);
}

#line 1612 "bootstrap/stage0/ReCode.code"
void Parser__warning(struct Parser* self, struct String* message) {
#line 1613 "bootstrap/stage0/ReCode.code"
    Token__warning(self->scanner->current_token, message);
}

#line 1616 "bootstrap/stage0/ReCode.code"
struct Token* Parser__peek_token(struct Parser* self, uint8_t offset) {
#line 1617 "bootstrap/stage0/ReCode.code"
    return Scanner__peek_token(self->scanner, offset);
}

#line 1622 "bootstrap/stage0/ReCode.code"
bool Parser__matches_three(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self), bool second_required, bool (*third_is)(struct Token* self)) {
#line 1623 "bootstrap/stage0/ReCode.code"
    uint8_t peek_offset = (uint8_t) 0;
#line 1624 "bootstrap/stage0/ReCode.code"
    if (first_is(Parser__peek_token(self, peek_offset))) {
#line 1625 "bootstrap/stage0/ReCode.code"
        peek_offset = peek_offset + (uint8_t) 1;
    } else if (first_required) {
#line 1627 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 1629 "bootstrap/stage0/ReCode.code"
    if (second_is != NULL) {
#line 1630 "bootstrap/stage0/ReCode.code"
        if (second_is(Parser__peek_token(self, peek_offset))) {
#line 1631 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
        } else if (second_required) {
#line 1633 "bootstrap/stage0/ReCode.code"
            return false;
        }
    }
#line 1636 "bootstrap/stage0/ReCode.code"
    if (third_is != NULL) {
#line 1637 "bootstrap/stage0/ReCode.code"
        return third_is(Parser__peek_token(self, peek_offset));
    }
#line 1639 "bootstrap/stage0/ReCode.code"
    return true;
}

#line 1642 "bootstrap/stage0/ReCode.code"
bool Parser__matches_two(struct Parser* self, bool (*first_is)(struct Token* self), bool first_required, bool (*second_is)(struct Token* self)) {
#line 1643 "bootstrap/stage0/ReCode.code"
    return Parser__matches_three(self, first_is, first_required, second_is, true, NULL);
}

#line 1646 "bootstrap/stage0/ReCode.code"
bool Parser__matches_one(struct Parser* self, bool (*first_is)(struct Token* self)) {
#line 1647 "bootstrap/stage0/ReCode.code"
    return Parser__matches_two(self, first_is, true, NULL);
}

#line 1650 "bootstrap/stage0/ReCode.code"
struct Token* Parser__consume_token(struct Parser* self, bool (*check)(struct Token* self)) {
#line 1651 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, check)) {
#line 1652 "bootstrap/stage0/ReCode.code"
        struct Token* token = self->scanner->current_token;
#line 1653 "bootstrap/stage0/ReCode.code"
        Scanner__next_token(self->scanner);
#line 1654 "bootstrap/stage0/ReCode.code"
        return token;
    }
#line 1656 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unexpected token"));
#line 1657 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 1660 "bootstrap/stage0/ReCode.code"
void Parser__consume_comment(struct Parser* self) {
#line 1661 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_comment);
}

#line 1664 "bootstrap/stage0/ReCode.code"
void Parser__consume_space(struct Parser* self, uint16_t count) {
#line 1665 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_space)) {
#line 1666 "bootstrap/stage0/ReCode.code"
        struct Space_Token* token = (struct Space_Token*) Parser__consume_token(self, Token__is_space);
#line 1667 "bootstrap/stage0/ReCode.code"
        if (token->count != count) {
#line 1668 "bootstrap/stage0/ReCode.code"
            struct String* message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), (int16_t) token->count), " spaces where "), (int16_t) count), " were expected");
#line 1669 "bootstrap/stage0/ReCode.code"
            Token__warning((struct Token*) token, message);
#line 1670 "bootstrap/stage0/ReCode.code"
            String__delete(message);
        }
    } else if (count > (uint16_t) 0) {
#line 1673 "bootstrap/stage0/ReCode.code"
        struct String* message = String__append_cstring(String__append_i16(String__append_cstring(String__append_i16(String__create_from("Consumed "), (int16_t) 0), " spaces where "), (int16_t) count), " were expected");
#line 1674 "bootstrap/stage0/ReCode.code"
        Parser__warning(self, message);
#line 1675 "bootstrap/stage0/ReCode.code"
        String__delete(message);
    }
}

#line 1679 "bootstrap/stage0/ReCode.code"
void Parser__consume_end_of_line(struct Parser* self) {
#line 1680 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1681 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1682 "bootstrap/stage0/ReCode.code"
        Parser__consume_comment(self);
    } else {
#line 1684 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
    }
#line 1686 "bootstrap/stage0/ReCode.code"
    struct Token* token = Parser__consume_token(self, Token__is_end_of_line);
#line 1687 "bootstrap/stage0/ReCode.code"
    if (Token__is_end_of_file(token)) {
#line 1688 "bootstrap/stage0/ReCode.code"
        Token__warning(token, String__create_from("Unexpected end of file"));
    }
}

#line 1692 "bootstrap/stage0/ReCode.code"
bool Parser__consume_empty_line(struct Parser* self) {
#line 1693 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_end_of_file)) {
#line 1694 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 1696 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 1697 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
#line 1698 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 1699 "bootstrap/stage0/ReCode.code"
            Parser__consume_comment(self);
        } else {
#line 1701 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
        }
#line 1703 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_end_of_line);
#line 1704 "bootstrap/stage0/ReCode.code"
        return true;
    }
#line 1706 "bootstrap/stage0/ReCode.code"
    return false;
}

#line 1717 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_primary_expression(struct Parser* self) {
#line 1718 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_true)) {
#line 1719 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true);
    }
#line 1721 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_null)) {
#line 1722 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null));
    }
#line 1724 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_false)) {
#line 1725 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false);
    }
#line 1727 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_identifier)) {
#line 1728 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier));
    }
#line 1730 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_integer)) {
#line 1731 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Integer_Expression__create((struct Integer_Token*) Parser__consume_token(self, Token__is_integer));
    }
#line 1733 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_character)) {
#line 1734 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Character_Expression__create((struct Character_Token*) Parser__consume_token(self, Token__is_character));
    }
#line 1736 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_string)) {
#line 1737 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_String_Expression__create((struct String_Token*) Parser__consume_token(self, Token__is_string));
    }
#line 1739 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_opening_paren)) {
#line 1740 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1741 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1742 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_expression(self);
#line 1743 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1744 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_closing_paren);
#line 1745 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Group_Expression__create(location, expression);
    }
#line 1747 "bootstrap/stage0/ReCode.code"
    Parser__error(self, String__create_from("Unsupported primary expression"));
#line 1748 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 1753 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_access_expression(struct Parser* self) {
#line 1754 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_primary_expression(self);
#line 1755 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 1756 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* old_expression = expression;
#line 1757 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_dot)) {
#line 1758 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1759 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_dot);
#line 1760 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1761 "bootstrap/stage0/ReCode.code"
            if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1762 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_asterisk);
#line 1763 "bootstrap/stage0/ReCode.code"
                expression = (struct Parsed_Expression*) Parsed_Dereference_Expression__create(expression);
            } else {
#line 1765 "bootstrap/stage0/ReCode.code"
                struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 1766 "bootstrap/stage0/ReCode.code"
                expression = (struct Parsed_Expression*) Parsed_Member_Access_Expression__create(expression, name);
            }
        }
#line 1769 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
#line 1770 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1771 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_opening_paren);
#line 1772 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1773 "bootstrap/stage0/ReCode.code"
            struct Parsed_Call_Expression* call_expression = Parsed_Call_Expression__create(expression);
#line 1774 "bootstrap/stage0/ReCode.code"
            if (!Parser__matches_one(self, Token__is_closing_paren)) {
#line 1775 "bootstrap/stage0/ReCode.code"
                struct Parsed_Call_Argument* last_argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1776 "bootstrap/stage0/ReCode.code"
                call_expression->first_argument = last_argument;
#line 1777 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 0);
#line 1778 "bootstrap/stage0/ReCode.code"
                while (Parser__matches_one(self, Token__is_comma)) {
#line 1779 "bootstrap/stage0/ReCode.code"
                    Parser__consume_token(self, Token__is_comma);
#line 1780 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, (uint16_t) 1);
#line 1781 "bootstrap/stage0/ReCode.code"
                    struct Parsed_Call_Argument* argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
#line 1782 "bootstrap/stage0/ReCode.code"
                    last_argument->next_argument = argument;
#line 1783 "bootstrap/stage0/ReCode.code"
                    last_argument = argument;
#line 1784 "bootstrap/stage0/ReCode.code"
                    Parser__consume_space(self, (uint16_t) 0);
                }
            }
#line 1787 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) call_expression;
#line 1788 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_closing_paren);
        }
#line 1790 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
#line 1791 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1792 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_opening_bracket);
#line 1793 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1794 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* index_expression = Parser__parse_expression(self);
#line 1795 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 1796 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_closing_bracket);
#line 1797 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Array_Access_Expression__create(expression, index_expression);
        }
#line 1799 "bootstrap/stage0/ReCode.code"
        if (old_expression == expression) {
#line 1800 "bootstrap/stage0/ReCode.code"
            break;
        }
    }
#line 1803 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1813 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_unary_expression(struct Parser* self) {
#line 1814 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_minus)) {
#line 1815 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_minus)->location;
#line 1816 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1817 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1818 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Minus_Expression__create(location, expression);
    }
#line 1820 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_exclamation_mark)) {
#line 1821 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_exclamation_mark)->location;
#line 1822 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1823 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1824 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Not_Expression__create(location, expression);
    }
#line 1826 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_ampersand)) {
#line 1827 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_ampersand)->location;
#line 1828 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1829 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1830 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Address_Of_Expression__create(location, expression);
    }
#line 1832 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_three(self, Token__is_opening_paren, true, Token__is_space, false, Token__is_identifier)) {
#line 1833 "bootstrap/stage0/ReCode.code"
        uint8_t peek_offset = (uint8_t) 1;
#line 1834 "bootstrap/stage0/ReCode.code"
        if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1835 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
        }
#line 1837 "bootstrap/stage0/ReCode.code"
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
#line 1838 "bootstrap/stage0/ReCode.code"
            peek_offset = peek_offset + (uint8_t) 1;
#line 1839 "bootstrap/stage0/ReCode.code"
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1840 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
            }
#line 1842 "bootstrap/stage0/ReCode.code"
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
#line 1843 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
#line 1844 "bootstrap/stage0/ReCode.code"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1845 "bootstrap/stage0/ReCode.code"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
            }
#line 1848 "bootstrap/stage0/ReCode.code"
            if (Token__is_closing_paren(Parser__peek_token(self, peek_offset))) {
#line 1849 "bootstrap/stage0/ReCode.code"
                peek_offset = peek_offset + (uint8_t) 1;
#line 1850 "bootstrap/stage0/ReCode.code"
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
#line 1851 "bootstrap/stage0/ReCode.code"
                    peek_offset = peek_offset + (uint8_t) 1;
                }
#line 1853 "bootstrap/stage0/ReCode.code"
                struct Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
#line 1854 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 0);
#line 1855 "bootstrap/stage0/ReCode.code"
                struct Parsed_Type* type = Parser__parse_type(self);
#line 1856 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 0);
#line 1857 "bootstrap/stage0/ReCode.code"
                Parser__consume_token(self, Token__is_closing_paren);
#line 1858 "bootstrap/stage0/ReCode.code"
                Parser__consume_space(self, (uint16_t) 1);
#line 1859 "bootstrap/stage0/ReCode.code"
                struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1860 "bootstrap/stage0/ReCode.code"
                return (struct Parsed_Expression*) Parsed_Cast_Expression__create(location, expression, type);
            }
        }
    }
#line 1864 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_sizeof)) {
#line 1865 "bootstrap/stage0/ReCode.code"
        struct Source_Location* location = Parser__consume_token(self, Token__is_sizeof)->location;
#line 1866 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1867 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_opening_paren);
#line 1868 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1869 "bootstrap/stage0/ReCode.code"
        struct Parsed_Type* type = Parser__parse_type(self);
#line 1870 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 1871 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_closing_paren);
#line 1872 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Expression*) Parsed_Sizeof_Expression__create(location, type);
    }
#line 1874 "bootstrap/stage0/ReCode.code"
    return Parser__parse_access_expression(self);
}

#line 1877 "bootstrap/stage0/ReCode.code"
bool Token__is_mutliplication(struct Token* self) {
#line 1878 "bootstrap/stage0/ReCode.code"
    return Token__is_asterisk(self) || Token__is_slash(self) || Token__is_percent(self);
}

#line 1883 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_multiplication_expression(struct Parser* self) {
#line 1884 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_unary_expression(self);
#line 1885 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
#line 1886 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1887 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_asterisk)) {
#line 1888 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_asterisk);
#line 1889 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1890 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1891 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Multiply_Expression__create(expression, right_expression);
        } else if (Parser__matches_one(self, Token__is_slash)) {
#line 1893 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_slash);
#line 1894 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1895 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1896 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Divide_Expression__create(expression, right_expression);
        } else {
#line 1898 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_percent);
#line 1899 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1900 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
#line 1901 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Modulo_Expression__create(expression, right_expression);
        }
    }
#line 1904 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1907 "bootstrap/stage0/ReCode.code"
bool Token__is_addition(struct Token* self) {
#line 1908 "bootstrap/stage0/ReCode.code"
    return Token__is_plus(self) || Token__is_minus(self);
}

#line 1913 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_addition_expression(struct Parser* self) {
#line 1914 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_multiplication_expression(self);
#line 1915 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
#line 1916 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1917 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_plus)) {
#line 1918 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_plus);
#line 1919 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1920 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
#line 1921 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Add_Expression__create(expression, right_expression);
        } else {
#line 1923 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_minus);
#line 1924 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1925 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
#line 1926 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Substract_Expression__create(expression, right_expression);
        }
    }
#line 1929 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1934 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_comparison_expression(struct Parser* self) {
#line 1935 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_addition_expression(self);
#line 1936 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
#line 1937 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1938 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_less_than);
#line 1939 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_equals)) {
#line 1940 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_equals);
#line 1941 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1942 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1943 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
#line 1945 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1946 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1947 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
#line 1950 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1951 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_greater_than);
#line 1952 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_equals)) {
#line 1953 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_equals);
#line 1954 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1955 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1956 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
#line 1958 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 1959 "bootstrap/stage0/ReCode.code"
            struct Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
#line 1960 "bootstrap/stage0/ReCode.code"
            expression = (struct Parsed_Expression*) Parsed_Greater_Expression__create(expression, right_expression);
        }
    }
#line 1963 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1968 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_equality_expression(struct Parser* self) {
#line 1969 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_comparison_expression(self);
#line 1970 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
#line 1971 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1972 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 1973 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 1974 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1975 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
#line 1976 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Equals_Expression__create(expression, right_expression);
    } else if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
#line 1978 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1979 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_exclamation_mark);
#line 1980 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 1981 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1982 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
#line 1983 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Not_Equals_Expression__create(expression, right_expression);
    }
#line 1985 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 1990 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_and_expression(struct Parser* self) {
#line 1991 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_equality_expression(self);
#line 1992 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_ampersand, true, Token__is_ampersand)) {
#line 1993 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1994 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1995 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_ampersand);
#line 1996 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 1997 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_equality_expression(self);
#line 1998 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Logic_And_Expression__create(expression, right_expression);
    }
#line 2000 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 2005 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_logic_or_expression(struct Parser* self) {
#line 2006 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_logic_and_expression(self);
#line 2007 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_three(self, Token__is_space, false, Token__is_vertical_bar, true, Token__is_vertical_bar)) {
#line 2008 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2009 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 2010 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_vertical_bar);
#line 2011 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2012 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* right_expression = Parser__parse_logic_and_expression(self);
#line 2013 "bootstrap/stage0/ReCode.code"
        expression = (struct Parsed_Expression*) Parsed_Logic_Or_Expression__create(expression, right_expression);
    }
#line 2015 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 2020 "bootstrap/stage0/ReCode.code"
struct Parsed_Expression* Parser__parse_expression(struct Parser* self) {
#line 2021 "bootstrap/stage0/ReCode.code"
    return Parser__parse_logic_or_expression(self);
}

#line 2026 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_opaque_type(struct Parser* self, struct Token* name) {
#line 2027 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opaque);
#line 2028 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2029 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_type);
#line 2030 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) Parsed_Opaque_Type_Statement__create(name->location, name);
}

#line 2035 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_struct(struct Parser* self, struct Token* name) {
#line 2036 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_struct);
#line 2037 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2038 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2039 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2040 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Statement* struct_statement = Parsed_Struct_Statement__create(name->location, name);
#line 2041 "bootstrap/stage0/ReCode.code"
    struct Parsed_Struct_Member* last_member = NULL;
#line 2042 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2043 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 2046 "bootstrap/stage0/ReCode.code"
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2047 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2048 "bootstrap/stage0/ReCode.code"
        struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2049 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2050 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_colon);
#line 2051 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2052 "bootstrap/stage0/ReCode.code"
        struct Parsed_Type* type = Parser__parse_type(self);
#line 2053 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2054 "bootstrap/stage0/ReCode.code"
        struct Parsed_Struct_Member* member = Parsed_Struct_Member__create(name, type);
#line 2055 "bootstrap/stage0/ReCode.code"
        if (last_member == NULL) {
#line 2056 "bootstrap/stage0/ReCode.code"
            struct_statement->first_member = member;
#line 2057 "bootstrap/stage0/ReCode.code"
            last_member = member;
        } else {
#line 2059 "bootstrap/stage0/ReCode.code"
            last_member->next_member = member;
#line 2060 "bootstrap/stage0/ReCode.code"
            last_member = member;
        }
#line 2062 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2066 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2067 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2068 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2069 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) struct_statement;
}

#line 2074 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_enum(struct Parser* self, struct Token* name) {
#line 2075 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_enum);
#line 2076 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2077 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2078 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2079 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Statement* enum_statement = Parsed_Enum_Statement__create(name->location, name);
#line 2080 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Member* last_member = NULL;
#line 2081 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2082 "bootstrap/stage0/ReCode.code"
    while (Parser__consume_empty_line(self)) {
    }
#line 2085 "bootstrap/stage0/ReCode.code"
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2086 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2087 "bootstrap/stage0/ReCode.code"
        struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2088 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2089 "bootstrap/stage0/ReCode.code"
        struct Parsed_Enum_Member* member = Parsed_Enum_Member__create(name);
#line 2090 "bootstrap/stage0/ReCode.code"
        if (last_member == NULL) {
#line 2091 "bootstrap/stage0/ReCode.code"
            enum_statement->first_member = member;
#line 2092 "bootstrap/stage0/ReCode.code"
            last_member = member;
        } else {
#line 2094 "bootstrap/stage0/ReCode.code"
            last_member->next_member = member;
#line 2095 "bootstrap/stage0/ReCode.code"
            last_member = member;
        }
#line 2097 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
    }
#line 2101 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2102 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2103 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2104 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) enum_statement;
}

#line 2109 "bootstrap/stage0/ReCode.code"
struct Parsed_Type* Parser__parse_type(struct Parser* self) {
#line 2110 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2111 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = Parsed_Named_Type__create(name);
#line 2112 "bootstrap/stage0/ReCode.code"
    while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
#line 2113 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2114 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_asterisk);
#line 2115 "bootstrap/stage0/ReCode.code"
        type = Parsed_Pointer_Type__create(type);
    }
#line 2117 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2122 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_type_alias(struct Parser* self) {
#line 2123 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
#line 2124 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2125 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2126 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2127 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2128 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2129 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2130 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Type_Parameter* first_parameter = NULL;
#line 2131 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2132 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2133 "bootstrap/stage0/ReCode.code"
        struct Parsed_Type* parameter_type = Parser__parse_type(self);
#line 2134 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2135 "bootstrap/stage0/ReCode.code"
        struct Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
#line 2136 "bootstrap/stage0/ReCode.code"
        first_parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
#line 2137 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Type_Parameter* last_parameter = first_parameter;
#line 2138 "bootstrap/stage0/ReCode.code"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2139 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 2140 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_comma);
#line 2141 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2142 "bootstrap/stage0/ReCode.code"
            struct Parsed_Type* parameter_type = Parser__parse_type(self);
#line 2143 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2144 "bootstrap/stage0/ReCode.code"
            struct Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
#line 2145 "bootstrap/stage0/ReCode.code"
            struct Parsed_Function_Type_Parameter* parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
#line 2146 "bootstrap/stage0/ReCode.code"
            last_parameter->next_parameter = parameter;
#line 2147 "bootstrap/stage0/ReCode.code"
            last_parameter = parameter;
        }
    }
#line 2150 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2151 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2152 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Type_Statement__create(location, name, first_parameter, return_type);
}

#line 2157 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_variable(struct Parser* self) {
#line 2158 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_let);
#line 2159 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2160 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2161 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = NULL;
#line 2162 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_colon)) {
#line 2163 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2164 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_colon);
#line 2165 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2166 "bootstrap/stage0/ReCode.code"
        type = Parser__parse_type(self);
    }
#line 2168 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2169 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_equals);
#line 2170 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2172 "bootstrap/stage0/ReCode.code"
    bool is_external;
#line 2173 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* value_expression;
#line 2174 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_external)) {
#line 2175 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_external);
#line 2176 "bootstrap/stage0/ReCode.code"
        value_expression = NULL;
#line 2177 "bootstrap/stage0/ReCode.code"
        is_external = true;
    } else if (Parser__matches_one(self, Token__is_undefined)) {
#line 2179 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_undefined);
#line 2180 "bootstrap/stage0/ReCode.code"
        value_expression = NULL;
#line 2181 "bootstrap/stage0/ReCode.code"
        is_external = false;
    } else {
#line 2183 "bootstrap/stage0/ReCode.code"
        value_expression = Parser__parse_expression(self);
#line 2184 "bootstrap/stage0/ReCode.code"
        is_external = false;
    }
#line 2186 "bootstrap/stage0/ReCode.code"
    struct Parsed_Variable_Statement* variable_statement = Parsed_Variable_Statement__create(name->location, name, type, is_external);
#line 2187 "bootstrap/stage0/ReCode.code"
    variable_statement->expression = value_expression;
#line 2188 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) variable_statement;
}

#line 2193 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_old_variable(struct Parser* self) {
#line 2194 "bootstrap/stage0/ReCode.code"
    bool is_external;
#line 2195 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location;
#line 2196 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_external)) {
#line 2197 "bootstrap/stage0/ReCode.code"
        is_external = true;
#line 2198 "bootstrap/stage0/ReCode.code"
        location = Parser__consume_token(self, Token__is_external)->location;
#line 2199 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
    } else {
#line 2201 "bootstrap/stage0/ReCode.code"
        is_external = false;
#line 2202 "bootstrap/stage0/ReCode.code"
        location = Parser__peek_token(self, (uint8_t) 0)->location;
    }
#line 2204 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = Parser__parse_type(self);
#line 2205 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2206 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2207 "bootstrap/stage0/ReCode.code"
    struct Parsed_Variable_Statement* variable_statement = Parsed_Variable_Statement__create(location, name, type, is_external);
#line 2208 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2209 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2210 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 2211 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2212 "bootstrap/stage0/ReCode.code"
        variable_statement->expression = Parser__parse_expression(self);
    }
#line 2214 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) variable_statement;
}

#line 2219 "bootstrap/stage0/ReCode.code"
struct Parsed_Block_Statement* Parser__parse_block_statement(struct Parser* self) {
#line 2220 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_opening_brace)->location;
#line 2221 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2222 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statements* statements = Parsed_Statements__create(false);
#line 2223 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2224 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2225 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2226 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2227 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2228 "bootstrap/stage0/ReCode.code"
    return Parsed_Block_Statement__create(location, statements);
}

#line 2233 "bootstrap/stage0/ReCode.code"
struct Parsed_Function_Parameter* Parser__parse_function_parameter(struct Parser* self) {
#line 2234 "bootstrap/stage0/ReCode.code"
    struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2235 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2236 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_colon);
#line 2237 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2238 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* type = Parser__parse_type(self);
#line 2239 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Parameter__create(name, type);
}

#line 2244 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_function(struct Parser* self, struct Token* name) {
#line 2245 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2246 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2247 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2248 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* first_parameter = NULL;
#line 2249 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2250 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2251 "bootstrap/stage0/ReCode.code"
        first_parameter = Parser__parse_function_parameter(self);
#line 2252 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Parameter* last_parameter = first_parameter;
#line 2253 "bootstrap/stage0/ReCode.code"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2254 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 2255 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_comma);
#line 2256 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2257 "bootstrap/stage0/ReCode.code"
            last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2258 "bootstrap/stage0/ReCode.code"
            last_parameter = last_parameter->next_parameter;
        }
    }
#line 2261 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2262 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2263 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2264 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2265 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2266 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2267 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2268 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2269 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2270 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_brace);
#line 2271 "bootstrap/stage0/ReCode.code"
    Parser__consume_end_of_line(self);
#line 2272 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statements* statements = Parsed_Statements__create(false);
#line 2273 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation + (uint16_t) 1;
#line 2274 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, statements);
#line 2275 "bootstrap/stage0/ReCode.code"
    self->current_identation = self->current_identation - (uint16_t) 1;
#line 2276 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2277 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_brace);
#line 2278 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, statements, false);
}

#line 2283 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_external_function(struct Parser* self, struct Token* name) {
#line 2284 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_external);
#line 2285 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2286 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_func);
#line 2287 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2288 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2289 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* first_parameter = NULL;
#line 2290 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
#line 2291 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 0);
#line 2292 "bootstrap/stage0/ReCode.code"
        first_parameter = Parser__parse_function_parameter(self);
#line 2293 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Parameter* last_parameter = first_parameter;
#line 2294 "bootstrap/stage0/ReCode.code"
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
#line 2295 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 0);
#line 2296 "bootstrap/stage0/ReCode.code"
            Parser__consume_token(self, Token__is_comma);
#line 2297 "bootstrap/stage0/ReCode.code"
            Parser__consume_space(self, (uint16_t) 1);
#line 2298 "bootstrap/stage0/ReCode.code"
            last_parameter->next_parameter = Parser__parse_function_parameter(self);
#line 2299 "bootstrap/stage0/ReCode.code"
            last_parameter = last_parameter->next_parameter;
        }
    }
#line 2302 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2303 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2304 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2305 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_minus);
#line 2306 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2307 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_greater_than);
#line 2308 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2309 "bootstrap/stage0/ReCode.code"
    struct Parsed_Type* return_type = Parser__parse_type(self);
#line 2310 "bootstrap/stage0/ReCode.code"
    return Parsed_Function_Statement__create(name->location, name, first_parameter, return_type, NULL, true);
}

#line 2315 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_return_statement(struct Parser* self) {
#line 2316 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_return)->location;
#line 2317 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = NULL;
#line 2318 "bootstrap/stage0/ReCode.code"
    if (!Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 2319 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2320 "bootstrap/stage0/ReCode.code"
        expression = Parser__parse_expression(self);
    }
#line 2322 "bootstrap/stage0/ReCode.code"
    return Parsed_Return_Statement__create(location, expression);
}

#line 2327 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_break_statement(struct Parser* self) {
#line 2328 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_break)->location;
#line 2329 "bootstrap/stage0/ReCode.code"
    return Parsed_Break_Statement__create(location);
}

#line 2334 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_if_statement(struct Parser* self) {
#line 2335 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_if)->location;
#line 2336 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2337 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2338 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2339 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* condition_expression = Parser__parse_expression(self);
#line 2340 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2341 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2342 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2343 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* true_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
#line 2344 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* false_statement = NULL;
#line 2345 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
#line 2346 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2347 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_else);
#line 2348 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2349 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_if)) {
#line 2350 "bootstrap/stage0/ReCode.code"
            false_statement = Parser__parse_if_statement(self);
        } else {
#line 2352 "bootstrap/stage0/ReCode.code"
            false_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
        }
    }
#line 2355 "bootstrap/stage0/ReCode.code"
    return Parsed_If_Statement__create(location, condition_expression, true_statement, false_statement);
}

#line 2360 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_while_statement(struct Parser* self) {
#line 2361 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Parser__consume_token(self, Token__is_while)->location;
#line 2362 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2363 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_opening_paren);
#line 2364 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2365 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* condition_expression = Parser__parse_expression(self);
#line 2366 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 0);
#line 2367 "bootstrap/stage0/ReCode.code"
    Parser__consume_token(self, Token__is_closing_paren);
#line 2368 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, (uint16_t) 1);
#line 2369 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* body_statement = (struct Parsed_Statement*) Parser__parse_block_statement(self);
#line 2370 "bootstrap/stage0/ReCode.code"
    return Parsed_While_Statement__create(location, condition_expression, body_statement);
}

#line 2380 "bootstrap/stage0/ReCode.code"
struct Parsed_Statement* Parser__parse_statement(struct Parser* self) {
#line 2381 "bootstrap/stage0/ReCode.code"
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
#line 2383 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_if)) {
#line 2384 "bootstrap/stage0/ReCode.code"
        return Parser__parse_if_statement(self);
    }
#line 2386 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_while)) {
#line 2387 "bootstrap/stage0/ReCode.code"
        return Parser__parse_while_statement(self);
    }
#line 2389 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_return)) {
#line 2390 "bootstrap/stage0/ReCode.code"
        return Parser__parse_return_statement(self);
    }
#line 2392 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_break)) {
#line 2393 "bootstrap/stage0/ReCode.code"
        return Parser__parse_break_statement(self);
    }
#line 2396 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_define)) {
#line 2397 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_define);
#line 2398 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2399 "bootstrap/stage0/ReCode.code"
        struct Token* name = Parser__consume_token(self, Token__is_identifier);
#line 2400 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2401 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 2402 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2403 "bootstrap/stage0/ReCode.code"
        if (Parser__matches_one(self, Token__is_func)) {
#line 2404 "bootstrap/stage0/ReCode.code"
            return Parser__parse_function(self, name);
        } else if (Parser__matches_one(self, Token__is_struct)) {
#line 2406 "bootstrap/stage0/ReCode.code"
            return Parser__parse_struct(self, name);
        } else if (Parser__matches_three(self, Token__is_opaque, true, Token__is_space, true, Token__is_type)) {
#line 2408 "bootstrap/stage0/ReCode.code"
            return Parser__parse_opaque_type(self, name);
        } else if (Parser__matches_one(self, Token__is_enum)) {
#line 2410 "bootstrap/stage0/ReCode.code"
            return Parser__parse_enum(self, name);
        } else if (Parser__matches_three(self, Token__is_external, true, Token__is_space, true, Token__is_func)) {
#line 2412 "bootstrap/stage0/ReCode.code"
            return Parser__parse_external_function(self, name);
        }
#line 2414 "bootstrap/stage0/ReCode.code"
        Parser__error(self, String__create_from("Unsupported define"));
#line 2415 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 2418 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_typedef)) {
#line 2419 "bootstrap/stage0/ReCode.code"
        return Parser__parse_type_alias(self);
    }
#line 2422 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_one(self, Token__is_let)) {
#line 2423 "bootstrap/stage0/ReCode.code"
        return Parser__parse_variable(self);
    }
#line 2426 "bootstrap/stage0/ReCode.code"
    struct Parsed_Expression* expression = Parser__parse_access_expression(self);
#line 2427 "bootstrap/stage0/ReCode.code"
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
#line 2428 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2429 "bootstrap/stage0/ReCode.code"
        Parser__consume_token(self, Token__is_equals);
#line 2430 "bootstrap/stage0/ReCode.code"
        Parser__consume_space(self, (uint16_t) 1);
#line 2431 "bootstrap/stage0/ReCode.code"
        struct Parsed_Expression* value_expression = Parser__parse_expression(self);
#line 2432 "bootstrap/stage0/ReCode.code"
        return (struct Parsed_Statement*) Parsed_Assignment_Statement__create(expression, value_expression);
    }
#line 2434 "bootstrap/stage0/ReCode.code"
    return (struct Parsed_Statement*) Parsed_Expression_Statement__create(expression);
}

#line 2439 "bootstrap/stage0/ReCode.code"
void Parser__parse_statements(struct Parser* self, struct Parsed_Statements* statements) {
#line 2440 "bootstrap/stage0/ReCode.code"
    while (true) {
#line 2441 "bootstrap/stage0/ReCode.code"
        while (Parser__consume_empty_line(self)) {
        }
#line 2445 "bootstrap/stage0/ReCode.code"
        if (statements->has_globals) {
#line 2446 "bootstrap/stage0/ReCode.code"
            if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
#line 2447 "bootstrap/stage0/ReCode.code"
                return;
            }
        } else {
#line 2450 "bootstrap/stage0/ReCode.code"
            if (Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
#line 2451 "bootstrap/stage0/ReCode.code"
                return;
            }
        }
#line 2455 "bootstrap/stage0/ReCode.code"
        struct Parsed_Statement* statement = Parser__parse_statement(self);
#line 2457 "bootstrap/stage0/ReCode.code"
        Parser__consume_end_of_line(self);
#line 2459 "bootstrap/stage0/ReCode.code"
        Parsed_Statements__append(statements, statement);
    }
}

#line 2463 "bootstrap/stage0/ReCode.code"
void Parser__parse_source(struct Parser* self, struct Source* source) {
#line 2464 "bootstrap/stage0/ReCode.code"
    struct Scanner* other_scanner = self->scanner;
#line 2466 "bootstrap/stage0/ReCode.code"
    self->scanner = Scanner__create(source);
#line 2468 "bootstrap/stage0/ReCode.code"
    Parser__parse_statements(self, self->compilation_unit->statements);
#line 2470 "bootstrap/stage0/ReCode.code"
    struct Token* last_token = Parser__peek_token(self, (uint8_t) 0);
#line 2471 "bootstrap/stage0/ReCode.code"
    if (!Token__is_end_of_file(last_token)) {
#line 2472 "bootstrap/stage0/ReCode.code"
        Parser__error(self, String__create_from("Scanner didn\'t reach end of file"));
#line 2473 "bootstrap/stage0/ReCode.code"
        abort();
    } else if (last_token->location->column != (uint16_t) 1) {
#line 2475 "bootstrap/stage0/ReCode.code"
        Parser__warning(self, String__create_from("No new line at the end of file"));
    }
#line 2478 "bootstrap/stage0/ReCode.code"
    self->scanner = other_scanner;
}

#line 2481 "bootstrap/stage0/ReCode.code"
struct Parsed_Source* parse(struct Source* source) {
#line 2482 "bootstrap/stage0/ReCode.code"
    struct Parser parser;
#line 2483 "bootstrap/stage0/ReCode.code"
    parser.scanner = NULL;
#line 2484 "bootstrap/stage0/ReCode.code"
    parser.compilation_unit = Parsed_Compilation_Unit__create();
#line 2485 "bootstrap/stage0/ReCode.code"
    parser.current_identation = (uint16_t) 0;
#line 2487 "bootstrap/stage0/ReCode.code"
    Parser__parse_source(&parser, source);
#line 2489 "bootstrap/stage0/ReCode.code"
    return parser.compilation_unit;
}

#line 2527 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checked_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 2528 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = (struct Checked_Type*) malloc(kind_size);
#line 2529 "bootstrap/stage0/ReCode.code"
    type->kind = kind;
#line 2530 "bootstrap/stage0/ReCode.code"
    type->location = location;
#line 2531 "bootstrap/stage0/ReCode.code"
    type->next_type = NULL;
#line 2532 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2535 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_same_type(struct Checked_Type* self, struct Checked_Type* other_type, struct Source_Location* location) {
#line 2536 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__POINTER && other_type->kind == Checked_Type_Kind__NULL) {
#line 2537 "bootstrap/stage0/ReCode.code"
        return;
    }
#line 2539 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__equals(self, other_type)) {
#line 2540 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create_from("Unexpected type. Got \"");
#line 2541 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, other_type);
#line 2542 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" instead of \"");
#line 2543 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, self);
#line 2544 "bootstrap/stage0/ReCode.code"
        String__append_char(message, '\"');
#line 2545 "bootstrap/stage0/ReCode.code"
        Source_Location__error(location, message);
#line 2546 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 2550 "bootstrap/stage0/ReCode.code"
bool Checked_Type__is_scalar_type(struct Checked_Type* self) {
#line 2551 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__CHAR) {
#line 2552 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I16) {
#line 2554 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I32) {
#line 2556 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I64) {
#line 2558 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__I8) {
#line 2560 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U16) {
#line 2562 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U32) {
#line 2564 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U64) {
#line 2566 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__U8) {
#line 2568 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__USIZE) {
#line 2570 "bootstrap/stage0/ReCode.code"
        return true;
    } else if (self->kind == Checked_Type_Kind__ENUM) {
#line 2572 "bootstrap/stage0/ReCode.code"
        return true;
    }
#line 2574 "bootstrap/stage0/ReCode.code"
    return false;
}

#line 2577 "bootstrap/stage0/ReCode.code"
void Checked_Type__expect_scalar_type(struct Checked_Type* self, struct Source_Location* location) {
#line 2578 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__is_scalar_type(self)) {
#line 2579 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create_from("Type \"");
#line 2580 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, self);
#line 2581 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" is not a scalar type");
#line 2582 "bootstrap/stage0/ReCode.code"
        Source_Location__error(location, message);
#line 2583 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 2592 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checked_Named_Type__create_kind(enum Checked_Type_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name) {
#line 2593 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* type = (struct Checked_Named_Type*) Checked_Type__create_kind(kind, kind_size, location);
#line 2594 "bootstrap/stage0/ReCode.code"
    type->name = name;
#line 2595 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2605 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Member__create(struct Source_Location* location, struct String* name) {
#line 2606 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* member = (struct Checked_Enum_Member*) malloc(sizeof(struct Checked_Enum_Member));
#line 2607 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2608 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2609 "bootstrap/stage0/ReCode.code"
    member->symbol = NULL;
#line 2610 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2611 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2619 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Type* Checked_Enum_Type__create(struct Source_Location* location, struct String* name) {
#line 2620 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Type* type = (struct Checked_Enum_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__ENUM, sizeof(struct Checked_Enum_Type), location, name);
#line 2621 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2622 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2625 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member* Checked_Enum_Type__find_member(struct Checked_Enum_Type* self, struct String* name) {
#line 2626 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* member = self->first_member;
#line 2627 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2628 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, member->name)) {
#line 2629 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 2631 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2633 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2643 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter* Checked_Function_Parameter__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2644 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* parameter = (struct Checked_Function_Parameter*) malloc(sizeof(struct Checked_Function_Parameter));
#line 2645 "bootstrap/stage0/ReCode.code"
    parameter->location = location;
#line 2646 "bootstrap/stage0/ReCode.code"
    parameter->name = name;
#line 2647 "bootstrap/stage0/ReCode.code"
    parameter->type = type;
#line 2648 "bootstrap/stage0/ReCode.code"
    parameter->next_parameter = NULL;
#line 2649 "bootstrap/stage0/ReCode.code"
    return parameter;
}

#line 2658 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Type* Checked_Function_Type__create(struct Source_Location* location, struct String* name, struct Checked_Type* return_type) {
#line 2659 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* type = (struct Checked_Function_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__FUNCTION, sizeof(struct Checked_Function_Type), location, name);
#line 2660 "bootstrap/stage0/ReCode.code"
    type->return_type = return_type;
#line 2661 "bootstrap/stage0/ReCode.code"
    type->first_parameter = NULL;
#line 2662 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2665 "bootstrap/stage0/ReCode.code"
bool Checked_Function_Type__equals(struct Checked_Function_Type* self, struct Checked_Type* other_type) {
#line 2666 "bootstrap/stage0/ReCode.code"
    if (other_type->kind != self->super.super.kind) {
#line 2667 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2669 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) other_type;
#line 2670 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__equals(self->return_type, function_type->return_type)) {
#line 2671 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2673 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* self_parameter = self->first_parameter;
#line 2674 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2675 "bootstrap/stage0/ReCode.code"
    while (self_parameter != NULL && function_parameter != NULL) {
#line 2676 "bootstrap/stage0/ReCode.code"
        if (!Checked_Type__equals(self_parameter->type, function_parameter->type)) {
#line 2677 "bootstrap/stage0/ReCode.code"
            return false;
        }
#line 2679 "bootstrap/stage0/ReCode.code"
        self_parameter = self_parameter->next_parameter;
#line 2680 "bootstrap/stage0/ReCode.code"
        function_parameter = function_parameter->next_parameter;
    }
#line 2682 "bootstrap/stage0/ReCode.code"
    if (self_parameter != NULL || function_parameter != NULL) {
#line 2683 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2685 "bootstrap/stage0/ReCode.code"
    return true;
}

#line 2692 "bootstrap/stage0/ReCode.code"
struct Checked_Opaque_Type* Checked_Opaque_Type__create(struct Source_Location* location, struct String* name) {
#line 2693 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Opaque_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__OPAQUE, sizeof(struct Checked_Opaque_Type), location, name);
}

#line 2701 "bootstrap/stage0/ReCode.code"
struct Checked_Pointer_Type* Checked_Pointer_Type__create(struct Source_Location* location, struct Checked_Type* other_type) {
#line 2702 "bootstrap/stage0/ReCode.code"
    struct Checked_Pointer_Type* type = (struct Checked_Pointer_Type*) Checked_Type__create_kind(Checked_Type_Kind__POINTER, sizeof(struct Checked_Pointer_Type), location);
#line 2703 "bootstrap/stage0/ReCode.code"
    type->other_type = other_type;
#line 2704 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2707 "bootstrap/stage0/ReCode.code"
bool Checked_Pointer_Type__equals(struct Checked_Pointer_Type* self, struct Checked_Type* other_type) {
#line 2708 "bootstrap/stage0/ReCode.code"
    if (other_type->kind != self->super.kind) {
#line 2709 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2711 "bootstrap/stage0/ReCode.code"
    return Checked_Type__equals(self->other_type, ((struct Checked_Pointer_Type*) other_type)->other_type);
}

#line 2719 "bootstrap/stage0/ReCode.code"
struct Checked_Defined_Type* Checked_Defined_Type__create(struct Checked_Named_Type* defined_type) {
#line 2720 "bootstrap/stage0/ReCode.code"
    struct Checked_Defined_Type* type = (struct Checked_Defined_Type*) Checked_Type__create_kind(Checked_Type_Kind__DEFINED, sizeof(struct Checked_Defined_Type), defined_type->super.location);
#line 2721 "bootstrap/stage0/ReCode.code"
    type->defined_type = defined_type;
#line 2722 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2732 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Member__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2733 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* member = (struct Checked_Struct_Member*) malloc(sizeof(struct Checked_Struct_Member));
#line 2734 "bootstrap/stage0/ReCode.code"
    member->location = location;
#line 2735 "bootstrap/stage0/ReCode.code"
    member->name = name;
#line 2736 "bootstrap/stage0/ReCode.code"
    member->type = type;
#line 2737 "bootstrap/stage0/ReCode.code"
    member->next_member = NULL;
#line 2738 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2747 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Type* Checked_Struct_Type__create(struct Source_Location* location, struct String* name) {
#line 2748 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Type* type = (struct Checked_Struct_Type*) Checked_Named_Type__create_kind(Checked_Type_Kind__STRUCT, sizeof(struct Checked_Struct_Type), location, name);
#line 2749 "bootstrap/stage0/ReCode.code"
    type->super_type = NULL;
#line 2750 "bootstrap/stage0/ReCode.code"
    type->first_member = NULL;
#line 2751 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 2754 "bootstrap/stage0/ReCode.code"
struct Checked_Struct_Member* Checked_Struct_Type__find_member(struct Checked_Struct_Type* self, struct String* name) {
#line 2755 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* member = self->first_member;
#line 2756 "bootstrap/stage0/ReCode.code"
    while (member != NULL) {
#line 2757 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, member->name)) {
#line 2758 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 2760 "bootstrap/stage0/ReCode.code"
        member = member->next_member;
    }
#line 2762 "bootstrap/stage0/ReCode.code"
    return member;
}

#line 2765 "bootstrap/stage0/ReCode.code"
bool Checked_Struct_Type__equals(struct Checked_Struct_Type* self, struct Checked_Type* other_type) {
#line 2766 "bootstrap/stage0/ReCode.code"
    if (self->super.super.kind != other_type->kind) {
#line 2767 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2769 "bootstrap/stage0/ReCode.code"
    return String__equals_string(self->super.name, ((struct Checked_Struct_Type*) other_type)->super.name);
}

#line 2772 "bootstrap/stage0/ReCode.code"
bool Checked_Type__equals(struct Checked_Type* self, struct Checked_Type* other_type) {
#line 2773 "bootstrap/stage0/ReCode.code"
    if (self == other_type) {
#line 2774 "bootstrap/stage0/ReCode.code"
        return true;
    }
#line 2776 "bootstrap/stage0/ReCode.code"
    if (self->kind != other_type->kind) {
#line 2777 "bootstrap/stage0/ReCode.code"
        return false;
    }
#line 2779 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__FUNCTION) {
#line 2780 "bootstrap/stage0/ReCode.code"
        return Checked_Function_Type__equals((struct Checked_Function_Type*) self, other_type);
    }
#line 2782 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__POINTER) {
#line 2783 "bootstrap/stage0/ReCode.code"
        return Checked_Pointer_Type__equals((struct Checked_Pointer_Type*) self, other_type);
    }
#line 2785 "bootstrap/stage0/ReCode.code"
    if (self->kind == Checked_Type_Kind__STRUCT) {
#line 2786 "bootstrap/stage0/ReCode.code"
        return Checked_Struct_Type__equals((struct Checked_Struct_Type*) self, other_type);
    }
#line 2788 "bootstrap/stage0/ReCode.code"
    Source_Location__error(self->location, String__create_from("Unsupported type"));
#line 2789 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 2792 "bootstrap/stage0/ReCode.code"
struct String* String__append_checked_type(struct String* self, struct Checked_Type* type) {
#line 2793 "bootstrap/stage0/ReCode.code"
    if (type->kind <= Checked_Type_Kind__NULL) {
#line 2794 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* named_type = (struct Checked_Named_Type*) type;
#line 2795 "bootstrap/stage0/ReCode.code"
        String__append_string(self, named_type->name);
    } else if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2797 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) type;
#line 2798 "bootstrap/stage0/ReCode.code"
        String__append_cstring(self, "struct ");
#line 2799 "bootstrap/stage0/ReCode.code"
        String__append_string(self, struct_type->super.name);
    } else if (type->kind == Checked_Type_Kind__FUNCTION) {
#line 2801 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) type;
#line 2802 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(self, function_type->return_type);
#line 2803 "bootstrap/stage0/ReCode.code"
        String__append_char(self, ' ');
#line 2804 "bootstrap/stage0/ReCode.code"
        String__append_string(self, function_type->super.name);
#line 2805 "bootstrap/stage0/ReCode.code"
        String__append_char(self, '(');
#line 2806 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2807 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL) {
#line 2808 "bootstrap/stage0/ReCode.code"
            String__append_checked_type(self, function_parameter->type);
#line 2809 "bootstrap/stage0/ReCode.code"
            String__append_char(self, ' ');
#line 2810 "bootstrap/stage0/ReCode.code"
            String__append_string(self, function_parameter->name);
#line 2811 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 2812 "bootstrap/stage0/ReCode.code"
            if (function_parameter != NULL) {
#line 2813 "bootstrap/stage0/ReCode.code"
                String__append_cstring(self, ", ");
            }
        }
#line 2816 "bootstrap/stage0/ReCode.code"
        String__append_char(self, ')');
    } else if (type->kind == Checked_Type_Kind__ENUM) {
#line 2818 "bootstrap/stage0/ReCode.code"
        struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) type;
#line 2819 "bootstrap/stage0/ReCode.code"
        String__append_cstring(self, "enum ");
#line 2820 "bootstrap/stage0/ReCode.code"
        String__append_string(self, enum_type->super.name);
    } else if (type->kind == Checked_Type_Kind__POINTER) {
#line 2822 "bootstrap/stage0/ReCode.code"
        struct Checked_Pointer_Type* pointer_type = (struct Checked_Pointer_Type*) type;
#line 2823 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(self, pointer_type->other_type);
#line 2824 "bootstrap/stage0/ReCode.code"
        String__append_char(self, '*');
    } else {
#line 2826 "bootstrap/stage0/ReCode.code"
        Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2827 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 2829 "bootstrap/stage0/ReCode.code"
    return self;
}

#line 2832 "bootstrap/stage0/ReCode.code"
void File__write_checked_function_parameter(struct File* self, struct Checked_Function_Parameter* parameter) {
#line 2833 "bootstrap/stage0/ReCode.code"
    if (parameter->type->kind == Checked_Type_Kind__POINTER && ((struct Checked_Pointer_Type*) parameter->type)->other_type->kind == Checked_Type_Kind__FUNCTION) {
#line 2834 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) ((struct Checked_Pointer_Type*) parameter->type)->other_type;
#line 2835 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, function_type->return_type);
#line 2836 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, " (*");
#line 2837 "bootstrap/stage0/ReCode.code"
        File__write_string(self, parameter->name);
#line 2838 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, ")(");
#line 2839 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2840 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL) {
#line 2841 "bootstrap/stage0/ReCode.code"
            File__write_checked_function_parameter(self, function_parameter);
#line 2842 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 2843 "bootstrap/stage0/ReCode.code"
            if (function_parameter != NULL) {
#line 2844 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, ", ");
            }
        }
#line 2847 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ')');
    } else {
#line 2849 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, parameter->type);
#line 2850 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ' ');
#line 2851 "bootstrap/stage0/ReCode.code"
        File__write_string(self, parameter->name);
    }
}

#line 2855 "bootstrap/stage0/ReCode.code"
void File__write_checked_type(struct File* self, struct Checked_Type* type) {
#line 2856 "bootstrap/stage0/ReCode.code"
    if (type == NULL) {
#line 2857 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "null");
    } else if (type->kind == Checked_Type_Kind__I16) {
#line 2859 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int16_t");
    } else if (type->kind == Checked_Type_Kind__I32) {
#line 2861 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int32_t");
    } else if (type->kind == Checked_Type_Kind__I64) {
#line 2863 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int64_t");
    } else if (type->kind == Checked_Type_Kind__I8) {
#line 2865 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "int8_t");
    } else if (type->kind == Checked_Type_Kind__U16) {
#line 2867 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint16_t");
    } else if (type->kind == Checked_Type_Kind__U32) {
#line 2869 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint32_t");
    } else if (type->kind == Checked_Type_Kind__U64) {
#line 2871 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint64_t");
    } else if (type->kind == Checked_Type_Kind__U8) {
#line 2873 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "uint8_t");
    } else if (type->kind == Checked_Type_Kind__USIZE) {
#line 2875 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "size_t");
    } else if (type->kind <= Checked_Type_Kind__NULL) {
#line 2877 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* named_type = (struct Checked_Named_Type*) type;
#line 2878 "bootstrap/stage0/ReCode.code"
        File__write_string(self, named_type->name);
    } else if (type->kind == Checked_Type_Kind__STRUCT) {
#line 2880 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) type;
#line 2881 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "struct ");
#line 2882 "bootstrap/stage0/ReCode.code"
        File__write_string(self, struct_type->super.name);
    } else if (type->kind == Checked_Type_Kind__OPAQUE) {
#line 2884 "bootstrap/stage0/ReCode.code"
        struct Checked_Opaque_Type* opaque_type = (struct Checked_Opaque_Type*) type;
#line 2885 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "struct ");
#line 2886 "bootstrap/stage0/ReCode.code"
        File__write_string(self, opaque_type->super.name);
    } else if (type->kind == Checked_Type_Kind__FUNCTION) {
#line 2888 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) type;
#line 2889 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, function_type->return_type);
#line 2890 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ' ');
#line 2891 "bootstrap/stage0/ReCode.code"
        File__write_string(self, function_type->super.name);
#line 2892 "bootstrap/stage0/ReCode.code"
        File__write_char(self, '(');
#line 2893 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 2894 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL) {
#line 2895 "bootstrap/stage0/ReCode.code"
            File__write_checked_function_parameter(self, function_parameter);
#line 2896 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 2897 "bootstrap/stage0/ReCode.code"
            if (function_parameter != NULL) {
#line 2898 "bootstrap/stage0/ReCode.code"
                File__write_cstring(self, ", ");
            }
        }
#line 2901 "bootstrap/stage0/ReCode.code"
        File__write_char(self, ')');
    } else if (type->kind == Checked_Type_Kind__ENUM) {
#line 2903 "bootstrap/stage0/ReCode.code"
        struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) type;
#line 2904 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self, "enum ");
#line 2905 "bootstrap/stage0/ReCode.code"
        File__write_string(self, enum_type->super.name);
    } else if (type->kind == Checked_Type_Kind__POINTER) {
#line 2907 "bootstrap/stage0/ReCode.code"
        struct Checked_Pointer_Type* pointer_type = (struct Checked_Pointer_Type*) type;
#line 2908 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self, pointer_type->other_type);
#line 2909 "bootstrap/stage0/ReCode.code"
        File__write_char(self, '*');
    } else {
#line 2911 "bootstrap/stage0/ReCode.code"
        Source_Location__error(type->location, String__create_from("Unsupported type"));
#line 2912 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 2937 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbol__create_kind(enum Checked_Symbol_Kind kind, size_t kind_size, struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2938 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = (struct Checked_Symbol*) malloc(kind_size);
#line 2939 "bootstrap/stage0/ReCode.code"
    symbol->kind = kind;
#line 2940 "bootstrap/stage0/ReCode.code"
    symbol->location = location;
#line 2941 "bootstrap/stage0/ReCode.code"
    symbol->name = name;
#line 2942 "bootstrap/stage0/ReCode.code"
    symbol->type = type;
#line 2943 "bootstrap/stage0/ReCode.code"
    symbol->prev_symbol = NULL;
#line 2944 "bootstrap/stage0/ReCode.code"
    symbol->next_symbol = NULL;
#line 2945 "bootstrap/stage0/ReCode.code"
    return symbol;
}

#line 2952 "bootstrap/stage0/ReCode.code"
struct Checked_Enum_Member_Symbol* Checked_Enum_Member_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2953 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Enum_Member_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__ENUM_MEMBER, sizeof(struct Checked_Enum_Member_Symbol), location, name, type);
}

#line 2962 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Symbol* Checked_Function_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Function_Type* function_type) {
#line 2963 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Symbol* symbol = (struct Checked_Function_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION, sizeof(struct Checked_Function_Symbol), location, name, (struct Checked_Type*) Checked_Pointer_Type__create(function_type->super.super.location, (struct Checked_Type*) function_type));
#line 2964 "bootstrap/stage0/ReCode.code"
    symbol->function_type = function_type;
#line 2965 "bootstrap/stage0/ReCode.code"
    symbol->checked_statements = NULL;
#line 2966 "bootstrap/stage0/ReCode.code"
    return symbol;
}

#line 2973 "bootstrap/stage0/ReCode.code"
struct Checked_Function_Parameter_Symbol* Checked_Function_Parameter_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2974 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Function_Parameter_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__FUNCTION_PARAMETER, sizeof(struct Checked_Function_Parameter_Symbol), location, name, type);
}

#line 2982 "bootstrap/stage0/ReCode.code"
struct Checked_Type_Symbol* Checked_Type_Symbol__create(struct Source_Location* location, struct String* name, struct Checked_Named_Type* named_type) {
#line 2983 "bootstrap/stage0/ReCode.code"
    struct Checked_Type_Symbol* symbol = (struct Checked_Type_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__TYPE, sizeof(struct Checked_Type_Symbol), location, name, (struct Checked_Type*) Checked_Defined_Type__create(named_type));
#line 2984 "bootstrap/stage0/ReCode.code"
    symbol->named_type = named_type;
#line 2985 "bootstrap/stage0/ReCode.code"
    return symbol;
}

#line 2992 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Symbol* Checked_Variable__create(struct Source_Location* location, struct String* name, struct Checked_Type* type) {
#line 2993 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Variable_Symbol*) Checked_Symbol__create_kind(Checked_Symbol_Kind__VARIABLE, sizeof(struct Checked_Variable_Symbol), location, name, type);
}

#line 3002 "bootstrap/stage0/ReCode.code"
struct Checked_Symbols* Checked_Symbols__create(struct Checked_Symbols* parent) {
#line 3003 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbols* symbols = (struct Checked_Symbols*) malloc(sizeof(struct Checked_Symbols));
#line 3004 "bootstrap/stage0/ReCode.code"
    symbols->parent = parent;
#line 3005 "bootstrap/stage0/ReCode.code"
    symbols->first_symbol = NULL;
#line 3006 "bootstrap/stage0/ReCode.code"
    symbols->last_symbol = NULL;
#line 3007 "bootstrap/stage0/ReCode.code"
    return symbols;
}

#line 3010 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_sibling_symbol(struct Checked_Symbols* self, struct String* name) {
#line 3011 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = self->first_symbol;
#line 3012 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 3013 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, symbol->name)) {
#line 3014 "bootstrap/stage0/ReCode.code"
            return symbol;
        }
#line 3016 "bootstrap/stage0/ReCode.code"
        symbol = symbol->next_symbol;
    }
#line 3018 "bootstrap/stage0/ReCode.code"
    return NULL;
}

#line 3021 "bootstrap/stage0/ReCode.code"
void Checked_Symbols__append_symbol(struct Checked_Symbols* self, struct Checked_Symbol* symbol) {
#line 3022 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* other_symbol = Checked_Symbols__find_sibling_symbol(self, symbol->name);
#line 3023 "bootstrap/stage0/ReCode.code"
    if (other_symbol != NULL) {
#line 3024 "bootstrap/stage0/ReCode.code"
        Source_Location__error(symbol->location, String__append_source_location(String__create_from("Symbol declared first here: "), other_symbol->location));
#line 3025 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3028 "bootstrap/stage0/ReCode.code"
    if (self->last_symbol == NULL) {
#line 3029 "bootstrap/stage0/ReCode.code"
        self->first_symbol = symbol;
    } else {
#line 3031 "bootstrap/stage0/ReCode.code"
        self->last_symbol->next_symbol = symbol;
#line 3032 "bootstrap/stage0/ReCode.code"
        symbol->prev_symbol = self->last_symbol;
    }
#line 3034 "bootstrap/stage0/ReCode.code"
    self->last_symbol = symbol;
}

#line 3037 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol* Checked_Symbols__find_symbol(struct Checked_Symbols* self, struct String* name) {
#line 3038 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = self->last_symbol;
#line 3039 "bootstrap/stage0/ReCode.code"
    while (symbol != NULL) {
#line 3040 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, symbol->name)) {
#line 3041 "bootstrap/stage0/ReCode.code"
            return symbol;
        }
#line 3043 "bootstrap/stage0/ReCode.code"
        symbol = symbol->prev_symbol;
    }
#line 3045 "bootstrap/stage0/ReCode.code"
    if (self->parent != NULL) {
#line 3046 "bootstrap/stage0/ReCode.code"
        return Checked_Symbols__find_symbol(self->parent, name);
    }
#line 3048 "bootstrap/stage0/ReCode.code"
    return NULL;
}

#line 3093 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checked_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type) {
#line 3094 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = (struct Checked_Expression*) malloc(kind_size);
#line 3095 "bootstrap/stage0/ReCode.code"
    expression->kind = kind;
#line 3096 "bootstrap/stage0/ReCode.code"
    expression->location = location;
#line 3097 "bootstrap/stage0/ReCode.code"
    expression->type = type;
#line 3098 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3107 "bootstrap/stage0/ReCode.code"
struct Checked_Binary_Expression* Checked_Binary_Expression__create_kind(enum Checked_Expression_Kind kind, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3108 "bootstrap/stage0/ReCode.code"
    struct Checked_Binary_Expression* expression = (struct Checked_Binary_Expression*) Checked_Expression__create_kind(kind, sizeof(struct Checked_Binary_Expression), location, type);
#line 3109 "bootstrap/stage0/ReCode.code"
    expression->left_expression = left_expression;
#line 3110 "bootstrap/stage0/ReCode.code"
    expression->right_expression = right_expression;
#line 3111 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3119 "bootstrap/stage0/ReCode.code"
struct Checked_Unary_Expression* Checked_Unary_Expression__create_kind(enum Checked_Expression_Kind kind, size_t kind_size, struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3120 "bootstrap/stage0/ReCode.code"
    struct Checked_Unary_Expression* expression = (struct Checked_Unary_Expression*) Checked_Expression__create_kind(kind, kind_size, location, type);
#line 3121 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3122 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3129 "bootstrap/stage0/ReCode.code"
struct Checked_Add_Expression* Checked_Add_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3130 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Add_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__ADD, location, type, left_expression, right_expression);
}

#line 3137 "bootstrap/stage0/ReCode.code"
struct Checked_Address_Of_Expression* Checked_Address_Of_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3138 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Address_Of_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__ADDRESS_OF, sizeof(struct Checked_Address_Of_Expression), location, type, other_expression);
}

#line 3147 "bootstrap/stage0/ReCode.code"
struct Checked_Array_Access_Expression* Checked_Array_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* array_expression, struct Checked_Expression* index_expression) {
#line 3148 "bootstrap/stage0/ReCode.code"
    struct Checked_Array_Access_Expression* expression = (struct Checked_Array_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__ARRAY_ACCESS, sizeof(struct Checked_Array_Access_Expression), location, type);
#line 3149 "bootstrap/stage0/ReCode.code"
    expression->array_expression = array_expression;
#line 3150 "bootstrap/stage0/ReCode.code"
    expression->index_expression = index_expression;
#line 3151 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3159 "bootstrap/stage0/ReCode.code"
struct Checked_Bool_Expression* Checked_Bool_Expression__create(struct Source_Location* location, struct Checked_Type* type, bool value) {
#line 3160 "bootstrap/stage0/ReCode.code"
    struct Checked_Bool_Expression* expression = (struct Checked_Bool_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__BOOL, sizeof(struct Checked_Bool_Expression), location, type);
#line 3161 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3162 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3170 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Argument* Checked_Call_Argument__create(struct Checked_Expression* expression) {
#line 3171 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Argument* argument = (struct Checked_Call_Argument*) malloc(sizeof(struct Checked_Call_Argument));
#line 3172 "bootstrap/stage0/ReCode.code"
    argument->expression = expression;
#line 3173 "bootstrap/stage0/ReCode.code"
    argument->next_argument = NULL;
#line 3174 "bootstrap/stage0/ReCode.code"
    return argument;
}

#line 3183 "bootstrap/stage0/ReCode.code"
struct Checked_Call_Expression* Checked_Call_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* callee_expression, struct Checked_Call_Argument* first_argument) {
#line 3184 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Expression* expression = (struct Checked_Call_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CALL, sizeof(struct Checked_Call_Expression), location, type);
#line 3185 "bootstrap/stage0/ReCode.code"
    expression->callee_expression = callee_expression;
#line 3186 "bootstrap/stage0/ReCode.code"
    expression->first_argument = first_argument;
#line 3187 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3195 "bootstrap/stage0/ReCode.code"
struct Checked_Cast_Expression* Checked_Cast_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3196 "bootstrap/stage0/ReCode.code"
    struct Checked_Cast_Expression* expression = (struct Checked_Cast_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CAST, sizeof(struct Checked_Cast_Expression), location, type);
#line 3197 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3198 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3206 "bootstrap/stage0/ReCode.code"
struct Checked_Character_Expression* Checked_Character_Expression__create(struct Source_Location* location, struct Checked_Type* type, char value) {
#line 3207 "bootstrap/stage0/ReCode.code"
    struct Checked_Character_Expression* expression = (struct Checked_Character_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__CHARACTER, sizeof(struct Checked_Character_Expression), location, type);
#line 3208 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3209 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3217 "bootstrap/stage0/ReCode.code"
struct Checked_Dereference_Expression* Checked_Dereference_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* value_expression) {
#line 3218 "bootstrap/stage0/ReCode.code"
    struct Checked_Dereference_Expression* expression = (struct Checked_Dereference_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__DEREFERENCE, sizeof(struct Checked_Dereference_Expression), location, type);
#line 3219 "bootstrap/stage0/ReCode.code"
    expression->value_expression = value_expression;
#line 3220 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3227 "bootstrap/stage0/ReCode.code"
struct Checked_Divide_Expression* Checked_Divide_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3228 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Divide_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__DIVIDE, location, type, left_expression, right_expression);
}

#line 3235 "bootstrap/stage0/ReCode.code"
struct Checked_Equals_Expression* Checked_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3236 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__EQUALS, location, type, left_expression, right_expression);
}

#line 3243 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Expression* Checked_Greater_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3244 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Greater_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER, location, type, left_expression, right_expression);
}

#line 3251 "bootstrap/stage0/ReCode.code"
struct Checked_Greater_Or_Equals_Expression* Checked_Greater_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3252 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Greater_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__GREATER_OR_EQUALS, location, type, left_expression, right_expression);
}

#line 3260 "bootstrap/stage0/ReCode.code"
struct Checked_Group_Expression* Checked_Group_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3261 "bootstrap/stage0/ReCode.code"
    struct Checked_Group_Expression* expression = (struct Checked_Group_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__GROUP, sizeof(struct Checked_Group_Expression), location, type);
#line 3262 "bootstrap/stage0/ReCode.code"
    expression->other_expression = other_expression;
#line 3263 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3271 "bootstrap/stage0/ReCode.code"
struct Checked_Integer_Expression* Checked_Integer_Expression__create(struct Source_Location* location, struct Checked_Type* type, uint64_t value) {
#line 3272 "bootstrap/stage0/ReCode.code"
    struct Checked_Integer_Expression* expression = (struct Checked_Integer_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__INTEGER, sizeof(struct Checked_Integer_Expression), location, type);
#line 3273 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3274 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3281 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Expression* Checked_Less_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3282 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Less_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS, location, type, left_expression, right_expression);
}

#line 3289 "bootstrap/stage0/ReCode.code"
struct Checked_Less_Or_Equals_Expression* Checked_Less_Or_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3290 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Less_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LESS_OR_EQUALS, location, type, left_expression, right_expression);
}

#line 3297 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_And_Expression* Checked_Logic_And_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3298 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Logic_And_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_AND, location, type, left_expression, right_expression);
}

#line 3305 "bootstrap/stage0/ReCode.code"
struct Checked_Logic_Or_Expression* Checked_Logic_Or_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3306 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Logic_Or_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__LOGIC_OR, location, type, left_expression, right_expression);
}

#line 3315 "bootstrap/stage0/ReCode.code"
struct Checked_Member_Access_Expression* Checked_Member_Access_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* object_expression, struct Checked_Struct_Member* member) {
#line 3316 "bootstrap/stage0/ReCode.code"
    struct Checked_Member_Access_Expression* expression = (struct Checked_Member_Access_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__MEMBER_ACCESS, sizeof(struct Checked_Member_Access_Expression), location, type);
#line 3317 "bootstrap/stage0/ReCode.code"
    expression->object_expression = object_expression;
#line 3318 "bootstrap/stage0/ReCode.code"
    expression->member = member;
#line 3319 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3326 "bootstrap/stage0/ReCode.code"
struct Checked_Minus_Expression* Checked_Minus_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3327 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Minus_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__MINUS, sizeof(struct Checked_Minus_Expression), location, type, other_expression);
}

#line 3334 "bootstrap/stage0/ReCode.code"
struct Checked_Modulo_Expression* Checked_Modulo_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3335 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Modulo_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MODULO, location, type, left_expression, right_expression);
}

#line 3342 "bootstrap/stage0/ReCode.code"
struct Checked_Multiply_Expression* Checked_Multiply_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3343 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Multiply_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__MULTIPLY, location, type, left_expression, right_expression);
}

#line 3350 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Expression* Checked_Not_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* other_expression) {
#line 3351 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Not_Expression*) Checked_Unary_Expression__create_kind(Checked_Expression_Kind__NOT, sizeof(struct Checked_Not_Expression), location, type, other_expression);
}

#line 3358 "bootstrap/stage0/ReCode.code"
struct Checked_Not_Equals_Expression* Checked_Not_Equals_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3359 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Not_Equals_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__NOT_EQUALS, location, type, left_expression, right_expression);
}

#line 3366 "bootstrap/stage0/ReCode.code"
struct Checked_Null_Expression* Checked_Null_Expression__create(struct Source_Location* location, struct Checked_Type* type) {
#line 3367 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Null_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__NULL, sizeof(struct Checked_Null_Expression), location, type);
}

#line 3375 "bootstrap/stage0/ReCode.code"
struct Checked_Sizeof_Expression* Checked_Sizeof_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Type* sized_type) {
#line 3376 "bootstrap/stage0/ReCode.code"
    struct Checked_Sizeof_Expression* expression = (struct Checked_Sizeof_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SIZEOF, sizeof(struct Checked_Sizeof_Expression), location, type);
#line 3377 "bootstrap/stage0/ReCode.code"
    expression->sized_type = sized_type;
#line 3378 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3386 "bootstrap/stage0/ReCode.code"
struct Checked_String_Expression* Checked_String_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct String* value) {
#line 3387 "bootstrap/stage0/ReCode.code"
    struct Checked_String_Expression* expression = (struct Checked_String_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__STRING, sizeof(struct Checked_String_Expression), location, type);
#line 3388 "bootstrap/stage0/ReCode.code"
    expression->value = value;
#line 3389 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3396 "bootstrap/stage0/ReCode.code"
struct Checked_Substract_Expression* Checked_Substract_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Expression* left_expression, struct Checked_Expression* right_expression) {
#line 3397 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Substract_Expression*) Checked_Binary_Expression__create_kind(Checked_Expression_Kind__SUBSTRACT, location, type, left_expression, right_expression);
}

#line 3405 "bootstrap/stage0/ReCode.code"
struct Checked_Symbol_Expression* Checked_Symbol_Expression__create(struct Source_Location* location, struct Checked_Type* type, struct Checked_Symbol* symbol) {
#line 3406 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol_Expression* expression = (struct Checked_Symbol_Expression*) Checked_Expression__create_kind(Checked_Expression_Kind__SYMBOL, sizeof(struct Checked_Symbol_Expression), location, type);
#line 3407 "bootstrap/stage0/ReCode.code"
    expression->symbol = symbol;
#line 3408 "bootstrap/stage0/ReCode.code"
    return expression;
}

#line 3432 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checked_Statement__create_kind(enum Checked_Statement_Kind kind, size_t kind_size, struct Source_Location* location) {
#line 3433 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* statement = (struct Checked_Statement*) malloc(kind_size);
#line 3434 "bootstrap/stage0/ReCode.code"
    statement->kind = kind;
#line 3435 "bootstrap/stage0/ReCode.code"
    statement->location = location;
#line 3436 "bootstrap/stage0/ReCode.code"
    statement->next_statement = NULL;
#line 3437 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3446 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checked_Assignment_Statement__create(struct Source_Location* location, struct Checked_Expression* object_expression, struct Checked_Expression* value_expression) {
#line 3447 "bootstrap/stage0/ReCode.code"
    struct Checked_Assignment_Statement* statement = (struct Checked_Assignment_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__ASSIGNMENT, sizeof(struct Checked_Assignment_Statement), location);
#line 3448 "bootstrap/stage0/ReCode.code"
    statement->object_expression = object_expression;
#line 3449 "bootstrap/stage0/ReCode.code"
    statement->value_expression = value_expression;
#line 3450 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3458 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checked_Block_Statement__create(struct Source_Location* location, struct Checked_Statements* statements) {
#line 3459 "bootstrap/stage0/ReCode.code"
    struct Checked_Block_Statement* statement = (struct Checked_Block_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BLOCK, sizeof(struct Checked_Block_Statement), location);
#line 3460 "bootstrap/stage0/ReCode.code"
    statement->statements = statements;
#line 3461 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3468 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checked_Break_Statement__create(struct Source_Location* location) {
#line 3469 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Break_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__BREAK, sizeof(struct Checked_Break_Statement), location);
}

#line 3477 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checked_Expression_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) {
#line 3478 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression_Statement* statement = (struct Checked_Expression_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__EXPRESSION, sizeof(struct Checked_Expression_Statement), location);
#line 3479 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3480 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3490 "bootstrap/stage0/ReCode.code"
struct Checked_If_Statement* Checked_If_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* true_statement, struct Checked_Statement* false_statement) {
#line 3491 "bootstrap/stage0/ReCode.code"
    struct Checked_If_Statement* statement = (struct Checked_If_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__IF, sizeof(struct Checked_If_Statement), location);
#line 3492 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3493 "bootstrap/stage0/ReCode.code"
    statement->true_statement = true_statement;
#line 3494 "bootstrap/stage0/ReCode.code"
    statement->false_statement = false_statement;
#line 3495 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3503 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checked_Return_Statement__create(struct Source_Location* location, struct Checked_Expression* expression) {
#line 3504 "bootstrap/stage0/ReCode.code"
    struct Checked_Return_Statement* statement = (struct Checked_Return_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__RETURN, sizeof(struct Checked_Return_Statement), location);
#line 3505 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3506 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3516 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checked_Variable_Statement__create(struct Source_Location* location, struct Checked_Variable_Symbol* variable, struct Checked_Expression* expression, bool is_external) {
#line 3517 "bootstrap/stage0/ReCode.code"
    struct Checked_Variable_Statement* statement = (struct Checked_Variable_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__VARIABLE, sizeof(struct Checked_Variable_Statement), location);
#line 3518 "bootstrap/stage0/ReCode.code"
    statement->variable = variable;
#line 3519 "bootstrap/stage0/ReCode.code"
    statement->expression = expression;
#line 3520 "bootstrap/stage0/ReCode.code"
    statement->is_external = is_external;
#line 3521 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3530 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checked_While_Statement__create(struct Source_Location* location, struct Checked_Expression* condition_expression, struct Checked_Statement* body_statement) {
#line 3531 "bootstrap/stage0/ReCode.code"
    struct Checked_While_Statement* statement = (struct Checked_While_Statement*) Checked_Statement__create_kind(Checked_Statement_Kind__WHILE, sizeof(struct Checked_While_Statement), location);
#line 3532 "bootstrap/stage0/ReCode.code"
    statement->condition_expression = condition_expression;
#line 3533 "bootstrap/stage0/ReCode.code"
    statement->body_statement = body_statement;
#line 3534 "bootstrap/stage0/ReCode.code"
    return statement;
}

#line 3542 "bootstrap/stage0/ReCode.code"
struct Checked_Statements* Checked_Statements__create() {
#line 3543 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* statements = (struct Checked_Statements*) malloc(sizeof(struct Checked_Statements));
#line 3544 "bootstrap/stage0/ReCode.code"
    statements->first_statement = NULL;
#line 3545 "bootstrap/stage0/ReCode.code"
    statements->last_statement = NULL;
#line 3546 "bootstrap/stage0/ReCode.code"
    return statements;
}

#line 3549 "bootstrap/stage0/ReCode.code"
void Checked_Statements__append(struct Checked_Statements* self, struct Checked_Statement* statement) {
#line 3550 "bootstrap/stage0/ReCode.code"
    if (self->first_statement == NULL) {
#line 3551 "bootstrap/stage0/ReCode.code"
        self->first_statement = statement;
    } else {
#line 3553 "bootstrap/stage0/ReCode.code"
        self->last_statement->next_statement = statement;
    }
#line 3555 "bootstrap/stage0/ReCode.code"
    self->last_statement = statement;
}

#line 3579 "bootstrap/stage0/ReCode.code"
struct Checker* Checker__create() {
#line 3580 "bootstrap/stage0/ReCode.code"
    struct Checker* checker = (struct Checker*) malloc(sizeof(struct Checker));
#line 3581 "bootstrap/stage0/ReCode.code"
    checker->first_type = NULL;
#line 3582 "bootstrap/stage0/ReCode.code"
    checker->last_type = NULL;
#line 3583 "bootstrap/stage0/ReCode.code"
    checker->symbols = Checked_Symbols__create(NULL);
#line 3585 "bootstrap/stage0/ReCode.code"
    struct Source_Location* location = Source_Location__create(NULL, (uint16_t) 0, (uint16_t) 1);
#line 3586 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__BOOL, sizeof(struct Checked_Named_Type), location, String__create_from("bool")));
#line 3587 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__CHAR, sizeof(struct Checked_Named_Type), location, String__create_from("char")));
#line 3588 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I16, sizeof(struct Checked_Named_Type), location, String__create_from("i16")));
#line 3589 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I32, sizeof(struct Checked_Named_Type), location, String__create_from("i32")));
#line 3590 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I64, sizeof(struct Checked_Named_Type), location, String__create_from("i64")));
#line 3591 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__I8, sizeof(struct Checked_Named_Type), location, String__create_from("i8")));
#line 3592 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U16, sizeof(struct Checked_Named_Type), location, String__create_from("u16")));
#line 3593 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U32, sizeof(struct Checked_Named_Type), location, String__create_from("u32")));
#line 3594 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U64, sizeof(struct Checked_Named_Type), location, String__create_from("u64")));
#line 3595 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__U8, sizeof(struct Checked_Named_Type), location, String__create_from("u8")));
#line 3596 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__USIZE, sizeof(struct Checked_Named_Type), location, String__create_from("usize")));
#line 3597 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__VOID, sizeof(struct Checked_Named_Type), location, String__create_from("void")));
#line 3598 "bootstrap/stage0/ReCode.code"
    Checker__append_type(checker, Checked_Named_Type__create_kind(Checked_Type_Kind__NULL, sizeof(struct Checked_Named_Type), location, String__create_from("null")));
#line 3599 "bootstrap/stage0/ReCode.code"
    checker->last_builting_type = checker->last_type;
#line 3601 "bootstrap/stage0/ReCode.code"
    return checker;
}

#line 3604 "bootstrap/stage0/ReCode.code"
void Checker__append_type(struct Checker* self, struct Checked_Named_Type* type) {
#line 3605 "bootstrap/stage0/ReCode.code"
    if (self->first_type == NULL) {
#line 3606 "bootstrap/stage0/ReCode.code"
        self->first_type = type;
    } else {
#line 3608 "bootstrap/stage0/ReCode.code"
        self->last_type->super.next_type = (struct Checked_Type*) type;
    }
#line 3610 "bootstrap/stage0/ReCode.code"
    self->last_type = type;
#line 3612 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Type_Symbol__create(type->super.location, type->name, type));
}

#line 3615 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__find_type(struct Checker* self, struct String* name) {
#line 3616 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* type = self->first_type;
#line 3617 "bootstrap/stage0/ReCode.code"
    while (type != NULL) {
#line 3618 "bootstrap/stage0/ReCode.code"
        if (String__equals_string(name, type->name)) {
#line 3619 "bootstrap/stage0/ReCode.code"
            break;
        }
#line 3621 "bootstrap/stage0/ReCode.code"
        type = (struct Checked_Named_Type*) type->super.next_type;
    }
#line 3623 "bootstrap/stage0/ReCode.code"
    return type;
}

#line 3626 "bootstrap/stage0/ReCode.code"
struct Checked_Named_Type* Checker__get_builtin_type(struct Checker* self, enum Checked_Type_Kind kind) {
#line 3627 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* type = self->first_type;
#line 3628 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* custom_type = (struct Checked_Named_Type*) self->last_builting_type->super.next_type;
#line 3629 "bootstrap/stage0/ReCode.code"
    while (type != custom_type) {
#line 3630 "bootstrap/stage0/ReCode.code"
        if (type->super.kind == kind) {
#line 3631 "bootstrap/stage0/ReCode.code"
            return type;
        }
#line 3633 "bootstrap/stage0/ReCode.code"
        type = (struct Checked_Named_Type*) type->super.next_type;
    }
#line 3635 "bootstrap/stage0/ReCode.code"
    error(String__create_from("No such builtin type"));
#line 3636 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 3639 "bootstrap/stage0/ReCode.code"
struct Checked_Type* Checker__resolve_type(struct Checker* self, struct Parsed_Type* parsed_type) {
#line 3640 "bootstrap/stage0/ReCode.code"
    if (parsed_type->kind == Parsed_Type_Kind__NAMED) {
#line 3641 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* type = Checker__find_type(self, ((struct Parsed_Named_Type*) parsed_type)->name);
#line 3642 "bootstrap/stage0/ReCode.code"
        if (type != NULL) {
#line 3643 "bootstrap/stage0/ReCode.code"
            return (struct Checked_Type*) type;
        }
    }
#line 3646 "bootstrap/stage0/ReCode.code"
    if (parsed_type->kind == Parsed_Type_Kind__POINTER) {
#line 3647 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Type*) Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((struct Parsed_Pointer_Type*) parsed_type)->other_type));
    }
#line 3649 "bootstrap/stage0/ReCode.code"
    if (parsed_type->kind == Parsed_Type_Kind__STRUCT) {
#line 3650 "bootstrap/stage0/ReCode.code"
        struct Checked_Type* type = Checker__resolve_type(self, ((struct Parsed_Struct_Type*) parsed_type)->other_type);
#line 3651 "bootstrap/stage0/ReCode.code"
        if (type->kind != Checked_Type_Kind__STRUCT) {
#line 3652 "bootstrap/stage0/ReCode.code"
            TODO("Report unexpected type");
#line 3653 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 3655 "bootstrap/stage0/ReCode.code"
        return type;
    }
#line 3657 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_type->location, String__create_from("Undefined type"));
#line 3658 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 3661 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_add_expression(struct Checker* self, struct Parsed_Add_Expression* parsed_expression) {
#line 3662 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3663 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3664 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3665 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3666 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3669 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_address_of_expression(struct Checker* self, struct Parsed_Address_Of_Expression* parsed_expression) {
#line 3670 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3671 "bootstrap/stage0/ReCode.code"
    if (other_expression->kind != Checked_Expression_Kind__SYMBOL) {
#line 3672 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->super.super.location, String__create_from("Not a symbol"));
#line 3673 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3675 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
}

#line 3678 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_array_access_expression(struct Checker* self, struct Parsed_Array_Access_Expression* parsed_expression) {
#line 3679 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* array_expression = Checker__check_expression(self, parsed_expression->array_expression);
#line 3680 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* array_type = array_expression->type;
#line 3681 "bootstrap/stage0/ReCode.code"
    if (array_type->kind != Checked_Type_Kind__POINTER) {
#line 3682 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create();
#line 3683 "bootstrap/stage0/ReCode.code"
        String__append_char(message, '\"');
#line 3684 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, array_type);
#line 3685 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" is not a pointer type.");
#line 3686 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->array_expression->location, message);
#line 3687 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3689 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = ((struct Checked_Pointer_Type*) array_type)->other_type;
#line 3690 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* index_expression = Checker__check_expression(self, parsed_expression->index_expression);
#line 3691 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE), index_expression->type, index_expression->location);
#line 3692 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

#line 3695 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_bool_expression(struct Checker* self, struct Parsed_Bool_Expression* parsed_expression) {
#line 3696 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL);
#line 3697 "bootstrap/stage0/ReCode.code"
    bool value = parsed_expression->value;
#line 3698 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3701 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_call_expression(struct Checker* self, struct Parsed_Call_Expression* parsed_expression) {
#line 3702 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* callee_expression = Checker__check_expression(self, parsed_expression->callee_expression);
#line 3703 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* callee_type = callee_expression->type;
#line 3704 "bootstrap/stage0/ReCode.code"
    if (callee_type->kind != Checked_Type_Kind__POINTER || ((struct Checked_Pointer_Type*) callee_type)->other_type->kind != Checked_Type_Kind__FUNCTION) {
#line 3705 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->super.location, String__create_from("Not a function"));
#line 3706 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3708 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = (struct Checked_Function_Type*) ((struct Checked_Pointer_Type*) callee_type)->other_type;
#line 3709 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Argument* first_argument = NULL;
#line 3710 "bootstrap/stage0/ReCode.code"
    if (parsed_expression->first_argument != NULL) {
#line 3711 "bootstrap/stage0/ReCode.code"
        struct Checked_Call_Argument* last_argument = NULL;
#line 3712 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_parameter = function_type->first_parameter;
#line 3713 "bootstrap/stage0/ReCode.code"
        struct Parsed_Call_Argument* parsed_argument = parsed_expression->first_argument;
#line 3714 "bootstrap/stage0/ReCode.code"
        while (function_parameter != NULL && parsed_argument != NULL) {
#line 3715 "bootstrap/stage0/ReCode.code"
            struct Checked_Expression* argument_expression = Checker__check_expression(self, parsed_argument->expression);
#line 3716 "bootstrap/stage0/ReCode.code"
            Checked_Type__expect_same_type(function_parameter->type, argument_expression->type, argument_expression->location);
#line 3717 "bootstrap/stage0/ReCode.code"
            struct Checked_Call_Argument* argument = Checked_Call_Argument__create(argument_expression);
#line 3718 "bootstrap/stage0/ReCode.code"
            if (last_argument == NULL) {
#line 3719 "bootstrap/stage0/ReCode.code"
                first_argument = argument;
            } else {
#line 3721 "bootstrap/stage0/ReCode.code"
                last_argument->next_argument = argument;
            }
#line 3723 "bootstrap/stage0/ReCode.code"
            last_argument = argument;
#line 3724 "bootstrap/stage0/ReCode.code"
            function_parameter = function_parameter->next_parameter;
#line 3725 "bootstrap/stage0/ReCode.code"
            parsed_argument = parsed_argument->next_argument;
        }
#line 3727 "bootstrap/stage0/ReCode.code"
        if (function_parameter != NULL) {
#line 3728 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too few arguments"));
#line 3729 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 3731 "bootstrap/stage0/ReCode.code"
        if (parsed_argument != NULL) {
#line 3732 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too many arguments"));
#line 3733 "bootstrap/stage0/ReCode.code"
            abort();
        }
    }
#line 3736 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Call_Expression__create(parsed_expression->super.location, function_type->return_type, callee_expression, first_argument);
}

#line 3739 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_cast_expression(struct Checker* self, struct Parsed_Cast_Expression* parsed_expression) {
#line 3740 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = Checker__resolve_type(self, parsed_expression->type);
#line 3741 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3742 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* other_type = other_expression->type;
#line 3743 "bootstrap/stage0/ReCode.code"
    bool can_cast = false;
#line 3744 "bootstrap/stage0/ReCode.code"
    if (type->kind == Checked_Type_Kind__POINTER) {
#line 3745 "bootstrap/stage0/ReCode.code"
        if (other_type->kind == Checked_Type_Kind__POINTER) {
#line 3746 "bootstrap/stage0/ReCode.code"
            can_cast = true;
        }
    } else if (Checked_Type__is_scalar_type(type)) {
#line 3749 "bootstrap/stage0/ReCode.code"
        if (Checked_Type__is_scalar_type(type)) {
#line 3750 "bootstrap/stage0/ReCode.code"
            can_cast = true;
        }
    }
#line 3753 "bootstrap/stage0/ReCode.code"
    if (Checked_Type__equals(type, other_type)) {
#line 3754 "bootstrap/stage0/ReCode.code"
        Source_Location__warning(parsed_expression->super.super.location, String__create_from("Redundant cast"));
    }
#line 3756 "bootstrap/stage0/ReCode.code"
    if (!can_cast) {
#line 3757 "bootstrap/stage0/ReCode.code"
        struct String* message = String__create_from("Cannot cast \"");
#line 3758 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, other_expression->type);
#line 3759 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\" to \"");
#line 3760 "bootstrap/stage0/ReCode.code"
        String__append_checked_type(message, type);
#line 3761 "bootstrap/stage0/ReCode.code"
        String__append_cstring(message, "\".");
#line 3762 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->super.super.location, message);
#line 3763 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3765 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Cast_Expression__create(parsed_expression->super.super.location, type, other_expression);
}

#line 3768 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_character_expression(struct Checker* self, struct Parsed_Character_Expression* parsed_expression) {
#line 3769 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR);
#line 3770 "bootstrap/stage0/ReCode.code"
    char value = parsed_expression->value;
#line 3771 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3774 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_dereference_expression(struct Checker* self, struct Parsed_Dereference_Expression* parsed_expression) {
#line 3775 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* value_expression = Checker__check_expression(self, parsed_expression->value_expression);
#line 3776 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* value_type = value_expression->type;
#line 3777 "bootstrap/stage0/ReCode.code"
    if (value_type->kind != Checked_Type_Kind__POINTER) {
#line 3778 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_expression->super.location, String__create_from("Not a pointer value"));
#line 3779 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3781 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Dereference_Expression__create(parsed_expression->super.location, ((struct Checked_Pointer_Type*) value_type)->other_type, value_expression);
}

#line 3784 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_divide_expression(struct Checker* self, struct Parsed_Divide_Expression* parsed_expression) {
#line 3785 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3786 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3787 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3788 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3789 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3792 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_equals_expression(struct Checker* self, struct Parsed_Equals_Expression* parsed_expression) {
#line 3793 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3794 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3795 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3796 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3799 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_expression(struct Checker* self, struct Parsed_Greater_Expression* parsed_expression) {
#line 3800 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3801 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3802 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3803 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3804 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Greater_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3807 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_greater_or_equals_expression(struct Checker* self, struct Parsed_Greater_Or_Equals_Expression* parsed_expression) {
#line 3808 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3809 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3810 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3811 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3812 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3815 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_group_expression(struct Checker* self, struct Parsed_Group_Expression* parsed_expression) {
#line 3816 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->other_expression);
#line 3817 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

#line 3820 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_integer_expression(struct Checker* self, struct Parsed_Integer_Expression* parsed_expression) {
#line 3821 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__I32);
#line 3822 "bootstrap/stage0/ReCode.code"
    uint64_t value = parsed_expression->value;
#line 3823 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3826 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_expression(struct Checker* self, struct Parsed_Less_Expression* parsed_expression) {
#line 3827 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3828 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3829 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3830 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3831 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Less_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3834 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_less_or_equals_expression(struct Checker* self, struct Parsed_Less_Or_Equals_Expression* parsed_expression) {
#line 3835 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3836 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3837 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3838 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3839 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3842 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_and_expression(struct Checker* self, struct Parsed_Logic_And_Expression* parsed_expression) {
#line 3843 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3844 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression->type, left_expression->location);
#line 3845 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3846 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3847 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3850 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_logic_or_expression(struct Checker* self, struct Parsed_Logic_Or_Expression* parsed_expression) {
#line 3851 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3852 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression->type, left_expression->location);
#line 3853 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3854 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3855 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3858 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_member_access_expression(struct Checker* self, struct Parsed_Member_Access_Expression* parsed_expression) {
#line 3859 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* object_expression = Checker__check_expression(self, parsed_expression->object_expression);
#line 3860 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* object_type = object_expression->type;
#line 3861 "bootstrap/stage0/ReCode.code"
    if (object_type->kind == Checked_Type_Kind__POINTER) {
#line 3862 "bootstrap/stage0/ReCode.code"
        object_type = ((struct Checked_Pointer_Type*) object_type)->other_type;
#line 3863 "bootstrap/stage0/ReCode.code"
        if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3864 "bootstrap/stage0/ReCode.code"
            return Checker__check_struct_member_access_expression(self, object_expression, (struct Checked_Struct_Type*) object_type, parsed_expression->member_name);
        }
    } else if (object_type->kind == Checked_Type_Kind__STRUCT) {
#line 3867 "bootstrap/stage0/ReCode.code"
        return Checker__check_struct_member_access_expression(self, object_expression, (struct Checked_Struct_Type*) object_type, parsed_expression->member_name);
    } else if (object_type->kind == Checked_Type_Kind__DEFINED) {
#line 3869 "bootstrap/stage0/ReCode.code"
        struct Checked_Named_Type* defined_type = ((struct Checked_Defined_Type*) object_type)->defined_type;
#line 3870 "bootstrap/stage0/ReCode.code"
        if (defined_type->super.kind == Checked_Type_Kind__ENUM) {
#line 3871 "bootstrap/stage0/ReCode.code"
            struct Checked_Enum_Type* enum_type = (struct Checked_Enum_Type*) defined_type;
#line 3872 "bootstrap/stage0/ReCode.code"
            struct Checked_Enum_Member* enum_member = Checked_Enum_Type__find_member(enum_type, parsed_expression->member_name->lexeme);
#line 3873 "bootstrap/stage0/ReCode.code"
            if (enum_member == NULL) {
#line 3874 "bootstrap/stage0/ReCode.code"
                Source_Location__error(object_expression->location, String__create_from("No such enum members"));
#line 3875 "bootstrap/stage0/ReCode.code"
                abort();
            }
#line 3877 "bootstrap/stage0/ReCode.code"
            return (struct Checked_Expression*) Checked_Symbol_Expression__create(object_expression->location, (struct Checked_Type*) enum_type, enum_member->symbol);
        }
#line 3879 "bootstrap/stage0/ReCode.code"
        Source_Location__error(object_expression->location, String__create_from("Type has no members"));
#line 3880 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3882 "bootstrap/stage0/ReCode.code"
    Source_Location__error(object_expression->location, String__create_from("Unsupported type"));
#line 3883 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 3886 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_struct_member_access_expression(struct Checker* self, struct Checked_Expression* object_expression, struct Checked_Struct_Type* struct_type, struct Token* member_name) {
#line 3887 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* member = Checked_Struct_Type__find_member(struct_type, member_name->lexeme);
#line 3888 "bootstrap/stage0/ReCode.code"
    if (member == NULL) {
#line 3889 "bootstrap/stage0/ReCode.code"
        if (struct_type->super_type != NULL) {
#line 3890 "bootstrap/stage0/ReCode.code"
            object_expression = (struct Checked_Expression*) Checked_Member_Access_Expression__create(object_expression->location, struct_type->first_member->type, object_expression, struct_type->first_member);
#line 3891 "bootstrap/stage0/ReCode.code"
            return Checker__check_struct_member_access_expression(self, object_expression, struct_type->super_type, member_name);
        }
#line 3893 "bootstrap/stage0/ReCode.code"
        Source_Location__error(member_name->location, String__create_from("No such struct member"));
#line 3894 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3896 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Member_Access_Expression__create(object_expression->location, member->type, object_expression, member);
}

#line 3899 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_minus_expression(struct Checker* self, struct Parsed_Minus_Expression* parsed_expression) {
#line 3900 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3901 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* other_expression_type = other_expression->type;
#line 3902 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(other_expression_type, other_expression->location);
#line 3903 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

#line 3906 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_modulo_expression(struct Checker* self, struct Parsed_Modulo_Expression* parsed_expression) {
#line 3907 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3908 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3909 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3910 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3911 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3914 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_multiply_expression(struct Checker* self, struct Parsed_Multiply_Expression* parsed_expression) {
#line 3915 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3916 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3917 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3918 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3919 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3922 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_expression(struct Checker* self, struct Parsed_Not_Expression* parsed_expression) {
#line 3923 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
#line 3924 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* other_expression_type = other_expression->type;
#line 3925 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), other_expression_type, other_expression->location);
#line 3926 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

#line 3929 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_not_equals_expression(struct Checker* self, struct Parsed_Not_Equals_Expression* parsed_expression) {
#line 3930 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3931 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3932 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3933 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), left_expression, right_expression);
}

#line 3936 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_null_expression(struct Checker* self, struct Parsed_Null_Expression* parsed_expression) {
#line 3937 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__NULL);
#line 3938 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

#line 3941 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_sizeof_expression(struct Checker* self, struct Parsed_Sizeof_Expression* parsed_expression) {
#line 3942 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__USIZE);
#line 3943 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* sized_type = Checker__resolve_type(self, parsed_expression->type);
#line 3944 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

#line 3947 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_string_expression(struct Checker* self, struct Parsed_String_Expression* parsed_expression) {
#line 3948 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* char_type = (struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__CHAR);
#line 3949 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* expression_type = (struct Checked_Type*) Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type);
#line 3950 "bootstrap/stage0/ReCode.code"
    struct String* value = parsed_expression->value;
#line 3951 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

#line 3954 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_substract_expression(struct Checker* self, struct Parsed_Substract_Expression* parsed_expression) {
#line 3955 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
#line 3956 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
#line 3957 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
#line 3958 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
#line 3959 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

#line 3962 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_symbol_expression(struct Checker* self, struct Parsed_Symbol_Expression* parsed_expression) {
#line 3963 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = Checked_Symbols__find_symbol(self->symbols, parsed_expression->name->lexeme);
#line 3964 "bootstrap/stage0/ReCode.code"
    if (symbol == NULL) {
#line 3965 "bootstrap/stage0/ReCode.code"
        Token__error(parsed_expression->name, String__create_from("Undefined symbol"));
#line 3966 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3968 "bootstrap/stage0/ReCode.code"
    if (symbol->type == NULL) {
#line 3969 "bootstrap/stage0/ReCode.code"
        Token__error(parsed_expression->name, String__create_from("Symbol without type"));
#line 3970 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 3972 "bootstrap/stage0/ReCode.code"
    return (struct Checked_Expression*) Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol);
}

#line 3975 "bootstrap/stage0/ReCode.code"
struct Checked_Expression* Checker__check_expression(struct Checker* self, struct Parsed_Expression* parsed_expression) {
#line 3976 "bootstrap/stage0/ReCode.code"
    if (parsed_expression->kind == Parsed_Expression_Kind__ADD) {
#line 3977 "bootstrap/stage0/ReCode.code"
        return Checker__check_add_expression(self, (struct Parsed_Add_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__ADDRESS_OF) {
#line 3979 "bootstrap/stage0/ReCode.code"
        return Checker__check_address_of_expression(self, (struct Parsed_Address_Of_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__ARRAY_ACCESS) {
#line 3981 "bootstrap/stage0/ReCode.code"
        return Checker__check_array_access_expression(self, (struct Parsed_Array_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__BOOL) {
#line 3983 "bootstrap/stage0/ReCode.code"
        return Checker__check_bool_expression(self, (struct Parsed_Bool_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__CALL) {
#line 3985 "bootstrap/stage0/ReCode.code"
        return Checker__check_call_expression(self, (struct Parsed_Call_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__CAST) {
#line 3987 "bootstrap/stage0/ReCode.code"
        return Checker__check_cast_expression(self, (struct Parsed_Cast_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__CHARACTER) {
#line 3989 "bootstrap/stage0/ReCode.code"
        return Checker__check_character_expression(self, (struct Parsed_Character_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__DEREFERENCE) {
#line 3991 "bootstrap/stage0/ReCode.code"
        return Checker__check_dereference_expression(self, (struct Parsed_Dereference_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__DIVIDE) {
#line 3993 "bootstrap/stage0/ReCode.code"
        return Checker__check_divide_expression(self, (struct Parsed_Divide_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__EQUALS) {
#line 3995 "bootstrap/stage0/ReCode.code"
        return Checker__check_equals_expression(self, (struct Parsed_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__GREATER) {
#line 3997 "bootstrap/stage0/ReCode.code"
        return Checker__check_greater_expression(self, (struct Parsed_Greater_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__GREATER_OR_EQUALS) {
#line 3999 "bootstrap/stage0/ReCode.code"
        return Checker__check_greater_or_equals_expression(self, (struct Parsed_Greater_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__GROUP) {
#line 4001 "bootstrap/stage0/ReCode.code"
        return Checker__check_group_expression(self, (struct Parsed_Group_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__INTEGER) {
#line 4003 "bootstrap/stage0/ReCode.code"
        return Checker__check_integer_expression(self, (struct Parsed_Integer_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LESS) {
#line 4005 "bootstrap/stage0/ReCode.code"
        return Checker__check_less_expression(self, (struct Parsed_Less_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LESS_OR_EQUALS) {
#line 4007 "bootstrap/stage0/ReCode.code"
        return Checker__check_less_or_equals_expression(self, (struct Parsed_Less_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_AND) {
#line 4009 "bootstrap/stage0/ReCode.code"
        return Checker__check_logic_and_expression(self, (struct Parsed_Logic_And_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__LOGIC_OR) {
#line 4011 "bootstrap/stage0/ReCode.code"
        return Checker__check_logic_or_expression(self, (struct Parsed_Logic_Or_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MEMBER_ACCESS) {
#line 4013 "bootstrap/stage0/ReCode.code"
        return Checker__check_member_access_expression(self, (struct Parsed_Member_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MINUS) {
#line 4015 "bootstrap/stage0/ReCode.code"
        return Checker__check_minus_expression(self, (struct Parsed_Minus_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MODULO) {
#line 4017 "bootstrap/stage0/ReCode.code"
        return Checker__check_modulo_expression(self, (struct Parsed_Modulo_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__MULTIPLY) {
#line 4019 "bootstrap/stage0/ReCode.code"
        return Checker__check_multiply_expression(self, (struct Parsed_Multiply_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__NOT) {
#line 4021 "bootstrap/stage0/ReCode.code"
        return Checker__check_not_expression(self, (struct Parsed_Not_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__NOT_EQUALS) {
#line 4023 "bootstrap/stage0/ReCode.code"
        return Checker__check_not_equals_expression(self, (struct Parsed_Not_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__NULL) {
#line 4025 "bootstrap/stage0/ReCode.code"
        return Checker__check_null_expression(self, (struct Parsed_Null_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__SIZEOF) {
#line 4027 "bootstrap/stage0/ReCode.code"
        return Checker__check_sizeof_expression(self, (struct Parsed_Sizeof_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__STRING) {
#line 4029 "bootstrap/stage0/ReCode.code"
        return Checker__check_string_expression(self, (struct Parsed_String_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__SUBSTRACT) {
#line 4031 "bootstrap/stage0/ReCode.code"
        return Checker__check_substract_expression(self, (struct Parsed_Substract_Expression*) parsed_expression);
    } else if (parsed_expression->kind == Parsed_Expression_Kind__SYMBOL) {
#line 4033 "bootstrap/stage0/ReCode.code"
        return Checker__check_symbol_expression(self, (struct Parsed_Symbol_Expression*) parsed_expression);
    }
#line 4035 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_expression->location, String__create_from("Unsupported expression kind"));
#line 4036 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 4039 "bootstrap/stage0/ReCode.code"
void Checker__check_enum_statement(struct Checker* self, struct Parsed_Enum_Statement* parsed_statement) {
#line 4040 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Type* enum_type = Checked_Enum_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4041 "bootstrap/stage0/ReCode.code"
    Checker__append_type(self, (struct Checked_Named_Type*) enum_type);
#line 4043 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* last_enum_member = NULL;
#line 4044 "bootstrap/stage0/ReCode.code"
    struct Parsed_Enum_Member* parsed_enum_member = parsed_statement->first_member;
#line 4045 "bootstrap/stage0/ReCode.code"
    while (parsed_enum_member != NULL) {
#line 4046 "bootstrap/stage0/ReCode.code"
        struct Checked_Enum_Member* enum_member = Checked_Enum_Member__create(parsed_enum_member->name->location, parsed_enum_member->name->lexeme);
#line 4047 "bootstrap/stage0/ReCode.code"
        struct String* enum_member_symbol_name = String__append_string(String__append_cstring(String__append_string(String__create(), enum_type->super.name), "__"), enum_member->name);
#line 4048 "bootstrap/stage0/ReCode.code"
        enum_member->symbol = (struct Checked_Symbol*) Checked_Enum_Member_Symbol__create(enum_member->location, enum_member_symbol_name, (struct Checked_Type*) enum_type);
#line 4049 "bootstrap/stage0/ReCode.code"
        Checked_Symbols__append_symbol(self->symbols, enum_member->symbol);
#line 4050 "bootstrap/stage0/ReCode.code"
        if (last_enum_member == NULL) {
#line 4051 "bootstrap/stage0/ReCode.code"
            enum_type->first_member = enum_member;
        } else {
#line 4053 "bootstrap/stage0/ReCode.code"
            last_enum_member->next_member = enum_member;
        }
#line 4055 "bootstrap/stage0/ReCode.code"
        last_enum_member = enum_member;
#line 4056 "bootstrap/stage0/ReCode.code"
        parsed_enum_member = parsed_enum_member->next_member;
    }
}

#line 4060 "bootstrap/stage0/ReCode.code"
void Checker__check_function_type_statement(struct Checker* self, struct Parsed_Function_Type_Statement* parsed_statement) {
#line 4061 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4062 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type;
#line 4063 "bootstrap/stage0/ReCode.code"
    if (other_type != NULL) {
#line 4064 "bootstrap/stage0/ReCode.code"
        TODO("Handle type redeclaration");
#line 4065 "bootstrap/stage0/ReCode.code"
        abort();
    } else {
#line 4067 "bootstrap/stage0/ReCode.code"
        struct Checked_Type* return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 4068 "bootstrap/stage0/ReCode.code"
        function_type = Checked_Function_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, return_type);
#line 4069 "bootstrap/stage0/ReCode.code"
        Checker__append_type(self, (struct Checked_Named_Type*) function_type);
    }
#line 4072 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->first_parameter != NULL) {
#line 4073 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* last_function_parameter = NULL;
#line 4074 "bootstrap/stage0/ReCode.code"
        struct Parsed_Function_Type_Parameter* parsed_parameter = parsed_statement->first_parameter;
#line 4075 "bootstrap/stage0/ReCode.code"
        while (parsed_parameter != NULL) {
#line 4076 "bootstrap/stage0/ReCode.code"
            struct Checked_Type* function_parameter_type = Checker__resolve_type(self, parsed_parameter->type);
#line 4077 "bootstrap/stage0/ReCode.code"
            struct Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, function_parameter_type);
#line 4078 "bootstrap/stage0/ReCode.code"
            if (last_function_parameter == NULL) {
#line 4079 "bootstrap/stage0/ReCode.code"
                function_type->first_parameter = function_parameter;
            } else {
#line 4081 "bootstrap/stage0/ReCode.code"
                last_function_parameter->next_parameter = function_parameter;
            }
#line 4083 "bootstrap/stage0/ReCode.code"
            last_function_parameter = function_parameter;
#line 4084 "bootstrap/stage0/ReCode.code"
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
}

#line 4089 "bootstrap/stage0/ReCode.code"
void Checker__create_opaque_type(struct Checker* self, struct Parsed_Opaque_Type_Statement* parsed_statement) {
#line 4090 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4091 "bootstrap/stage0/ReCode.code"
    if (other_type != NULL) {
#line 4092 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4093 "bootstrap/stage0/ReCode.code"
        abort();
    } else {
#line 4095 "bootstrap/stage0/ReCode.code"
        struct Checked_Opaque_Type* opaque_type = Checked_Opaque_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4096 "bootstrap/stage0/ReCode.code"
        Checker__append_type(self, (struct Checked_Named_Type*) opaque_type);
    }
}

#line 4100 "bootstrap/stage0/ReCode.code"
void Checker__create_struct_type(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) {
#line 4101 "bootstrap/stage0/ReCode.code"
    struct Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4102 "bootstrap/stage0/ReCode.code"
    if (other_type != NULL) {
#line 4103 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Type declared first here: "), other_type->super.location));
#line 4104 "bootstrap/stage0/ReCode.code"
        abort();
    } else {
#line 4106 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Type* struct_type = Checked_Struct_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
#line 4107 "bootstrap/stage0/ReCode.code"
        Checker__append_type(self, (struct Checked_Named_Type*) struct_type);
    }
}

#line 4111 "bootstrap/stage0/ReCode.code"
void Checker__check_struct_statement(struct Checker* self, struct Parsed_Struct_Statement* parsed_statement) {
#line 4112 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Type* struct_type = (struct Checked_Struct_Type*) Checker__find_type(self, parsed_statement->super.name->lexeme);
#line 4113 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->first_member != NULL) {
#line 4114 "bootstrap/stage0/ReCode.code"
        struct Checked_Struct_Member* last_struct_member = NULL;
#line 4115 "bootstrap/stage0/ReCode.code"
        struct Parsed_Struct_Member* parsed_member = parsed_statement->first_member;
#line 4116 "bootstrap/stage0/ReCode.code"
        while (parsed_member != NULL) {
#line 4117 "bootstrap/stage0/ReCode.code"
            struct Checked_Struct_Member* struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
#line 4118 "bootstrap/stage0/ReCode.code"
            if (struct_member != NULL) {
#line 4119 "bootstrap/stage0/ReCode.code"
                Source_Location__error(parsed_member->name->location, String__append_source_location(String__create_from("Struct member declared first here: "), struct_member->location));
#line 4120 "bootstrap/stage0/ReCode.code"
                abort();
            }
#line 4122 "bootstrap/stage0/ReCode.code"
            struct Checked_Type* struct_member_type = Checker__resolve_type(self, parsed_member->type);
#line 4123 "bootstrap/stage0/ReCode.code"
            struct_member = Checked_Struct_Member__create(parsed_member->name->location, parsed_member->name->lexeme, struct_member_type);
#line 4124 "bootstrap/stage0/ReCode.code"
            if (String__equals_cstring(struct_member->name, "super")) {
#line 4125 "bootstrap/stage0/ReCode.code"
                if (struct_type->first_member != NULL) {
#line 4126 "bootstrap/stage0/ReCode.code"
                    Source_Location__error(parsed_member->name->location, String__create_from("Must be the first struct member"));
#line 4127 "bootstrap/stage0/ReCode.code"
                    abort();
                }
#line 4129 "bootstrap/stage0/ReCode.code"
                if (struct_member->type->kind != Checked_Type_Kind__STRUCT) {
#line 4130 "bootstrap/stage0/ReCode.code"
                    Source_Location__error(parsed_member->type->location, String__create_from("Must be a struct"));
#line 4131 "bootstrap/stage0/ReCode.code"
                    abort();
                }
#line 4133 "bootstrap/stage0/ReCode.code"
                struct Checked_Struct_Type* struct_super_type = (struct Checked_Struct_Type*) struct_member->type;
#line 4134 "bootstrap/stage0/ReCode.code"
                struct Checked_Struct_Type* other_struct_type = struct_super_type;
#line 4135 "bootstrap/stage0/ReCode.code"
                while (other_struct_type != NULL) {
#line 4136 "bootstrap/stage0/ReCode.code"
                    if (other_struct_type == struct_type) {
#line 4137 "bootstrap/stage0/ReCode.code"
                        Source_Location__error(parsed_member->type->location, String__create_from("Type recursivity"));
#line 4138 "bootstrap/stage0/ReCode.code"
                        abort();
                    }
#line 4140 "bootstrap/stage0/ReCode.code"
                    other_struct_type = other_struct_type->super_type;
                }
#line 4142 "bootstrap/stage0/ReCode.code"
                struct_type->super_type = struct_super_type;
            }
#line 4144 "bootstrap/stage0/ReCode.code"
            if (last_struct_member == NULL) {
#line 4145 "bootstrap/stage0/ReCode.code"
                struct_type->first_member = struct_member;
            } else {
#line 4147 "bootstrap/stage0/ReCode.code"
                last_struct_member->next_member = struct_member;
            }
#line 4149 "bootstrap/stage0/ReCode.code"
            last_struct_member = struct_member;
#line 4150 "bootstrap/stage0/ReCode.code"
            parsed_member = parsed_member->next_member;
        }
    }
}

#line 4155 "bootstrap/stage0/ReCode.code"
struct Checked_Assignment_Statement* Checker__check_assignment_statement(struct Checker* self, struct Parsed_Assignment_Statement* parsed_statement) {
#line 4156 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* object_expression = Checker__check_expression(self, parsed_statement->object_expression);
#line 4157 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* value_expression = Checker__check_expression(self, parsed_statement->value_expression);
#line 4158 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type(object_expression->type, value_expression->type, value_expression->location);
#line 4159 "bootstrap/stage0/ReCode.code"
    return Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);
}

#line 4162 "bootstrap/stage0/ReCode.code"
struct Checked_Block_Statement* Checker__check_block_statement(struct Checker* self, struct Parsed_Block_Statement* parsed_statement) {
#line 4163 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* statements = Checker__check_statements(self, parsed_statement->statements);
#line 4164 "bootstrap/stage0/ReCode.code"
    return Checked_Block_Statement__create(parsed_statement->super.location, statements);
}

#line 4167 "bootstrap/stage0/ReCode.code"
struct Checked_Break_Statement* Checker__check_break_statement(struct Checker* self, struct Parsed_Break_Statement* parsed_statement) {
#line 4168 "bootstrap/stage0/ReCode.code"
    return Checked_Break_Statement__create(parsed_statement->super.location);
}

#line 4171 "bootstrap/stage0/ReCode.code"
struct Checked_Expression_Statement* Checker__check_expression_statement(struct Checker* self, struct Parsed_Expression_Statement* parsed_statement) {
#line 4172 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = Checker__check_expression(self, parsed_statement->expression);
#line 4173 "bootstrap/stage0/ReCode.code"
    if (!Checked_Type__equals((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__VOID), expression->type)) {
    }
#line 4176 "bootstrap/stage0/ReCode.code"
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

#line 4179 "bootstrap/stage0/ReCode.code"
struct Checked_If_Statement* Checker__check_if_statement(struct Checker* self, struct Parsed_If_Statement* parsed_statement) {
#line 4180 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4181 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), considition_expression->type, considition_expression->location);
#line 4182 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* true_statement = Checker__check_statement(self, parsed_statement->true_statement);
#line 4183 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* false_statement = NULL;
#line 4184 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->false_statement != NULL) {
#line 4185 "bootstrap/stage0/ReCode.code"
        false_statement = Checker__check_statement(self, parsed_statement->false_statement);
    }
#line 4187 "bootstrap/stage0/ReCode.code"
    return Checked_If_Statement__create(parsed_statement->super.location, considition_expression, true_statement, false_statement);
}

#line 4190 "bootstrap/stage0/ReCode.code"
struct Checked_Return_Statement* Checker__check_return_statement(struct Checker* self, struct Parsed_Return_Statement* parsed_statement) {
#line 4191 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = NULL;
#line 4192 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->expression != NULL) {
#line 4193 "bootstrap/stage0/ReCode.code"
        expression = Checker__check_expression(self, parsed_statement->expression);
#line 4194 "bootstrap/stage0/ReCode.code"
        Checked_Type__expect_same_type(self->return_type, expression->type, expression->location);
    } else if (self->return_type->kind != Checked_Type_Kind__VOID) {
#line 4196 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_statement->super.location, String__create_from("Missing expression"));
#line 4197 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 4199 "bootstrap/stage0/ReCode.code"
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);
}

#line 4202 "bootstrap/stage0/ReCode.code"
struct Checked_Variable_Statement* Checker__check_variable_statement(struct Checker* self, struct Parsed_Variable_Statement* parsed_statement) {
#line 4203 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* type = NULL;
#line 4204 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->type != NULL) {
#line 4205 "bootstrap/stage0/ReCode.code"
        type = Checker__resolve_type(self, parsed_statement->type);
#line 4206 "bootstrap/stage0/ReCode.code"
        if (type->kind == Checked_Type_Kind__OPAQUE) {
#line 4207 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->super.super.location, String__create_from("Variable cannot have an opaque type"));
#line 4208 "bootstrap/stage0/ReCode.code"
            abort();
        }
    }
#line 4211 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* expression = NULL;
#line 4212 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->expression != NULL) {
#line 4213 "bootstrap/stage0/ReCode.code"
        expression = Checker__check_expression(self, parsed_statement->expression);
#line 4214 "bootstrap/stage0/ReCode.code"
        if (type != NULL) {
#line 4215 "bootstrap/stage0/ReCode.code"
            Checked_Type__expect_same_type(type, expression->type, expression->location);
#line 4216 "bootstrap/stage0/ReCode.code"
            if (expression->type->kind != Checked_Type_Kind__NULL) {
#line 4217 "bootstrap/stage0/ReCode.code"
                Source_Location__warning(parsed_statement->type->location, String__create_from("Redundant type declaration"));
            }
        } else {
#line 4220 "bootstrap/stage0/ReCode.code"
            type = expression->type;
        }
    }
#line 4223 "bootstrap/stage0/ReCode.code"
    if (type == NULL || type->kind == Checked_Type_Kind__NULL) {
#line 4224 "bootstrap/stage0/ReCode.code"
        Source_Location__error(parsed_statement->super.super.location, String__create_from("Unknown variable type"));
#line 4225 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 4227 "bootstrap/stage0/ReCode.code"
    struct Checked_Variable_Symbol* variable = Checked_Variable__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
#line 4228 "bootstrap/stage0/ReCode.code"
    Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) variable);
#line 4229 "bootstrap/stage0/ReCode.code"
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);
}

#line 4232 "bootstrap/stage0/ReCode.code"
struct Checked_While_Statement* Checker__check_while_statement(struct Checker* self, struct Parsed_While_Statement* parsed_statement) {
#line 4233 "bootstrap/stage0/ReCode.code"
    struct Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
#line 4234 "bootstrap/stage0/ReCode.code"
    Checked_Type__expect_same_type((struct Checked_Type*) Checker__get_builtin_type(self, Checked_Type_Kind__BOOL), considition_expression->type, considition_expression->location);
#line 4235 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* body_statement = Checker__check_statement(self, parsed_statement->body_statement);
#line 4236 "bootstrap/stage0/ReCode.code"
    return Checked_While_Statement__create(parsed_statement->super.location, considition_expression, body_statement);
}

#line 4239 "bootstrap/stage0/ReCode.code"
void Checker__check_function_declaration(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) {
#line 4240 "bootstrap/stage0/ReCode.code"
    struct String* function_name = parsed_statement->super.name->lexeme;
#line 4241 "bootstrap/stage0/ReCode.code"
    struct Checked_Type* function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
#line 4242 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Parameter* function_first_parameter = NULL;
#line 4243 "bootstrap/stage0/ReCode.code"
    struct Parsed_Function_Parameter* parsed_parameter = parsed_statement->first_parameter;
#line 4244 "bootstrap/stage0/ReCode.code"
    if (parsed_parameter != NULL) {
#line 4245 "bootstrap/stage0/ReCode.code"
        function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
#line 4246 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* function_last_parameter = function_first_parameter;
#line 4247 "bootstrap/stage0/ReCode.code"
        parsed_parameter = parsed_parameter->next_parameter;
#line 4248 "bootstrap/stage0/ReCode.code"
        while (parsed_parameter != NULL) {
#line 4249 "bootstrap/stage0/ReCode.code"
            struct Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
#line 4250 "bootstrap/stage0/ReCode.code"
            function_last_parameter->next_parameter = function_parameter;
#line 4251 "bootstrap/stage0/ReCode.code"
            function_last_parameter = function_parameter;
#line 4252 "bootstrap/stage0/ReCode.code"
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
#line 4255 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_name, function_return_type);
#line 4256 "bootstrap/stage0/ReCode.code"
    function_type->first_parameter = function_first_parameter;
#line 4258 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* other_symbol = Checked_Symbols__find_sibling_symbol(self->symbols, function_name);
#line 4259 "bootstrap/stage0/ReCode.code"
    if (other_symbol != NULL) {
#line 4260 "bootstrap/stage0/ReCode.code"
        if (other_symbol->kind != Checked_Symbol_Kind__FUNCTION || !Checked_Type__equals((struct Checked_Type*) function_type, (struct Checked_Type*) ((struct Checked_Function_Symbol*) other_symbol)->function_type)) {
#line 4261 "bootstrap/stage0/ReCode.code"
            TODO("Report overloaded function");
#line 4262 "bootstrap/stage0/ReCode.code"
            abort();
        } else {
#line 4264 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->super.name->location, String__append_source_location(String__create_from("Function declared first here: "), other_symbol->location));
#line 4265 "bootstrap/stage0/ReCode.code"
            abort();
        }
    } else {
#line 4268 "bootstrap/stage0/ReCode.code"
        Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Function_Symbol__create(parsed_statement->super.name->location, function_name, function_type));
    }
}

#line 4272 "bootstrap/stage0/ReCode.code"
struct Checked_Statement* Checker__check_statement(struct Checker* self, struct Parsed_Statement* parsed_statement) {
#line 4273 "bootstrap/stage0/ReCode.code"
    if (parsed_statement->kind == Parsed_Statement_Kind__ASSIGNMENT) {
#line 4274 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_assignment_statement(self, (struct Parsed_Assignment_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__BLOCK) {
#line 4276 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_block_statement(self, (struct Parsed_Block_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__BREAK) {
#line 4278 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_break_statement(self, (struct Parsed_Break_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__EXPRESSION) {
#line 4280 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_expression_statement(self, (struct Parsed_Expression_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__IF) {
#line 4282 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_if_statement(self, (struct Parsed_If_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__RETURN) {
#line 4284 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_return_statement(self, (struct Parsed_Return_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4286 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_variable_statement(self, (struct Parsed_Variable_Statement*) parsed_statement);
    } else if (parsed_statement->kind == Parsed_Statement_Kind__WHILE) {
#line 4288 "bootstrap/stage0/ReCode.code"
        return (struct Checked_Statement*) Checker__check_while_statement(self, (struct Parsed_While_Statement*) parsed_statement);
    }
#line 4290 "bootstrap/stage0/ReCode.code"
    Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4291 "bootstrap/stage0/ReCode.code"
    abort();
}

#line 4294 "bootstrap/stage0/ReCode.code"
struct Checked_Statements* Checker__check_statements(struct Checker* self, struct Parsed_Statements* parsed_statements) {
#line 4296 "bootstrap/stage0/ReCode.code"
    self->symbols = Checked_Symbols__create(self->symbols);
#line 4298 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* checked_statements = Checked_Statements__create();
#line 4299 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* parsed_statement = parsed_statements->first_statement;
#line 4300 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4301 "bootstrap/stage0/ReCode.code"
        struct Checked_Statement* checked_statement = Checker__check_statement(self, parsed_statement);
#line 4302 "bootstrap/stage0/ReCode.code"
        Checked_Statements__append(checked_statements, checked_statement);
#line 4303 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4307 "bootstrap/stage0/ReCode.code"
    self->symbols = self->symbols->parent;
#line 4309 "bootstrap/stage0/ReCode.code"
    return checked_statements;
}

#line 4312 "bootstrap/stage0/ReCode.code"
void Checker__check_function_definition(struct Checker* self, struct Parsed_Function_Statement* parsed_statement) {
#line 4313 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* symbol = Checked_Symbols__find_sibling_symbol(self->symbols, parsed_statement->super.name->lexeme);
#line 4314 "bootstrap/stage0/ReCode.code"
    if (symbol == NULL || symbol->kind != Checked_Symbol_Kind__FUNCTION) {
#line 4315 "bootstrap/stage0/ReCode.code"
        TODO("Report missing function symbol");
#line 4316 "bootstrap/stage0/ReCode.code"
        abort();
    }
#line 4318 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Symbol* function_symbol = (struct Checked_Function_Symbol*) symbol;
#line 4319 "bootstrap/stage0/ReCode.code"
    struct Checked_Function_Type* function_type = function_symbol->function_type;
#line 4320 "bootstrap/stage0/ReCode.code"
    self->return_type = function_type->return_type;
#line 4323 "bootstrap/stage0/ReCode.code"
    self->symbols = Checked_Symbols__create(self->symbols);
#line 4325 "bootstrap/stage0/ReCode.code"
    if (function_type->first_parameter != NULL) {
#line 4327 "bootstrap/stage0/ReCode.code"
        struct Checked_Function_Parameter* parameter = function_type->first_parameter;
#line 4328 "bootstrap/stage0/ReCode.code"
        while (parameter != NULL) {
#line 4329 "bootstrap/stage0/ReCode.code"
            Checked_Symbols__append_symbol(self->symbols, (struct Checked_Symbol*) Checked_Function_Parameter_Symbol__create(parameter->location, parameter->name, parameter->type));
#line 4330 "bootstrap/stage0/ReCode.code"
            parameter = parameter->next_parameter;
        }
    }
#line 4335 "bootstrap/stage0/ReCode.code"
    function_symbol->checked_statements = Checker__check_statements(self, parsed_statement->statements);
#line 4338 "bootstrap/stage0/ReCode.code"
    self->symbols = self->symbols->parent;
}

#line 4341 "bootstrap/stage0/ReCode.code"
struct Checked_Source* Checker__check_source(struct Checker* self, struct Parsed_Source* parsed_source) {
#line 4342 "bootstrap/stage0/ReCode.code"
    struct Checked_Statements* checked_statements = Checked_Statements__create();
#line 4344 "bootstrap/stage0/ReCode.code"
    struct Parsed_Statement* parsed_statement;
#line 4347 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4348 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4349 "bootstrap/stage0/ReCode.code"
        struct Checked_Statement* checked_statement = NULL;
#line 4350 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4355 "bootstrap/stage0/ReCode.code"
            Checker__create_struct_type(self, (struct Parsed_Struct_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
#line 4357 "bootstrap/stage0/ReCode.code"
            Checker__create_opaque_type(self, (struct Parsed_Opaque_Type_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
#line 4359 "bootstrap/stage0/ReCode.code"
            Checker__check_enum_statement(self, (struct Parsed_Enum_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
        } else {
#line 4363 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4364 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4366 "bootstrap/stage0/ReCode.code"
        if (checked_statement != NULL) {
#line 4367 "bootstrap/stage0/ReCode.code"
            Checked_Statements__append(checked_statements, checked_statement);
        }
#line 4369 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4373 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4374 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4375 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
#line 4376 "bootstrap/stage0/ReCode.code"
            Checker__check_struct_statement(self, (struct Parsed_Struct_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
#line 4378 "bootstrap/stage0/ReCode.code"
            Checker__check_function_type_statement(self, (struct Parsed_Function_Type_Statement*) parsed_statement);
        }
#line 4380 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4384 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4385 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4386 "bootstrap/stage0/ReCode.code"
        struct Checked_Statement* checked_statement = NULL;
#line 4387 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4388 "bootstrap/stage0/ReCode.code"
            Checker__check_function_declaration(self, (struct Parsed_Function_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
#line 4390 "bootstrap/stage0/ReCode.code"
            checked_statement = (struct Checked_Statement*) Checker__check_variable_statement(self, (struct Parsed_Variable_Statement*) parsed_statement);
        } else if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
        } else {
#line 4400 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4401 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4403 "bootstrap/stage0/ReCode.code"
        if (checked_statement != NULL) {
#line 4404 "bootstrap/stage0/ReCode.code"
            Checked_Statements__append(checked_statements, checked_statement);
        }
#line 4406 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4410 "bootstrap/stage0/ReCode.code"
    parsed_statement = parsed_source->statements->first_statement;
#line 4411 "bootstrap/stage0/ReCode.code"
    while (parsed_statement != NULL) {
#line 4412 "bootstrap/stage0/ReCode.code"
        if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION) {
#line 4413 "bootstrap/stage0/ReCode.code"
            struct Parsed_Function_Statement* function_statement = (struct Parsed_Function_Statement*) parsed_statement;
#line 4414 "bootstrap/stage0/ReCode.code"
            if (function_statement->statements != NULL) {
#line 4415 "bootstrap/stage0/ReCode.code"
                Checker__check_function_definition(self, function_statement);
            }
        } else if (parsed_statement->kind == Parsed_Statement_Kind__VARIABLE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__STRUCT) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__OPAQUE_TYPE) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__ENUM) {
        } else if (parsed_statement->kind == Parsed_Statement_Kind__FUNCTION_TYPE) {
        } else {
#line 4428 "bootstrap/stage0/ReCode.code"
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
#line 4429 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4431 "bootstrap/stage0/ReCode.code"
        parsed_statement = parsed_statement->next_statement;
    }
#line 4434 "bootstrap/stage0/ReCode.code"
    struct Checked_Source* checked_source = (struct Checked_Source*) malloc(sizeof(struct Checked_Source));
#line 4435 "bootstrap/stage0/ReCode.code"
    checked_source->first_symbol = self->symbols->first_symbol;
#line 4436 "bootstrap/stage0/ReCode.code"
    checked_source->statements = checked_statements;
#line 4437 "bootstrap/stage0/ReCode.code"
    return checked_source;
}

#line 4440 "bootstrap/stage0/ReCode.code"
struct Checked_Source* check(struct Parsed_Source* parsed_source) {
#line 4441 "bootstrap/stage0/ReCode.code"
    struct Checker* type_checker = Checker__create();
#line 4443 "bootstrap/stage0/ReCode.code"
    return Checker__check_source(type_checker, parsed_source);
}

#line 4455 "bootstrap/stage0/ReCode.code"
void Generator__write_source_location(struct Generator* self, struct Source_Location* location) {
#line 4456 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "#line ");
#line 4457 "bootstrap/stage0/ReCode.code"
    File__write_i32(self->file, (int32_t) location->line);
#line 4458 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " \"");
#line 4459 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, location->source->path);
#line 4460 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "\"\n");
}

#line 4463 "bootstrap/stage0/ReCode.code"
void Generator__generate_add_expression(struct Generator* self, struct Checked_Add_Expression* expression) {
#line 4464 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4465 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " + ");
#line 4466 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4469 "bootstrap/stage0/ReCode.code"
void Generator__generate_address_of_expression(struct Generator* self, struct Checked_Address_Of_Expression* expression) {
#line 4470 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "&");
#line 4471 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4474 "bootstrap/stage0/ReCode.code"
void Generator__generate_array_access_expression(struct Generator* self, struct Checked_Array_Access_Expression* expression) {
#line 4475 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->array_expression);
#line 4476 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "[");
#line 4477 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->index_expression);
#line 4478 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "]");
}

#line 4481 "bootstrap/stage0/ReCode.code"
void Generator__generate_bool_expression(struct Generator* self, struct Checked_Bool_Expression* expression) {
#line 4482 "bootstrap/stage0/ReCode.code"
    if (expression->value) {
#line 4483 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "true");
    } else {
#line 4485 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "false");
    }
}

#line 4489 "bootstrap/stage0/ReCode.code"
void Generator__generate_call_expression(struct Generator* self, struct Checked_Call_Expression* expression) {
#line 4490 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->callee_expression);
#line 4491 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4492 "bootstrap/stage0/ReCode.code"
    struct Checked_Call_Argument* argument = expression->first_argument;
#line 4493 "bootstrap/stage0/ReCode.code"
    while (argument != NULL) {
#line 4494 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, argument->expression);
#line 4495 "bootstrap/stage0/ReCode.code"
        argument = argument->next_argument;
#line 4496 "bootstrap/stage0/ReCode.code"
        if (argument != NULL) {
#line 4497 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, ", ");
        }
    }
#line 4500 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");
}

#line 4503 "bootstrap/stage0/ReCode.code"
void Generator__generate_cast_expression(struct Generator* self, struct Checked_Cast_Expression* expression) {
#line 4504 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4505 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->super.type);
#line 4506 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4507 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
}

#line 4510 "bootstrap/stage0/ReCode.code"
void File__write_octal_escaped_char(struct File* stream, char value) {
#line 4511 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, '\\');
#line 4512 "bootstrap/stage0/ReCode.code"
    if (value > (char) 64) {
#line 4513 "bootstrap/stage0/ReCode.code"
        File__write_char(stream, value / (char) 64 % (char) 8 + '0');
    }
#line 4515 "bootstrap/stage0/ReCode.code"
    if (value > (char) 8) {
#line 4516 "bootstrap/stage0/ReCode.code"
        File__write_char(stream, value / (char) 8 % (char) 8 + '0');
    }
#line 4518 "bootstrap/stage0/ReCode.code"
    File__write_char(stream, value % (char) 8 + '0');
}

#line 4521 "bootstrap/stage0/ReCode.code"
void File__write_escaped_char(struct File* stream, char ch) {
#line 4522 "bootstrap/stage0/ReCode.code"
    if (ch < (char) 32) {
#line 4523 "bootstrap/stage0/ReCode.code"
        if (ch == '\n') {
#line 4524 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\n");
        } else if (ch == '\t') {
#line 4526 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\t");
        } else {
#line 4528 "bootstrap/stage0/ReCode.code"
            File__write_octal_escaped_char(stream, ch);
        }
    } else if (ch < (char) 127) {
#line 4531 "bootstrap/stage0/ReCode.code"
        if (ch == '\"') {
#line 4532 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\\"");
        } else if (ch == '\'') {
#line 4534 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\\'");
        } else if (ch == '\\') {
#line 4536 "bootstrap/stage0/ReCode.code"
            File__write_cstring(stream, "\\\\");
        } else {
#line 4538 "bootstrap/stage0/ReCode.code"
            File__write_char(stream, ch);
        }
    } else {
#line 4541 "bootstrap/stage0/ReCode.code"
        File__write_octal_escaped_char(stream, ch);
    }
}

#line 4545 "bootstrap/stage0/ReCode.code"
void Generator__generate_character_expression(struct Generator* self, struct Checked_Character_Expression* expression) {
#line 4546 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');
#line 4547 "bootstrap/stage0/ReCode.code"
    File__write_escaped_char(self->file, expression->value);
#line 4548 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\'');
}

#line 4551 "bootstrap/stage0/ReCode.code"
void Generator__generate_dereference_expression(struct Generator* self, struct Checked_Dereference_Expression* expression) {
#line 4552 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "*(");
#line 4553 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->value_expression);
#line 4554 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ')');
}

#line 4557 "bootstrap/stage0/ReCode.code"
void Generator__generate_divide_expression(struct Generator* self, struct Checked_Divide_Expression* expression) {
#line 4558 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4559 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " / ");
#line 4560 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4563 "bootstrap/stage0/ReCode.code"
void Generator__generate_equals_expression(struct Generator* self, struct Checked_Equals_Expression* expression) {
#line 4564 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4565 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " == ");
#line 4566 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4569 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_expression(struct Generator* self, struct Checked_Greater_Expression* expression) {
#line 4570 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4571 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " > ");
#line 4572 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4575 "bootstrap/stage0/ReCode.code"
void Generator__generate_greater_or_equals_expression(struct Generator* self, struct Checked_Greater_Or_Equals_Expression* expression) {
#line 4576 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4577 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " >= ");
#line 4578 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4581 "bootstrap/stage0/ReCode.code"
void Generator__generate_group_expression(struct Generator* self, struct Checked_Group_Expression* expression) {
#line 4582 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "(");
#line 4583 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->other_expression);
#line 4584 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");
}

#line 4587 "bootstrap/stage0/ReCode.code"
void Generator__generate_integer_expression(struct Generator* self, struct Checked_Integer_Expression* expression) {
#line 4588 "bootstrap/stage0/ReCode.code"
    File__write_u64(self->file, expression->value);
}

#line 4591 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_expression(struct Generator* self, struct Checked_Less_Expression* expression) {
#line 4592 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4593 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " < ");
#line 4594 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4597 "bootstrap/stage0/ReCode.code"
void Generator__generate_less_or_equals_expression(struct Generator* self, struct Checked_Less_Or_Equals_Expression* expression) {
#line 4598 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4599 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " <= ");
#line 4600 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4603 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_and_expression(struct Generator* self, struct Checked_Logic_And_Expression* expression) {
#line 4604 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4605 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " && ");
#line 4606 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4609 "bootstrap/stage0/ReCode.code"
void Generator__generate_logic_or_expression(struct Generator* self, struct Checked_Logic_Or_Expression* expression) {
#line 4610 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4611 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " || ");
#line 4612 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4615 "bootstrap/stage0/ReCode.code"
void Generator__generate_member_access_expression(struct Generator* self, struct Checked_Member_Access_Expression* expression) {
#line 4616 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->object_expression);
#line 4617 "bootstrap/stage0/ReCode.code"
    if (expression->object_expression->type->kind == Checked_Type_Kind__POINTER) {
#line 4618 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "->");
    } else {
#line 4620 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ".");
    }
#line 4622 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->member->name);
}

#line 4625 "bootstrap/stage0/ReCode.code"
void Generator__generate_minus_expression(struct Generator* self, struct Checked_Minus_Expression* expression) {
#line 4626 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "-");
#line 4627 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4630 "bootstrap/stage0/ReCode.code"
void Generator__generate_modulo_expression(struct Generator* self, struct Checked_Modulo_Expression* expression) {
#line 4631 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4632 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " % ");
#line 4633 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4636 "bootstrap/stage0/ReCode.code"
void Generator__generate_multiply_expression(struct Generator* self, struct Checked_Multiply_Expression* expression) {
#line 4637 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4638 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " * ");
#line 4639 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4642 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_expression(struct Generator* self, struct Checked_Not_Expression* expression) {
#line 4643 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "!");
#line 4644 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.other_expression);
}

#line 4647 "bootstrap/stage0/ReCode.code"
void Generator__generate_not_equals_expression(struct Generator* self, struct Checked_Not_Equals_Expression* expression) {
#line 4648 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4649 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " != ");
#line 4650 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4653 "bootstrap/stage0/ReCode.code"
void Generator__generate_null_expression(struct Generator* self, struct Checked_Null_Expression* expression) {
#line 4654 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "NULL");
}

#line 4657 "bootstrap/stage0/ReCode.code"
void Generator__generate_sizeof_expression(struct Generator* self, struct Checked_Sizeof_Expression* expression) {
#line 4658 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "sizeof(");
#line 4659 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, expression->sized_type);
#line 4660 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ")");
}

#line 4663 "bootstrap/stage0/ReCode.code"
void Generator__generate_string_expression(struct Generator* self, struct Checked_String_Expression* expression) {
#line 4664 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');
#line 4665 "bootstrap/stage0/ReCode.code"
    size_t index = (size_t) 0;
#line 4666 "bootstrap/stage0/ReCode.code"
    while (index < expression->value->length) {
#line 4667 "bootstrap/stage0/ReCode.code"
        File__write_escaped_char(self->file, expression->value->data[index]);
#line 4668 "bootstrap/stage0/ReCode.code"
        index = index + (size_t) 1;
    }
#line 4670 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, '\"');
}

#line 4673 "bootstrap/stage0/ReCode.code"
void Generator__generate_substract_expression(struct Generator* self, struct Checked_Substract_Expression* expression) {
#line 4674 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.left_expression);
#line 4675 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " - ");
#line 4676 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, expression->super.right_expression);
}

#line 4679 "bootstrap/stage0/ReCode.code"
void Generator__generate_symbol_expression(struct Generator* self, struct Checked_Symbol_Expression* expression) {
#line 4680 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, expression->symbol->name);
}

#line 4683 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression(struct Generator* self, struct Checked_Expression* expression) {
#line 4684 "bootstrap/stage0/ReCode.code"
    if (expression->kind == Checked_Expression_Kind__ADD) {
#line 4685 "bootstrap/stage0/ReCode.code"
        Generator__generate_add_expression(self, (struct Checked_Add_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__ADDRESS_OF) {
#line 4687 "bootstrap/stage0/ReCode.code"
        Generator__generate_address_of_expression(self, (struct Checked_Address_Of_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__ARRAY_ACCESS) {
#line 4689 "bootstrap/stage0/ReCode.code"
        Generator__generate_array_access_expression(self, (struct Checked_Array_Access_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__BOOL) {
#line 4691 "bootstrap/stage0/ReCode.code"
        Generator__generate_bool_expression(self, (struct Checked_Bool_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__CALL) {
#line 4693 "bootstrap/stage0/ReCode.code"
        Generator__generate_call_expression(self, (struct Checked_Call_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__CAST) {
#line 4695 "bootstrap/stage0/ReCode.code"
        Generator__generate_cast_expression(self, (struct Checked_Cast_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__CHARACTER) {
#line 4697 "bootstrap/stage0/ReCode.code"
        Generator__generate_character_expression(self, (struct Checked_Character_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__DEREFERENCE) {
#line 4699 "bootstrap/stage0/ReCode.code"
        Generator__generate_dereference_expression(self, (struct Checked_Dereference_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__DIVIDE) {
#line 4701 "bootstrap/stage0/ReCode.code"
        Generator__generate_divide_expression(self, (struct Checked_Divide_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__EQUALS) {
#line 4703 "bootstrap/stage0/ReCode.code"
        Generator__generate_equals_expression(self, (struct Checked_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__GREATER) {
#line 4705 "bootstrap/stage0/ReCode.code"
        Generator__generate_greater_expression(self, (struct Checked_Greater_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__GREATER_OR_EQUALS) {
#line 4707 "bootstrap/stage0/ReCode.code"
        Generator__generate_greater_or_equals_expression(self, (struct Checked_Greater_Or_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__GROUP) {
#line 4709 "bootstrap/stage0/ReCode.code"
        Generator__generate_group_expression(self, (struct Checked_Group_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__INTEGER) {
#line 4711 "bootstrap/stage0/ReCode.code"
        Generator__generate_integer_expression(self, (struct Checked_Integer_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LESS) {
#line 4713 "bootstrap/stage0/ReCode.code"
        Generator__generate_less_expression(self, (struct Checked_Less_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LESS_OR_EQUALS) {
#line 4715 "bootstrap/stage0/ReCode.code"
        Generator__generate_less_or_equals_expression(self, (struct Checked_Less_Or_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LOGIC_AND) {
#line 4717 "bootstrap/stage0/ReCode.code"
        Generator__generate_logic_and_expression(self, (struct Checked_Logic_And_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__LOGIC_OR) {
#line 4719 "bootstrap/stage0/ReCode.code"
        Generator__generate_logic_or_expression(self, (struct Checked_Logic_Or_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MEMBER_ACCESS) {
#line 4721 "bootstrap/stage0/ReCode.code"
        Generator__generate_member_access_expression(self, (struct Checked_Member_Access_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MINUS) {
#line 4723 "bootstrap/stage0/ReCode.code"
        Generator__generate_minus_expression(self, (struct Checked_Minus_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MODULO) {
#line 4725 "bootstrap/stage0/ReCode.code"
        Generator__generate_modulo_expression(self, (struct Checked_Modulo_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__MULTIPLY) {
#line 4727 "bootstrap/stage0/ReCode.code"
        Generator__generate_multiply_expression(self, (struct Checked_Multiply_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__NOT) {
#line 4729 "bootstrap/stage0/ReCode.code"
        Generator__generate_not_expression(self, (struct Checked_Not_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__NOT_EQUALS) {
#line 4731 "bootstrap/stage0/ReCode.code"
        Generator__generate_not_equals_expression(self, (struct Checked_Not_Equals_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__NULL) {
#line 4733 "bootstrap/stage0/ReCode.code"
        Generator__generate_null_expression(self, (struct Checked_Null_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__SIZEOF) {
#line 4735 "bootstrap/stage0/ReCode.code"
        Generator__generate_sizeof_expression(self, (struct Checked_Sizeof_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__STRING) {
#line 4737 "bootstrap/stage0/ReCode.code"
        Generator__generate_string_expression(self, (struct Checked_String_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__SUBSTRACT) {
#line 4739 "bootstrap/stage0/ReCode.code"
        Generator__generate_substract_expression(self, (struct Checked_Substract_Expression*) expression);
    } else if (expression->kind == Checked_Expression_Kind__SYMBOL) {
#line 4741 "bootstrap/stage0/ReCode.code"
        Generator__generate_symbol_expression(self, (struct Checked_Symbol_Expression*) expression);
    } else {
#line 4743 "bootstrap/stage0/ReCode.code"
        Source_Location__error(expression->location, String__create_from("Unsupported expression"));
#line 4744 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 4748 "bootstrap/stage0/ReCode.code"
void Generator__write_identation(struct Generator* self) {
#line 4749 "bootstrap/stage0/ReCode.code"
    uint16_t identation = self->identation;
#line 4750 "bootstrap/stage0/ReCode.code"
    while (identation > (uint16_t) 0) {
#line 4751 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "    ");
#line 4752 "bootstrap/stage0/ReCode.code"
        identation = identation - (uint16_t) 1;
    }
}

#line 4756 "bootstrap/stage0/ReCode.code"
void Generator__generate_assignment_statement(struct Generator* self, struct Checked_Assignment_Statement* statement) {
#line 4757 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->object_expression);
#line 4758 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " = ");
#line 4759 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->value_expression);
#line 4760 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4763 "bootstrap/stage0/ReCode.code"
void Generator__generate_block_statement(struct Generator* self, struct Checked_Block_Statement* statement) {
#line 4764 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "{\n");
#line 4765 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, statement->statements);
#line 4766 "bootstrap/stage0/ReCode.code"
    Generator__write_identation(self);
#line 4767 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "}");
}

#line 4770 "bootstrap/stage0/ReCode.code"
void Generator__generate_break_statement(struct Generator* self, struct Checked_Break_Statement* statement) {
#line 4771 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "break;");
}

#line 4774 "bootstrap/stage0/ReCode.code"
void Generator__generate_expression_statement(struct Generator* self, struct Checked_Expression_Statement* statement) {
#line 4775 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->expression);
#line 4776 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4779 "bootstrap/stage0/ReCode.code"
void Generator__generate_if_statement(struct Generator* self, struct Checked_If_Statement* statement) {
#line 4780 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "if (");
#line 4781 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4782 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4783 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->true_statement);
#line 4784 "bootstrap/stage0/ReCode.code"
    if (statement->false_statement != NULL) {
#line 4785 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, " else ");
#line 4786 "bootstrap/stage0/ReCode.code"
        Generator__generate_statement(self, statement->false_statement);
    }
}

#line 4790 "bootstrap/stage0/ReCode.code"
void Generator__generate_return_statement(struct Generator* self, struct Checked_Return_Statement* statement) {
#line 4791 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "return");
#line 4792 "bootstrap/stage0/ReCode.code"
    if (statement->expression != NULL) {
#line 4793 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, " ");
#line 4794 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, statement->expression);
    }
#line 4796 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4799 "bootstrap/stage0/ReCode.code"
void Generator__generate_variable_statement(struct Generator* self, struct Checked_Variable_Statement* statement) {
#line 4800 "bootstrap/stage0/ReCode.code"
    if (statement->is_external) {
#line 4801 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "extern ");
    }
#line 4803 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, statement->variable->super.type);
#line 4804 "bootstrap/stage0/ReCode.code"
    File__write_char(self->file, ' ');
#line 4805 "bootstrap/stage0/ReCode.code"
    File__write_string(self->file, statement->variable->super.name);
#line 4806 "bootstrap/stage0/ReCode.code"
    if (statement->expression != NULL) {
#line 4807 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, " = ");
#line 4808 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression(self, statement->expression);
    }
#line 4810 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";");
}

#line 4813 "bootstrap/stage0/ReCode.code"
void Generator__generate_while_statement(struct Generator* self, struct Checked_While_Statement* statement) {
#line 4814 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "while (");
#line 4815 "bootstrap/stage0/ReCode.code"
    Generator__generate_expression(self, statement->condition_expression);
#line 4816 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ") ");
#line 4817 "bootstrap/stage0/ReCode.code"
    Generator__generate_statement(self, statement->body_statement);
}

#line 4820 "bootstrap/stage0/ReCode.code"
void Generator__generate_statement(struct Generator* self, struct Checked_Statement* statement) {
#line 4821 "bootstrap/stage0/ReCode.code"
    if (statement->kind == Checked_Statement_Kind__ASSIGNMENT) {
#line 4822 "bootstrap/stage0/ReCode.code"
        Generator__generate_assignment_statement(self, (struct Checked_Assignment_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__BLOCK) {
#line 4824 "bootstrap/stage0/ReCode.code"
        Generator__generate_block_statement(self, (struct Checked_Block_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__BREAK) {
#line 4826 "bootstrap/stage0/ReCode.code"
        Generator__generate_break_statement(self, (struct Checked_Break_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__EXPRESSION) {
#line 4828 "bootstrap/stage0/ReCode.code"
        Generator__generate_expression_statement(self, (struct Checked_Expression_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__IF) {
#line 4830 "bootstrap/stage0/ReCode.code"
        Generator__generate_if_statement(self, (struct Checked_If_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__RETURN) {
#line 4832 "bootstrap/stage0/ReCode.code"
        Generator__generate_return_statement(self, (struct Checked_Return_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 4834 "bootstrap/stage0/ReCode.code"
        Generator__generate_variable_statement(self, (struct Checked_Variable_Statement*) statement);
    } else if (statement->kind == Checked_Statement_Kind__WHILE) {
#line 4836 "bootstrap/stage0/ReCode.code"
        Generator__generate_while_statement(self, (struct Checked_While_Statement*) statement);
    } else {
#line 4838 "bootstrap/stage0/ReCode.code"
        Source_Location__error(statement->location, String__create_from("Unsupported statement"));
#line 4839 "bootstrap/stage0/ReCode.code"
        abort();
    }
}

#line 4843 "bootstrap/stage0/ReCode.code"
void Generator__generate_statements(struct Generator* self, struct Checked_Statements* statements) {
#line 4844 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation + (uint16_t) 1;
#line 4846 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* statement = statements->first_statement;
#line 4847 "bootstrap/stage0/ReCode.code"
    while (statement != NULL) {
#line 4848 "bootstrap/stage0/ReCode.code"
        Generator__write_source_location(self, statement->location);
#line 4850 "bootstrap/stage0/ReCode.code"
        Generator__write_identation(self);
#line 4852 "bootstrap/stage0/ReCode.code"
        Generator__generate_statement(self, statement);
#line 4854 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, "\n");
#line 4856 "bootstrap/stage0/ReCode.code"
        statement = statement->next_statement;
    }
#line 4859 "bootstrap/stage0/ReCode.code"
    self->identation = self->identation - (uint16_t) 1;
}

#line 4862 "bootstrap/stage0/ReCode.code"
void Generator__generate_enum(struct Generator* self, struct Checked_Enum_Type* enum_type) {
#line 4863 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) enum_type);
#line 4864 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4865 "bootstrap/stage0/ReCode.code"
    struct Checked_Enum_Member* enum_member = enum_type->first_member;
#line 4866 "bootstrap/stage0/ReCode.code"
    while (enum_member != NULL) {
#line 4867 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4868 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, enum_member->symbol->name);
#line 4869 "bootstrap/stage0/ReCode.code"
        enum_member = enum_member->next_member;
#line 4870 "bootstrap/stage0/ReCode.code"
        if (enum_member != NULL) {
#line 4871 "bootstrap/stage0/ReCode.code"
            File__write_cstring(self->file, ",\n");
        } else {
#line 4873 "bootstrap/stage0/ReCode.code"
            File__write_char(self->file, '\n');
        }
    }
#line 4876 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n");
}

#line 4879 "bootstrap/stage0/ReCode.code"
void Generator__declare_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4880 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) function_symbol->function_type);
#line 4881 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");
}

#line 4884 "bootstrap/stage0/ReCode.code"
void Generator__generate_function(struct Generator* self, struct Checked_Function_Symbol* function_symbol) {
#line 4885 "bootstrap/stage0/ReCode.code"
    if (function_symbol->checked_statements == NULL) {
#line 4886 "bootstrap/stage0/ReCode.code"
        return;
    }
#line 4888 "bootstrap/stage0/ReCode.code"
    Generator__write_source_location(self, function_symbol->super.location);
#line 4889 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) function_symbol->function_type);
#line 4890 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4891 "bootstrap/stage0/ReCode.code"
    Generator__generate_statements(self, function_symbol->checked_statements);
#line 4892 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "}\n\n");
}

#line 4895 "bootstrap/stage0/ReCode.code"
void Generator__declare_opaque_type(struct Generator* self, struct Checked_Opaque_Type* opaque_type) {
#line 4896 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) opaque_type);
#line 4897 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");
}

#line 4900 "bootstrap/stage0/ReCode.code"
void Generator__declare_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4901 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) struct_type);
#line 4902 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, ";\n");
}

#line 4905 "bootstrap/stage0/ReCode.code"
void Generator__generate_struct(struct Generator* self, struct Checked_Struct_Type* struct_type) {
#line 4906 "bootstrap/stage0/ReCode.code"
    struct Checked_Struct_Member* struct_member = struct_type->first_member;
#line 4907 "bootstrap/stage0/ReCode.code"
    if (struct_member == NULL) {
#line 4908 "bootstrap/stage0/ReCode.code"
        return;
    }
#line 4910 "bootstrap/stage0/ReCode.code"
    File__write_checked_type(self->file, (struct Checked_Type*) struct_type);
#line 4911 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, " {\n");
#line 4912 "bootstrap/stage0/ReCode.code"
    while (struct_member != NULL) {
#line 4913 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, '\t');
#line 4914 "bootstrap/stage0/ReCode.code"
        File__write_checked_type(self->file, struct_member->type);
#line 4915 "bootstrap/stage0/ReCode.code"
        File__write_char(self->file, ' ');
#line 4916 "bootstrap/stage0/ReCode.code"
        File__write_string(self->file, struct_member->name);
#line 4917 "bootstrap/stage0/ReCode.code"
        File__write_cstring(self->file, ";\n");
#line 4918 "bootstrap/stage0/ReCode.code"
        struct_member = struct_member->next_member;
    }
#line 4920 "bootstrap/stage0/ReCode.code"
    File__write_cstring(self->file, "};\n\n");
}

#line 4923 "bootstrap/stage0/ReCode.code"
void generate(struct File* file, struct Checked_Source* checked_source) {
#line 4924 "bootstrap/stage0/ReCode.code"
    struct Generator generator;
#line 4925 "bootstrap/stage0/ReCode.code"
    generator.file = file;
#line 4926 "bootstrap/stage0/ReCode.code"
    generator.identation = (uint16_t) 0;
#line 4928 "bootstrap/stage0/ReCode.code"
    struct Checked_Symbol* checked_symbol;
#line 4930 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "/* Copyright (C) 2023 Stefan Selariu */\n");
#line 4931 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4932 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <inttypes.h>\n");
#line 4933 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stdbool.h>\n");
#line 4934 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "#include <stddef.h>\n");
#line 4935 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4938 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4939 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4940 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 4941 "bootstrap/stage0/ReCode.code"
            struct Checked_Named_Type* named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 4942 "bootstrap/stage0/ReCode.code"
            if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 4943 "bootstrap/stage0/ReCode.code"
                Generator__declare_struct(&generator, (struct Checked_Struct_Type*) named_type);
            } else if (named_type->super.kind == Checked_Type_Kind__OPAQUE) {
#line 4945 "bootstrap/stage0/ReCode.code"
                Generator__declare_opaque_type(&generator, (struct Checked_Opaque_Type*) named_type);
            } else if (named_type->super.kind == Checked_Type_Kind__ENUM) {
#line 4947 "bootstrap/stage0/ReCode.code"
                Generator__generate_enum(&generator, (struct Checked_Enum_Type*) named_type);
            }
        }
#line 4950 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4952 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4955 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4956 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4957 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__TYPE) {
#line 4958 "bootstrap/stage0/ReCode.code"
            struct Checked_Named_Type* named_type = ((struct Checked_Type_Symbol*) checked_symbol)->named_type;
#line 4959 "bootstrap/stage0/ReCode.code"
            if (named_type->super.kind == Checked_Type_Kind__STRUCT) {
#line 4960 "bootstrap/stage0/ReCode.code"
                Generator__generate_struct(&generator, (struct Checked_Struct_Type*) named_type);
            }
        }
#line 4963 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4967 "bootstrap/stage0/ReCode.code"
    struct Checked_Statement* checked_statement = checked_source->statements->first_statement;
#line 4968 "bootstrap/stage0/ReCode.code"
    while (checked_statement != NULL) {
#line 4969 "bootstrap/stage0/ReCode.code"
        if (checked_statement->kind == Checked_Statement_Kind__VARIABLE) {
#line 4970 "bootstrap/stage0/ReCode.code"
            Generator__generate_variable_statement(&generator, (struct Checked_Variable_Statement*) checked_statement);
#line 4971 "bootstrap/stage0/ReCode.code"
            File__write_cstring(generator.file, "\n");
        } else {
#line 4973 "bootstrap/stage0/ReCode.code"
            Source_Location__error(checked_statement->location, String__create_from("Unsupported statement"));
#line 4974 "bootstrap/stage0/ReCode.code"
            abort();
        }
#line 4976 "bootstrap/stage0/ReCode.code"
        checked_statement = checked_statement->next_statement;
    }
#line 4978 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4981 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4982 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4983 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 4984 "bootstrap/stage0/ReCode.code"
            Generator__declare_function(&generator, (struct Checked_Function_Symbol*) checked_symbol);
        }
#line 4986 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
#line 4988 "bootstrap/stage0/ReCode.code"
    File__write_cstring(generator.file, "\n");
#line 4991 "bootstrap/stage0/ReCode.code"
    checked_symbol = checked_source->first_symbol;
#line 4992 "bootstrap/stage0/ReCode.code"
    while (checked_symbol != NULL) {
#line 4993 "bootstrap/stage0/ReCode.code"
        if (checked_symbol->kind == Checked_Symbol_Kind__FUNCTION) {
#line 4994 "bootstrap/stage0/ReCode.code"
            Generator__generate_function(&generator, (struct Checked_Function_Symbol*) checked_symbol);
        }
#line 4996 "bootstrap/stage0/ReCode.code"
        checked_symbol = checked_symbol->next_symbol;
    }
}

#line 5004 "bootstrap/stage0/ReCode.code"
int32_t main(int32_t argc, char** argv) {
#line 5005 "bootstrap/stage0/ReCode.code"
    if (argc < 3) {
#line 5006 "bootstrap/stage0/ReCode.code"
        error(String__append_cstring(String__append_cstring(String__create_from("Usage: "), argv[(size_t) 0]), " SOURCE OUTPUT"));
#line 5007 "bootstrap/stage0/ReCode.code"
        return 1;
    }
#line 5010 "bootstrap/stage0/ReCode.code"
    char* source_file_path = argv[(size_t) 1];
#line 5011 "bootstrap/stage0/ReCode.code"
    struct File* source_file = fopen(source_file_path, "r");
#line 5012 "bootstrap/stage0/ReCode.code"
    if (source_file == NULL) {
#line 5013 "bootstrap/stage0/ReCode.code"
        error(String__append_cstring(String__create_from("Cannot open file: "), source_file_path));
#line 5014 "bootstrap/stage0/ReCode.code"
        return 1;
    }
#line 5017 "bootstrap/stage0/ReCode.code"
    char* output_file_path = argv[(size_t) 2];
#line 5018 "bootstrap/stage0/ReCode.code"
    struct File* output_file;
#line 5019 "bootstrap/stage0/ReCode.code"
    if (String__equals_cstring(String__create_from(output_file_path), "-")) {
#line 5020 "bootstrap/stage0/ReCode.code"
        output_file = stdout;
    } else {
#line 5022 "bootstrap/stage0/ReCode.code"
        output_file = fopen(output_file_path, "w");
#line 5023 "bootstrap/stage0/ReCode.code"
        if (output_file == NULL) {
#line 5024 "bootstrap/stage0/ReCode.code"
            error(String__append_cstring(String__create_from("Cannot open file: "), output_file_path));
#line 5025 "bootstrap/stage0/ReCode.code"
            return 1;
        }
    }
#line 5029 "bootstrap/stage0/ReCode.code"
    struct Source* source = Source__create(source_file, source_file_path);
#line 5030 "bootstrap/stage0/ReCode.code"
    struct Parsed_Source* parsed_source = parse(source);
#line 5031 "bootstrap/stage0/ReCode.code"
    struct Checked_Source* checked_source = check(parsed_source);
#line 5032 "bootstrap/stage0/ReCode.code"
    generate(output_file, checked_source);
#line 5034 "bootstrap/stage0/ReCode.code"
    fclose(source_file);
#line 5035 "bootstrap/stage0/ReCode.code"
    return fclose(output_file);
}

