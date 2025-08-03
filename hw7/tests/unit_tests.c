/*
DO NOT CHANGE THE CONTENTS OF THIS FILE IN CASE A NEW VERSION IS DISTRIBUTED.
PUT YOUR OWN TEST CASES IN student_tests.c
*/

#include "unit_tests.h"
#include "hw7.h"

static char test_log_outfile[100];

int run_with_valgrind(char *test_name) {
#if defined(__linux__)
    char executable[100];
    sprintf(executable, "./bin/%s", test_name);
    assert(access(executable, F_OK) == 0);
    char cmd[500];
    sprintf(test_log_outfile, "%s/%s.log", TEST_OUTPUT_DIR, test_name);
    sprintf(cmd, "ulimit -f 300; ulimit -t 5; valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --error-exitcode=37 ./bin/%s > %s 2>&1",
	    test_name, test_log_outfile);
    return system(cmd);
#else
    cr_log_warn("Skipping valgrind tests. Run tests on Linux or GitHub for full output.\n");
    return 0;
#endif
}

int run_script_with_valgrind(char *script_file) {
#if defined(__linux__)
    char executable[100];
    sprintf(executable, "./bin/execute_script");
    assert(access(executable, F_OK) == 0);
    char cmd[500];
    sprintf(test_log_outfile, "%s/%s.log", TEST_OUTPUT_DIR, script_file);
    sprintf(cmd, "ulimit -f 300; ulimit -t 5; valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --error-exitcode=37 ./bin/execute_script %s > %s 2>&1",
	    script_file, test_log_outfile);
    return system(cmd);
#else
    cr_log_warn("Skipping valgrind tests. Run tests on Linux or GitHub for full output.\n");
    return 0;
#endif
}

// We use this version to check the correctness of the output.
void run_without_valgrind(char *test_name) {
    char executable[100];
    sprintf(executable, "./bin/%s", test_name);
    assert(access(executable, F_OK) == 0);
    char cmd[500];
    sprintf(test_log_outfile, "%s/%s.txt", TEST_OUTPUT_DIR, test_name);
    sprintf(cmd, "ulimit -f 300; ulimit -t 5; ./bin/%s > %s 2>&1", test_name, test_log_outfile);
    system(cmd);
    expect_outfile_matches(test_name);
}

void run_script_without_valgrind(char *script_file) {
    char executable[100];
    sprintf(executable, "./bin/execute_script");
    assert(access(executable, F_OK) == 0);
    char cmd[500];
    sprintf(test_log_outfile, "%s/%s.txt", TEST_OUTPUT_DIR, script_file);
    sprintf(cmd, "ulimit -f 300; ulimit -t 5; ./bin/execute_script %s > %s 2>&1",
        script_file, test_log_outfile);
    system(cmd);
    expect_outfile_matches(script_file);
}
void expect_normal_exit(int status) {
    cr_expect_eq(status, 0, "The program did not exit normally (status = %d).\n", status);
}

void expect_error_exit(int actual_status, int expected_status) {
    cr_expect_eq(WEXITSTATUS(actual_status), expected_status,
		 "The program exited with status %d instead of %d.\n", WEXITSTATUS(actual_status), expected_status);
}

void expect_no_valgrind_errors(int status) {
    cr_expect_neq(WEXITSTATUS(status), 37, "Valgrind reported errors -- see %s", test_log_outfile);
}

void expect_outfile_matches(char *name) {
    char cmd[500];
    sprintf(cmd, "diff tests.out.exp/%s.txt %s ", name, test_log_outfile);
    int err = system(cmd);
    cr_expect_eq(err, 0, "The output was not what was expected (diff exited with status %d).\n", WEXITSTATUS(err));
}

void print_array(unsigned int array[], unsigned int array_len) {
    for (unsigned int i = 0; i < array_len; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void expect_matrices_equal(matrix_sf *actual, unsigned int num_rows, unsigned int num_cols, int *values) {
    cr_expect_eq(actual->num_rows, num_rows);
    cr_expect_eq(actual->num_cols, num_cols);
    cr_expect_arr_eq(actual->values, values, num_cols*num_rows*sizeof(int),
            "Contents of matrix incorrect. See unit_tests.c or grading_tests.c for expected values.");
}

bst_sf* build_bst() {
    matrix_sf *A = copy_matrix(3, 5, (int[]){-4, 18, 6, 7, 10, -14, 29, 8, 21, -99, 0, 7, 5, 2, -9});
    A->name = 'A';
    matrix_sf *B = copy_matrix(3, 5, (int[]){10, 9, -2, -33, 22, 44, 10, 12, 72, 52, -88, 17, 16, 14, -9});
    B->name = 'B';
    matrix_sf *C = copy_matrix(1, 4, (int[]){-123, 47, -4, 140});  
    C->name = 'C';
    matrix_sf *D = copy_matrix(1, 4, (int[]){-16, 122, 135, 107});
    D->name = 'D';
    matrix_sf *E = copy_matrix(6, 4, (int[]){83, -22, 56, -1, 97, 94, 135, -10, 84, 40, -83, -4, 79, 28, 52, -101, 138, 146, 99, 0, -23, -73, -39, -47});
    E->name = 'E';
    matrix_sf *F = copy_matrix(4, 7, (int[]){-77, -20, 111, -2, 41, 117, 118, 21, -29, -45, 135, 98, 54, 131, 54, 1, 80, 143, -127, 148, 114, -81, 87, -33, -2, -6, 115, 59});
    F->name = 'F';
    matrix_sf *G = copy_matrix(7, 1, (int[]){-38, 4, 46, -14, -102, -72, -27});
    G->name = 'G';
    matrix_sf *H = copy_matrix(1, 5, (int[]){52, 65, -94, -73, -48});
    H->name = 'H';
    matrix_sf *I = copy_matrix(4, 4, (int[]){-7, 78, -87, -113, -144, -94, 22, -75, -137, -130, -113, -106, 85, -120, 50, 55});
    I->name = 'I';
    matrix_sf *J = copy_matrix(6, 3, (int[]){121, -1, 128, 78, -138, 138, -61, 51, -35, -84, 125, -83, -78, 138, 2, 81, -5, -36});
    J->name = 'J';
    bst_sf* Anode = malloc(sizeof(bst_sf));
    Anode->mat = A;
    Anode->left_child = NULL;
    Anode->right_child = NULL;
    bst_sf* Cnode = malloc(sizeof(bst_sf));
    Cnode->mat = C;
    Cnode->left_child = NULL;
    Cnode->right_child = NULL;
    bst_sf* Hnode = malloc(sizeof(bst_sf));
    Hnode->mat = H;
    Hnode->left_child = NULL;
    Hnode->right_child = NULL;
    bst_sf* Jnode = malloc(sizeof(bst_sf));
    Jnode->mat = J;
    Jnode->left_child = NULL;
    Jnode->right_child = NULL;
    bst_sf* Bnode = malloc(sizeof(bst_sf));
    Bnode->mat = B;
    Bnode->left_child = Anode;
    Bnode->right_child = Cnode;
    bst_sf* Fnode = malloc(sizeof(bst_sf));
    Fnode->mat = F;
    Fnode->left_child = NULL;
    Fnode->right_child = NULL;
    bst_sf* Inode = malloc(sizeof(bst_sf));
    Inode->mat = I;
    Inode->left_child = Hnode;
    Inode->right_child = Jnode;
    bst_sf* Dnode = malloc(sizeof(bst_sf));
    Dnode->mat = D;
    Dnode->left_child = Bnode;
    Dnode->right_child = NULL;
    bst_sf* Gnode = malloc(sizeof(bst_sf));
    Gnode->mat = G;
    Gnode->left_child = Fnode;
    Gnode->right_child = Inode;
    bst_sf* Enode = malloc(sizeof(bst_sf));
    Enode->mat = E;
    Enode->left_child = Dnode;
    Enode->right_child = Gnode;
    return Enode;
}

TestSuite(base_operator_return, .timeout=TEST_TIMEOUT, .disabled=false); // return value of add, mult, transpose
TestSuite(base_operator_valgrind, .timeout=TEST_TIMEOUT, .disabled=false); 

TestSuite(base_insert_bst, .timeout=TEST_TIMEOUT, .disabled=false); // test insert_bst_sf for correct BST update
TestSuite(base_find_bst, .timeout=TEST_TIMEOUT, .disabled=false);
TestSuite(base_free_bst, .timeout=TEST_TIMEOUT, .disabled=false);

TestSuite(base_create_matrix, .timeout=TEST_TIMEOUT, .disabled=false);
TestSuite(base_infix2postfix, .timeout=TEST_TIMEOUT, .disabled=false);
TestSuite(base_evaluate_expr, .timeout=TEST_TIMEOUT, .disabled=false);
TestSuite(base_execute, .timeout=TEST_TIMEOUT, .disabled=false); // execute_script_sf result
TestSuite(base_execute_valgrind, .timeout=TEST_TIMEOUT, .disabled=false);

/* add_mats_sf, mult_mats_sf, transpose_mat_sf tests */
// 1. call function to check for correctness
// 2. call function in a main() to check for memory errors
Test(base_operator_return, add01, .description="Add 2 3x5 matrices") {
    matrix_sf *A = copy_matrix(3, 5, (int[]){-4, 18, 6, 7, 10, -14, 29, 8, 21, -99, 0, 7, 5, 2, -9});
    matrix_sf *B = copy_matrix(3, 5, (int[]){10, 9, -2, -33, 22, 44, 10, 12, 72, 52, -88, 17, 16, 14, -9});
    matrix_sf *C = add_mats_sf(A, B);
    expect_matrices_equal(C, 3, 5, (int[]){6, 27, 4, -26, 32, 30, 39, 20, 93, -47, -88, 24, 21, 16, -18});
    free(A);
    free(B);
    free(C);
} 
Test(base_operator_valgrind, add01) { expect_no_valgrind_errors(run_with_valgrind("add01")); }

Test(base_operator_return, add02, .description="Add 2 1x4 matrices") {
    matrix_sf *Q = copy_matrix(1, 4, (int[]){-123, 47, -4, 140});  
    matrix_sf *G = copy_matrix(1, 4, (int[]){-16, 122, 135, 107});
    matrix_sf *Z = add_mats_sf(Q, G);
    expect_matrices_equal(Z, 1, 4, (int[]){-139, 169, 131, 247});
    free(Q);
    free(G);
    free(Z);
} 
Test(base_operator_valgrind, add02) { expect_no_valgrind_errors(run_with_valgrind("add02")); }

Test(base_operator_return, mult01, .description="Multiply 2 matrices") {
    matrix_sf *G = copy_matrix(6, 4, (int[]){83, -22, 56, -1, 97, 94, 135, -10, 84, 40, -83, -4, 79, 28, 52, -101, 138, 146, 99, 0, -23, -73, -39, -47});
    matrix_sf *D = copy_matrix(4, 7, (int[]){-77, -20, 111, -2, 41, 117, 118, 21, -29, -45, 135, 98, 54, 131, 54, 1, 80, 143, -127, 148, 114, -81, 87, -33, -2, -6, 115, 59});
    matrix_sf *Z = mult_mats_sf(G, D);
    expect_matrices_equal(Z, 6, 7, (int[]){-3748, -1053, 14716, 4874, -5859, 16696, 13237, 2605, -5401, 17667, 31821, -3896, 35255, 38560, -9786, -3271, 1016, -6629, 17929, -756, 5454, 5494, -11127, 15002, 11260, -15, 6836, 12959, -2214, -6895, 16668, 33591, 7393, 38682, 46696, 1939, -1551, -837, -15292, -2862, -17810, -19496});
    free(G);
    free(D);
    free(Z);
}
Test(base_operator_valgrind, mult01) { expect_no_valgrind_errors(run_with_valgrind("mult01")); }

Test(base_operator_return, mult02, .description="Multiply 2 matrices") {
    matrix_sf *U = copy_matrix(7, 1, (int[]){-38, 4, 46, -14, -102, -72, -27});
    matrix_sf *N = copy_matrix(1, 5, (int[]){52, 65, -94, -73, -48});
    matrix_sf *Z = mult_mats_sf(U, N);
    expect_matrices_equal(Z, 7, 5, (int[]){-1976, -2470, 3572, 2774, 1824, 208, 260, -376, -292, -192, 2392, 2990, -4324, -3358, -2208, -728, -910, 1316, 1022, 672, -5304, -6630, 9588, 7446, 4896, -3744, -4680, 6768, 5256, 3456, -1404, -1755, 2538, 1971, 1296});
    free(U);
    free(N);
    free(Z);
}
Test(base_operator_valgrind, mult02) { expect_no_valgrind_errors(run_with_valgrind("mult02")); }

Test(base_operator_return, trans01, .description="Transpose a 4x4 matrix") {
    matrix_sf *M = copy_matrix(4, 4, (int[]){-7, 78, -87, -113, -144, -94, 22, -75, -137, -130, -113, -106, 85, -120, 50, 55});
    matrix_sf *G = transpose_mat_sf(M);
    expect_matrices_equal(G, 4, 4, (int[]){-7, -144, -137, 85, 78, -94, -130, -120, -87, 22, -113, 50, -113, -75, -106, 55});
    free(M);
    free(G);
}
Test(base_operator_valgrind, trans01) { expect_no_valgrind_errors(run_with_valgrind("trans01")); }

Test(base_operator_return, trans02, .description="Transpose a 6x3 matrix") {
    matrix_sf *X = copy_matrix(6, 3, (int[]){121, -1, 128, 78, -138, 138, -61, 51, -35, -84, 125, -83, -78, 138, 2, 81, -5, -36});
    matrix_sf *G = transpose_mat_sf(X);
    expect_matrices_equal(G, 3, 6, (int[]){121, 78, -61, -84, -78, 81, -1, -138, 51, 125, 138, -5, 128, 138, -35, -83, 2, -36});
    free(X);
    free(G);
}
Test(base_operator_valgrind, trans02) { expect_no_valgrind_errors(run_with_valgrind("trans02")); }

/* insert_bst_sf() tests */
void inorder_sf(bst_sf *root, char *output) {
    if (!root) return;
    inorder_sf(root->left_child, output);
    char s[2] = {root->mat->name};
    strcat(output, s);
    inorder_sf(root->right_child, output);
}
int compare_chars_sf(const void* a, const void* b) { return (*(char*)a - *(char*)b); }
void sort_string_sf(char* str) { qsort(str, strlen(str), sizeof(char), compare_chars_sf); }

Test(base_insert_bst, insert_bst01, .description="Test if insert_bst_sf creates a valid BST.") {
    bst_sf *root = NULL;
    char names[] = "HBZ";
    matrix_sf *mats[strlen(names)];
    for (size_t i = 0; i < strlen(names); i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char output[27] = {0};
    inorder_sf(root, output);
    sort_string_sf(names);
    cr_expect_arr_eq(output, names, strlen(names), "BST does not store the nodes in sorted order.");
    for (size_t i = 0; i < strlen(names); i++)
        free(mats[i]);
    // Note: test does not deallocate memory of BST.    
}

Test(base_insert_bst, insert_bst02, .description="Test if insert_bst_sf creates a valid BST.") {
    bst_sf *root = NULL;
    char names[] = "HABETZ";
    matrix_sf *mats[strlen(names)];
    for (size_t i = 0; i < strlen(names); i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char output[27] = {0};
    inorder_sf(root, output);
    sort_string_sf(names);
    cr_expect_arr_eq(output, names, strlen(names), "BST does not store the nodes in sorted order.");
    for (size_t i = 0; i < strlen(names); i++)
        free(mats[i]);
    // Note: test does not deallocate memory of BST.    
}

Test(base_insert_bst, insert_bst03, .description="Test if insert_bst_sf creates a valid BST.") {
    bst_sf *root = NULL;
    char names[] = "GTHRNBVCUJELMOPSQZA";
    matrix_sf *mats[strlen(names)];
    for (size_t i = 0; i < strlen(names); i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char output[27] = {0};
    inorder_sf(root, output);
    sort_string_sf(names);
    cr_expect_arr_eq(output, names, strlen(names), "BST does not store the nodes in sorted order.");
    for (size_t i = 0; i < strlen(names); i++)
        free(mats[i]);
    // Note: test does not deallocate memory of BST.    
}

/* find_bst_sf() tests */
Test(base_find_bst, search_bst01, .description="Test if find_bst returns the correct matrix.") {
    bst_sf *root = NULL;
    char names[] = "HABETZ";
    matrix_sf *mats[strlen(names)];
    for (size_t i = 0; i < strlen(names); i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char *search_names = "BTZ";
    matrix_sf *mat;
    for (size_t i = 0; i < strlen(search_names); i++) {
        mat = find_bst_sf(search_names[i], root);
        cr_expect_eq(mat->name, search_names[i], 
            "The returned matrix did not have the expected name. Actual: %c, Expected: %c", mat->name, search_names[i]);
    } 
    
    for (size_t i = 0; i < strlen(names); i++)
        free(mats[i]);
    // Note: test does not deallocate memory of BST.  
}

Test(base_find_bst, search_bst02, .description="Test if find_bst returns the correct matrix.") {
    bst_sf *root = NULL;
    char names[] = "GTHRNBVCUJELMOPSQZA";
    matrix_sf *mats[strlen(names)];
    for (size_t i = 0; i < strlen(names); i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char *search_names = "ERPQT";
    matrix_sf *mat;
    for (size_t i = 0; i < strlen(search_names); i++) {
        mat = find_bst_sf(search_names[i], root);
        cr_expect_eq(mat->name, search_names[i], 
            "The returned matrix did not have the expected name. Actual: %c, Expected: %c", mat->name, search_names[i]);
    } 
    
    for (size_t i = 0; i < strlen(names); i++)
        free(mats[i]);
    // Note: test does not deallocate memory of BST.  
}

Test(base_find_bst, search_bst03, .description="Test if find_bst returns the correct matrix.") {
    bst_sf *root = NULL;
    char names[] = "GTHRNBVCUJELMOPSQZA";
    matrix_sf *mats[strlen(names)];
    for (size_t i = 0; i < strlen(names); i++) {
        mats[i] = malloc(sizeof(matrix_sf));
        mats[i]->name = names[i];
        root = insert_bst_sf(mats[i], root);
    }
    char *search_names = "AZXHODJAE";
    matrix_sf *mat;
    for (size_t i = 0; i < strlen(search_names); i++) {
        mat = find_bst_sf(search_names[i], root);
        if (search_names[i] == 'D' || search_names[i] == 'X')
            cr_expect_eq(mat, NULL, "The return value should have been NULL, but it was %p", mat);
        else
            cr_expect_eq(mat->name, search_names[i], 
                "The returned matrix did not have the expected name. Actual: %c, Expected: %c", mat->name, search_names[i]);
    } 
    
    for (size_t i = 0; i < strlen(names); i++)
        free(mats[i]);
    // Note: test does not deallocate memory of BST.  
}

/* free_bst_sf() tests */
Test(base_free_bst, free_bst01, .description="Test if BST is properly deallocated.") {
    expect_no_valgrind_errors(run_with_valgrind("free_bst01"));
}

Test(base_free_bst, free_bst02, .description="Test if BST is properly deallocated.") {
    expect_no_valgrind_errors(run_with_valgrind("free_bst02"));
}

Test(base_free_bst, free_bst03, .description="Test if BST is properly deallocated.") {
    expect_no_valgrind_errors(run_with_valgrind("free_bst03"));
}

/* create_matrix_sf() tests*/
Test(base_create_matrix, create01, .description="Create an 8x1 matrix") {
    matrix_sf *mat = create_matrix_sf('V', "8 1 [-105 ; -19 ; -140 ; 122 ; -123 ; 105 ; 90 ; 90 ; ]");
    expect_matrices_equal(mat, 8, 1, (int[]){-105, -19, -140, 122, -123, 105, 90, 90});
    cr_expect_eq(mat->name, 'V', "The new matrix did not have the expected name. Actual: %c, Expected: V", mat->name);
}

Test(base_create_matrix, create02, .description="Create a 7x3 matrix") {
    matrix_sf *mat = create_matrix_sf('Z', "7 3 [137 39 111 ; -142 -128 -45 ; 116 -135 134 ; 91 64 32 ; 88 148 139 ; 51 -45 35 ; 143 89 -64 ; ]");
    expect_matrices_equal(mat, 7, 3, (int[]){137, 39, 111, -142, -128, -45, 116, -135, 134, 91, 64, 32, 88, 148, 139, 51, -45, 35, 143, 89, -64});
    cr_expect_eq(mat->name, 'Z', "The new matrix did not have the expected name. Actual: %c, Expected: Z", mat->name);
}

/* infix2postfix_sf() tests */
Test(base_infix2postfix, infix2postfix01, .description="Convert a simple infix expression to posfix") {
    char *actual = infix2postfix_sf("A+B*C");
    char *expected = "ABC*+";
    cr_expect_arr_eq(actual, expected, strlen(expected), "The returned postfix expression was %s, but it should have been %s",
        actual, expected);
}

Test(base_infix2postfix, infix2postfix02, .description="Convert a moderately complex expression to posfix") {
    char *actual = infix2postfix_sf("(A+B)*(C+D)");
    char *expected = "AB+CD+*";
    cr_expect_arr_eq(actual, expected, strlen(expected), "The returned postfix expression was %s, but it should have been %s",
        actual, expected);
}

Test(base_infix2postfix, infix2postfix03, .description="Convert a moderately complex expression to posfix") {
    char *actual = infix2postfix_sf("(A+B)'*(C+D)*E'");
    char *expected = "AB+'CD+*E'*";
    cr_expect_arr_eq(actual, expected, strlen(expected), "The returned postfix expression was %s, but it should have been %s",
        actual, expected);
}

Test(base_infix2postfix, infix2postfix04, .description="Convert a complex expression to posfix") {
    char *actual = infix2postfix_sf("Z'+(A+B)'*(C+D)*E+((F'+G')*Z)+M'");
    char *expected = "Z'AB+'CD+*E*+F'G'+Z*+M'+";
    cr_expect_arr_eq(actual, expected, strlen(expected), "The returned postfix expression was %s, but it should have been %s",
        actual, expected);
}

/* evaluate_expr_sf tests*/
Test(base_evaluate_expr, expr01, .description="Given root of a tree, evaluation of an expression") {
    bst_sf* root = build_bst();
    matrix_sf* result = evaluate_expr_sf('R', "G * C + F'", root);
    expect_matrices_equal(result, 7, 4, (int[]){4597, -1765, 206, -5401, -512, 159, -15, 647, -5547, 2117, -104, 6407, 1720, -523, 199, -1962, 12587, -4696, 281, -14286, 8973, -3330, 436, -9965, 3439, -1138, 222, -3721});
}

Test(base_evaluate_expr, expr02, .description="Given root of a tree, evaluation of an expression") {
    bst_sf* root = build_bst();
    matrix_sf* result = evaluate_expr_sf('R', "(A + B) * H' * D", root);
    expect_matrices_equal(result, 3, 4, (int[]){-32848, 250466, 277155, 219671, 37088, -282796, -312930, -248026, 84704, -645868, -714690, -566458});
}

Test(base_evaluate_expr, expr03, .description="Given root of a tree, evaluation of an expression") {
    bst_sf* root = build_bst();
    matrix_sf* result = evaluate_expr_sf('R', "(I + D' * C) * E' * J", root);
    expect_matrices_equal(result, 4, 3, (int[]){-11171376, 56535582, 3236371, 69463160, -416294603, -47900609, 76095851, -459940949, -56668593, 60848961, -362841916, -37213021});
}

/* execute_script_sf tests */
// 1. call execute_script_sf() to check for correctness()
// 2. call execute_script_sf() via valgrind to check for memory errors
Test(base_execute, add_mats01) { run_script_without_valgrind("script01"); }
Test(base_execute_valgrind, add_mats01) { expect_no_valgrind_errors(run_script_with_valgrind("script01")); }

Test(base_execute, add_mats02) { run_script_without_valgrind("script02"); }
Test(base_execute_valgrind, add_mats02) { expect_no_valgrind_errors(run_script_with_valgrind("script02")); }

Test(base_execute, mult_mats01) { run_script_without_valgrind("script03"); }
Test(base_execute_valgrind, mult_mats01) { expect_no_valgrind_errors(run_script_with_valgrind("script03")); }

Test(base_execute, mult_mats02) { run_script_without_valgrind("script04"); }
Test(base_execute_valgrind, mult_mats02) { expect_no_valgrind_errors(run_script_with_valgrind("script04")); }

Test(base_execute, trans_mat01) { run_script_without_valgrind("script05"); }
Test(base_execute_valgrind, trans_mat01) { expect_no_valgrind_errors(run_script_with_valgrind("script05")); }

Test(base_execute, trans_mat02) { run_script_without_valgrind("script06"); }
Test(base_execute_valgrind, trans_mat02) { expect_no_valgrind_errors(run_script_with_valgrind("script06")); }

Test(base_execute, add_mats03) { run_script_without_valgrind("script07"); } // A + B + C
Test(base_execute_valgrind, add_mats03) { expect_no_valgrind_errors(run_script_with_valgrind("script07")); }

Test(base_execute, mult_mats03) { run_script_without_valgrind("script08"); } // A * B * C
Test(base_execute_valgrind, mult_mats03) { expect_no_valgrind_errors(run_script_with_valgrind("script08")); }

Test(base_execute, trans_mat03) { run_script_without_valgrind("script09"); } // A''
Test(base_execute_valgrind, trans_mat03) { expect_no_valgrind_errors(run_script_with_valgrind("script09")); }

Test(base_execute, script10) { run_script_without_valgrind("script10"); } // A * B + C
Test(base_execute_valgrind, script10) { expect_no_valgrind_errors(run_script_with_valgrind("script10")); }

Test(base_execute, script11) { run_script_without_valgrind("script11"); } // A + B * C
Test(base_execute_valgrind, script11) { expect_no_valgrind_errors(run_script_with_valgrind("script11")); }

Test(base_execute, script12) { run_script_without_valgrind("script12"); } // (A + B) * C
Test(base_execute_valgrind, script12) { expect_no_valgrind_errors(run_script_with_valgrind("script12")); }

Test(base_execute, script13) { run_script_without_valgrind("script13"); } // (A + B) * (C + D)
Test(base_execute_valgrind, script13) { expect_no_valgrind_errors(run_script_with_valgrind("script13")); }

Test(base_execute, script14) { run_script_without_valgrind("script14"); } // (A + B * C) * (C + D * E) * (E + F * G)
Test(base_execute_valgrind, script14) { expect_no_valgrind_errors(run_script_with_valgrind("script14")); }

Test(base_execute, script15) { run_script_without_valgrind("script15"); } // (A + B * C) * (C + D * E)
Test(base_execute_valgrind, script15) { expect_no_valgrind_errors(run_script_with_valgrind("script15")); }

Test(base_execute, script16) { run_script_without_valgrind("script16"); } // A' * B + C
Test(base_execute_valgrind, script16) { expect_no_valgrind_errors(run_script_with_valgrind("script16")); }

Test(base_execute, script17) { run_script_without_valgrind("script17"); } // (A' * B + C)'
Test(base_execute_valgrind, script17) { expect_no_valgrind_errors(run_script_with_valgrind("script17")); }

Test(base_execute, script18) { run_script_without_valgrind("script18"); } 
Test(base_execute_valgrind, script18) { expect_no_valgrind_errors(run_script_with_valgrind("script18")); }

Test(base_execute, script19) { run_script_without_valgrind("script19"); } 
Test(base_execute_valgrind, script19) { expect_no_valgrind_errors(run_script_with_valgrind("script19")); }

Test(base_execute, script20) { run_script_without_valgrind("script20"); } 
Test(base_execute_valgrind, script20) { expect_no_valgrind_errors(run_script_with_valgrind("script20")); }

