#include <stdlib.h>
#include <string.h>
#include "tools/rlsl_str.h"
#include "tools/rlsl_vec.h"
#include "token/rlsl_token.h"
#include "rlsl_ast_struct.h"
#include "rlsl_ast.h"

bool rlsl_ast_struct_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_t* out_struct, rlsl_ast_module_t* m) {
    memset(out_struct, 0, sizeof(rlsl_ast_struct_t));

    rlsl_token_t* struct_name = rlsl_token_stream_advance(ts);
    if(!rlsl_ast_token_ensure(struct_name, RLSL_TOKEN_LITERAL_IDENTIFIER, m)) {
        goto err;
    }
    out_struct->name = rlsl_str_cpy(struct_name->value.identifier);

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED, m)) {
        goto err;
    }

    while(true) {
        if(rlsl_ast_token_next_is(ts, RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED)) {
            break;
        }

        rlsl_ast_member_t struct_member;
        if(rlsl_ast_member_parse(ts, &struct_member, m)) {
            rlsl_vec_push(out_struct->members, struct_member);
        }
    }

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED, m)) {
        goto err;
    }
    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_SEMICOLON, m)) {
        goto err;
    }
    out_struct->member_count = rlsl_vec_size(out_struct->members);
    out_struct->start = struct_name->cursor_start;
    out_struct->end = struct_name->cursor_end;
    return true;
err:
    rlsl_token_stream_recover_top_level(ts);
    rlsl_ast_struct_free(out_struct);
    return false;
}

void rlsl_ast_struct_free(rlsl_ast_struct_t* s) {
    if(!s) {
        return;
    }
    for(size_t i = 0; i < s->member_count; i++) {
        rlsl_ast_member_free(&s->members[i]);
    }

    rlsl_vec_free(s->members);
    free(s->name);
}