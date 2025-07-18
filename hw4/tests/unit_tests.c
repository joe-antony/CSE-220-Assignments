/*
DO NOT CHANGE THE CONTENTS OF THIS FILE IN CASE A NEW VERSION IS DISTRIBUTED.
PUT YOUR OWN TEST CASES IN student_tests.c
*/

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


// encrypt
Test(base_suite, encrypt_full_msg, .description="A full plaintext message can be encrypted.") {
    const char *plaintext = "System Fundamentals";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 1);
    char *ciphertext_exp = "Tztufn Gvoebnfoubmt__EOM__";
    int count_exp = 18;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(base_suite, encrypt_full_msg_numbers, .description="A full plaintext message with numbers can be encrypted.") {
    const char *plaintext = "Cse220";
    char ciphertext_act[] = "***I can store any message!***";
    int count_act = encrypt(plaintext, ciphertext_act, 1);
    char *ciphertext_exp = "Dtf331__EOM__";
    int count_exp = 6;
    cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// decrypt
Test(base_suite, decrypt_full_msg, .description="A full ciphertext message can be decrypted.") {
    const char *ciphertext = "Tztufn Gvoebnfoubmt__EOM__";
    char plaintext_act[] = "***I can store any message!***";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "System Fundamentals";
    int count_exp = 18;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "ciphertext was:          %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(base_suite, decrypt_full_msg_numbers, .description="A full ciphertext message with numbers can be decrypted.") {
    const char *ciphertext = "Dtf331__EOM__";
    char plaintext_act[] = "I can store any message!";
    int count_act = decrypt(ciphertext, plaintext_act, 1);
    char *plaintext_exp = "Cse220";
    int count_exp = 6;
    cr_expect_str_eq(plaintext_act, plaintext_exp, "ciphertext was:          %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}