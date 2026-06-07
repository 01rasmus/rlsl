#include <string.h>
#include <token/rlsl_token.h>
#include <ast/rlsl_ast.h>
#include "test_tools.h"

bool test_ast_errors_end_of_stream_okay_at_top_level() {
    const char* source = "input(0) vec3 pos; \n\t ";
    return _expect_ast_errors(source, NULL, 0);
}

bool test_ast_errors_multiple_top_level_invalid_tokens() {
    const char* source = "inp2ut(0) vec3 pos;\ninp2ut(0) vec3 pos;";
    const rlsl_error_t errors[] = {
        EXPECT_ERROR(RLSL_ERROR_EXPECTED_TOKEN,  rlsl_cursor_at_position(source, 1, 1), rlsl_cursor_at_position(source, 1, 7), false),
        EXPECT_ERROR(RLSL_ERROR_EXPECTED_TOKEN,  rlsl_cursor_at_position(source, 2, 1), rlsl_cursor_at_position(source, 2, 7), false),
    };
    return expect_ast_errors(source, errors);
}