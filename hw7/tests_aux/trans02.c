#include "unit_tests.h"
#include "hw7.h"
int main() { 
    matrix_sf *X = copy_matrix(6, 3, (int[]){121, -1, 128, 78, -138, 138, -61, 51, -35, -84, 125, -83, -78, 138, 2, 81, -5, -36});
    matrix_sf *G = transpose_mat_sf(X);
    free(X);
    free(G);
    return 0;
}
