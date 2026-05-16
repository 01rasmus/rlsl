#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "tools/rlsl_str.h"
#include "rlsl_error.h"

rlsl_error_t _rlsl_error_createf(rlsl_error_enum_t error_code, rlsl_cursor_t start, rlsl_cursor_t end, const char* format, ...) {
    rlsl_error_t error = (rlsl_error_t) {
        .code = error_code,
        .start = start,
        .end = end,
        .message_is_static = false,
        .severity = rlsl_error_severity(error_code),
        .message = NULL,
        .dynamic_message = NULL
    };

    va_list args;
    va_list args_copy;
    va_start(args, format);
    va_copy(args_copy, args);

    int32_t size = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    error.dynamic_message = malloc(size);
    vsnprintf(error.dynamic_message, size, format, args_copy);
    va_end(args_copy);
    return error;
}

uint8_t rlsl_error_severity(rlsl_error_enum_t error_code) {
    uint8_t severity = 0;
    switch(error_code) {
        #define X(NAME, CODE, MESSAGE, SEVERITY) case CODE: { severity = SEVERITY; break; }
        RLSL_ERRORS(X)
        #undef X
        default: {
            severity = RLSL_SEVERITY_ERROR;
            break;
        }
    }
    return severity;
}

const char* rlsl_error_string(rlsl_error_enum_t error_code) {
    const char* message = NULL;
    switch(error_code) {
        #define X(NAME, CODE, MESSAGE, SEVERITY) case CODE: { message = MESSAGE; break; }
        RLSL_ERRORS(X)
        #undef X
        default: {
            message = "unknown error";
            break;
        }
    }
    return message;
}

void rlsl_error_print(rlsl_error_t* error, const char* source, const char* identifier) {

    printf(PRINTF_COL_BOLD "%s:%zu:%zu: " PRINTF_COL_RED "error" PRINTF_COL_RESET PRINTF_COL_BOLD ": %s " PRINTF_COL_RESET "(0x%05x)\n", identifier, error->start.line, error->start.column, error->message_is_static ? error->message : error->dynamic_message, error->code);
    printf(PRINTF_COL_RESET "\t");

    const int64_t offset = 10;

    int64_t start = (int64_t)error->start.index;
    for(int64_t i = 0; i < offset; i++) {
        if(source[start - 1] == '\n') {
            break;
        }
        start--;
    }
    if(start < 0) {
        start = 0;
    }

    for(int64_t i = start; i < (error->end.index + offset); i++) {
        char c = source[i];
        if(c == '\n' || c == '\0') {
            break;
        }
        printf("%c", c);
    }
    printf("\n\t" PRINTF_COL_BOLD PRINTF_COL_GREEN);

    for(int64_t i = start; i < (error->end.index + offset); i++) {
        char c = source[i];
        if(i == start && c == '\n') {
            continue;
        }
        if(i >= error->start.index && i < error->end.index) {
            printf("^");
        } else {
            printf(c == '\t' ? "\t" : " ");
        }
    }
    printf(PRINTF_COL_RESET "\n");
}

void rlsl_error_free(rlsl_error_t* error) {
    if(!error) {
        return;
    }
    if(!error->message_is_static) {
        free(error->dynamic_message);
        error->dynamic_message = NULL;
    }
}