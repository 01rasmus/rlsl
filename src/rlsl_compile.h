/*
    RL Render Shader Language
*/
#pragma once
#include <stddef.h>
#include "rlsl_ast.h"

rlsl_ast_node_t* rlsl_compile(const char* source, char* out_errors, size_t* out_error_count, size_t out_errors_size);