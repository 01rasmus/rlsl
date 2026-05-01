#pragma once
#include <stdint.h>
#include "cursor.h"

#define RLR_SL_SEVERITY_WARNING   0x1
#define RLR_SL_SEVERITY_ERROR     0x2
#define RLR_SL_SEVERITY_INFO      0x4

#define RLR_SL_ERRORS(X) \
    X(INVALID_BINARY_NUMBER,                0x10001,    "not a valid binary number",                    RLR_SL_SEVERITY_ERROR) \
    X(INVALID_DECIMAL_NUMBER,               0x10002,    "not a valid number",                           RLR_SL_SEVERITY_ERROR) \
    X(INVALID_HEXADECIMAL_NUMBER,           0x10003,    "not a valid hexadecimal number",               RLR_SL_SEVERITY_ERROR) \
    X(FLOAT_TOO_MANY_COMMAS,                0x10004,    "floating point has too many commas",           RLR_SL_SEVERITY_ERROR) \
    X(INVALID_CHARACTER_IN_LIT_OR_IDENT,    0x10005,    "invalid character in literal or identifier",   RLR_SL_SEVERITY_ERROR) \
    X(FLOAT_IS_NOT_DECIMAL,                 0x10006,    "floating point is not a decimal number",                RLR_SL_SEVERITY_ERROR) \

typedef enum rlr_sl_error_enum_t {
    #define X(NAME, CODE, MESSAGE, SEVERITY) RLR_SL_ERROR_##NAME = CODE,
    RLR_SL_ERRORS(X)
    #undef X
} rlr_sl_error_enum_t;

typedef struct rlr_sl_error_t {
    const char* message;
    uint8_t severity;
    uint64_t code;
    rlr_sl_cursor_t start;
    rlr_sl_cursor_t end;
} rlr_sl_error_t;

rlr_sl_error_t rlr_sl_error_create(uint64_t error_code, const rlr_sl_cursor_t* start, const rlr_sl_cursor_t* end);
void rlr_sl_error_print(rlr_sl_error_t* error, const char* identifier, const char* source);