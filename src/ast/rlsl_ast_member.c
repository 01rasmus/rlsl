#include <string.h>
#include <stdlib.h>
#include "tools/rlsl_str.h"
#include "token/rlsl_token.h"
#include "rlsl_ast.h"
#include "rlsl_ast_member.h"

bool rlsl_ast_member_parse(rlsl_token_stream_t* ts, rlsl_ast_member_t* out_member, rlsl_ast_module_t* m) {
    memset(out_member, 0, sizeof(rlsl_ast_member_t));

    rlsl_token_type_t first_expected_tokens[] = {
        RLSL_TOKEN_PRECISION_LOWP,
        RLSL_TOKEN_PRECISION_MEDIUMP,
        RLSL_TOKEN_PRECISION_HIGHP,
        RLSL_TOKEN_LITERAL_IDENTIFIER
    };

    rlsl_token_t* first_token = rlsl_ast_token_expect_any_of(ts, first_expected_tokens, m);
    if(!first_token) {
        goto err;
    }
    switch(first_token->type) {
        case RLSL_TOKEN_PRECISION_LOWP: {
            out_member->precision = RLSL_AST_PRECISION_LOWP;
            break;
        }
        case RLSL_TOKEN_PRECISION_MEDIUMP: {
            out_member->precision = RLSL_AST_PRECISION_MEDIUMP;
            break;
        }
        case RLSL_TOKEN_PRECISION_HIGHP: {
            out_member->precision = RLSL_AST_PRECISION_HIGHP;
            break;
        }
        default:
            out_member->precision = RLSL_AST_PRECISION_NONE;
            break;
    }

    rlsl_token_t* type_token = first_token;
    if(out_member->precision != RLSL_AST_PRECISION_NONE) {
        type_token = rlsl_token_stream_advance(ts);
    }

    if(!rlsl_ast_token_ensure(type_token, RLSL_TOKEN_LITERAL_IDENTIFIER, m)) {
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
    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_SEMICOLON, m)) {
        goto err;
    }

    out_member->name = rlsl_str_cpy(name_token->value.identifier);
    out_member->type = rlsl_str_cpy(type_token->value.identifier);
    out_member->start = first_token->cursor_start;
    out_member->end = name_token->cursor_end;
    return true;
err:
    rlsl_token_stream_recover_var_declaration(ts, true);
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
    rlsl_token_stream_recover_var_declaration(ts, false);
    return false;
}

void rlsl_ast_member_free(rlsl_ast_member_t* sm) {
    if(!sm) {
        return;
    }
    free(sm->name);
    free(sm->type);
}