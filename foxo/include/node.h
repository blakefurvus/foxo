#ifndef FX_NODE_H
#define FX_NODE_H

#include "tok.h"

typedef struct fx_node fx_node;
struct fx_node {
    fx_tok tok;

    unsigned int len;
    fx_node *children;
};

void fx_free_node(fx_node *node);
void fx_print_node(fx_node *node, unsigned int indent);

#endif
