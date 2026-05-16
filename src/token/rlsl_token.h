#pragma once
#include <stdbool.h>
#include "rlsl_cursor.h"
#include "rlsl_error.h"

#define TOKEN_LITERAL_RESULT_SIZE           2048

#define TOKEN_LITERAL_FLAG_BINARY           0x1
#define TOKEN_LITERAL_FLAG_DECIMAL          (0x2 | TOKEN_LITERAL_FLAG_BINARY)
#define TOKEN_LITERAL_FLAG_HEX              (0x4 | TOKEN_LITERAL_FLAG_DECIMAL)
#define TOKEN_LITERAL_FLAG_NUMBER           0x8
#define TOKEN_LITERAL_FLAG_LETTER           0x10
#define TOKEN_LITERAL_FLAG_DECIMAL_POINT    0x20
#define TOKEN_LITERAL_FLAG_INVALID          0x40

#define RLSL_TOKEN_TYPE(X) \
    X(RLSL_TOKEN_LITERAL_IDENTIFIER, "identifier") \
    X(RLSL_TOKEN_LITERAL_FALSE, "false boolean literal") \
    X(RLSL_TOKEN_LITERAL_TRUE, "true boolean literal") \
    X(RLSL_TOKEN_LITERAL_FLOAT, "float literal") \
    X(RLSL_TOKEN_LITERAL_INT, "integer literal") \
    X(RLSL_TOKEN_PRECISION_LOWP, "lowp") \
    X(RLSL_TOKEN_PRECISION_MEDIUMP, "mediump") \
    X(RLSL_TOKEN_PRECISION_HIGHP, "highp") \
    X(RLSL_TOKEN_KEYWORD_UNIFORM, "uniform") \
    X(RLSL_TOKEN_KEYWORD_INPUT, "input") \
    X(RLSL_TOKEN_KEYWORD_OUTPUT, "output") \
    X(RLSL_TOKEN_KEYWORD_STRUCT, "struct") \
    X(RLSL_TOKEN_KEYWORD_WHILE, "while") \
    X(RLSL_TOKEN_KEYWORD_FOR, "for") \
    X(RLSL_TOKEN_KEYWORD_IF, "if") \
    X(RLSL_TOKEN_KEYWORD_ELSE, "else") \
    X(RLSL_TOKEN_KEYWORD_RETURN, "return") \
    X(RLSL_TOKEN_KEYWORD_CONST, "const") \
    X(RLSL_TOKEN_SYMBOL_SPACE, "space") \
    X(RLSL_TOKEN_SYMBOL_COMMENT, "comment") \
    X(RLSL_TOKEN_SYMBOL_SEMICOLON, ";") \
    X(RLSL_TOKEN_SYMBOL_COLON, ":") \
    X(RLSL_TOKEN_SYMBOL_STAR, "*") \
    X(RLSL_TOKEN_SYMBOL_DASH, "-") \
    X(RLSL_TOKEN_SYMBOL_PLUS, "+") \
    X(RLSL_TOKEN_SYMBOL_FORWARD_SLASH, "/") \
    X(RLSL_TOKEN_SYMBOL_TILDE, "~") \
    X(RLSL_TOKEN_SYMBOL_DOT, ".") \
    X(RLSL_TOKEN_SYMBOL_AND, "&") \
    X(RLSL_TOKEN_SYMBOL_PIPE, "|") \
    X(RLSL_TOKEN_SYMBOL_PERCENT, "%") \
    X(RLSL_TOKEN_SYMBOL_EXCLAMATION, "!") \
    X(RLSL_TOKEN_SYMBOL_EQUAL, "=") \
    X(RLSL_TOKEN_SYMBOL_COMMA, ",") \
    X(RLSL_TOKEN_SYMBOL_ARROW_LEFT, "<") \
    X(RLSL_TOKEN_SYMBOL_ARROW_RIGHT, ">") \
    X(RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED, "{") \
    X(RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED, "}") \
    X(RLSL_TOKEN_SYMBOL_BRACKET_OPENED, "[") \
    X(RLSL_TOKEN_SYMBOL_BRACKET_CLOSED, "]") \
    X(RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED, "(") \
    X(RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED, ")")

typedef enum rlsl_token_type_t {
    #define X(NAME, STRING) NAME,
    RLSL_TOKEN_TYPE(X)
    #undef X
} rlsl_token_type_t;

#define rlsl_token_create_static(TYPE, CURSOR_START, CURSOR_END)             (rlsl_token_t){ .type = (TYPE), .cursor_start = (CURSOR_START), .cursor_end = (CURSOR_END) }
#define rlsl_token_create_int(INTEGER, OVERFLOW, CURSOR_START, CURSOR_END)   (rlsl_token_t){ \
    .type = RLSL_TOKEN_LITERAL_INT, \
    .cursor_start = (CURSOR_START), \
    .cursor_end = (CURSOR_END), \
    .value.num_int = { \
        .value = (INTEGER), \
        .overflow = (OVERFLOW) \
    } \
}

#define rlsl_token_create_float(FLOAT, OVERFLOW, CURSOR_START, CURSOR_END)   (rlsl_token_t){ \
    .type = RLSL_TOKEN_LITERAL_FLOAT, \
    .cursor_start = (CURSOR_START), \
    .cursor_end = (CURSOR_END), \
    .value.num_float = { \
        .value = (FLOAT), \
        .overflow = (OVERFLOW) \
    } \
}

#define rlsl_token_create_identifier(IDENT, CURSOR_START, CURSOR_END)   (rlsl_token_t){ \
    .type = RLSL_TOKEN_LITERAL_IDENTIFIER, \
    .cursor_start = (CURSOR_START), \
    .cursor_end = (CURSOR_END), \
    .value.identifier = (IDENT), \
}

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
            double value;
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

typedef struct rlsl_token_str_to_type_t {
    const char* string;
    rlsl_token_type_t type;
} rlsl_token_str_to_type_t;

typedef bool (*rlsl_tokenizer_function_t)(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier);

rlsl_tokenizer_result_t* rlsl_token_tokenize_string(const char* source, const char* compile_unit_identifier);
void rlsl_tokenizer_result_free(rlsl_tokenizer_result_t* result);
void rlsl_token_free(rlsl_token_t* token);

const char* rlsl_token_type_to_string(rlsl_token_type_t type);