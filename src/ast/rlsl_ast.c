#include <string.h>
#include "tools/rlsl_vec.h"
#include "tools/rlsl_str.h"
#include "rlsl_token_stream.h"
#include "rlsl_ast.h"
#include "rlsl_ast_struct.h"

rlsl_ast_module_t rlsl_ast_parse_tokens(rlsl_token_t* tokens, size_t token_count) {
    rlsl_token_stream_t ts = rlsl_token_stream_create(tokens, token_count);
    rlsl_ast_module_t ast_module;
    memset(&ast_module, 0, sizeof(rlsl_ast_module_t));

    while(true) {
        rlsl_token_t* first_token = rlsl_token_stream_advance(&ts);
        if(!first_token) {
            break;
        }

        switch(first_token->type) {
            case RLSL_TOKEN_KEYWORD_STRUCT: {
                rlsl_ast_struct_t s;
                if(rlsl_ast_struct_parse(&ts, &s)) {
                    rlsl_vec_push(ast_module.structs, s);
                }
                continue;
            }

            default:
                //error
                continue;
        }
    }

    ast_module.struct_count = rlsl_vec_size(ast_module.structs);
    ast_module.error_count = rlsl_vec_size(ast_module.errors);
    return ast_module;
}

void rlsl_ast_module_free(rlsl_ast_module_t* m) {
    if(!m) {
        return;
    }
    for(size_t i = 0; i < m->struct_count; i++) {
        rlsl_ast_struct_free(&m->structs[i]);
    }

    rlsl_vec_free(m->structs);
    rlsl_vec_free(m->errors);
}

/*
    helper functions
*/

rlsl_token_t* rlsl_ast_token_expect(rlsl_token_stream_t* ts, rlsl_token_type_t expected_token) {
    rlsl_token_t* token = rlsl_token_stream_advance(ts);
    if(!token) {
        return NULL;
    }
    if(token->type != expected_token) {
        return NULL;
    }
    return token;
}

bool rlsl_ast_token_next_is(rlsl_token_stream_t* ts, rlsl_token_type_t token) {
    rlsl_token_t* next = rlsl_token_stream_peek(ts, 1);
    if(!next) {
        return false;
    }
    return next->type == token;
}

bool rlsl_ast_token_ensure(rlsl_token_t* token, rlsl_token_type_t expected_token) {
    if(!token) {
        return false;
    }
    return token->type == expected_token;
}

bool rlsl_ast_token_otional_check(rlsl_token_t* token, rlsl_token_type_t expected_token) {
    if(!token) {
        return false;
    }
    return token->type == expected_token;
}