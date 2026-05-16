#pragma once
#include <stdbool.h>
#include "token/rlsl_token.h"
#include "rlsl_cursor.h"
#include "rlsl_ast_struct.h"
#include "rlsl_ast_uniform.h"

typedef struct rlsl_token_stream_t rlsl_token_stream_t;

typedef struct rlsl_ast_module_t {
    size_t struct_count;
    rlsl_ast_struct_t* structs;

    size_t uniform_count;
    rlsl_ast_uniform_t* uniforms;

    rlsl_cursor_t last_cursor_start;
    rlsl_cursor_t last_cursor_end;

    size_t error_count;
    rlsl_error_t* errors;
} rlsl_ast_module_t;

rlsl_ast_module_t rlsl_ast_parse_tokens(rlsl_token_t* tokens, size_t token_count);
void rlsl_ast_module_free(rlsl_ast_module_t* m);

/*
    helper functions that create errors on failure
*/
#define rlsl_ast_token_expect_any_of(TS, EXPECTED_TOKENS, M) \
    _rlsl_ast_token_expect_any_of(TS, EXPECTED_TOKENS, sizeof(EXPECTED_TOKENS) / sizeof(EXPECTED_TOKENS[0]), M)
#define rlsl_ast_token_ensure_any_of(TOK, EXPECTED_TOKENS, M) \
    _rlsl_ast_token_ensure_any_of(TOK, sizeof(EXPECTED_TOKENS) / sizeof(EXPECTED_TOKENS[0]), M)

rlsl_token_t* rlsl_ast_token_expect(rlsl_token_stream_t* ts, rlsl_token_type_t expected_token, rlsl_ast_module_t* m);
bool rlsl_ast_token_ensure(rlsl_token_t* token, rlsl_token_type_t expected_token, rlsl_ast_module_t* m);
rlsl_token_t* _rlsl_ast_token_expect_any_of(rlsl_token_stream_t* ts, const rlsl_token_type_t* expected_tokens, int64_t expected_token_count, rlsl_ast_module_t* m);
bool _rlsl_ast_token_ensure_any_of(rlsl_token_t* token, const rlsl_token_type_t* expected_tokens, int64_t expected_token_count, rlsl_ast_module_t* m);

/*
    helper functions that does not create errors
*/
bool rlsl_ast_token_next_is(rlsl_token_stream_t* ts, rlsl_token_type_t token);
bool rlsl_ast_token_otional_check(rlsl_token_t* token, rlsl_token_type_t expected_token);