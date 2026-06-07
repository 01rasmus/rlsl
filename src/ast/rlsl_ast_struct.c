#include <stdlib.h>
#include <string.h>
#include "tools/rlsl_str.h"
#include "tools/rlsl_vec.h"
#include "token/rlsl_token.h"
#include "rlsl_ast_struct.h"
#include "rlsl_ast.h"

bool rlsl_ast_struct_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_t* out_struct, rlsl_ast_module_t* m) {
    memset(out_struct, 0, sizeof(rlsl_ast_struct_t));

    rlsl_token_t* struct_name = rlsl_ast_token_expect(ts, RLSL_TOKEN_LITERAL_IDENTIFIER, m);
    if(!struct_name) {
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

bool rlsl_ast_struct_equal(const rlsl_ast_struct_t* a, const rlsl_ast_struct_t* b) {
    if(a->member_count != b->member_count) {
        return false;
    }
    if(strcmp(a->name, b->name) != 0) {
        return false;
    }
    for(size_t i = 0; i < a->member_count; i++) {
        if(!rlsl_ast_member_equal(&a->members[i], &b->members[i])) {
            return false;
        }
    }
    if(rlsl_cursor_compare(&a->start, &b->start) != 0) {
        return false;
    }
    if(rlsl_cursor_compare(&a->end, &b->end) != 0) {
        return false;
    }
    return true;
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