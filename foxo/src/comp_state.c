#include "comp_state.h"

// Get relative name to the namespace
void get_name(fx_comp_state *state, char *name, char *buf)
{
    // Copy namespace
    char *nsi = state->ns;
    while (*nsi != '\0')
        *buf++ = *nsi++;
    *buf++ = '@';

    // Append var name
    while (*name != '\0')
        *buf++ = *name++;
    *buf = '\0';
}

fx_comp_state fx_create_comp_state(char *src)
{
    int len = strlen(src);

    fx_comp_state ret = {
        .len = len,
        .src = src,
        .iter = src,

        .indent_len = 0,
        .indent_dep = 0,

        .ns = {0},
        .nsi = NULL,

        .varnames = calloc(len, sizeof(char*)),
        .varnodes = calloc(len, sizeof(fx_node))
    };

    ret.nsi = ret.ns;
    memset(ret.varnames, 0, len * sizeof(char*));

    return ret;
}

void fx_free_comp_state(fx_comp_state *state)
{
    free(state->src);

    for (unsigned int i = 0; i < state->len; i++) {
        if (state->varnames[i] != NULL) {
            int at_count = 0;

            char *p = state->varnames[i];
            while (*p != '\0') {
                if (*p++ == '@')
                    at_count++;
            }

            if (at_count == 1) {
                if (state->varnodes[i].tok.type != FX_TOKTYPE_EOF)
                    fx_free_node(state->varnodes + i);
            }

            free(state->varnames[i]);
        }
    }
    free(state->varnames);
    free(state->varnodes);
}

void fx_asc_ns(fx_comp_state *state, char *name)
{
    *state->nsi++ = '@';
    while (*name != '\0')
        *state->nsi++ = *name++;
}

void fx_desc_ns(fx_comp_state *state)
{
    if (strcmp(state->ns, "")) {
        while (*--state->nsi != '@')
            *state->nsi = '\0';
        *state->nsi = '\0';
    }
}

void fx_set_vartype(fx_comp_state *state, char *name, fx_vartype type)
{
    // Get name
    char *buf = alloca(state->len);
    get_name(state, name, buf);

    // Set type
    for (unsigned int i = 0; i < state->len; i++) {

        if (state->varnames[i] == NULL) {
            state->varnames[i] = strdup(buf);
            state->vartypes[i] = type;
            return;
        }
        else if (!strcmp(state->varnames[i], buf)) {
            state->vartypes[i] = type;
            return;
        }

    }
}

fx_vartype fx_get_vartype(fx_comp_state *state, char *name)
{
    // Get name
    char *buf = alloca(state->len);
    get_name(state, name, buf);

    // Get type
    for (unsigned int i = 0; i < state->len; i++) {
        if (state->varnames[i] == NULL)
            return FX_VARTYPE_ANY;
        else if (!strcmp(state->varnames[i], buf))
            return state->vartypes[i];
    }

    return FX_VARTYPE_ANY;
}

void fx_set_varnode(fx_comp_state *state, char *name, fx_node node)
{
    // Get name
    char *buf = alloca(state->len);
    get_name(state, name, buf);

    // Set node
    for (unsigned int i = 0; i < state->len; i++) {

        if (state->varnames[i] == NULL) {
            state->varnames[i] = strdup(buf);
            state->varnodes[i] = node;
            return;
        }
        else if (!strcmp(state->varnames[i], buf)) {
            state->varnodes[i] = node;
            return;
        }

    }
}

fx_node *fx_get_varnode(fx_comp_state *state, char *name)
{
    // Get name
    char *buf = alloca(state->len);
    get_name(state, name, buf);

    // Get node
    for (unsigned int i = 0; i < state->len; i++) {
        if (state->varnames[i] == NULL)
            return NULL;
        else if (!strcmp(state->varnames[i], buf))
            return state->varnodes + i;
    }

    return NULL;
}

void fx_print_varnodes(fx_comp_state *state)
{
    for (unsigned int i = 0; i < state->len; i++) {
        if (state->varnames[i] == NULL)
            break;
        printf("%s:\n", state->varnames[i]);
        fx_print_node(state->varnodes + i);
    }
}