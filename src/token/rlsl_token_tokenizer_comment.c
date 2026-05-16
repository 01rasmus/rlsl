#include <string.h>
#include "tools/rlsl_vec.h"
#include "rlsl_token_tokenizer_comment.h"

bool rlsl_token_tokenizer_parse_comment(rlsl_cursor_t* cursor, rlsl_tokenizer_result_t* res, const char* source, const char* compile_unit_identifier) {
    const char* str = source + cursor->index;
    const char* end = NULL;
    bool is_comment = false;
    if(strncmp(str, "//", 2) == 0) {
        end = strpbrk(str, "\n");
        if(end) {
            end++; //include the breakline character
        }
        is_comment = true;
    } else if(strncmp(source + cursor->index, "/*", 2) == 0) {
        end = strstr(str, "*/");
        if(end) {
            end += 2; //include the end */ character
        }

        is_comment = true;
    }

    if(!is_comment) {
        return false;
    }

    if(!end) {
        end = strchr(str, '\0'); //the same as "str + strlen(str)"
    }
    ptrdiff_t diff = end - str;

    rlsl_cursor_t cur_start = (*cursor);
    rlsl_cursor_advance(cursor, source, diff);
    rlsl_vec_push(res->tokens, rlsl_token_create_static(RLSL_TOKEN_SYMBOL_COMMENT, cur_start, (*cursor)));
    return true;
}