#ifndef FX_COMP_STATE_H
#define FX_COMP_STATE_H

typedef struct {
    unsigned int len;
    char *src;
    char *iter;

    int indent_len;
    int indent_dep;
} fx_comp_state;

fx_comp_state fx_create_comp_state(char *src);
void fx_free_comp_state(fx_comp_state *state);

#endif
