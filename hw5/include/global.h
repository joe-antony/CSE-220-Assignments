/* DO NOT ADD CODE TO THIS FILE. IT WILL BE REPLACED DURING GRADING. */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int SparseMatrix(int row, int col, int** M, int** S);
int Addition(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A);
int Multiplication(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A);
int Transpose(int RA, int RC, int RAT, int CAT, int** A, int** AT);
