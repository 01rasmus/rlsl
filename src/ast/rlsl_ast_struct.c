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

        rlsl_ast_struct_member_t struct_member;
        if(rlsl_ast_struct_member_parse(ts, &struct_member, m)) {
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
    rlsl_token_stream_recover(ts);
    rlsl_ast_struct_free(out_struct);
    return false;
}

bool rlsl_ast_struct_member_parse(rlsl_token_stream_t* ts, rlsl_ast_struct_member_t* out_struct_member, rlsl_ast_module_t* m) {
    memset(out_struct_member, 0, sizeof(rlsl_ast_struct_member_t));

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
            out_struct_member->precision = RLSL_AST_PRECISION_LOWP;
            break;
        }
        case RLSL_TOKEN_PRECISION_MEDIUMP: {
            out_struct_member->precision = RLSL_AST_PRECISION_MEDIUMP;
            break;
        }
        case RLSL_TOKEN_PRECISION_HIGHP: {
            out_struct_member->precision = RLSL_AST_PRECISION_HIGHP;
            break;
        }
        default:
            out_struct_member->precision = RLSL_AST_PRECISION_NONE;
            break;
    }

    rlsl_token_t* type_token = first_token;
    if(out_struct_member->precision != RLSL_AST_PRECISION_NONE) {
        type_token = rlsl_token_stream_advance(ts);
    }

    if(!rlsl_ast_token_ensure(type_token, RLSL_TOKEN_LITERAL_IDENTIFIER, m)) {
        goto err;
    }
    rlsl_token_t* name_token = rlsl_token_stream_advance(ts);
    if(!rlsl_ast_token_ensure(name_token, RLSL_TOKEN_LITERAL_IDENTIFIER, m)) {
        goto err;
    }
    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_SEMICOLON, m)) {
        goto err;
    }

    out_struct_member->name = rlsl_str_cpy(name_token->value.identifier);
    out_struct_member->type = rlsl_str_cpy(type_token->value.identifier);
    out_struct_member->start = first_token->cursor_start;
    out_struct_member->end = name_token->cursor_end;
    return true;
err:
    rlsl_token_stream_recover(ts);
    rlsl_ast_struct_member_free(out_struct_member);
    return false;
}

void rlsl_ast_struct_free(rlsl_ast_struct_t* s) {
    if(!s) {
        return;
    }
    for(size_t i = 0; i < s->member_count; i++) {
        rlsl_ast_struct_member_free(&s->members[i]);
    }

    rlsl_vec_free(s->members);
    free(s->name);
}

void rlsl_ast_struct_member_free(rlsl_ast_struct_member_t* sm) {
    if(!sm) {
        return;
    }
    free(sm->name);
    free(sm->type);
}