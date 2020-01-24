#include "lexer.h"

fx_tok fx_next_tok(char **iter_p)
{
    char *iter = *iter_p;

    while (*iter == ' ' || *iter == '\t')
        iter++;

    if (isalpha(*iter) || *iter == '_') {
        char *bufbase, *buf;
        bufbase = buf = malloc(strlen(iter));

        while (isalpha(*iter) || *iter == '_')
            *buf++ = *iter++;
        *buf = '\0';

        *iter_p = iter;
        if (!strcmp(bufbase, "let")) {
            free(bufbase);
            return (fx_tok){FX_TOKTYPE_LET, NULL};
        }
        else
            return (fx_tok){FX_TOKTYPE_SYMBOL, bufbase};
    }
    else if (*iter == '=') {
        *iter_p = ++iter;
        return (fx_tok){FX_TOKTYPE_EQUAL, NULL};
    }
    else if (*iter == ';' && *(iter + 1) == ';') {
        *iter_p = iter + 2;
        return (fx_tok){FX_TOKTYPE_DSCOLON, NULL};
    }
    else if (*iter == '\n') {
        while (*iter++ == '\n');
        *iter_p = --iter;
        return (fx_tok){FX_TOKTYPE_EOL, NULL};
    }
    else if (*iter == '\'' || *iter == '\"') {
        char pair = *iter++;
        char *bufbase, *buf;
        bufbase = buf = malloc(strlen(iter));

        while (*iter != pair)
            *buf++ = *iter++;
        *buf = '\0';
        iter++;

        *iter_p = iter;
        return (fx_tok){FX_TOKTYPE_STRING, bufbase, FX_VARTYPE_STRING};
    }
    else if (isdigit(*iter)) {
        char *bufbase, *buf;
        bufbase = buf = malloc(strlen(iter));

        while (isdigit(*iter))
            *buf++ = *iter++;
        *buf = '\0';

        *iter_p = iter;
        return (fx_tok){FX_TOKTYPE_INT, bufbase, FX_VARTYPE_INT};
    }

    return (fx_tok){FX_TOKTYPE_EOF, NULL};
}
