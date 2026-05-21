#pragma once
#include <stdbool.h>
#include "token/rlsl_token_stream.h"
#include "rlsl_cursor.h"
#include "rlsl_ast_member.h"

typedef struct rlsl_ast_module_t rlsl_ast_module_t;

typedef struct rlsl_ast_uniform_t {
    char* name;
    size_t uniform_index;
    size_t member_count;
    rlsl_ast_member_t* members;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_ast_uniform_t;

bool rlsl_ast_uniform_parse(rlsl_token_stream_t* ts, rlsl_ast_uniform_t* out_uniform, rlsl_ast_module_t* m);
bool rlsl_ast_uniform_equal(const rlsl_ast_uniform_t* a, const rlsl_ast_uniform_t* b);
void rlsl_ast_uniform_free(rlsl_ast_uniform_t* s);