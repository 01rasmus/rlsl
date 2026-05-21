#pragma once
#include <stdbool.h>
#include "token/rlsl_token_stream.h"
#include "rlsl_cursor.h"

typedef struct rlsl_ast_module_t rlsl_ast_module_t;

typedef enum rlsl_ast_precision_t {
    RLSL_AST_PRECISION_NONE,
    RLSL_AST_PRECISION_LOWP,
    RLSL_AST_PRECISION_MEDIUMP,
    RLSL_AST_PRECISION_HIGHP,
} rlsl_ast_precision_t;

typedef struct rlsl_ast_member_t {
    char* name;
    char* type;
    uint64_t component_count; // if this is more than 1, it is an array
    rlsl_ast_precision_t precision;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_ast_member_t;

bool rlsl_ast_member_parse(rlsl_token_stream_t* ts, rlsl_ast_member_t* out_member, rlsl_ast_module_t* m);
bool rlsl_ast_member_array_count_parse(rlsl_token_stream_t* ts, uint64_t* out_comp_count, rlsl_ast_module_t* m);
bool rlsl_ast_member_equal(const rlsl_ast_member_t* a, const rlsl_ast_member_t* b);
void rlsl_ast_member_free(rlsl_ast_member_t* sm);