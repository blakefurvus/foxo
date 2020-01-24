#ifndef FX_PARSE_H
#define FX_PARSE_H

#include "lex.h"
#include "node.h"

// Parses the next node
fx_node fx_next_node(fx_comp_state *state);

#endif
