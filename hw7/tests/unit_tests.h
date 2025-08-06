#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "criterion/criterion.h"
#include "hw7.h"

#define TEST_TIMEOUT 10
#define TEST_INPUT_DIR "tests.in"
#define TEST_OUTPUT_DIR "tests.out"

int run_with_valgrind(char *test_name);
void run_without_valgrind(char *test_name);
int run_script_with_valgrind(char *script_file);
void run_script_without_valgrind(char *script_file);
void expect_normal_exit(int status);
void expect_no_valgrind_errors(int status);
void expect_outfile_matches(char *name);

void expect_matrices_equal(matrix_sf *actual, unsigned int num_rows, unsigned int num_cols, int *values);






