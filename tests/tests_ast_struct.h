#include <string.h>
#include <token/rlsl_token.h>
#include <ast/rlsl_ast.h>
#include "test_tools.h"

bool test_ast_struct_empty() {
    const char* source = "struct test {};";

    rlsl_ast_struct_t structs[] = {
        (rlsl_ast_struct_t) {
            .name = "test",
            .member_count = 0,
            .members = NULL,
            .start = rlsl_cursor_at_position(source, 1, 8),
            .end = rlsl_cursor_at_position(source, 1, 12),
        },
    };
    
    rlsl_ast_module_t expected = { 0 };
    expected.struct_count = 1;
    expected.structs = structs;

    return expect_ast(source, &expected);
}

bool test_ast_struct_float() {
    const char* source = "struct test { float var; };";

    rlsl_ast_member_t members[] = {
        (rlsl_ast_member_t) {
            .name = "var",
            .type = "float",
            .precision = RLSL_AST_PRECISION_NONE,
            .component_count = 1,
            .start = rlsl_cursor_at_position(source, 1, 15),
            .end = rlsl_cursor_at_position(source, 1, 25),
        }
    };

    rlsl_ast_struct_t structs[] = {
        (rlsl_ast_struct_t) {
            .name = "test",
            .member_count = 1,
            .members = members,
            .start = rlsl_cursor_at_position(source, 1, 8),
            .end = rlsl_cursor_at_position(source, 1, 12),
        },
    };
    
    rlsl_ast_module_t expected = { 0 };
    expected.struct_count = 1;
    expected.structs = structs;

    return expect_ast(source, &expected);
}

bool test_ast_struct_float_lowp() {
    const char* source = "struct test { lowp float var; };";

    rlsl_ast_member_t members[] = {
        (rlsl_ast_member_t) {
            .name = "var",
            .type = "float",
            .precision = RLSL_AST_PRECISION_LOWP,
            .component_count = 1,
            .start = rlsl_cursor_at_position(source, 1, 15),
            .end = rlsl_cursor_at_position(source, 1, 30),
        }
    };

    rlsl_ast_struct_t structs[] = {
        (rlsl_ast_struct_t) {
            .name = "test",
            .member_count = 1,
            .members = members,
            .start = rlsl_cursor_at_position(source, 1, 8),
            .end = rlsl_cursor_at_position(source, 1, 12),
        },
    };
    
    rlsl_ast_module_t expected = { 0 };
    expected.struct_count = 1;
    expected.structs = structs;

    return expect_ast(source, &expected);
}

bool test_ast_struct_float_mediump() {
    const char* source = "struct test { mediump float var; };";

    rlsl_ast_member_t members[] = {
        (rlsl_ast_member_t) {
            .name = "var",
            .type = "float",
            .precision = RLSL_AST_PRECISION_MEDIUMP,
            .component_count = 1,
            .start = rlsl_cursor_at_position(source, 1, 15),
            .end = rlsl_cursor_at_position(source, 1, 33),
        }
    };

    rlsl_ast_struct_t structs[] = {
        (rlsl_ast_struct_t) {
            .name = "test",
            .member_count = 1,
            .members = members,
            .start = rlsl_cursor_at_position(source, 1, 8),
            .end = rlsl_cursor_at_position(source, 1, 12),
        },
    };
    
    rlsl_ast_module_t expected = { 0 };
    expected.struct_count = 1;
    expected.structs = structs;

    return expect_ast(source, &expected);
}

bool test_ast_struct_float_highp() {
    const char* source = "struct test { highp float var; };";

    rlsl_ast_member_t members[] = {
        (rlsl_ast_member_t) {
            .name = "var",
            .type = "float",
            .precision = RLSL_AST_PRECISION_HIGHP,
            .component_count = 1,
            .start = rlsl_cursor_at_position(source, 1, 15),
            .end = rlsl_cursor_at_position(source, 1, 31),
        }
    };

    rlsl_ast_struct_t structs[] = {
        (rlsl_ast_struct_t) {
            .name = "test",
            .member_count = 1,
            .members = members,
            .start = rlsl_cursor_at_position(source, 1, 8),
            .end = rlsl_cursor_at_position(source, 1, 12),
        },
    };
    
    rlsl_ast_module_t expected = { 0 };
    expected.struct_count = 1;
    expected.structs = structs;

    return expect_ast(source, &expected);
}
