#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tools/rlsl_str.h"
#include "tools/rlsl_vec.h"
#include "rlsl_token_tokenizer_literal_and_keyword.h"

_Static_assert(sizeof(unsigned long long) == 8, "Expected 64-bit unsigned long long");
_Static_assert(sizeof(double) == 8, "Expected 64-bit doubles");

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

static const char* hex_substrings[] = { "A", "B", "C", "D", "E", "F", "a", "b", "c", "d", "e", "f" };
static const char* dec_substrings[] = { "2", "3", "4", "5", "6", "7", "8", "9" };
static const char* bin_substrings[] = { "0", "1" };

bool rlsl_token_tokenizer_parse_literal_and_keyword(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    rlsl_cursor_t cursor_current = (*cursor);

    //we should first check if the character at the start even is valid as a number/identifier
    const char first_char = source[cursor->offset];
    const char second_char = source[cursor->offset + 1];
    bool valid_first_char = isalnum((uint8_t)first_char) || first_char == '_' || (first_char == '.' && isdigit((uint8_t)second_char));
    if(!valid_first_char) {
        return false;
    }

    char result[TOKEN_LITERAL_RESULT_SIZE] = { 0 };
    size_t result_size = 0;
    const char* integer_prefixes[] = { "0x", "0b" };
    const uint64_t integer_prefix_flags[] = { TOKEN_LITERAL_FLAG_HEX, TOKEN_LITERAL_FLAG_BINARY };

    uint64_t contains_flags = 0;
    uint64_t starts_with = 0;
    uint32_t decimal_point_count = 0;
    bool has_invalid_letter = false;
    bool has_letter = false;

    //check if it starts with one of the integer suffixes
    int32_t suffix_index = rlsl_str_starts_with_any_of(source + cursor_current.offset, integer_prefixes);
    if(suffix_index != -1) {
        const char* str = integer_prefixes[suffix_index];
        uint64_t flag = integer_prefix_flags[suffix_index];
        rlsl_str_cat(result, TOKEN_LITERAL_RESULT_SIZE, str);
        starts_with |= flag;
        result_size = rlsl_cursor_advance(&cursor_current, source, strlen(str));
    } else if(isdigit((uint8_t)source[cursor_current.offset])) {
        starts_with |= TOKEN_LITERAL_FLAG_DECIMAL;
    } else if(isalpha((uint8_t)source[cursor_current.offset])) {
        starts_with |= TOKEN_LITERAL_FLAG_LETTER;
    } else if(first_char == '.' && isdigit((uint8_t)second_char)) {
        char str[3] = {
            first_char,
            second_char,
            '\0'
        };
        rlsl_str_cat(result, TOKEN_LITERAL_RESULT_SIZE, str);
        contains_flags |= TOKEN_LITERAL_FLAG_DECIMAL_POINT;
        contains_flags |= TOKEN_LITERAL_FLAG_DECIMAL;
        starts_with |= TOKEN_LITERAL_FLAG_DECIMAL_POINT;
        decimal_point_count++;
        result_size = rlsl_cursor_advance(&cursor_current, source, strlen(str));
    }

    //check characters
    const char* str = NULL;
    char temp[2] = { 0 };
    while(true) {
        if(str) {
            rlsl_str_cat(result, TOKEN_LITERAL_RESULT_SIZE, str);
            rlsl_cursor_advance(&cursor_current, source, strlen(str));
            str = NULL;
            result_size++;
        }

        const char current_char = source[cursor_current.offset];
        const bool is_identifier = (contains_flags & TOKEN_LITERAL_FLAG_LETTER) == TOKEN_LITERAL_FLAG_LETTER;
        const bool should_continue = isalnum((uint8_t)current_char) || current_char == '_' || (current_char == '.' && !is_identifier);
        if(!should_continue) {
            break;
        }

        int32_t hex_index = rlsl_str_starts_with_any_of(source + cursor_current.offset, hex_substrings);
        if(hex_index != -1) {
            str = hex_substrings[hex_index];
            contains_flags |= TOKEN_LITERAL_FLAG_HEX;
            continue;
        }

        int32_t dec_index = rlsl_str_starts_with_any_of(source + cursor_current.offset, dec_substrings);
        if(dec_index != -1) {
            str = dec_substrings[dec_index];
            contains_flags |= TOKEN_LITERAL_FLAG_DECIMAL;
            continue;
        }

        int32_t bin_index = rlsl_str_starts_with_any_of(source + cursor_current.offset, bin_substrings);
        if(bin_index != -1) {
            str = bin_substrings[bin_index];
            contains_flags |= TOKEN_LITERAL_FLAG_BINARY;
            continue;
        }

        if(isalpha((uint8_t)current_char) || current_char == '_') {
            temp[0] = current_char;
            str = temp;
            contains_flags |= TOKEN_LITERAL_FLAG_LETTER;
            continue;
        }

        if(current_char == '.') {
            temp[0] = '.';
            str = temp;
            decimal_point_count++;
            contains_flags |= TOKEN_LITERAL_FLAG_DECIMAL_POINT;
            continue;
        }

        if(!str) {
            temp[0] = current_char;
            str = temp;
            contains_flags |= TOKEN_LITERAL_FLAG_INVALID;
            continue;
        }
    }

    if(result_size == 0) {
        goto done;
    }

    if(contains_flags & TOKEN_LITERAL_FLAG_INVALID) {
        rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_INVALID_CHARACTER_IN_LIT_OR_IDENT, cursor, &cursor_current));
        goto done;
    }

    if(contains_flags & TOKEN_LITERAL_FLAG_DECIMAL_POINT) {
        uint64_t starts_with_hex = starts_with == TOKEN_LITERAL_FLAG_HEX;
        uint64_t starts_with_dec = starts_with == TOKEN_LITERAL_FLAG_DECIMAL;
        uint64_t starts_with_decimal_point = starts_with == TOKEN_LITERAL_FLAG_DECIMAL_POINT;
        uint64_t starts_with_bin = starts_with ==  TOKEN_LITERAL_FLAG_BINARY;
        uint64_t starts_with_let = (starts_with & TOKEN_LITERAL_FLAG_LETTER) == TOKEN_LITERAL_FLAG_LETTER;
        uint64_t contains_hex = (contains_flags & TOKEN_LITERAL_FLAG_HEX) == TOKEN_LITERAL_FLAG_HEX;
        if(starts_with_bin) {
            rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_INVALID_BINARY_NUMBER, cursor, &cursor_current));
            goto done;
        }
        if(starts_with_hex) {
            rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER, cursor, &cursor_current));
            goto done;
        }
        if(decimal_point_count > 1) {
            rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_FLOAT_TOO_MANY_DECIMAL_POINTS, cursor, &cursor_current));
            goto done;
        }
        if(!(starts_with_dec || starts_with_decimal_point) || starts_with == 0 || contains_hex) {
            rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_FLOAT_IS_NOT_DECIMAL, cursor, &cursor_current));
            goto done;
        }

        errno = 0;
        double value = strtod(result, NULL);
        bool overflow = errno == ERANGE;
        rlsl_vec_push(res->tokens, rlsl_token_create_float(value, overflow, (*cursor), cursor_current));
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
        
        //check if there were a bunch of zeroes at the start that follows 0x or 0b
        for(int64_t i = 0; i < strlen(result); i++) {
            if(result[i] != '0') {
                break;
            }

            uint64_t which = rlsl_str_starts_with_any_of(result + i, integer_prefixes);
            if(which == 0) {
                rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER, cursor, &cursor_current));
                goto done;
            } else if(which == 1) {
                rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_INVALID_BINARY_NUMBER, cursor, &cursor_current));
                goto done;
            }
        }

        //decimal numbers cannot start with zeros (in some languages they can but then they would be octal)
        //caution: only if the number is actually more than 1 character wide. the number '0' **is** valid
        if(result_size > 1 && result[0] == '0') {
            rlsl_vec_push(res->errors, rlsl_error_create(RLSL_ERROR_DECIMAL_LEADING_ZERO, cursor, &cursor_current));
            goto done;
        }
    } else if(starts_with == TOKEN_LITERAL_FLAG_BINARY) {
        valid_number = contains_flags == TOKEN_LITERAL_FLAG_BINARY;
        base_index = 0;
    }

    if(base_index != -1) {
        if(!valid_number) {
            rlsl_vec_push(res->errors, rlsl_error_create(base_error_codes[base_index], cursor, &cursor_current));
            goto done;
        }

        //fine value!
        int32_t base = bases[base_index];
        errno = 0;
        uint64_t value = strtoull(base == 10 ? result : (result + 2), NULL, base);
        bool overflow = errno == ERANGE;

        rlsl_vec_push(res->tokens, rlsl_token_create_int(value, overflow, (*cursor), cursor_current));
        goto done;
    }

    //first check if the result is a keyword
    bool found_token = false;
    for(int32_t i = 0; i < sizeof(rlsl_token_keywords) / sizeof(rlsl_token_str_to_type_t); i++) {
        rlsl_token_str_to_type_t* stt = &rlsl_token_keywords[i];
        if(strcmp(stt->string, result) == 0) {
            found_token = true;
            rlsl_vec_push(res->tokens, rlsl_token_create_static(stt->type, (*cursor), cursor_current));
            break;
        }
    }

    //if not, it is an identifier
    if(!found_token) {
        size_t identifier_size = strlen(result) + 1;
        char* identifier = malloc(identifier_size);
        if(identifier) {
            memcpy(identifier, result, identifier_size);
        }

        rlsl_vec_push(res->tokens, rlsl_token_create_identifier(identifier, (*cursor), cursor_current));
    }
    
    goto done;
done:
    (*cursor) = cursor_current;
    return true;
}