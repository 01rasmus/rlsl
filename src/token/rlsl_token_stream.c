#include "rlsl_token_stream.h"
#include "rlsl_token.h"

rlsl_token_stream_t rlsl_token_stream_create(rlsl_token_t* borrowed_tokens, size_t token_count) {
    return (rlsl_token_stream_t) {
        .position = 0,
        .token_count = token_count,
        .tokens = borrowed_tokens,
    };
}

rlsl_token_t* rlsl_token_stream_peek(rlsl_token_stream_t* ts, int64_t offset) {
    int64_t real_offset = ts->position;
    int64_t used_offsets = 0;
    while(true) {
        if(real_offset < 0 || real_offset >= ts->token_count) {
            return NULL;
        }

        rlsl_token_t* token = &ts->tokens[real_offset + 1];
        bool is_skippable_token = token->type == RLSL_TOKEN_SYMBOL_SPACE || token->type == RLSL_TOKEN_SYMBOL_COMMENT;
        if(!is_skippable_token) {
            used_offsets++;
        }
        real_offset++;
        if(used_offsets == offset) {
            break;
        }
    }
    return &ts->tokens[real_offset];
}

rlsl_token_t* rlsl_token_stream_advance(rlsl_token_stream_t* ts) {
    while(true) {
        if(ts->position < 0 || ts->position >= ts->token_count) {
            return NULL;
        }
        rlsl_token_t* token = &ts->tokens[ts->position];
        ts->position++;
        
        bool is_skippable_token = token->type == RLSL_TOKEN_SYMBOL_SPACE || token->type == RLSL_TOKEN_SYMBOL_COMMENT;
        if(!is_skippable_token) {
            return token;
        }
    }
}

void rlsl_token_stream_jump_to_safespot(rlsl_token_stream_t* ts) {

}