#ifndef FX_LEX_H
#define FX_LEX_H

#include <string.h>
#include <ctype.h>
#include "comp_state.h"
#include "tok.h"

// Lexes the next token
fx_tok fx_next_tok(fx_comp_state *state);
fx_tok fx_peek_tok(fx_comp_state *state);

#endif
