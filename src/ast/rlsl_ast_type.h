#pragma once
#include <stdbool.h>
#include "token/rlsl_token_stream.h"
#include "rlsl_cursor.h"

typedef struct rlsl_ast_module_t rlsl_ast_module_t;

typedef enum rlsl_ast_precision_t {
    RLSL_AST_PRECISION_NONE = 0,
    RLSL_AST_PRECISION_LOWP,
    RLSL_AST_PRECISION_MEDIUMP,
    RLSL_AST_PRECISION_HIGHP,
} rlsl_ast_precision_t;

typedef struct rlsl_ast_type_t {
    rlsl_cursor_t start;
    rlsl_cursor_t end;
    char* type;
    rlsl_ast_precision_t precision;
    bool is_const;
} rlsl_ast_type_t;

/*
    this parse function does not recover on failure
    (which is fine since its always inside another parse function)
*/
bool rlsl_ast_type_parse(rlsl_token_stream_t* ts, rlsl_ast_type_t* out_type, rlsl_ast_module_t* m);
bool rlsl_ast_type_equal(const rlsl_ast_type_t* a, const rlsl_ast_type_t* b);
void rlsl_ast_type_free(rlsl_ast_type_t* t);