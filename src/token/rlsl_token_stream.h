#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct rlsl_token_t rlsl_token_t;

typedef struct rlsl_token_stream_t {
    size_t token_count;
    rlsl_token_t* tokens;
    int64_t position;
    int64_t curly_bracket_depth;
    int64_t parenthesis_depth;
} rlsl_token_stream_t;

rlsl_token_stream_t rlsl_token_stream_create(rlsl_token_t* borrowed_tokens, size_t token_count);

bool rlsl_token_stream_is_at_end(rlsl_token_stream_t* ts);

/*
    peeks at the next token
    without changing the walker's
    position
*/
rlsl_token_t* rlsl_token_stream_peek(rlsl_token_stream_t* ts, int64_t offset);

/*
    consumes the next token and
    changes the walker's position
*/
rlsl_token_t* rlsl_token_stream_advance(rlsl_token_stream_t* ts);

void rlsl_token_stream_recover_var_declaration(rlsl_token_stream_t* ts);
void rlsl_token_stream_recover_top_level(rlsl_token_stream_t* ts);