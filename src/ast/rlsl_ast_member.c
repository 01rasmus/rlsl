#include <string.h>
#include <stdlib.h>
#include "tools/rlsl_str.h"
#include "token/rlsl_token.h"
#include "rlsl_ast.h"
#include "rlsl_ast_member.h"

bool rlsl_ast_member_parse(rlsl_token_stream_t* ts, rlsl_ast_member_t* out_member, rlsl_ast_module_t* m) {
    memset(out_member, 0, sizeof(rlsl_ast_member_t));

    rlsl_token_t* first_token_peek = rlsl_token_stream_peek(ts, 1);
    if(!rlsl_ast_type_parse(ts, &out_member->type, m)) {
        goto err;
    }

    rlsl_token_t* name_token = rlsl_token_stream_advance(ts);
    if(!rlsl_ast_token_ensure(name_token, RLSL_TOKEN_LITERAL_IDENTIFIER, m)) {
        goto err;
    }
    uint64_t comp_count;
    if(!rlsl_ast_member_array_count_parse(ts, &out_member->component_count, m)) {
        goto err;
    }

    rlsl_token_t* end_token = rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_SEMICOLON, m);
    if(!end_token) {
        goto err;
    }

    out_member->name = rlsl_str_cpy(name_token->value.identifier);
    out_member->start = first_token_peek->cursor_start;
    out_member->end = end_token->cursor_end;
    return true;
err:
    rlsl_token_stream_recover_var_declaration(ts);
    rlsl_ast_member_free(out_member);
    return false;
}

bool rlsl_ast_member_array_count_parse(rlsl_token_stream_t* ts, uint64_t* out_comp_count, rlsl_ast_module_t* m) {
    if(!rlsl_ast_token_next_is(ts, RLSL_TOKEN_SYMBOL_BRACKET_OPENED)) {
        //it is not an array structure, so we shouldnt parse anything
        (*out_comp_count) = 1;
        return true;
    }

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_BRACKET_OPENED, m)) {
        goto err;
    }

    rlsl_token_t* int_token = rlsl_ast_token_expect(ts, RLSL_TOKEN_LITERAL_INT, m);
    if(!int_token) {
        goto err;
    }
    uint64_t comp_count = int_token->value.num_int.value;

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_BRACKET_CLOSED, m)) {
        goto err;
    }
    (*out_comp_count) = comp_count;
    return true;
err:
    return false;
}

bool rlsl_ast_member_equal(const rlsl_ast_member_t* a, const rlsl_ast_member_t* b) {
    if(a->component_count != b->component_count) {
        return false;
    }
    if(!rlsl_ast_type_equal(&a->type, &b->type)) {
        return false;
    }
    if(strcmp(a->name, b->name) != 0) {
        return false;
    }
    if(rlsl_cursor_compare(&a->start, &b->start) != 0) {
        return false;
    }
    if(rlsl_cursor_compare(&a->end, &b->end) != 0) {
        return false;
    }
    return true;
}

void rlsl_ast_member_free(rlsl_ast_member_t* sm) {
    if(!sm) {
        return;
    }
    free(sm->name);
    rlsl_ast_type_free(&sm->type);
}