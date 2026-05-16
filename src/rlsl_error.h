#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "rlsl_cursor.h"

#define RLSL_SEVERITY_WARNING   0x1
#define RLSL_SEVERITY_ERROR     0x2
#define RLSL_SEVERITY_INFO      0x4

#define RLSL_ERRORS(X) \
    X(INVALID_BINARY_NUMBER,                0x10001,    "not a valid binary number",                    RLSL_SEVERITY_ERROR) \
    X(INVALID_DECIMAL_NUMBER,               0x10002,    "not a valid number",                           RLSL_SEVERITY_ERROR) \
    X(INVALID_HEXADECIMAL_NUMBER,           0x10003,    "not a valid hexadecimal number",               RLSL_SEVERITY_ERROR) \
    X(FLOAT_TOO_MANY_DECIMAL_POINTS,        0x10004,    "floating point has too decimal points",        RLSL_SEVERITY_ERROR) \
    X(INVALID_CHARACTER_IN_LIT_OR_IDENT,    0x10005,    "invalid character in literal or identifier",   RLSL_SEVERITY_ERROR) \
    X(FLOAT_IS_NOT_DECIMAL,                 0x10006,    "floating point is not a decimal number",       RLSL_SEVERITY_ERROR) \
    X(FLOAT_HAS_TWO_LEADING_ZEROS,          0x10007,    "floating point has two leading zeros",         RLSL_SEVERITY_ERROR) \
    X(DECIMAL_LEADING_ZERO,                 0x10008,    "decimal number has a leading zero",            RLSL_SEVERITY_ERROR) \
    X(EXPECTED_TOKEN,                       0x10009,    NULL,                                           RLSL_SEVERITY_ERROR) \
    X(END_OF_TOKEN_STREAM,                  0x1000A,    "expected a token but is at end of stream",     RLSL_SEVERITY_ERROR) \

#define rlsl_error_create(ERROR_CODE, START, END) \
    (rlsl_error_t) { \
        .message = rlsl_error_string(ERROR_CODE), \
        .dynamic_message = NULL, \
        .message_is_static = true, \
        .severity = rlsl_error_severity(ERROR_CODE), \
        .code = (ERROR_CODE), \
        .start = (*START), \
        .end = (*END), \
    }

#define rlsl_error_createf(ERROR_CODE, START, END, ...) \
    _rlsl_error_createf(ERROR_CODE, START, END, __VA_ARGS__)

typedef enum rlsl_error_enum_t {
    #define X(NAME, CODE, MESSAGE, SEVERITY) RLSL_ERROR_##NAME = CODE,
    RLSL_ERRORS(X)
    #undef X
} rlsl_error_enum_t;

typedef enum rlsl_token_type_t rlsl_token_type_t;

typedef struct rlsl_error_t {
    const char* message;
    char* dynamic_message;
    bool message_is_static;
    uint8_t severity;
    rlsl_error_enum_t code;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_error_t;

rlsl_error_t rlsl_error_create_from_expected_tokens(rlsl_cursor_t start, rlsl_cursor_t end, rlsl_token_type_t got_token_type, const rlsl_token_type_t* expected_tokens, int64_t expected_tokens_count);
rlsl_error_t _rlsl_error_createf(rlsl_error_enum_t error_code, rlsl_cursor_t start, rlsl_cursor_t end, const char* format, ...);
uint8_t rlsl_error_severity(rlsl_error_enum_t error_code);
const char* rlsl_error_string(rlsl_error_enum_t error_code);
void rlsl_error_print(rlsl_error_t* error, const char* source, const char* identifier);
void rlsl_error_free(rlsl_error_t* error);