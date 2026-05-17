#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "tools/rlsl_str.h"
#include "tools/rlsl_vec.h"
#include "rlsl_token.h"

#include "rlsl_token_tokenizer_comment.h"
#include "rlsl_token_tokenizer_literal_and_keyword.h"
#include "rlsl_token_tokenizer_space.h"
#include "rlsl_token_tokenizer_single_char.h"

/*
    list of tokenizer functions.
    the order of these functions are important
    and should not be changed
*/
static rlsl_tokenizer_function_t tokenizer_functions[] = {
    rlsl_token_tokenizer_parse_comment,
    rlsl_token_tokenizer_parse_literal_and_keyword,
    rlsl_token_tokenizer_parse_space,
    rlsl_token_tokenizer_parse_single_char_token,
};

const rlsl_token_type_t top_level_tokens[4] = {
    RLSL_TOKEN_KEYWORD_STRUCT,
    RLSL_TOKEN_KEYWORD_UNIFORM,
    RLSL_TOKEN_KEYWORD_INPUT,
    RLSL_TOKEN_KEYWORD_OUTPUT,
};

rlsl_tokenizer_result_t* rlsl_token_tokenize_string(const char* source, const char* compile_unit_identifier) {
    rlsl_tokenizer_result_t* res = malloc(sizeof(rlsl_tokenizer_result_t));
    if(!res) {
        goto err;
    }

    res->error_count = 0;
    res->token_count = 0;
    res->errors = NULL;
    res->tokens = NULL;

    rlsl_cursor_t cursor = rlsl_cursor_create();
    size_t source_length = strlen(source);
    while(1) {
        bool added_token = false;
        for(int32_t i = 0; i < sizeof(tokenizer_functions) / sizeof(rlsl_tokenizer_function_t); i++) {
            rlsl_tokenizer_function_t tokenizer = tokenizer_functions[i];
            if(tokenizer(&cursor, res, source, compile_unit_identifier)) {
                added_token = true;
                break;
            }
        }

        //we arrived at a character that is illegal.
        //we will add it as an error, and continue
        //to check if there are more errors further down
        if(!added_token) {
            rlsl_cursor_t next_cur = cursor;
            rlsl_cursor_advance(&next_cur, source, 1);
            rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_INVALID_CHARACTER_IN_LIT_OR_IDENT, &cursor, &next_cur));
            cursor = next_cur;
        }

        if(source_length <= cursor.index || source[cursor.index] == '\0') {
            break;
        }
    }
    
    res->error_count = rlsl_vec_size(res->errors);
    res->token_count = rlsl_vec_size(res->tokens);
    return res;
err:
    rlsl_tokenizer_result_free(res);
    return NULL;
}

void rlsl_tokenizer_result_free(rlsl_tokenizer_result_t* result) {
    if(!result) {
        return;
    }
    
    for(int64_t i = 0; i < rlsl_vec_size(result->tokens); i++) {
        rlsl_token_free(&result->tokens[i]);
    }

    for(int64_t i = 0; i < rlsl_vec_size(result->errors); i++) {
        rlsl_error_free(&result->errors[i]);
    }

    rlsl_vec_free(result->tokens);
    rlsl_vec_free(result->errors);
    free(result);
}

void rlsl_token_free(rlsl_token_t* token) {
    switch(token->type) {
        case RLSL_TOKEN_LITERAL_IDENTIFIER: {
            free(token->value.identifier);
            break;
        }
        default:
            break;
    }
}

const char* rlsl_token_type_to_string(rlsl_token_type_t type) {
    switch(type) {
        #define X(NAME, STRING) case NAME: return STRING;
        RLSL_TOKEN_TYPE(X)
        #undef X
        default:
            return "unknown";
    }
}