#include <stdlib.h>
#include <string.h>
#include "tools/rlsl_str.h"
#include "token/rlsl_token.h"
#include "ast/rlsl_ast_type.h"
#include "rlsl_ast.h"

bool rlsl_ast_type_parse(rlsl_token_stream_t* ts, rlsl_ast_type_t* out_type, rlsl_ast_module_t* m) {
    memset(out_type, 0, sizeof(rlsl_ast_type_t));

    rlsl_token_type_t first_expected_tokens[] = {
        RLSL_TOKEN_KEYWORD_CONST,
        RLSL_TOKEN_PRECISION_LOWP,
        RLSL_TOKEN_PRECISION_MEDIUMP,
        RLSL_TOKEN_PRECISION_HIGHP,
        RLSL_TOKEN_LITERAL_IDENTIFIER,
    };

    rlsl_token_t* token = rlsl_ast_token_expect_any_of(ts, first_expected_tokens, m);
    if(!token) {
        goto err;
    }
    out_type->start = token->cursor_start;

    if(token->type == RLSL_TOKEN_KEYWORD_CONST) {
        out_type->is_const = true;

        /*
            since the token was a const, we need to check the next token
            for either any of the precision identifiers or and identifier
        */
        rlsl_token_type_t after_const_expected_tokens[] = {
            RLSL_TOKEN_PRECISION_LOWP,
            RLSL_TOKEN_PRECISION_MEDIUMP,
            RLSL_TOKEN_PRECISION_HIGHP,
            RLSL_TOKEN_LITERAL_IDENTIFIER,
        };

        //we can reuse the same token
        token = rlsl_ast_token_expect_any_of(ts, after_const_expected_tokens, m);
        if(!token) {
            goto err;
        }
    }

    switch(token->type) {
        case RLSL_TOKEN_PRECISION_LOWP: {
            out_type->precision = RLSL_AST_PRECISION_LOWP;
            break;
        }
        case RLSL_TOKEN_PRECISION_MEDIUMP: {
            out_type->precision = RLSL_AST_PRECISION_MEDIUMP;
            break;
        }
        case RLSL_TOKEN_PRECISION_HIGHP: {
            out_type->precision = RLSL_AST_PRECISION_HIGHP;
            break;
        }
        default:
            out_type->precision = RLSL_AST_PRECISION_NONE;
            break;
    }

    /*
        if the last token was a precision token, we need
        to get the next identifier token
    */
    if(out_type->precision != RLSL_AST_PRECISION_NONE) {
        token = rlsl_ast_token_expect(ts, RLSL_TOKEN_LITERAL_IDENTIFIER, m);
        if(!token) {
            goto err;
        }
    }

    out_type->end = token->cursor_end;
    out_type->type = rlsl_str_cpy(token->value.identifier);
    return true;
err:
    rlsl_ast_type_free(out_type);
    return false;
}

bool rlsl_ast_type_equal(const rlsl_ast_type_t* a, const rlsl_ast_type_t* b) {
    if(a->is_const != b->is_const) {
        return false;
    }
    if(a->precision != b->precision) {
        return false;
    }
    if(strcmp(a->type, b->type) != 0) {
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

void rlsl_ast_type_free(rlsl_ast_type_t* t) {
    if(!t) {
        return;
    }
    free(t->type);
}