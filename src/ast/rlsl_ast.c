#include <string.h>
#include "tools/rlsl_vec.h"
#include "tools/rlsl_str.h"
#include "token/rlsl_token_stream.h"
#include "rlsl_ast.h"
#include "rlsl_ast_struct.h"
#include "rlsl_ast_uniform.h"
#include "rlsl_ast_io.h"

rlsl_ast_module_t rlsl_ast_parse_tokens(rlsl_token_t* tokens, size_t token_count) {
    rlsl_token_stream_t ts = rlsl_token_stream_create(tokens, token_count);
    rlsl_ast_module_t ast_module;
    memset(&ast_module, 0, sizeof(rlsl_ast_module_t));

    if(ts.token_count == 0) {
        return ast_module;
    }

    ast_module.last_cursor_start = ts.tokens[0].cursor_start;
    ast_module.last_cursor_end = ts.tokens[0].cursor_end;

    while(true) {
        if(rlsl_token_stream_is_at_end(&ts)) {
            break;
        }

        rlsl_token_t* first_token = rlsl_ast_token_expect_any_of(&ts, top_level_tokens, &ast_module);
        if(!first_token) {
            break;
        }

        switch(first_token->type) {
            case RLSL_TOKEN_KEYWORD_STRUCT: {
                rlsl_ast_struct_t s;
                if(rlsl_ast_struct_parse(&ts, &s, &ast_module)) {
                    rlsl_vec_push(ast_module.structs, s);
                }
                continue;
            }
            case RLSL_TOKEN_KEYWORD_UNIFORM: {
                rlsl_ast_uniform_t u;
                if(rlsl_ast_uniform_parse(&ts, &u, &ast_module)) {
                    rlsl_vec_push(ast_module.uniforms, u);
                }
                continue;
            }
            case RLSL_TOKEN_KEYWORD_INPUT: {
                rlsl_ast_io_t io;
                if(rlsl_ast_io_parse(&ts, RLSL_AST_IO_INPUT, &io, &ast_module)) {
                    rlsl_vec_push(ast_module.inputs, io);
                }
                continue;
            }
            case RLSL_TOKEN_KEYWORD_OUTPUT: {
                rlsl_ast_io_t io;
                if(rlsl_ast_io_parse(&ts, RLSL_AST_IO_OUTPUT, &io, &ast_module)) {
                    rlsl_vec_push(ast_module.outputs, io);
                }
                continue;
            }
            default:
                //error
                continue;
        }
    }

    #define X(NAME, TYPE) ast_module.NAME##_count = rlsl_vec_size(ast_module.NAME##s);
    RLSL_AST_MODULE_PARTS(X)
    #undef X

    ast_module.error_count = rlsl_vec_size(ast_module.errors);
    return ast_module;
}

#include <stdio.h>
bool rlsl_ast_module_equal(const rlsl_ast_module_t* a, const rlsl_ast_module_t* b) {
    #define X(NAME, TYPE) if(a->NAME##_count != b->NAME##_count) { \
        return false; \
    } \
    for(int64_t i = 0; i < a->NAME##_count; i++) { \
        if(!TYPE##_equal(&a->NAME##s[i], &b->NAME##s[i])) { \
            return false; \
        } \
    }
    
    RLSL_AST_MODULE_PARTS(X)
    #undef X

    return true;
}

void rlsl_ast_module_free(rlsl_ast_module_t* m) {
    if(!m) {
        return;
    }

    #define X(NAME, TYPE) for(int64_t i = 0; i < rlsl_vec_size(m->NAME##s); i++) { \
        TYPE##_free(&(m->NAME##s)[i]); \
    } \
    rlsl_vec_free(m->NAME##s); \
    m->NAME##s = NULL;
    RLSL_AST_MODULE_PARTS(X)
    #undef X

    for(int64_t i = 0; i < rlsl_vec_size(m->errors); i++) {
        rlsl_error_free(&m->errors[i]);
    }
    rlsl_vec_free(m->errors);
}

/*
    error emitting helper functions
*/

rlsl_token_t* rlsl_ast_token_expect(rlsl_token_stream_t* ts, rlsl_token_type_t expected_token, rlsl_ast_module_t* m) {
    rlsl_token_t* token = rlsl_token_stream_advance(ts);
    if(!token) {
        rlsl_vec_push(m->errors, rlsl_error_create(RLSL_ERROR_END_OF_TOKEN_STREAM, &m->last_cursor_start, &m->last_cursor_end));
        return NULL;
    }
    if(token->type != expected_token) {
        rlsl_error_t error = rlsl_error_createf(
            RLSL_ERROR_EXPECTED_TOKEN,
            token->cursor_start,
            token->cursor_end,
            "expected token \"%s\" but got \"%s\"",
            rlsl_token_type_to_string(expected_token),
            rlsl_token_type_to_string(token->type)
        );
        rlsl_vec_push(m->errors, error);
        return NULL;
    }

    //success
    m->last_cursor_start = token->cursor_start;
    m->last_cursor_end = token->cursor_end;
    return token;
}

bool rlsl_ast_token_ensure(rlsl_token_t* token, rlsl_token_type_t expected_token, rlsl_ast_module_t* m) {
    if(!token) {
        rlsl_vec_push(m->errors, rlsl_error_create(RLSL_ERROR_END_OF_TOKEN_STREAM, &m->last_cursor_start, &m->last_cursor_end));
        return false;
    }
    if(token->type != expected_token) {
        rlsl_error_t error = rlsl_error_createf(
            RLSL_ERROR_EXPECTED_TOKEN,
            token->cursor_start,
            token->cursor_end,
            "expected token \"%s\" but got \"%s\"",
            rlsl_token_type_to_string(expected_token),
            rlsl_token_type_to_string(token->type)
        );
        rlsl_vec_push(m->errors, error);
        return false;
    }

    //success
    m->last_cursor_start = token->cursor_start;
    m->last_cursor_end = token->cursor_end;
    return true;
}

rlsl_token_t* _rlsl_ast_token_expect_any_of(rlsl_token_stream_t* ts, const rlsl_token_type_t* expected_tokens, int64_t expected_token_count, rlsl_ast_module_t* m) {
    rlsl_token_t* token = rlsl_token_stream_advance(ts);
    if(!token) {
        rlsl_vec_push(m->errors, rlsl_error_create(RLSL_ERROR_END_OF_TOKEN_STREAM, &m->last_cursor_start, &m->last_cursor_end));
        return NULL;
    }

    bool found = false;
    for(int64_t i = 0; i < expected_token_count; i++) {
        rlsl_token_type_t type = expected_tokens[i];
        if(type == token->type) {
            found = true;
            break;
        }
    }/*
    helper functions that don't emit errors
*/

    if(found) {
        m->last_cursor_start = token->cursor_start;
        m->last_cursor_end = token->cursor_end;
        return token;
    }

    rlsl_error_t error = rlsl_error_create_from_expected_tokens(token->cursor_start, token->cursor_end, token->type, expected_tokens, expected_token_count);
    rlsl_vec_push(m->errors, error);
    return NULL;
}

bool _rlsl_ast_token_ensure_any_of(rlsl_token_t* token, const rlsl_token_type_t* expected_tokens, int64_t expected_token_count, rlsl_ast_module_t* m) {
    if(expected_token_count == 1) {
        return rlsl_ast_token_ensure(token, expected_tokens[0], m);
    }

    if(!token) {
        rlsl_vec_push(m->errors, rlsl_error_create(RLSL_ERROR_END_OF_TOKEN_STREAM, &m->last_cursor_start, &m->last_cursor_end));
        return false;
    }

    bool found = false;
    for(int64_t i = 0; i < expected_token_count; i++) {
        rlsl_token_type_t type = expected_tokens[i];
        if(type == token->type) {
            found = true;
            break;
        }
    }

    if(found) {
        m->last_cursor_start = token->cursor_start;
        m->last_cursor_end = token->cursor_end;
        return true;
    }

    rlsl_error_t error = rlsl_error_create_from_expected_tokens(token->cursor_start, token->cursor_end, token->type, expected_tokens, expected_token_count);
    rlsl_vec_push(m->errors, error);
    return false;
}

/*
    helper functions that don't emit errors
*/

bool rlsl_ast_token_otional_check(rlsl_token_t* token, rlsl_token_type_t expected_token) {
    if(!token) {
        return false;
    }
    return token->type == expected_token;
}

bool rlsl_ast_token_next_is(rlsl_token_stream_t* ts, rlsl_token_type_t token) {
    rlsl_token_t* next = rlsl_token_stream_peek(ts, 1);
    if(!next) {
        return false;
    }
    return next->type == token;
}