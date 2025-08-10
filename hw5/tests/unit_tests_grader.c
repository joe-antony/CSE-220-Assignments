/*
DO NOT CHANGE THE CONTENTS OF THIS FILE IN CASE A NEW VERSION IS DISTRIBUTED.
PUT YOUR OWN TEST CASES IN student_tests.c
*/

#include "global.h"
#include "unit_tests.h"

static char test_log_outfile[100];

int run_using_system(char *test_name) {
    char executable[100];
    sprintf(executable, "./bin/%s", test_name);
    assert(access(executable, F_OK) == 0);

    char cmd[500];
    sprintf(test_log_outfile, "%s/%s.log", TEST_OUTPUT_DIR, test_name);
#if defined(__linux__)
    sprintf(cmd, "valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --error-exitcode=37 ./bin/%s > %s 2>&1",
	    test_name, test_log_outfile);
#else
    cr_log_warn("Skipping valgrind tests. Run tests on Linux or GitHub for full output.\n");
    sprintf(cmd, "./bin/%s > %s 2>&1", test_name, test_log_outfile);
#endif
    return system(cmd);
}

void assert_normal_exit(int status) {
    cr_expect_eq(status, 0, "The program did not exit normally (status = 0x%x).\n", status);
}

void assert_error_exit(int status) {
    cr_expect_eq(WEXITSTATUS(status), 0xff,
		 "The program did not exit with status 0xff (status was 0x%x).\n", status);
}

void assert_no_valgrind_errors(int status) {
    cr_expect_neq(WEXITSTATUS(status), 37, "Valgrind reported errors -- see %s", test_log_outfile);
    if (WEXITSTATUS(status) == 37) {
        char cmd[200];
        sprintf(cmd, "cat %s", test_log_outfile);
        system(cmd);
    }
}

TestSuite(base_suite, .timeout=TEST_TIMEOUT);

bool areMatricesEqual(int** matrix1, int** matrix2, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;  // Matrices have different elements.
            }
        }
    }
    return true;  // Matrices are equal.
}
#ifndef GRADER_TESTS
Test(base_suite, SparseMatrix_full, .description="Full Sparse Matrix") {
    int** M = initializeMatrix(4, 2, (int[]){0,4,0,5,0,0,2,0});
    int** S_act = initializeMatrix(3, 4, (int[]){0,0,0,0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 4, (int[]){0,1,3,0,1,1,0,0,4,5,2,0});
    int row = 4;
    int col = 2;
    int ret_act = SparseMatrix(row, col, M, S_act);
    int ret_exp = 3;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 4), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(4, M); freeMatrix(3, S_act); freeMatrix(3, S_exp);
}

Test(base_suite, addition_case_yes, .description="Matrices are compatible for addition") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 1, 3, 4, 5});
    int** N = initializeMatrix(3, 2, (int[]){3, 3, 7, 2, 1,5});
    int** A_act = initializeMatrix(3, 2, (int[]){0, 0, 0, 0, 0,0});
    int** A_exp = initializeMatrix(3, 2, (int[]){5, 6, 8, 5, 5,10});
    int D[6] = {3,2,3,2,3,2};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 2), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(3, N); freeMatrix(3, A_act); freeMatrix(3, A_exp);
}

Test(base_suite, addition_case_no, .description="Matrices are compatible for addition, but not A. A also contains garbage values") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 1, 3, 4, 5});
    int** N = initializeMatrix(3, 2, (int[]){3, 3, 7, 2, 1,5});
    int** A_act = initializeMatrix(3, 3, (int[]){5, 6, 0, 8, 5, 0, 5, 10, 0});
    int** A_exp = initializeMatrix(3, 3, (int[]){5, 6, 0, 8, 5, 0, 5, 10, 0});
    int D[6] = {3,2,3,2,3,3};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 3), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(3, N); freeMatrix(3, A_act); freeMatrix(3, A_exp);
}

Test(base_suite, addition_case_no_small, .description="Matrices are incompatible for addition, and A has little space") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 1, 3, 4, 5});
    int** N = initializeMatrix(4, 2, (int[]){5, 6, 8, 5, 5, 10, 5,10});
    int** A_act = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int** A_exp = initializeMatrix(2, 2, (int[]){7, 9, 9, 8});
    int D[6] = {3,2,4,2,2,2};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(4, N); freeMatrix(2, A_act); freeMatrix(2, A_exp);
}

Test(base_suite, addition_case_no_big, .description="Matrices are incompatible for addition, and A has enough space") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 1, 3, 4, 5});
    int** N = initializeMatrix(4, 2, (int[]){5, 6, 8, 5, 5, 10, 5,10});
    int** A_act = initializeMatrix(5, 2, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    int** A_exp = initializeMatrix(5, 2, (int[]){7, 9, 9, 8, 9, 15, 0, 0, 0, 0});
    int D[6] = {3,2,4,2,5,2};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = -1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 5, 2), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(4, N); freeMatrix(5, A_act); freeMatrix(5, A_exp);
}

Test(base_suite, addition_case_yes_small, .description="Matrices are compatible, but A is small") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 1, 3, 4, 5});
    int** N = initializeMatrix(3, 2, (int[]){3, 3, 7, 2, 1, 5});
    int** A_act = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int** A_exp = initializeMatrix(2, 2, (int[]){5, 6, 8, 5});
    int D[6] = {3,2,3,2,2,2};
    int ret_act = Addition(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = -3;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(3, N); freeMatrix(2, A_act); freeMatrix(2, A_exp);
}

Test(base_suite, multiplication_case_yes, .description="Matrices are compatible for multiplication") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 5, 4, 2, 3});
    int** N = initializeMatrix(2, 3, (int[]){3, 2, 1, 1, 3, 4});
    int** A_act = initializeMatrix(3, 3, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0});
    int** A_exp = initializeMatrix(3, 3, (int[]){9, 13, 14, 19, 22, 21, 9, 13, 14});
    int D[6] = {3,2,2,3,3,3};
    int ret_act = Multiplication(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 3), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(2, N); freeMatrix(3, A_act); freeMatrix(3, A_exp);
}

Test(base_suite, multiplication_case_no_small, .description="Matrices are incompatible for multiplicaiton, and A is small") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 5, 4, 2, 3});
    int** N = initializeMatrix(3, 2, (int[]){3, 3, 7, 2, 1, 5});
    int** A_act = initializeMatrix(2, 2, (int[]){0, 0, 0, 0});
    int** A_exp = initializeMatrix(2, 2, (int[]){27, 12, 43, 23});
    int D[6] = {3,2,3,2,2,2};
    int ret_act = Multiplication(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = -2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 2), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(3, N); freeMatrix(2, A_act); freeMatrix(2, A_exp);
}

Test(base_suite, multiplication_case_no_big, .description="Matrices are incompatible for multiplicaiton, but A is big") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 5, 4, 2, 3});
    int** N = initializeMatrix(3, 2, (int[]){3, 3, 7, 2, 1, 5});
    int** A_act = initializeMatrix(4, 3, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    int** A_exp = initializeMatrix(4, 3, (int[]){27,12,0,43,23,0,27,12,0,0,0,0});
    int D[6] = {3,2,3,2,4,3};
    int ret_act = Multiplication(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = -1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 4, 3), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(3, N); freeMatrix(4, A_act); freeMatrix(4, A_exp);
}

Test(base_suite, multiplication_case_yes_big, .description="Matrices are compatible for multiplicaiton, but A is big") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 5, 4, 2, 3});
    int** N = initializeMatrix(2, 3, (int[]){3, 2, 1, 1, 3, 4});
    int** A_act = initializeMatrix(4, 4, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0});
    int** A_exp = initializeMatrix(4, 4, (int[]){9,13,14,0,19,22,21,0,9,13,14,0,0, 0,0, 0});
    int D[6] = {3,2,2,3,4,4};
    int ret_act = Multiplication(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 4, 4), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(2, N); freeMatrix(4, A_act); freeMatrix(4, A_exp);
}

Test(base_suite, multiplication_case_yes_incorrect, .description="Matrices are compatible for multiplicaiton, but A is incorrect") {
    int** M = initializeMatrix(3, 2, (int[]){ 2, 3, 5, 4, 2, 3});
    int** N = initializeMatrix(2, 3, (int[]){3, 2, 1, 1, 3, 4});
    int** A_act = initializeMatrix(2, 4, (int[]){0, 0, 0, 0, 0, 0, 0, 0});
    int** A_exp = initializeMatrix(2, 4, (int[]){9,13,14,0,19,22,21,0});    
    int D[6] = {3,2,2,3,2,4};
    int ret_act = Multiplication(D[0],D[1],D[2],D[3],D[4],D[5],M, N, A_act);
    int ret_exp = -3;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 4), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(2, N); freeMatrix(2, A_act); freeMatrix(2, A_exp);
}

Test(base_suite, transpose_case_yes, .description="Matrices are compatible for transpose") {
    int** M = initializeMatrix(3, 2, (int[]){9, 9, 1, 2, 9, 3});
    int** A_act = initializeMatrix(2, 3, (int[]){0, 0, 0, 0, 0, 0});
    int** A_exp = initializeMatrix(2, 3, (int[]){9, 1, 9, 9, 2, 3});
    int D[4] = {3,2,2,3};
    int ret_act = Transpose(D[0],D[1],D[2],D[3],M, A_act);
    int ret_exp = 1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 2, 3), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(2, A_act); freeMatrix(2, A_exp);
}

Test(base_suite, transpose_case_no, .description="Matrices are incompatible for transpose") {
    int** M = initializeMatrix(3, 2, (int[]){9, 9, 1, 2, 9, 3});
    int** A_act = initializeMatrix(3, 2, (int[]){0, 0, 0, 0, 0, 0});
    int** A_exp = initializeMatrix(3, 2, (int[]){9, 1, 9, 2, 0, 0});
    int D[4] = {3,2,3,2};
    int ret_act = Transpose(D[0],D[1],D[2],D[3],M, A_act);
    int ret_exp = -1;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 2), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(3, A_act); freeMatrix(3, A_exp);
}

Test(base_suite, transpose_case_no_big, .description="Matrices are incompatible for transpose") {
    int** M = initializeMatrix(3, 2, (int[]){9, 9, 1, 2, 9, 3});
    int** A_act = initializeMatrix(4, 4, (int[]){0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0});
    int** A_exp = initializeMatrix(4, 4, (int[]){9, 1, 9, 0, 9,2,3,0,0,0,0,0,0,0,0,0});
    int D[4] = {3,2,4,4};
    int ret_act = Transpose(D[0],D[1],D[2],D[3],M, A_act);
    int ret_exp = 2;
    cr_expect_eq(ret_act, ret_exp, "Return value was %d, but it should have been %d.\n", ret_act, ret_exp);
    cr_assert(areMatricesEqual(A_act, A_exp, 4, 4), "Contents of matrix incorrect. See unit_tests.c for expected values.");
    freeMatrix(3, M); freeMatrix(4, A_act); freeMatrix(4, A_exp);
}

//Case 1: Sparse (non-zero <= max dim), returns count
Test(grader_suite, sparse_case_sparse_valid, .description="Sparse matrix valid, fills correctly") {
    int** M = initializeMatrix(4, 2, (int[]){0,4, 5,0, 0,0, 2,0});
    int** S_act = initializeMatrix(3, 4, (int[]){0,0,0,0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 4, (int[]){0,1,3,0, 1,0,0,0, 4,5,2,0});
    int ret_act = SparseMatrix(4, 2, M, S_act);
    int ret_exp = 3;
    cr_expect_eq(ret_act, ret_exp);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 4));
    freeMatrix(4, M); freeMatrix(3, S_act); freeMatrix(3, S_exp);
}

// Case 2: Not sparse (non-zero > max dim), returns -1
Test(grader_suite, sparse_case_not_sparse, .description="Matrix not sparse, return -1") {
    int** M = initializeMatrix(4, 4, (int[]){
        1,0,2,3, 0,4,5,0, 6,0,0,0, 0,7,8,9
    });
    int** S_act = initializeMatrix(3, 4, (int[]){0,0,0,0,0,0,0,0,0,0,0,0});
    int ret_act = SparseMatrix(4, 4, M, S_act);
    cr_expect_eq(ret_act, -1);
    freeMatrix(4, M); freeMatrix(3, S_act);
}

// Case 3: All zeros (0 non-zero elements)
Test(grader_suite, sparse_case_all_zero, .description="Sparse matrix all zeros, fills S with zeros") {
    int** M = initializeMatrix(3, 3, (int[]){0,0,0, 0,0,0, 0,0,0});
    int** S_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 3, (int[]){0,0,0, 0,0,0, 0,0,0});
    int ret_act = SparseMatrix(3, 3, M, S_act);
    cr_expect_eq(ret_act, 0);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 3));
    freeMatrix(3, M); freeMatrix(3, S_act); freeMatrix(3, S_exp);
}

// Case 4: Exactly max dim non-zero
Test(grader_suite, sparse_case_exact_maxdim, .description="Number of non-zero elements == max dim") {
    int** M = initializeMatrix(3, 5, (int[]){
        1,0,0,0,7, 0,2,0,0,0, 0,0,3,0,4
    });
    int** S_act = initializeMatrix(3, 5, (int[]){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 5, (int[]){0,0,1,2,2, 0,4,1,2,4, 1,7,2,3,4});
    int ret_act = SparseMatrix(3, 5, M, S_act);
    cr_expect_eq(ret_act, 5);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 5));
    freeMatrix(3, M); freeMatrix(3, S_act); freeMatrix(3, S_exp);
}

// Case 5: Rectangular tall matrix
Test(grader_suite, sparse_case_tall_matrix, .description="Tall matrix with a few non-zero elements") {
    int** M = initializeMatrix(5, 2, (int[]){
        0,0, 3,0, 0,0, 4,0, 0,0
    });
    int** S_act = initializeMatrix(3, 5, (int[]){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    int** S_exp = initializeMatrix(3, 5, (int[]){1,3,0,0,0, 0,0,0,0,0, 3,4,0,0,0});
    int ret_act = SparseMatrix(5, 2, M, S_act);
    cr_expect_eq(ret_act, 2);
    cr_assert(areMatricesEqual(S_act, S_exp, 3, 5));
    freeMatrix(5, M); freeMatrix(3, S_act); freeMatrix(3, S_exp);
}

// Case 1: Fully compatible (return 1)
Test(grader_suite, add_case_full_compat, .description="M and N same size, A same size -> return 1") {
    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(3, 2, (int[]){4,5,6,7,8,9});
    int** A_act = initializeMatrix(3, 2, (int[]){0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 2, (int[]){5,7,9,11,13,15});
    int ret_act = Addition(3,2,3,2,3,2,M,N,A_act);
    cr_expect_eq(ret_act, 1);
    cr_assert(areMatricesEqual(A_act, A_exp, 3, 2));
    freeMatrix(3,M); freeMatrix(3,N); freeMatrix(3,A_act); freeMatrix(3,A_exp);
}

// Case 2: Compatible M & N, A oversized (return 2)
Test(grader_suite, add_case_a_oversized, .description="M & N same, A bigger -> return 2") {
    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(3, 2, (int[]){4,5,6,7,8,9});
    int** A_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 3, (int[]){5,7,0,9,11,0,13,15,0});
    int ret_act = Addition(3,2,3,2,3,3,M,N,A_act);
    cr_expect_eq(ret_act, 2);
    cr_assert(areMatricesEqual(A_act,A_exp,3,3));
    freeMatrix(3,M); freeMatrix(3,N); freeMatrix(3,A_act); freeMatrix(3,A_exp);
}

// Case 3: Compatible M & N, A too small (return -3)
Test(grader_suite, add_case_a_too_small_fullcompat, .description="M & N compatible, A too small -> -3") {
    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(3, 2, (int[]){4,5,6,7,8,9});
    int** A_act = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int** A_exp = initializeMatrix(2, 2, (int[]){5,7,9,11});
    int ret_act = Addition(3,2,3,2,2,2,M,N,A_act);
    cr_expect_eq(ret_act, -3);
    cr_assert(areMatricesEqual(A_act,A_exp,2,2));
    freeMatrix(3,M); freeMatrix(3,N); freeMatrix(2,A_act); freeMatrix(2,A_exp);
}

// Case 4: Incompatible M & N, A fits result (-1)
Test(grader_suite, add_case_incompat_a_fits, .description="M & N diff size, A fits overlap (-1)") {
    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(4, 2, (int[]){6,7,8,9,10,11,12,13});
    int** A_act = initializeMatrix(3, 2, (int[]){0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 2, (int[]){7,9,11,13,15,17});
    int ret_act = Addition(3,2,4,2,3,2,M,N,A_act);
    cr_expect_eq(ret_act,-1);
    cr_assert(areMatricesEqual(A_act,A_exp,3,2));
    freeMatrix(3,M); freeMatrix(4,N); freeMatrix(3,A_act); freeMatrix(3,A_exp);
}

// Case 5: Incompatible M & N, A small (-2)
Test(grader_suite, add_case_incompat_a_small, .description="M & N diff, A smaller than overlap (-2)") {
    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(4, 2, (int[]){6,7,8,9,10,11,12,13});
    int** A_act = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int** A_exp = initializeMatrix(2, 2, (int[]){7,9,11,13});
    int ret_act = Addition(3,2,4,2,2,2,M,N,A_act);
    cr_expect_eq(ret_act,-2);
    cr_assert(areMatricesEqual(A_act,A_exp,2,2));
    freeMatrix(3,M); freeMatrix(4,N); freeMatrix(2,A_act); freeMatrix(2,A_exp);
}

// Case 1: Fully compatible, exact A size -> return 1
Test(grader_suite, mult_case_full_compat, .description="M*N exact size -> 1") {
    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(2, 3, (int[]){1,2,3,4,5,6});
    int** A_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 3, (int[]){9,12,15,19,26,33,29,40,51});
    int ret_act = Multiplication(3,2,2,3,3,3,M,N,A_act);
    cr_expect_eq(ret_act,1);
    cr_assert(areMatricesEqual(A_act,A_exp,3,3));
    freeMatrix(3,M); freeMatrix(2,N); freeMatrix(3,A_act); freeMatrix(3,A_exp);
}

// Case 2: Compatible, A oversized -> return 2
Test(grader_suite, mult_case_a_oversized, .description="M*N compatible, A bigger -> return 2") {
    int** M = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** N = initializeMatrix(2, 2, (int[]){5,6,7,8});
    int** A_act = initializeMatrix(3, 3, (int[]){0,0,0,0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 3, (int[]){19,22,0,43,50,0,0,0,0});
    int ret_act = Multiplication(2,2,2,2,3,3,M,N,A_act);
    cr_expect_eq(ret_act,2);
    cr_assert(areMatricesEqual(A_act,A_exp,3,3));
    freeMatrix(2,M); freeMatrix(2,N); freeMatrix(3,A_act); freeMatrix(3,A_exp);
}

// Case 3: Compatible, A too small -> return -3
Test(grader_suite, mult_case_a_small_fullcompat, .description="M*N compatible, A small -> -3") {
    int** M = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** N = initializeMatrix(2, 3, (int[]){1,2,3,4,5,6});
    int** A_act = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int** A_exp = initializeMatrix(2, 2, (int[]){9,12,19,26});
    int ret_act = Multiplication(3,2,2,3,2,2,M,N,A_act);
    cr_expect_eq(ret_act,-3);
    cr_assert(areMatricesEqual(A_act,A_exp,2,2));
    freeMatrix(3,M); freeMatrix(2,N); freeMatrix(2,A_act); freeMatrix(2,A_exp);
}

// Case 4: Incompatible, A fits overlap (-1)
Test(grader_suite, mult_case_incompat_a_fits, .description="M & N diff, partial multiply, A fits -> -1") {
    int** M = initializeMatrix(3, 3, (int[]){1,2,3,4,3,6,7,8,9});
    int** N = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** A_act = initializeMatrix(3, 2, (int[]){0,0,0,0,0,0});
    int** A_exp = initializeMatrix(3, 2, (int[]){7,10,13,20,31,46});
    int ret_act = Multiplication(3,3,2,2,3,2,M,N,A_act);
    cr_expect_eq(ret_act,-1);
    cr_assert(areMatricesEqual(A_act,A_exp,3,2));
    freeMatrix(3,M); freeMatrix(2,N); freeMatrix(3,A_act); freeMatrix(3,A_exp);
}

// Case 5: Incompatible, A small (-2)
Test(grader_suite, mult_case_incompat_a_small, .description="M & N diff, partial multiply, A too small -> -2") {
    int** M = initializeMatrix(3, 3, (int[]){1,2,3,4,3,6,7,8,9});
    int** N = initializeMatrix(2, 2, (int[]){1,2,3,4});
    int** A_act = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int** A_exp = initializeMatrix(2, 2, (int[]){7,10,13,20});
    int ret_act = Multiplication(3,3,2,2,2,2,M,N,A_act);
    cr_expect_eq(ret_act,-2);
    cr_assert(areMatricesEqual(A_act,A_exp,2,2));
    freeMatrix(3,M); freeMatrix(2,N); freeMatrix(2,A_act); freeMatrix(2,A_exp);
}

// Case 1: Compatible exact -> return 1
Test(grader_suite, trans_case_exact, .description="A transpose fits exactly -> 1") {
    int** A = initializeMatrix(3, 2, (int[]){1,2,3,4,5,6});
    int** AT_act = initializeMatrix(2, 3, (int[]){0,0,0,0,0,0});
    int** AT_exp = initializeMatrix(2, 3, (int[]){1,3,5,2,4,6});
    int ret_act = Transpose(3,2,2,3,A,AT_act);
    cr_expect_eq(ret_act,1);
    cr_assert(areMatricesEqual(AT_act,AT_exp,2,3));
    freeMatrix(3,A); freeMatrix(2,AT_act); freeMatrix(2,AT_exp);
}

// Case 2: AT oversized -> return 2
Test(grader_suite, trans_case_oversized, .description="Transpose fits inside larger AT -> 2") {
    int** A = initializeMatrix(3, 2, (int[]){9,1,9,2,0,3});
    int** AT_act = initializeMatrix(4, 4, (int[]){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    int** AT_exp = initializeMatrix(4, 4, (int[]){9,9,0,0,1,2,3,0,0,0,0,0,0,0,0,0});
    int ret_act = Transpose(3,2,4,4,A,AT_act);
    cr_expect_eq(ret_act,2);
    cr_assert(areMatricesEqual(AT_act,AT_exp,4,4));
    freeMatrix(3,A); freeMatrix(4,AT_act); freeMatrix(4,AT_exp);
}

// Case 3: AT small -> return -1
Test(grader_suite, trans_case_small, .description="Transpose matrix too small -> -1") {
    int** A = initializeMatrix(3, 2, (int[]){9,1,9,2,0,3});
    int** AT_act = initializeMatrix(2, 2, (int[]){0,0,0,0});
    int** AT_exp = initializeMatrix(2, 2, (int[]){9,9,1,2});
    int ret_act = Transpose(3,2,2,2,A,AT_act);
    cr_expect_eq(ret_act,-1);
    cr_assert(areMatricesEqual(AT_act,AT_exp,2,2));
    freeMatrix(3,A); freeMatrix(2,AT_act); freeMatrix(2,AT_exp);
}

// Case 4: 1x1 matrix
Test(grader_suite, trans_case_1x1, .description="Transpose of 1x1 is itself") {
    int** A = initializeMatrix(1, 1, (int[]){5});
    int** AT_act = initializeMatrix(1, 1, (int[]){0});
    int** AT_exp = initializeMatrix(1, 1, (int[]){5});
    int ret_act = Transpose(1,1,1,1,A,AT_act);
    cr_expect_eq(ret_act,1);
    cr_assert(areMatricesEqual(AT_act,AT_exp,1,1));
    freeMatrix(1,A); freeMatrix(1,AT_act); freeMatrix(1,AT_exp);
}

// Case 5: Wide matrix transpose into tall target
Test(grader_suite, trans_case_wide_to_tall, .description="Wide matrix into taller AT") {
    int** A = initializeMatrix(2, 4, (int[]){1,2,3,4,5,6,7,8});
    int** AT_act = initializeMatrix(4, 3, (int[]){0,0,0,0,0,0,0,0,0,0,0,0});
    int** AT_exp = initializeMatrix(4, 3, (int[]){1,5,0,2,6,0,3,7,0,4,8,0});
    int ret_act = Transpose(2,4,4,3,A,AT_act);
    cr_expect_eq(ret_act,2);
    cr_assert(areMatricesEqual(AT_act,AT_exp,4,3));
    freeMatrix(2,A); freeMatrix(4,AT_act); freeMatrix(4,AT_exp);
}

#endif
/*
DO NOT CHANGE THE CONTENTS OF THIS FILE IN CASE A NEW VERSION IS DISTRIBUTED.
PUT YOUR OWN TEST CASES IN student_tests.c
*/
