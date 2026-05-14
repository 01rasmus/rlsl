#pragma once
#include <stdbool.h>
#include "rlsl_cursor.h"
#include "rlsl_token.h"

typedef struct rlsl_token_stream_t rlsl_token_stream_t;

typedef enum rlsl_ast_precision_t {
    RLSL_AST_PRECISION_NONE,
    RLSL_AST_PRECISION_LOWP,
    RLSL_AST_PRECISION_MEDIUMP,
    RLSL_AST_PRECISION_HIGHP,
} rlsl_ast_precision_t;

typedef struct rlsl_ast_struct_member_t {
    char* name;
    char* type;
    rlsl_ast_precision_t precision;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_ast_struct_member_t;

typedef struct rlsl_ast_struct_t {
    char* name;
    size_t member_count;
    rlsl_ast_struct_member_t* members;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_ast_struct_t;

typedef struct rlsl_ast_module_t {
    size_t struct_count;
    rlsl_ast_struct_t* structs;

    size_t error_count;
    rlsl_error_t* errors;
} rlsl_ast_module_t;

rlsl_ast_module_t rlsl_ast_parse_tokens(rlsl_token_t* tokens, size_t token_count);
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

bool rlsl_ast_struct_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_t* out_struct);
bool rlsl_ast_struct_member_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_member_t* out_struct_member);

void rlsl_ast_module_free(rlsl_ast_module_t* m);
void rlsl_ast_struct_free(rlsl_ast_struct_t* s);
void rlsl_ast_struct_member_free(rlsl_ast_struct_member_t* sm);