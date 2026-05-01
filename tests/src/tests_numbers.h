#include <stdio.h>
#include <rlsl_token.h>

bool test_token_number_with_line_break() {
    const char* source = "0x10\n0x10";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    if(res.token_count != 3) {
        return false;
    }

    rlsl_token_t t1 = res.tokens[0];
    rlsl_token_t t2 = res.tokens[1];
    rlsl_token_t t3 = res.tokens[2];

    if(!(t1.type == RLSL_TOKEN_LITERAL_INT && t1.value.integer.value == 16)) {
        return false;
    }

    if(t2.type != RLSL_TOKEN_SYMBOL_SPACE) {
        return false;
    }

    if(!(t3.type == RLSL_TOKEN_LITERAL_INT && t3.value.integer.value == 16)) {
        return false;
    }
    return true;
}