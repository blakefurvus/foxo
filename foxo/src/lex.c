#include "lex.h"

fx_tok fx_next_tok(fx_comp_state *state)
{
    // Commonly used buffer;
    char *bufbase, *buf;
    bufbase = buf = alloca(state->len);

    // Skip whitespace
    while (*state->iter == ' ' || *state->iter == '\t')
        state->iter++;

    // Indentation
    if (*state->iter == '\n') {
        while (*state->iter++ == '\n');

        int new_indent_len = 0;
        while (*state->iter == ' ' || *state->iter == '\t') {
            new_indent_len++;
            if (*state->iter++ == '\t')
                new_indent_len += 3;
        }
        state->iter--;

        if (new_indent_len > state->indent_len) {
            state->indent_dep++;
            state->indent_len = new_indent_len;
            return (fx_tok){FX_TOKTYPE_INDENT};
        }
        else if (new_indent_len < state->indent_len) {
            state->indent_dep--;
            state->indent_len = new_indent_len;
            return (fx_tok){FX_TOKTYPE_DEDENT};
        }
        else {
            return (fx_tok){FX_TOKTYPE_EOL};
        }
    }

    // Symbols
    if (isalpha(*state->iter) || *state->iter == '_') {
        while (isalpha(*state->iter) || *state->iter == '_')
            *buf++ = *state->iter++;
        *buf = '\0';

        if (!strcmp(bufbase, "let")) {
            return state->indent_dep == 0
                ? (fx_tok){FX_TOKTYPE_F_DEF}
                : (fx_tok){FX_TOKTYPE_LET};
        }

        return (fx_tok){FX_TOKTYPE_SYM, strdup(bufbase)};
    }

    // Numbers
    else if (isdigit(*state->iter)) {
        while (isdigit(*state->iter))
            *buf++ = *state->iter++;
        *buf = '\0';

        return (fx_tok){FX_TOKTYPE_LIT, strdup(bufbase), FX_VARTYPE_INT};
    }

    // Strings
    else if (*state->iter == '\'' || *state->iter == '\"') {
        char pair = *state->iter++;

        while (*state->iter != pair)
            *buf++ = *state->iter++;
        *buf = '\0';
        state->iter++;

        return (fx_tok){FX_TOKTYPE_LIT, strdup(bufbase), FX_VARTYPE_STR};
    }

    // Operators
    else if (*state->iter == '=') {
        state->iter++;
        return (fx_tok){FX_TOKTYPE_EQ};
    }

    // Dedents at eof
    else if (state->indent_dep-- > 0)
        return (fx_tok){FX_TOKTYPE_DEDENT};

    // End of file
    return (fx_tok){FX_TOKTYPE_EOF};
}

fx_tok fx_peek_tok(fx_comp_state *state)
{
    char *backup = state->iter;
    fx_tok ret = fx_next_tok(state);
    state->iter = backup;
    return ret;
}