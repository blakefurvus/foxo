#ifndef FX_LEXER_H
#define FX_LEXER_H

#include <string.h>
#include <ctype.h>
#include "tok.h"
fx_tok fx_next_tok(char **iter_p);

#endif
