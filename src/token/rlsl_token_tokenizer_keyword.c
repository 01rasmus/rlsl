#include <string.h>
#include "tools/rlsl_vec.h"
#include "rlsl_token_tokenizer_keyword.h"
#include "rlsl_token.h"

/*
    this array contains strings that matches
    the actual strings that is equialent
    to a static token. Like "struct" or "*".

    these are sorted by length and then
    by alphabetical order, starting with
    the longest
*/
static rlsl_token_str_to_type_t rlsl_token_keywords[] = {
    { .string = "mediump", .type = RLSL_TOKEN_PRECISION_MEDIUMP },
    { .string = "uniform", .type = RLSL_TOKEN_KEYWORD_UNIFORM },
    { .string = "output", .type = RLSL_TOKEN_KEYWORD_OUTPUT },
    { .string = "return", .type = RLSL_TOKEN_KEYWORD_RETURN },
    { .string = "struct", .type = RLSL_TOKEN_KEYWORD_STRUCT },
    { .string = "const", .type = RLSL_TOKEN_KEYWORD_CONST },
    { .string = "false", .type = RLSL_TOKEN_LITERAL_FALSE },
    { .string = "highp", .type = RLSL_TOKEN_PRECISION_HIGHP },
    { .string = "input", .type = RLSL_TOKEN_KEYWORD_INPUT },
    { .string = "while", .type = RLSL_TOKEN_KEYWORD_WHILE },
    { .string = "else", .type = RLSL_TOKEN_KEYWORD_ELSE },
    { .string = "lowp", .type = RLSL_TOKEN_PRECISION_LOWP },
    { .string = "true", .type = RLSL_TOKEN_LITERAL_TRUE },
    { .string = "for", .type = RLSL_TOKEN_KEYWORD_FOR },
    { .string = "if", .type = RLSL_TOKEN_KEYWORD_IF },
};

bool rlsl_token_tokenizer_parse_keyword(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    rlsl_cursor_t cursor_current = *cursor;

    bool found_token = false;
    for(int32_t i = 0; i < sizeof(rlsl_token_keywords) / sizeof(rlsl_token_str_to_type_t); i++) {
        rlsl_token_str_to_type_t* stt = &rlsl_token_keywords[i];
        size_t token_string_length = strlen(stt->string);

        if(strncmp(stt->string, source + cursor_current.index, strlen(stt->string)) == 0) {
            if(rlsl_cursor_advance(&cursor_current, source, token_string_length) != token_string_length) {
                break;
            }
            found_token = true;
            rlsl_vec_push(res->tokens, rlsl_token_create_static(stt->type, (*cursor), cursor_current));
            (*cursor) = cursor_current;
            break;
        }
    }
    return found_token;
}