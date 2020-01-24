#include "foxo.h"

char *rf(char *fpath) {
    FILE *f = fopen(fpath, "r");
    if (!f)
        return NULL;

    fseek(f, 0, SEEK_END);
    const int len = ftell(f);
    rewind(f);

    char *ret = malloc(len + 1);
    fread(ret, 1, len, f);

    fclose(f);
    return ret;
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        char *src = rf(argv[1]);
        if (!src) {
            puts("Failed to open file");
            return EXIT_FAILURE;
        }

        fx_comp_state state = fx_create_comp_state(src);

        fx_node node;
        while ((node = fx_next_node(&state)).tok.type) {
            fx_print_node(&node, 0);
            fx_free_node(&node);
        }

        fx_free_comp_state(&state);
    }
    else if (argc == 3) {
        char *src = rf(argv[2]);
        if (!src) {
            puts("Failed to open file");
            return EXIT_FAILURE;
        }

        fx_comp_state state = fx_create_comp_state(src);

        if (!strcmp(argv[1], "lex")) {
            fx_tok tok;
            while ((tok = fx_next_tok(&state)).type) {
                fx_print_tok(&tok);
                fx_free_tok(&tok);
            }
        }
        else if (!strcmp(argv[1], "parse")) {
            fx_node node;
            while ((node = fx_next_node(&state)).tok.type) {
                fx_print_node(&node, 0);
                fx_free_node(&node);
            }
        }

        fx_free_comp_state(&state);
    }
}
