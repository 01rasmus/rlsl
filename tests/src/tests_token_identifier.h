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

bool test_token_identifier_with_digits() {
    return expect_token("test1234", EXPECT_TOKEN_IDENT("test1234"));
}

bool test_token_identifier_with_digits_and_underscore() {
    return expect_token("_test1234", EXPECT_TOKEN_IDENT("_test1234"));
}

bool test_token_identifier_ensure_error_invalid_character() {
    const expect_token_t tokens[] = {
        EXPECT_TOKEN_IDENT("test"),
    };
    return expect_tokens("testä", tokens);
}