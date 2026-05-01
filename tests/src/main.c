#include <stdio.h>
#include <token.h>

int main() {

    rlr_sl_tokenizer_result_t res = rlr_sl_token_tokenize_string("100 0x1Q0 0b102 0b1Ä\n0x2733nq 1237.1123", __FILE__);

    return 0;
}