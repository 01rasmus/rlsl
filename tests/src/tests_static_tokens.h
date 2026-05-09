#include <rlsl_token.h>

bool test_token_static(const char* source, rlsl_token_type_t type) {
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == type && res.error_count == 0;
}

bool test_token_static_double() {
    return test_token_static("double", RLSL_TOKEN_TYPE_DOUBLE);
}

bool test_token_static_uniform() {
    return test_token_static("uniform", RLSL_TOKEN_KEYWORD_UNIFORM);
}

bool test_token_static_input() {
    return test_token_static("input", RLSL_TOKEN_KEYWORD_INPUT);
}

bool test_token_static_output() {
    return test_token_static("output", RLSL_TOKEN_KEYWORD_OUTPUT);
}

bool test_token_static_mat2x2() {
    return test_token_static("mat2x2", RLSL_TOKEN_TYPE_MAT2X2);
}

bool test_token_static_mat2x3() {
    return test_token_static("mat2x3", RLSL_TOKEN_TYPE_MAT2X3);
}

bool test_token_static_mat2x4() {
    return test_token_static("mat2x4", RLSL_TOKEN_TYPE_MAT2X4);
}

bool test_token_static_mat3x2() {
    return test_token_static("mat3x2", RLSL_TOKEN_TYPE_MAT3X2);
}

bool test_token_static_mat3x3() {
    return test_token_static("mat3x3", RLSL_TOKEN_TYPE_MAT3X3);
}

bool test_token_static_mat3x4() {
    return test_token_static("mat3x4", RLSL_TOKEN_TYPE_MAT3X4);
}

bool test_token_static_mat4x2() {
    return test_token_static("mat4x2", RLSL_TOKEN_TYPE_MAT4X2);
}

bool test_token_static_mat4x3() {
    return test_token_static("mat4x3", RLSL_TOKEN_TYPE_MAT4X3);
}

bool test_token_static_mat4x4() {
    return test_token_static("mat4x4", RLSL_TOKEN_TYPE_MAT4X4);
}

bool test_token_static_return() {
    return test_token_static("return", RLSL_TOKEN_KEYWORD_RETURN);
}

bool test_token_static_struct() {
    return test_token_static("struct", RLSL_TOKEN_KEYWORD_STRUCT);
}

bool test_token_static_bvec2() {
    return test_token_static("bvec2", RLSL_TOKEN_TYPE_BVEC2);
}

bool test_token_static_bvec3() {
    return test_token_static("bvec3", RLSL_TOKEN_TYPE_BVEC3);
}

bool test_token_static_bvec4() {
    return test_token_static("bvec4", RLSL_TOKEN_TYPE_BVEC4);
}

bool test_token_static_const() {
    return test_token_static("const", RLSL_TOKEN_KEYWORD_CONST);
}

bool test_token_static_dvec2() {
    return test_token_static("dvec2", RLSL_TOKEN_TYPE_DVEC2);
}

bool test_token_static_dvec3() {
    return test_token_static("dvec3", RLSL_TOKEN_TYPE_DVEC3);
}

bool test_token_static_dvec4() {
    return test_token_static("dvec4", RLSL_TOKEN_TYPE_DVEC4);
}

bool test_token_static_false() {
    return test_token_static("false", RLSL_TOKEN_LITERAL_FALSE);
}

bool test_token_static_float() {
    return test_token_static("float", RLSL_TOKEN_TYPE_FLOAT);
}

bool test_token_static_ivec2() {
    return test_token_static("ivec2", RLSL_TOKEN_TYPE_IVEC2);
}

bool test_token_static_ivec3() {
    return test_token_static("ivec3", RLSL_TOKEN_TYPE_IVEC3);
}

bool test_token_static_ivec4() {
    return test_token_static("ivec4", RLSL_TOKEN_TYPE_IVEC4);
}

bool test_token_static_uvec2() {
    return test_token_static("uvec2", RLSL_TOKEN_TYPE_UVEC2);
}

bool test_token_static_uvec3() {
    return test_token_static("uvec3", RLSL_TOKEN_TYPE_UVEC3);
}

bool test_token_static_uvec4() {
    return test_token_static("uvec4", RLSL_TOKEN_TYPE_UVEC4);
}

bool test_token_static_while() {
    return test_token_static("while", RLSL_TOKEN_KEYWORD_WHILE);
}

bool test_token_static_bool() {
    return test_token_static("bool", RLSL_TOKEN_TYPE_BOOL);
}

bool test_token_static_else() {
    return test_token_static("else", RLSL_TOKEN_KEYWORD_ELSE);
}

bool test_token_static_mat2() {
    return test_token_static("mat2", RLSL_TOKEN_TYPE_MAT2);
}

bool test_token_static_mat3() {
    return test_token_static("mat3", RLSL_TOKEN_TYPE_MAT3);
}

bool test_token_static_mat4() {
    return test_token_static("mat4", RLSL_TOKEN_TYPE_MAT4);
}

bool test_token_static_true() {
    return test_token_static("true", RLSL_TOKEN_LITERAL_TRUE);
}

bool test_token_static_uint() {
    return test_token_static("uint", RLSL_TOKEN_TYPE_UINT);
}

bool test_token_static_vec2() {
    return test_token_static("vec2", RLSL_TOKEN_TYPE_VEC2);
}

bool test_token_static_vec3() {
    return test_token_static("vec3", RLSL_TOKEN_TYPE_VEC3);
}

bool test_token_static_vec4() {
    return test_token_static("vec4", RLSL_TOKEN_TYPE_VEC4);
}

bool test_token_static_for() {
    return test_token_static("for", RLSL_TOKEN_KEYWORD_FOR);
}

bool test_token_static_int() {
    return test_token_static("int", RLSL_TOKEN_TYPE_INT);
}

bool test_token_static_if() {
    return test_token_static("if", RLSL_TOKEN_KEYWORD_IF);
}

bool test_token_static_dash() {
    return test_token_static("-", RLSL_TOKEN_SYMBOL_DASH);
}

bool test_token_static_comma() {
    return test_token_static(",", RLSL_TOKEN_SYMBOL_COMMA);
}

bool test_token_static_semi_colon() {
    return test_token_static(";", RLSL_TOKEN_SYMBOL_SEMICOLON);
}

bool test_token_static_colon() {
    return test_token_static(":", RLSL_TOKEN_SYMBOL_COLON);
}

bool test_token_static_exclamation_mark() {
    return test_token_static("!", RLSL_TOKEN_SYMBOL_EXCLAMATION);
}

bool test_token_static_opened_paranthesis() {
    return test_token_static("(", RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED);
}

bool test_token_static_closed_paranthesis() {
    return test_token_static(")", RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED);
}

bool test_token_static_opened_bracket() {
    return test_token_static("[", RLSL_TOKEN_SYMBOL_BRACKET_OPENED);
}

bool test_token_static_closed_bracket() {
    return test_token_static("]", RLSL_TOKEN_SYMBOL_BRACKET_CLOSED);
}

bool test_token_static_opened_curly_bracket() {
    return test_token_static("{", RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED);
}

bool test_token_static_closed_curly_bracket() {
    return test_token_static("}", RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED);
}

bool test_token_static_star() {
    return test_token_static("*", RLSL_TOKEN_SYMBOL_STAR);
}

bool test_token_static_forward_slash() {
    return test_token_static("/", RLSL_TOKEN_SYMBOL_FORWARD_SLASH);
}

bool test_token_static_and() {
    return test_token_static("&", RLSL_TOKEN_SYMBOL_AND);
}

bool test_token_static_percent() {
    return test_token_static("%", RLSL_TOKEN_SYMBOL_PERCENT);
}

bool test_token_static_plus() {
    return test_token_static("+", RLSL_TOKEN_SYMBOL_PLUS);
}

bool test_token_static_arrow_left() {
    return test_token_static("<", RLSL_TOKEN_SYMBOL_ARROW_LEFT);
}

bool test_token_static_equal() {
    return test_token_static("=", RLSL_TOKEN_SYMBOL_EQUAL);
}

bool test_token_static_arrow_right() {
    return test_token_static(">", RLSL_TOKEN_SYMBOL_ARROW_RIGHT);
}

bool test_token_static_bar() {
    return test_token_static("|", RLSL_TOKEN_SYMBOL_PIPE);
}

bool test_token_static_tilde() {
    return test_token_static("~", RLSL_TOKEN_SYMBOL_TILDE);
}