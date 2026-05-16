#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct rlsl_token_t rlsl_token_t;

typedef struct rlsl_token_stream_t {
    size_t token_count;
    rlsl_token_t* tokens;
    int64_t position;
} rlsl_token_stream_t;

rlsl_token_stream_t rlsl_token_stream_create(rlsl_token_t* borrowed_tokens, size_t token_count);

/*
    peeks at the next token
    without changing the walker's
    position
*/
rlsl_token_t* rlsl_token_stream_peek(rlsl_token_stream_t* ts, int64_t offset);

rlsl_token_t* rlsl_token_stream_advance(rlsl_token_stream_t* ts);

/*
    used after an error. it jumps to the nearest ";" or keyword
    that would usually start a new structure
*/
void rlsl_token_stream_jump_to_safespot(rlsl_token_stream_t* ts);