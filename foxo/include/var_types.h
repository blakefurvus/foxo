#ifndef FX_VAR_TYPES_H
#define FX_VAR_TYPES_H

#define VARTYPES \
    X(ANY, void, null) \
    X(INT, int, %d) \
    X(STRING, char *, %s)

typedef enum {
    #define X(value, ret, fmt) FX_VARTYPE_##value,
        VARTYPES
    #undef X
} fx_vartype;

static const char *fx_vartype_str[] = {
    #define X(value, ret, fmt) #value,
        VARTYPES
    #undef X
};

static const char *fx_vartype_ret[] = {
    #define X(value, ret, fmt) #ret,
        VARTYPES
    #undef X
};

static const char *fx_vartype_fmt[] = {
    #define X(value, ret, fmt) #fmt,
        VARTYPES
    #undef X
};

#undef VARTYPES

#endif
