#include "parse.h"

fx_node fx_next_node(fx_comp_state *state)
{
    fx_tok tok = fx_next_tok(state);

    switch (tok.type) {

        // Function definitions
        case FX_TOKTYPE_F_DEF:
        case FX_TOKTYPE_LET: {

            // Functions name
            fx_tok fname = fx_next_tok(state);
            fname.type = tok.type;

            // TODO: Parse arguments too

            // TODO: Error handling
            if (fx_next_tok(state).type != FX_TOKTYPE_EQ) {
                puts("Expected a '='");
                exit(EXIT_FAILURE);
            }

            // Functions body
            fx_node *contents = calloc(1, sizeof(fx_node));
            contents[0] = fx_next_node(state);

            return (fx_node){fname, 1, contents};
            break;

        }

        // Code scopes
        case FX_TOKTYPE_INDENT: {
            unsigned int statements_len = 0;
            fx_node *statements = calloc(state->len, sizeof(fx_node));

            fx_node next = fx_next_node(state);
            while (
                next.tok.type != FX_TOKTYPE_DEDENT
                && next.tok.type != FX_TOKTYPE_EOF
            ) {
                statements[statements_len++] = next;
                next = fx_next_node(state);
            }

            return (fx_node) {
                (fx_tok){FX_TOKTYPE_SCOPE},
                statements_len,
                statements
            };
            break;
        }

        // Function calls & constants
        case FX_TOKTYPE_SYM: {
            unsigned int args_len = 0;
            fx_node *args = calloc(state->len, sizeof(fx_node));

            fx_tok peek = fx_peek_tok(state);
            while (peek.type == FX_TOKTYPE_SYM || peek.type == FX_TOKTYPE_LIT) {
                args[args_len++] = fx_next_node(state);
                peek = fx_peek_tok(state);
            }

            if (args_len != 0)
                tok.type = FX_TOKTYPE_F_CALL;

            return (fx_node){tok, args_len, args};
        }

        // Default (returns the tok)
        default: {
            return (fx_node){tok, 0, NULL};
            break;
        }
    }
}
