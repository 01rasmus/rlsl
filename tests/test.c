#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <tools/rlsl_str.h>

#include "tests_token_static.h"
#include "tests_token_numbers.h"
#include "tests_token_identifier.h"
#include "tests_token_comments.h"
#include "tests_ast_recovery.h"
#include "tests_ast_struct.h"
#include "tests_ast_errors.h"

#define TEST_REGISTRATION(TEST) { .name = #TEST, .function = TEST }

typedef bool (*test_function_t)();

typedef struct test_registration_t {
    const char* name;
    test_function_t function;
} test_registration_t;

test_registration_t tests[] = {
    TEST_REGISTRATION(test_token_static_uniform),
    TEST_REGISTRATION(test_token_static_input),
    TEST_REGISTRATION(test_token_static_output),
    TEST_REGISTRATION(test_token_static_return),
    TEST_REGISTRATION(test_token_static_struct),
    TEST_REGISTRATION(test_token_static_const),
    TEST_REGISTRATION(test_token_static_lowp),
    TEST_REGISTRATION(test_token_static_mediump),
    TEST_REGISTRATION(test_token_static_highp),
    TEST_REGISTRATION(test_token_static_false),
    TEST_REGISTRATION(test_token_static_while),
    TEST_REGISTRATION(test_token_static_else),
    TEST_REGISTRATION(test_token_static_true),
    TEST_REGISTRATION(test_token_static_for),
    TEST_REGISTRATION(test_token_static_if),
    TEST_REGISTRATION(test_token_static_dash),
    TEST_REGISTRATION(test_token_static_comma),
    TEST_REGISTRATION(test_token_static_semi_colon),
    TEST_REGISTRATION(test_token_static_colon),
    TEST_REGISTRATION(test_token_static_exclamation_mark),
    TEST_REGISTRATION(test_token_static_opened_paranthesis),
    TEST_REGISTRATION(test_token_static_closed_paranthesis),
    TEST_REGISTRATION(test_token_static_opened_bracket),
    TEST_REGISTRATION(test_token_static_closed_bracket),
    TEST_REGISTRATION(test_token_static_opened_curly_bracket),
    TEST_REGISTRATION(test_token_static_closed_curly_bracket),
    TEST_REGISTRATION(test_token_static_star),
    TEST_REGISTRATION(test_token_static_forward_slash),
    TEST_REGISTRATION(test_token_static_and),
    TEST_REGISTRATION(test_token_static_percent),
    TEST_REGISTRATION(test_token_static_plus),
    TEST_REGISTRATION(test_token_static_arrow_left),
    TEST_REGISTRATION(test_token_static_equal),
    TEST_REGISTRATION(test_token_static_arrow_right),
    TEST_REGISTRATION(test_token_static_bar),
    TEST_REGISTRATION(test_token_static_tilde),
    TEST_REGISTRATION(test_token_static_dot),

    TEST_REGISTRATION(test_token_number_with_line_break),
    TEST_REGISTRATION(test_token_number_hexadecimal_full_range),
    TEST_REGISTRATION(test_token_number_hexadecimal_dec_range),
    TEST_REGISTRATION(test_token_number_hexadecimal_bin_range),
    TEST_REGISTRATION(test_token_number_decimal_full_range),
    TEST_REGISTRATION(test_token_number_decimal_bin_range),
    TEST_REGISTRATION(test_token_number_binary),
    TEST_REGISTRATION(test_token_number_float),
    TEST_REGISTRATION(test_token_number_ensure_error_hexadecimal_comma),
    TEST_REGISTRATION(test_token_number_ensure_error_binary_comma),
    TEST_REGISTRATION(test_token_number_ensure_error_decimal_with_hexadecimal),
    TEST_REGISTRATION(test_token_number_ensure_error_binary_with_hexadecimal),
    TEST_REGISTRATION(test_token_number_ensure_error_binary_with_decimal),
    TEST_REGISTRATION(test_token_number_ensure_error_float_with_multiple_commas),
    TEST_REGISTRATION(test_token_number_ensure_error_hexadecimal_with_invalid_character),
    TEST_REGISTRATION(test_token_number_ensure_error_decimal_with_invalid_character),
    TEST_REGISTRATION(test_token_number_ensure_error_binary_with_invalid_character),
    TEST_REGISTRATION(test_token_number_ensure_error_decimal_with_zero_at_start),
    TEST_REGISTRATION(test_token_number_float_with_multiple_zeros_at_start),
    TEST_REGISTRATION(test_token_number_hexadecimal_with_zeroes_at_start),
    TEST_REGISTRATION(test_token_number_binary_with_zeroes_at_start),
    TEST_REGISTRATION(test_token_number_ensure_error_hexadecimal_with_more_than_one_zero_at_start),
    TEST_REGISTRATION(test_token_number_ensure_error_binary_with_more_than_one_zero_at_start),
    TEST_REGISTRATION(test_token_number_float_operators),
    TEST_REGISTRATION(test_token_number_float_operators_with_space),
    TEST_REGISTRATION(test_token_number_integer_operators),
    TEST_REGISTRATION(test_token_number_integer_operators_with_space),
    TEST_REGISTRATION(test_token_number_integer_operators_with_new_line),
    TEST_REGISTRATION(test_token_number_integer_operators_with_tab),
    TEST_REGISTRATION(test_token_number_float_with_decimal_point_at_start),
    TEST_REGISTRATION(test_token_number_integer_zero),

    TEST_REGISTRATION(test_token_identifier),
    TEST_REGISTRATION(test_token_identifier_address_sequence),
    TEST_REGISTRATION(test_token_identifier_with_digits),
    TEST_REGISTRATION(test_token_identifier_with_keyword),
    TEST_REGISTRATION(test_token_identifier_with_digits_and_underscore),
    //TEST_REGISTRATION(test_token_identifier_ensure_error_invalid_character),

    TEST_REGISTRATION(test_token_comment_simple),
    TEST_REGISTRATION(test_token_comment_c_style),
    TEST_REGISTRATION(test_token_comment_c_style_without_close),
    TEST_REGISTRATION(test_token_comment_with_variable_declaration_after_simple),
    TEST_REGISTRATION(test_token_comment_with_variable_declaration_after_c_styled),
    TEST_REGISTRATION(test_token_comment_with_c_styled_start_token_in_simple),
    TEST_REGISTRATION(test_token_comment_with_c_styled_end_token_in_simple),

    TEST_REGISTRATION(test_ast_struct_empty),
    TEST_REGISTRATION(test_ast_struct_float),
    TEST_REGISTRATION(test_ast_struct_float_lowp),
    TEST_REGISTRATION(test_ast_struct_float_mediump),
    TEST_REGISTRATION(test_ast_struct_float_highp),

    TEST_REGISTRATION(test_ast_errors_end_of_stream_okay_at_top_level),
    TEST_REGISTRATION(test_ast_errors_multiple_top_level_invalid_tokens),
    
    TEST_REGISTRATION(tests_ast_recovery_invalid_var_declaration_in_multiple_structs),
    TEST_REGISTRATION(test_ast_recovery_ensure_valid_vars_stay_even_with_invalid_var_declarations),
};

int32_t main() {
    uint64_t passed = 0;
    uint64_t failed = 0;

    for(size_t i = 0; i < sizeof(tests) / sizeof(test_registration_t); i++) {
        test_registration_t test = tests[i];
        bool pass = test.function();
        if(pass) {
            printf(PRINTF_COL_GREEN PRINTF_COL_BOLD "passed " PRINTF_COL_RESET "%s\n", test.name);
            passed++;
        } else {
            printf(PRINTF_COL_RED PRINTF_COL_BOLD "failed " PRINTF_COL_RESET "%s\n", test.name);
            failed++;
        }
    }

    if(failed > 0) {
        printf(PRINTF_COL_RED PRINTF_COL_BOLD);
    } else {
        printf(PRINTF_COL_GREEN PRINTF_COL_BOLD);
    }

    printf("\nPassed %llu, and failed %llu\n" PRINTF_COL_RESET, passed, failed);
    return failed;
}