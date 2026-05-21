#include <stdlib.h>
#include <string.h>
#include "tools/rlsl_vec.h"
#include "tools/rlsl_str.h"
#include "token/rlsl_token.h"
#include "rlsl_ast_uniform.h"
#include "rlsl_ast.h"

bool rlsl_ast_uniform_parse(rlsl_token_stream_t* ts, rlsl_ast_uniform_t* out_uniform, rlsl_ast_module_t* m) {
    memset(out_uniform, 0, sizeof(rlsl_ast_uniform_t));

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED, m)) {
        goto err;
    }
    rlsl_token_t* uniform_index_token = rlsl_ast_token_expect(ts, RLSL_TOKEN_LITERAL_INT, m);
    if(!uniform_index_token) {
        goto err;
    }
    out_uniform->uniform_index = uniform_index_token->value.num_int.value;
    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED, m)) {
        goto err;
    }
    rlsl_token_t* uniform_name_token = rlsl_ast_token_expect(ts, RLSL_TOKEN_LITERAL_IDENTIFIER, m);
    if(!uniform_name_token) {
        goto err;
    }
    out_uniform->name = rlsl_str_cpy(uniform_name_token->value.identifier);

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED, m)) {
        goto err;
    }

    while(true) {
        if(rlsl_ast_token_next_is(ts, RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED)) {
            break;
        }

        rlsl_ast_member_t member;
        if(rlsl_ast_member_parse(ts, &member, m)) {
            rlsl_vec_push(out_uniform->members, member);
        }
    }

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED, m)) {
        goto err;
    }
    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_SEMICOLON, m)) {
        goto err;
    }

    out_uniform->member_count = rlsl_vec_size(out_uniform->members);
    out_uniform->start = uniform_name_token->cursor_start;
    out_uniform->end = uniform_name_token->cursor_end;
    return true;
err:
    rlsl_token_stream_recover_top_level(ts);
    rlsl_ast_uniform_free(out_uniform);
    return false;
}

bool rlsl_ast_uniform_equal(const rlsl_ast_uniform_t* a, const rlsl_ast_uniform_t* b) {
    if(a->uniform_index != b->uniform_index) {
        return false;
    }
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

void rlsl_ast_uniform_free(rlsl_ast_uniform_t* u) {
    if(!u) {
        return;
    }
    for(size_t i = 0; i < u->member_count; i++) {
        rlsl_ast_member_free(&u->members[i]);
    }

    rlsl_vec_free(u->members);
    free(u->name);
}