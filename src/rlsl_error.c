#include <stdio.h>
#include "rlsl_error.h"

#define PRINTF_COL_RESET            "\x1B[0m"
#define PRINTF_COL_BOLD             "\x1B[1m"
#define PRINTF_COL_BLACK            "\x1B[30m"
#define PRINTF_COL_RED              "\x1B[31m"
#define PRINTF_COL_GREEN            "\x1B[32m"
#define PRINTF_COL_YELLOW           "\x1B[33m"
#define PRINTF_COL_BLUE             "\x1B[34m"
#define PRINTF_COL_MAGENTA          "\x1B[35m"
#define PRINTF_COL_CYAN             "\x1B[36m"
#define PRINTF_COL_WHITE            "\x1B[37m"

rlsl_error_t rlsl_error_create(uint64_t error_code, const rlsl_cursor_t* start, const rlsl_cursor_t* end) {
    uint8_t severity = 0;
    const char* message = NULL;

    switch(error_code) {
        #define X(NAME, CODE, MESSAGE, SEVERITY) case CODE: { message = MESSAGE; severity = SEVERITY; break; }
        RLSL_ERRORS(X)
        #undef X
        default: {
            severity = RLSL_SEVERITY_ERROR;
            message = "unknown error";
            break;
        }
    }

    return (rlsl_error_t) {
        .severity = severity,
        .message = message,
        .code = error_code,
        .start = (*start),
        .end = (*end)
    };
}

void rlsl_error_print(rlsl_error_t* error, const char* source, const char* identifier) {
    printf(PRINTF_COL_BOLD "%s:%zu:%zu: " PRINTF_COL_RED "error" PRINTF_COL_RESET PRINTF_COL_BOLD ": %s " PRINTF_COL_RESET "(0x%05llx)\n", identifier, error->start.line, error->start.column, error->message, error->code);
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