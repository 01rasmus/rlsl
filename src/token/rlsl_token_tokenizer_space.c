#include <ctype.h>
#include "tools/rlsl_vec.h"
#include "rlsl_token_tokenizer_space.h"

bool rlsl_token_tokenizer_parse_space(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    rlsl_cursor_t cursor_current = *cursor;
    rlsl_cursor_t cursor_start = cursor_current;
    bool is_space = false;
    while(1) {
        const char character = source[cursor_current.index];
        bool current_is_space = isspace((uint8_t)character);
        if(current_is_space) {
            is_space = true;
        } else {
            break;
        }
        if(rlsl_cursor_advance(&cursor_current, source, 1) != 1) {
            break;
        }
    }
    if(is_space) {
        (*cursor) = cursor_current;
        rlsl_vec_push(res->tokens, rlsl_token_create_static(RLSL_TOKEN_SYMBOL_SPACE, cursor_start, cursor_current));
    }
    return is_space;
}