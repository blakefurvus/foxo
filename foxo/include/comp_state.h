#ifndef FX_COMP_STATE_H
#define FX_COMP_STATE_H

#include <stdlib.h>
#include <string.h>
#include "var_types.h"
#include "node.h"

typedef struct {
    unsigned int len;
    char *src;
    char *iter;

    int indent_len;
    int indent_dep;

    char ns[256];
    char *nsi;

    char **varnames;
    fx_vartype *vartypes;
    int *varargcounts;
    fx_node *varnodes;
} fx_comp_state;

fx_comp_state fx_create_comp_state(char *src);
void fx_free_comp_state(fx_comp_state *state);

void fx_asc_ns(fx_comp_state *state, char *name);
void fx_desc_ns(fx_comp_state *state);

void fx_set_vartype(fx_comp_state *state, char *name, fx_vartype type);
fx_vartype fx_get_vartype(fx_comp_state *state, char *name);

void fx_set_varnode(fx_comp_state *state, char *name, fx_node node);
fx_node *fx_get_varnode(fx_comp_state *state, char *name);
void fx_print_varnodes(fx_comp_state *state);

#endif
