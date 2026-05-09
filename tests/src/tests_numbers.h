#include <stdio.h>
#include <rlsl_token.h>

bool _test_token_number_integer(const char* source, uint64_t number) {
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    if(res.token_count != 1) {
        return false;
    }

    if(res.error_count > 0) {
        return false;
    }

    rlsl_token_t token = res.tokens[0];
    return token.type == RLSL_TOKEN_LITERAL_INT && token.value.num_int.value == number;
}

bool _test_token_number_double(const char* source, long double number) {
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    if(res.token_count != 1) {
        return false;
    }

    if(res.error_count > 0) {
        return false;
    }
    
    rlsl_token_t token = res.tokens[0];
    return token.type == RLSL_TOKEN_LITERAL_FLOAT && token.value.num_float.value == number;
}

bool _test_token_number_error(const char* source, rlsl_error_enum_t error) {
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    if(res.token_count > 0) {
        return false;
    }

    if(res.error_count != 1) {
        return false;
    }

    rlsl_error_t err = res.errors[0];
    return err.code == error;
}

bool test_token_number_with_line_break() {
    const char* source = "0x10\n0x10";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    if(res.token_count != 3) {
        return false;
    }

    rlsl_token_t t1 = res.tokens[0];
    rlsl_token_t t2 = res.tokens[1];
    rlsl_token_t t3 = res.tokens[2];

    if(!(t1.type == RLSL_TOKEN_LITERAL_INT && t1.value.num_int.value == 16)) {
        return false;
    }

    if(t2.type != RLSL_TOKEN_SYMBOL_SPACE) {
        return false;
    }

    if(!(t3.type == RLSL_TOKEN_LITERAL_INT && t3.value.num_int.value == 16)) {
        return false;
    }
    return true;
}

bool test_token_number_hexadecimal_full_range() {
    return _test_token_number_integer("0xEE98710", 250185488);
}

bool test_token_number_hexadecimal_dec_range() {
    return _test_token_number_integer("0x6543210", 106181136);
}

bool test_token_number_hexadecimal_bin_range() {
    return _test_token_number_integer("0x100", 256);
}

bool test_token_number_decimal_full_range() {
    return _test_token_number_integer("6543210", 6543210);
}

bool test_token_number_decimal_bin_range() {
    return _test_token_number_integer("100", 100);
}

bool test_token_number_binary() {
    return _test_token_number_integer("0b100", 4);
}

bool test_token_number_float() {
    return _test_token_number_double("4.0", 4.0);
}

bool test_token_number_ensure_error_hexadecimal_comma() {
    return _test_token_number_error("0x10.1AF", RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER);
}

bool test_token_number_ensure_error_binary_comma() {
    return _test_token_number_error("0b10.1001", RLSL_ERROR_INVALID_BINARY_NUMBER);
}

bool test_token_number_ensure_error_decimal_with_hexadecimal() {
    return _test_token_number_error("10EF", RLSL_ERROR_INVALID_DECIMAL_NUMBER);
}

bool test_token_number_ensure_error_binary_with_hexadecimal() {
    return _test_token_number_error("0b10EF", RLSL_ERROR_INVALID_BINARY_NUMBER);
}

bool test_token_number_ensure_error_binary_with_decimal() {
    return _test_token_number_error("0b1032", RLSL_ERROR_INVALID_BINARY_NUMBER);
}

bool test_token_number_ensure_error_float_with_multiple_commas() {
    return _test_token_number_error("0.0.1", RLSL_ERROR_FLOAT_TOO_MANY_COMMAS);
}

bool test_token_number_ensure_error_hexadecimal_with_invalid_character() {
    return _test_token_number_error("0x10Q", RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER);
}

bool test_token_number_ensure_error_decimal_with_invalid_character() {
    return _test_token_number_error("10S", RLSL_ERROR_INVALID_DECIMAL_NUMBER);
}

bool test_token_number_ensure_error_binary_with_invalid_character() {
    return _test_token_number_error("0b10G", RLSL_ERROR_INVALID_BINARY_NUMBER);
}

bool test_token_number_ensure_error_decimal_with_zero_at_start() {
    return _test_token_number_error("010378198", RLSL_ERROR_DECIMAL_HAS_ZERO_AT_START);
}

bool test_token_number_float_with_multiple_zeros_at_start() {
    return _test_token_number_double("004.0", 4.0);
}

bool test_token_number_hexadecimal_with_zeroes_at_start() {
    return _test_token_number_integer("0x00010", 16);
}

bool test_token_number_binary_with_zeroes_at_start() {
    return _test_token_number_integer("0b00010", 2);
}

bool test_token_number_ensure_error_hexadecimal_with_more_than_one_zero_at_start() {
    return _test_token_number_error("00x10", RLSL_ERROR_INVALID_HEXADECIMAL_NUMBER);
}

bool test_token_number_ensure_error_binary_with_more_than_one_zero_at_start() {
    return _test_token_number_error("00b10", RLSL_ERROR_INVALID_BINARY_NUMBER);
}