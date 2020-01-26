#include "tok.h"

void fx_free_tok(fx_tok *tok)
{
    if (tok->val)
        free(tok->val);
}

void fx_print_tok(fx_tok *tok)
{
    printf("(%s", fx_toktype_str[tok->type]);

    if (tok->val)
        printf(", '%s'", tok->val);

    printf(", %s", fx_vartype_str[tok->var_type]);

    puts(")");
}
