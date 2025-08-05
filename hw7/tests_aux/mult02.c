#include "unit_tests.h"
#include "hw7.h"
int main() { 
    matrix_sf *U = copy_matrix(7, 1, (int[]){-38, 4, 46, -14, -102, -72, -27});
    matrix_sf *N = copy_matrix(1, 5, (int[]){52, 65, -94, -73, -48});
    matrix_sf *Z = mult_mats_sf(U, N);
    free(U);
    free(N);
    free(Z);
    return 0;
}
