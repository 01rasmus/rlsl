#pragma once
#include <stdbool.h>
#include "rlsl_cursor.h"
#include "rlsl_token_stream.h"

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

bool rlsl_ast_struct_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_t* out_struct);
bool rlsl_ast_struct_member_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_member_t* out_struct_member);

void rlsl_ast_struct_free(rlsl_ast_struct_t* s);
void rlsl_ast_struct_member_free(rlsl_ast_struct_member_t* sm);