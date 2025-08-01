/* Siddharth Korukonda
   CSE 220.01
   115607752
*/

#include "global.h"


int SparseMatrix(int row, int col, int** M, int** S){
    /* Edge case where matrix pointers are null. Return value of -2 indicates that even before we can calculate if the matrix is a sparse matrix or not, the
       matrix itself is invalid. Therefore, I created a new return value to indicate that the matrix itself is invalid to separate all edge cases and to
       make debugging easier. Check README.md file for more information
    */ 
    if (M == NULL || S == NULL) {
        // Indicates that there is no matrix to begin with
        return -2;
    }

    /* Edge case where the matrix dimensions are invalid. Return value of -2 indicates that even before we can calculate if the matrix is a sparse matrix or
       not, the matrix itself is invalid. Therefore, I created a new return value to indicate that the matrix itself is invalid to separate all edge cases 
       and to make debugging easier. Check README.md file for more information
    */ 
    if (row <= 0 || col <= 0) {
        // Indicates that there is no matrix to begin with
        return -2;
    }

    /* Edge case to see if the matrix rows are allocated properly. This loop checks if memory for the rows of matrix M is allocated properly, and if its 
       not, then there is a structural error with matrix M, returning -2. Check README.md file for more information
    */
    for (int i=0; i<row; i++) {
        // Conditional to check if the memory of the current row of matrix M is NULL or not
        if (*(M+i) == NULL) {
            // Indicates that there is a structural error with matrix M
            return -2;
        }
    }

    /* Edge case to see if the matrix rows are allocated properly. This loop checks if memory for the rows of matrix S is allocated properly, and if its not, 
       then there is a structural error with matrix S, returning -2. Check README.md file for more information
    */
    for (int i=0; i<3; i++) {
        // Conditional to check if the memory of the current row of matrix S is NULL or not
        if (*(S+i) == NULL) {
            // Indicates that there is a structural error with matrix S
            return -2;
        }
    }
    
    // Initializes the count of the non-zero elements in a matrix to later compare if the matrix is a sparse matrix or not
    int count = 0;
    // Initializes the max number of non-zero elements in a matrix to later compare if the matrix is a sparse matrix or not
    int max = 0;

    /* Conditional to assign the max value of non-zero elements to either the row count or the column count, depending on what is greater. The max value is 
       set to the greater value between the row count and the column count because we don't know the exact number of non-zero elements inside the matrix, 
       but we know for sure that it cannot exceed the number of rows or columns in the matrix. By setting the max value to the greater value between the row
       count and the column count, we can safely iterate through the matrix and find out if it is a sparse matrix or not without causing an overflow
    */
    if (row > col) {
        /* Since row count is greater than column count, the max value for non-zero elements has been set to the row count because there is a greater
           possibility that the number of non-zero elements in the rows is greater than the number of non-zero elements in the columns. This ensures safety
           without overflow
        */
        max = row;
    } else {
        /* Since column count is greater than row count, the max value for non-zero elements has been set to the column count because there is a greater
           possibility that the number of non-zero elements in the columns is greater than the number of non-zero elements in the rows. This ensures safety
           without overflow
        */
        max = col;
    }

    // A loop that iterates over each element of M to allow element-by-element check to see if the current value of M is non-zero or not
    for (int i=0; i<row; i++) { // Iterates through the rows of matrix M
        for (int j=0; j<col; j++) { // Iterates through the columns of matrix M
            // Conditional to check if the current element in matrix M is non-zero or not
            if (*(*(M+i)+j) != 0) {
                /* Conditional to check if the number of non-zero elements in matrix M exceeded the maximum number of non-zero elements in matrix M. If the
                   number of non-zero elements in matrix M exceeded the maximum number of non-zero elements in matrix M, then the function returns -1, which
                   indicates that the matrix is not a sparse matrix
                */
                if (count >= max) {
                    // Indicates that the matrix is not a sparse matrix
                    return -1;
                }

                // Stores the row index of the non-zero element
                *(*(S+0)+count) = i;
                // Stores the column index of the non-zero element
                *(*(S+1)+count) = j;
                // Stores the actual value of the non-zero element
                *(*(S+2)+count) = *(*(M+i)+j);
                // Increments the non-zero count by one after the non-zero element indices have been stored
                count++;
            }
        }
    }

    /* A loop to iterate beyond the count of non-zero elements up to the maximum number of non-zero elements so that the remaining entries inside the 
       matrix can be zeroed out. This allows the clean up of unused sparse matrices by avoiding garbage values
    */
    for (int i=count; i<max; i++) {
        // Zeros out the the remaining row indicies
        *(*(S+0)+i) = 0;
        // Zeros out the remaining column indicies
        *(*(S+1)+i) = 0;
        // Zeros out the actual value
        *(*(S+2)+i) = 0;
    }

    // Return the total number of non-zero entries stored in the sparse matrix
    return count; 
}


int Addition(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A) {
    /* Edge case where the matrix pointers are NULL. If any one of the matrix pointer are NULL, the matrix does not exist, and therefore, matrix addition 
       cannot be done to begin with. Therefore, I created a new return value to indicate that the matrix itself is invalid to separate all edge cases and to
       make debugging easier. Check README.md file for more information
    */
    if (M == NULL || N == NULL || A == NULL) {
        // Indicates that there is no matrix to begin with, which indicates a structural error
        return -4;
    }

    /* Edge case where the matrix dimensions are invalid. If the matrix dimension arguments are negative, then the matrix practically cannot exist. This means
       that matrix addition cannot be performed. Therefore, I used the same return value for the NULL matrix pointers to indicate that the matrix itself is 
       invalid to seperate all edge cases and to make debugging easier. Check README.md file for more information
    */
    if (RM <= 0 || CM <= 0 || RN <= 0 || CN <= 0 || RA <= 0 || CA <= 0) {
        // Indicates that there is no matrix to begin with, which indicates a structural error
        return -4;
    }

    /* Edge case to see if the matrix rows are allocated properly. This conditional checks if memory for the rows of matrix M is allocated properly, and if not, 
       the return value is -1. This indicates a structural error, and will return the custom error that I've assigned for structural errors in the matrices. 
       This custom error seperates all edge cases and makes debugging easier. Check README.MD file for more information. This loop iterates through each of the
       rows in matrix M
    */
    for (int i=0; i<RM; i++) {
        // Conditional to check if the memory of the current row of matrix M is NULL or not
        if (*(M+i) == NULL) {
            // Indicates that there is a structural error with matrix M
            return -4;
        }
    }

    /* Edge case to see if the matrix rows are allocated properly. This conditional checks if memory for the rows of matrix N is allocated properly, and if not, 
       the return value is -4. This indicates a structural error, and will return the custom error that I've assigned for structural errors in the matrices. 
       This custom error seperates all edge cases and makes debugging easier. Check README.MD file for more information. This loop iterates through each of the
       rows in matrix N
    */
    for (int i=0; i<RN; i++) {
        // Conditional to check if the memory of the current row of matrix N is NULL or not
        if (*(N+i) == NULL) {
            // Indicates that there is a structural error with matrix N
            return -4;
        }
    }

    /* Edge case to see if the matrix rows are allocated properly. This conditional checks if memory for the rows of matrix A is allocated properly, and if not, 
       the return value is -4. This indicates a structural error, and will return the custom error that I've assigned for structural errors in the matrices. 
       This custom error seperates all edge cases and makes debugging easier. Check README.MD file for more information. This loop iterates through each of the
       rows in matrix N
    */
    for (int i=0; i<RA; i++) {
        // Conditional to check if the memory of the current row of matrix A is NULL or not
        if (*(A+i) == NULL) {
            // Indicates that there is a strcutural error with matrix A
            return -4;
        }
    }

    /* This portion of the code iterates through each of the elements in matrix A and zeros out all the values of A so that all the garbage values of matrix A 
       are defined
    */
    for (int i=0; i<RA; i++) {
        for (int j=0; j<CA; j++) {
            // Zeros out all the values of matrix A
            *(*(A+i)+j) = 0;
        }
    }

    /* This portion of the code is the first case of matrix addition: matrices M and N share the exact same dimensions. This allows for easy, straightforward
       addition. The first conditional checks if the rows of matrices M and N, and the columns of matrices M and N, are the same
    */
    if (RM == RN && CM == CN) {
        // This conditional checks a subcase where A is large enough to store the full result
        if (RA >= RM && CA >= CM) {
            /* Two loops to iterate through each of the values matrix A and perform a fill matrix addition using the values at the exact same places in matrix M 
               and matrix N. We use RM and CM because the sizes of matrix M and N are the same.
            */
            for (int i=0; i<RM; i++) {
                for (int j=0; j<CM; j++) {
                    // Performs matrix addition and stores the value in matrix A
                    *(*(A+i)+j) = *(*(M+i)+j) + *(*(N+i)+j);
                }
            }

            // This conditional checks if matrix A is an exact fit, indicating that simple matrix addition was done properly without any unused elements
            if (RA == RM && CA == CM) {
                // Indicates that matrix A was an exact fit
                return 1;
            }

            // Indicates that matrix A was oversized, which means simple matrix addition was done properly with usued elements
            return 2;
        }

        /* Checks the subcase where matrix A is too small. This means we need to store as much as possible. Therefore, we choose the minimum value of the row or
           column between matrix M or matrix A so that we store the maximum number of values that we can use for matrix addition without going overboard. This
           first of two sets of conditionals sets the row count needed for limited size matrix addition
        */
        int fullRows = 0;
        if (RA < RM) {
            fullRows = RA;
        } else {
            fullRows = RM;
        }

        // This next set of conditionals (second of two) sets the column count needed for limited size matrix addition
        int fullCols = 0;
        if (CA < CM) {
            fullCols = CA;
        } else {
            fullCols = CM;
        }

        /* The next two loops are used to iterate through each value of matrix A and compute the partial sum matrix using the values at the exact same positions
           in matrices M and N
        */
        for (int i=0; i<fullRows; i++) {
            for (int j=0; j<fullCols; j++) {
                // Performs matrix adition and stores the values in matrix A
                *(*(A+i)+j) = *(*(M+i)+j) + *(*(N+i)+j);
            }
        }

        // Indicates that a partial sum matrix has been computed
        return -3;
    }

    /* The next portion of the code checks another case in matrix addition: matrices M and N have different sizes, which in this case, the function should only
       add the values in the overlapping region. Therefore, we need to find the minimum value of the row or column between matrices M and N because the size of
       the smaller matrix is less than the size of the larger matrix, so the smaller matrix is bound to fit inside the larger matrix, indicating overlap. The 
       first of two sets of conditionals determine the minimum row or column number to faciliate matrix addition over the overlapped region
    */
    int overlapRows = 0;
    if (RM < RN) {
        overlapRows = RM;
    } else {
        overlapRows = RN;
    }

    // This next set of conditionals (second of two) sets the column count needed for overlapping matrix addition
    int overlapCols = 0;
    if (CM < CN) {
        overlapCols = CM;
    } else {
        overlapCols = CN;
    }

    /* This is a subcase to check if matrix A is big enough to store the full matrix sum of the overlapped section of the matrices. The conditional first checks
       if matrix A is larger than the size of the overlapping region, and then the next two loops are used to iterate through each value of matrix A and compute 
       the sum using the values at the exact same positions in matrices M and N
    */
    if (RA >= overlapRows && CA >= overlapCols) {
        // Iterates through each of the elements in matrix A
        for (int i=0; i<overlapRows; i++) {
            for (int j = 0; j < overlapCols; j++) {
                // Performs matrix addition and stores the values in matrix A
                *(*(A+i)+j) = *(*(M+i)+j) + *(*(N+i)+j);
            }
        }
        
        // Indicates that the full sum obtained by matrix addition being performed on the overlapping region is stored
        return -1;

    }

    /* Checks the subcase where matrix A is too small. This means we need to store as much as possible. Therefore, we choose the minimum value of the row or
       column between matrix M or matrix A so that we store the maximum number of values that we can use for matrix addition on the overlapping region without 
       going overboard. This first of two sets of conditionals sets the row count needed for limited size overlapped region matrix addition
    */
    int partialRows = 0;
    if (RA < overlapRows) {
        partialRows = RA;
    } else {
        partialRows = overlapRows;
    }

    // This next set of conditionals (second of two) sets the column count needed for limited size overlapped region matrix addition
    int partialCols = 0;
    if (CA < overlapCols) {
        partialCols = CA;
    } else {
        partialCols = overlapCols;
    }

    /* The next two loops are used to iterate through each value of matrix A and compute the partial sum using the values at the exact same positions in
        matrices M and N
    */
    for (int i=0; i<partialRows; i++) {
        for (int j=0; j<partialCols; j++) {
            // Performs matrix addition and stores the values in matrix A
            *(*(A+i)+j) = *(*(M+i)+j) + *(*(N+i)+j);
        }
    }

    // Indicates that a partial sum matrix using different sizes of matrices M and N has been computed
    return -2;
}


int Multiplication(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A) {
    /* Edge case where the matrix pointers are NULL. If any one of the matrix pointer are NULL, the matrix does not exist, and therefore, matrix multiplication 
       cannot be done to begin with. Therefore, I created a new return value to indicate that the matrix itself is invalid to separate all edge cases and to
       make debugging easier. Check README.md file for more information
    */
    if (M == NULL || N == NULL || A == NULL) {
        // Indicates that there is no matrix to begin with, indicating a structural error
        return -4;
    }

    /* Edge case where the matrix dimensions are invalid. If the matrix dimension arguments are negative, then the matrix practically cannot exist. This means
       that matrix addition cannot be performed. Therefore, I used the same return value for the NULL matrix pointers to indicate that the matrix itself is 
       invalid to seperate all edge cases and to make debugging easier. Check README.md file for more information
    */
    if (RM <= 0 || CM <= 0 || RN <= 0 || CN <= 0 || RA <= 0 || CA <= 0) {
        // Indicates that there is no matrix to begin with, indicating a structural error
        return -4;
    }

    /* Edge case to see if the matrix rows are allocated properly. This conditional checks if memory for the rows of matrix M is allocated properly, and if not, 
       the return value is -1. This indicates a structural error, and will return the custom error that I've assigned for structural errors in the matrices. 
       This custom error seperates all edge cases and makes debugging easier. Check README.MD file for more information. This loop iterates through each of the
       rows in matrix M
    */
    for (int i=0; i<RM; i++) {
        // Conditional to check if the memory of the current row of matrix M is NULL or not
        if (*(M+i) == NULL) {
            // Indicates that there is a structural error with matrix M
            return -4;
        }
    }

    /* Edge case to see if the matrix rows are allocated properly. This conditional checks if memory for the rows of matrix N is allocated properly, and if not, 
       the return value is -4. This indicates a structural error, and will return the custom error that I've assigned for structural errors in the matrices. 
       This custom error seperates all edge cases and makes debugging easier. Check README.MD file for more information. This loop iterates through each of the
       rows in matrix N
    */
    for (int i=0; i<RN; i++) {
        // Conditional to check if the memory of the current row of matrix N is NULL or not
        if (*(N+i) == NULL) {
            // Indicates that there is a structural error with matrix N
            return -4;
        }
    }

    /* Edge case to see if the matrix rows are allocated properly. This conditional checks if memory for the rows of matrix N is allocated properly, and if not, 
       the return value is -4. This indicates a structural error, and will return the custom error that I've assigned for structural errors in the matrices. 
       This custom error seperates all edge cases and makes debugging easier. Check README.MD file for more information. This loop iterates through each of the
       rows in matrix N
    */
    for (int i=0; i<RA; i++) {
        // Conditional to check if the memory of the current row of matrix A is NULL or not
        if (*(A+i) == NULL) {
            // Indicates that there is a structural error with matrix A
            return -4;
        }
    }

    /* This portion of the code iterates through each of the elements in matrix A and zeros out all the values of A so that all the garbage values of matrix A 
       are defined.
    */
    for (int i=0; i<RA; i++) {
        for (int j=0; j<CA; j++) {
            // Zeros out all the values of matrix A
            *(*(A+i)+j) = 0;
        }
    }

    /* This portion of the code checks the first case of matrix multiplication: the row count of matrix N matches the column count of matrix M. This allows for
       full matrix multiplication. The first conditional checks exactly this
    */
    if (CM == RN) {
        /* This conditional checks if matrix A is large enough to store the full result*/
        if (RA >= RM && CA >= CN) {
            /* Two loops to iterate through each of the values matrix A and perform a fill matrix multiplication using the values at the exact same places in 
               matrix M and perform matrix multiplication. We use RM and CN because these are the dimensions used when performing matrix multiplication
            */
            for (int i=0; i<RM; i++) {
                for (int j=0; j<CN; j++) {
                    // This variable initializes the dot product result for the ith row of matrix M and the jth row of matrix N
                    int dot = 0;

                    // This for loop iterates over the shared dimension between matrices M and N in order to compute the dot product
                    for (int k=0; k<CM; k++) {
                        // Calculates the dot product
                        dot += *(*(M+i)+k) * *(*(N+k)+j);
                    }

                    // Stores the dot product in the designated spot in matrix A
                    *(*(A+i)+j) = dot;
                }
            }
            
            // This conditional checks if matrix A is an exact fit, indicating that simple matrix multiplication was done properly without any unused elements
            if (RA > RM || CA > CN) {
                // Indicates that matrix A was an exact fit
                return 2;
            } else {
                // Indicates that matrix A was oversized, which means simple matrix multiplication was done properly with usued elements
                return 1;
            }
        }

        /* Checks the subcase where matrix A is too small. This means we need to store as much as possible. Therefore, we choose the minimum value of the row or
           column between matrix M or matrix A so that we store the maximum number of values that we can use for matrix multiplication without going overboard. 
           This first of two sets of conditionals sets the row count needed for limited size matrix multiplication
        */
        int fullRows = 0;
        if (RA < RM) {
            fullRows = RA;
        } else {
            fullRows = RM;
        }

        // This next set of conditionals (second of two) sets the column count needed for limited size matrix multiplication
        int fullCols = 0;
        if (CA < CN) {
            fullCols = CA;
        } else {
            fullCols = CN;
        }

        /* The next two loops are used to iterate through each value of matrix A and compute the partial product matrix using the values at the exact same 
           positions in matrices M and N
        */
        for (int i=0; i<fullRows; i++) {
            for (int j=0; j<fullCols; j++) {
                // This variable initializes the dot product result for the ith row of matrix M and the jth row of matrix N
                int dot = 0;

                // This for loop iterates over the shared dimension between matrices M and N in order to compute the dot product
                for (int k=0; k<CM; k++) {
                    // Calculates the dot product
                    dot += *(*(M+i)+k) * *(*(N+k)+j);
                }

                // Stores the dot product in the designated spot in matrix A
                *(*(A+i)+j) = dot;
            }
        }

        // Indicates that a partial product matrix has been computed
        return -3;
    }

    /* This portion of the code checks the second case for matrix multiplication: the row count of matrix N doesn't match the column count of matrix M. In this 
       case, the function should only multiply the values in the overlapping region. Therefore, we need to find the minimum value of the shared dimension 
       between 
    matrices M and N because the size of the smaller matrix is less than the size of the larger matrix, so the smaller matrix is bound to fit inside the larger
       matrix, indicating overlap.
    */
    int overlap = 0;
    if (CM < RN) {
        overlap = CM;
    } else {
        overlap = RN;
    }

    if (RA >= RM && CA >= CN) {
        for (int i = 0; i < RM; i++) {
            for (int j = 0; j < CN; j++) {
                int sum = 0;
                for (int k = 0; k < overlap; k++) {
                    sum += *(*(M + i) + k) * *(*(N + k) + j);
                }
                *(*(A + i) + j) = sum;
            }
        }
        return -1; // Intersection product fits
    }

    int partialRows = 0; // Compute rows that fit
    if (RA < RM) {
        partialRows = RA;
    } else {
        partialRows = RM;
    }

    int partialCols = 0; // Compute cols that fit
    if (CA < CN) {
        partialCols = CA;
    } else {
        partialCols = CN;
    }

    for (int i = 0; i < partialRows; i++) {
        for (int j = 0; j < partialCols; j++) {
            int sum = 0;
            for (int k = 0; k < overlap; k++) {
                sum += *(*(M + i) + k) * *(*(N + k) + j);
            }
            *(*(A + i) + j) = sum;
        }
    }

    return -2; // Partial intersection product stored
}


int Transpose(int RA, int RC, int RAT, int CAT, int** A, int** AT) {
    if (A == NULL || AT == NULL) { // Check for null pointers
        return -1;
    }

    if (RA <= 0 || RC <= 0 || RAT <= 0 || CAT <= 0) { // Check for invalid dimensions
        return -1;
    }

    for (int i = 0; i < RA; i++) { // Validate rows of A
        if (*(A + i) == NULL) {
            return -1;
        }
    }

    for (int i = 0; i < RAT; i++) { // Validate rows of AT
        if (*(AT + i) == NULL) {
            return -1;
        }
    }

    for (int i = 0; i < RAT; i++) { // Zero out AT
        for (int j = 0; j < CAT; j++) {
            *(*(AT + i) + j) = 0;
        }
    }

    if (RAT > RC && CAT > RA) { // Oversized transpose
        for (int i = 0; i < RA; i++) {
            for (int j = 0; j < RC; j++) {
                *(*(AT + j) + i) = *(*(A + i) + j);
            }
        }
        return 2;
    }

    if (RAT == RC && CAT == RA) { // Exact-fit transpose
        for (int i = 0; i < RA; i++) {
            for (int j = 0; j < RC; j++) {
                *(*(AT + j) + i) = *(*(A + i) + j);
            }
        }
        return 1;
    }

    for (int i = 0; i < RA; i++) { // Partial transpose
        for (int j = 0; j < RC; j++) {
            if (j < RAT && i < CAT) {
                *(*(AT + j) + i) = *(*(A + i) + j);
            }
        }
    }

    return -1; // Partial transpose stored
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