#include "tok.h"

void fx_free_tok(fx_tok *tok)
{
    if (tok->val)
        free(tok->val);
}

void fx_print_tok(fx_tok *tok)
{
    printf("fx_tok(%s", fx_toktype_str[tok->type]);
    if (tok->val)
        printf(", '%s'", tok->val);
    puts(")");
}
