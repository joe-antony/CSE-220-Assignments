#include "unit_tests.h"
#include "hw7.h"
int main() { 
    matrix_sf *A = copy_matrix(3, 4, (int[]){-4, 18, 6, 7, 10, -14, 29, 8, 21, -99, 0, 7});
    matrix_sf *B = copy_matrix(3, 4, (int[]){10, 9, -2, -33, 22, 44, 10, 12, 72, 52, -88, -9});
    matrix_sf *C = add_mats_sf(A, B);
    free(A);
    free(B);
    free(C);
    return 0;
}
