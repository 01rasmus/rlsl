#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct rlsl_token_t rlsl_token_t;

typedef struct rlsl_token_stream_t {
    size_t token_count;
    rlsl_token_t* tokens;
    int64_t position;
} rlsl_token_stream_t;

rlsl_token_stream_t rlsl_token_stream_create(rlsl_token_t* borrowed_tokens, size_t token_count);

bool rlsl_token_stream_is_at_end(rlsl_token_stream_t* ts);

/*
    peeks at the next token
    without changing the walker's
    position
*/
rlsl_token_t* rlsl_token_stream_peek(rlsl_token_stream_t* ts, int64_t offset);

rlsl_token_t* rlsl_token_stream_advance(rlsl_token_stream_t* ts);

/*
    jumps forward to a safe spot in case of a failure
    to make sure the parser can get expected tokens.

    this function jumps forward to either } or ;
*/
void rlsl_token_stream_recover(rlsl_token_stream_t* ts, bool consume_token);