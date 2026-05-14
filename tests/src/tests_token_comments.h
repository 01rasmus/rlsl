#include <string.h>
#include <rlsl_token.h>
#include "test_tools.h"

bool test_token_comment_simple() {
    return expect_token("//this is a comment", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMENT));
}

bool test_token_comment_c_style() {
    return expect_token("/* this is a c style comment */", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMENT));
}

bool test_token_comment_c_style_without_close() {
    return expect_token("/* this is a c style comment\n\n\n", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMENT));
}

bool test_token_comment_with_variable_declaration_after_simple() {
    expect_token_t tokens[] = {
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMENT),
        EXPECT_TOKEN_IDENT("float"),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_IDENT("test"),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_EQUAL),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_FLOAT(1.0),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SEMICOLON),
    };
    return expect_tokens("//test declaration\nfloat test = 1.0;", tokens);
}

bool test_token_comment_with_variable_declaration_after_c_styled() {
    expect_token_t tokens[] = {
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMENT),
        EXPECT_TOKEN_IDENT("float"),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_IDENT("test"),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_EQUAL),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SPACE),
        EXPECT_TOKEN_FLOAT(1.0),
        EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SEMICOLON),
    };
    return expect_tokens("/* test declaration\nand this is a comment on the other line */float test = 1.0;", tokens);
}

bool test_token_comment_with_c_styled_start_token_in_simple() {
    return expect_token("// c style open /*float", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMENT));
}

bool test_token_comment_with_c_styled_end_token_in_simple() {
    return expect_token("// c style end */float", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMENT));
}