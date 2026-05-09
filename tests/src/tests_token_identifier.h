#include <string.h>
#include <rlsl_token.h>
#include "test_tools.h"

bool test_token_identifier() {
    return expect_token("test", EXPECT_TOKEN_IDENT("test"));
}

bool test_token_identifier_address_sequence() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_IDENT("test"),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_DOT),
        EXPECT_TOKEN_IDENT("test2")
    };
    return expect_tokens("test.test2", tokens);
}