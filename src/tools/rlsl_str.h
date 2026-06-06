#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

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

#define RLSL_STR_STREAM_STDOUT      0x0
#define RLSL_STR_STREAM_MEMORY      0x1

typedef struct rlsl_str_stream_t {
    char* string;
    int64_t capacity;
    int64_t length;
    uint8_t type;
} rlsl_str_stream_t;

rlsl_str_stream_t rlsl_str_stream_create(uint8_t stream_type);
void rlsl_str_stream_printf(rlsl_str_stream_t* sstr, const char* format, ...);
void rlsl_str_stream_print_json_string(rlsl_str_stream_t* sstr, const char* string);
int64_t rlsl_str_stream_length(rlsl_str_stream_t* sstr);

/*
    make sure not to free this and the stream.
    only free this one or the stream
*/
char* rlsl_str_stream_raw(rlsl_str_stream_t* sstr);
void rlsl_str_stream_free(rlsl_str_stream_t* sstr);

/*
    int32_t str_starts_with_any(const char* src, const char** substrings)

    A macro that checks if a string starts with any of the substrings
    given. Since it's a macro, no size of the substrings array needs
    to be provided.

    The substrings need to be null terminated.

    On success, it returns the index of the matched substring
    in the array. On error, it returns -1.
*/
#define rlsl_str_starts_with_any_of(SRC, SUBSTRINGS) \
    _rlsl_str_starts_with_any_of(SRC, SUBSTRINGS, sizeof(SUBSTRINGS) / sizeof(const char*))

/*
    Concatenates two strings. It will
    add the source to the end of 
    dest (at the null terminator).
    It will always make a string that has a null
    terminator as a result.

    The dest_total_size includes the null terminator.

    This is intended to work similarily
    to unix/bsd's version of strlcat.
*/
size_t rlsl_str_cat(char* dest, size_t dest_total_size, const char* src);

/*
    makes a copy of a string
    on the heap. needs to
    manually be freed with "free"
*/
char* rlsl_str_cpy(const char* string);

/*
    this functions escapes a string
    to make it possible to use as
    a string in a json string
*/
void rlsl_str_print_json_string(FILE* fd, const char* str);

int32_t _rlsl_str_starts_with_any_of(const char* src, const char** substrings, int32_t substring_count);