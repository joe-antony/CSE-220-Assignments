/* Siddharth Korukonda
   CSE 220.01
   115607752
*/

#include "global.h"
#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/


// Sparse Matrix Test Cases
Test(base_suite, SparseMatrix_generic, .description="Generic test case that returns count over 0") {
    int** M = initializeMatrix(4, 2, (int[]){0,4,0,5,0,0,2,0});
    int** S_act = initializeMatrix(3, 4, (int[]){0,0,0,0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 4, (int[]){0,1,3,0,1,1,0,0,4,5,2,0});
    int row = 4;
    int col = 2;
    int ret_act = SparseMatrix(row, col, M, S_act);
    int ret_exp = 3;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 4), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(row, M); 
    freeMatrix(3, S_act); 
    freeMatrix(3, S_exp);
}

Test(base_suite, sparsematrix_null_matrix_check, .description="M or S is NULL returns -2") {
    int row = 2;
    int col = 1;

    int** M_null = NULL;
    int** S_valid = initializeMatrix(3, 1, (int[]){0, 0, 0});
    int ret_M_null = SparseMatrix(row, col, M_null, S_valid);
    cr_expect_eq(ret_M_null, -2, "Expected -2 when M is NULL, got %d.", ret_M_null);
    freeMatrix(3, S_valid);

    int** M_valid = initializeMatrix(2, 1, (int[]){1, 0});
    int** S_null = NULL;
    int ret_S_null = SparseMatrix(row, col, M_valid, S_null);
    cr_expect_eq(ret_S_null, -2, "Expected -2 when S is NULL, got %d.", ret_S_null);
    freeMatrix(2, M_valid);
}


Test(base_suite, sparse_invalid_dimensions, .description="Row or Col <= 0 returns -2") {
    int** M = initializeMatrix(0, 0, NULL);
    int** S_act = initializeMatrix(3, 1, (int[]){0,0,0});
    int row = 0;
    int col = 0;
    int ret_act = SparseMatrix(row, col, M, S_act);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Expected -2 for row or col <= 0, got %d.", ret_act);
    freeMatrix(3, S_act);
}

Test(base_suite, sparsematrix_null_row_check, .description="Any row in M or S is NULL returns -2") {
    int row = 3;
    int col = 2;

    int** M = initializeMatrix(row, col, (int[]){1, 2, 3, 4, 5, 6});
    free(M[1]);
    M[1] = NULL;
    int** S_valid = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int ret_M_row_null = SparseMatrix(row, col, M, S_valid);
    cr_expect_eq(ret_M_row_null, -2, "Expected -2 when M row is NULL, got %d.", ret_M_row_null);
    free(M[0]); 
    free(M[2]); 
    free(M);
    freeMatrix(3, S_valid);

    int** M_valid = initializeMatrix(2, 2, (int[]){1,0,0,2});
    int** S = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    free(S[2]);
    S[2] = NULL;
    int ret_S_row_null = SparseMatrix(2, 2, M_valid, S);
    cr_expect_eq(ret_S_row_null, -2, "Expected -2 when S row is NULL, got %d.", ret_S_row_null);
    freeMatrix(2, M_valid);
    free(S[0]); 
    free(S[1]); 
    free(S);
}


Test(base_suite, SparseMatrix_not_sparse, .description="Matrix is not sparse, returns -1") {
    int** M = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** S_act = initializeMatrix(3, 2, (int[]){0,0,0,0,0,0});
    int row = 2;
    int col = 2;
    int ret_act = SparseMatrix(row, col, M, S_act);
    int ret_exp = -1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    freeMatrix(row, M); 
    freeMatrix(3, S_act);
}

Test(base_suite, SparseMatrix_prioritize_structural_error, .description="Return -2 over -1 (structure invalid)") {
    int** M = NULL;
    int** S_act = initializeMatrix(3, 2, (int[]){0,0,0,0,0,0});
    int row = 2;
    int col = 2;
    int ret_act = SparseMatrix(row, col, M, S_act);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    freeMatrix(3, S_act);
}

Test(base_suite, SparseMatrix_max_equal, .description="Matrix with non-zero count equal to max(row, col)") {
    int** M = initializeMatrix(3, 3, (int[]){1,0,0,0,2,0,0,0,3});  // 3 non-zero
    int** S_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 3, (int[]){0,1,2,0,1,2,1,2,3});
    int row = 3;
    int col = 3;
    int ret_act = SparseMatrix(row, col, M, S_act);
    int ret_exp = 3;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.\n", ret_act, ret_exp);
    freeMatrix(row, M); 
    freeMatrix(3, S_act); 
    freeMatrix(3, S_exp);
}

Test(base_suite, SparseMatrix_all_zeros, .description="Matrix with all zero elements") {
    int** M = initializeMatrix(2, 3, (int[]){0,0,0,0,0,0});
    int** S_act = initializeMatrix(3, 3, (int[]){1,1,1,1,1,1,1,1,1});
    int** S_exp = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int row = 2;
    int col = 3;
    int ret_act = SparseMatrix(row, col, M, S_act);
    int ret_exp = 0;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, should be 0.\n", ret_act);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 3), "Sparse matrix should be all zeros.");
    freeMatrix(row, M); 
    freeMatrix(3, S_act); 
    freeMatrix(3, S_exp);
}


// Addition Test Cases
Test(base_suite, addition_exact_fit, .description="Exact fit of M+N into A") {
    int** M = initializeMatrix(2, 3, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(2, 3, (int[]){6,5,4,3,2,1});
    int** A_act = initializeMatrix(2, 3, (int[]){0,0,0,0,0,0});
    int** A_exp = initializeMatrix(2, 3, (int[]){7,7,7,7,7,7});
    int D[6] = {2,3,2,3,2,3};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 3), "Result matrix incorrect.");
    freeMatrix(2, M);
    freeMatrix(2, N);
    freeMatrix(2, A_act);
    freeMatrix(2, A_exp);
}

Test(base_suite, addition_oversized_A, .description="Oversized A container") {
    int** M = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** N = initializeMatrix(2, 2, (int[]){4,3,2,1});
    int** A_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 3, (int[]){5,5,0,5,5,0,0,0,0});
    int D[6] = {2,2,2,2,3,3};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 3), "Result matrix incorrect for oversized A.");
    freeMatrix(2, M);
    freeMatrix(2, N);
    freeMatrix(3, A_act);
    freeMatrix(3, A_exp);
}

Test(base_suite, addition_partial_same_size, .description="Partial result when A too small for full") {
    int** M = initializeMatrix(3, 3, (int[]){1,1,1,1,1,1,1,1,1});
    int** N = initializeMatrix(3, 3, (int[]){2,2,2,2,2,2,2,2,2});
    int** A_act = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int** A_exp = initializeMatrix(2, 2, (int[]){3,3,3,3});
    int D[6] = {3,3,3,3,2,2};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = -3;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "Partial same‐size result incorrect.");
    freeMatrix(3, M);
    freeMatrix(3, N);
    freeMatrix(2, A_act);
    freeMatrix(2, A_exp);
}

Test(base_suite, addition_full_overlap, .description="Full overlap for different M,N sizes") {
    int** M = initializeMatrix(2, 4, (int[]){1,1,1,1,2,2,2,2});
    int** N = initializeMatrix(3, 3, (int[]){3,3,3,3,3,3,3,3,3});
    int** A_act = initializeMatrix(2, 3, (int[]){0,0,0,0,0,0});
    int** A_exp = initializeMatrix(2, 3, (int[]){4,4,4,5,5,5});
    int D[6] = {2,4,3,3,2,3};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = -1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 3), "Full overlap result incorrect.");
    freeMatrix(2, M);
    freeMatrix(3, N);
    freeMatrix(2, A_act);
    freeMatrix(2, A_exp);
}

Test(base_suite, addition_partial_overlap, .description="Partial overlap for different M,N sizes") {
    int** M = initializeMatrix(3, 3, (int[]){1,2,3,4,5,6,7,8,9});
    int** N = initializeMatrix(4, 2, (int[]){1,1,1,1,1,1,1,1});
    int** A_act = initializeMatrix(1, 1, (int[]){0});
    int** A_exp = initializeMatrix(1, 1, (int[]){2});
    int D[6] = {3,3,4,2,1,1};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 1, 1), "Partial overlap result incorrect.");
    freeMatrix(3, M);
    freeMatrix(4, N);
    freeMatrix(1, A_act);
    freeMatrix(1, A_exp);
}

Test(base_suite, addition_null_matrix_check, .description="M, N, or A is NULL returns -4") {
    int D[6] = {2, 2, 2, 2, 2, 2};

    int** N = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** A1 = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int ret_null_M = Addition(D[0], D[1], D[2], D[3], D[4], D[5], NULL, N, A1);
    cr_expect_eq(ret_null_M, -4, "Expected -4 when M is NULL, got %d.", ret_null_M);
    freeMatrix(2, N);
    freeMatrix(2, A1);

    int** M = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** A2 = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int ret_null_N = Addition(D[0], D[1], D[2], D[3], D[4], D[5], M, NULL, A2);
    cr_expect_eq(ret_null_N, -4, "Expected -4 when N is NULL, got %d.", ret_null_N);
    freeMatrix(2, M); 
    freeMatrix(2, A2);

    int** M2 = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** N2 = initializeMatrix(2, 2, (int[]){4,3,2,1});
    int ret_null_A = Addition(D[0], D[1], D[2], D[3], D[4], D[5], M2, N2, NULL);
    cr_expect_eq(ret_null_A, -4, "Expected -4 when A is NULL, got %d.", ret_null_A);
    freeMatrix(2, M2); 
    freeMatrix(2, N2);
}

Test(base_suite, addition_null_row_check, .description="Any row of M, N, or A is NULL returns -4") {
    int D[6] = {3, 2, 3, 2, 3, 2};

    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    free(M[1]); M[1] = NULL;
    int** N1 = initializeMatrix(3, 2, (int[]){1,1,1,1,1,1});
    int** A1 = initializeMatrix(3, 2, (int[]){0,0,0,0,0,0});
    int ret_row_M_null = Addition(D[0], D[1], D[2], D[3], D[4], D[5], M, N1, A1);
    cr_expect_eq(ret_row_M_null, -4, "Expected -4 when M has a NULL row, got %d.", ret_row_M_null);
    free(M[0]); free(M[2]); free(M);
    freeMatrix(3, N1); freeMatrix(3, A1);

    int** M2 = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(3, 2, (int[]){1,1,1,1,1,1});
    free(N[2]); N[2] = NULL;
    int** A2 = initializeMatrix(3, 2, (int[]){0,0,0,0,0,0});
    int ret_row_N_null = Addition(D[0], D[1], D[2], D[3], D[4], D[5], M2, N, A2);
    cr_expect_eq(ret_row_N_null, -4, "Expected -4 when N has a NULL row, got %d.", ret_row_N_null);
    freeMatrix(3, M2); free(N[0]); free(N[1]); free(N); freeMatrix(3, A2);

    int** M3 = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** N3 = initializeMatrix(2, 2, (int[]){4,3,2,1});
    int** A3 = initializeMatrix(2, 2, (int[]){0,0,0,0});
    free(A3[0]); A3[0] = NULL;
    int D3[6] = {2,2,2,2,2,2};
    int ret_row_A_null = Addition(D3[0], D3[1], D3[2], D3[3], D3[4], D3[5], M3, N3, A3);
    cr_expect_eq(ret_row_A_null, -4, "Expected -4 when A has a NULL row, got %d.", ret_row_A_null);
    freeMatrix(2, M3); freeMatrix(2, N3); free(A3[1]); free(A3);
}

Test(base_suite, addition_invalid_dimensions, .description="Any dimension <= 0 returns -4") {
    int** M = initializeMatrix(0, 2, NULL); 
    int** N = initializeMatrix(1, 0, NULL);  
    int** A = initializeMatrix(0, 0, NULL);  
    int D[6] = {0,2,1,0,0,0}; 
    int ret_act = Addition(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A);
    int ret_exp = -4;
    cr_expect_eq(ret_act, ret_exp, "Expected -4 for any invalid dimension, got %d.", ret_act);
    freeMatrix(0, M);
    freeMatrix(1, N);
    freeMatrix(0, A);
}

Test(base_suite, addition_structural_priority, .description="Structural error overrides any size‐mismatch") {
    int** M = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** N = initializeMatrix(2, 2, (int[]){4, 3, 2, 1});
    int** A_act = initializeMatrix(1, 1, (int[]){0});
    free(M[0]);
    M[0] = NULL;
    int D[6] = {2, 2, 2, 2, 1, 1};
    int ret_act = Addition(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = -4;
    cr_expect_eq(ret_act, ret_exp, "Expected structural error (-4) to take priority, got %d", ret_act);
    free(M[1]);
    free(M);
    freeMatrix(2, N);
    freeMatrix(1, A_act);
}

Test(base_suite, addition_A_not_zeroed, .description="Ensure A is overwritten even if initially non-zero") {
    int** M = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** N = initializeMatrix(2, 2, (int[]){5,6,7,8});
    int** A_act = initializeMatrix(2, 2, (int[]){100,100,100,100});
    int** A_exp = initializeMatrix(2, 2, (int[]){6,8,10,12});
    int D[6] = {2,2,2,2,2,2};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5], M, N, A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "A was not overwritten correctly.");
    freeMatrix(2, M);
    freeMatrix(2, N);
    freeMatrix(2, A_act);
    freeMatrix(2, A_exp);
}


// Multiplication Test Cases
Test(base_suite, multiplication_case_exact_fit, .description="Matrices are compatible for multiplication with exact fit in A") {
    int** M = initializeMatrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    int** N = initializeMatrix(3, 2, (int[]){7, 8, 9, 10, 11, 12});
    int** A_act = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int** A_exp = initializeMatrix(2, 2, (int[]){58, 64, 139, 154});
    int D[6] = {2, 3, 3, 2, 2, 2};
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "Matrix contents incorrect.");
    freeMatrix(2, M); freeMatrix(3, N); freeMatrix(2, A_act); freeMatrix(2, A_exp);
}

Test(base_suite, multiplication_case_oversized_A, .description="Matrices are compatible, A is oversized") {
    int** M = initializeMatrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    int** N = initializeMatrix(3, 2, (int[]){7, 8, 9, 10, 11, 12});
    int** A_act = initializeMatrix(4, 4, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    int** A_exp = initializeMatrix(4, 4, (int[]){58, 64, 0, 0, 139, 154, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    int D[6] = {2, 3, 3, 2, 4, 4};
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 4, 4), "Matrix contents incorrect.");
    freeMatrix(2, M); freeMatrix(3, N); freeMatrix(4, A_act); freeMatrix(4, A_exp);
}

Test(base_suite, multiplication_case_partial_fit, .description="A too small for full product, partial result stored") {
    int** M = initializeMatrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    int** N = initializeMatrix(3, 2, (int[]){7, 8, 9, 10, 11, 12});
    int** A_act = initializeMatrix(1, 1, (int[]){0});
    int** A_exp = initializeMatrix(1, 1, (int[]){58});
    int D[6] = {2, 3, 3, 2, 1, 1};
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = -3;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 1, 1), "Matrix contents incorrect.");
    freeMatrix(2, M); freeMatrix(3, N); freeMatrix(1, A_act); freeMatrix(1, A_exp);
}

Test(base_suite, multiplication_case_overlap_fullfit, .description="M and N overlap, A big enough") {
    int** M = initializeMatrix(2, 4, (int[]){1, 2, 3, 4, 5, 6, 7, 8});
    int** N = initializeMatrix(3, 2, (int[]){1, 0, 0, 1, 1, 1});
    int** A_act = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int** A_exp = initializeMatrix(2, 2, (int[]){4, 5, 12, 13}); 
    int D[6] = {2, 4, 3, 2, 2, 2};
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = -1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, expected %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "Matrix contents incorrect.");
    freeMatrix(2, M); freeMatrix(3, N); freeMatrix(2, A_act); freeMatrix(2, A_exp);
}

Test(base_suite, multiplication_case_overlap_partial, .description="M and N overlap, A too small") {
    int** M = initializeMatrix(2, 4, (int[]){1, 2, 3, 4, 5, 6, 7, 8});
    int** N = initializeMatrix(3, 2, (int[]){1, 0, 0, 1, 1, 1});
    int** A_act = initializeMatrix(1, 1, (int[]){0});
    int** A_exp = initializeMatrix(1, 1, (int[]){4}); 
    int D[6] = {2, 4, 3, 2, 1, 1};
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, expected %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 1, 1), "Matrix contents incorrect.");
    freeMatrix(2, M); freeMatrix(3, N); freeMatrix(1, A_act); freeMatrix(1, A_exp);
}

Test(base_suite, multiplication_null_matrix_check, .description="M, N, or A is NULL returns -4") {
    int D[6] = {1, 1, 1, 1, 1, 1};

    int** N1 = initializeMatrix(1, 1, (int[]){1});
    int** A1 = initializeMatrix(1, 1, (int[]){0});
    int ret_null_M = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], NULL, N1, A1);
    cr_expect_eq(ret_null_M, -4, "Expected -4 when M is NULL, got %d.", ret_null_M);
    freeMatrix(1, N1); freeMatrix(1, A1);

    int** M2 = initializeMatrix(1, 1, (int[]){1});
    int** A2 = initializeMatrix(1, 1, (int[]){0});
    int ret_null_N = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M2, NULL, A2);
    cr_expect_eq(ret_null_N, -4, "Expected -4 when N is NULL, got %d.", ret_null_N);
    freeMatrix(1, M2); freeMatrix(1, A2);

    int** M3 = initializeMatrix(1, 1, (int[]){1});
    int** N3 = initializeMatrix(1, 1, (int[]){1});
    int ret_null_A = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M3, N3, NULL);
    cr_expect_eq(ret_null_A, -4, "Expected -4 when A is NULL, got %d.", ret_null_A);
    freeMatrix(1, M3); freeMatrix(1, N3);
}

Test(base_suite, multiplication_null_row_check, .description="Any row of M, N, or A is NULL returns -4") {
    int D[6] = {2, 2, 2, 2, 2, 2};

    int** M1 = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    free(M1[1]); M1[1] = NULL;
    int** N1 = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** A1 = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int ret_M_null_row = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M1, N1, A1);
    cr_expect_eq(ret_M_null_row, -4, "Expected -4 when a row of M is NULL, got %d.", ret_M_null_row);
    free(M1[0]); free(M1); freeMatrix(2, N1); freeMatrix(2, A1);

    int** M2 = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** N2 = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    free(N2[1]); N2[1] = NULL;
    int** A2 = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int ret_N_null_row = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M2, N2, A2);
    cr_expect_eq(ret_N_null_row, -4, "Expected -4 when a row of N is NULL, got %d.", ret_N_null_row);
    freeMatrix(2, M2); free(N2[0]); free(N2); freeMatrix(2, A2);

    int** M3 = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** N3 = initializeMatrix(2, 2, (int[]){5, 6, 7, 8});
    int** A3 = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    free(A3[1]); A3[1] = NULL;
    int ret_A_null_row = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M3, N3, A3);
    cr_expect_eq(ret_A_null_row, -4, "Expected -4 when a row of A is NULL, got %d.", ret_A_null_row);
    freeMatrix(2, M3); freeMatrix(2, N3); free(A3[0]); free(A3);
}

Test(base_suite, multiplication_invalid_dimensions, .description="Any dimension <= 0 returns -4") {
    int** M = initializeMatrix(0, 1, NULL);  
    int** N = initializeMatrix(1, 0, NULL);  
    int** A = initializeMatrix(0, 0, NULL);  
    int D[6] = {0, 1, 1, 0, 0, 0}; 
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A);
    int ret_exp = -4;
    cr_expect_eq(ret_act, ret_exp, "Expected -4 for any invalid dimension, got %d.", ret_act);
    freeMatrix(0, M);
    freeMatrix(1, N);
    freeMatrix(0, A);
}

Test(base_suite, multiplication_prioritize_structural_error, .description="Return -4 over other errors (structure invalid)") {
    int** M = NULL;
    int** N = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** A_act = initializeMatrix(1, 1, (int[]){0});
    int D[6] = {1, 2, 2, 2, 1, 1};
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = -4;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    freeMatrix(2, N);
    freeMatrix(1, A_act);
}

Test(base_suite, multiplication_A_not_zeroed, .description="Ensure A is overwritten even if initially non-zero") {
    int** M = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** N = initializeMatrix(2, 2, (int[]){5, 6, 7, 8});
    int** A_act = initializeMatrix(2, 2, (int[]){100, 100, 100, 100});
    int** A_exp = initializeMatrix(2, 2, (int[]){19, 22, 43, 50});
    int D[6] = {2, 2, 2, 2, 2, 2};
    int ret_act = Multiplication(D[0], D[1], D[2], D[3], D[4], D[5], M, N, A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "A was not overwritten correctly.");
    freeMatrix(2, M);
    freeMatrix(2, N);
    freeMatrix(2, A_act);
    freeMatrix(2, A_exp);
}


// Transpose Test Cases
Test(base_suite, transpose_case_exact_fit, .description="AT exactly fits the transpose of A") {
    int** A = initializeMatrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    int** AT = initializeMatrix(3, 2, (int[]){0, 0, 0, 0, 0, 0});
    int** AT_exp = initializeMatrix(3, 2, (int[]){1, 4, 2, 5, 3, 6});
    int D[4] = {2, 3, 3, 2};
    int ret_act = Transpose(D[0], D[1], D[2], D[3], A, AT);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(AT, AT_exp, 3, 2), "Transpose contents incorrect.");
    freeMatrix(2, A);
    freeMatrix(3, AT);
    freeMatrix(3, AT_exp);
}

Test(base_suite, transpose_case_oversized, .description="AT is larger than needed for the transpose") {
    int** A = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** AT = initializeMatrix(4, 4, (int[]){0});
    int** AT_exp = initializeMatrix(4, 4, (int[]){1, 3, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    int D[4] = {2, 2, 4, 4};
    int ret_act = Transpose(D[0], D[1], D[2], D[3], A, AT);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(AT, AT_exp, 4, 4), "Transpose contents incorrect.");
    freeMatrix(2, A);
    freeMatrix(4, AT);
    freeMatrix(4, AT_exp);
}

Test(base_suite, transpose_case_partial, .description="AT too small to hold full transpose, partial stored") {
    int** A = initializeMatrix(2, 3, (int[]){1, 2, 3, 4, 5, 6});
    int** AT = initializeMatrix(1, 1, (int[]){0});
    int** AT_exp = initializeMatrix(1, 1, (int[]){1});
    int D[4] = {2, 3, 1, 1};
    int ret_act = Transpose(D[0], D[1], D[2], D[3], A, AT);
    int ret_exp = -1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(AT, AT_exp, 1, 1), "Partial transpose incorrect.");
    freeMatrix(2, A);
    freeMatrix(1, AT);
    freeMatrix(1, AT_exp);
}

Test(base_suite, transpose_oversize_case, .description="AT has extra space beyond exact transpose fit") {
    int** A = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** AT = initializeMatrix(3, 3, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0});
    int** AT_exp = initializeMatrix(3, 3, (int[]){1, 3, 0, 2, 4, 0, 0, 0, 0});
    int D[4] = {2, 2, 3, 3};
    int ret_act = Transpose(D[0], D[1], D[2], D[3], A, AT);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(AT, AT_exp, 3, 3), "Transpose contents incorrect.");
    freeMatrix(2, A);
    freeMatrix(3, AT);
    freeMatrix(3, AT_exp);
}

Test(base_suite, transpose_generic_case, .description="Generic transpose of 2x3 matrix into 3x2") {
    int** A = initializeMatrix(2, 3, (int[]){7, 8, 9, 10, 11, 12});
    int** AT = initializeMatrix(3, 2, (int[]){0, 0, 0, 0, 0, 0});
    int** AT_exp = initializeMatrix(3, 2, (int[]){7, 10, 8, 11, 9, 12});
    int D[4] = {2, 3, 3, 2};
    int ret_act = Transpose(D[0], D[1], D[2], D[3], A, AT);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but should have been %d.", ret_act, ret_exp);
    cr_assert(areMatricesEqual(AT, AT_exp, 3, 2), "Transpose contents incorrect.");
    freeMatrix(2, A);
    freeMatrix(3, AT);
    freeMatrix(3, AT_exp);
}


// The following test cases are failing on my end. All of them belong to the Transpose function. I did not have time to debug them in time
Test(base_suite, transpose_null_matrix_check, .description="A or AT is NULL returns -2") {
    int D[4] = {1, 1, 1, 1};

    int** A1 = NULL;
    int** AT1 = initializeMatrix(1, 1, (int[]){0});
    int ret_null_A = Transpose(D[0], D[1], D[2], D[3], A1, AT1);
    cr_expect_eq(ret_null_A, -2, "Expected -2 when A is NULL, got %d.", ret_null_A);
    freeMatrix(1, AT1);

    int** A2 = initializeMatrix(1, 1, (int[]){1});
    int** AT2 = NULL;
    int ret_null_AT = Transpose(D[0], D[1], D[2], D[3], A2, AT2);
    cr_expect_eq(ret_null_AT, -2, "Expected -2 when AT is NULL, got %d.", ret_null_AT);
    freeMatrix(1, A2);
}

Test(base_suite, transpose_null_row_check, .description="Row in A or AT is NULL returns -2") {
    int D[4] = {2, 2, 2, 2};

    int** A1 = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int* tempA = A1[1];
    A1[1] = NULL;
    int** AT1 = initializeMatrix(2, 2, (int[]){0});
    int ret_row_null_A = Transpose(D[0], D[1], D[2], D[3], A1, AT1);
    cr_expect_eq(ret_row_null_A, -2, "Expected -2 when a row in A is NULL, got %d.", ret_row_null_A);
    A1[1] = tempA;
    freeMatrix(2, A1); freeMatrix(2, AT1);

    int** A2 = initializeMatrix(2, 2, (int[]){1, 2, 3, 4});
    int** AT2 = initializeMatrix(2, 2, (int[]){0});
    int* tempAT = AT2[1];
    AT2[1] = NULL;
    int ret_row_null_AT = Transpose(D[0], D[1], D[2], D[3], A2, AT2);
    cr_expect_eq(ret_row_null_AT, -2, "Expected -2 when a row in AT is NULL, got %d.", ret_row_null_AT);
    AT2[1] = tempAT;
    freeMatrix(2, A2); freeMatrix(2, AT2);
}

Test(base_suite, transpose_invalid_dimensions, .description="Any dimension <= 0 returns -2") {
    int** A = initializeMatrix(1, 1, (int[]){1});
    int** AT = initializeMatrix(1, 1, (int[]){0});
    int D[4] = {0, -1, 0, -1};
    int ret_act = Transpose(D[0], D[1], D[2], D[3], A, AT);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Expected -2 for any invalid dimension, got %d.", ret_act);
    freeMatrix(1, A);
    freeMatrix(1, AT);
}


