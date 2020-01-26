#ifndef FX_VAR_TYPES_H
#define FX_VAR_TYPES_H

#define VARTYPES \
    X(ANY) \
    X(FUN) \
    X(INT) \
    X(STR)

typedef enum {
    #define X(value) FX_VARTYPE_##value,
        VARTYPES
    #undef X
} fx_vartype;

static const char *fx_vartype_str[] = {
    #define X(value) #value,
        VARTYPES
    #undef X
};

#undef VARTYPES

#endif
