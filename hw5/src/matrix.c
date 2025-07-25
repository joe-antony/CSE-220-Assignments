#include "global.h"


int SparseMatrix(int** M, int** S, int* D){
    // TO BE IMPLEMENTED
    abort();
}
int Addition(int** M, int** N, int** A, int* D){
   // TO BE IMPLEMENTED
    abort();
}
int Multiplication(int** M, int** N, int** A, int* D){
   // TO BE IMPLEMENTED
    abort();
}
int Transpose(int** A, int** AT, int* D){
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
    
    // Add your test cases here to validate the functionality of the implemented functions
    return 0;
}
#endif