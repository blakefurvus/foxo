#include "deduce.h"

void fx_deduce_type(fx_comp_state *state, fx_node *node)
{
    switch (node->tok.type)
    {
        case FX_TOKTYPE_F_DEF: {
            // TODO: Deduce args and scope
            for (unsigned int i = 0; i < node->children[1].len; i++)
                fx_deduce_type(state, node->children[1].children + i);

            // Upload function to state
            fx_node *scope = node->children + 1;
            node->tok.var_type = scope->children[scope->len - 1].tok.var_type;
            fx_set_varnode(state, node->tok.val, *node);

            break;
        }

        case FX_TOKTYPE_SYM: {
            // TODO: Sync here with state's
            node->tok.var_type = fx_get_vartype(state, node->tok.val);
            break;
        }

        case FX_TOKTYPE_EQ: {
            // TODO: Sync here with state's
            node->children[0].tok.var_type = node->children[1].tok.var_type;
            node->tok.var_type = node->children[0].tok.var_type;
            break;
        }

        default:
            break;
    }
}