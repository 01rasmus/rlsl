#include <rlsl_token.h>

bool test_token_static_double() {
    const char* source = "double";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_DOUBLE;
}

bool test_token_static_uniform() {
    const char* source = "uniform";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_UNIFORM;
}

bool test_token_static_input() {
    const char* source = "input";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_INPUT;
}

bool test_token_static_output() {
    const char* source = "output";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_OUTPUT;
}

bool test_token_static_mat2x2() {
    const char* source = "mat2x2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT2X2;
}

bool test_token_static_mat2x3() {
    const char* source = "mat2x3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT2X3;
}

bool test_token_static_mat2x4() {
    const char* source = "mat2x4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT2X4;
}

bool test_token_static_mat3x2() {
    const char* source = "mat3x2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT3X2;
}

bool test_token_static_mat3x3() {
    const char* source = "mat3x3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT3X3;
}

bool test_token_static_mat3x4() {
    const char* source = "mat3x4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT3X4;
}

bool test_token_static_mat4x2() {
    const char* source = "mat4x2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT4X2;
}

bool test_token_static_mat4x3() {
    const char* source = "mat4x3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT4X3;
}

bool test_token_static_mat4x4() {
    const char* source = "mat4x4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT4X4;
}

bool test_token_static_return() {
    const char* source = "return";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_RETURN;
}

bool test_token_static_struct() {
    const char* source = "struct";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_STRUCT;
}

bool test_token_static_bvec2() {
    const char* source = "bvec2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_BVEC2;
}

bool test_token_static_bvec3() {
    const char* source = "bvec3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_BVEC3;
}

bool test_token_static_bvec4() {
    const char* source = "bvec4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_BVEC4;
}

bool test_token_static_const() {
    const char* source = "const";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_CONST;
}

bool test_token_static_dvec2() {
    const char* source = "dvec2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_DVEC2;
}

bool test_token_static_dvec3() {
    const char* source = "dvec3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_DVEC3;
}

bool test_token_static_dvec4() {
    const char* source = "dvec4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_DVEC4;
}

bool test_token_static_false() {
    const char* source = "false";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_LITERAL_FALSE;
}

bool test_token_static_float() {
    const char* source = "float";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_FLOAT;
}

bool test_token_static_ivec2() {
    const char* source = "ivec2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_IVEC2;
}

bool test_token_static_ivec3() {
    const char* source = "ivec3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_IVEC3;
}

bool test_token_static_ivec4() {
    const char* source = "ivec4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_IVEC4;
}

bool test_token_static_uvec2() {
    const char* source = "uvec2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_UVEC2;
}

bool test_token_static_uvec3() {
    const char* source = "uvec3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_UVEC3;
}

bool test_token_static_uvec4() {
    const char* source = "uvec4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_UVEC4;
}

bool test_token_static_while() {
    const char* source = "while";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_WHILE;
}

bool test_token_static_bool() {
    const char* source = "bool";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_BOOL;
}

bool test_token_static_else() {
    const char* source = "else";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_ELSE;
}

bool test_token_static_mat2() {
    const char* source = "mat2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT2;
}

bool test_token_static_mat3() {
    const char* source = "mat3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT3;
}

bool test_token_static_mat4() {
    const char* source = "mat4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_MAT4;
}

bool test_token_static_true() {
    const char* source = "true";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_LITERAL_TRUE;
}

bool test_token_static_uint() {
    const char* source = "uint";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_UINT;
}

bool test_token_static_vec2() {
    const char* source = "vec2";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_VEC2;
}

bool test_token_static_vec3() {
    const char* source = "vec3";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_VEC3;
}

bool test_token_static_vec4() {
    const char* source = "vec4";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_VEC4;
}

bool test_token_static_for() {
    const char* source = "for";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_FOR;
}

bool test_token_static_int() {
    const char* source = "int";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_TYPE_INT;
}

bool test_token_static_if() {
    const char* source = "if";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_KEYWORD_IF;
}

bool test_token_static_dash() {
    const char* source = "-";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_DASH;
}

bool test_token_static_comma() {
    const char* source = ",";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_COMMA;
}

bool test_token_static_semi_colon() {
    const char* source = ";";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_SEMICOLON;
}

bool test_token_static_colon() {
    const char* source = ":";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_COLON;
}

bool test_token_static_exclamation_mark() {
    const char* source = "!";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_EXCLAMATION;
}

bool test_token_static_opened_paranthesis() {
    const char* source = "(";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_PARENTHESIS_OPENED;
}

bool test_token_static_closed_paranthesis() {
    const char* source = ")";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_PARENTHESIS_CLOSED;
}

bool test_token_static_opened_bracket() {
    const char* source = "[";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_BRACKET_OPENED;
}

bool test_token_static_closed_bracket() {
    const char* source = "]";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_BRACKET_CLOSED;
}

bool test_token_static_opened_curly_bracket() {
    const char* source = "{";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_CURLY_BRACKET_OPENED;
}

bool test_token_static_closed_curly_bracket() {
    const char* source = "}";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_CURLY_BRACKET_CLOSED;
}

bool test_token_static_star() {
    const char* source = "*";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_STAR;
}

bool test_token_static_forward_slash() {
    const char* source = "/";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_FORWARD_SLASH;
}

bool test_token_static_and() {
    const char* source = "&";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_AND;
}

bool test_token_static_percent() {
    const char* source = "%";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_PERCENT;
}

bool test_token_static_plus() {
    const char* source = "+";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_PLUS;
}

bool test_token_static_arrow_left() {
    const char* source = "<";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_ARROW_LEFT;
}

bool test_token_static_equal() {
    const char* source = "=";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_EQUAL;
}

bool test_token_static_arrow_right() {
    const char* source = ">";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_ARROW_RIGHT;
}

bool test_token_static_bar() {
    const char* source = "|";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_PIPE;
}

bool test_token_static_tilde() {
    const char* source = "~";
    rlsl_tokenizer_result_t res = rlsl_token_tokenize_string(source, NULL);
    return res.token_count == 1 && res.tokens[0].type == RLSL_TOKEN_SYMBOL_TILDE;
}