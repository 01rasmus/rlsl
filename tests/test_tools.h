#pragma once
#include <token/rlsl_token.h>
#include <ast/rlsl_ast.h>

typedef struct expect_token_t {
    rlsl_token_type_t type;
    union {
        double d;
        uint64_t i;
        const char* s;
    } value;
} expect_token_t;

#define EXPECT_TOKEN(TYPE) (expect_token_t){ .type = TYPE }
#define EXPECT_TOKEN_INT(VAL) (expect_token_t){ .type = RLSL_TOKEN_LITERAL_INT, .value.i = VAL }
#define EXPECT_TOKEN_FLOAT(VAL) (expect_token_t){ .type = RLSL_TOKEN_LITERAL_FLOAT, .value.d = VAL }
#define EXPECT_TOKEN_IDENT(VAL) (expect_token_t){ .type = RLSL_TOKEN_LITERAL_IDENTIFIER, .value.s = VAL }
#define EXPECT_ERROR(ERROR_CODE, START, END, STATIC) \
    (rlsl_error_t) { \
        .message = STATIC ? rlsl_error_string(ERROR_CODE) : NULL, \
        .dynamic_message = NULL, \
        .message_is_static = STATIC, \
        .severity = rlsl_error_severity(ERROR_CODE), \
        .code = (ERROR_CODE), \
        .start = (START), \
        .end = (END), \
    }

bool expect_token(const char* source, const expect_token_t expect);
bool expect_error(const char* source, const rlsl_error_enum_t error, uint64_t start_line, uint64_t start_column, uint64_t end_line, uint64_t end_column);

#define expect_tokens(SOURCE, EXPECTS) \
    _expect_tokens(SOURCE, EXPECTS, sizeof(EXPECTS) / sizeof(expect_token_t))

#define expect_ast_errors(SOURCE, EXPECTED_ERRORS) \
    _expect_ast_errors(SOURCE, EXPECTED_ERRORS, sizeof(EXPECTED_ERRORS) / sizeof(EXPECTED_ERRORS[0]))

bool ast_get(const char* source, rlsl_ast_module_t* out);
bool expect_ast(const char* source, const rlsl_ast_module_t* expected_module);

bool _expect_tokens(const char* source, const expect_token_t* expects, size_t expects_length);
bool _expect_ast_errors(const char* source, const rlsl_error_t* expected_errors, size_t expected_error_count);