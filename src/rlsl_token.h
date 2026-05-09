#pragma once
#include <stdbool.h>
#include "rlsl_cursor.h"
#include "rlsl_error.h"

#define TOKEN_LITERAL_FLAG_BINARY           0x1
#define TOKEN_LITERAL_FLAG_DECIMAL          (0x2 | TOKEN_LITERAL_FLAG_BINARY)
#define TOKEN_LITERAL_FLAG_HEX              (0x4 | TOKEN_LITERAL_FLAG_DECIMAL)
#define TOKEN_LITERAL_FLAG_NUMBER           0x8
#define TOKEN_LITERAL_FLAG_LETTER           0x10
#define TOKEN_LITERAL_FLAG_DECIMAL_POINT    0x20
#define TOKEN_LITERAL_FLAG_INVALID          0x40

typedef enum rlsl_token_type_t {
    //literals
    RLSL_TOKEN_LITERAL_IDENTIFIER = 0,
    RLSL_TOKEN_LITERAL_FALSE,
    RLSL_TOKEN_LITERAL_TRUE,
    RLSL_TOKEN_LITERAL_FLOAT,
    RLSL_TOKEN_LITERAL_INT,

    //base types
    RLSL_TOKEN_TYPE_BOOL,
    RLSL_TOKEN_TYPE_INT,
    RLSL_TOKEN_TYPE_UINT,
    RLSL_TOKEN_TYPE_FLOAT,
    RLSL_TOKEN_TYPE_DOUBLE,

    //vector types
    RLSL_TOKEN_TYPE_BVEC2,
    RLSL_TOKEN_TYPE_IVEC2,
    RLSL_TOKEN_TYPE_UVEC2,
    RLSL_TOKEN_TYPE_DVEC2,
    RLSL_TOKEN_TYPE_VEC2,
    RLSL_TOKEN_TYPE_BVEC3,
    RLSL_TOKEN_TYPE_IVEC3,
    RLSL_TOKEN_TYPE_UVEC3,
    RLSL_TOKEN_TYPE_DVEC3,
    RLSL_TOKEN_TYPE_VEC3,
    RLSL_TOKEN_TYPE_BVEC4,
    RLSL_TOKEN_TYPE_IVEC4,
    RLSL_TOKEN_TYPE_UVEC4,
    RLSL_TOKEN_TYPE_DVEC4,
    RLSL_TOKEN_TYPE_VEC4,

    //matrix types
    RLSL_TOKEN_TYPE_MAT2,
    RLSL_TOKEN_TYPE_MAT3,
    RLSL_TOKEN_TYPE_MAT4,
    RLSL_TOKEN_TYPE_MAT2X2,
    RLSL_TOKEN_TYPE_MAT2X3,
    RLSL_TOKEN_TYPE_MAT2X4,
    RLSL_TOKEN_TYPE_MAT3X2,
    RLSL_TOKEN_TYPE_MAT3X3,
    RLSL_TOKEN_TYPE_MAT3X4,
    RLSL_TOKEN_TYPE_MAT4X2,
    RLSL_TOKEN_TYPE_MAT4X3,
    RLSL_TOKEN_TYPE_MAT4X4,

    //keywords
    RLSL_TOKEN_KEYWORD_UNIFORM,
    RLSL_TOKEN_KEYWORD_INPUT,
    RLSL_TOKEN_KEYWORD_OUTPUT,
    RLSL_TOKEN_KEYWORD_STRUCT,
    RLSL_TOKEN_KEYWORD_WHILE,
    RLSL_TOKEN_KEYWORD_FOR,
    RLSL_TOKEN_KEYWORD_IF,
    RLSL_TOKEN_KEYWORD_ELSE,
    RLSL_TOKEN_KEYWORD_RETURN,
    RLSL_TOKEN_KEYWORD_CONST,

    //symbols
    RLSL_TOKEN_SYMBOL_SPACE,
    RLSL_TOKEN_SYMBOL_COMMENT,
    RLSL_TOKEN_SYMBOL_SEMICOLON,
    RLSL_TOKEN_SYMBOL_COLON,
    RLSL_TOKEN_SYMBOL_STAR,
    RLSL_TOKEN_SYMBOL_DASH,
    RLSL_TOKEN_SYMBOL_PLUS,
    RLSL_TOKEN_SYMBOL_FORWARD_SLASH,
    RLSL_TOKEN_SYMBOL_TILDE,
    RLSL_TOKEN_SYMBOL_DOT,
    RLSL_TOKEN_SYMBOL_AND,
    RLSL_TOKEN_SYMBOL_PIPE,
    RLSL_TOKEN_SYMBOL_PERCENT,
    RLSL_TOKEN_SYMBOL_EXCLAMATION,
    RLSL_TOKEN_SYMBOL_EQUAL,
    RLSL_TOKEN_SYMBOL_COMMA,
    RLSL_TOKEN_SYMBOL_ARROW_LEFT,
    RLSL_TOKEN_SYMBOL_ARROW_RIGHT,
    RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED,
    RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED,
    RLSL_TOKEN_SYMBOL_BRACKET_OPENED,
    RLSL_TOKEN_SYMBOL_BRACKET_CLOSED,
    RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED,
    RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED,
} rlsl_token_type_t;

typedef struct rlsl_token_t {
    rlsl_token_type_t type;
    rlsl_cursor_t cursor_start;
    rlsl_cursor_t cursor_end;

    union {
        struct {
            uint64_t value;
            bool overflow;
        } num_int;
        struct {
            long double value;
            bool overflow;
        } num_float;
        char* identifier;
    } value;
} rlsl_token_t;

typedef struct rlsl_tokenizer_result_t {
    size_t token_count;
    rlsl_token_t* tokens;
    size_t error_count;
    rlsl_error_t* errors;
} rlsl_tokenizer_result_t;

rlsl_tokenizer_result_t rlsl_token_tokenize_string(const char* source, const char* compile_unit_identifier);
void rlsl_token_free(rlsl_token_t* token);

typedef bool (*rlsl_tokenizer_function_t)(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier);

/*
    internal tokenizer functions
*/
bool _rlsl_token_tokenizer_parse_comments(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier);
bool _rlsl_token_tokenizer_parse_space(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier);
bool _rlsl_token_tokenizer_parse_static_tokens(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier);
bool _rlsl_token_tokenizer_parse_literal(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier);