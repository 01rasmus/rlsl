#include <string.h>
#include <token/rlsl_token.h>
#include <ast/rlsl_ast.h>
#include "test_tools.h"

#include <stdio.h>

bool test_ast_struct() {
    rlsl_tokenizer_result_t* res = rlsl_token_tokenize_string("struct test { float test; float test2; highp float test3; }; struct test2 { };", NULL);
    rlsl_ast_module_t ast = rlsl_ast_parse_tokens(res->tokens, res->token_count);

    printf("ast: %d\n", ast.struct_count);

    rlsl_tokenizer_result_free(res);
    rlsl_ast_module_free(&ast);
    return false;
}
