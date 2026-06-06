#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <token/rlsl_token.h>
#include <ast/rlsl_ast.h>

int32_t main(int32_t argc, char** args) {

    //load file
    if(argc != 2) {
        return 0;
    }
    FILE* file = fopen(args[1], "rb");
    int64_t length = 0;
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(length + 1);
    if(!buffer) {
        return 0;
    }
    fread(buffer, 1, length, file);
    fclose(file);
    file = NULL;
    buffer[length] = '\0';

    //transpile
    rlsl_tokenizer_result_t* res = rlsl_token_tokenize_string(buffer, args[1]);
    if(res->error_count > 0) {
        for(int64_t i = 0; i < res->error_count; i++) {
            rlsl_error_print(&res->errors[i], buffer, args[1], RLSL_ERROR_OUTPUT_TYPE_NORMAL, NULL);
        }
        return 1;
    }

    rlsl_ast_module_t module_ast = rlsl_ast_parse_tokens(res->tokens, res->token_count);
    if(module_ast.error_count > 0) {
        for(int64_t i = 0; i < module_ast.error_count; i++) {
            rlsl_error_print(&module_ast.errors[i], buffer, args[1], RLSL_ERROR_OUTPUT_TYPE_NORMAL, NULL);
        }
        return 1;
    }

    return 0;
}