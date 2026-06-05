#include <string.h>
#include "tools/rlsl_vec.h"
#include "rlsl_token_tokenizer_single_char.h"
#include "rlsl_token.h"

static rlsl_token_str_to_type_t rlsl_token_single_char_tokens[] = {
    { .string = "-", .type = RLSL_TOKEN_SYMBOL_DASH },
    { .string = ",", .type = RLSL_TOKEN_SYMBOL_COMMA },
    { .string = ";", .type = RLSL_TOKEN_SYMBOL_SEMICOLON },
    { .string = ":", .type = RLSL_TOKEN_SYMBOL_COLON },
    { .string = "!", .type = RLSL_TOKEN_SYMBOL_EXCLAMATION },
    { .string = ".", .type = RLSL_TOKEN_SYMBOL_DOT },
    { .string = "(", .type = RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED },
    { .string = ")", .type = RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED },
    { .string = "[", .type = RLSL_TOKEN_SYMBOL_BRACKET_OPENED },
    { .string = "]", .type = RLSL_TOKEN_SYMBOL_BRACKET_CLOSED },
    { .string = "{", .type = RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED },
    { .string = "}", .type = RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED },
    { .string = "*", .type = RLSL_TOKEN_SYMBOL_STAR },
    { .string = "/", .type = RLSL_TOKEN_SYMBOL_FORWARD_SLASH },
    { .string = "&", .type = RLSL_TOKEN_SYMBOL_AND },
    { .string = "%", .type = RLSL_TOKEN_SYMBOL_PERCENT },
    { .string = "+", .type = RLSL_TOKEN_SYMBOL_PLUS },
    { .string = "<", .type = RLSL_TOKEN_SYMBOL_ARROW_LEFT },
    { .string = "=", .type = RLSL_TOKEN_SYMBOL_EQUAL },
    { .string = ">", .type = RLSL_TOKEN_SYMBOL_ARROW_RIGHT },
    { .string = "|", .type = RLSL_TOKEN_SYMBOL_PIPE },
    { .string = "~", .type = RLSL_TOKEN_SYMBOL_TILDE },
};

bool rlsl_token_tokenizer_parse_single_char_token(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    rlsl_cursor_t cursor_current = *cursor;

    bool found_token = false;
    for(int32_t i = 0; i < sizeof(rlsl_token_single_char_tokens) / sizeof(rlsl_token_str_to_type_t); i++) {
        rlsl_token_str_to_type_t* stt = &rlsl_token_single_char_tokens[i];
        size_t token_string_length = strlen(stt->string);

        if(strncmp(stt->string, source + cursor_current.offset, strlen(stt->string)) == 0) {
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