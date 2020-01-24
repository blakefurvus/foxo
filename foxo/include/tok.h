#ifndef FX_TOK_H
#define FX_TOK_H

#include <stdio.h>
#include <stdlib.h>

#include "var_types.h"

/*
 * TOKEN TYPES
 */

#define TOKTYPES \
    /* Invincibles */ \
    X(EOF) \
    X(EOL) \
    X(INDENT) \
    X(DEDENT) \
\
    /* Literals */ \
    X(SYM) \
    X(LIT) \
\
    /* Keywords */ \
    X(LET) \
    X(RET) \
\
    /* Operators */ \
    X(EQ) \
\
    /* Parsing specials */ \
    X(F_DEF) \
    X(F_CALL) \
    X(SCOPE)

typedef enum {
    #define X(value) FX_TOKTYPE_##value,
        TOKTYPES
    #undef X
} fx_toktype;

static const char *fx_toktype_str[] = {
    #define X(value) #value,
        TOKTYPES
    #undef X
};

#undef TOKTYPES


/*
 * TOKEN
 */

typedef struct {
    fx_toktype type;
    char *val;
    fx_vartype var_type;
} fx_tok;

void fx_free_tok(fx_tok *tok);
void fx_print_tok(fx_tok *tok);

#endif
