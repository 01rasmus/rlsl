#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <rlsl_tools/rlsl_str.h>

#include "tests_static_tokens.h"
#include "tests_numbers.h"

typedef bool (*test_function_t)();

typedef struct test_registration_t {
    const char* name;
    test_function_t function;
} test_registration_t;

test_registration_t tests[] = {
    { .name = "token static double", .function = test_token_static_double },
    { .name = "token static uniform", .function = test_token_static_uniform },
    { .name = "token static input", .function = test_token_static_input },
    { .name = "token static output", .function = test_token_static_output },
    { .name = "token static mat2x2", .function = test_token_static_mat2x2 },
    { .name = "token static mat2x3", .function = test_token_static_mat2x3 },
    { .name = "token static mat2x4", .function = test_token_static_mat2x4 },
    { .name = "token static mat3x2", .function = test_token_static_mat3x2 },
    { .name = "token static mat3x3", .function = test_token_static_mat3x3 },
    { .name = "token static mat3x4", .function = test_token_static_mat3x4 },
    { .name = "token static mat4x2", .function = test_token_static_mat4x2 },
    { .name = "token static mat4x3", .function = test_token_static_mat4x3 },
    { .name = "token static mat4x4", .function = test_token_static_mat4x4 },
    { .name = "token static return", .function = test_token_static_return },
    { .name = "token static struct", .function = test_token_static_struct },
    { .name = "token static bvec2", .function = test_token_static_bvec2 },
    { .name = "token static bvec3", .function = test_token_static_bvec3 },
    { .name = "token static bvec4", .function = test_token_static_bvec4 },
    { .name = "token static const", .function = test_token_static_const },
    { .name = "token static dvec2", .function = test_token_static_dvec2 },
    { .name = "token static dvec3", .function = test_token_static_dvec3 },
    { .name = "token static dvec4", .function = test_token_static_dvec4 },
    { .name = "token static false", .function = test_token_static_false },
    { .name = "token static float", .function = test_token_static_float },
    { .name = "token static ivec2", .function = test_token_static_ivec2 },
    { .name = "token static ivec3", .function = test_token_static_ivec3 },
    { .name = "token static ivec4", .function = test_token_static_ivec4 },
    { .name = "token static uvec2", .function = test_token_static_uvec2 },
    { .name = "token static uvec3", .function = test_token_static_uvec3 },
    { .name = "token static uvec4", .function = test_token_static_uvec4 },
    { .name = "token static while", .function = test_token_static_while },
    { .name = "token static bool", .function = test_token_static_bool },
    { .name = "token static else", .function = test_token_static_else },
    { .name = "token static mat2", .function = test_token_static_mat2 },
    { .name = "token static mat3", .function = test_token_static_mat3 },
    { .name = "token static mat4", .function = test_token_static_mat4 },
    { .name = "token static true", .function = test_token_static_true },
    { .name = "token static uint", .function = test_token_static_uint },
    { .name = "token static vec2", .function = test_token_static_vec2 },
    { .name = "token static vec3", .function = test_token_static_vec3 },
    { .name = "token static vec4", .function = test_token_static_vec4 },
    { .name = "token static for", .function = test_token_static_for },
    { .name = "token static int", .function = test_token_static_int },
    { .name = "token static if", .function = test_token_static_if },
    { .name = "token static -", .function = test_token_static_dash },
    { .name = "token static ,", .function = test_token_static_comma },
    { .name = "token static ;", .function = test_token_static_semi_colon },
    { .name = "token static :", .function = test_token_static_colon },
    { .name = "token static !", .function = test_token_static_exclamation_mark },
    { .name = "token static (", .function = test_token_static_opened_paranthesis },
    { .name = "token static )", .function = test_token_static_closed_paranthesis },
    { .name = "token static [", .function = test_token_static_opened_bracket },
    { .name = "token static ]", .function = test_token_static_closed_bracket },
    { .name = "token static {", .function = test_token_static_opened_curly_bracket },
    { .name = "token static }", .function = test_token_static_closed_curly_bracket },
    { .name = "token static *", .function = test_token_static_star },
    { .name = "token static /", .function = test_token_static_forward_slash },
    { .name = "token static &", .function = test_token_static_and },
    { .name = "token static %", .function = test_token_static_percent },
    { .name = "token static +", .function = test_token_static_plus },
    { .name = "token static <", .function = test_token_static_arrow_left },
    { .name = "token static =", .function = test_token_static_equal },
    { .name = "token static >", .function = test_token_static_arrow_right },
    { .name = "token static |", .function = test_token_static_bar },
    { .name = "token static ~", .function = test_token_static_tilde },

    { .name = "token static numbers with line break", .function = test_token_number_with_line_break },
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

    printf("\nPassed %llu tests, and failed %llu\n", passed, failed);
    return failed;
}