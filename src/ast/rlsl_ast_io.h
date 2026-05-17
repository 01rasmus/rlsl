#pragma once
#include <stdbool.h>
#include "token/rlsl_token_stream.h"
#include "rlsl_ast_member.h"
#include "rlsl_cursor.h"

typedef struct rlsl_ast_module_t rlsl_ast_module_t;

typedef enum rlsl_ast_io_type_t {
    RLSL_AST_IO_INPUT,
    RLSL_AST_IO_OUTPUT,
} rlsl_ast_io_type_t;

typedef struct rlsl_ast_io_t {
    rlsl_ast_io_type_t type;
    uint64_t index;
    rlsl_ast_member_t member;
    rlsl_cursor_t start;
    rlsl_cursor_t end;
} rlsl_ast_io_t;

bool rlsl_ast_io_parse(rlsl_token_stream_t* ts, rlsl_ast_io_type_t type, rlsl_ast_io_t* out_io, rlsl_ast_module_t* m);
void rlsl_ast_io_free(rlsl_ast_io_t* io);