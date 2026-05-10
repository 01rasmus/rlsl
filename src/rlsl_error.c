#include <stdio.h>
#include "rlsl_tools/rlsl_str.h"
#include "rlsl_error.h"

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
    printf(PRINTF_COL_BOLD "%s:%zu:%zu: " PRINTF_COL_RED "error" PRINTF_COL_RESET PRINTF_COL_BOLD ": %s " PRINTF_COL_RESET "(0x%05x)\n", identifier, error->start.line, error->start.column, error->message, error->code);
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