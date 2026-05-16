#pragma once
#include <stdbool.h>
#include "rlsl_cursor.h"
#include "rlsl_token.h"
#include "rlsl_ast_struct.h"

typedef struct rlsl_token_stream_t rlsl_token_stream_t;

typedef struct rlsl_ast_module_t {
    size_t struct_count;
    rlsl_ast_struct_t* structs;

    size_t error_count;
    rlsl_error_t* errors;
} rlsl_ast_module_t;

rlsl_ast_module_t rlsl_ast_parse_tokens(rlsl_token_t* tokens, size_t token_count);
void rlsl_ast_module_free(rlsl_ast_module_t* m);

/*
    helper functions
*/
rlsl_token_t* rlsl_ast_token_expect(rlsl_token_stream_t* ts, rlsl_token_type_t expected_token);
bool rlsl_ast_token_next_is(rlsl_token_stream_t* ts, rlsl_token_type_t token);

/*
    this function creates an error on fail
*/
bool rlsl_ast_token_ensure(rlsl_token_t* token, rlsl_token_type_t expected_token);

/*
    this function does not create an error
    on fail, since the value is supposed
    to be optional
*/
bool rlsl_ast_token_otional_check(rlsl_token_t* token, rlsl_token_type_t expected_token);