#ifndef FX_COMPILER_H
#define FX_COMPILER_H

#include "parser.h"

fx_vartype fx_get_ftype(char *fname);
void fx_set_ftype(char *fname, fx_vartype ftype);

void fx_prepare_comp();
void fx_finish_comp();

void fx_compile_node(fx_node *node);

#endif
