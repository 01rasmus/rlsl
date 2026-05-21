#include <string.h>
#include "rlsl_ast_io.h"
#include "rlsl_ast.h"

bool rlsl_ast_io_parse(rlsl_token_stream_t* ts, rlsl_ast_io_type_t type, rlsl_ast_io_t* out_io, rlsl_ast_module_t* m) {
    memset(out_io, 0, sizeof(rlsl_ast_io_t));

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED, m)) {
        goto err;
    }

    rlsl_token_t* io_attribute_index = rlsl_ast_token_expect(ts, RLSL_TOKEN_LITERAL_INT, m);
    if(!io_attribute_index) {
        goto err;
    }
    out_io->index = io_attribute_index->value.num_int.value;

    if(!rlsl_ast_token_expect(ts, RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED, m)) {
        goto err;
    }

    if(!rlsl_ast_member_parse(ts, &out_io->member, m)) {
        goto err;
    }

    out_io->type = type;
    return true;
err:
    rlsl_token_stream_recover_top_level(ts);
    rlsl_ast_io_free(out_io);
    return false;
}

bool rlsl_ast_io_equal(const rlsl_ast_io_t* a, const rlsl_ast_io_t* b) {
    if(a->type != b->type) {
        return false;
    }
    if(a->index != b->index) {
        return false;
    }
    if(rlsl_cursor_compare(&a->start, &b->start) != 0) {
        return false;
    }
    if(rlsl_cursor_compare(&a->end, &b->end) != 0) {
        return false;
    }
    if(!rlsl_ast_member_equal(&a->member, &b->member)) {
        return false;
    }
    return true;
}

void rlsl_ast_io_free(rlsl_ast_io_t* io) {
    if(!io) {
        return;
    }
    rlsl_ast_member_free(&io->member);
}
