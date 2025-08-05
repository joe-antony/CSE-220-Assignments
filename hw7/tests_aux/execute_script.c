#include "hw7.h"

int main(int argc, char *argv[]) {    
    (void)argc;
    char script[200];
    sprintf(script, "tests.in/%s.txt", argv[1]);
    assert(access(script, F_OK) == 0);
    matrix_sf *mat = execute_script_sf(script);
    print_matrix_sf(mat);
    fflush(stdout);
    free(mat);
    return 0;
}



