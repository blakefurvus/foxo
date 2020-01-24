#include "comp_state.h"

fx_comp_state fx_create_comp_state(char *src)
{
    int len = strlen(src);

    return (fx_comp_state) {
        .len = len,
        .src = src,
        .iter = src,

        .indent_len = 0,
        .indent_dep = 0
    };
}

void fx_free_comp_state(fx_comp_state *state)
{
    free(state->src);
}