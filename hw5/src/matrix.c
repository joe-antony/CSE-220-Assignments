#include "global.h"


int SparseMatrix(int row, int col, int** M, int** S){
    // TO BE IMPLEMENTED
    abort();
}
int Addition(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A){
   // TO BE IMPLEMENTED
    abort();
}
int Multiplication(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A){
   // TO BE IMPLEMENTED
    abort();
}
int Transpose(int RA, int RC, int RAT, int CAT, int** A, int** AT){
    // TO BE IMPLEMENTED
    abort();
}

// Helper functions for Testing
int** initializeMatrix(int n, int m, int* values){
    int** ret = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        ret[i] = (int*)malloc(m*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ret[i][j] = values[i*m+j];
        }
    }
    return ret;
}

void freeMatrix(int n, int** M){
    for(int i=0; i<n; i++){
        free(M[i]);
    }
    free(M);
}

#ifndef STUDENT_MAIN /* Do not remove this line*/
int main(int argc, char* argv[]){
    (void)argc;
	(void)argv;

    return 0;
}
#endif