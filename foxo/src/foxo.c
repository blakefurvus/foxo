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
        char *srcbase, *src;
        srcbase = src = rf(argv[1]);

        if (!srcbase) {
            puts("Failed to open file");
            return EXIT_FAILURE;
        }

        fx_prepare_comp();

        fx_node node;
        while ((node = fx_next_node(&src)).tok.type) {
            fx_compile_node(&node);
            fx_free_node(&node);
        }

        fx_finish_comp();
        free(srcbase);
    }
    else {
        char *srcbase, *src;

        while (1) {
            srcbase = src = readline(" > ");
            if (!strcmp(src, "exit"))
                break;
            add_history(srcbase);

            fx_node node;
            while ((node = fx_next_node(&src)).tok.type) {
                fx_print_node(&node, 0);
                fx_free_node(&node);
            }

            free(srcbase);
        }

        free(srcbase);
    }
}
