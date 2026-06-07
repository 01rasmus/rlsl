#include <string.h>
#include <token/rlsl_token.h>
#include <ast/rlsl_ast.h>
#include "test_tools.h"

bool tests_ast_recovery_invalid_var_declaration_in_multiple_structs() {
    rlsl_ast_module_t ast = {0};
    const char* source = "struct Test { float a = 0; };\nstruct Light { float a; };\nstruct Test2 { float a; 1234 };\nstruct Light2 { vec3 pos; };";

    const rlsl_error_t errors[] = {
        EXPECT_ERROR(RLSL_ERROR_EXPECTED_TOKEN, rlsl_cursor_at_position(source, 1, 23), rlsl_cursor_at_position(source, 1, 24), false),
        EXPECT_ERROR(RLSL_ERROR_EXPECTED_TOKEN, rlsl_cursor_at_position(source, 3, 25), rlsl_cursor_at_position(source, 3, 29), false),
    };
    bool expect_errors = expect_ast_errors(source, errors);

    if(!ast_get(source, &ast)) {
        goto err;
    }

    if(ast.struct_count != 4) {
        goto err;
    }
    if(strcmp(ast.structs[0].name, "Test") != 0) {
        goto err;
    }
    if(strcmp(ast.structs[1].name, "Light") != 0) {
        goto err;
    }
    if(strcmp(ast.structs[2].name, "Test2") != 0) {
        goto err;
    }
    if(strcmp(ast.structs[3].name, "Light2") != 0) {
        goto err;
    }
    
    rlsl_ast_module_free(&ast);
    return expect_errors;
err:
    rlsl_ast_module_free(&ast);
    return false;
}

bool test_ast_recovery_ensure_valid_vars_stay_even_with_invalid_var_declarations() {
    rlsl_ast_module_t ast = {0};
    const char* source = "struct Test { float a;\nfloat b = 0;\nfloat c; };";

    const rlsl_error_t errors[] = {
        EXPECT_ERROR(RLSL_ERROR_EXPECTED_TOKEN, rlsl_cursor_at_position(source, 2, 9), rlsl_cursor_at_position(source, 2, 10), false),
    };
    bool expect_errors = expect_ast_errors(source, errors);

    if(!ast_get(source, &ast)) {
        goto err;
    }

    //ensure that the struct Test exist
    if(ast.struct_count != 1) {
        goto err;
    }

    rlsl_ast_struct_t strct = ast.structs[0];
    if(strcmp(strct.name, "Test") != 0) {
        goto err;
    }

    //ensure that it has two variables
    if(strct.member_count != 2) {
        return false;
    }
    if(strcmp(strct.members[0].name, "a") != 0) {
        return false;
    }
    if(strcmp(strct.members[0].type.type, "float") != 0) {
        return false;
    }
    if(strcmp(strct.members[1].name, "c") != 0) {
        return false;
    }
    if(strcmp(strct.members[1].type.type, "float") != 0) {
        return false;
    }
    
    rlsl_ast_module_free(&ast);
    return expect_errors;
err:
    rlsl_ast_module_free(&ast);
    return false;
}