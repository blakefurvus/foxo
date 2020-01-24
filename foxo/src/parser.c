#include "parser.h"

fx_node fx_next_node(char **iter_p)
{
    char *iter = *iter_p;
    fx_tok tok = fx_next_tok(&iter);

    switch (tok.type) {
        case FX_TOKTYPE_LET: {
            fx_tok fname = fx_next_tok(&iter);
            fname.type = FX_TOKTYPE_LET;

            int is_main = !strcmp(fname.val, "main");
            if (is_main)
                fname.var_type = FX_VARTYPE_INT;

            if (fx_next_tok(&iter).type != FX_TOKTYPE_EQUAL) {
                puts("Expected a '='");
                exit(EXIT_FAILURE);
            }

            unsigned int statements_len = 0;
            fx_node *statements = calloc(strlen(iter), sizeof(fx_node));

            while (1) {
                fx_node next = fx_next_node(&iter);
                if (next.tok.type == FX_TOKTYPE_DSCOLON || !next.tok.type)
                    break;

                statements[statements_len++] = next;
            }

            if (!is_main) {
                fname.var_type = statements[statements_len - 1].tok.var_type;
                if (fname.var_type) {
                    fx_node *mem = malloc(sizeof(fx_node));
                    *mem = statements[statements_len - 1];

                    statements[statements_len - 1] =
                        (fx_node){(fx_tok){FX_TOKTYPE_RETURN}, 1, mem};
                }
            }

            *iter_p = iter;
            return (fx_node){fname, statements_len, statements};
            break;
        }

        case FX_TOKTYPE_SYMBOL: {
            unsigned int args_len = 0;
            fx_node *args = calloc(strlen(iter), sizeof(fx_node));

            while (1) {
                fx_node next = fx_next_node(&iter);
                if (
                    next.tok.type == FX_TOKTYPE_EOL
                    || next.tok.type == FX_TOKTYPE_DSCOLON
                    || !next.tok.type)
                    break;

                args[args_len++] = next;
            }

            *iter_p = iter;
            return (fx_node){tok, args_len, args};
        }

        default: {
            *iter_p = iter;
            return (fx_node){tok, 0, NULL};
            break;
        }
    }
}
