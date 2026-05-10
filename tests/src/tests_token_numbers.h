#include <rlsl_token.h>
#include "test_tools.h"

bool test_token_number_with_line_break() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_INT(16),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_INT(16)
    };
    return expect_tokens("0x10\n0x10", tokens);
}

bool test_token_number_hexadecimal_full_range() {
    return expect_token("0xEE98710", EXPECT_TOKEN_INT(250185488));
}

bool test_token_number_hexadecimal_dec_range() {
    return expect_token("0x6543210", EXPECT_TOKEN_INT(106181136));
}

bool test_token_number_hexadecimal_bin_range() {
    return expect_token("0x100", EXPECT_TOKEN_INT(256));
}

bool test_token_number_decimal_full_range() {
    return expect_token("6543210", EXPECT_TOKEN_INT(6543210));
}

bool test_token_number_decimal_bin_range() {
    return expect_token("100", EXPECT_TOKEN_INT(100));
}

bool test_token_number_binary() {
    return expect_token("0b100", EXPECT_TOKEN_INT(4));
}

bool test_token_number_float() {
    return expect_token("4.0", EXPECT_TOKEN_FLOAT(4.0));
}

bool test_token_number_ensure_error_hexadecimal_comma() {
    return expect_error("0x10.1AF", RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER, 1, 1, 1, 9);
}

bool test_token_number_ensure_error_binary_comma() {
    return expect_error("0b10.1001", RLSL_ERROR_INVALID_BINARY_NUMBER, 1, 1, 1, 10);
}

bool test_token_number_ensure_error_decimal_with_hexadecimal() {
    return expect_error("10EF", RLSL_ERROR_INVALID_DECIMAL_NUMBER, 1, 1, 1, 5);
}

bool test_token_number_ensure_error_binary_with_hexadecimal() {
    return expect_error("0b10EF", RLSL_ERROR_INVALID_BINARY_NUMBER, 1, 1, 1, 7);
}

bool test_token_number_ensure_error_binary_with_decimal() {
    return expect_error("0b1032", RLSL_ERROR_INVALID_BINARY_NUMBER, 1, 1, 1, 7);
}

bool test_token_number_ensure_error_float_with_multiple_commas() {
    return expect_error("0.0.1", RLSL_ERROR_FLOAT_TOO_MANY_DECIMAL_POINTS, 1, 1, 1, 6);
}

bool test_token_number_ensure_error_hexadecimal_with_invalid_character() {
    return expect_error("0x10Q", RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER, 1, 1, 1, 6);
}

bool test_token_number_ensure_error_decimal_with_invalid_character() {
    return expect_error("10S", RLSL_ERROR_INVALID_DECIMAL_NUMBER, 1, 1, 1, 4);
}

bool test_token_number_ensure_error_binary_with_invalid_character() {
    return expect_error("0b10G", RLSL_ERROR_INVALID_BINARY_NUMBER, 1, 1, 1, 6);
}

bool test_token_number_ensure_error_decimal_with_zero_at_start() {
    return expect_error("010378198", RLSL_ERROR_DECIMAL_LEADING_ZERO, 1, 1, 1, 10);
}

bool test_token_number_float_with_multiple_zeros_at_start() {
    return expect_token("004.0", EXPECT_TOKEN_FLOAT(4.0));
}

bool test_token_number_hexadecimal_with_zeroes_at_start() {
    return expect_token("0x00010", EXPECT_TOKEN_INT(16));
}

bool test_token_number_binary_with_zeroes_at_start() {
    return expect_token("0b00010", EXPECT_TOKEN_INT(2));
}

bool test_token_number_ensure_error_hexadecimal_with_more_than_one_zero_at_start() {
    return expect_error("00x10", RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER, 1, 1, 1, 6);
}

bool test_token_number_ensure_error_binary_with_more_than_one_zero_at_start() {
    return expect_error("00b10", RLSL_ERROR_INVALID_BINARY_NUMBER, 1, 1, 1, 6);
}

bool test_token_number_float_operators() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_FLOAT(1.0),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_PLUS),
        EXPECT_TOKEN_FLOAT(2.0),
    };
    return expect_tokens("1.0+2.0", tokens);
}

bool test_token_number_float_operators_with_space() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_FLOAT(1.0),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_STAR),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_FLOAT(2.0),
    };
    return expect_tokens("1.0 * 2.0", tokens);
}

bool test_token_number_integer_operators() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_INT(100),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_PLUS),
        EXPECT_TOKEN_INT(200),
    };
    return expect_tokens("100+200", tokens);
}

bool test_token_number_integer_operators_with_space() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_INT(100),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_STAR),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_INT(200),
    };
    return expect_tokens("100 * 200", tokens);
}

bool test_token_number_integer_operators_with_new_line() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_INT(100),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_STAR),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_INT(200),
    };
    return expect_tokens("100 *\n 200", tokens);
}

bool test_token_number_integer_operators_with_tab() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_INT(100),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_STAR),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_INT(200),
    };
    return expect_tokens("100 *\t 200", tokens);
}

bool test_token_number_float_with_decimal_point_at_start() {
    return expect_token(".4", EXPECT_TOKEN_FLOAT(0.4));
}