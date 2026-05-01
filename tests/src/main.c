#include <stdio.h>
#include <rlsl_token.h>

int main() {

    const char* source = "100 0x1Q0 0b102 0b1Ä\n0x2733nq 1237.1123";
    const char* id = "test";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, id);

    for(int32_t i = 0; i < res.error_count; i++) {
        rlsl_error_print(&res.errors[i], source, id);
    }
    printf("Errors: %zu\n", res.error_count);
    return 0;
}