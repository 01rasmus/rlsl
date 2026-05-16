#pragma once
#include <stdbool.h>
#include "token/rlsl_token_stream.h"
#include "rlsl_cursor.h"
#include "rlsl_ast_member.h"

typedef struct rlsl_ast_module_t rlsl_ast_module_t;

typedef struct rlsl_ast_struct_t {
    char* name;
    size_t member_count;
    rlsl_ast_member_t* members;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_ast_struct_t;

bool rlsl_ast_struct_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_t* out_struct, rlsl_ast_module_t* m);
void rlsl_ast_struct_free(rlsl_ast_struct_t* s);