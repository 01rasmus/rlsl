#include <rlsl_token.h>
#include "test_tools.h"

bool test_token_static_uniform() {
    return expect_token("uniform", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_UNIFORM));
}

bool test_token_static_input() {
    return expect_token("input", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_INPUT));
}

bool test_token_static_output() {
    return expect_token("output", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_OUTPUT));
}

bool test_token_static_mat2x2() {
    return expect_token("mat2x2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT2X2));
}

bool test_token_static_mat2x3() {
    return expect_token("mat2x3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT2X3));
}

bool test_token_static_mat2x4() {
    return expect_token("mat2x4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT2X4));
}

bool test_token_static_mat3x2() {
    return expect_token("mat3x2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT3X2));
}

bool test_token_static_mat3x3() {
    return expect_token("mat3x3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT3X3));
}

bool test_token_static_mat3x4() {
    return expect_token("mat3x4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT3X4));
}

bool test_token_static_mat4x2() {
    return expect_token("mat4x2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT4X2));
}

bool test_token_static_mat4x3() {
    return expect_token("mat4x3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT4X3));
}

bool test_token_static_mat4x4() {
    return expect_token("mat4x4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT4X4));
}

bool test_token_static_return() {
    return expect_token("return", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_RETURN));
}

bool test_token_static_struct() {
    return expect_token("struct", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_STRUCT));
}

bool test_token_static_bvec2() {
    return expect_token("bvec2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_BVEC2));
}

bool test_token_static_bvec3() {
    return expect_token("bvec3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_BVEC3));
}

bool test_token_static_bvec4() {
    return expect_token("bvec4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_BVEC4));
}

bool test_token_static_const() {
    return expect_token("const", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_CONST));
}

bool test_token_static_false() {
    return expect_token("false", EXPECT_TOKEN(RLSL_TOKEN_LITERAL_FALSE));
}

bool test_token_static_void() {
    return expect_token("void", EXPECT_TOKEN(RLSL_TOKEN_TYPE_VOID));
}

bool test_token_static_lowp() {
    return expect_token("lowp", EXPECT_TOKEN(RLSL_TOKEN_TYPE_PRECISION_LOWP));
}

bool test_token_static_mediump() {
    return expect_token("mediump", EXPECT_TOKEN(RLSL_TOKEN_TYPE_PRECISION_MEDIUMP));
}

bool test_token_static_highp() {
    return expect_token("highp", EXPECT_TOKEN(RLSL_TOKEN_TYPE_PRECISION_HIGHP));
}

bool test_token_static_float() {
    return expect_token("float", EXPECT_TOKEN(RLSL_TOKEN_TYPE_FLOAT));
}

bool test_token_static_ivec2() {
    return expect_token("ivec2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_IVEC2));
}

bool test_token_static_ivec3() {
    return expect_token("ivec3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_IVEC3));
}

bool test_token_static_ivec4() {
    return expect_token("ivec4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_IVEC4));
}

bool test_token_static_uvec2() {
    return expect_token("uvec2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_UVEC2));
}

bool test_token_static_uvec3() {
    return expect_token("uvec3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_UVEC3));
}

bool test_token_static_uvec4() {
    return expect_token("uvec4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_UVEC4));
}

bool test_token_static_while() {
    return expect_token("while", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_WHILE));
}

bool test_token_static_bool() {
    return expect_token("bool", EXPECT_TOKEN(RLSL_TOKEN_TYPE_BOOL));
}

bool test_token_static_else() {
    return expect_token("else", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_ELSE));
}

bool test_token_static_mat2() {
    return expect_token("mat2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT2));
}

bool test_token_static_mat3() {
    return expect_token("mat3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT3));
}

bool test_token_static_mat4() {
    return expect_token("mat4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_MAT4));
}

bool test_token_static_true() {
    return expect_token("true", EXPECT_TOKEN(RLSL_TOKEN_LITERAL_TRUE));
}

bool test_token_static_uint() {
    return expect_token("uint", EXPECT_TOKEN(RLSL_TOKEN_TYPE_UINT));
}

bool test_token_static_vec2() {
    return expect_token("vec2", EXPECT_TOKEN(RLSL_TOKEN_TYPE_VEC2));
}

bool test_token_static_vec3() {
    return expect_token("vec3", EXPECT_TOKEN(RLSL_TOKEN_TYPE_VEC3));
}

bool test_token_static_vec4() {
    return expect_token("vec4", EXPECT_TOKEN(RLSL_TOKEN_TYPE_VEC4));
}

bool test_token_static_for() {
    return expect_token("for", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_FOR));
}

bool test_token_static_int() {
    return expect_token("int", EXPECT_TOKEN(RLSL_TOKEN_TYPE_INT));
}

bool test_token_static_if() {
    return expect_token("if", EXPECT_TOKEN(RLSL_TOKEN_KEYWORD_IF));
}

bool test_token_static_dash() {
    return expect_token("-", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_DASH));
}

bool test_token_static_comma() {
    return expect_token(",", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COMMA));
}

bool test_token_static_semi_colon() {
    return expect_token(";", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_SEMICOLON));
}

bool test_token_static_colon() {
    return expect_token(":", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_COLON));
}

bool test_token_static_exclamation_mark() {
    return expect_token("!", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_EXCLAMATION));
}

bool test_token_static_opened_paranthesis() {
    return expect_token("(", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED));
}

bool test_token_static_closed_paranthesis() {
    return expect_token(")", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED));
}

bool test_token_static_opened_bracket() {
    return expect_token("[", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_BRACKET_OPENED));
}

bool test_token_static_closed_bracket() {
    return expect_token("]", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_BRACKET_CLOSED));
}

bool test_token_static_opened_curly_bracket() {
    return expect_token("{", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED));
}

bool test_token_static_closed_curly_bracket() {
    return expect_token("}", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED));
}

bool test_token_static_star() {
    return expect_token("*", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_STAR));
}

bool test_token_static_forward_slash() {
    return expect_token("/", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_FORWARD_SLASH));
}

bool test_token_static_and() {
    return expect_token("&", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_AND));
}

bool test_token_static_percent() {
    return expect_token("%", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_PERCENT));
}

bool test_token_static_plus() {
    return expect_token("+", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_PLUS));
}

bool test_token_static_arrow_left() {
    return expect_token("<", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_ARROW_LEFT));
}

bool test_token_static_equal() {
    return expect_token("=", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_EQUAL));
}

bool test_token_static_arrow_right() {
    return expect_token(">", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_ARROW_RIGHT));
}

bool test_token_static_bar() {
    return expect_token("|", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_PIPE));
}

bool test_token_static_tilde() {
    return expect_token("~", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_TILDE));
}

bool test_token_static_dot() {
    return expect_token(".", EXPECT_TOKEN(RLSL_TOKEN_SYMBOL_DOT));
}