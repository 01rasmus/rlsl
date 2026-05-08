#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "rlsl_tools/rlsl_str.h"
#include "rlsl_tools/rlsl_vec.h"
#include "rlsl_token.h"

_Static_assert(sizeof(unsigned long long) == 8, "Expected 64-bit unsigned long long");

typedef struct rlsl_token_str_to_type_t {
    const char* string;
    rlsl_token_type_t type;
} rlsl_token_str_to_type_t;

/*
    this array contains strings that matches
    the actual strings that is equialent
    to a static token. Like "struct" or "*".

    these are sorted by length and then
    by alphabetical order, starting with
    the longest
*/
static rlsl_token_str_to_type_t rlsl_token_static_matches[] = {
    { .string = "uniform", .type = RLSL_TOKEN_KEYWORD_UNIFORM },
    { .string = "double", .type = RLSL_TOKEN_TYPE_DOUBLE },
    { .string = "mat2x2", .type = RLSL_TOKEN_TYPE_MAT2X2 },
    { .string = "mat2x3", .type = RLSL_TOKEN_TYPE_MAT2X3 },
    { .string = "mat2x4", .type = RLSL_TOKEN_TYPE_MAT2X4 },
    { .string = "mat3x2", .type = RLSL_TOKEN_TYPE_MAT3X2 },
    { .string = "mat3x3", .type = RLSL_TOKEN_TYPE_MAT3X3 },
    { .string = "mat3x4", .type = RLSL_TOKEN_TYPE_MAT3X4 },
    { .string = "mat4x2", .type = RLSL_TOKEN_TYPE_MAT4X2 },
    { .string = "mat4x3", .type = RLSL_TOKEN_TYPE_MAT4X3 },
    { .string = "mat4x4", .type = RLSL_TOKEN_TYPE_MAT4X4 },
    { .string = "output", .type = RLSL_TOKEN_KEYWORD_OUTPUT },
    { .string = "return", .type = RLSL_TOKEN_KEYWORD_RETURN },
    { .string = "struct", .type = RLSL_TOKEN_KEYWORD_STRUCT },
    { .string = "bvec2", .type = RLSL_TOKEN_TYPE_BVEC2 },
    { .string = "bvec3", .type = RLSL_TOKEN_TYPE_BVEC3 },
    { .string = "bvec4", .type = RLSL_TOKEN_TYPE_BVEC4 },
    { .string = "const", .type = RLSL_TOKEN_KEYWORD_CONST },
    { .string = "dvec2", .type = RLSL_TOKEN_TYPE_DVEC2 },
    { .string = "dvec3", .type = RLSL_TOKEN_TYPE_DVEC3 },
    { .string = "dvec4", .type = RLSL_TOKEN_TYPE_DVEC4 },
    { .string = "false", .type = RLSL_TOKEN_LITERAL_FALSE },
    { .string = "float", .type = RLSL_TOKEN_TYPE_FLOAT },
    { .string = "input", .type = RLSL_TOKEN_KEYWORD_INPUT },
    { .string = "ivec2", .type = RLSL_TOKEN_TYPE_IVEC2 },
    { .string = "ivec3", .type = RLSL_TOKEN_TYPE_IVEC3 },
    { .string = "ivec4", .type = RLSL_TOKEN_TYPE_IVEC4 },
    { .string = "uvec2", .type = RLSL_TOKEN_TYPE_UVEC2 },
    { .string = "uvec3", .type = RLSL_TOKEN_TYPE_UVEC3 },
    { .string = "uvec4", .type = RLSL_TOKEN_TYPE_UVEC4 },
    { .string = "while", .type = RLSL_TOKEN_KEYWORD_WHILE },
    { .string = "bool", .type = RLSL_TOKEN_TYPE_BOOL },
    { .string = "else", .type = RLSL_TOKEN_KEYWORD_ELSE },
    { .string = "mat2", .type = RLSL_TOKEN_TYPE_MAT2 },
    { .string = "mat3", .type = RLSL_TOKEN_TYPE_MAT3 },
    { .string = "mat4", .type = RLSL_TOKEN_TYPE_MAT4 },
    { .string = "true", .type = RLSL_TOKEN_LITERAL_TRUE },
    { .string = "uint", .type = RLSL_TOKEN_TYPE_UINT },
    { .string = "vec2", .type = RLSL_TOKEN_TYPE_VEC2 },
    { .string = "vec3", .type = RLSL_TOKEN_TYPE_VEC3 },
    { .string = "vec4", .type = RLSL_TOKEN_TYPE_VEC4 },
    { .string = "for", .type = RLSL_TOKEN_KEYWORD_FOR },
    { .string = "int", .type = RLSL_TOKEN_TYPE_INT },
    { .string = "if", .type = RLSL_TOKEN_KEYWORD_IF },

    //single character tokens
    { .string = "-", .type = RLSL_TOKEN_SYMBOL_DASH },
    { .string = ",", .type = RLSL_TOKEN_SYMBOL_COMMA },
    { .string = ";", .type = RLSL_TOKEN_SYMBOL_SEMICOLON },
    { .string = ":", .type = RLSL_TOKEN_SYMBOL_COLON },
    { .string = "!", .type = RLSL_TOKEN_SYMBOL_EXCLAMATION },
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

static const char* hex_substrings[] = { "A", "B", "C", "D", "E", "F", "a", "b", "c", "d", "e", "f" };
static const char* dec_substrings[] = { "2", "3", "4", "5", "6", "7", "8", "9" };
static const char* bin_substrings[] = { "0", "1" };

void rlsl_token_free(rlsl_token_t* token) {
    switch(token->type) {
        default:
            break;
    }
}

/*
    list of tokenizer functions.
    the order of these functions are important
    and should not be changed
*/
static rlsl_tokenizer_function_t tokenizer_functions[] = {
    _rlsl_token_tokenizer_parse_space,
    _rlsl_token_tokenizer_parse_static_tokens,
    _rlsl_token_tokenizer_parse_literal,
};

rlsl_tokenizer_result_t rlsl_token_tokenize_string(const char* source, const char* compile_unit_identifier) {
    rlsl_tokenizer_result_t res = (rlsl_tokenizer_result_t){
        .error_count = 0,
        .token_count = 0,
        .errors = NULL,
        .tokens = NULL,
    };

    rlsl_cursor_t cursor = rlsl_cursor_create();
    size_t source_length = strlen(source);
    while(1) {
        bool added_token = false;
        for(int32_t i = 0; i < sizeof(tokenizer_functions) / sizeof(rlsl_tokenizer_function_t); i++) {
            rlsl_tokenizer_function_t tokenizer = tokenizer_functions[i];
            if(tokenizer(&cursor, &res, source, compile_unit_identifier)) {
                added_token = true;
                break;
            }
        }

        //we arrived at a character that is illegal.
        //we will add it as an error, and continue
        //to check if there are more errors further down
        if(!added_token) {

        }

        if(source_length <= cursor.index) {
            break;
        }
    }

    res.error_count = rlsl_vec_size(res.errors);
    res.token_count = rlsl_vec_size(res.tokens);
    return res;
err:
    rlsl_vec_free(res.errors);
    rlsl_vec_free(res.tokens);
    res.errors = NULL;
    res.tokens = NULL;
    return res;
}

bool _rlsl_token_tokenizer_parse_space(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    rlsl_cursor_t cursor_current = *cursor;
    rlsl_cursor_t cursor_start = cursor_current;
    bool is_space = false;
    while(1) {
        const char character = source[cursor_current.index];
        bool current_is_space = isspace(character);
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
        rlsl_token_t token = (rlsl_token_t){
            .type = RLSL_TOKEN_SYMBOL_SPACE,
            .cursor_start = cursor_start,
            .cursor_end = cursor_current,
        };
        (*cursor) = cursor_current;
        rlsl_vec_push(res->tokens, token);
    }
    return is_space;
}

bool _rlsl_token_tokenizer_parse_static_tokens(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    rlsl_cursor_t cursor_current = *cursor;

    bool found_token = false;
    for(int32_t i = 0; i < sizeof(rlsl_token_static_matches) / sizeof(rlsl_token_str_to_type_t); i++) {
        rlsl_token_str_to_type_t* stt = &rlsl_token_static_matches[i];
        size_t token_string_length = strlen(stt->string);

        if(strcmp(stt->string, source + cursor_current.index) == 0) {
            if(rlsl_cursor_advance(&cursor_current, source, token_string_length) != token_string_length) {
                break;
            }
            rlsl_token_t token = (rlsl_token_t){
                .type = stt->type,
                .cursor_start = *cursor,
                .cursor_end = cursor_current,
            };
            found_token = true;
            rlsl_vec_push(res->tokens, token);
            (*cursor) = cursor_current;
            break;
        }
    }
    return found_token;
}

#include <stdio.h>

bool _rlsl_token_tokenizer_parse_literal(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    rlsl_cursor_t cursor_current = (*cursor);

    const size_t result_size = 2048;
    char result[result_size] = { 0 };
    const char* integer_prefixes[] = { "0x", "0b" };
    const uint64_t integer_prefix_flags[] = { TOKEN_LITERAL_FLAG_HEX, TOKEN_LITERAL_FLAG_BINARY };

    uint64_t contains_flags = 0;
    uint64_t starts_with = 0;
    uint32_t comma_count = 0;
    bool has_invalid_letter = false;
    bool has_letter = false;

    //check if it starts with one of the integer suffixes
    int32_t suffix_index = rlsl_str_starts_with_any(source + cursor_current.index, integer_prefixes);
    if(suffix_index != -1) {
        const char* str = integer_prefixes[suffix_index];
        uint64_t flag = integer_prefix_flags[suffix_index];
        rlsl_str_cat(result, result_size, str);
        starts_with |= flag;
        rlsl_cursor_advance(&cursor_current, source, strlen(str));
    } else if(isnumber(source[cursor_current.index])) {
        starts_with |= TOKEN_LITERAL_FLAG_DECIMAL;
    } else if(isalpha(source[cursor_current.index])) {
        starts_with |= TOKEN_LITERAL_FLAG_LETTER;
    }

    //check characters
    const char* str = NULL;
    char temp[2] = { 0 };
    while(true) {
        if(str) {
            rlsl_str_cat(result, result_size, str);
            rlsl_cursor_advance(&cursor_current, source, strlen(str));
            str = NULL;
        }

        const char current_char = source[cursor_current.index];
        if(isspace(current_char) || current_char == '\0') {
            break;
        }

        int32_t hex_index = rlsl_str_starts_with_any(source + cursor_current.index, hex_substrings);
        if(hex_index != -1) {
            str = hex_substrings[hex_index];
            contains_flags |= TOKEN_LITERAL_FLAG_HEX;
            continue;
        }

        int32_t dec_index = rlsl_str_starts_with_any(source + cursor_current.index, dec_substrings);
        if(dec_index != -1) {
            str = dec_substrings[dec_index];
            contains_flags |= TOKEN_LITERAL_FLAG_DECIMAL;
            continue;
        }

        int32_t bin_index = rlsl_str_starts_with_any(source + cursor_current.index, bin_substrings);
        if(bin_index != -1) {
            str = bin_substrings[bin_index];
            contains_flags |= TOKEN_LITERAL_FLAG_BINARY;
            continue;
        }
        
        if(isalpha(current_char)) {
            temp[0] = current_char;
            str = temp;
            contains_flags |= TOKEN_LITERAL_FLAG_LETTER;
            continue;
        }

        if(current_char == '.') {
            temp[0] = '.';
            str = temp;
            comma_count++;
            contains_flags |= TOKEN_LITERAL_FLAG_COMMA;
            continue;
        }

        if(!str) {
            temp[0] = current_char;
            str = temp;
            contains_flags |= TOKEN_LITERAL_FLAG_INVALID;
            continue;
        }
    }

    if(contains_flags & TOKEN_LITERAL_FLAG_INVALID) {
        rlsl_error_t error = rlsl_error_create(RLSL_ERROR_INVALID_CHARACTER_IN_LIT_OR_IDENT, cursor, &cursor_current);
        rlsl_vec_push(res->errors, error);
        goto done;
    }

    if(contains_flags & TOKEN_LITERAL_FLAG_COMMA) {
        if(comma_count > 1) {
            rlsl_error_t error = rlsl_error_create(RLSL_ERROR_FLOAT_TOO_MANY_COMMAS, cursor, &cursor_current);
            rlsl_vec_push(res->errors, error);
            goto done;
        }

        uint64_t starts_with_hex = (starts_with & TOKEN_LITERAL_FLAG_HEX) == TOKEN_LITERAL_FLAG_HEX;
        uint64_t starts_with_dec = (starts_with & TOKEN_LITERAL_FLAG_DECIMAL) == TOKEN_LITERAL_FLAG_DECIMAL;
        uint64_t starts_with_bin = (starts_with & TOKEN_LITERAL_FLAG_BINARY) == TOKEN_LITERAL_FLAG_BINARY;
        uint64_t starts_with_let = (starts_with & TOKEN_LITERAL_FLAG_LETTER) == TOKEN_LITERAL_FLAG_LETTER;
        uint64_t contains_hex = (contains_flags & TOKEN_LITERAL_FLAG_HEX) == TOKEN_LITERAL_FLAG_HEX;
        printf("%llu %d\n", starts_with_let, !starts_with_dec);
        if((starts_with_bin || starts_with_hex || starts_with_let || starts_with == 0 || contains_hex)) {
            rlsl_error_t error = rlsl_error_create(RLSL_ERROR_FLOAT_IS_NOT_DECIMAL, cursor, &cursor_current);
            rlsl_vec_push(res->errors, error);
            goto done;
        }

        errno = 0;
        long double value = strtold(result, NULL);
        bool overflow = errno == ERANGE;
        printf("%Lf %d %d\n", value, overflow, !starts_with_dec);
        goto done;
    }

    const int32_t bases[] = { 2, 10, 16 };
    const uint64_t base_error_codes[] = {
        RLSL_ERROR_INVALID_BINARY_NUMBER,
        RLSL_ERROR_INVALID_DECIMAL_NUMBER,
        RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER
    };

    int32_t base_index = -1;
    bool valid_number = false;
    if(starts_with == TOKEN_LITERAL_FLAG_HEX) {
        valid_number = (contains_flags == TOKEN_LITERAL_FLAG_HEX) || (contains_flags == TOKEN_LITERAL_FLAG_DECIMAL) || (contains_flags == TOKEN_LITERAL_FLAG_BINARY);
        base_index = 2;
    } else if(starts_with == TOKEN_LITERAL_FLAG_DECIMAL) {
        valid_number = (contains_flags == TOKEN_LITERAL_FLAG_DECIMAL) || (contains_flags == TOKEN_LITERAL_FLAG_BINARY);
        base_index = 1;
    } else if(starts_with == TOKEN_LITERAL_FLAG_BINARY) {
        valid_number = contains_flags == TOKEN_LITERAL_FLAG_BINARY;
        base_index = 0;
    }

    if(base_index != -1) {
        if(!valid_number) {
            rlsl_error_t error = rlsl_error_create(base_error_codes[base_index], cursor, &cursor_current);
            rlsl_vec_push(res->errors, error);
            goto done;
        }

        //fine value!
        int32_t base = bases[base_index];
        errno = 0;
        uint64_t value = strtoull(base == 10 ? result : (result + 2), NULL, base);
        bool overflow = errno == ERANGE;

        rlsl_token_t token = (rlsl_token_t){
            .type = RLSL_TOKEN_LITERAL_INT,
            .value = {
                .integer = {
                    .value = value,
                    .overflow = overflow,
                }
            },
            .cursor_start = (*cursor),
            .cursor_end = cursor_current
        };
        rlsl_vec_push(res->tokens, token);

        //printf("res: %s %d %llu %llu %d\n", result, base, value, contains_flags, overflow);
    }
done:
    (*cursor) = cursor_current;
    return true;
}