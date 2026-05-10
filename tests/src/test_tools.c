#include <math.h>
#include <string.h>
#include <rlsl_token.h>
#include "test_tools.h"

bool expect_token(const char* source, const expect_token_t expect) {
    const expect_token_t expects[1] = { expect };
    return _expect_tokens(source, expects, 1);
}

bool _expect_tokens(const char* source, const expect_token_t* expects, size_t expects_length) {
    rlsl_tokenizer_result_t* res = rlsl_token_tokenize_string(source, NULL);
    if(res->token_count != expects_length) {
        goto fail;
    }

    if(res->error_count > 0) {
        goto fail;
    }

    for(size_t i = 0; i < expects_length; i++) {
        rlsl_token_t token = res->tokens[i];
        expect_token_t expect = expects[i];

        if(expect.type != token.type) {
            goto fail;
        }
        if(expect.type == RLSL_TOKEN_LITERAL_INT || expect.type == RLSL_TOKEN_LITERAL_FLOAT || expect.type == RLSL_TOKEN_LITERAL_IDENTIFIER) {
            switch(expect.type) {
                case RLSL_TOKEN_LITERAL_INT: {
                    if(expect.value.i != token.value.num_int.value) {
                        goto fail;
                    }
                    break;
                }
                case RLSL_TOKEN_LITERAL_FLOAT: {
                    const long double epsilon = 0.000001L;
                    if(fabsl(expect.value.d - token.value.num_float.value) > epsilon) {
                        goto fail;
                    }
                    break;
                }
                case RLSL_TOKEN_LITERAL_IDENTIFIER: {
                    if(strncmp(expect.value.s, token.value.identifier, strlen(expect.value.s)) != 0) {
                        goto fail;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    rlsl_tokenizer_result_free(res);
    return true;
fail:
    rlsl_tokenizer_result_free(res);
    return false;
}

bool expect_error(const char* source, const rlsl_error_enum_t error, uint64_t start_line, uint64_t start_column, uint64_t end_line, uint64_t end_column) {
    rlsl_tokenizer_result_t* res = rlsl_token_tokenize_string(source, NULL);
    if(res->token_count > 0) {
        goto fail;
    }

    if(res->error_count != 1) {
        goto fail;
    }

    rlsl_error_t err = res->errors[0];
    bool success = err.code == error && err.start.line == start_line && err.start.column == start_column && err.end.line == end_line && err.end.column == end_column;
    if(success) {
        rlsl_tokenizer_result_free(res);
        return true;
    }
fail:
    rlsl_tokenizer_result_free(res);
    return false;
}