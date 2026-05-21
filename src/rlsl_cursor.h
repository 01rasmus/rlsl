#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct rlsl_cursor_t {
    size_t line;
    size_t column;
    size_t index;
} rlsl_cursor_t;

rlsl_cursor_t rlsl_cursor_create();
rlsl_cursor_t rlsl_cursor_at_position(const char* source, size_t line, size_t column);

/*
    Returns the amount of characters
    advanced. If it does not equal the 
    amount given, then the rlsl_cursor stopped
    at the null character.
*/
size_t rlsl_cursor_advance(rlsl_cursor_t* rlsl_cursor, const char* string, size_t amount);

int32_t rlsl_cursor_compare(const rlsl_cursor_t* a, const rlsl_cursor_t* b);