#include "parse.h"

fx_node fx_next_node(fx_comp_state *state)
{
    fx_tok tok = fx_next_tok(state);

    switch (tok.type) {

        // Functions, symbols & variables
        case FX_TOKTYPE_SYM: {
            // Name
            fx_tok name = tok;
            tok = fx_peek_tok(state);

            // Args
            fx_node args = {
                (fx_tok){FX_TOKTYPE_ARGS},
                0, calloc(state->len, sizeof(fx_node))
            };

            // Is either a function call or definition
            if (tok.type == FX_TOKTYPE_L_PAREN) {
                fx_next_tok(state);

                // No args f()
                if (fx_peek_tok(state).type == FX_TOKTYPE_R_PAREN) {
                    fx_next_tok(state);

                    // Function definition f() =
                    if (fx_peek_tok(state).type == FX_TOKTYPE_EQ) {
                        name.type = FX_TOKTYPE_F_DEF;
                        fx_next_tok(state);

                        fx_node *context = calloc(2, sizeof(fx_node));
                        context[0] = args;
                        context[1] = fx_next_node(state);

                        if (context[1].tok.type != FX_TOKTYPE_SCOPE) {
                            fx_node scope = {
                                (fx_tok){FX_TOKTYPE_SCOPE},
                                1, malloc(sizeof(fx_node))
                            };
                            scope.children[0] = context[1];
                            context[1] = scope;
                        }

                        return (fx_node){name, 2, context};
                    }

                    // Function call f()...
                    else {
                        name.type = FX_TOKTYPE_F_CALL;
                        return (fx_node){name, args.len, args.children};
                    }

                }

                // Has args f(...)
                else {
                    while (1) {
                        args.children[args.len++] = fx_next_node(state);

                        tok = fx_next_tok(state);
                        if (tok.type == FX_TOKTYPE_COMMA)
                            continue;
                        else if (tok.type == FX_TOKTYPE_R_PAREN)
                            break;
                        else {
                            // TODO: Error handling
                            printf(
                                "Expected ',' or ')'. Found %s\n",
                                fx_toktype_str[tok.type]
                            );
                            exit(EXIT_FAILURE);
                        }
                    }

                    // Function definition f(...) =
                    if (fx_peek_tok(state).type == FX_TOKTYPE_EQ) {
                        name.type = FX_TOKTYPE_F_DEF;
                        fx_next_tok(state);

                        fx_node *context = calloc(2, sizeof(fx_node));
                        context[0] = args;
                        context[1] = fx_next_node(state);

                        if (context[1].tok.type != FX_TOKTYPE_SCOPE) {
                            fx_node scope = {
                                (fx_tok){FX_TOKTYPE_SCOPE},
                                1, malloc(sizeof(fx_node))
                            };
                            scope.children[0] = context[1];
                            context[1] = scope;
                        }

                        return (fx_node){name, 2, context};
                    }

                    // Function call f(...)
                    name.type = FX_TOKTYPE_F_CALL;
                    return (fx_node){name, args.len, args.children};
                }
            }

            // Equation x = y
            else if (tok.type == FX_TOKTYPE_EQ) {
                tok = fx_next_tok(state);

                fx_node *context = calloc(2, sizeof(fx_node));
                context[0] = (fx_node){name};
                context[1] = fx_next_node(state);

                return (fx_node){tok, 2, context};
            }

            // Is a symbol/variable
            free(args.children);
            return (fx_node){name};
        }

        // Scope
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

        // Default (returns the tok)
        default: {
            return (fx_node){tok};
            break;
        }
    }
}
