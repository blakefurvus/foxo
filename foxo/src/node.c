#include "node.h"

void fx_free_node(fx_node *node)
{
    if (node->children) {
        for (unsigned int i = 0; i < node->len; i++)
            fx_free_node(node->children + i);
        free(node->children);
        fx_free_tok(&node->tok);
    }
}

void fx_print_node(fx_node *node, unsigned int indent)
{
    unsigned int x = 0;
    while (x++ < indent)
        putchar(' ');
    fx_print_tok(&node->tok);

    for (unsigned int i = 0; i < node->len; i++)
        fx_print_node(node->children + i, indent + 4);
}
