#include "compiler.h"

struct {
    FILE *out;
    char fnames[60][60];
    fx_vartype ftypes[60];
} fx_comp_state = {NULL, {0}, {0}};

fx_vartype fx_get_ftype(char *fname)
{
    for (unsigned int i = 0; i < 60; i++) {
        if (!strcmp(fx_comp_state.fnames[i], fname))
            return fx_comp_state.ftypes[i];
    }

    return FX_VARTYPE_ANY;
}

void fx_set_ftype(char *fname, fx_vartype ftype)
{
    for (unsigned int i = 0; i < 60; i++)
        if (!strcmp(fx_comp_state.fnames[i], fname)) {
            fx_comp_state.ftypes[i] = ftype;
            return;
        }

    for (unsigned int i = 0; i < 60; i++) {
        if (!strcmp(fx_comp_state.fnames[i], "")) {
            strcpy(fx_comp_state.fnames[i], fname);
            fx_comp_state.ftypes[i] = ftype;
            return;
        }
    }
}

void fx_prepare_comp()
{
    fx_comp_state.out = fopen("fx.c", "w");
    if (!fx_comp_state.out) {
        puts("Failed to prepare for compile");
        exit(EXIT_FAILURE);
    }

    fprintf(fx_comp_state.out, "#include <stdio.h>\n");
}

void fx_finish_comp()
{
    fclose(fx_comp_state.out);
    system("clang fx.c -o a.out");
    remove("fx.c");
}

void fx_compile_node(fx_node *node)
{
    switch (node->tok.type) {
        case FX_TOKTYPE_LET:
            fx_set_ftype(node->tok.val, node->tok.var_type);

            fprintf(
                fx_comp_state.out, "%s %s() {",
                fx_vartype_ret[node->tok.var_type],
                node->tok.val
            );

            for (unsigned int i = 0; i < node->len; i++)
                fx_compile_node(node->children + i);

            if (!strcmp(node->tok.val, "main"))
                fprintf(fx_comp_state.out, "return 0;");

            fprintf(fx_comp_state.out, "}");
            break;

        case FX_TOKTYPE_SYMBOL:
            if (!strcmp(node->tok.val, "print")) {
                fprintf(fx_comp_state.out, "printf(\"");

                for (unsigned int i = 0; i < node->len; i++) {
                    if (node->children[i].tok.type == FX_TOKTYPE_SYMBOL)
                        fprintf(
                            fx_comp_state.out, "%s",
                            fx_vartype_fmt[
                                fx_get_ftype(node->children[i].tok.val)
                            ]
                        );
                    else
                        fprintf(
                            fx_comp_state.out, "%s",
                            fx_vartype_fmt[node->children[i].tok.var_type]
                        );
                }
                fprintf(fx_comp_state.out, "\\n\"");

                for (unsigned int i = 0; i < node->len; i++) {
                    fprintf(fx_comp_state.out, ", ");
                    fx_compile_node(node->children + i);
                }

                fprintf(fx_comp_state.out, ");");
            }
            else
                fprintf(fx_comp_state.out, "%s()", node->tok.val);
            break;

        case FX_TOKTYPE_RETURN:
            fprintf(fx_comp_state.out, "return ");
            fx_compile_node(node->children);
            fprintf(fx_comp_state.out, ";");
            break;

        case FX_TOKTYPE_INT:
            fprintf(fx_comp_state.out, "%s" ,node->tok.val);
            break;

        case FX_TOKTYPE_STRING:
            fprintf(fx_comp_state.out, "\"%s\"" ,node->tok.val);
            break;

        default:
            break;
    }
}
