#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "tools/rlsl_str.h"
#include "token/rlsl_token.h"
#include "rlsl_error.h"

#define TEMP_STRING_LENGTH  32768
static char temp_string[TEMP_STRING_LENGTH] = { 0 };

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

rlsl_error_t rlsl_error_create_from_expected_tokens(rlsl_cursor_t start, rlsl_cursor_t end, rlsl_token_type_t got_token_type, const rlsl_token_type_t* expected_tokens, int64_t expected_tokens_count) {
    
    strcpy(temp_string, "expected token");
    for(int64_t i = 0; i < expected_tokens_count; i++) {
        rlsl_token_type_t expected_token = expected_tokens[i];

        if(i == expected_tokens_count - 1) {
            rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, " or \"");
        } else {
            rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, " \"");
        }
        
        rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, rlsl_token_type_to_string(expected_token));

        if(i >= expected_tokens_count - 2) {
            rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, "\"");
        } else {
            rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, "\",");
        }
    }
    rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, " but got \"");
    rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, rlsl_token_type_to_string(got_token_type));
    rlsl_str_cat(temp_string, TEMP_STRING_LENGTH, "\"");

    return (rlsl_error_t) {
        .code = RLSL_ERROR_EXPECTED_TOKEN,
        .start = start,
        .end = end,
        .message = NULL,
        .dynamic_message = rlsl_str_cpy(temp_string),
        .message_is_static = false,
        .severity = RLSL_SEVERITY_ERROR,
    };
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