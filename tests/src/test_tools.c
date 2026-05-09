#include <math.h>
#include <string.h>
#include <rlsl_token.h>
#include "test_tools.h"

bool expect_token(const char* source, const expect_token_t expect) {
    const expect_token_t expects[1] = { expect };
    return _expect_tokens(source, expects, 1);
}

bool _expect_tokens(const char* source, const expect_token_t* expects, size_t expects_length) {
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    if(res.token_count != expects_length) {
        return false;
    }

    if(res.error_count > 0) {
        return false;
    }

    for(size_t i = 0; i < expects_length; i++) {
        rlsl_token_t token = res.tokens[i];
        expect_token_t expect = expects[i];

        if(expect.type != token.type) {
            return false;
        }
        if(expect.type == RLSL_TOKEN_LITERAL_INT || expect.type == RLSL_TOKEN_LITERAL_FLOAT || expect.type == RLSL_TOKEN_LITERAL_IDENTIFIER) {
            switch(expect.type) {
                case RLSL_TOKEN_LITERAL_INT: {
                    if(expect.value.i != token.value.num_int.value) {
                        return false;
                    }
                    break;
                }
                case RLSL_TOKEN_LITERAL_FLOAT: {
                    const long double epsilon = 0.000001L;
                    if(fabsl(expect.value.d - token.value.num_float.value) > epsilon) {
                        return false;
                    }
                    break;
                }
                case RLSL_TOKEN_LITERAL_IDENTIFIER: {
                    if(strncmp(expect.value.s, token.value.identifier, strlen(expect.value.s)) != 0) {
                        return false;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    return true;
}

bool expect_error(const char* source, const rlsl_error_enum_t error, uint64_t start_line, uint64_t start_column, uint64_t end_line, uint64_t end_column) {
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    if(res.token_count > 0) {
        return false;
    }

    if(res.error_count != 1) {
        return false;
    }

    rlsl_error_t err = res.errors[0];
    return err.code == error && err.start.line == start_line && err.start.column == start_column && err.end.line == end_line && err.end.column == end_column;
}