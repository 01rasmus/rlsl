#pragma once
#include <stdbool.h>
#include "rlsl_cursor.h"
#include "rlsl_token.h"

bool rlsl_token_tokenizer_parse_single_char_token(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier);