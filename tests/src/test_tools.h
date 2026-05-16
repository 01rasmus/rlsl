#pragma once
#include <rlsl_token.h>

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

bool expect_token(const char* source, const expect_token_t expect);

bool expect_error(const char* source, const rlsl_error_enum_t error, uint64_t start_line, uint64_t start_column, uint64_t end_line, uint64_t end_column);

#define expect_tokens(SOURCE, EXPECTS) \
    _expect_tokens(SOURCE, EXPECTS, sizeof(EXPECTS) / sizeof(expect_token_t))

bool _expect_tokens(const char* source, const expect_token_t* expects, size_t expects_length);