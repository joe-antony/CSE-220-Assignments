#include "unit_tests.h"
#include "hw7.h"
int main() { 
    matrix_sf *G = copy_matrix(6, 4, (int[]){83, -22, 56, -1, 97, 94, 135, -10, 84, 40, -83, -4, 79, 28, 52, -101, 138, 146, 99, 0, -23, -73, -39, -47});
    matrix_sf *D = copy_matrix(4, 7, (int[]){-77, -20, 111, -2, 41, 117, 118, 21, -29, -45, 135, 98, 54, 131, 54, 1, 80, 143, -127, 148, 114, -81, 87, -33, -2, -6, 115, 59});
    matrix_sf *Z = mult_mats_sf(G, D);
    free(G);
    free(D);
    free(Z);
    return 0;
}
