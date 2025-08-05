#include "unit_tests.h"
#include "hw7.h"
int main() { 
    bst_sf *root = NULL;
    char names[] = "GTHRNBVCUJELMOPSQZA";
    matrix_sf *mats[strlen(names)];
    for (size_t i = 0; i < strlen(names); i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    free_bst_sf(root);
    return 0;
}
