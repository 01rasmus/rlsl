#pragma once
#include <stdint.h>
#include "rlsl_cursor.h"

#define RLSL_SEVERITY_WARNING   0x1
#define RLSL_SEVERITY_ERROR     0x2
#define RLSL_SEVERITY_INFO      0x4

#define RLSL_ERRORS(X) \
    X(INVALID_BINARY_NUMBER,                0x10001,    "not a valid binary number",                    RLSL_SEVERITY_ERROR) \
    X(INVALID_DECIMAL_NUMBER,               0x10002,    "not a valid number",                           RLSL_SEVERITY_ERROR) \
    X(INVALID_HEXADECIMAL_NUMBER,           0x10003,    "not a valid hexadecimal number",               RLSL_SEVERITY_ERROR) \
    X(FLOAT_TOO_MANY_COMMAS,                0x10004,    "floating point has too many commas",           RLSL_SEVERITY_ERROR) \
    X(INVALID_CHARACTER_IN_LIT_OR_IDENT,    0x10005,    "invalid character in literal or identifier",   RLSL_SEVERITY_ERROR) \
    X(FLOAT_IS_NOT_DECIMAL,                 0x10006,    "floating point is not a decimal number",                RLSL_SEVERITY_ERROR) \

typedef enum rlsl_error_enum_t {
    #define X(NAME, CODE, MESSAGE, SEVERITY) RLSL_ERROR_##NAME = CODE,
    RLSL_ERRORS(X)
    #undef X
} rlsl_error_enum_t;

typedef struct rlsl_error_t {
    const char* message;
    uint8_t severity;
    uint64_t code;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_error_t;

rlsl_error_t rlsl_error_create(uint64_t error_code, const rlsl_cursor_t* start, const rlsl_cursor_t* end);
void rlsl_error_print(rlsl_error_t* error, const char* identifier, const char* source);